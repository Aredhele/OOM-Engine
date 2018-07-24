/// \file       CRenderer.hpp
/// \date       21/07/2018
/// \project    OOM-Engine
/// \package    Render
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_RENDERER_HPP__
#define OOM_ENGINE_C_RENDERER_HPP__

#include <vector>

namespace Oom
{

// Forward declaration
class CWindow;
class IRenderer;

class CRenderer
{
public:
    CWindow* GetWindow ();

private:
    friend class CEngine;
    friend class IRenderer;

    bool     Initialize();
    void     Release   ();
    void     Render    ();

    static void RegisterRenderer   (IRenderer* p_renderer);
    static void UnregisterRenderer (IRenderer* p_renderer);

private:
    CWindow*                 mp_window = nullptr;
    std::vector<IRenderer*>  m_renderers;

private:

    static CRenderer* sp_instance;
};

}

#endif // !OOM_ENGINE_C_RENDERER_HPP__