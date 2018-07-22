/// \file       CEngine.inl
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#include "Composite/Component/CTransform.hpp"

namespace Oom
{

template<class T>
/* static */ inline T* CEngine::AllocateComponent()
{
    static_assert(std::is_base_of<CBehavior, T>::value);
    static_assert(std::is_default_constructible<T>::value);

    // Behavior
    T* p_component = new T();
    sp_instance->BehaviorRegister(p_component);

    return p_component;
}

template<>
/* static */ inline CTransform* CEngine::AllocateComponent()
{
    CTransform* p_transform = new CTransform();
    return p_transform;
}

template<class T>
/* static */ inline void CEngine::ReleaseComponent(T* p_component)
{
    // Behavior
    delete p_component;
}


}