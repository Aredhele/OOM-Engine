/// \file       CConfig.hpp
/// \date       07/08/2018
/// \project    OOM-Engine
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_CONFIG_HPP__
#define OOM_ENGINE_C_CONFIG_HPP__

namespace Oom
{

class CConfig
{
public:

	static bool  window_full_screen;
	static bool  enable_anti_aliasing;
	static bool  enable_post_processing;

	static int   opengl_version_major;
	static int   opengl_version_minor;
	static int   default_window_width;
	static int   default_window_height;
	static int   default_update_per_second;
};

}

#endif // !OOM_ENGINE_C_CONFIG_HPP__