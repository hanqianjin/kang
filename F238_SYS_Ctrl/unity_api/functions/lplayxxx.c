/*****************************************************************************
Copyright:    2018-2010,  Tech. Co., Ltd.
File name:    lplay.c
Description:  audio play file
Author:       brook.lv
Version:      v1.01
Date:         2018.6.12
History:    

*****************************************************************************/
 
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <locale.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <alsa/asoundlib.h>
#include <assert.h>
#include <pthread.h>
#include "wav_parser.h"
#include "sndwav_common.h"
#include "sndfm_common.h"

static SNDPCMContainer_t playback;
static pthread_t play_thread;
static pthread_mutex_t g_mutex;
static pthread_cond_t thread_cond = PTHREAD_COND_INITIALIZER;

enum SND_STATUS {
	SND_STOP,
	SND_WAV,
	SND_FM,
	SND_PAUSE,
};
static enum SND_STATUS snd_status = SND_PAUSE; 

struct snd_file_info_t {
	enum SND_STATUS type;
	int             fd;
	uint32_t        size;
};

static struct snd_file_info_t snd_file_info;


static ssize_t snd_getdata(int fd, void *buf, size_t count)
{
	ssize_t ret = -1;;

	if (snd_status == SND_WAV) {
		ret = SNDWAV_P_SaveRead(fd, buf, count);
	}
	else if (snd_status == SND_FM) {
		ret = SNDFM_Read(fd, buf, count);
	}
	return ret;
}
 
static void snd_play(SNDPCMContainer_t *sndpcm, int fd, uint32_t length, enum SND_STATUS status)
{
    int load, ret;
    off64_t written = 0;
    off64_t c;
    off64_t count = 0;

	if (length > 0) {
		count = LE_INT(length);
	}
    load = 0;
    while (written < count) {
        /* Must read [chunk_bytes] bytes data enough. */
        do {
            c = count - written;
            if (c > sndpcm->chunk_bytes)
                c = sndpcm->chunk_bytes;
            c -= load;

            if (c == 0)
                break;
			if (snd_status == SND_PAUSE)
				break;			

            ret = snd_getdata(fd, sndpcm->data_buf + load, c);
            if (ret < 0) {
                fprintf(stderr, "Error safe_read\n");
                //exit(-1);
				break;
            }
            if (ret == 0)
                break;
            load += ret;
        } while ((size_t)load < sndpcm->chunk_bytes);
		//printf("thread snd_status=%d\n", snd_status);
		if (snd_status == SND_PAUSE)
			break;			
        /* Transfer to size frame */
        load = load * 8 / sndpcm->bits_per_frame;
        ret = SNDWAV_WritePcm(sndpcm, load);
        if (ret != load)
            break;

        ret = ret * sndpcm->bits_per_frame / 8;
        written += ret;
        load = 0;
    }
	
	//wav file over play
	if(snd_status == SND_WAV){
		snd_status = SND_PAUSE;
		if (snd_file_info.fd > 0) {
			close(snd_file_info.fd);
			snd_file_info.fd = -1;
		}
	}
}

/*************************************************
Function:       stopSnd
Description:    stop playing 
Calls:          
Called By:      extern
Input:          null
Output:         null
Return:         DI_SUCCESS   --success
                less than 0  --err
Others:         NULL
*************************************************/
int stopSnd(void)
{
	if (snd_status == SND_WAV){
		pthread_mutex_lock(&g_mutex);
		snd_status = SND_PAUSE;
		pthread_mutex_unlock(&g_mutex);
		if (snd_file_info.fd > 0) {
			close(snd_file_info.fd);
			snd_file_info.fd = -1;
		}
	}
	if (snd_status == SND_FM){
		pthread_mutex_lock(&g_mutex);
		snd_status = SND_PAUSE;
		pthread_mutex_unlock(&g_mutex);
	}
	snd_pcm_drain(playback.handle);
	if (playback.data_buf != NULL) {
		free(playback.data_buf);
		playback.data_buf = NULL;
	}
	return 0;
}

