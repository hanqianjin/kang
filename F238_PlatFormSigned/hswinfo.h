#ifndef HSWINFO_H
#define HSWINFO_H

#include <QWidget>

namespace Ui {
  class hswinfo;
}

class hswinfo : public QWidget
{
  Q_OBJECT

public:
  explicit hswinfo(QWidget *parent = 0);
  ~hswinfo();

private:
  Ui::hswinfo *ui;
};

#endif // HSWINFO_H
