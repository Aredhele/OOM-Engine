/// \file       CCollision.hpp
/// \date       05/08/2018
/// \project    OOM-Engine
/// \package    Physics
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_COLLISION_HPP__
#define OOM_ENGINE_C_COLLISION_HPP__

// Forward declaration
struct q3Box;
struct q3Body;

namespace Oom
{

// Forward declaration
class CGameObject;

}

struct CCollision
{
	Oom::CGameObject* p_game_object;
	q3Box*			  p_box;
	q3Body*           p_body;
};

#endif // OOM_ENGINE_C_COLLISION_HPP__