#ifndef PLTNOTICE_H
#define PLTNOTICE_H

#include <QDialog>

namespace Ui {
  class pltnotice;
}

typedef struct
{
  qint32 itype; //!<now ana mode
  qint32 istyle;//!<to set notice widget style  
}PLT_NOTICE;

class pltnotice : public QDialog
{
  Q_OBJECT

public:
  explicit pltnotice(QWidget *parent = 0);
  pltnotice(qint32 itype = 0, qint32 istyle = 0, QWidget *parent = 0);
  ~pltnotice();

  qint32 GetSelectState();
  void StopZeroCalc(bool bl);
  void SetNoticDisMode(qint32 imod);  
private slots:
  void on_pushButtoncancel_clicked();

  void on_pushButtonok_clicked();

  void on_lineEdit_returnPressed();

  void on_pushButton_clicked();

private:
  Ui::pltnotice *ui;
  qint32 btnstate;
  PLT_NOTICE pltnot;
  qint32 involid;

  qint32 eyestate;
  qint32 dismode;
  void SetEyeOpenDisM();
  void SetEyeCloseDisM();
protected:
  void keyPressEvent(QKeyEvent *event);

};

#endif // PLTNOTICE_H