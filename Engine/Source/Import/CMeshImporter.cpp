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

/* static */ std::vector<SObjectFile*> CMeshImporter::object_files;

/* static */ void CMeshImporter::ImportFromObj(const char* p_path)
{
	FILE* file_descriptor = fopen(p_path, "r");
	if (!file_descriptor)
	{
		SLogger::LogError("Mesh importer : Unable to open %s.", p_path);
		return;
	}

	auto* p_object_file = new SObjectFile();
	p_object_file->file_name = p_path;
	
	char p_buffer[1024];
	while (fgets(p_buffer, sizeof(p_buffer), file_descriptor) != nullptr)
	{
		const size_t line_size = strlen(p_buffer);
		p_buffer[line_size - 1] = '\0';

		if (p_buffer[0] == 'o')
		{
			ImportObj(file_descriptor, p_buffer, p_object_file);
		}
	}

	object_files.push_back(p_object_file);

	SLogger::LogUser("%d mesh loaded from %s :", 
		p_object_file->objects.size(), 
		p_object_file->file_name.Data());

	for (const auto* p_object : p_object_file->objects)
		SLogger::LogUser(" - (%d\t vertices) : %s", 
			p_object->vertices.size(), 
			p_object->name.Data());

	// Closing the descriptor
	fclose(file_descriptor);
}

/* static */ void CMeshImporter::AddMeshToGameObject(CGameObject* p_game_object, const char* p_name)
{
	for (const auto* p_file : object_files)
	{
		for (const auto* p_object : p_file->objects)
		{
			if (p_object->name == p_name)
			{
				AssembleGameObject(*p_object, p_game_object);
				return;
			}
		}
	}
}

/* static */ CGameObject* CMeshImporter::CreateObjectFromMesh(const char* p_name)
{
	for(const auto* p_file : object_files)
	{
		for(const auto* p_object : p_file->objects)
		{
			if (p_object->name == p_name)
				return AssembleGameObject(*p_object);
		}
	}

	SLogger::LogWaring("Mesh not found (%s)", p_name);
	return nullptr;
}

/* static */ std::vector<CGameObject*> CMeshImporter::CreateObjectsFromFile(const char* p_file_name)
{
	std::vector<CGameObject*> game_objects;

	for (const auto* p_file : object_files)
	{
		for (const auto* p_object : p_file->objects)
		{
			auto* p_game_object = AssembleGameObject(*p_object);

			if (p_game_object)
				game_objects.push_back(p_game_object);
		}
	}

	return game_objects;
}

CGameObject* CMeshImporter::AssembleGameObject(const SObjectFile::SObject& object)
{
	CGameObject* p_game_object = CEngine::Instantiate();
	p_game_object->SetName(object.name);

	if (!object.vertices.empty() && !object.normals.empty())
	{
		auto* p_material      = p_game_object->AddComponent<CMaterial>();
		auto* p_mesh_filter   = p_game_object->AddComponent<CMeshFilter>();
		auto* p_mesh_renderer = p_game_object->AddComponent<CMeshRenderer>();
		
		p_material->SetShader(EShaderType::UnlitColor);
		p_material->SetColor(glm::vec3(1.0f, 0.0f, 1.0f));

		p_mesh_filter->GetMesh().SetVertices(object.vertices);
		p_mesh_filter->GetMesh().SetNormals (object.normals);

		if (!object.uvs.empty())
		{
			p_mesh_filter->GetMesh().SetUVs(object.uvs);

			if (object.texture != 0)
			{
				p_material->SetShader(EShaderType::Standard);
				p_material->SetTexture(object.texture);
			}
		}

		// Moving the mesh
		p_game_object->GetTransform().SetPosition(
			p_game_object->GetTransform().GetPosition() + 
			p_mesh_filter->GetMesh().GetMeshOffset());
	}

	return p_game_object;
}

