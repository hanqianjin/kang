#ifndef SYSINFO_H
#define SYSINFO_H

#include <QWidget>

namespace Ui {
  class sysinfo;
}

class sysinfo : public QWidget
{
  Q_OBJECT

public:
  explicit sysinfo(QWidget *parent = 0);
  ~sysinfo();

private:
  Ui::sysinfo *ui;
};

#endif // SYSINFO_H
