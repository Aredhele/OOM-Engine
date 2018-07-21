#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "CEngine.hpp"

int main()
{
    Oom::CEngine engine;

    engine.Initialize();
    engine.Run();
    engine.Release();
}