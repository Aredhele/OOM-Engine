/// \file       CRenderer.cpp
/// \date       21/07/2018
/// \project    OOM-Engine
/// \package    Renderer
/// \author     Vincent STEHLY--CALISTO

#include "Render/CWindow.hpp"
#include "Render/CRenderer.hpp"
#include "Render/Renderer/IRenderer.hpp"
#include "Render/Shader/SRenderData.hpp"
#include "Render/Shader/SShaderManager.hpp"

#include "Core/Debug/SLogger.hpp"
#include "Composite/CGameObject.hpp"

#include "Built-in/Script/S_Camera.hpp"
#include "Built-in/Script/S_PointLight.hpp"
#include "Built-in/Script/S_DirectionalLight.hpp"

void GLAPIENTRY GLErrorCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    if(severity == 0x9146)
    {
        int a;
        a++;
    }

 fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
          (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
           type, severity, message );
}

namespace Oom
{

/* static */ CRenderer* CRenderer::sp_instance = nullptr;

bool CRenderer::Initialize()
{
    SLogger::LogInfo("Renderer initialization.");

    sp_instance = this;
    mp_window   = new CWindow();
    mp_window->Initialize(1600, 900, "Oom-Engine"); //< TODO : Add option

    // OpenGL pipeline states
    glEnable   (GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable   (GL_CULL_FACE);
    glCullFace (GL_BACK);
    glFrontFace(GL_CCW);

    glEnable   (GL_MULTISAMPLE);

    // Enables debug callback
    glEnable              (GL_DEBUG_OUTPUT);
    glDebugMessageCallback(GLErrorCallback, nullptr);

    // Registering unlit shaders
    SShaderManager::RegisterShader(SShaderManager::EShaderType::Text,
        "Text",
        "Resources/Shader/Text/TextVertexShader.glsl",
        "Resources/Shader/Text/TextFragmentShader.glsl");

    SShaderManager::RegisterShader(SShaderManager::EShaderType::Standard,
        "Standard",
        "Resources/Shader/Standard/StandardVertexShader.glsl",
        "Resources/Shader/Standard/StandardFragmentShader.glsl");

    SShaderManager::RegisterShader(SShaderManager::EShaderType::UnlitLine,
        "UnlitLine",
        "Resources/Shader/Unlit/UnlitLineVertexShader.glsl",
        "Resources/Shader/Unlit/UnlitLineFragmentShader.glsl");

    SShaderManager::RegisterShader(SShaderManager::EShaderType::UnlitColor,
        "UnlitColor",
        "Resources/Shader/Unlit/UnlitColorVertexShader.glsl",
        "Resources/Shader/Unlit/UnlitColorFragmentShader.glsl");

    SShaderManager::RegisterShader(SShaderManager::EShaderType::UnlitTexture,
        "UnlitTexture",
        "Resources/Shader/Unlit/UnlitTextureVertexShader.glsl",
        "Resources/Shader/Unlit/UnlitTextureFragmentShader.glsl");

    SShaderManager::RegisterShader(SShaderManager::EShaderType::UnlitTransparent,
        "UnlitTransparent",
        "Resources/Shader/Unlit/UnlitTransparentVertexShader.glsl",
        "Resources/Shader/Unlit/UnlitTransparentFragmentShader.glsl");

    SLogger::LogInfo("Renderer initialization.");
    return true;
}

void CRenderer::Release()
{
    SLogger::LogInfo("Releasing renderer.");

    mp_window->Release();
    delete mp_window;

    mp_window   = nullptr;
    sp_instance = nullptr;

    SLogger::LogInfo("Renderer released.");
}

void CRenderer::Render()
{
    // Getting the camera
    CGameObject* p_camera = CEngine::FindWithTag("MainCamera");

    if(!p_camera)
    {
        SLogger::LogWaring("No main camera found.");
        return;
    }

    // Getting the camera script
    auto* p_camera_script = p_camera->GetComponent<S_Camera>();

    if(!p_camera_script)
    {
        SLogger::LogWaring("There is no script attached to the camera.");
        return;
    }

    mp_window->Clear(p_camera_script->GetClearColor());

    // Getting matrix
    const glm::mat4& view       = p_camera_script->GetViewMatrix();
    const glm::mat4& projection = p_camera_script->GetProjectionMatrix();

    SRenderData render_data;
    render_data.V = view;
    render_data.P = projection;

    // Gathering all point lights
    auto game_objects = CEngine::GetAllGameObjects();

    for(auto* p_game_object : game_objects)
    {
        const auto point_behaviors = p_game_object->GetComponents<S_PointLight>();
        const auto direc_behaviors = p_game_object->GetComponent<S_DirectionalLight>();

        auto size = point_behaviors.size();
        for(auto i = 0; i < size; ++i)
        {
            render_data.point_lights.push_back({
                point_behaviors[i]->GetRange(),
                point_behaviors[i]->GetIntensity(),
                point_behaviors[i]->GetColor(),
                p_game_object->GetTransform().GetWorldPosition()});
        }

        if(direc_behaviors != nullptr)
        {
            render_data.directional.m_ambient_color     = direc_behaviors->GetAmbientColor();
            render_data.directional.m_light_color       = direc_behaviors->GetLightColor();
            render_data.directional.m_direction         = direc_behaviors->GetDirection();
            render_data.directional.m_ambient_intensity = direc_behaviors->GetAmbientIntensity();
            render_data.directional.m_light_intensity   = direc_behaviors->GetLightIntensity();
        }
    }

    // Forward rendering
    for(auto* p_renderer : m_renderers)
    {
        if(p_renderer->IsVisible())
            p_renderer->Draw(render_data);
    }

    mp_window->Display();
}

CWindow* CRenderer::GetWindow()
{ return mp_window; }


/* static */ void Oom::CRenderer::RegisterRenderer(IRenderer* p_renderer)
{
    sp_instance->m_renderers.push_back(p_renderer);
}

/* static */ void Oom::CRenderer::UnregisterRenderer(IRenderer* p_renderer)
{
    std::vector<IRenderer*>& renderers = sp_instance->m_renderers;

    for(auto i = 0; i < renderers.size(); ++i)
    {
        if(renderers[i] == p_renderer)
        {
            renderers[i] = renderers.back();
            renderers.pop_back();
            break;
        }
    }
}

}

