/// \file       CTextureImporter.hpp
/// \date       01/08/2018
/// \project    OOM-Engine
/// \package    Import
/// \author     Vincent STEHLY--CALISTO

#include <cstdio>
#include <Wincodec.h>
#include <Core/Standard/CString.hpp>

#include "Core/Debug/SLogger.hpp"
#include "Import/CTextureImporter.hpp"

namespace Oom
{

GLuint Oom::CTextureImporter::ImportTexture(const char* p_path)
{
    TextureProperty properties {};

    FILE* p_file = fopen(p_path, "rb");

    if(!p_file)
    {
        SLogger::LogError("Unable to open %s", p_path);
        return 0;
    }

    properties.width  = 0;
    properties.height = 0;

    fseek(p_file, 0, SEEK_END);
    auto image_size = static_cast<size_t>(ftell(p_file));
    rewind(p_file);

    auto* p_image_data =   static_cast<unsigned char*>(malloc(image_size));
    fread(p_image_data, 1, static_cast<size_t>(image_size), p_file);
    fclose(p_file);

    GetSize(p_path, static_cast<long>(image_size), p_image_data, properties.width, properties.height);

    int decoded_size   = properties.width  * properties.height * 3;
    properties.pBuffer = static_cast<unsigned char*>(malloc(static_cast<size_t>(decoded_size)));

    if(!W32DecodeJPG(static_cast<unsigned int>(image_size),   p_image_data,
                     static_cast<unsigned int>(decoded_size), properties))
    {
        SLogger::LogError("Unable to decode the jpeg ...");
        free(p_image_data);
        free(properties.pBuffer);

        return 0;
    }

    GLuint ret = BindTexture(properties);

    free(p_image_data);
    free(properties.pBuffer);

    return ret;
}

GLuint Oom::CTextureImporter::BindTexture(const Oom::CTextureImporter::TextureProperty& properties)
{
    GLuint texture_id;

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, properties.width, properties.height, 0, GL_BGR, GL_UNSIGNED_BYTE, properties.pBuffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.6f);
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture_id;
}

bool CTextureImporter::W32DecodeJPG(unsigned int encoded_size, unsigned char* p_encoded_data,
                                    unsigned int decoded_size, TextureProperty& properties)
{
    static IWICImagingFactory* p_iwic_factory = nullptr;
    if(p_iwic_factory == nullptr)
    {
        if(CoInitializeEx(nullptr, COINIT_MULTITHREADED) != S_OK)
        {
            SLogger::LogError("Failed to initialize the COM library.");
            return false;
        }

        if(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&p_iwic_factory)) != S_OK)
        {
            SLogger::LogError("Failed to create an instance of WIC.");
            return false;
        }
    }

    IWICStream* p_stream = nullptr;
    if(p_iwic_factory->CreateStream(&p_stream) != S_OK)
    {
        SLogger::LogError("Failed to create the WIC stream.");
        return false;
    }

    if(p_stream->InitializeFromMemory(p_encoded_data, encoded_size) != S_OK)
    {
        SLogger::LogError("Failed to initialize stream from memory.");
        return false;
    }

    IWICBitmapDecoder* bitmap_decoder = nullptr;
    if(p_iwic_factory->CreateDecoderFromStream(p_stream, nullptr, WICDecodeMetadataCacheOnDemand, &bitmap_decoder) != S_OK)
    {
        SLogger::LogError("Failed to create bitmap decoder from stream.");
        return false;
    }

    IWICBitmapFrameDecode* frame_decode = nullptr;
    if(bitmap_decoder->GetFrame(0, &frame_decode) != S_OK)
    {
        SLogger::LogError("Failed to get 0th frame from frame decoder.");
        return false;
    }

    IWICFormatConverter* format_converter = nullptr;
    if(p_iwic_factory->CreateFormatConverter(&format_converter) != S_OK)
    {
        SLogger::LogError("Failed to create format converter.");
        return false;
    }

    if(format_converter->Initialize(frame_decode, GUID_WICPixelFormat24bppBGR, WICBitmapDitherTypeNone,
                                    nullptr, 0.0f, WICBitmapPaletteTypeCustom) != S_OK)
    {
        SLogger::LogError("Failed to initialize format converter");
        return false;
    }

    IWICBitmap* bitmap = nullptr;
    if(p_iwic_factory->CreateBitmapFromSource(format_converter, WICBitmapCacheOnDemand, &bitmap) != S_OK)
    {
        SLogger::LogError("Failed to create bitmap from format converter.");
        return false;
    }

    unsigned int width, height;
    if(bitmap->GetSize(&width, &height) != S_OK)
    {
        SLogger::LogError("Failed to get the size of the bitmap.");
        return false;
    }

    WICRect Rect = {0, 0, (int)width, (int)height};
    IWICBitmapLock *p_lock = nullptr;

    if(bitmap->Lock(&Rect, WICBitmapLockRead, &p_lock) != S_OK)
    {
        SLogger::LogError("Failed to lock bitmap.");
        return false;
    }

    unsigned int    pixel_data_size = 0;
    unsigned char * pixel_data      = nullptr;

    if(p_lock->GetDataPointer(&pixel_data_size, &pixel_data) != S_OK)
    {
        SLogger::LogError("Failed to get data pointer.");
        return false;
    }

    properties.width  = width;
    properties.height = height;
    memcpy(properties.pBuffer, pixel_data, decoded_size < pixel_data_size ? decoded_size : pixel_data_size);

    p_stream->Release();
    bitmap_decoder->Release();
    frame_decode->Release();
    format_converter->Release();
    bitmap->Release();
    p_lock->Release();

    return true;
}

void ReverseByte(unsigned char *start, int size)
{
    unsigned char *lo = start;
    unsigned char *hi = start + size - 1;
    unsigned char swap;

    while (lo < hi)
    {
        swap = *lo;
        *lo++ = *hi;
        *hi-- = swap;
    }
}

void CTextureImporter::GetSize(const char* fname, long fsize, unsigned char* data, unsigned int& x, unsigned int& y)
{
    // Supported format JPG and PNG
    CString name      = fname;
    CString extension;

    for(uint32_t i = name.Size() - 1; i >= 0; --i)
    {
        if(name[i] == '.')
            break;

        extension += name[i];
    }

    if(extension == "gnp")
    {
        x = *(unsigned int *)&data[16];
        y = *(unsigned int *)&data[20];
        ReverseByte(reinterpret_cast<unsigned char*>(&x), 4);
        ReverseByte(reinterpret_cast<unsigned char*>(&y), 4);
    }
    else if(extension == "gpj" || extension == "gepj")
    {
        for(int i = 0; i < fsize; i += 2)
        {
            if(data[i] == 0xFF && data[i + 1] == 0xC0)
            {
                i += 5;
                y = data[i + 0] << 8 | data[i + 1]; // NOLINT
                x = data[i + 2] << 8 | data[i + 3]; // NOLINT
                break;
            }
        }
    }
}

}

