#ifndef __WIRELESS_H__
#define __WIRELESS_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _tSSIDInfo
{
	char bssid[25];
	int  frequency;
	int  signal_level;
    char flags[100];
	char ssid[100];
}SSIDInfo;

typedef enum _eStaStatus
{
	STACONNECTED,
	STADISCONNECTED,
	STASCANNING,
	STACONNECTING
}StaStatus;

typedef enum _eAPAuth
{
    AUTH_OPEN,
    AUTH_WPA,
    AUTH_WPA2
}APAuth;

char* shellcmd(char* cmd, char* buff, int size);
int wireless_open();
int wireless_close();
int wireless_status(StaStatus *status);
int wireless_set_sta();
int wireless_scan(int(*deal_scan)(void *scan_data));
int wireless_connect(int *net_id, char *ssid, char *passwd);
int wireless_disconnect(int net_id);
int wireless_auto_dhcp();

int wireless_set_ap(char *ssid, char *passwd, APAuth auth);
int wireless_dhcpd(char* start_ip, char* end_ip);

#ifdef __cplusplus
}   
#endif

#endif  /* ndef __WIRELESS_H__ */

