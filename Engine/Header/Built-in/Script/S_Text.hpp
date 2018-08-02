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

    void Start () override;
    void Update() override;

    void Set        (const Oom::CString& text, const glm::tvec2<int>& position, uint32_t size, const glm::vec3& color);
    void SetSize    (uint32_t size);
    void SetText    (const Oom::CString& text );
    void SetColor   (const glm::vec3& color   );
    void SetPosition(const glm::tvec2<int>& position);

private:

    void UpdateText();

private:

    Oom::CString    m_text;
    uint32_t        m_size;
    glm::vec3       m_color;
    glm::tvec2<int> m_position;
};

#endif // !OOM_ENGINE_S_TEXT_HPP__