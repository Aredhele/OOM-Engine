/// \file       CEngine.hpp
/// \date       21/07/2018
/// \project    OOM-Engine
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_ENGINE_HPP__
#define OOM_ENGINE_C_ENGINE_HPP__

#include "Render/CRenderer.hpp"

namespace Oom
{

class CEngine
{
public:

    bool Initialize ();
    void Release    ();
    void Run        ();

private:

    CRenderer* mp_renderer = nullptr;
};

}

#endif // !OOM_ENGINE_C_ENGINE_HPP__