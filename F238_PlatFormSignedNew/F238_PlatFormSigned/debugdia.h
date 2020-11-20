#ifndef DEBUG_H
#define DEBUG_H

#include <QDialog>
#include "softbus.h"

namespace Ui {
  class debugdia;
}

class debugdia : public QDialog
{
  Q_OBJECT

public:
  explicit debugdia(QWidget *parent = 0);
  ~debugdia();

private slots:
  void on_pushButton_clicked();
  void on_pushButton_15_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_3_clicked();
  void on_pushButton_4_clicked();
private:
  Ui::debugdia *ui;
  qint32 calcloseflag;
  PDEVEMSG debugmsgH;
protected:
  void keyPressEvent(QKeyEvent *event);
public:
  qint32 GetCalcCloseFlag();
  void RefleshStates(PDEVEMSG pHandle);
};

#endif // DEBUG_H
