/// \file       CMeshImporter.hpp
/// \date       01/08/2018
/// \project    OOM-Engine
/// \package    Import
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_MESH_IMPORTER_HPP__
#define OOM_ENGINE_C_MESH_IMPORTER_HPP__

#include <cstdio>
#include <vector>

namespace Oom
{

// Forward declaration
class CGameObject;

class CMeshImporter
{
public:

    static std::vector<CGameObject*> ImportFromObj(const char* p_path);

private:

    static void ImportObj(FILE* file_descriptor, char* current_line, std::vector<CGameObject*>& game_objects);
};

}

#endif // !OOM_ENGINE_C_MESH_IMPORTER_HPP__