/*************************************************
Function:       playWav
Description:    play wav file 
Calls:          
Called By:      extern
Input:          wavfile      --wav file name
Output:         
Return:         DI_SUCCESS   --success
                less than 0  --err
Others:         NULL
*************************************************/
int playWav(char *wavfile)
{
    int fd; 
    WAVContainer_t wav;

	if (snd_status==SND_WAV) {
		printf("You are playing....\n");
		return -1;
	}
	if (snd_status==SND_FM) {
		printf("You are playing FM\n");
		stopSnd();
	}
	if(wavfile == NULL) {
		fprintf(stderr, "No wav file input\n");
	}
    fd = open(wavfile, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Error open [%s]\n", wavfile);
        return -1; 
    }
        
    if (WAV_ReadHeader(fd, &wav) < 0) {
        fprintf(stderr, "Error WAV_Parse [%s]\n", wavfile);
        goto Err;
    }
 
 
    if (SNDWAV_SetParams(&playback, &wav) < 0) {
        fprintf(stderr, "Error set_snd_pcm_params\n");
        goto Err;
    }
    snd_pcm_dump(playback.handle, playback.log);

	snd_file_info.type = SND_WAV;
	snd_file_info.fd = fd;
	snd_file_info.size = wav.chunk.length;

    pthread_mutex_lock(&g_mutex);
    snd_status = SND_WAV;
    pthread_cond_signal(&thread_cond);
    pthread_mutex_unlock(&g_mutex); 
    //snd_pcm_drain(playback.handle);
 
//    close(fd);
//    free(playback.data_buf);
//    snd_output_close(playback.log);
//    snd_pcm_close(playback.handle);
    return 0;
 
Err:
    close(fd);
    if (playback.data_buf) free(playback.data_buf);
    if (playback.log) snd_output_close(playback.log);
    return -1; 
}


/*************************************************
Function:       playFM
Description:    play FM 
Calls:          
Called By:      extern
Input:          null
Output:         null
Return:         DI_SUCCESS   --success
                less than 0  --err
Others:         NULL
*************************************************/
int playFM(void)
{
    int fd; 
    WAVContainer_t wav;

	if (snd_status==SND_FM) {
		printf("You are playing....\n");
		return -1;
	}
	if (snd_status==SND_WAV) {
		printf("You are playing WAV\n");
		stopSnd();
	}
    fd = open("music.wav", O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Error open file\n");
        return -1; 
    }
        
    if (WAV_ReadHeader(fd, &wav) < 0) {
        fprintf(stderr, "Error WAV_Parse wav\n");
    }
 
	SNDFM_SetParams(&playback, SND_PCM_FORMAT_S16_LE, 2, 44100);
   // if (SNDWAV_SetParams(&playback, &wav) < 0) {
   //     fprintf(stderr, "Error set_snd_pcm_params\n");
   //     goto Err;
   // }
    snd_pcm_dump(playback.handle, playback.log);

	snd_file_info.type = SND_FM;
	snd_file_info.fd = fd;
	snd_file_info.size = 59559696;
    
	pthread_mutex_lock(&g_mutex);
    snd_status = SND_FM;
    pthread_cond_signal(&thread_cond);
    pthread_mutex_unlock(&g_mutex); 

	return 0; 
}


void *play_thread_fun(void *arg)
{
	while(snd_status != SND_STOP) {
	printf("in play_thread_fun snd_status=%d\n", snd_status);
		if ((snd_status == SND_WAV) || (snd_status == SND_FM))
			snd_play(&playback, snd_file_info.fd, snd_file_info.size, snd_status);
		pthread_mutex_lock(&g_mutex);
		while (snd_status == SND_PAUSE)
		{
			pthread_cond_wait(&thread_cond, &g_mutex);
		}
		pthread_mutex_unlock(&g_mutex);
	}
	return NULL;
}

