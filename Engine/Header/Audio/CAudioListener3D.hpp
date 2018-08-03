/// \file       CAudioListener3D.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Audio
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_AUDIO_LISTENER_3_D_HPP__
#define OOM_ENGINE_C_AUDIO_LISTENER_3_D_HPP__

#include <dsound.h>
#include "Composite/IComponent.hpp"

namespace Oom
{

class CAudioListener3D : public IComponent
{
public:

     void OnEnable  () final;
     void OnDisable () final;
     void OnDestroy () final;

protected:

    void _Register() final;
    void _Destroy () final;

private:

    IDirectSound3DListener8* mp_listener = nullptr;
};

}

#endif // !OOM_ENGINE_C_AUDIO_LISTENER_3_D_HPP__