/// \file       CEngine.cpp
/// \date       21/07/2018
/// \project    OOM-Engine
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#include "CEngine.hpp"
#include "Core/Debug/SLogger.hpp"
#include "Render/Shader/SShaderCompiler.hpp"
#include "Glm/glm.hpp"
#include "Glm/ext.hpp"

// Keep
#include "Composite/CGameObject.hpp"
#include "Composite/Component/CBehavior.hpp"
#include "Composite/Component/CTransform.hpp"
#include "Built-in/Script/S_Camera.hpp"
#include "Built-in/Script/S_CameraController.hpp"
#include "Render/Mesh/CMeshFilter.hpp"

// Keep²
#include "Render/CRenderer.hpp"
#include "Render/Mesh/CMeshFilter.hpp"
#include "Render/Mesh/CMeshRenderer.hpp"

namespace Oom
{

/* static */ CEngine* CEngine::sp_instance = nullptr;

bool CEngine::Initialize()
{
    SLogger::LogInfo("Oom-Engine initialization.");

    mp_renderer = new CRenderer();
    mp_renderer->Initialize();

    // Static instance initialization
    sp_instance = this;

    SLogger::LogInfo("Oom-Engine initialized.");
    return true;
}

void CEngine::Release()
{
    SLogger::LogInfo("Releasing Oom-Engine");

    mp_renderer->Release();
    delete mp_renderer;

    mp_renderer = nullptr;
    sp_instance = nullptr;

    SLogger::LogInfo("Oom-Engine released.");
}

static const float g_vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
};

static const GLfloat g_color_buffer_data[] = {
        0.583f,  0.771f,  0.014f,
        0.609f,  0.115f,  0.436f,
        0.327f,  0.483f,  0.844f,
        0.822f,  0.569f,  0.201f,
        0.435f,  0.602f,  0.223f,
        0.310f,  0.747f,  0.185f,
        0.597f,  0.770f,  0.761f,
        0.559f,  0.436f,  0.730f,
        0.359f,  0.583f,  0.152f,
        0.483f,  0.596f,  0.789f,
        0.559f,  0.861f,  0.639f,
        0.195f,  0.548f,  0.859f,
        0.014f,  0.184f,  0.576f,
        0.771f,  0.328f,  0.970f,
        0.406f,  0.615f,  0.116f,
        0.676f,  0.977f,  0.133f,
        0.971f,  0.572f,  0.833f,
        0.140f,  0.616f,  0.489f,
        0.997f,  0.513f,  0.064f,
        0.945f,  0.719f,  0.592f,
        0.543f,  0.021f,  0.978f,
        0.279f,  0.317f,  0.505f,
        0.167f,  0.620f,  0.077f,
        0.347f,  0.857f,  0.137f,
        0.055f,  0.953f,  0.042f,
        0.714f,  0.505f,  0.345f,
        0.783f,  0.290f,  0.734f,
        0.722f,  0.645f,  0.174f,
        0.302f,  0.455f,  0.848f,
        0.225f,  0.587f,  0.040f,
        0.517f,  0.713f,  0.338f,
        0.053f,  0.959f,  0.120f,
        0.393f,  0.621f,  0.362f,
        0.673f,  0.211f,  0.457f,
        0.820f,  0.883f,  0.371f,
        0.982f,  0.099f,  0.879f
};

#include "Built-in/Script/S_Camera.hpp"
#include "Built-in/Script/S_CameraController.hpp"

