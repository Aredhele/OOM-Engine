/// \file       CWaveHeader.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Audio
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_WAVE_HEADER_HPP__
#define OOM_ENGINE_C_WAVE_HEADER_HPP__

#include <cstdio>
#include <cstring>

namespace Oom
{

class CWaveHeader
{
public:

	CWaveHeader ();
	CWaveHeader (unsigned long sample_rate, unsigned short bits_per_sample, unsigned short channels, unsigned long data_size);

public:

	static bool ISWaveFile(FILE* p_wave_file);

private:

	unsigned char  m_riff_ID[4];		   ///< 'RIFF'
	unsigned long  m_riff_size;			   ///< DataSize + 44
	unsigned char  m_riff_type[4];		   ///< WAVE'

	unsigned char  m_fmt_ID[4];			   ///< 'fmt '
	unsigned long  m_fmt_length;		   ///< 16
	unsigned short m_fmt_format;		   ///< 1 (=MS PCM)
	unsigned short m_fmt_channels;		   ///< 1 = mono, 2 = stereo
	unsigned long  m_fmt_sampling_rate;	   ///< (e.g 44100)
	unsigned long  m_fmt_data_rate;		   ///< SamplingRate * BlockAlign
	unsigned short m_fmt_block_align;	   ///< Channels * BitsPerSample / 8
	unsigned short m_fmt_bits_per_sample;  ///< 8 or 16

	unsigned char  m_data_ID[4];		   ///<'data'
	unsigned long  m_data_size;		       ///< Size of the following data	
};

}

#endif ! //OOM_ENGINE_C_WAVE_HEADER_HPP__