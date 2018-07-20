/// \file       SLogger.hpp
/// \date       09/02/2018
/// \project    OOM-Engine
/// \package    Core/Debug
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_LOGGER_HPP__
#define OOM_ENGINE_S_LOGGER_HPP__

namespace Oom
{

class SLogger
{
public:

    static void LogUser  (const char * szFormat, ...);
    static void LogInfo  (const char * szFormat, ...);
    static void LogWaring(const char * szFormat, ...);
    static void LogError (const char * szFormat, ...);

private:

    static constexpr const char* s_engine_name = "[OOM][";
};

}

#endif // !OOM_ENGINE_S_LOGGER_HPP__