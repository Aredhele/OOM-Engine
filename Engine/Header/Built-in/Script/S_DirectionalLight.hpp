/// \file       S_DirectionalLight.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_DIRECTIONAL_LIGHT_HPP__
#define OOM_ENGINE_S_DIRECTIONAL_LIGHT_HPP__

#include "Composite/Component/CBehavior.hpp"

class S_DirectionalLight : public Oom::CBehavior
{
public:

	void Awake () override;
    void Start () override;
    void Update() override;

    void SetLightIntensity   (float intensity);
    void SetAmbientIntensity (float intensity);
    void SetDirection        (glm::vec3 const& direction);
    void SetLightColor       (glm::vec3 const& color);
    void SetAmbientColor     (glm::vec3 const& color);

    float            GetLightIntensity   () const;
    float            GetAmbientIntensity () const;
    glm::vec3 const& GetDirection        () const;
    glm::vec3 const& GetLightColor       () const;
    glm::vec3 const& GetAmbientColor     () const;

private:

    float     m_light_intensity;
    float     m_ambient_intensity;
    glm::vec3 m_light_color;
    glm::vec3 m_ambient_color;
    glm::vec3 m_direction;
};

#endif // !OOM_ENGINE_S_DIRECTIONAL_LIGHT_HPP__