void CEngine::Run()
{
    // Getting GLFW window
    GLFWwindow* p_handle = mp_renderer->GetWindow()->GetHandle();

    double lag        = 0.0;
    double previous   = glfwGetTime();
    double delta_time = 1.0 / 60.0;




    glEnable   (GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable   (GL_CULL_FACE);
    glCullFace (GL_BACK);
    glFrontFace(GL_CCW);
    glEnable   (GL_MULTISAMPLE);

    CGameObject* p_camera                   = Instantiate();
    S_Camera* p_camera_component            = p_camera->AddComponent<S_Camera>();
    S_CameraController* p_camera_controller = p_camera->AddComponent<S_CameraController>();

    p_camera->AddComponent<CMeshFilter>();

    // Test
    const char* vshader =
            "#version 330 core\n"
            "layout(location = 0) in vec3 model;\n"
            "layout(location = 1) in vec3 vertexColor;\n"
            "out vec3 fragmentColor;\n"
            "uniform mat4 MVP;\n"
            "void main(){"
            "gl_Position =  MVP * vec4(model,1);"
            "fragmentColor = vertexColor;}";

    const char* fshader =
            "#version 330 core\n"
            "out vec3 color;\n"
            "in vec3 fragmentColor;\n"
            "void main(){"
            "color = fragmentColor;}";

    GLuint cg_program = Oom::SShaderCompiler::CreateProgram("Default", vshader, fshader);

    p_camera->GetTransform().SetWorldPosition(5.0f, 2.0f, 6.0f);
    glm::mat4 MVP = p_camera_component->GetProjectionMatrix() * p_camera_component->GetViewMatrix() * glm::mat4(1.0f);

    GLuint MatrixID = static_cast<GLuint>(glGetUniformLocation(cg_program, "MVP"));
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
    );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
    );


    glfwSetInputMode(p_handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    while (glfwWindowShouldClose(p_handle) == 0 &&
           glfwGetKey(p_handle, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {

        glm::vec3 m_clearColor = p_camera_component->GetClearColor();
        glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, 1.0f);

        double current = glfwGetTime();
        double elapsed = current - previous;
        previous       = current;

        lag += elapsed;

        // Processing events
        glfwPollEvents();

        // Fixed granularity
        while(lag >= delta_time)
        {
            BehaviorUpdate(p_handle,   static_cast<float>(delta_time));
            GameObjectUpdate(p_handle, static_cast<float>(delta_time));
            MVP = p_camera_component->GetProjectionMatrix() * p_camera_component->GetViewMatrix() * glm::mat4(1.0f);

            lag -= delta_time;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(cg_program);
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        glBindVertexArray(VertexArrayID);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glDrawArrays(GL_TRIANGLES, 0, 12*3);
        glDisableVertexAttribArray(0);

        mp_renderer->Render();
        glfwSwapBuffers(p_handle);
    }
}

void CEngine::BehaviorUpdate(GLFWwindow* p_window, float delta_time)
{
    // Behavior updates
    auto behavior_count = static_cast<uint32_t>(m_behaviors.size());
    for(uint32_t i = 0; i < behavior_count; ++i)
    {
        CBehavior* p_behavior = m_behaviors[i];

        CTransform* root = p_behavior->GetTransform()->GetRoot();
        CGameObject* go = root->mp_game_object;

        // We can update the behavior
        if(p_behavior->m_is_enabled && go->IsActive())
        {
            if(p_behavior->m_first_update)
                p_behavior->__Start();

            p_behavior->__Update();
        }
    }
}

void CEngine::BehaviorRegister(CBehavior* p_behavior)
{
    p_behavior->Awake();
    m_behaviors.push_back(p_behavior);
}

void CEngine::GameObjectUpdate(GLFWwindow* p_window, float delta_time)
{
    // Game objects life cycle check
    auto go_count = static_cast<uint32_t>(m_game_objects.size());
    for(uint32_t n_go = 0; n_go < go_count; /* no increment */)
    {
        CGameObject* p_game_object = m_game_objects[n_go];

        // The go is being destroyed
        if(p_game_object->m_is_destroyed &&
           p_game_object->m_destroy_delay != 0.0f)
        {
            p_game_object->m_destroy_elapsed += delta_time;
            if(p_game_object->m_destroy_elapsed >=
               p_game_object->m_destroy_delay)
            {
                p_game_object->m_destroy_delay = 0.0f;
            }
        }

        // The go is destroyed
        if(p_game_object->m_is_destroyed &&
           p_game_object->m_destroy_delay == 0.0f)
        {
            // Destroy notification
            p_game_object->__DestroyMessage();

            m_game_objects[n_go] = m_game_objects.back();
            m_game_objects.pop_back();

            delete p_game_object;
            go_count = static_cast<uint32_t>(m_game_objects.size());
        }
        else
        {
            n_go++;
        }
    }
}

/* static */ CGameObject* CEngine::Instantiate(/* void */)
{
    return Instantiate(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f));
}

/* static */ CGameObject* CEngine::Instantiate(CTransform* parent)
{
    auto* p_game_object = new CGameObject(parent);
    sp_instance->m_game_objects.push_back(p_game_object);

    return p_game_object;
}

/* static */ CGameObject* CEngine::Instantiate(const glm::vec3& position)
{
    return Instantiate((position), glm::vec3(0.0f), glm::vec3(0.0f));
}

/* static */ CGameObject* CEngine::Instantiate(const glm::vec3& position, const glm::vec3& scale)
{
    return Instantiate((position), glm::vec3(0.0f), glm::vec3(0.0f));
}

/* static */ CGameObject* CEngine::Instantiate(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& orientation)
{
    auto* p_game_object = new CGameObject(position, scale, orientation);
    sp_instance->m_game_objects.push_back(p_game_object);

    return p_game_object;
}

/* static */ void CEngine::Destroy(CGameObject* p_game_object)
{
    p_game_object->m_is_destroyed = true;

    for(CTransform* p_transform : p_game_object->GetTransform().GetChildren())
        Destroy(p_transform->GetGameObject());
}

/* static */ void CEngine::Destroy(CGameObject* p_game_object, float delay)
{
    p_game_object->m_is_destroyed   = true;
    p_game_object->m_destroy_delay = delay;

    for(CTransform* p_transform : p_game_object->GetTransform().GetChildren())
        Destroy(p_transform->GetGameObject(), delay);
}

/* static */ void CEngine::DestroyImmediate(CGameObject* p_game_object)
{
    std::vector<CGameObject*> destroy_list(1, p_game_object);
    for(CTransform* p_transform : p_game_object->GetTransform().GetChildren())
        destroy_list.push_back(p_transform->GetGameObject());

    auto go_count = static_cast<uint32_t>(sp_instance->m_game_objects.size());
    for(uint32_t n_go = 0; n_go < go_count; /* no increment */ )
    {
        if(!destroy_list.empty() && sp_instance->m_game_objects[n_go] == destroy_list.back())
        {
            destroy_list.back()->__DestroyMessage();

            sp_instance->m_game_objects[n_go] = sp_instance->m_game_objects.back();
            sp_instance->m_game_objects.pop_back();

            delete destroy_list.back();
            destroy_list.pop_back();

            go_count = static_cast<uint32_t>(sp_instance->m_game_objects.size());
        }
        else
        {
            n_go++;
        }
    }
}

/* static */ CGameObject* CEngine::Find(const CString& name)
{
    for(auto* p_game_object : sp_instance->m_game_objects)
    {
        if(p_game_object->GetName() == name)
            return p_game_object;
    }

    return nullptr;
}

/* static */ CGameObject* CEngine::FindWithTag(const CString& tag)
{
    for(auto* p_game_object : sp_instance->m_game_objects)
    {
        if(p_game_object->GetTag() == tag)
            return p_game_object;
    }

    return nullptr;
}

/* static */ std::vector<CGameObject*> CEngine::FindGameObjectsWithTag(const CString& tag)
{
    std::vector<CGameObject*> game_objects;
    for(auto* p_game_object : sp_instance->m_game_objects)
    {
        if(p_game_object->GetTag() == tag)
            game_objects.push_back(p_game_object);
    }

    return game_objects;
}

/* static */ void CEngine::SetMousePosition(const glm::vec2 &position)
{
    glfwSetCursorPos(sp_instance->mp_renderer->GetWindow()->GetHandle(),
                     position.x, position.y);
}

/* static */ glm::tvec3<double> CEngine::GetMousePosition()
{
    glm::tvec3<double> mouse;
    glfwGetCursorPos(sp_instance->mp_renderer->GetWindow()->GetHandle(),
                     &mouse.x, &mouse.y);

    return mouse;
}

/* static */ glm::vec2 CEngine::GetWindowSize()
{
    return sp_instance->mp_renderer->GetWindow()->GetWindowSize();
}

/* static */ bool CEngine::IsKeyPressed(int key_code)
{
    return (glfwGetKey(sp_instance->mp_renderer->GetWindow()->GetHandle(), key_code) == GLFW_PRESS);
}

/* static */ bool CEngine::IsKeyReleased(int key_code)
{
    return (glfwGetKey(sp_instance->mp_renderer->GetWindow()->GetHandle(), key_code) == GLFW_RELEASE);
}

CTransform* CEngine::AllocateTransform()
{
    return new CTransform();
}

CMaterial* CEngine::AllocateMaterial()
{
    return new CMaterial();
}

CMeshFilter* CEngine::AllocateMeshFilter()
{
    return new CMeshFilter();
}

CMeshRenderer* CEngine::AllocateMeshRenderer()
{
    // TODO register in graphic engine
    return new CMeshRenderer();
}

void CEngine::ReleaseBehavior(CBehavior* p_behavior)
{
    p_behavior->Awake();
    m_behaviors.push_back(p_behavior);

    for(auto i = 0; i < m_behaviors.size(); ++i)
    {
        if(m_behaviors[i] == p_behavior)
        {
            m_behaviors[i] = m_behaviors.back();
            m_behaviors.pop_back();

            break;
        }
    }

    delete p_behavior;
}

void CEngine::ReleaseTransform(CTransform* p_transform)
{
    delete p_transform;
}

void CEngine::ReleaseMaterial(CMaterial* p_material)
{
    delete p_material;
}

void CEngine::ReleaseMeshFilter(CMeshFilter* p_mesh_filter)
{
    delete p_mesh_filter;
}

void CEngine::ReleaseMeshRenderer(CMeshRenderer* p_mesh_renderer)
{
    // TODO : Delete from renderer
    delete p_mesh_renderer;
}

}