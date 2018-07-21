#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "CEngine.hpp"
#include "Render/CCamera.hpp"
#include <Core/Debug/SLogger.hpp>
#include "Render/Shader/SShaderCompiler.hpp"

int main()
{
    Oom::CEngine engine;

    engine.Initialize();
    engine.Run();
    engine.Release();
}
