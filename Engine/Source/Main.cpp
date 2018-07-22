#include "CEngine.hpp"
#include "Composite/CGameObject.hpp"
#include "Composite/Component/CBehavior.hpp"

class S_CameraController : public Oom::CBehavior {};

int main()
{
    Oom::CEngine engine;

    engine.Initialize();

    auto*   p_game_object  = Oom::CEngine::Instantiate();
    auto* p_cam_controller = p_game_object->AddComponent<S_CameraController>();

    engine.Run();
    engine.Release();
}
