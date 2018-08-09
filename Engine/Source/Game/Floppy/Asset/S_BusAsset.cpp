/// \file       S_BusAsset.cpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/S_Floppy.hpp"
#include "Game/Floppy/Asset/S_BusAsset.hpp"

/* virtual */ void S_BusAsset::Awake()
{
	m_speed      = 3.0f;
	m_asset_type = EAsset::BusAsset;
}

/* virtual */ void S_BusAsset::Start()
{
	Sdk::GameObject::AddMesh(GetGameObject(), "Asset_Cube");
}

/* virtual */ void S_BusAsset::Update()
{
	auto& transform = *GetTransform();
	auto& position  = GetTransform()->GetPosition();

	// The is the target that the asset must reach
	const glm::vec3 target(0.0f, 0.0f, position.z);

	// Check distance from the origin
	const float distance = glm::distance(position, target);

	if(distance <= 20.0f)
	{
		// Finds the floppy
		auto* p_floppy_go = CGameObject::FindWithTag("Floppy");

		if(p_floppy_go)
		{
			auto* p_floppy = p_floppy_go->GetComponent<S_Floppy>();

			if(p_floppy)
				p_floppy->AddKiloByte(m_kilo_bytes);
		}
		
		// The asset has reached the floppy
		Destroy(GetGameObject());
		return;
	}

	// Translating the asset toward the center
	transform.Translate(GetTransform()->GetForward() * m_speed * CTime::delta_time);
}

/* virtual */ void S_BusAsset::OnDestroy()
{
	// None
}
