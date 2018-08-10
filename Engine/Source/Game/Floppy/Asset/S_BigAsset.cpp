/// \file       S_BigAsset.cpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/S_Floppy.hpp"
#include "Game/Floppy/Asset/S_BigAsset.hpp"
#include "Game/Floppy/Util/S_SoundSource.hpp"

/* virtual */ void S_BigAsset::Awake()
{
	m_speed = 3.0f;
	m_asset_type = EAsset::BigAsset;
}

/* virtual */ void S_BigAsset::Start()
{
	auto* p_game_object = GetGameObject();

	// Adds the renderer
	Sdk::GameObject::AddMesh(p_game_object, "Super_Asset");

	// Adds the collider
	auto* p_body = p_game_object->AddComponent<CRigidBody>();
	auto* p_box  = p_game_object->AddComponent<CBoxCollider>();

	p_body->SetBodyType(CRigidBody::EBodyType::Kinematic);
	p_body->SetOrientationZ(GetTransform()->GetEulerAngles().z);

	p_box->SetExtent(glm::vec3(4.0f, 4.0f, 4.0f));
}

/* virtual */ void S_BigAsset::Update()
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
	transform.Translate(transform.GetForward() * m_speed * CTime::delta_time);
}

/* virtual */ void S_BigAsset::OnDestroy()
{
	auto* p_death_sound = Instantiate(GetTransform()->GetPosition());
	auto* p_sound_compo = p_death_sound->AddComponent<S_SoundSource>();

	p_sound_compo->SetSound("Resources/Sound/sound_bigasset_killed.ogg");
	Destroy(p_death_sound, 2.0f);
}
