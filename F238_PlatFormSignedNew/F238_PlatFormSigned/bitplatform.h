#ifndef BITPLATFORM_H
#define BITPLATFORM_H

#include <QMainWindow>
#include "loadctrlrunparam.h"
#include "bitsa.h"
#include "bitrtsa.h"
#include <QProcess>
#include <QFile>
#include "plusmode.h"
#include "softbus.h"
#include "setwid.h"
#include "switmod.h"
#include "QLabel"
#include "bitltefdd.h"
#include "bitltetdd.h"
#include "bitnr.h"
#include "bpltinterface.h"
#include "pltcirlist.h"
#include "noticmsg.h"
//#include <QCursor>

namespace Ui {
  class BitPlatForm;
}

class BitPlatForm : public QMainWindow
{
  Q_OBJECT

public:
  explicit BitPlatForm(QWidget *parent = 0);
  ~BitPlatForm();
  QVector<const QByteArray*>noticexcepicvec;
private:
  void PltToMainExit();
  qint32 lcf;
  qint32 ncf;
  qint32 lncf;
  qint32 nncf;
  PLTPRESTATE pltsystate;
public:
  PLTSTATEPARAM pltlastallstates;

private:
  DEVEMSG pltdevelopmsg;

  qint32 BURN_STATE;//!<when 0 means burning,when PON means finish burning
  qint32 timerstate;//!<to tell sysctrl that timer communicate with sysctrl has finished when POFF

  Ui::BitPlatForm *ui;
  QProcess sactrlprocess;
  QProcess rtsactrlprocess;
  QProcess ltefddctrlprocess;
  QProcess ltetddctrlprocess;
  QProcess fgnrctrlprocess;
  QVector<QProcess*> processvec;
  void IniOther();
  void IniCtrlVec();
  void IniBtnVecText();

  QProcess sysprocess;
  QProcess homeprocess;
  QProcess upgradeprocess;

  QProcess calcProcess;

  void Uphomeapp();
  void Downhomeapp();

  static QFile logfile;
  static QChar regchar;
  static const char* syncpath;

  void FillConstText();
  QVector<QString> nowmodetext;
  QVector<QPushButton*> nowmodebtn;
  QVector<QLabel*> modelabel;
  QVector<QPushButton*> clobtnvec;
  qint32 NowModExitor(QString &modstr);
  qint32 SetModBtntext(qint32 iIndex, QString &modstr, qint32 iflag);

  /**
  * @brief for different mode log msg by RUNMODE order
  */
  QStringList ctrlstr;

  /**
  * @brief when switch ana mode by home and now UI do not have the selected mode,
  *        so should keep last meas state,the size should be same with RUNMODE
  * @since {2019-01-24}
  */
  QVector<QString>modesmeasstr;
  noticmsg *perrwid;

  /**
* @class
* @brief
* @since {2019-11-12}
*/
  void PltIniSa();
  void PltIniRtsa();
  void PltIniIa();
  void PltIniPm();
  void PltIniFdd();
  void PltIniTdd();
  void PltIniFgnr();
private:
  qint32 modeswitchtimerhandle;
  qint32 sysmsgtimerhandle;
  qint32 tempertimerhandle;

  QString timerstr;
  QString batterystr;
  quint32 batnum;
  QString gpstr;

  loadctrlrunparam gloadctrlparam;

  static quint32 modesumnum;//!<the same with mode num
  QVector<const QByteArray*>battpicvec;
  QVector<const QByteArray*>toppicvec;  
  QVector<const QByteArray*>noticexcetoolpicvec;
  pltcirlist *pcirlmsgqueue;
  QVector<const QByteArray*>plusnorvec;
  QVector<const QByteArray*>plusclickvec;
protected:
  void timerEvent(QTimerEvent *event);
//  void changeEvent(QEvent *event);

private:
  void SetIniQss();
  qint32 LoadAllTimer();
  void ReleaseAllTimer();
  void InnerTimeCtrl(qint32 tid);
  void QueryBatAndGps();
  qint32 qdeta;
  void SetBtnTextByHomeSwitch(qint32 imod);
  void NoBatteryCtrl();
  void ChargeStateCtrl();
  void DisChargeStateCtrl();
  void FullBatteryCtrl();
  void PlusBtnCtrl();
  void CloseBtnCtrl(qint32 iIndex);

  void ConnectAllSigSlot();
  void InitP();
  void DeleteW();

  qint32 GetModeNum(QString& str);
  qint32 HomeModeExistornot(quint32 ihmode);

  //@dismod start
  void GpsPltdisMod(qint32 imode,qint32 enflag);
  void CtrlModePltdis(qint32 imode,qint32 ictrl);
  void BatPicPltdis(qint32 imode);
  void TopTabPicdis(qint32 imode);
  void ExcePicdis(qint32 imode,qint32 icome);
  void PlusPicPltdis(qint32 imode,qint32 inum);
  //@finish dismod

  //@start mode switch
  bool CloseCtrlApp(quint32 modetype);
  qint32 CutSwitchPic(quint32 action);//!<could not cut maybe
  void HideModeGui(quint32 modetype);
  qint32 FlashBitStream(quint32 modetype);
  void ShowModeGui(quint32 modetype);
public:
  bool StartCtrlApp(quint32 modetype);
private:
  //@finish mode switch
  static void bitRedirectHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);

  QVector<QWidget*> modewidvec;//!<for all modes handle
  QVector<BPltInterface*> modeintervec;//!<for interface

  QMap<qint32,QString> wavmap;//!<for demode sounding
  qint32 wavlen;

  void CloseAnaWigInherit(qint32 imod);
  void ChangeModeMeasure(qint32 imod, qint32 imea);
  void ChangeModeLR(qint32 imod, qint32 ilr);
  void SetRmdTemper();

  switmod *pswitchwid;
  //for different mode handle
