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
#include "Resource/CMesh.hpp"
#include "QU3E/q3.h"



// Keep
#include "Composite/CGameObject.hpp"
#include "Composite/Component/CBehavior.hpp"
#include "Composite/Component/CTransform.hpp"
#include "Built-in/Script/S_Camera.hpp"
#include "Built-in/Script/S_CameraController.hpp"
#include "Render/Mesh/CMeshFilter.hpp"

// Keep²
#include "Render/CWindow.hpp"
#include "Render/CRenderer.hpp"
#include "Render/Mesh/CMeshFilter.hpp"
#include "Render/Renderer/CMeshRenderer.hpp"
#include "Render/Shader/SShaderManager.hpp"
#include "Render/Material/CMaterial.hpp"

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
#include <GLM/gtx/quaternion.hpp>
glm::vec3 MatrixToEulerAngles(const glm::mat3& matrix)
{
    glm::vec3 ret(0.0f);
    glm::mat4 m(matrix);
    glm::extractEulerAngleXYX(m, ret.x, ret.z, ret.y);
    return ret;

    /*float sy = static_cast<float>(sqrt(matrix[0][0] * matrix[0][0] + matrix[1][0] * matrix[1][0]));

    bool singular = sy < 1e-6; // If

    float x, y, z;
    if (!singular)
    {
        x = static_cast<float>(atan2(matrix[2][1], matrix[2][2]));
        y = static_cast<float>(atan2(-matrix[2][0] , sy));
        z = static_cast<float>(atan2(matrix[1][0] , matrix[0][0]));
    }
    else
    {
        x = static_cast<float>(atan2(-matrix[1][2] , matrix[1][1]));
        y = static_cast<float>(atan2(-matrix[2][0] , sy));
        z = 0;
    }

    return glm::vec3(x, z, y);*/
}

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
    p_camera->SetTag("MainCamera");

    // Test
    const char* vshader =
            "#version 330 core\n"
            "layout(location = 0) in vec3 model;\n"
            "layout(location = 1) in vec3 vertexColor;\n" // location = 1
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

    SShaderManager::RegisterShader(SShaderManager::EShaderType::Test, "Default", vshader, fshader);



    GLuint cg_program = Oom::SShaderCompiler::CreateProgram("Default", vshader, fshader);

    p_camera->GetTransform().SetWorldPosition(8.0f, 4.0f, 10.0f);
    glm::mat4 MVP_1 = p_camera_component->GetProjectionMatrix() * p_camera_component->GetViewMatrix() * glm::mat4(1.0f);
    glm::mat4 MVP_2 = p_camera_component->GetProjectionMatrix() * p_camera_component->GetViewMatrix() * glm::mat4(1.0f);
    glm::mat4 MVP_3 = p_camera_component->GetProjectionMatrix() * p_camera_component->GetViewMatrix() * glm::mat4(1.0f);


    CGameObject* p_cube_1 = Instantiate();

    auto* p_material      = p_cube_1->AddComponent<CMaterial>();
    auto* p_mesh_filter   = p_cube_1->AddComponent<CMeshFilter>();
    auto* p_mesh_renderer = p_cube_1->AddComponent<CMeshRenderer>();

    p_material->SetMatrix("MVP", MVP_1);
    p_material->SetShader(SShaderManager::EShaderType::Test);
    p_mesh_filter->GetMesh().SetVertices(g_vertex_buffer_data, 108);
    p_mesh_filter->GetMesh().SetColors  (g_color_buffer_data,  108);

    CGameObject* p_cube_2 = Instantiate();

    auto* p_material_2      = p_cube_2->AddComponent<CMaterial>();
    auto* p_mesh_filter_2   = p_cube_2->AddComponent<CMeshFilter>();
    auto* p_mesh_renderer_2 = p_cube_2->AddComponent<CMeshRenderer>();

    p_material_2->SetMatrix("MVP", MVP_2);
    p_material_2->SetShader(EShaderType::Test);
    p_mesh_filter_2->GetMesh().SetVertices(g_vertex_buffer_data, 108);
    p_mesh_filter_2->GetMesh().SetColors  (g_color_buffer_data,  108);


    CGameObject* p_cube_3 = Instantiate();

    auto* p_material_3      = p_cube_3->AddComponent<CMaterial>();
    auto* p_mesh_filter_3   = p_cube_3->AddComponent<CMeshFilter>();
    auto* p_mesh_renderer_3 = p_cube_3->AddComponent<CMeshRenderer>();

    p_material_3->SetMatrix("MVP", MVP_3);
    p_material_3->SetShader(EShaderType::Test);
    p_mesh_filter_3->GetMesh().SetVertices(g_vertex_buffer_data, 108);
    p_mesh_filter_3->GetMesh().SetColors  (g_color_buffer_data,  108);

    p_cube_1->GetTransform().SetLocalPosition(glm::vec3(.0f));
    p_cube_1->GetTransform().SetLocalScale(glm::vec3(7.0f, 7.0f, 0.1f));
    p_cube_2->GetTransform().SetLocalPosition(glm::vec3(0.0f, 0.0f, 0.5f));
    p_cube_3->GetTransform().SetLocalPosition(glm::vec3(0.6f, 0.4f, 7.0f));

    q3Scene scene(1.0f / 60.0f);
    q3BodyDef body_def_1;
    q3BodyDef body_def_2;
    q3BodyDef body_def_3;

    body_def_2.position.y = 0.5f;
    body_def_3.position.x = 0.6f;
    body_def_3.position.y = 7.0f;
    body_def_3.position.z = 0.4f;

    body_def_1.bodyType = eStaticBody;
    body_def_2.bodyType = eStaticBody;
    body_def_3.bodyType = eDynamicBody;
    q3Body* body_1 = scene.CreateBody(body_def_1);
    q3Body* body_2 = scene.CreateBody(body_def_2);
    q3Body* body_3 = scene.CreateBody(body_def_3);

    q3BoxDef box_def_1;
    q3BoxDef box_def_2;
    q3BoxDef box_def_3;
    box_def_1.SetRestitution(0);
    box_def_2.SetRestitution(0);
    box_def_3.SetRestitution(0);

    // 1
    q3Transform localSpace;
    q3Identity (localSpace);
    box_def_1.Set(localSpace, q3Vec3(7.0f, 0.0f, 7.0f));

    // 2
    q3Identity (localSpace);
    // localSpace.position.x = p_cube_2->GetTransform().GetLocalPosition().x;
    // localSpace.position.y = p_cube_2->GetTransform().GetLocalPosition().z;
    // localSpace.position.z = p_cube_2->GetTransform().GetLocalPosition().y;
    box_def_2.Set(localSpace, q3Vec3(1.0f, 1.0f, 1.0f));

    // 3
    q3Identity (localSpace);
    // localSpace.position.x = p_cube_3->GetTransform().GetLocalPosition().x;
    // localSpace.position.y = p_cube_3->GetTransform().GetLocalPosition().z;
    // localSpace.position.z = p_cube_3->GetTransform().GetLocalPosition().y;
    box_def_3.Set(localSpace, q3Vec3(1.0f, 1.0f, 1.0f));

    body_1->AddBox(box_def_1);
    body_2->AddBox(box_def_2);
    body_3->AddBox(box_def_3);



    GLuint MatrixID = static_cast<GLuint>(glGetUniformLocation(cg_program, "MVP"));
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP_1[0][0]);

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
            scene.Step();

            //p_camera->GetTransform().LookAt(p_cube_1->GetTransform());

            p_cube_1->GetTransform().SetLocalPosition(body_1->GetTransform().position.x, body_1->GetTransform().position.z, body_1->GetTransform().position.y);
            p_cube_2->GetTransform().SetLocalPosition(body_2->GetTransform().position.x, body_2->GetTransform().position.z, body_2->GetTransform().position.y);
            p_cube_3->GetTransform().SetLocalPosition(body_3->GetTransform().position.x, body_3->GetTransform().position.z, body_3->GetTransform().position.y);

            q3Mat3 rotation = body_3->GetTransform().rotation;
            glm::mat3 mat(rotation[0][0], rotation[0][1], rotation[0][2],
                          rotation[1][0], rotation[1][1], rotation[1][2],
                          rotation[2][0], rotation[2][1], rotation[2][2]);

            // p_cube_3->GetTransform().SetTest(glm::mat4(mat));

            // p_cube->GetTransform().Translate(glm::vec3(1.0f, 0.0f, 0.0f) * delta_time);
            // p_cube_1->GetTransform().SetLocalScale(p_cube_1->GetTransform().GetLocalScale() + glm::vec3(0.1 * delta_time, 0.1f * delta_time, 0.0f));
            // p_cube_1->GetTransform().Rotate       (0.00f, 0.001f, 0.0f);
            // p_cube_2->GetTransform().Translate    (glm::vec3(1.0f, 0.0f, 0.0f) * sin(glfwGetTime()) * delta_time);
            // p_cube_3->GetTransform().SetLocalScale(p_cube_3->GetTransform().GetLocalScale() + glm::vec3(0.2f) * delta_time * sin(glfwGetTime()));

            BehaviorUpdate  (p_handle, static_cast<float>(delta_time));
            GameObjectUpdate(p_handle, static_cast<float>(delta_time));

            lag -= delta_time;
        }

        mp_renderer->Render();
    }
}

void CEngine::BehaviorUpdate(GLFWwindow* p_window, float delta_time)
{
    // Behavior updates
    auto behavior_count = static_cast<uint32_t>(m_behaviors.size());
    for(uint32_t i = 0; i < behavior_count; ++i)
    {
        CBehavior* p_behavior = m_behaviors[i];

        // TODO : Root is not a valid reference
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

/* static */ void CEngine::RegisterBehavior(CBehavior* p_behavior)
{
    sp_instance->m_behaviors.push_back(p_behavior);
}

/* static */ void CEngine::UnregisterBehavior(CBehavior* p_behavior)
{
    std::vector<CBehavior*>& behaviors = sp_instance->m_behaviors;

    for(auto i = 0; i < behaviors.size(); ++i)
    {
        if(behaviors[i] == p_behavior)
        {
            behaviors[i] = behaviors.back();
            behaviors.pop_back();
            break;
        }
    }
}

}