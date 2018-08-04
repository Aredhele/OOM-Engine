/// \file       CGizmosAudioSource.hpp
/// \date       04/08/2018
/// \project    OOM-Engine
/// \package    Render/Gizmos
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_GIZMOS_AUDIO_SOURCE_HPP__
#define OOM_ENGINE_C_GIZMOS_AUDIO_SOURCE_HPP__

#include <GLM/glm.hpp>

namespace Oom {

	void DrawAudioSource(glm::vec3 const& position, float distance_min, float distance_max, int resolution, float scale);

}

#endif // !OOM_ENGINE_C_GIZMOS_AUDIO_SOURCE_HPP__