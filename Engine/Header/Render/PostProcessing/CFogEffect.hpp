/// \file       CFogEffect.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/PostProcessing
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_FOG_EFFECT_HPP__
#define OOM_ENGINE_C_FOG_EFFECT_HPP__

#include <GLM/glm.hpp>
#include "Render/PostProcessing/IPostEffect.hpp"

namespace Oom
{

class CFogEffect : public IPostEffect
{
public:

    const glm::vec3& GetFogColor  () const;
    float            GetFogDensity() const;

    void SetFogColor   (const glm::vec3& color);
    void SetFogDensity (float density);

private:

    friend class CPostProcessingStack;

    CFogEffect ();
    ~CFogEffect();

    void ApplyEffect(GLuint color_texture, GLuint depth_texture) final;

private:

    int  m_fogColorID;
    int  m_fogDensityID;

    glm::vec3 m_fogColor;
    float     m_fogDensity;
};

} // !namespace

#endif // !OOM_ENGINE_C_FOG_EFFECT_HPP__