/// \file       CEngine.inl
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#include "Composite/Component/CTransform.hpp"

namespace Oom
{

template<class T>
inline T* CEngine::AllocateComponent()
{
    static_assert(std::is_base_of<CBehavior, T>::value);
    static_assert(std::is_default_constructible<T>::value);

    // Behavior
    T* p_behavior = new T();
    return p_behavior;
}

template<>
inline CTransform* CEngine::AllocateComponent()
{
    CTransform* p_transform = new CTransform();
    return p_transform;
}

template<class T>
inline void CEngine::ReleaseComponent(T* p_component)
{
    // Behavior
    delete p_component;
}


}