#ifndef SETWID_H
#define SETWID_H

#include <QWidget>
#include <QtWidgets/QPushButton>
#include "comset.h"
#include "dsdtset.h"
#include "hswinfo.h"
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
  explicit setwid(QWidget *parent = 0);
  ~setwid();

private:
  Ui::setwid *ui;

  void LoadAllSetwid(qint32 iIndex);
  comset *pcomsetwid;
  dsdtset *pdedtsetwid;
  networkset *pnetsetwid;
  licemana *plicmanwid;
  hswinfo *phswinfowid;
  sysinfo *psyswid;
  QVector<QWidget*> setwidvec;
  QButtonGroup *bitsetbtngroup;

  qint32 lastsetindex;
private slots:
  void on_clobtn_clicked();
  void on_buttonGroup_clicked(qint32 idIndex);
public:

};

#endif // SETWID_H
