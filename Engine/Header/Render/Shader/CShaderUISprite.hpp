/// \file       CShaderUISprite.hpp
/// \date       06/08/2018
/// \project    OOM-Engine
/// \package    Render/Shader
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_SHADER_UI_SPRITE_HPP__
#define OOM_ENGINE_C_SHADER_UI_SPRITE_HPP__

#include "Render/Shader/IShader.hpp"

namespace Oom
{

class CShaderUISprite : public IShader
{
public:

	CShaderUISprite();

	void Begin(const SRenderData& render_data) final;
	void End()                                 final;
};

}

#endif // !OOM_ENGINE_C_SHADER_UI_SPRITE_HPP__