#ifdef _Linux_PLT_SA  
  BitSA *pSaAna;
#else
  QLabel *pSaAna;
#endif

#ifdef _Linux_PLT_RTSA
  BitRtSa *pRtsaAna;
#else
  QLabel *pRtsaAna;
#endif

#ifdef _Linux_PLT_SA
  BitSA *pInterAna;
#else
  QLabel *pInterAna;
#endif

#ifdef _Linux_PLT_SA
  BitSA *pPowerAna;
#else
  QLabel *pPowerAna;
#endif

#ifdef _Linux_PLT_FDD
  BitLteFdd *pLtefddAna;
#else
  QLabel *pLtefddAna;
#endif

#ifdef _Linux_PLT_TDD
  BitLteTdd *pLtetddAna;
#else
  QLabel *pLtetddAna;
#endif

#ifdef _Linux_PLT_FGNR
  BitNr *pFgnrAna;
#else
  QLabel *pFgnrAna;
#endif

  plusmode *pPlusDia;//!<for mode plus handle

  void SaveAllModeWhenShutOff(qint32 ireset);
signals:
  void ModeSwitchSig(quint32 switchtype);
  void PltFactorySig();
  void Pltexcenotsig(quint32 icode);
private:
  qint32 modbtnindex;//!<indicate max four btn which now light
  qint32 loreflag;//!<pon remote,poff local
  qint32 touchstate;//!<when lock state and cut mode to recovery lock state
  qint32 gradeflag;
  //  QCursor bitCursor;  
private slots:
  void DoSwitchAction(quint32 switchtype);
  void PlatZoomCtrl(bool flag);
  void SysPanelCtrl();
  void ChangeMeaTitle(qint32 iIndex);
  void DoexcenotAciton(quint32 icode);

  void on_mode1btn_clicked();
  void on_mode2btn_clicked();
  void on_mode3btn_clicked();
  void on_mode4btn_clicked();
  void on_plusbtn_clicked();
  void ChangeModPic(qint32 isum,qint32 imod);

  void on_chafir_clicked();
  void on_chasec_clicked();
  void on_chathird_clicked();
  void on_chafourth_clicked();
  void CloseAnaMode(qint32 imod);
  void keyPressEvent(QKeyEvent *event);
  void on_timelabel_clicked();
  void on_gpslabel_clicked();
  void on_batpiclabel_clicked();
  void on_batterylabel_clicked();
  void on_label_3_clicked();
  void on_label_10_clicked();
  void on_label_11_clicked();
  void on_label_4_clicked();
public:
  //this interface for remote mode ctrling
  void CloseAnaModeR(qint32 imode);
  void SwitchAnaMode(qint32 imode,qint32 imeas);
  void SetRemoteUi();
  void StartDevCalc();
  void StartUpGrade(qint32 iflag);

  void SetSysVolume(qint32 ivol);
  void SetSysVolSwitch(qint32 iswitch);
  void SetSysLcdBri(qint32 ibri);
  void SetSysDateType(qint32 itype);
  void SetSysDisMod(qint32 imod);
  void SetSysSleepT(qint32 itype);
  void SetSysKeyBeep(qint32 iswitch);
  void SetGpsEnable(qint32 iswitch);
  void SetSysIpAddr(QString ipstr);
  void SetSysMaskAddr(QString maskstr);
  void SetSysGateAddr(QString gatestr);
  void SetSysNetPort(qint32 port);  
  void SetSysWifiSwitch(qint32 iswitch);
  void SetSysWifMib(QString mibstr);
  void SetSysBlueSwitch(qint32 iswitch);
  void SetSysRef(quint32 iref);
  void SetSysPowerState(qint32 itype);
  void SetSysLanType(qint32 itype);
  void SetSysRefleshUserState();
  void SetRefUiStates(qint32 iref);  
  qint32 PltSaveStates(qint32 itype);
  setwid *pSetWid;    
  qint32 PltDismodForstart(qint32 imod);
  void SetExceNoticClear();
  //Johnson 20200528
  qreal getRfTemp();
  qreal getBoardTemp();
  qreal getFpgaTemp();
  float getBatteryTemp();
  //Johnson 20200615
  void refreshPltConfig(const PLTSTATEPARAM rcvCofig);
  void GetPltParam(PLTSTATEPARAM *dest);
public slots:
  //this interface for remote mode ctrling
  void SetLocalUi(qint32 ival);
  void QuitZeroCalc(bool bl);
  void PltFactorySet();
  qint32 PltSetDisMod(qint32 imod);
  void PltPlayWav(qint32 itype,qint32 iswitch);
private:
  QString GetMeasIteamsNum(qint32 imod, qint32 inum);
  void SetLockUiStates(qint32 imode, qint32 ilock);
  void PltSaveAnayStates(qint32 itype);
  void PartWtichMode(QString mstr);

  qint32 PltSaveDevelopMsg();
  qint32 PltLoadDevelopMsg();
  qint32 PltLoadStates(qint32 itype);
  qint32 PltSavePreStates();
  qint32 PltLoadPreStates();
  void PltSysPlugFactory();

  const char* GetShowExceNotiMsg(short imode,short index);

  QString ChangeGPSDisFormat(QString str);
  void checkLogFileSize();
public:
  PDEVEMSG GetDMsgHandle();
  pltcirlist* GetCirHandle();
  void ClearExceUi();
};

#endif // BITPLATFORM_H
