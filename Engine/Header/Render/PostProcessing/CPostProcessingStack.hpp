/// \file       CPostProcessingStack.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/PostProcessing
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_POST_PROCESSING_STACK_HPP__
#define OOM_ENGINE_C_POST_PROCESSING_STACK_HPP__

#include <vector>
#include "Render/Config.hpp"
#include "Render/PostProcessing/IPostEffect.hpp"

// Post effects
#include "Render/PostProcessing/CIdentityEffect.hpp"

namespace Oom
{

class CPostProcessingStack
{
public:

    IPostEffect* GetPostEffect  (IPostEffect::EType type);
    void         SetEffectActive(IPostEffect::EType type, bool bActive);

private:

    friend class CRenderer;

    CPostProcessingStack ();
    ~CPostProcessingStack();

    void Initialize();
    void Release   ();

    void OnPostProcessingBegin     ();
    void OnPostProcessingRender    ();
    void OnPostProcessingEnd       ();
    int GetActivePostProcessShaders() const;

private:

    // QUAD
    GLuint m_postProcessVao;
    GLuint m_postProcessQuadVbo;

    // FBO 1
    GLuint m_postProcessFbo;
    GLuint m_postProcessRbo;
    GLuint m_postProcessTexture;
    GLuint m_postProcessDepthTexture;

    // FBO 2
    GLuint m_postProcessFboBuffer;
    GLuint m_postProcessTextureBuffer;

    // PostEffects stack
    std::vector <IPostEffect *> m_stack;
};

} // !namespace

#endif // !OOM_ENGINE_C_POST_PROCESSING_STACK_HPP__