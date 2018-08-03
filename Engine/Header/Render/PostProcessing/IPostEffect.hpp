/// \file       IPostEffect.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/PostProcessing
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_I_POST_EFFECT_HPP__
#define OOM_ENGINE_I_POST_EFFECT_HPP__

#include "Render/Config.hpp"
#include "Core/Standard/CString.hpp"

namespace Oom
{

class IPostEffect
{
public:

    enum EType
    {
        Identity,
        Mirror,
        Negative,
        Sepia,
        BoxBlur,
        GaussianBlur,
        Sharpen,
        EdgeDetection,
        Bloom,
        Vignette,
        FXAA,
        DepthOfField,
        Fog
    };

    const CString& GetName() const;

protected:

    friend class CPostProcessingStack;

    IPostEffect   (EType type, const CString& name);
    void SetActive(bool bActive);
    bool IsActive () const;

    virtual void ApplyEffect(GLuint color_texture, GLuint depth_texture) = 0;

protected:

    EType       m_type;
    bool        m_is_active;
    CString     m_name;

    GLuint      m_shader_id;
    GLint       m_color_texture_id;
    GLint       m_depth_texture_id;
};

}

#endif // !OOM_ENGINE_I_POST_EFFECT_HPP__