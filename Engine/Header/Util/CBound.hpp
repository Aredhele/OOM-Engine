/// \file       CBound.hpp
/// \date       23/07/2018
/// \project    OOM-Engine
/// \package    Resource
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_BOUND_HPP__
#define OOM_ENGINE_C_BOUND_HPP__

#include <GLM/glm.hpp>

namespace Oom
{

class CBound
{
public:

    const glm::vec3& GetCenter  () const;
    const glm::vec3& GetExtents () const;
    void SetCenter (const glm::vec3& center);
    void SetExtents(const glm::vec3& extents);

private:

    glm::vec3 m_center;
    glm::vec3 m_extents;
};

}

#endif // !OOM_ENGINE_C_BOUND_HPP__