/* static */ void CMeshImporter::AssembleGameObject(const SObjectFile::SObject& object, CGameObject* p_game_object)
{
	if (!object.vertices.empty() && !object.normals.empty())
	{
		auto* p_material      = p_game_object->AddComponent<CMaterial>();
		auto* p_mesh_filter   = p_game_object->AddComponent<CMeshFilter>();
		auto* p_mesh_renderer = p_game_object->AddComponent<CMeshRenderer>();

		p_material->SetShader(EShaderType::UnlitColor);
		p_material->SetColor(glm::vec3(1.0f, 0.0f, 1.0f));

		p_mesh_filter->GetMesh().SetVertices(object.vertices);
		p_mesh_filter->GetMesh().SetNormals(object.normals);

		if (!object.uvs.empty())
		{
			p_mesh_filter->GetMesh().SetUVs(object.uvs);

			if (object.texture != 0)
			{
				p_material->SetShader(EShaderType::Standard);
				p_material->SetTexture(object.texture);
			}
		}

		// Moving the mesh
		p_game_object->GetTransform().SetPosition(
			p_game_object->GetTransform().GetPosition() + 
			p_mesh_filter->GetMesh().GetMeshOffset());
	}
}

/* static */ void CMeshImporter::ImportObj(FILE* file_descriptor, char* current_line, SObjectFile* p_object_file)
{
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> vertices;

	auto* p_object = new SObjectFile::SObject();

	// Getting the name of the first 
	char p_name[128] = { '\0' };
	sscanf(current_line, "o %s", p_name);

    char p_buffer[1024];
    while(fgets(p_buffer, sizeof(p_buffer), file_descriptor) != nullptr)
    {
        if(p_buffer[0] == 'o')
        {
			p_object->name = p_name;
			p_object_file->objects.push_back(p_object);

			// Getting next name
			sscanf(p_buffer, "o %s", p_name);
			p_object = new SObjectFile::SObject();
        }
        else if(p_buffer[0] == 't')
        {
            char p_texture_name[128] = {'\0'};
            sscanf(p_buffer, "t %s", p_texture_name);

            CString path      = CString("Resources/Texture/") + p_texture_name;
			p_object->texture = CTextureImporter::ImportTexture(path.Data());
        }
        else if(p_buffer[0] == 'v' && p_buffer[1] == ' ')
        {
            glm::vec3 vertex;
            sscanf(p_buffer, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
            vertices.push_back(vertex);
        }
        else if(p_buffer[0] == 'v' && p_buffer[1] == 'n')
        {
            glm::vec3 normal;
            sscanf(p_buffer, "vn %f %f %f", &normal.x, &normal.y, &normal.z);
            normals.push_back(normal);
        }
        else if(p_buffer[0] == 'v' && p_buffer[1] == 't')
        {
            glm::vec2 uv;
            sscanf(p_buffer, "vt %f %f", &uv.x, &uv.y);
            uvs.push_back(uv);
        }
        else if(p_buffer[0] == 'f')
        {
            // Unindexing faces
            if(!uvs.empty())
            {
                int index[9] = {0};
                sscanf(p_buffer, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                       &index[0], &index[1], &index[2], &index[3], &index[4],
                       &index[5], &index[6], &index[7], &index[8]);

				p_object->vertices.push_back(vertices[index[0] - 1]);
                p_object->vertices.push_back(vertices[index[3] - 1]);
                p_object->vertices.push_back(vertices[index[6] - 1]);
		
                p_object->uvs.push_back(uvs[index[1] - 1]);
                p_object->uvs.push_back(uvs[index[4] - 1]);
                p_object->uvs.push_back(uvs[index[7] - 1]);

                p_object->normals.push_back(normals[index[2] - 1]);
                p_object->normals.push_back(normals[index[5] - 1]);
                p_object->normals.push_back(normals[index[8] - 1]);
            }
            else
            {
                int index[6] = {0};
                sscanf(p_buffer, "f %d//%d %d//%d %d//%d",
                       &index[0], &index[1], &index[2],
                       &index[3], &index[4], &index[5]);

				p_object->vertices.push_back(vertices[index[0] - 1]);
				p_object->vertices.push_back(vertices[index[2] - 1]);
				p_object->vertices.push_back(vertices[index[4] - 1]);

                p_object->normals.push_back(normals[index[1] - 1]);
                p_object->normals.push_back(normals[index[3] - 1]);
                p_object->normals.push_back(normals[index[5] - 1]);
            }
        }
    }

	p_object->name = p_name;
	p_object_file->objects.push_back(p_object);
}

}