#ifndef COMSET_H
#define COMSET_H

#include <QWidget>
#include "pltnotice.h"

namespace Ui {
  class comset;
}

typedef struct COM_VAR
{
  qint32* pref;
  qint32* ppower;
  qint32* plang;
  quint32* panamode;

  qint32* pdismode;
}ComSetVar,*PComSetVar;

class comset : public QWidget
{
  Q_OBJECT

public:
  explicit comset(QWidget *parent = 0);
  ~comset();

private:
  quint32 refsource;
  ComSetVar comvar;//!<for recovery

public:
  //for recovery use
  void SetRefBtnCheck(qint32 *iIndex);
  void SetPowerBtnCheck(qint32 *iIndex);
  void SetLangBtnCheck(qint32 *iIndex);
  void GetNowAnaMode(quint32 *inowmode);

  /**
* @class
* @brief for notice widget to set dismode by pdismode
* @since {2019-09-12}
*/
  void GetDisModeExt(qint32 *idismode);
private slots:
  void on_interrefbtn_clicked();
  void on_ext10btn_clicked();
  void on_ext13btn_clicked();
  void on_ext15btn_clicked();
  void on_gpsrefbtn_clicked();
  void on_pushButton_12_clicked();
  void on_pushButton_13_clicked();
  void on_pushButton_14_clicked();
  void on_pushButton_15_clicked();
  void on_pushButton_16_clicked();
  void on_pushButton_17_clicked();
  void on_pushButton_18_clicked();
  void on_pushButton_20_clicked();
  void on_pushButton_19_clicked();

private:
  Ui::comset *ui;
  pltnotice *pnwid;
  void PltSetRef(quint32 iref);
public:
  //for scpi use
  void SetFreqRef(quint32 iref);
  void SetLanType(qint32 itype);
  void SetPowerType(qint32 itype);
  void SetNowTouser();
};

#endif // COMSET_H
