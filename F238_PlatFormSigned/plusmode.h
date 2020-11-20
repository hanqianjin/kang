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
  plusmode(QWidget *parent = Q_NULLPTR, quint32* pmode = 0, quint32 *pmeaitem = 0, qint32 *pallmeas = 0, qint32 inum = 0, QVector<QString> *meastrvec = 0);
  ~plusmode();

private:
  Ui::plusmode *ui;

  QButtonGroup *bitbtngroup;
  QButtonGroup *meabtngroup;
  QButtonGroup *rtsabtngroup;
  QButtonGroup *intertnmgroup;
  QButtonGroup *pmbtngroup;
  QButtonGroup *ltetddbtngroup;
  QVector<QWidget*> btnwidvec;
  QVector<const QString*> pstrvec;

  quint32 unokmode;//!<when setting ok,will pass unokmode to anamode,inner use
  quint32* anamode;//for out
  QString modstr;
  QVector<QString> *pmeastrvec;

  qint32 unokmeas[NONEMODE];//inner use
  quint32* measitem;//for out
  QString meastr;

  void AddBtnGroups(quint32* tmode,quint32 *tmea);
  void ReleaseRes();

  qint32 okaction;//whether or not click ok button
  void GetAllModeMeaIndex(qint32* pmeas,qint32 inum);
public:
  QString getmodstr() const;
  qint32 getdostate() const;

private slots:
  //mode
  void on_buttonGroup_clicked(qint32 idIndex);
  //measure
  void on_meaGroup_clicked(qint32 idIndex);
  void on_rtsameaGroup_clicked(qint32 idIndex);
  void on_intermeaGroup_clicked(qint32 idIndex);
  void on_pmmeaGroup_clicked(qint32 idIndex);
  void on_ltetddmeaGroup_clicked(qint32 idIndex);

  void on_pushButton_16_clicked();
  void on_pushButton_17_clicked();
};

#endif // PLUSMODE_H
