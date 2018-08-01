/// \file       Game.cpp
/// \date       01/08/2018
/// \project    OOM-Engine
/// \package    Game
/// \author     Vincent STEHLY--CALISTO

#include <Core/Debug/SLogger.hpp>
#include "Hook.hpp"
#include "SDK/SDK.hpp"

#include "Import/CMeshImporter"

/* static */ GLuint ImportTexture_BMP(const char* szPath)
{
    unsigned char header[54];
    unsigned int  dataPos       = 0;
    unsigned int  imageSize     = 0;
    unsigned int  width, height = 0;

    FILE *file = fopen(szPath, "rb");
    if (!file)
    {
        return 0;
    }

    // Header processing
    if (fread(header, 1, 54, file) != 54)
    {
        fclose(file);
        return 0;
    }

    if (header[0] != 'B' || header[1] != 'M')
    {
        fclose(file);
        return 0;
    }

    // Make sure this is a 24bpp file
    if (*(int *) &(header[0x1E]) != 0)
    {
        fclose(file);
        return 0;
    }

    if (*(int *) &(header[0x1C]) != 24)
    {
        fclose(file);
        return 0;
    }

    // Read the information about the image
    dataPos   = *(unsigned int *) &(header[0x0A]);
    imageSize = *(unsigned int *) &(header[0x22]);
    width     = *(unsigned int *) &(header[0x12]);
    height    = *(unsigned int *) &(header[0x16]);

    if (imageSize == 0)
    {
        // RGB
        imageSize = width * height * 3;
    }

    if (dataPos == 0)
    {
        dataPos = 54;
    }

    unsigned char* buffer = static_cast<unsigned char*>(malloc(8192 * 8192));

    // Gets texture data
    fread(buffer, 1, imageSize, file);
    fclose(file);

    GLuint textureID;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    GLenum err = glGetError();
    if(glGetError() != GL_NO_ERROR)
    {
        SLogger::LogError("ERROR GL");
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, buffer);

    err = glGetError();
    if(err != GL_NO_ERROR)
    {
        SLogger::LogError("ERROR GL");
    }

    err = glGetError();
    if(err != GL_NO_ERROR)
    {
        SLogger::LogError("ERROR GL");
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.6f);
    glGenerateMipmap(GL_TEXTURE_2D);

    if(err != GL_NO_ERROR)
    {
        SLogger::LogError("ERROR GL");
    }

    free(buffer);

    return textureID;
}

void LoadScene()
{
    CGameObject* p_camera = Sdk::GameObject::CreateCamera();
    p_camera->AddComponent<S_CameraController>();
    p_camera->SetTag("MainCamera");

    GLenum err = glGetError();
    if(err != GL_NO_ERROR)
    {
        SLogger::LogError("ERROR GL");
    }

    //std::vector<CGameObject*> gog1 = Sdk::Import::ImportMesh("Resources/Mesh/R8.obj");
    std::vector<CGameObject*> gog2 = Sdk::Import::ImportMesh("Resources/Mesh/Cube.obj");

    GLuint texture = ImportTexture_BMP("Resources/Texture/TMP.bmp");
    //GLuint texture = Sdk::Import::ImportTexture("Resources/Texture/Cube_map.jpg");
    gog2[0]->GetComponent<CMaterial>()->SetTexture(texture);
    gog2[0]->GetComponent<CMaterial>()->SetShader(EShaderType::UnlitTexture);

    if(err != GL_NO_ERROR)
    {
        SLogger::LogError("ERROR GL");
    }
}