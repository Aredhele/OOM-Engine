/// \file       IComponent.hpp
/// \date       22/07/2018 
/// \project    OOM-Engine
/// \package    Composite
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_I_COMPONENT_HPP__
#define OOM_ENGINE_I_COMPONENT_HPP__

#include "Composite/CObject.hpp"

namespace Oom
{

// Forward declaration
class CGameObject;
class CTransform;

class IComponent : public CObject
{
public:

    // Properties
    const CString&      GetTag        () const;
    const CTransform&   GetTransform  () const;
    const CGameObject&  GetGameObject () const;

    void SetTag (const CString& tag);
    void SetTag (CString&& tag);

public:

    // Methods
    // TODO

private:

    // Properties
    CString      m_tag;
    CTransform*  mp_transform   = nullptr;
    CGameObject* mp_game_object = nullptr;

private:

    uint32_t    m_component_id  = 0;
};

}

#endif // !OOM_ENGINE_I_COMPONENT_HPP__