/// \file       CPostProcessingStack.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Render/PostProcessing
/// \author     Vincent STEHLY--CALISTO

#include "Core/Debug/SLogger.hpp"
#include "Render/PostProcessing/CPostProcessingStack.hpp"

namespace Oom
{

CPostProcessingStack::CPostProcessingStack()
{
    m_postProcessVao          = 0;
    m_postProcessFbo          = 0;
    m_postProcessRbo          = 0;
    m_postProcessQuadVbo      = 0;
    m_postProcessTexture      = 0;
    m_postProcessDepthTexture = 0;
}

CPostProcessingStack::~CPostProcessingStack() // NOLINT
{
    // None
}

void CPostProcessingStack::Initialize()
{
    SLogger::LogInfo("Initializing the post-processing stack.");

    // Generating the frame buffer object
    glGenFramebuffers(1, &m_postProcessFbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_postProcessFbo);

    glGenTextures  (1, &m_postProcessTexture);
    glBindTexture  (GL_TEXTURE_2D, m_postProcessTexture);
    glTexImage2D   (GL_TEXTURE_2D, 0, GL_RGB, 1600, 900, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // FBO to render the depth buffer
    m_postProcessRbo = 0;
    glGenRenderbuffers       (1, &m_postProcessRbo);
    glBindRenderbuffer       (GL_RENDERBUFFER, m_postProcessRbo);
    glRenderbufferStorage    (GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1600, 900);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,  GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_postProcessRbo);

    // Texture for the depth texture
    glGenTextures(1, &m_postProcessDepthTexture);
    glBindTexture(GL_TEXTURE_2D, m_postProcessDepthTexture);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, 1600, 900, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Binding buffer
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_postProcessTexture,      0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,  m_postProcessDepthTexture, 0);

    // Attaching the list of buffers to draw
    GLenum DrawBuffers[2] = {GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT};
    glDrawBuffers(2, DrawBuffers);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        SLogger::LogError("Error while creating the post-processing buffers.");
    }

    // VAO for the quad
    glGenVertexArrays(1, &m_postProcessVao);
    glBindVertexArray(m_postProcessVao);

    // Quad vertices
    static const GLfloat g_quad_vertex_buffer_data[] =
    {
        -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, -1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f, 1.0f, -1.0f, 0.0f,  1.0f,  1.0f, 0.0f,
    };

    glGenBuffers(1, &m_postProcessQuadVbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_postProcessQuadVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);

    // Unbind vao
    glBindVertexArray(0);

    // Generating the frame buffer object buffer
    glGenFramebuffers(1, &m_postProcessFboBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_postProcessFboBuffer);

    glGenTextures  (1, &m_postProcessTextureBuffer);
    glBindTexture  (GL_TEXTURE_2D, m_postProcessTextureBuffer);
    glTexImage2D   (GL_TEXTURE_2D, 0, GL_RGB, 1600, 900, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Binding buffer
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_postProcessTextureBuffer, 0);

    // Attaching the list of buffers to draw
    DrawBuffers[0] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        SLogger::LogError("Error while creating the post-processing buffers.");
    }

    m_stack.push_back(new CIdentityEffect());
    // m_stack.push_back(new DepthBuffer());
    // m_stack.push_back(new Mirror());
    m_stack.push_back(new CFogEffect());
    // m_stack.push_back(new Negative());
    // m_stack.push_back(new Sepia());
    // m_stack.push_back(new BoxBlur());
    // m_stack.push_back(new GaussianBlur());
    // m_stack.push_back(new Sharpen());
    // m_stack.push_back(new EdgeDetection());
    // m_stack.push_back(new GodRay());
    // m_stack.push_back(new Bloom());
    // m_stack.push_back(new Vignette());
    // m_stack.push_back(new DepthOfField());
    // m_stack.push_back(new FXAA());
    // m_stack.push_back(new Experimental1());
    // m_stack.push_back(new Experimental2());

    SLogger::LogInfo("Post-processing stack successfully initialized.");
}


void CPostProcessingStack::Release()
{
    // None
}

void CPostProcessingStack::OnPostProcessingBegin()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_postProcessFbo);
    glViewport(0, 0, 1600, 900);
}

void CPostProcessingStack::OnPostProcessingRender()
{
    bool bSwapped = true;

    glBindFramebuffer     (GL_FRAMEBUFFER, m_postProcessFboBuffer);
    glViewport            (0, 0, 1600, 900);
    glFramebufferTexture2D(GL_FRAMEBUFFER , GL_COLOR_ATTACHMENT0 , GL_TEXTURE_2D, m_postProcessTextureBuffer, 0);

    // Processing the stack (Ping pong with FBO)
    int effectCount = static_cast<int>(m_stack.size());    // NOLINT
    for(int nEffect = 0; nEffect < effectCount; ++nEffect) // NOLINT
    {
        if(m_stack[nEffect]->IsActive())
        {
            if(bSwapped)
            {
                glFramebufferTexture2D(GL_FRAMEBUFFER , GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_postProcessTextureBuffer, 0);
                m_stack[nEffect]->ApplyEffect(m_postProcessTexture, m_postProcessDepthTexture);
                bSwapped = false;
            }
            else
            {
                glFramebufferTexture2D(GL_FRAMEBUFFER , GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_postProcessTexture, 0);
                m_stack[nEffect]->ApplyEffect(m_postProcessTextureBuffer, m_postProcessDepthTexture);
                bSwapped = true;
            }

            glBindVertexArray(m_postProcessVao);
            glEnableVertexAttribArray(0);

            glDrawArrays(GL_TRIANGLES, 0, 6);

            glDisableVertexAttribArray(0);
            glBindVertexArray(0);
        }
    }

    // Render the texture on the physical frame buffer
    // Binding physical buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, 1600, 900);

    // Clears the buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(bSwapped)
        m_stack[0]->ApplyEffect(m_postProcessTexture, m_postProcessDepthTexture);
    else
        m_stack[0]->ApplyEffect(m_postProcessTextureBuffer, m_postProcessDepthTexture);

    glBindVertexArray(m_postProcessVao);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
}

void CPostProcessingStack::OnPostProcessingEnd()
{
    // None
}

IPostEffect* CPostProcessingStack::GetPostEffect(IPostEffect::EType type)
{
    IPostEffect* p_effect = nullptr;
    int effectCount = static_cast<int>(m_stack.size());    // NOLINT
    for(int nEffect = 0; nEffect < effectCount; ++nEffect) // NOLINT
    {
        if(m_stack[nEffect]->m_type == type)
        {
            p_effect = m_stack[nEffect];
            break;
        }
    }

    return p_effect;
}

void CPostProcessingStack::SetEffectActive(IPostEffect::EType type, bool bActive)
{
    int effectCount = static_cast<int>(m_stack.size());    // NOLINT
    for(int nEffect = 0; nEffect < effectCount; ++nEffect) // NOLINT
    {
        if(m_stack[nEffect]->m_type == type)
        {
            m_stack[nEffect]->SetActive(bActive);
        }
    }
}

int CPostProcessingStack::GetActivePostProcessShaders() const
{
    int sum = 0;
    int effectCount = static_cast<int>(m_stack.size());    // NOLINT
    for(int nEffect = 0; nEffect < effectCount; ++nEffect) // NOLINT
    {
        if(m_stack[nEffect]->IsActive()) sum++;
    }

    return sum;
}

} // !namespace