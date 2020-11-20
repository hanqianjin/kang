#ifndef RSAHALA_H
#define RSAHALA_H

#include <QWidget>
#include "runstateshm.h"
#include "modethread.h"
#include <QFile>

namespace Ui {
  class RsaHala;
}

class RsaHala : public QWidget
{
  Q_OBJECT

public:
  explicit RsaHala(QWidget *parent = NULL);
  ~RsaHala();

private:
  Ui::RsaHala *ui;
  modethread* pmthread;

  qint32 lcf;
  qint32 ncf;
  qint32 lncf;
  qint32 nncf;

  qint32 timerHandle;
  qint32 batteryHandle;
  QString batterystr;
  quint32 batnum;
  qint32 showflag;//!<when PON means show and could get battery msg,when poff means hide and could not get battery msg and so on
  qint32 presetflag;
  void HomeTimeCtrl(qint32 id);

  qint32 LoadTimerHandle();
  void ReleaseTimerHandle();

  void NoBatteryCtrl();
  void ChargeStateCtrl();
  void DisChargeStateCtrl();
  void FullBatteryCtrl();

  qint32 homedismode;
  QVector<const QByteArray*>battpicvec;  
  static QFile logfile;
  static void bithomeRedirectHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);
protected:
  void timerEvent(QTimerEvent *event);
  void changeEvent(QEvent *event);
private slots:
  void on_bsabutton_clicked();
  void on_rsabutton_clicked();
  void on_ltetddbutton_clicked();
  void on_ltefddbutton_clicked();
  void on_pmbutton_clicked();
  void on_interbutton_clicked();
  void on_fivegbutton_clicked();
  void on_sysbutton_clicked();
  void homeuishow();
  void on_pushButton_clicked();

private:
  void DoSwitchCtrl(quint32 imode);
  void BatPicPltdis(qint32 imode);

protected:
  void keyPressEvent(QKeyEvent *event);
};

#endif // RSAHALA_H
