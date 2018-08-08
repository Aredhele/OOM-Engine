/// \file       S_Floppy.hpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_FLOPPY_HPP__
#define OOM_ENGINE_S_FLOPPY_HPP__

#include "SDK/SDK.hpp"

class S_Floppy : public CBehavior
{
public:

	// Behavior
	void Awake    () final;
	void Start    () final;
	void Update   () final;
	void OnDestroy() final;

public:

	void AddKiloByte(uint32_t kilo_bytes);

public:

	uint32_t GetLimitSize  () const;
	uint32_t GetCurrentSize() const;
	
private:

	uint32_t m_limit_size;
	uint32_t m_current_size;

	S_Text*		 mp_text;
	CGameObject* mp_floppy_text;
	CGameObject* mp_floppy_sprite;
};

#endif // !OOM_ENGINE_S_FLOPPY_HPP__
