/// \file       CWaveHeader.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Audio
/// \author     Vincent STEHLY--CALISTO

#include "Audio/CWaveHeader.hpp"

namespace Oom
{

CWaveHeader::CWaveHeader()
{
	memset(this, 0x0, sizeof(*this));
}

CWaveHeader::CWaveHeader(unsigned long sample_rate, unsigned short bits_per_sample, unsigned short channels, unsigned long data_size)
{
	memset(this, 0x0, sizeof(*this));

	// Set Riff-Chunk
	memcpy(m_riff_ID,   "RIFF", 4);
	m_riff_size = data_size + 44;
	memcpy(m_riff_type, "WAVE", 4);

	// Set Fmt-Chunk
	memcpy(m_fmt_ID, "fmt ", 4);
	m_fmt_length          = 16;
	m_fmt_format          = 1;
	m_fmt_channels        = channels;
	m_fmt_sampling_rate   = sample_rate;
	m_fmt_block_align     = channels * bits_per_sample / 8;
	m_fmt_data_rate       = channels * bits_per_sample * sample_rate / 8;
	m_fmt_bits_per_sample = bits_per_sample;

	// Set Data-Chunk
	memcpy(m_data_ID, "data", 4);
	m_data_size = data_size;
}

/* static */ bool CWaveHeader::ISWaveFile(FILE* p_wave_file)
{
	CWaveHeader header;

	// Reading the first 44 bytes
	fread(&header, 1, 44, p_wave_file);

	char riff_id  [5];
	char riff_type[5];
	char fmt_id   [5];
	char data_id  [5];

	memcpy(riff_id,   &header.m_riff_ID,   4);
	memcpy(riff_type, &header.m_riff_type, 4);
	memcpy(fmt_id,    &header.m_fmt_ID,    4);
	memcpy(data_id,   &header.m_data_ID,   4);

	riff_id  [4] = '\0';
	riff_type[4] = '\0';
	fmt_id   [4] = '\0';
	data_id  [4] = '\0';

	return (strcmp(riff_id, "RIFF") == 0 && strcmp(riff_type, "WAVE") == 0 && 
		    strcmp(fmt_id,  "fmt ") == 0 && strcmp(data_id,   "data") == 0);
}

}
