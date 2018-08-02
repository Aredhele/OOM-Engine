/// \file       SRenderData.hpp
/// \date       02/08/2018
/// \project    OOM-Engine
/// \package    Render/Shader
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_RENDER_DATA_HPP__
#define OOM_ENGINE_S_RENDER_DATA_HPP__

#include <vector>
#include <GLM/glm.hpp>

namespace Oom
{

struct SPointLight
{
    float     range;
    float     intensity;
    glm::vec3 color;
    glm::vec3 position;
};

struct SDirectionalLight
{
    float     m_light_intensity;
    float     m_ambient_intensity;
    glm::vec3 m_light_color;
    glm::vec3 m_ambient_color;
    glm::vec3 m_direction;
};

struct SRenderData
{
    glm::mat4 MVP;
    glm::mat4 M;
    glm::mat4 V;
    glm::mat4 P;

    SDirectionalLight        directional;
    std::vector<SPointLight> point_lights;
};

}

#endif // !OOM_ENGINE_S_RENDER_DATA_HPP__