/// \file       CMeshImporter.hpp
/// \date       01/08/2018
/// \project    OOM-Engine
/// \package    Import
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_MESH_IMPORTER_HPP__
#define OOM_ENGINE_C_MESH_IMPORTER_HPP__

#include <cstdio>
#include <vector>
#include "Core/Standard/CString.hpp"

namespace Oom
{

// Forward declaration
class CGameObject;

struct SObjectFile
{
	struct SObject
	{
		CString  name;
		uint32_t texture;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec3> vertices;
	};

	CString	file_name;
	std::vector<SObject*> objects;
};

class CMeshImporter
{
public:

    static void				         ImportFromObj        (const char* p_path);
	static CGameObject*		         CreateObjectFromMesh (const char* p_name);
	static std::vector<CGameObject*> CreateObjectsFromFile(const char* p_file_name);

private:

	static CGameObject* AssembleGameObject(const SObjectFile::SObject& object);
    static void			ImportObj         (FILE* file_descriptor, char* current_line, SObjectFile* p_object_file);

private:

	static std::vector<SObjectFile*> object_files;
};

}

#endif // !OOM_ENGINE_C_MESH_IMPORTER_HPP__