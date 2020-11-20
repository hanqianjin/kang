#ifndef __LPLAY_H
#define __LPLAY_H

int openPcm(int *handle);
int playWav(char *wavfile);
int playFM(void);
int stopSnd(void);
int setVolume(int value);
int closePcm(int handle);

#endif

