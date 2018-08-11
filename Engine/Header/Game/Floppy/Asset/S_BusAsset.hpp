/// \file       S_BusAsset.hpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_BUS_ASSET_HPP__
#define OOM_ENGINE_S_BUS_ASSET_HPP__

#include "SDK/SDK.hpp"
#include "Game/Floppy/Asset/IAsset.hpp"

class S_BusAsset : public CBehavior, public IAsset
{
public:

	void Awake				()								final;
	void Start				()								final;
	void Update				()								final;
	void OnDestroy			()								final;
	void OnCollisionEnter	(const CCollision& collision)	final;

public:

	void Hit();

public:

	static const constexpr uint32_t s_cost = 10;
};

#endif // !OOM_ENGINE_S_BUS_ASSET_HPP__
