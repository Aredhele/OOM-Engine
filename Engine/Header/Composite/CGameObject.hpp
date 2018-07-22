/// \file       CGameObject.hpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Composite
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_GAME_OBJECT_HPP__
#define OOM_ENGINE_C_GAME_OBJECT_HPP__

#include <vector>

#include "Composite/CObject.hpp"
#include "Core/Standard/CString.hpp"

// Components
#include "Composite/IComponent.hpp"
#include "Composite/CTransform.hpp"

namespace Oom
{

class CGameObject : public CObject
{
public:

    // Properties
    const CString& GetTag () const;

    void SetTag (const CString& tag);
    void SetTag (CString&& tag);

public:

    template <class T> inline T *				GetComponent			(/* void */);
    template <class T> inline std::vector<T*>  GetComponents			(/* void */);
    template <class T> inline T *				AddComponent			(/* void */);
    template <class T> inline void				RemoveComponent			(/* void */);
    template <class T> inline void				RemoveComponents		(/* void */);

private:

    // Properties
    CString m_tag;
    bool    m_is_active = true;

private:

    friend class CTransform;

    CTransform                m_transform;
    std::vector<IComponent* > m_components;
};

}

#include "Composite/Impl/CGameObject.inl"

#endif // !OOM_ENGINE_C_GAME_OBJECT_HPP__