#ifndef PLUSMODE_H
#define PLUSMODE_H

#include <QDialog>
#include <QtWidgets/QPushButton>
#include "softbus.h"

namespace Ui {
  class plusmode;
}

class plusmode : public QDialog
{
  Q_OBJECT

public:
  explicit plusmode(QWidget *parent = 0);
  plusmode(QWidget *parent = Q_NULLPTR, quint32* pmode = 0, qint32 *pallmeas = 0, qint32 inum = 0);
  ~plusmode();

private:
  Ui::plusmode *ui;

  QButtonGroup *bitbtngroup;
  QButtonGroup *meabtngroup;
  QButtonGroup *rtsabtngroup;
  QButtonGroup *intertnmgroup;
  QButtonGroup *pmbtngroup;
  QButtonGroup *ltefddbtngroup;
  QButtonGroup *ltetddbtngroup;
  QButtonGroup *fgnrbtngroup;
  QVector<QWidget*> btnwidvec;
  QVector<const QString*> pstrvec;

  quint32 unokmode;//!<when setting ok,will pass unokmode to anamode,inner use
  quint32* anamode;//for out
  QString modstr;

  qint32 unokmeas[NONEMODE];//inner use  
  QString meastr;

  void AddBtnGroups(quint32* tmode);
  void ReleaseRes();

  qint32 okaction;//whether or not click ok button
  void GetAllModeMeaIndex(qint32* pmeas,qint32 inum);

  QPushButton *testbtn;
  qint32 *pmodemeasbuffer;//!<for ok to reflesh mode measure index
public:
  QString getmodstr() const;
  qint32 getdostate() const;
  void SetPlusDisMode(qint32 imod);
private slots:
  //mode
  void buttonGroupClicked(qint32 idIndex);
  //measure
  void meaGroupClicked(qint32 idIndex);
  void rtsameaGroupClicked(qint32 idIndex);
  void intermeaGroupClicked(qint32 idIndex);
  void pmmeaGroupClicked(qint32 idIndex);
  void ltefddmeaGroupClicked(qint32 idIndex);
  void ltetddmeaGroupClicked(qint32 idIndex);
  void fgnrmeaGroupClicked(qint32 idIndex);

  void on_pushButton_15_clicked();
  void on_pushButton_16_clicked();
  void on_pushButton_17_clicked();  

protected:
  void keyPressEvent(QKeyEvent *event);
};

#endif // PLUSMODE_H
