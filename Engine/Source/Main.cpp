#include "CEngine.hpp"

int main()
{
    Oom::CEngine engine;

    engine.Initialize();
    engine.Run();
    engine.Release();

     return 0;
}
