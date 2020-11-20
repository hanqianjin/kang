#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <strings.h>
#include <string.h>
#include <signal.h>
#include "LinkList.h"
#include "wireless.h"

static HEAD_LISTNODE scan_list;

char* shellcmd(char* cmd, char* buff, int size)
{
	char temp[256];
	FILE* fp = NULL;
	int offset = 0;
	int len;

    //printf("cmd=%s;\n", cmd);
	fp = popen(cmd, "r");
	if(fp == NULL)
	{
		return NULL;
	}

	while(fgets(temp, sizeof(temp), fp) != NULL)
	{
		len = strlen(temp);
		if(offset + len < size)
		{
			strcpy(buff+offset, temp);
			offset += len;
		}
		else
		{
			buff[offset] = 0;
			break;
		}
	}

    //printf("buff=%s;\n", buff);
	if(fp != NULL)
	{
		pclose(fp);
	}

	return buff;
}

int wireless_open()
{
	system("rm /etc/udev/rules.d/70-persistent-net.rules\n");
	system("echo 2 > /sys/devices/soc0/amba/amba:wifi_bt/wifi_bt/wifi_bt_flag\n");
    //usleep(1000000);
    usleep(500000);
	system("ifconfig wlan0 up");
	usleep(10000);
    return 0;
}

int wireless_close()
{
    system("pkill -9 hostap\n");
    system("pkill -9 udhcpd\n");
    system("wpa_cli -i wlan0 terminate\n");
	system("ifconfig wlan0 down");
	usleep(10000);
	system("echo 0 > /sys/devices/soc0/amba/amba:wifi_bt/wifi_bt/wifi_bt_flag\n");
    return 0;
}

int wireless_status(StaStatus *status)
{
	char buf[1024] = {0};
	char key[128] = {0};
	char value[128] = {0};
	char *temp_result1;
	char *saveptr1;
	
	shellcmd("wpa_cli -i wlan0 status", buf, sizeof(buf));
	//printf("%s", buf);

	temp_result1 = strtok_r(buf, "\n", &saveptr1);
    while(temp_result1 != NULL)
	{
		sscanf(temp_result1, "%[^=]=%s", key, value);
		//printf("key:%s  val:%s \n", key, value);
		if(!strcmp(key, "wpa_state")) {
            //printf("now status is %s\n", value);
			if (!strcmp(value, "COMPLETED"))
			{
				*status = STACONNECTED;
			}
			else if (!strcmp(value, "SCANNING"))
			{
				*status = STASCANNING;
			}
			else if (!strcmp(value, "ASSOCIATING"))
			{
				*status = STACONNECTING;
			}
			else if (!strcmp(value, "INACTIVE"))
			{
				*status = STADISCONNECTED;
			}
			else if (!strcmp(value, "4WAY_HANDSHAKE"))
			{
				*status = STADISCONNECTED;
			}
			else if (!strcmp(value, "DISCONNECTED"))
			{
				*status = STADISCONNECTED;
			}
		}
		temp_result1 = strtok_r(NULL, "\n", &saveptr1);
	}
    return 0;
}

//***sta*****
int wireless_set_sta()
{
	system("pkill -9 hostap\n");
	system("pkill -9 udhcpd\n");
    system("wpa_supplicant -Dwext -iwlan0 -c /etc/wireless/wpa_supplicant.conf -B\n"); //USB wifi
    //system("wpa_supplicant -Dnl80211 -iwlan0 -c/etc/wireless/wpa_supplicant.conf -B\n");
	usleep(2000);
    return 0;
}

static int free_ap_list(void * data) {
	free(data);
	return 0;
}

