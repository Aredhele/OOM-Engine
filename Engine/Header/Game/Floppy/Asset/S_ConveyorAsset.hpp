/// \file       S_ConveyorAsset.hpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_CONVEYOR_HPP__
#define OOM_ENGINE_S_CONVEYOR_HPP__

#include "SDK/SDK.hpp"
#include "Game/Floppy/Asset/IAsset.hpp"

class S_ConveyorAsset : public CBehavior, public IAsset
{
public:

	void Awake    () final;
	void Start    () final;
	void Update   () final;
	void OnDestroy() final;

public:

	void Clean	  ();
	void Hit	  ();

public:

	static const constexpr uint32_t s_cost = 10;

private:

	bool m_is_being_cleaned;
};

#endif // !OOM_ENGINE_S_CONVEYOR_HPP__
