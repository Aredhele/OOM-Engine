/// \file       CObject.hpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Composite
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_OBJECT_HPP__
#define OOM_ENGINE_C_OBJECT_HPP__

#include "Core/Standard/CString.hpp"

namespace Oom
{

class CObject
{
public:

    void           SetName (const CString& name);
    void           SetName (CString&& name);
    const CString& GetName () const;

private:

    CString m_name;
};

}

#endif // !OOM_ENGINE_C_OBJECT_HPP__