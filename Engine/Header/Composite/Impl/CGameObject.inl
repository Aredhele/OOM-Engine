/// \file       CGameObject.inl
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    CGameObject
/// \author     Vincent STEHLY--CALISTO

#include "CEngine.hpp"
#include "Core/Standard/StringID.hpp"

namespace Oom
{

template<class T>
T* CGameObject::GetComponent(void)
{
    // Static check
    static_assert(std::is_base_of<IComponent, T>::value);

    // 1 - Component lookup
    // 2 - Gathers the first component

    return nullptr;
}

template<class T>
std::vector<T*> CGameObject::GetComponents(void)
{
    // Static check
    static_assert(std::is_base_of<IComponent, T>::value);

    // 1 - Component lookup
    // 2 - Gathers all components

    return std::vector<T*>();
}

template<class T>
T* CGameObject::AddComponent(void)
{
    // Static check
    static_assert(std::is_base_of<IComponent, T>::value);

    T* p_component = CEngine::AllocateComponent<T>();
    p_component->m_component_id = DSID(typeid(T).name());
    p_component->mp_transform   = &m_transform;
    p_component->mp_game_object = this;

    m_components.push_back(p_component);

    return p_component;
}

template<class T>
void CGameObject::RemoveComponent(void)
{
    // Static check
    static_assert(std::is_base_of<IComponent, T>::value);

    // 1 - Component lookup
    // 2 - Removes the component
    // 3 - Engine deallocation
}

template<class T>
void CGameObject::RemoveComponents(void)
{
    // Static check
    static_assert(std::is_base_of<IComponent, T>::value);

    // 1 - Component lookup
    // 2 - Removes the component
    // 3 - Engine deallocation
}

}