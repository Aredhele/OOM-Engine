/// \file       Shader.cpp
/// \date       23/07/2018
/// \project    OOM-Engine
/// \package    Built-in/Shader
/// \author     Vincent STEHLY--CALISTO

#include "Built-in/Shader/Shader.hpp"

const char g_default_vertex_shader[] =
        "#version 330 core\n"
        "layout(location = 0) in vec3 model;\n"
        //"layout(location = 1) in vec3 vertexColor;\n"
        "out vec3 fragmentColor;\n"
        "uniform mat4 MVP;\n"
        "void main(){"
        "gl_Position =  MVP * vec4(model,1);"
        "fragmentColor = vec3(1.0f, 0.0f, 0.4f);}";

const char g_default_fragment_shader[] =
        "#version 330 core\n"
        "out vec3 color;\n"
        "in vec3 fragmentColor;\n"
        "void main(){"
        "color = fragmentColor;}";

const char g_unlit_texture_vertex_shader[] =
        "#version 330 core\n"
        "layout(location = 0) in vec3 vertex;\n"
      //  "layout(location = 1) in vec3 vertex_normal;\n"
        "layout(location = 1) in vec2 vertex_uv;\n"
      //  "layout(location = 3) in vec2 vertex_color;\n"
        "out vec2 uv;\n"
        "uniform mat4 MVP;\n"
        "void main(){"
        "gl_Position = MVP * vec4(vertex, 1.0f);"
        "uv = vertex_uv;}";

const char g_unlit_texture_fragment_shader [] =
        "#version 330 core\n"
        "in vec2 uv;\n"
        "out vec3 color;\n"
        "uniform sampler2D texture_sampler;\n"
        "void main(){"
        "vec2 uv2 = vec2(0.2, 0.8);"
        "color = texture2D(texture_sampler, uv2).rgb;}";