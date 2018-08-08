/// \file       S_PointLight.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_POINT_LIGHT_HPP__
#define OOM_ENGINE_S_POINT_LIGHT_HPP__

#include "Composite/Component/CBehavior.hpp"

class S_PointLight : public Oom::CBehavior
{
public:

	void Awake () override;
    void Start () override;
    void Update() override;

    void SetRange    (float range);
    void SetIntensity(float intensity);
    void SetColor    (glm::vec3 const& color);

    float            GetRange    () const;
    float            GetIntensity() const;
    glm::vec3 const& GetColor    () const;

private:

    float     m_range;
    float     m_intensity;
    glm::vec3 m_color;
};

#endif // !OOM_ENGINE_S_POINT_LIGHT_HPP__