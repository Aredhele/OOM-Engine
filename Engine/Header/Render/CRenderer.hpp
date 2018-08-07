/// \file       CRenderer.hpp
/// \date       21/07/2018
/// \project    OOM-Engine
/// \package    Render
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_RENDERER_HPP__
#define OOM_ENGINE_C_RENDERER_HPP__

// #include <Windows.h>

#include <vector>
#include "Render/PostProcessing/CPostProcessingStack.hpp"

namespace Oom
{

// Vulkan style initialization
struct SRendererCreateInfo
{
	int         window_width;
	int         window_height;
	int			opengl_major;
	int			opengl_minor;
	bool		full_screen;
	const char* window_name;
};

// Forward declaration
class CWindow;
class IRenderer;

class CRenderer
{
public:
    CWindow* GetWindow ();

public:

	static void EnablePostProcessing  ();
	static void DisablePostProcessing ();
	static bool IsPostProcessingActive();

	static CPostProcessingStack* GetPostProcessingStack();

private:

    friend class CEngine;
    friend class IRenderer;
	friend class CAudioEngine;

    bool     Initialize(const SRendererCreateInfo& renderer_create_info);
    void     Release   ();
    void     Render    ();
    void     DrawGizmos(const glm::mat4& PV);

    static void RegisterRenderer      (IRenderer* p_renderer);
    static void UnregisterRenderer    (IRenderer* p_renderer);

private:

	bool				     m_b_post_process;
    CWindow*                 mp_window = nullptr;
    std::vector<IRenderer*>  m_renderers;
    CPostProcessingStack     m_post_processing;

private:

    static CRenderer* sp_instance;
};

}

#endif // !OOM_ENGINE_C_RENDERER_HPP__