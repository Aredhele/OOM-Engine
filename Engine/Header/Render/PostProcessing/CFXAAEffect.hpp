/// \file       CFXAAEffect.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/PostProcessing
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_CFXAA_EFFECT_HPP__
#define OOM_ENGINE_CFXAA_EFFECT_HPP__

#include <GLM/glm.hpp>
#include "Render/PostProcessing/IPostEffect.hpp"

namespace Oom
{

class CFXAAEffect : public IPostEffect
{
public:

    // None

private:

    friend class CPostProcessingStack;

    CFXAAEffect ();
    ~CFXAAEffect();

    void ApplyEffect(GLuint color_texture, GLuint depth_texture) final;

private:

    float m_fxaa_span;
    float m_fxaa_reduce_mul;
    float m_fxaa_reduce_min;

    int m_fxaa_span_id;
    int m_fxaa_reduce_mul_id;
    int m_fxaa_reduce_min_id;
};

} // !namespace

#endif // !OOM_ENGINE_CFXAA_EFFECT_HPP__