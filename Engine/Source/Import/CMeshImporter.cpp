/// \file       CMeshImporter.cpp
/// \date       01/08/2018
/// \project    OOM-Engine
/// \package    Import
/// \author     Vincent STEHLY--CALISTO


#include "Engine/CEngine.hpp"
#include "Core/Debug/SLogger.hpp"
#include "Import/CMeshImporter.hpp"
#include "Composite/CGameObject.hpp"
#include "Import/CTextureImporter.hpp"

#include "Render/Mesh/CMeshFilter.hpp"
#include "Render/Material/CMaterial.hpp"
#include "Render/Renderer/CMeshRenderer.hpp"

namespace Oom
{

std::vector<CGameObject*> CMeshImporter::ImportFromObj(const char* p_path)
{
    std::vector<CGameObject*> game_objects;

    FILE* file_descriptor = fopen(p_path, "r");
    if(!file_descriptor)
    {
        SLogger::LogError("Mesh importer : Unable to open %s.", p_path);
        return game_objects;
    }

    char p_buffer[1024];
    while(fgets(p_buffer, sizeof(p_buffer), file_descriptor) != nullptr)
    {
        size_t line_size = strlen(p_buffer);
        p_buffer[line_size - 1] = '\0';

        if(p_buffer[0] == 'o')
        {
			ImportObj(file_descriptor, p_buffer, game_objects);
        }
    }

    // Closing the descriptor
    fclose(file_descriptor);

    return game_objects;
}

void CMeshImporter::ImportObj(FILE* file_descriptor, char* current_line, std::vector<CGameObject*>& game_objects)
{
	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec3> _normals;
	std::vector<glm::vec2> _uvs;
	
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;

	int counter = 0;
    GLuint texture_id = 0;

	// Getting the name for the first time
	char p_name[128] = { '\0' };
	sscanf(current_line, "o %s", p_name);

    char p_buffer[1024];
    while(fgets(p_buffer, sizeof(p_buffer), file_descriptor) != nullptr)
    {
        if(p_buffer[0] == 'o')
        {
			// We get our gameoobject
			CGameObject* p_game_object = CEngine::Instantiate();
			p_game_object->SetName(p_name);

			printf("Instantiated : %s with %d vertices.\n", p_name, vertices.size());

			if (!vertices.empty() && !normals.empty())
			{
				auto* p_material      = p_game_object->AddComponent<CMaterial>();
				auto* p_mesh_renderer = p_game_object->AddComponent<CMeshRenderer>();
				auto* p_mesh_filter   = p_game_object->AddComponent<CMeshFilter>();

				p_material->SetShader(EShaderType::UnlitColor);
				p_material->SetColor(glm::vec3(1.0f, 0.0f, 1.0f));

				p_mesh_filter->GetMesh().SetVertices(std::move(vertices));
				p_mesh_filter->GetMesh().SetNormals(std::move(normals));

				if (!uvs.empty())
				{
					p_mesh_filter->GetMesh().SetUVs(std::move(uvs));

					if (texture_id != 0)
					{
						p_material->SetShader(EShaderType::Standard);
						p_material->SetTexture(texture_id);
					}
				}

				game_objects.push_back(p_game_object);
			}

			uvs.clear();
			normals.clear();
			vertices.clear();
			
			// Getting next name
			sscanf(p_buffer, "o %s", p_name);
        }
        else if(p_buffer[0] == 't')
        {
            char p_texture_name[128] = {'\0'};
            sscanf(p_buffer, "t %s", p_texture_name);

            CString path = CString("Resources/Texture/") + p_texture_name;
            texture_id = CTextureImporter::ImportTexture(path.Data());
        }
        else if(p_buffer[0] == 'v' && p_buffer[1] == ' ')
        {
            glm::vec3 vertex;
            sscanf(p_buffer, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z); // NOLINT
            _vertices.push_back(vertex);
			counter++;
        }
        else if(p_buffer[0] == 'v' && p_buffer[1] == 'n')
        {
            glm::vec3 normal;
            sscanf(p_buffer, "vn %f %f %f", &normal.x, &normal.y, &normal.z); // NOLINT
            _normals.push_back(normal);
        }
        else if(p_buffer[0] == 'v' && p_buffer[1] == 't')
        {
            glm::vec2 uv;
            sscanf(p_buffer, "vt %f %f", &uv.x, &uv.y); // NOLINT
            _uvs.push_back(uv);
        }
        else if(p_buffer[0] == 'f')
        {
            // Unindexing faces
            if(!_uvs.empty())
            {
                int index[9] = {0};
                sscanf(p_buffer, "f %d/%d/%d %d/%d/%d %d/%d/%d",                // NOLINT
                       &index[0], &index[1], &index[2], &index[3], &index[4],
                       &index[5], &index[6], &index[7], &index[8]);

                vertices.push_back(_vertices[index[0] - 1]);
                vertices.push_back(_vertices[index[3] - 1]);
                vertices.push_back(_vertices[index[6] - 1]);

                uvs.push_back(_uvs[index[1] - 1]);
                uvs.push_back(_uvs[index[4] - 1]);
                uvs.push_back(_uvs[index[7] - 1]);

                normals.push_back(_normals[index[2] - 1]);
                normals.push_back(_normals[index[5] - 1]);
                normals.push_back(_normals[index[8] - 1]);
            }
            else
            {
                int index[6] = {0};
                sscanf(p_buffer, "f %d//%d %d//%d %d//%d",                      // NOLINT
                       &index[0], &index[1], &index[2],
                       &index[3], &index[4], &index[5]);

                vertices.push_back(_vertices[index[0] - 1]);
                vertices.push_back(_vertices[index[2] - 1]);
                vertices.push_back(_vertices[index[4] - 1]);

                normals.push_back(_normals[index[1] - 1]);
                normals.push_back(_normals[index[3] - 1]);
                normals.push_back(_normals[index[5] - 1]);
            }
        }
    }
}

}