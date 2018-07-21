/// \file       CRenderer.hpp
/// \date       21/07/2018
/// \project    OOM-Engine
/// \package    Render
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_RENDERER_HPP__
#define OOM_ENGINE_C_RENDERER_HPP__

#include "Render/CWindow.hpp"

namespace Oom
{

class CRenderer
{
public:

    bool     Initialize();
    void     Release   ();
    void     Render    ();
    CWindow* GetWindow ();

private:

    CWindow* mp_window = nullptr;

private:

    static CRenderer* sp_instance;
};

}

#endif // !OOM_ENGINE_C_RENDERER_HPP__