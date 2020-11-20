#ifndef FILEMANA_H
#define FILEMANA_H

#include <QWidget>
#include "pltnotice.h"
#include "debugdia.h"

namespace Ui {
  class filemana;
}

typedef struct FMANA_VAR
{
  quint32 *panamode;
  qint32 *pdismode;
}FileSetVar,*PFileSetVar;

class filemana : public QWidget
{
  Q_OBJECT

public:
  explicit filemana(QWidget *parent = 0);
  ~filemana();

  void GetNowAnaMode(quint32 *imod);
  void GetDisMode(qint32 *imod);
  pltnotice *pnoticwid;
private slots:
  void on_pushButton_19_clicked();

  void on_pushButton_21_clicked();

private:
  Ui::filemana *ui;
  FileSetVar filemanavar;
  debugdia *pdegd;
};

#endif // FILEMANA_H
