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

    uint32_t id = DSID(typeid(T).name());
    for(auto i = 0; i < m_components.size(); ++i)
    {
        if(m_components[i]->m_component_id == id)
           return (T*)m_components[i];
    }

    return nullptr;
}

template<class T>
std::vector<T*> CGameObject::GetComponents(void)
{
    // Static check
    std::vector<T*> components;
    static_assert(std::is_base_of<IComponent, T>::value);

    uint32_t id = DSID(typeid(T).name());
    for(auto i = 0; i < m_components.size(); ++i)
    {
        if(m_components[i]->m_component_id == id)
            components.push_back(m_components[i]);
    }

    return components;
}

template<class T>
T* CGameObject::AddComponent(void)
{
    // Static check
    static_assert(std::is_base_of<IComponent, T>::value);

    IComponent* p_component = CEngine::AllocateComponent<T>();
    p_component->m_component_id               = DSID(typeid(T).name());
    p_component->mp_transform                 = &m_transform;
    p_component->mp_game_object               = this;
    p_component->mp_transform->mp_game_object = this;
    p_component->mp_transform->mp_parent      = m_transform.mp_parent;

    m_components.push_back(p_component);

    return (T*)p_component;
}

template<class T>
void CGameObject::RemoveComponent(void)
{
    // Static check
    static_assert(std::is_base_of<IComponent, T>::value);

    uint32_t id = DSID(typeid(T).name());
    for(auto i = 0; i < m_components.size(); ++i)
    {
        if(m_components[i]->m_component_id == id)
        {
            m_components[i]->__DestroyMessage();
            m_components[i] = m_components.back();
            m_components.pop_back();
            break;
        }
    }
}

template<class T>
void CGameObject::RemoveComponents(void)
{
    // Static check
    static_assert(std::is_base_of<IComponent, T>::value);

    uint32_t id = DSID(typeid(T).name());
    for(auto i = 0; i < m_components.size(); /* no increment */ )
    {
        if(m_components[i]->m_component_id == id)
        {
            m_components[i]->__DestroyMessage();
            m_components[i] = m_components.back();
            m_components.pop_back();
        }
        else
        {
            i++;
        }
    }
}

void CGameObject::RemoveComponents(void)
{
    for(auto* p_component : m_components)
        p_component->__DestroyMessage();

    m_components.clear();
}

}