/// \file       CTextureImporter.hpp
/// \date       01/08/2018
/// \project    OOM-Engine
/// \package    Import
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_TEXTURE_IMPORTER_HPP__
#define OOM_ENGINE_C_TEXTURE_IMPORTER_HPP__

#include "Render/Config.hpp"

namespace Oom
{

class CTextureImporter
{
public:

    struct TextureProperty
    {
        unsigned char*  pBuffer;
        unsigned int    width;
        unsigned int    height;
        unsigned int    format;
        unsigned int    mipmapCount;
    };

    static GLuint ImportTexture(const char* p_path);

private:

    static bool W32DecodeJPG(unsigned int encoded_size, unsigned char* p_encoded_data,
                             unsigned int decoded_size, TextureProperty& properties);

    static GLuint BindTexture (const TextureProperty& properties);
    static void   GetSize     (const char* fname, long fsize,
                               unsigned char* data, unsigned int& x, unsigned int& y);
};

}

#endif // !OOM_ENGINE_C_TEXTURE_IMPORTER_HPP__