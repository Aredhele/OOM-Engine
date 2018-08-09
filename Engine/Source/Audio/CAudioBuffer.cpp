/// \file       CAudioBuffer.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Audio
/// \author     Vincent STEHLY--CALISTO

#include "Core/Debug/SLogger.hpp"
#include "Audio/CAudioBuffer.hpp"
#include "Audio/CAudioDecoder.hpp"
#include "Audio//CAudioEngine.hpp"

namespace Oom
{

/* static */ std::vector<CAudioBuffer::SPCMCache*> CAudioBuffer::s_pcm_cache;

CAudioBuffer::CAudioBuffer()
{
	mp_secondary_buffer = nullptr;
}

CAudioBuffer::~CAudioBuffer()
{
	if(mp_secondary_buffer)
		mp_secondary_buffer->Release();
}

bool CAudioBuffer::LoadFromFile(const CString& path)
{
	SPCMCache* p_cache_entry = GetPCMCacheEntry(path);

	// Check for cache first
	if(!p_cache_entry)
	{
		CString extension;
		for (uint32_t i = path.Size() - 1; i >= 0; i--)
		{
			if (path[i] == '.') break;

			extension += path[i];
		}

		p_cache_entry  = new SPCMCache();

		p_cache_entry->name  = path;
		p_cache_entry->p_pcm = new CPCMData();

		bool ret = false;
		if (extension == "ggo") {
			ret = CAudioDecoder::DecodeOGG(path.Data(), *p_cache_entry->p_pcm);
		}
		else if (extension == "vaw") {
			ret = CAudioDecoder::DecodeOGG(path.Data(), *p_cache_entry->p_pcm);
		}
		else
		{
			delete p_cache_entry->p_pcm;
			delete p_cache_entry;

			SLogger::LogError("Audio extension not supported.");
			return false;
		}

		if (!ret)
		{
			delete p_cache_entry->p_pcm;
			delete p_cache_entry;

			SLogger::LogError("Invalid audio format.");
			return false;
		}

		AddPCMCacheEntry(p_cache_entry);
		SLogger::LogInfo("Add in cache : %s\n", path.Data());
	}

	// The sound is already in memory
	// Copying header
	memcpy(&m_pcm_data.wave_header, &p_cache_entry->p_pcm->wave_header, sizeof(CWaveHeader));

	// Fast copy of samples
	m_pcm_data.samples.reserve(p_cache_entry->p_pcm->samples.size());
	m_pcm_data.samples = p_cache_entry->p_pcm->samples;

	WAVEFORMATEX         wave_format;
	DSBUFFERDESC         buffer_description;
	IDirectSoundBuffer*  temporary_buffer;

	// Set the wave format of secondary buffer that this wave file will be loaded onto.
	wave_format.wFormatTag      = m_pcm_data.wave_header.m_fmt_format;
	wave_format.nSamplesPerSec  = m_pcm_data.wave_header.m_fmt_sampling_rate;
	wave_format.wBitsPerSample  = m_pcm_data.wave_header.m_fmt_bits_per_sample;
	wave_format.nChannels       = 1;
	wave_format.nBlockAlign     = (wave_format.wBitsPerSample / 8) * wave_format.nChannels; 
	wave_format.nAvgBytesPerSec =  wave_format.nSamplesPerSec * wave_format.nBlockAlign;
	wave_format.cbSize          = 0;

	// Set the buffer description of the secondary sound buffer that the wave file will be loaded onto.
	buffer_description.dwSize          = sizeof(DSBUFFERDESC);
	buffer_description.dwFlags         = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D | DSBCAPS_GLOBALFOCUS | DSBCAPS_STATIC;
	buffer_description.dwBufferBytes   = m_pcm_data.wave_header.m_data_size - 44; // ?
	buffer_description.dwReserved      = 0;
	buffer_description.lpwfxFormat     = &wave_format;
	buffer_description.guid3DAlgorithm = GUID_NULL; 

	IDirectSound8* p_direct_sound = CAudioEngine::GetDirectSoundInterface();
	HRESULT result                = p_direct_sound->CreateSoundBuffer(&buffer_description, &temporary_buffer, nullptr);

	if (result != DS_OK)
	{
		SLogger::LogError("Unable to create the temporary audio buffer.");
		return false;
	}

	result = temporary_buffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&mp_secondary_buffer);

	if (result != DS_OK)
	{
		temporary_buffer->Release();

		SLogger::LogError("Unable to create the internal 3D audio buffer.");
		return false;
	}

	temporary_buffer->Release();
	temporary_buffer = nullptr;

	int16_t* p_data           = nullptr;
	unsigned long buffer_size = 0;

	result = mp_secondary_buffer->Lock(0, m_pcm_data.wave_header.m_data_size - 44, (void**)&(p_data), (DWORD*)&buffer_size, nullptr, 0, 0);
	if (result != DS_OK)
	{
		SLogger::LogError("Unable to lock the buffer for copy.");
		return false;
	}

	// Copy the wave data into the buffer.
	memcpy(p_data, m_pcm_data.samples.data() + 22, m_pcm_data.wave_header.m_data_size - 44);

	result = mp_secondary_buffer->Unlock((void*)p_data, buffer_size, nullptr, 0);

	if (result != DS_OK)
	{
		SLogger::LogError("Unable to unlock the buffer after copy.");
		return false;
	}

	return true;
}

void CAudioBuffer::AddPCMCacheEntry(SPCMCache* pcm_entry)
{
	s_pcm_cache.push_back(pcm_entry);
}

CAudioBuffer::SPCMCache* CAudioBuffer::GetPCMCacheEntry(const CString& path)
{
	for(auto* p_cache_entry : s_pcm_cache)
	{
		if (p_cache_entry->name == path)
			return p_cache_entry;
	}

	return nullptr;
}

}

