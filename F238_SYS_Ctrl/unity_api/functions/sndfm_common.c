#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <alsa/asoundlib.h>
#include "sndfm_common.h"

ssize_t SNDFM_Read(int fd, void *buf, size_t count)
{
    ssize_t result = 0, res;
 
    while (count > 0) {
        if ((res = read(fd, buf, count)) == 0)
            break;
        if (res < 0)
            return result > 0 ? result : res;
        count -= res;
        result += res;
        buf = (char *)buf + res;
    }   
    return result;
}


int SNDFM_SetParams(SNDPCMContainer_t *sndpcm, snd_pcm_format_t format, uint32_t channels,uint32_t sample_rate)
{
    snd_pcm_hw_params_t *hwparams;
    uint32_t exact_rate;
    uint32_t buffer_time, period_time;

    /* Allocate the snd_pcm_hw_params_t structure on the stack. */
    snd_pcm_hw_params_alloca(&hwparams);

    /* Init hwparams with full configuration space */
    if (snd_pcm_hw_params_any(sndpcm->handle, hwparams) < 0) {
        fprintf(stderr, "Error snd_pcm_hw_params_any\n");
        goto ERR_SET_PARAMS;
    }

    if (snd_pcm_hw_params_set_access(sndpcm->handle, hwparams, SND_PCM_ACCESS_RW_INTERLEAVED) < 0) {
        fprintf(stderr, "Error snd_pcm_hw_params_set_access\n");
        goto ERR_SET_PARAMS;
    }

    /* Set sample format */
    if (snd_pcm_hw_params_set_format(sndpcm->handle, hwparams, format) < 0) {
        fprintf(stderr, "Error snd_pcm_hw_params_set_format\n");
        goto ERR_SET_PARAMS;
    }
    sndpcm->format = format;

    /* Set number of channels */
    if (snd_pcm_hw_params_set_channels(sndpcm->handle, hwparams, LE_SHORT(channels)) < 0) {
        fprintf(stderr, "Error snd_pcm_hw_params_set_channels\n");
        goto ERR_SET_PARAMS;
    }
    sndpcm->channels = LE_SHORT(channels);

    /* Set sample rate. If the exact rate is not supported */
    /* by the hardware, use nearest possible rate.         */
    exact_rate = LE_INT(sample_rate);
    if (snd_pcm_hw_params_set_rate_near(sndpcm->handle, hwparams, &exact_rate, 0) < 0) {
        fprintf(stderr, "Error snd_pcm_hw_params_set_rate_near\n");
        goto ERR_SET_PARAMS;
    }
    if (LE_INT(sample_rate) != exact_rate) {
        fprintf(stderr, "The rate %d Hz is not supported by your hardware.\n ==> Using %d Hz instead.\n",
            LE_INT(sample_rate), exact_rate);
    }
    if (snd_pcm_hw_params_get_buffer_time_max(hwparams, &buffer_time, 0) < 0) {
        fprintf(stderr, "Error snd_pcm_hw_params_get_buffer_time_max\n");
        goto ERR_SET_PARAMS;
    }
    if (buffer_time > 500000) buffer_time = 500000;
    period_time = buffer_time / 4;

    if (snd_pcm_hw_params_set_buffer_time_near(sndpcm->handle, hwparams, &buffer_time, 0) < 0) {
        fprintf(stderr, "Error snd_pcm_hw_params_set_buffer_time_near\n");
        goto ERR_SET_PARAMS;
    }
    if (snd_pcm_hw_params_set_period_time_near(sndpcm->handle, hwparams, &period_time, 0) < 0) {
        fprintf(stderr, "Error snd_pcm_hw_params_set_period_time_near\n");
        goto ERR_SET_PARAMS;
    }

    /* Set hw params */
    if (snd_pcm_hw_params(sndpcm->handle, hwparams) < 0) {
        fprintf(stderr, "Error snd_pcm_hw_params(handle, params)\n");
        goto ERR_SET_PARAMS;
    }

    snd_pcm_hw_params_get_period_size(hwparams, &sndpcm->chunk_size, 0);
    snd_pcm_hw_params_get_buffer_size(hwparams, &sndpcm->buffer_size);
    if (sndpcm->chunk_size == sndpcm->buffer_size) {
        fprintf(stderr, ("Can't use period equal to buffer size (%lu == %lu)\n"), sndpcm->chunk_size, sndpcm->buffer_size);
        goto ERR_SET_PARAMS;
    }

    sndpcm->bits_per_sample = snd_pcm_format_physical_width(format);
    sndpcm->bits_per_frame = sndpcm->bits_per_sample * LE_SHORT(channels);

    sndpcm->chunk_bytes = sndpcm->chunk_size * sndpcm->bits_per_frame / 8;

    /* Allocate audio data buffer */
    sndpcm->data_buf = (uint8_t *)malloc(sndpcm->chunk_bytes);
    if (!sndpcm->data_buf) {
        fprintf(stderr, "Error malloc: [data_buf]\n");
        goto ERR_SET_PARAMS;
    }

    return 0;

ERR_SET_PARAMS:
    return -1;
}

