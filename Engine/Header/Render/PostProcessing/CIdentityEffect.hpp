/// \file       CIdentityEffect.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/PostProcessing
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_IDENTITY_EFFECT_HPP__
#define OOM_ENGINE_C_IDENTITY_EFFECT_HPP__

#include "Render/PostProcessing/IPostEffect.hpp"

namespace Oom
{

class CIdentityEffect : public IPostEffect
{
public:

    // None

private:

    friend class CPostProcessingStack;

    CIdentityEffect ();
    ~CIdentityEffect();

    void ApplyEffect(GLuint color_texture, GLuint depth_texture) final;
};

} // !namespace

#endif // !OOM_ENGINE_C_IDENTITY_EFFECT_HPP__