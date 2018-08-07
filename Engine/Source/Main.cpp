/// \file       Main.cpp
/// \date       01/08/2018
/// \project    OOM-Engine
/// \author     Vincent STEHLY--CALISTO

#include "Engine/CEngine.hpp"

int main()
{
    Oom::CEngine engine;

    engine.Initialize();
    engine.Run();
    engine.Release();

    return 0;
}