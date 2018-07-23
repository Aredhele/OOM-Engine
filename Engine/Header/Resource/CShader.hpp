/// \file       CShader.hpp
/// \date       23/07/2018
/// \project    OOM-Engine
/// \package    CShader
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_SHADER_HPP__
#define OOM_ENGINE_C_SHADER_HPP__

#include <Render/Shader/SShaderManager.hpp>
#include "Render/Config.hpp"

class CShader
{
public:

    void    SetProgram  (GLuint program);
    GLuint  GetProgram  () const;

    Oom::SShaderManager::

protected:

    GLuint m_program;
};

#endif // !OOM_ENGINE_C_SHADER_HPP__