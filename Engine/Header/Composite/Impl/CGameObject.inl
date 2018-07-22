/// \file       CGameObject.inl
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    CGameObject
/// \author     Vincent STEHLY--CALISTO

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

    // 1 - Engine allocation
    // 2 - Add component to go

    return nullptr;
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