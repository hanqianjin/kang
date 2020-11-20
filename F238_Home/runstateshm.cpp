/****************************************Copyright (c)****************************************************
**
**                     DaHao Info Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name: runstateshm.cpp
** Latest Version: V0.0.1
** Latest modified Date:  2018-12-17
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by: BitYang
** Created date: 2018-12-17
** Descriptions: init shm and sync between other modes
**
*********************************************************************************************************/
#include "runstateshm.h"
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>
#include <homesoftbus.h>

extern NOTICMSG homexcep;
/**
* @class RunStateShm
* @brief init shm and sync
*/
RunStateShm::RunStateShm():
  homeuihandle(0)
{
  IniSaShm();
}

qint32 RunStateShm::IniSaShm()
{
  //home and platform shm init
  void* temptr = NULL;
  shm_homenoti_id = shmget((key_t)HOME_SEM_DICTION,sizeof(HOME_NOTIC_CODE),IPC_CREAT | 0666);
  if  (-1 == shm_homenoti_id)
    {
      qCritical(strerror(errno));
      return errno;
    }
  else
    {
      temptr= shmat(shm_homenoti_id, (void*)0, 0);
      if (temptr == (void*)-1)
        {
          qCritical(strerror(errno));
          return errno;
        }
      pshm_homenotic = static_cast<PHOME_NOTIC_CODE>(temptr);
    }

  //home and platform shm init
  shm_home_id = shmget((key_t)HOME_SHM_KEY,sizeof(SHM_HOME),IPC_CREAT | 0777);
  if  (-1 == shm_home_id)
    {
      qCritical(strerror(errno));
      homexcep.npflag = 1;
      homexcep.ntype = 2;
      homexcep.index = 0;
      RunStateShm::getsingleshm()->pshm_homenotic->noticode = GetNoticeCode(&homexcep);
      return errno;
    }
  else
    {
      temptr= shmat(shm_home_id, (void*)0, 0);
      if (temptr == (void*)-1)
        {
          qCritical(strerror(errno));
          homexcep.npflag = 1;
          homexcep.ntype = 2;
          homexcep.index = 1;
          RunStateShm::getsingleshm()->pshm_homenotic->noticode = GetNoticeCode(&homexcep);
          return errno;
        }
      pshm_home = static_cast<PSHM_HOME>(temptr);
    }

  shm_sysinfo_id = shmget((key_t)SYS_INFO_KEY,sizeof(SHM_SYS_INFO),IPC_CREAT | 0666);
  if  (-1 == shm_sysinfo_id)
    {
      qCritical(strerror(errno));
      homexcep.npflag = 1;
      homexcep.ntype = 2;
      homexcep.index = 0;
      RunStateShm::getsingleshm()->pshm_homenotic->noticode = GetNoticeCode(&homexcep);
      return errno;
    }
  else
    {
      temptr= shmat(shm_sysinfo_id, (void*)0, 0);
      if (temptr == (void*)-1)
        {
          qCritical(strerror(errno));
          homexcep.npflag = 1;
          homexcep.ntype = 2;
          homexcep.index = 1;
          RunStateShm::getsingleshm()->pshm_homenotic->noticode = GetNoticeCode(&homexcep);
          return errno;
        }
      pshm_sysinfo = static_cast<PSHM_SYS_INFO>(temptr);
    }

  shm_sysaction_id = shmget((key_t)SYS_BURN_KEY,sizeof(SHM_SYS_ACTION),IPC_CREAT | 0666);
  if  (-1 == shm_sysaction_id)
    {
      qCritical(strerror(errno));
      homexcep.npflag = 1;
      homexcep.ntype = 2;
      homexcep.index = 0;
      RunStateShm::getsingleshm()->pshm_homenotic->noticode = GetNoticeCode(&homexcep);
      return errno;
    }
  else
    {
      temptr= shmat(shm_sysaction_id, (void*)0, 0);
      if (temptr == (void*)-1)
        {
          qCritical(strerror(errno));
          homexcep.npflag = 1;
          homexcep.ntype = 2;
          homexcep.index = 1;
          RunStateShm::getsingleshm()->pshm_homenotic->noticode = GetNoticeCode(&homexcep);
          return errno;
        }
      pshm_sysaction = static_cast<PSHM_SYS_ACTION>(temptr);
    }

  //====================
  //home and all modes
  homeuihandle = semget(HOME_UI_SHOW_KEY,1,IPC_CREAT | 0660);
  if(-1 == homeuihandle)
    {
      homexcep.npflag = 1;
      homexcep.ntype = 2;
      homexcep.index = 2;
      RunStateShm::getsingleshm()->pshm_homenotic->noticode = GetNoticeCode(&homexcep);
      return errno;
    }

  if(-1 == semctl(homeuihandle,0,SETVAL,0))
    {
      homexcep.npflag = 1;
      homexcep.ntype = 2;
      homexcep.index = 3;
      RunStateShm::getsingleshm()->pshm_homenotic->noticode = GetNoticeCode(&homexcep);
      return errno;
    }

  IniShmMem();
  return 0;
}

/**
 * @brief delete ori mode set
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-05-22}
*/
void RunStateShm::IniShmMem()
{
  pshm_home->remotecloseflag = POFF;  
  pshm_home->systype = POFF;
  pshm_home->modesource = POFF;
  pshm_homenotic->noticode = PTY0;
  return;
}

qint32 RunStateShm::GetSemp(qint32 semphandle)
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

qint32 RunStateShm::ReleaseSemp(qint32 semphandle)
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

RunStateShm* RunStateShm::pshm = new RunStateShm();
RunStateShm *RunStateShm::getsingleshm()
{
  return pshm;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @author steve
 * @since {2019-02-25}
*/
qint32 RunStateShm::PassTrigToSys(quint32 itopflag, quint32 itemflag)
{
  RunStateShm::getsingleshm()->pshm_sysaction->system_flag = itemflag;
  RunStateShm::getsingleshm()->pshm_sysaction->top_flag = itopflag;
  return 0;
}
