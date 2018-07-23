/// \file       CEngine.inl
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#include "Composite/Component/CBehavior.hpp"

namespace Oom
{

template<class T>
/* static */ inline T* CEngine::AllocateComponent()
{
    static_assert(std::is_base_of<CBehavior,    T>::value);
    static_assert(std::is_default_constructible<T>::value);

    T* p_behavior = new T();
    sp_instance->BehaviorRegister(p_behavior);

    return p_behavior;
}

template<>
/* static */ inline CTransform* CEngine::AllocateComponent()
{ return sp_instance->AllocateTransform(); }

template<>
/* static */ inline CMeshFilter* CEngine::AllocateComponent()
{ return sp_instance->AllocateMeshFilter(); }

template<>
/* static */ inline CMaterial* CEngine::AllocateComponent()
{ return sp_instance->AllocateMaterial(); }

template<>
/* static */ inline CMeshRenderer* CEngine::AllocateComponent()
{ return sp_instance->AllocateMeshRenderer(); }

template<class T>
/* static */ inline void CEngine::ReleaseComponent(T* p_component)
{
    static_assert(std::is_base_of<CBehavior, T>::value);
    sp_instance->ReleaseBehavior(p_component);
}

template<>
/* static */ inline void CEngine::ReleaseComponent(CTransform* p_component)
{ sp_instance->ReleaseTransform(p_component); }

template<>
/* static */ inline void CEngine::ReleaseComponent(CMeshFilter* p_component)
{ sp_instance->ReleaseMeshFilter(p_component); }

template<>
/* static */ inline void CEngine::ReleaseComponent(CMaterial* p_component)
{ sp_instance->ReleaseMaterial(p_component); }

template<>
/* static */ inline void CEngine::ReleaseComponent(CMeshRenderer* p_component)
{ sp_instance->ReleaseMeshRenderer(p_component); }

}