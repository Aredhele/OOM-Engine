/// \file       S_Translate.hpp
/// \date       06/08/2018
/// \project    OOM-Engine
/// \package    Built-in/SCirpt
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_TRANSLATE_HPP__
#define OOM_ENGINE_S_TRANSLATE_HPP__

#include "Composite/Component/CBehavior.hpp"

class S_Translate : public Oom::CBehavior
{
public:

	// Behavior
	void Start () override;
	void Update() override;
};

#endif // !OOM_ENGINE_S_TRANSLATE_HPP__