#ifndef NOTICMSG_H
#define NOTICMSG_H
#include <QTableWidgetItem>
#include <QWidget>
#include "pltcirlist.h"

namespace Ui {
  class noticmsg;
}

class noticmsg : public QWidget
{
  Q_OBJECT

public:
  explicit noticmsg(QWidget *parent = 0);
  ~noticmsg();

private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

private:
  Ui::noticmsg *ui;
  qint32 rowindex;
  qint32 excenum;
  qint32 noticnum;
  qint32 dismode;
protected:
  void keyPressEvent(QKeyEvent *event);

public:  
  void InsertMsg(short itype, QString typestr, const char *str);
  void ChangeNodeDismode(qint32 imode,pltcirlist& pcirnode);
  void SetPltExceDisM(qint32 imod);
  //for scpi ctrl
  void ClearAllExceNotic();
};

#endif // NOTICMSG_H
