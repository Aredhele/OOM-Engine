/// \file       S_Spawner.hpp
/// \date       07/08/2018
/// \project    OOM-Engine
/// \package    Built-in/SCirpt
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_SPAWNER_HPP__
#define OOM_ENGINE_S_SPAWNER_HPP__

#include <SDK/SDK.hpp>

class S_Spawner : public Oom::CBehavior
{
public:

	void Start           () override;
	void Update          () override;
	void OnCollisionEnter(const CCollision& collision) override;
};

#endif // !OOM_ENGINE_S_SPAWNER_HPP__