int wireless_scan(int(*deal_scan)(void *scan_data))
{
	char buf[1024] = {0};
    int j, k;
    char *p;
	char *temp_result2, *temp_result1;
	char *saveptr1, *saveptr2;
	SSIDInfo *temp_info;
    char ssid_temp[256] = {0};

	system("wpa_cli -i wlan0 scan\n");
    usleep(5000000);
//    usleep(1000000);
	shellcmd("wpa_cli -i wlan0 scan_result", buf, sizeof(buf));
//	printf("%s", buf);

	list_clear(&scan_list, free_ap_list);

	temp_result1 = strtok_r(buf, "\n", &saveptr1);
	for (j = 0;; j++) {
		temp_result1 = strtok_r(NULL, "\n", &saveptr1);
		if(temp_result1 == NULL)
			break;

		temp_info = (SSIDInfo*)malloc(sizeof(SSIDInfo));

		temp_result2 = strtok_r(temp_result1, "\t", &saveptr2);
		if(temp_result2 != NULL) {
			strcpy(temp_info->bssid, temp_result2);
		}
			
		temp_result2 = strtok_r(NULL, "\t", &saveptr2);
		if(temp_result2 != NULL) {
			temp_info->frequency = atoi(temp_result2);
		}
		temp_result2 = strtok_r(NULL, "\t", &saveptr2);
		if(temp_result2 != NULL) {
			temp_info->signal_level = atoi(temp_result2);
		}
		temp_result2 = strtok_r(NULL, "\t", &saveptr2);
		if(temp_result2 != NULL) {
			strcpy(temp_info->flags, temp_result2);
		}
		temp_result2 = strtok_r(NULL, "\t", &saveptr2);
		if(temp_result2 != NULL) {
            strcpy(ssid_temp, temp_result2);
		}
		else {
            strcpy(ssid_temp, "*");
		}

        //deal chinese  ssid name
        p = ssid_temp;
        k = 0;
        while(*p){
            if ((*p == '\\') && (*(++p) == 'x'))
            {
                char a = *(++p);
                char b = *(++p);
                p++;
                if(a >= 'a') {
                    a = a - 'a' + 10;
                }
                else{
                    a = a - '0';
                }
                if(b >= 'a') {
                    b = b - 'a' + 10;
                }
                else{
                    b = b - '0';
                }

                a = a * 16 + b;
                temp_info->ssid[k] = a;
                printf("--%x ", a);
                k++;

            }
            else
            {
                temp_info->ssid[k] = *p++;
                k++;
            }
        }
        temp_info->ssid[k] = 0;

		list_insert(&scan_list, (void *)temp_info);
	}
    list_print(&scan_list, deal_scan);
    return 0;
}

int wireless_connect(int *net_id, char *ssid, char *passwd)
{
	char buf[128];
	char buf_ret[128];
	int net_num;

    printf("ssid=%s; passwd=%s\n", ssid, passwd);
    shellcmd("wpa_cli -i wlan0 add_network\n", buf_ret, sizeof(buf_ret));
	net_num = atoi(buf_ret);

    sprintf(buf, "wpa_cli -i wlan0 set_network %d ssid '\"%s\"'\n", net_num, ssid);
	shellcmd(buf, buf_ret, sizeof(buf_ret));
	if (strncmp(buf_ret, "OK", strlen("OK"))) {
		printf("add_network err:%s", buf_ret);
		return -1;
	}

	usleep(1000);
	if(passwd == NULL) {
		sprintf(buf, "wpa_cli -i wlan0 set_network %d key_mgmt NONE\n", net_num);
	}
	else {
        sprintf(buf, "wpa_cli -i wlan0 set_network %d psk '\"%s\"'\n", net_num, passwd);
    }
	shellcmd(buf, buf_ret, sizeof(buf_ret));
	if (strncmp(buf_ret, "OK", strlen("OK"))) {
		printf("set_network err:%s", buf_ret);
		return -1;
	}

	usleep(1000);
    sprintf(buf, "wpa_cli -i wlan0 enable_network %d\n", net_num);
	shellcmd(buf, buf_ret, sizeof(buf_ret));
	if (strncmp(buf_ret, "OK", strlen("OK"))) {
		printf("enable_network err:%s", buf_ret);
		return -1;
	}
	*net_id = net_num;
    return 0;
}

