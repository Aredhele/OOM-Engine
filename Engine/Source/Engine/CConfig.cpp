/// \file       CConfig.cpp
/// \date       07/08/2018
/// \project    OOM-Engine
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#include "Engine/CConfig.hpp"

namespace Oom
{

/* static */ bool  CConfig::window_full_screen     = false;
/* static */ bool  CConfig::enable_anti_aliasing   = true;
/* static */ bool  CConfig::enable_post_processing = true;

/* static */ int   CConfig::opengl_version_major      = 3;
/* static */ int   CConfig::opengl_version_minor      = 3;
/* static */ int   CConfig::default_window_width      = 1600;
/* static */ int   CConfig::default_window_height     = 900;
/* static */ int   CConfig::default_update_per_second = 60;

}