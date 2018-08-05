/// \file       CContactListener.cpp
/// \date       05/08/2018
/// \project    OOM-Engine
/// \package    Physics
/// \author     Vincent STEHLY--CALISTO

#include <QU3E/dynamics/q3Contact.h>

#include "Composite/CGameObject.hpp"
#include "Composite/Component/CBehavior.hpp"

#include "Physics/CCollision.hpp"
#include "Physics/CContactListener.hpp"

namespace Oom
{
	
/* virtual */ void CContactListener::BeginContact(const q3ContactConstraint* p_contact)
{
	CGameObject* p_game_object_A = nullptr;
	CGameObject* p_game_object_B = nullptr;

	if (p_contact->A) p_game_object_A = (CGameObject*)p_contact->A->GetUserdata();
	if (p_contact->B) p_game_object_B = (CGameObject*)p_contact->B->GetUserdata();

	if (p_game_object_A)
	{
		CCollision collision {};
		collision.p_game_object = p_game_object_B;
		collision.p_body        = p_contact->bodyB;
		collision.p_box         = p_contact->B;

		auto behaviors = p_game_object_A->__GetBehaviors();

		for(auto* p_behavior : behaviors) {
			p_behavior->OnCollisionEnter(collision);
		}
	}

	if (p_game_object_B)
	{
		CCollision collision {};
		collision.p_game_object = p_game_object_A;
		collision.p_body        = p_contact->bodyA;
		collision.p_box         = p_contact->A;

		auto behaviors = p_game_object_B->__GetBehaviors();

		for (auto* p_behavior : behaviors) {
			p_behavior->OnCollisionEnter(collision);
		}
	}
}

/* virtual */ void CContactListener::EndContact(const q3ContactConstraint* p_contact)
{
	/// None
}

}