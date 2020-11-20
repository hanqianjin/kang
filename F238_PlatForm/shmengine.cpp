/****************************************Copyright (c)****************************************************
**
**                     DaHao Info Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:shmengine.cpp
** Latest Version: V0.0.1
** Latest modified Date:  2018-12-13
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by: BitYang
** Created date: 2018-12-13
** Descriptions:shm between platform and multi analysis modes when mode switching for syn ctrl
**
*********************************************************************************************************/
#include "shmengine.h"
#include "sys/sem.h"
#include "sys/shm.h"
#include "softbus.h"
#include <qdebug.h>
#include <errno.h>

/**
* @class shmengine
* @brief when define the shmengine obj,the shm process has done;
*/
shmengine::shmengine()
{  
  if(inishmengine() < 0)
    {
      qCritical(strerror(errno));
    }
  addallctrlexit();
}

qint32 shmengine::GetSempC(qint32 semphandle)
{
  struct sembuf s;
  s.sem_num=0;
  s.sem_op=-1;
  s.sem_flg=0;
  if(-1 == semop(semphandle,&s,1))
    {
      return errno;
    }
  return 0;
}

qint32 shmengine::ReleaseSempC(qint32 semphandle)
{
  struct sembuf s;
  s.sem_num=0;
  s.sem_op=1;
  s.sem_flg=0;
  if(-1 == semop(semphandle,&s,1))
    {
      return errno;
    }
  return 0;
}

/**
 * @brief init all shm in obj structor
 * @return under zero means error
 * @note
 * @author steve
 * @since {2018-12-14}
*/
qint32 shmengine::inishmengine()
{
  void* temptr = 0;
  //platform and sys shm init
  shm_sysconf_id = shmget((key_t)SYS_CONF_KEY,sizeof(SHM_SYS_CONF),IPC_CREAT | 0777);
  if  (-1 == shm_sysconf_id)
    {
      qCritical(strerror(errno));
      return errno;
    }
  else
    {
      temptr= shmat(shm_sysconf_id, (void*)0, 0);
      if (temptr == (void*)-1)
        {
          qCritical(strerror(errno));
          return errno;
        }
      pshm_sysconf = static_cast<PSHM_SYS_CONF>(temptr);
    }
  shm_sysinfo_id = shmget((key_t)SYS_INFO_KEY,sizeof(SHM_SYS_INFO),IPC_CREAT | 0777);
  if  (-1 == shm_sysinfo_id)
    {
      qCritical(strerror(errno));
      return errno;
    }
  else
    {
      temptr= shmat(shm_sysinfo_id, (void*)0, 0);
      if (temptr == (void*)-1)
        {
          qCritical(strerror(errno));
          return errno;
        }
      pshm_sysinfo = static_cast<PSHM_SYS_INFO>(temptr);
    }

  //platform and sa shm init
  shm_sa_id = shmget((key_t)SA_SHM_KEY,sizeof(SHM_SA),IPC_CREAT | 0777);
  if  (-1 == shm_sa_id)
    {
      qCritical(strerror(errno));
      return errno;
    }
  else
    {
      temptr= shmat(shm_sa_id, (void*)0, 0);
      if (temptr == (void*)-1)
        {
          qCritical(strerror(errno));
          return errno;
        }
      pshm_sa = static_cast<PSHM_SA>(temptr);
    }

  //platform and rtsa shm init
  shm_rtsa_id = shmget((key_t)RTSA_SHM_KEY,sizeof(SHM_RTSA),IPC_CREAT | 0777);
  if  (-1 == shm_rtsa_id)
    {
      qCritical(strerror(errno));
      return errno;
    }
  else
    {
      temptr= shmat(shm_rtsa_id, (void*)0, 0);
      if (temptr == (void*)-1)
        {
          qCritical(strerror(errno));
          return errno;
        }
      pshm_rtsa = static_cast<PSHM_RTSA>(temptr);
    }

  //platform and home shm init
  shm_home_id = shmget((key_t)HOME_SHM_KEY,sizeof(SHM_HOME),IPC_CREAT | 0777);
  if  (-1 == shm_home_id)
    {
      qCritical(strerror(errno));
      return errno;
    }
  else
    {
      temptr= shmat(shm_home_id, (void*)0, 0);
      if (temptr == (void*)-1)
        {
          qCritical(strerror(errno));
          return errno;
        }
      pshm_home = static_cast<PSHM_HOME>(temptr);
    }

  inishmembers();
  return 0;
}

/**
 * @brief init shm variables after inishmengine
 * @note be called by inishmengine
 * @author steve
 * @since {2018-12-14}
*/
void shmengine::inishmembers()
{
  pshm_sa->appexit = BRUN;
  pshm_rtsa->appexit = BRUN;
  pshm_home->modetype = SA_MODE;
  pshm_home->modesource = POFF;
  return;
}

/**
 * @brief must in RUNMODE order
 * @note [pctrlexitvec will be extended when add a new mode]
 * @author steve
 * @since {2018-12-14}
*/
void shmengine::addallctrlexit()
{
  pctrlexitvec.append(&pshm_sa->appexit);
  pctrlexitvec.append(&pshm_rtsa->appexit);
  return;
}

shmengine* shmengine::shmobj = new shmengine();
/**
 * @brief single design mode
 * @return  pointer shmengine
 * @note
 * @author steve
 * @since {2018-12-17}
*/
shmengine *shmengine::getsingleshm()
{
  return shmobj;
}
