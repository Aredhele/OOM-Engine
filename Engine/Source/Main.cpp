#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "CEngine.hpp"
#include "Render/CCamera.hpp"

int main()
{
    Oom::CEngine engine;

    engine.Initialize();
    engine.Run();
    engine.Release();

    Oom::CCamera camera;
    camera.LookAt(glm::vec3(0.0f, 1.0f, 2.0f));
}