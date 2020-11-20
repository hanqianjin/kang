#ifndef SETWID_H
#define SETWID_H

#include <QWidget>
#include <QtWidgets/QPushButton>
#include "comset.h"
#include "dsdtset.h"
#include "filemana.h"
#include "licemana.h"
#include "networkset.h"
#include "sysinfo.h"

namespace Ui {
  class setwid;
}

class setwid : public QWidget
{
  Q_OBJECT

public:
  explicit setwid(PPLTPRESTATE psys = NULL,PPSTATEPARAM pplt = NULL,QWidget *parent = 0);
  ~setwid();

private:
  Ui::setwid *ui;

  void LoadAllSetwid(qint32 iIndex);
  QVector<QWidget*> setwidvec;
  QButtonGroup *bitsetbtngroup;
  PPLTPRESTATE recoversys;
  PPSTATEPARAM recoverplt;

  qint32 lastsetindex;
private slots:
  void on_clobtn_clicked();
  void buttonGroupClicked(qint32 idIndex);
public:
  comset *pcomsetwid;
  dsdtset *pdedtsetwid;
  networkset *pnetsetwid;
  licemana *plicmanwid;
  filemana *pfilemanaowid;
  sysinfo *psyswid;

  void LabCli(qint32 iIndex);
  void SetPltSysDisM(qint32 imod);
public  slots:
  void DisToHide();
protected:
  void keyPressEvent(QKeyEvent *event);
};

#endif // SETWID_H
