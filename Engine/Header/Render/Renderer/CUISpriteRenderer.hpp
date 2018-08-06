/// \file       CUISpriteRenderer.hpp
/// \date       06/08/2018
/// \project    OOM-Engine
/// \package    Render/Renderer
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_UI_SPRITE_RENDERER_HPP__
#define OOM_ENGINE_C_UI_SPRITE_RENDERER_HPP__

#include "Render/Renderer/IRenderer.hpp"

namespace Oom
{

class CUISpriteRenderer : public IRenderer
{
public:

	void Draw(SRenderData& render_data) final;
};

}

#endif // !OOM_ENGINE_C_UI_SPRITE_RENDERER_HPP__