/*************************************************
Function:       setVolume
Description:    set volume 
Calls:          
Called By:      extern
Input:          volumeNum    --volume between 1-100
Output:         
Return:         DI_SUCCESS   --success
                less than 0  --err
Others:         NULL
*************************************************/
int setVolume(int volumeNum)
{
	int volume = volumeNum;
	
	if(volume < 0)
	volume = 0;
	if(volume > 100)
	volume = 100;

    int unmute, chn;
   // long al, ar;
    snd_mixer_t *mixer;
    snd_mixer_elem_t *master_element;
 
    snd_mixer_open(&mixer, 0);
    snd_mixer_attach(mixer, "default");
    snd_mixer_selem_register(mixer, NULL, NULL);
    snd_mixer_load(mixer);  
    master_element = snd_mixer_first_elem(mixer);  
    snd_mixer_selem_set_playback_volume_range(master_element, 0, 100);  
    snd_mixer_selem_get_playback_switch(master_element, 0, &unmute);
 
    snd_mixer_selem_set_playback_volume(master_element, SND_MIXER_SCHN_FRONT_LEFT, volume);
    snd_mixer_selem_set_playback_volume(master_element, SND_MIXER_SCHN_FRONT_RIGHT, volume);  
    for (chn=0;chn<=SND_MIXER_SCHN_LAST;chn++) {
      snd_mixer_selem_set_playback_switch(master_element, chn, 0);
    } 
    for (chn=0;chn<=SND_MIXER_SCHN_LAST;chn++) {
      snd_mixer_selem_set_playback_switch(master_element, chn, 1);
    }
	snd_mixer_free(mixer);
	snd_mixer_detach(mixer, "default");
	snd_mixer_close(mixer);
	return 0;
}

/*************************************************
Function:       openPcm
Description:    open sound card 
Calls:          
Called By:      extern
Input:          null
Output:         handle       --the handle of the device (here just virtual)
Return:         DI_SUCCESS   --success
                less than 0  --err
Others:         NULL
*************************************************/
int openPcm(int * handle)
{
    char *devicename = "default";
	
	//creat play thread
	if ( pthread_create( &play_thread, NULL, play_thread_fun, NULL) ) {
		printf("error creating thread.\n");
		goto Err;
	}

    memset(&playback, 0x0, sizeof(playback));
    if (snd_output_stdio_attach(&playback.log, stdout, 0) < 0) {
        fprintf(stderr, "Error snd_output_stdio_attach\n");
        goto Err;
    }
 
    if (snd_pcm_open(&playback.handle, devicename, SND_PCM_STREAM_PLAYBACK, 0) < 0) {
        fprintf(stderr, "Error snd_pcm_open [ %s]\n", devicename);
        goto Err;
    }
	*handle = 1;//assume PCM is the std fd
	return 0;

Err:
    if (playback.handle)
		snd_pcm_close(playback.handle);
	return -1;
}
 
/*************************************************
Function:       closePcm
Description:    close sound card 
Calls:          
Called By:      extern
Input:          handle      --the handle of the device (here just virtual)
Output:         null
Return:         DI_SUCCESS   --success
                less than 0  --err
Others:         NULL
*************************************************/
int closePcm(int handle)
{
	if(snd_status != SND_PAUSE) {
		stopSnd();
	}
    pthread_mutex_lock(&g_mutex);
	snd_status = SND_STOP;
    pthread_cond_signal(&thread_cond);
    pthread_mutex_unlock(&g_mutex); 
	if (pthread_join(play_thread, NULL )) {
		printf("error join thread.");
    	abort();
	}

    snd_output_close(playback.log);
    snd_pcm_close(playback.handle);
printf("---closePcm\n");
	return 0;
}
/*
static dev_fun_opt* snd_fun;

void init_snd(void)
{
    snd_fun = (dev_fun_opt* )malloc(sizeof(struct dev_fun_opt));
    
    snd_fun->bus_name   = "VIRTUAL";
    snd_fun->dev_num    = 1;
    snd_fun->dev_type   = "DEVICE";
    snd_fun->open = openPcm;
    snd_fun->close= closePcm;

    register_dev_fun(snd_fun);
}

void exit_snd(void)
{
    unregister_dev_fun(snd_fun);
    free(snd_fun);
} */
