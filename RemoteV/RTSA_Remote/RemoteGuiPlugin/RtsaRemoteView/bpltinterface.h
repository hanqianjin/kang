#ifndef BPLTINTERFACE_H
#define BPLTINTERFACE_H
#include <QObject>
class BPltInterface
{
public:
  BPltInterface();

public:
  /**
 * @brief for plt to call to change ana mode mea item
 * @param[in]item:measure index same with plut widget
 * @param[in]
 * @return
*/
  virtual void SetMeasureItems(qint32 item) = 0;

  /**
 * @brief for plt to call to tell now running mode
 * @param[in]imode: SA_MODE 0, RTSA_MODE 1,INTERF_MODE 2,PM_MODE 3,LTE_FDD_MODE 4,FIVE_G_MODE 5
 * @param[in]
 * @return
*/
  virtual void PltCurAnaMode(qint32 imode) = 0;

  /**
 * @brief for plt to call to save now running mode and power state
 * @param[in]itype:default 0,last 1,user 2
 * @param[in]
 * @return error<0
*/
  virtual qint32 PltSavePres(qint32 itype) = 0;

  /**
 * @brief for plt to call to save ctrl states
 * @param[in]itype:default 0,last 1,user 2
 * @param[in]
 * @return error<0
*/
  virtual qint32 PltSaveConditions(qint32 itype) = 0;

  /**
 * @brief for plt to call to load states
 * @param[in]itype:default 0,last 1,user 2
 * @param[in]
 * @return error<0
*/
  virtual qint32 PltLoadConditions(qint32 itype) = 0;

  /**
 * @brief for plt to call to change ui state when other mode do lock action
 * @param[in]ilock:unlock 0,lock 1
 * @param[in]
 * @return
*/
  virtual void ChangeLcdStateWithNoSig(qint32 ilock) = 0;

  /**
 * @brief for plt to call to close ana pop widget
 * @param[in]
 * @param[in]
 * @return
*/
  virtual void MenuClose() = 0;

  /**
 * @brief for plt to call to tell ctrl mode
 * @param[in]imode:local 0, remote 1
 * @param[in]
 * @return
*/
  virtual void SetLocalRemoteMode(qint32 imode) = 0;

  /**
 * @brief for plt to call to preset factory states
 * @param[in]
 * @param[in]
 * @return
*/
  virtual void PresetDefaultStates() = 0;

  /**
 * @brief for plt to call to set display mode
 * @param[in]imode:indoor 0, outdoor 1 ,night 2
 * @param[in]
 * @return error<0
*/
  virtual void SetDisplayMode(qint32 imode) = 0;
  /**
 * @brief for plt to call to change other ana mode ui states when setting ref
 * @param[in]imode:Internal 0, External 10 MHz 1 ,External 13 MHz 2,External 15 MHz 3,GPS 4
 * @param[in]
 * @return error<0
*/
  virtual void SetSysRefuiStates(qint32 itype) = 0;


};

#endif // BPLTINTERFACE_H
