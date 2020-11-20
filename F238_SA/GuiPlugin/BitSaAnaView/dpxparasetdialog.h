#ifndef DPXPARASETDIALOG_H
#define DPXPARASETDIALOG_H

#include <QDialog>
#include "sa_shared_memory.h"

enum {
    DPX_CLOSE = 0,
    DPX_OPEN  = 1
};
enum {
    DPX_INFINITEPERSISTENCE = 0,
    DPX_VARIABLEPERSISTENCE = 1
};
enum {
    DPX_NOTCLEARZERO = 0,
    DPX_CLEARZERO    = 1
};
enum {
    DPX_NOTEXTRACT = 0,
    DPX_EXTRACT    = 1
};

namespace Ui {
class DPXParaSetDialog;
}

class DPXParaSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DPXParaSetDialog(QWidget *parent = 0);
    ~DPXParaSetDialog();
private slots:
    void on_OKbutton_clicked();
    void on_Cancelbutton_clicked();
private:
    Ui::DPXParaSetDialog *ui;
private:
    void setDpxEn(uint uDpxEn);
    void setDpxPersistence(uint uDpxPersistence);
    void setDpxClearFlag(uint uDpxClearFlag);
    void setDpxExtract(uint uDpxExtract);
    void setDpxBitAttenStep(double dPersistenceTime,double dAcqTime);
    void setDpxDensityStep(double dMaxDensity,double dMinDensity);
    void setDpxBlueColorStep(double dMaxDensity,double dMinDensity,double dCurve = 1);
    void setDpxGreenColorStep(double dMaxDensity,double dMinDensity,double dCurve = 1);
    void setDpxRedColorStep(double dMaxDensity,double dMinDensity,double dCurve = 1);
    void setDpxCounterMaxValue(double dPersistenceTime,double dAcqTime);
};

#endif // DPXPARASETDIALOG_H
