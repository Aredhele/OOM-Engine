/// \file       CTextRenderer.hpp
/// \date       02/08/2018
/// \project    OOM-Engine
/// \package    Render/Renderer
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_TEXT_RENDERER_HPP__
#define OOM_ENGINE_C_TEXT_RENDERER_HPP__

#include "Render/Renderer/IRenderer.hpp"

namespace Oom
{

class CTextRenderer : public IRenderer
{
public:

    void Draw(SRenderData render_data) final;
};

}

#endif // !OOM_ENGINE_C_TEXT_RENDERER_HPP__