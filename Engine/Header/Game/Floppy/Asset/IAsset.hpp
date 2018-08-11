/// \file       IAsset.hpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_I_ASSET_HPP__
#define OOM_ENGINE_I_ASSET_HPP__

#include "SDK/SDK.hpp"

enum EAsset
{
	BigAsset,
	BusAsset,
	ConveyorAsset
};

class IAsset
{
public:

	void SetSpeed     (float speed);
	void SetHitPoint  (uint32_t hit_point);
	void SetAssetType (EAsset asset_type);
	void SetKiloBytes (uint32_t kilo_bytes);

public:

	float	 GetSpeed     () const;
	uint32_t GetHitPoint  () const;
	EAsset   GetAssetType () const;
	uint32_t GetKiloBytes () const;

protected:

	
	float     m_speed;
	EAsset    m_asset_type;
	uint32_t  m_kilo_bytes;

	uint32_t  m_hit_point;
	glm::vec3 m_direction;
};

#endif // !OOM_ENGINE_S_ASSET_HPP__
