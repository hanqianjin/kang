#ifndef BITUPGRADE_H
#define BITUPGRADE_H

#include <QMainWindow>
#include "upaction.h"
//#include "bitsa.h"

namespace Ui {
  class bitupgrade;
}

typedef struct shmnotic
{
  qint32 notic; //!<1 means to start calc
}SHM_NOTIC,*PSHM_NOTIC;

class bitupgrade : public QMainWindow
{
  Q_OBJECT

public:
  explicit bitupgrade(QWidget *parent = 0);
  ~bitupgrade();

  void UpEngine();
private:
  Ui::bitupgrade *ui;

  qint32 tid;
  qint32 circle;
  upaction *bitupaction;  
  qint32 finper;
  qint32 shm_calnot_id;
  PSHM_NOTIC pshm_calnotic;
  qint32 midper;

//  BitSA *pSaAna;
signals:
  void dosig();
protected:
  void timerEvent(QTimerEvent *event);

private slots:
  void DoEnginer();
  void ShowUpStage(qint32 istage);
  void doslots();
  void on_pushButton_clicked();
};

#endif // BITUPGRADE_H
