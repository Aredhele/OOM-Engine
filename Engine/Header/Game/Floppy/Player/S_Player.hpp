/// \file       S_Player.hpp
/// \date       09/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_PLAYER_HPP__
#define OOM_ENGINE_S_PLAYER_HPP__

#include "SDK/SDK.hpp"

class S_Player : public CBehavior
{
public:

	void Awake       () final;
	void Start       () final;
	void Update      () final;
	void OnDestroy   () final;
	void OnDrawGizmos() final;

public:

	void	SetShootDelay	(float delay);
	float	GetShootDelay	(float delay);

private:

	CAudioBuffer    m_shoot_buffer;
	CAudioBuffer	m_music_buffer;

	CAudioSource3D* mp_music_source;
	CAudioSource3D* mp_shoot_source;

	float			m_shoot_delay;
	float			m_shoot_elapsed;
};

#endif // !OOM_ENGINE_S_PLAYER_HPP__
