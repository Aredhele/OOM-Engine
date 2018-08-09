/// \file       S_ConveyorAsset.cpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/S_Floppy.hpp"
#include "Game/Floppy/Asset/S_ConveyorAsset.hpp"

/* virtual */ void S_ConveyorAsset::Awake()
{
	m_speed      = 3.0f;
	m_asset_type = EAsset::ConveyorAsset;
}

/* virtual */ void S_ConveyorAsset::Start()
{
	Sdk::GameObject::AddMesh(GetGameObject(), "Asset_Cube");
}

/* virtual */ void S_ConveyorAsset::Update()
{
	auto& transform = *GetTransform();
	auto& position  = GetTransform()->GetPosition();

	// The is the target that the asset must reach
	const glm::vec3 target(0.0f, 0.0f, position.z);

	// Check distance from the origin
	const float distance = glm::distance(position, target);

	if (distance <= 20.0f)
	{
		// Finds the floppy
		auto* p_floppy_go = CGameObject::FindWithTag("Floppy");

		if (p_floppy_go)
		{
			auto* p_floppy = p_floppy_go->GetComponent<S_Floppy>();

			if (p_floppy)
				p_floppy->AddKiloByte(m_kilo_bytes);
		}

		// The asset has reached the floppy
		Destroy(GetGameObject());
		return;
	}

	// Translating the asset toward the center
	transform.Translate(GetTransform()->GetForward() * m_speed * CTime::delta_time);
}

/* virtual */ void S_ConveyorAsset::OnDestroy()
{
	// None
}
