/// \file       S_Rotate.hpp
/// \date       06/08/2018
/// \project    OOM-Engine
/// \package    Built-in/SCirpt
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_ROTATE_HPP__
#define OOM_ENGINE_S_ROTATE_HPP__

#include "Composite/Component/CBehavior.hpp"

class S_Rotate : public Oom::CBehavior
{
public:

	// Behavior
	void Awake   () override;
	void Start   () override;
	void Update  () override;
	void IsAround();
	void SetAxis (const glm::vec3& axis);

private:

	bool	  m_around;
	glm::vec3 m_axis;
};

#endif // !OOM_ENGINE_S_ROTATE_HPP__