int wireless_disconnect(int net_id)
{
	char buf[128] = {0};
	char buf_ret[128] = {0};

	sprintf(buf, "wpa_cli -i wlan0 remove_network %d\n", net_id);
	shellcmd(buf, buf_ret, sizeof(buf_ret));
	if (strncmp(buf_ret, "OK", strlen("OK"))) {
		printf("remove_network err:%s", buf_ret);
		return -1;
	}
    return 0;
}

int wireless_auto_dhcp()
{
    system("udhcpc -i wlan0 &\n");
    return 0;
}

//***ap*****
#define MAX_LIINE 512
int wireless_set_ap(char *ssid, char *passwd, APAuth auth)
{
    FILE * fd_new;
    char buf1[MAX_LIINE] = {0};
    char buf2[MAX_LIINE] = {0};

	system("wpa_cli -i wlan0 terminate\n");
    system("pkill -9 hostapd\n");

    //printf("ssid=%s;passwd=%s", ssid, passwd);
    if (ssid == NULL)
       return -1;
    if (auth != AUTH_OPEN)
        if(strlen(passwd) < 8 || strlen(passwd) > 63)
        {
            printf("size of passwd must butween 8...63\n");
            return -1;
        }
    fd_new = fopen("/etc/hostapd_new.conf", "w");
    if(fd_new == NULL)
    {
        printf("cannot open file:hostapd_new.conf\n");
        return -1;
    }

    sprintf(buf1, "interface=wlan0\ndriver=nl80211\n"
                  "ctrl_interface=/var/run/hostapd\n"
                  "device_name=RTL8192CU\nmanufacturer=Realtek\nmodel_name=RTW_SOFTAP\nmodel_number=WLAN_CU\n"
                  "ssid=%s\nchannel=6\nieee80211n=1\nbeacon_int=100\nhw_mode=g\nwme_enabled=1\n"
                  "ht_capab=[SHORT-GI-20][SHORT-GI-40][HT40-]\n", ssid);

    switch (auth) {
        case AUTH_OPEN:
            sprintf(buf2, "%s", buf1);
            break;
        case AUTH_WPA:
            sprintf(buf2,"%swpa=1\nwpa_pairwise=TKIP CCMP\nwpa_passphrase=%s\n", buf1, passwd);
            break;
        case AUTH_WPA2:
            sprintf(buf2,"%swpa=2\nwpa_pairwise=CCMP\nwpa_passphrase=%s\n",buf1, passwd);
            break;
        default:
            printf("err for auth\n");
            break;
    }

    fwrite(buf2, strlen(buf2),1,fd_new);

    fclose(fd_new);

    system("hostapd -B /etc/hostapd_new.conf\n");
    //system("udhcpd -f /etc/udhcpd.conf\n");
    return 0;
}

int wireless_dhcpd(char* start_ip, char* end_ip)
{
    FILE * fd, *fd_new;
    char buf[MAX_LIINE];

    if (start_ip != NULL && end_ip != NULL)
    {
        fd = fopen("/etc/udhcpd.conf", "r");
        fd_new = fopen("/etc/udhcpd_new.conf", "w");
        while(fgets(buf, MAX_LIINE, fd))
        {
            if (!strncmp(buf, "start", strlen("start")))
            {
                sprintf(buf, "start \t%s\n", start_ip);
            }
            else if (!strncmp(buf, "end", strlen("end")))
            {
                sprintf(buf, "end \t%s\n", end_ip);
            }
            fwrite(buf, strlen(buf), 1, fd_new);
        }
        fclose(fd);
        fclose(fd_new);
    }
    system("mv /etc/udhcpd_new.conf /etc/udhcpd.conf");
    system("udhcpd -f /etc/udhcpd.conf &\n");
    return 0;
}

