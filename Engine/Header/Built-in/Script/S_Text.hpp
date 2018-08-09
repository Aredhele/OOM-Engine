/// \file       S_Text.hpp
/// \date       02/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_TEXT_HPP__
#define OOM_ENGINE_S_TEXT_HPP__

#include "Composite/Component/CBehavior.hpp"

class S_Text : public Oom::CBehavior
{
public:

    void Start   () override;
    void Update  () override;
    void SetText (const Oom::CString& text );

private:

    void UpdateText();

private:

    Oom::CString m_text;
};

#endif // !OOM_ENGINE_S_TEXT_HPP__