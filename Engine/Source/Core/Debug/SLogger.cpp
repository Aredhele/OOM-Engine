/// \file       SLogger.cpp
/// \date       21/07/2018
/// \project    OOM-Engine
/// \package    Core/Debug
/// \author     Vincent STEHLY--CALISTO

#include <cstdio>  //< fprintf
#include <cstdarg> //< va_args

#include "Core/Debug/SLogger.hpp"

#ifndef NDEBUG
#   define __VA_LOG(FILE, ENGINE, LEVEL, FORMAT) \
        va_list  argList;                        \
        va_start(argList, FORMAT);               \
            fprintf (FILE, ENGINE);              \
            fprintf (FILE, LEVEL);               \
            vfprintf(FILE, FORMAT, argList);     \
            fprintf (FILE, "\n");                \
        va_end  (argList);
#else
#	define __VA_LOG(FILE, ENGINE, LEVEL, FORMAT)
#endif

namespace Oom
{

/* static */ void SLogger::LogUser(const char* szFormat, ...)
{ __VA_LOG(stdout, s_engine_name, "USER] : ", szFormat); }

/* static */ void SLogger::LogInfo(const char* szFormat, ...)
{ __VA_LOG(stdout, s_engine_name, "INFO] : ", szFormat); }

/* static */ void SLogger::LogWaring(const char* szFormat, ...)
{ __VA_LOG(stdout, s_engine_name, "WARN] : ", szFormat); }

/* static */ void SLogger::LogError(const char* szFormat, ...)
{ __VA_LOG(stderr, s_engine_name, "ERRO] : ", szFormat); }

}