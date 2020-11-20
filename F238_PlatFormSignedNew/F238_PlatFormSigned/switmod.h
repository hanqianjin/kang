#ifndef SWITMOD_H
#define SWITMOD_H

#include <QWidget>

namespace Ui {
  class switmod;
}

class switmod : public QWidget
{
  Q_OBJECT

public:
  explicit switmod(QWidget *parent = 0);
  ~switmod();

private:
  Ui::switmod *ui;  
};

#endif // SWITMOD_H
