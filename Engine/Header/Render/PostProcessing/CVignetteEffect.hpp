/// \file       CVignetteEffect.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/PostProcessing
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_VIGNETTE_EFFECT_HPP__
#define OOM_ENGINE_C_VIGNETTE_EFFECT_HPP__

#include <GLM/glm.hpp>
#include "Render/PostProcessing/IPostEffect.hpp"

namespace Oom
{

class CVignetteEffect : public IPostEffect
{
public:

    void SetRadius  (float radius);
    void SetOpacity (float opacity);
    void SetSoftness(float softness);
    void SetCenter  (const glm::vec2& center);

    float            GetRadius  () const;
    float            GetOpacity () const;
    float            GetSoftness() const;
    const glm::vec2& GetCenter  () const;

private:

    friend class CPostProcessingStack;

    CVignetteEffect ();
    ~CVignetteEffect();

    void ApplyEffect(GLuint color_texture, GLuint depth_texture) final;

private:

    float     m_radius;
    float     m_softness;
    glm::vec2 m_center;
    float     m_opacity;

    int m_radius_id;
    int m_softness_id;
    int m_center_id;
    int m_opacity_id;
};

} // !namespace

#endif // !OOM_ENGINE_C_VIGNETTE_EFFECT_HPP__