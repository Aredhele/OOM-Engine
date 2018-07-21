#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "CEngine.hpp"
#include "Render/CCamera.hpp"
#include <Core/Debug/SLogger.hpp>
#include <vector>
#include <stdio.h>

GLuint LoadShaders(const char* vshader, const char* fshader)
{
    // Create the shaders
    GLuint VertexShaderID   = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);


    GLint result      = GL_FALSE;
    int InfoLogLength = 0;

    // Compile Vertex Shader
    printf("Compiling shader...\n");

    glShaderSource (VertexShaderID, 1, &vshader , NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS,  &result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 )
    {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    // Compile Fragment Shader
    printf("Compiling shader...\n");
    glShaderSource (FragmentShaderID, 1, &fshader, NULL);
    glCompileShader(FragmentShaderID);



    char array[1024] = {0};
    GLsizei  lenght = 0;
    glGetShaderSource(FragmentShaderID, 1024, &lenght, array);




    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS,  &result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 )
    {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glProgramParameteri(ProgramID, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE);

    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glProgramParameteri(ProgramID, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE);

    glLinkProgram (ProgramID);
    glProgramParameteri(ProgramID, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE);

    // Check the program
    GLsizei size = 0;
    glGetProgramiv(ProgramID, GL_LINK_STATUS,     &result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    glGetProgramiv(ProgramID, GL_PROGRAM_BINARY_LENGTH, &size);


    if ( InfoLogLength > 0 )
    {
        printf("Error 3\n");
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

int main()
{
    Oom::CEngine engine;
    engine.Initialize();

    //engine.Run();
    //engine.Release();

    //Oom::CCamera camera;
    //camera.LookAt(glm::vec3(0.0f, 1.0f, 2.0f));

    // Test
    const char* vshader =
            "#version 330 core\n"
            "layout(location = 0) in vec3 model;\n"
            "void main(){"
            "gl_Position.xyz = model;"
            "gl_Position.w = 1.0;}";

    const char* fshader =
            "#version 330 core\n"
            "out vec3 color;\n"
            "void main(){"
            "color = vec3(1,0,0);}";

    GLuint program = LoadShaders(vshader, fshader);


    // glGetProgramBinary(GLuint program​, GLsizei bufsize​, GLsizei *length​, GLenum *binaryFormat​, void *binary​);

    char array[10024] = {0};
    GLsizei  lenght = 0;
    GLenum bin;
    glUseProgram(program);
    glGetProgramBinary(program, 10024, &lenght, &bin, array);

    printf("Binary :\n %s\n", array);
    engine.Release();
}
