/// \file       S_LookAt.hpp
/// \date       06/08/2018
/// \project    OOM-Engine
/// \package    Composite
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_LOOK_AT_HPP__
#define OOM_ENGINE_S_LOOK_AT_HPP__

#include <SDK/SDK.hpp>

class S_LookAt : public Oom::CBehavior
{
public:

	void Start     () override;
	void Update    () override;

	void SetTarget (Oom::CGameObject* p_game_object);

private:

	Oom::CGameObject* mp_target = nullptr;
};

#endif // !OOM_ENGINE_S_LOOK_AT_HPP__