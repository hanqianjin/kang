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

namespace Ui {
  class BitPlatForm;
}

class BitPlatForm : public QMainWindow
{
  Q_OBJECT

public:
  explicit BitPlatForm(QWidget *parent = 0);
  ~BitPlatForm();

private:
  Ui::BitPlatForm *ui; 
  QProcess sactrlprocess;
  QProcess rtsactrlprocess;
  QVector<QProcess*> processvec;
  void IniCtrlVec();

  QProcess homeprocess;
  void Uphomeapp();
  void Downhomeapp();

  static QFile logfile;

  void FillConstText();
  QVector<QString> nowmodetext;
  QVector<QPushButton*> nowmodebtn;
  QVector<QPushButton*> clobtnvec;
  qint32 NowModExitor(QString &modstr);
  qint32 SetModBtntext(qint32 iIndex, QString &modstr);

  /**
  * @brief accordance with btn text by runmode order
  */
  QStringList modestr;

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

  qint32 nowshowmodsum;
private:
  qint32 modeswitchtimerhandle;
  qint32 sysmsgtimerhandle;
  qint32 tempertimerhandle;

  QString timerstr;
  QString batterystr;
  qreal batnum;
  QString gpstr;

  quint32 orimode;//!<last run modBitRtSa *pRtsaAna;  e,for compare now shm mode,if same,do nothing
  loadctrlrunparam gloadctrlparam;

  static quint32 modesumnum;//!<the same with mode num

  void GetMeasitemsIndex(qint32 *iIndex = 0);
protected:
  void timerEvent(QTimerEvent *event);

private:
  void SetIniQss();
  qint32 LoadAllTimer();
  void ReleaseAllTimer();

  void ConnectAllSigSlot();
  void InitP();
  void DeleteW();

  qint32 GetModeNum(QString& str);
  qint32 HomeModeExistornot(quint32 ihmode);

  //@start mode switch
  qint32 CloseCtrlApp(quint32 modetype);
  qint32 CutSwitchPic(quint32 action);//!<could not cut maybe
  void HideModeGui(quint32 modetype);
  qint32 FlashBitStream(quint32 modetype);
  void ShowModeGui(quint32 modetype);
  qint32 StartCtrlApp(quint32 modetype);

  //@finish mode switch
  static void bitRedirectHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);

  QVector<QWidget*> modewidvec;//!<for all modes handle

  //for different mode handle  
  BitSA *pSaAna;
  BitRtSa *pRtsaAna;
  //......

  plusmode *pPlusDia;//!<for mode plus handle  
  setwid *pSetWid;
signals:
  void ModeSwitchSig(quint32 switchtype);

private slots:
  void DoSwitchAction(quint32 switchtype);
  void PlatZoomCtrl(bool flag);

  void on_mode1btn_clicked();
  void on_mode2btn_clicked();
  void on_mode3btn_clicked();
  void on_mode4btn_clicked();
  void on_plusbtn_clicked();

  void on_chafir_clicked();
  void on_chasec_clicked();
  void on_chathird_clicked();
  void on_chafourth_clicked();

  void on_pushButton_clicked();
public:
  //this interface for remote mode ctrling
  void CloseBtnCtrl(qint32 iIndex);
  void PlusBtnCtrl();
};

#endif // BITPLATFORM_H
