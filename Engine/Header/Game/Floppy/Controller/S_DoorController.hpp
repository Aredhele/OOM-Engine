/// \file       S_DoorController.hpp
/// \date       10/08/2018
/// \project    OOM-Engine
/// \package    Game/Floppy/Controller
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_DOOR_CONTROLLER_HPP__
#define OOM_ENGINE_S_DOOR_CONTROLLER_HPP__

#include "SDK/SDK.hpp"

class S_DoorController : public CBehavior
{
public:

	void Awake    () final;
	void Start    () final;
	void Update   () final;
	void OnDestroy() final;

public:

	void OpenDoor  ();
	void CloseDoor ();
};

#endif // !OOM_ENGINE_S_CONVEYOR_AUDIO_CONTROLLER_HPP__
