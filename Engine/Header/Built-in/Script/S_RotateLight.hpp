/// \file       S_RotateLight.hpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/SCirpt
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_ROTATE_LIGHT_HPP__
#define OOM_ENGINE_S_ROTATE_LIGHT_HPP__

class S_PointLight;
class S_DirectionalLight;

class S_RotateLight : public Oom::CBehavior
{
public:

	void Awake () override;
	void Start () override;
	void Update() override;

private:

	S_PointLight*       mp_p_light = nullptr;
	S_DirectionalLight* mp_d_light = nullptr;
};

#endif // !OOM_ENGINE_S_ROTATE_LIGHT_HPP__