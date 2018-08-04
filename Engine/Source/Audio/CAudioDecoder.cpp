/// \file       CAudioDecoder.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Audio
/// \author     Vincent STEHLY--CALISTO

#include <cmath>
#include <vector>
#include <Windows.h>
#include <VORBIS/codec.h>
#include "Core/Debug/SLogger.hpp"
#include "Audio/CAudioDecoder.hpp"

namespace Oom
{

/* static */ bool CAudioDecoder::DecodeOGG(const char* p_path, CPCMData& pcm_data)
{
	// Opening the file
	FILE* f_in  = fopen(p_path, "rb");
	pcm_data.samples.clear();

	if (!f_in)
	{
		SLogger::LogError("Unable to open %s.", p_path);
		return false;
	}

	long cumulative_read = 0;
	long ogg_total_size  = 0;

	// Getting the size of the file
	fseek(f_in, 0, SEEK_END);
	ogg_total_size = ftell(f_in);
	fseek(f_in, 0, SEEK_SET);

	// Page buffer
	ogg_int16_t convbuffer[4096];

	int  convsize    = 4096;
	long byteWritten = 0;

	ogg_sync_state   oy; // sync and verify incoming physical bitstream
	ogg_stream_state os; // take physical pages, weld into a logical stream of packets
	ogg_page         og; // one Ogg bitstream page. Vorbis packets are inside
	ogg_packet       op; // one raw packet of data for decode
	vorbis_info      vi; // struct that stores all the static vorbis bitstream settings
	vorbis_comment   vc; // struct that stores all the bitstream user comments
	vorbis_dsp_state vd; // central working state for the packet->PCM decoder
	vorbis_block     vb; // local working space for packet->PCM decode

	char* buffer = nullptr;
	int   bytes = 0;

	ogg_sync_init(&oy);

	while (true)
	{
		int i   = 0;
		int eos = 0;
		
		buffer = ogg_sync_buffer  (&oy, 4096);
		bytes  = fread(buffer, 1, 4096, f_in);

		ogg_sync_wrote(&oy, bytes);
		cumulative_read += bytes;

		// Getting the first page
		if (ogg_sync_pageout(&oy, &og) != 1)
		{
			// No more data ?
			if (bytes < 4096)
			{
				break;
			}
				
			// Corrupted file
			SLogger::LogError("%s : Corrupted ogg file.", p_path);
			fclose(f_in);

			return false;
		}

		ogg_stream_init(&os, ogg_page_serialno(&og));

		vorbis_info_init(&vi);
		vorbis_comment_init(&vc);

		if (ogg_stream_pagein(&os, &og) < 0)
		{
			SLogger::LogError("%s : Error while reading the first page.", p_path);
			fclose(f_in);

			return false;
		}

		if (ogg_stream_packetout(&os, &op) != 1)
		{
			SLogger::LogError("%s : Error while reading the first page.", p_path);
			fclose(f_in);

			return false;
		}

		if (vorbis_synthesis_headerin(&vi, &vc, &op)<0)
		{
			SLogger::LogError("%s : Not an ogg header", p_path);
			fclose(f_in);

			return false;
		}

		i = 0;
		while (i < 2)
		{
			while (i < 2)
			{
				int result = ogg_sync_pageout(&oy, &og);
				if (result == 0)
				{
					// No more data
					break;
				}

				if (result == 1)
				{
					ogg_stream_pagein(&os, &og); 
					while (i < 2)
					{
						result = ogg_stream_packetout(&os, &op);
						if (result == 0)break;
						if (result < 0)
						{
							SLogger::LogError("%s : Corrupted header", p_path);
							fclose(f_in);

							return false;
						}
						result = vorbis_synthesis_headerin(&vi, &vc, &op);

						if (result<0)
						{
							SLogger::LogError("%s : Error while reading the ogg header", p_path);
							fclose(f_in);

							return false;
						}
						i++;
					}
				}
			}

			buffer = ogg_sync_buffer(&oy, 4096);
			bytes  = fread(buffer, 1, 4096, f_in);

			cumulative_read += bytes;
			if (bytes == 0 && i < 2)
			{
				SLogger::LogError("%s : Error , early eof", p_path);
				fclose(f_in);

				return false;
			}

			ogg_sync_wrote(&oy, bytes);
		}

		convsize = 4096 / vi.channels;

		if (vorbis_synthesis_init(&vd, &vi) == 0)
		{
			vorbis_block_init(&vd, &vb);

			// While !End of Stream
			while (!eos)
			{
				while (!eos)
				{
					int result = ogg_sync_pageout(&oy, &og);
					if (result == 0)
					{
						// No more data
						break;
					}

					if (result<0)
					{
						SLogger::LogError("%s : Corrupted data found", p_path);
						// Ignoring
					}
					else
					{
						ogg_stream_pagein(&os, &og);

						while (true)
						{
							result = ogg_stream_packetout(&os, &op);
							if (result == 0)
							{
								// No more data
								break;
							}

							if (result < 0)
							{
								// Ignore errors
							}
							else
							{
								// Decode packets
								float **pcm = nullptr;
								int samples = 0;

								if (vorbis_synthesis(&vb, &op) == 0)
									vorbis_synthesis_blockin(&vd, &vb);

								while ((samples = vorbis_synthesis_pcmout(&vd, &pcm)) > 0)
								{
									int j        = 0;
									int clipflag = 0;
									int bout = (samples < convsize ? samples : convsize);

									for (i = 0; i < vi.channels; i++)
									{
										ogg_int16_t *ptr = convbuffer + i;
										float *mono = pcm[i];
										for (j = 0; j < bout; j++)
										{
											int val = floor(mono[j] * 32767.f + .5f);

											if (val > 32767)
											{
												val      = 32767;
												clipflag = 1;
											}
											if (val < -32768)
											{
												val      = -32768;
												clipflag = 1;
											}

											*ptr = val;
											ptr += vi.channels;
										}
									}

									for (auto i = 0; i < vi.channels * bout; ++i)
										pcm_data.samples.push_back(convbuffer[i]);

									byteWritten += (bout * 2 * vi.channels);
									vorbis_synthesis_read(&vd, bout);
								}
							}
						}

						if (ogg_page_eos(&og))
						{
							eos = 1;
						}	
					}
				}

				if (!eos)
				{
					buffer = ogg_sync_buffer(&oy, 4096);
					bytes = fread(buffer, 1, 4096, f_in);

					cumulative_read += bytes;

					ogg_sync_wrote(&oy, bytes);
					if (bytes == 0)
						eos = 1;
				}
			}

			vorbis_block_clear(&vb);
			vorbis_dsp_clear  (&vd);

			// Seek back and write the WAV header
			pcm_data.wave_header = CWaveHeader(vi.rate, 16, vi.channels, byteWritten);
		}
		else
		{
			SLogger::LogError("%s : Corrupted header found during playback initialization.", p_path);
			fclose(f_in);

			return false;
		}

		ogg_stream_clear    (&os);
		vorbis_comment_clear(&vc);
		vorbis_info_clear   (&vi);
	}

	/* OK, clean up the framer */
	ogg_sync_clear(&oy);

	if (f_in != nullptr)
		fclose(f_in);

	return true;
}

/* static */ bool CAudioDecoder::DecodeWAV(const char* p_path, CPCMData& pcm_data)
{
	// Not implemented
	return true;
}

}
