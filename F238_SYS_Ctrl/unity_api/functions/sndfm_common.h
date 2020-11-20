#include "sndwav_common.h"

#ifndef __SNDFM_COMMON_H
#define __SNDFM_COMMON_H


ssize_t SNDFM_Read(int fd, void *buf, size_t count);
int SNDFM_SetParams(SNDPCMContainer_t *sndpcm, snd_pcm_format_t format, uint32_t channels,uint32_t sample_rate);

#endif
