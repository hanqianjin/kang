#ifndef SYSINFO_H
#define SYSINFO_H

#include <QWidget>
#include "softbus.h"

namespace Ui {
  class sysinfo;
}

class sysinfo : public QWidget
{
  Q_OBJECT

public:
  explicit sysinfo(QWidget *parent = 0);
  ~sysinfo();
  void RefleshVerDate(PDEVEMSG pmsg);

  void SetTemperSysinfo(QStringList &slist);
  void RefreshVerMsg0();
  void RefreshVerMsg1();
  void RefreshVerMsg2();

  void Flszsb();
private:
  Ui::sysinfo *ui;
};

#endif // SYSINFO_H
