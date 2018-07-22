#include "CEngine.hpp"
#include "Composite/CGameObject.hpp"
#include "Composite/Component/CBehavior.hpp"

class S_CameraController : public Oom::CBehavior
{
public:
    void OnDestroy() override
    {

    }
};

int main()
{
    Oom::CEngine engine;

    engine.Initialize();

    auto*   p_game_object  = Oom::CEngine::Instantiate();
    auto* p_cam_controller = p_game_object->AddComponent<S_CameraController>();

    Oom::CEngine::Destroy(p_game_object);

    engine.Run();
    engine.Release();
}
