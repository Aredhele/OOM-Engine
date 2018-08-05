/// \file       CContactListener.hpp
/// \date       05/08/2018
/// \project    OOM-Engine
/// \package    Physics
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_CONTACT_LISTENER_HPP__
#define OOM_ENGINE_C_CONTACT_LISTENER_HPP__

#include <QU3E/q3.h>

namespace Oom
{
	
class CContactListener : public q3ContactListener
{
public:

	void BeginContact(const q3ContactConstraint* p_contact) final;
	void EndContact  (const q3ContactConstraint* p_contact) final;
};

}

#endif // !OOM_ENGINE_C_CONTACT_LISTENER_HPP__