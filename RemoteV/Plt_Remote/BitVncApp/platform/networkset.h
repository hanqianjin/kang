#ifndef NETWORKSET_H
#define NETWORKSET_H

#include <QWidget>
#include <QTableWidget>
#include "softbus.h"
#include "module/wireless.h"

namespace Ui {
  class networkset;
}
class IPLineEdit;
class SmKeyBoard;
class pltKeyBoard;
typedef struct
{
  qint32* wifiswi;
  qint32* bluswi;
  qint32* gpswi;

  qint32* port;
  char* ipName;
  char* strmaskName;
  char* strGateWayName;

  qint32* premotemode;
  char* strwifimib;
}PLT_NET,*PPLT_NET;

class networkset : public QWidget
{
  Q_OBJECT

public:
  explicit networkset(QWidget *parent = 0);
  ~networkset();
  void SetPluginProperty(const char *name, QString value);
  void ReflesGpsLabelStatus(qint32 istatus);
  void SetWifiOn(qint32 isOn);
  void SetBlutoothOn(qint32 isOn);
private:
  Ui::networkset *ui;
  PLT_NET pltnet; 
  void DelPreGateWay();
  QString ipName;
  QString strHostName;
  QString strGateWayName;
  bool SetIPAddress(QString ipaddr);
  bool SetMaskAddress(QString strMask);
  bool SetGateWayAddress(QString strGateWay);

  void SetIpBtnWord(QString str);
  void SetMaskBtnWord(QString str);
  void SetGateBtnWord(QString str);

  void GpsStyleOn();
  void GpsStyleOff();
  void WifiStyleOn();
  void WifiStyleOff();
  void BlueStyleOn();
  void BlueStyleOff();

  bool SetWifiSwitchAction(qint32 iswitch);
  bool SetWifiMibAction(QString mibstr);
  bool SetBltSwitchAction(qint32 iswitch);
private slots:
  void on_blutoothofbtn_clicked();
  void on_wifiofbtn_clicked();
  void on_gpsbtn_clicked();
  void on_netsetbtn_clicked();
  void on_pushButton_7_clicked();
  void on_pushButton_8_clicked();
  void on_pushButton_9_clicked();
  void on_netsetbtn_2_clicked();

  void on_lineEdit_14_loseFocus();

public:
  //!< for scpi
  void SetGpsSwitch(qint32 iswitch);
  bool SetIPAddressEx(QString ipaddr);
  bool SetMaskAddressEx(QString strMask);
  bool SetGateWayAddressEx(QString strGateWay);
  bool SetLanPort(qint32 port);

  bool SetWifiSwitch(qint32 iswitch);
  bool SetWifiMib(QString mibstr);
  bool SetBltSwitch(qint32 iswitch);

public:
  //!< for recovery  
  void SetGpsBtn(qint32* iIndex);
  void SetIpBtn(char* p);
  void SetMaskBtn(char* p);
  void SetGateBtn(char* p);
  void SetPortBtn(qint32* iport);

  void SetRemoteBtn(qint32 *iIndex);
  void SetWifiSwitchBtn(qint32 *iswitch);
  void SetWifiMibBtn(char* p);
  void SetBltSwitchBtn(qint32 *iswitch);

private:
  void keyPressEvent(QKeyEvent *event);
private:
  QMap<IPLineEdit*,qint32> *IPsetup;
  SmKeyBoard* mKeyBoard;
  pltKeyBoard* mPltKeyBoard;
private slots:
  void showKeyBoard();
  void hideKeyBoard();
  void on_ipEvent(qint32 type);
  void on_lineEdit_14_clicked();
  /*Tony for wifi and bluetooth*/
private slots:
  void on_wifiCilcked();
  void on_pb_wifi_refresh_clicked();
  void on_EditDevName_clicked();
  void on_EditDevName_loseFocus();
  void on_tableWidget_cellClicked(int row, int column);

  void on_EditDevName_2_clicked();

  void on_EditDevName_2_loseFocus();

private:

  void initWifiWidget();
  void refreshWifiList();
  static qint32 deal_scan(void * pdata);
private:

  SSIDInfo* pWifiInfo;
  qint32 netFd;
};

#endif // NETWORKSET_H
