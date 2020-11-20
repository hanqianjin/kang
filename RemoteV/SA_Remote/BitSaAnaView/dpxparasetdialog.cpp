#include "dpxparasetdialog.h"
#include "ui_dpxparasetdialog.h"

/**
 * @brief DPXParaSetDialog::DPXParaSetDialog
 * @param parent
 * @author Johnson
 * @date 2018/1203
 * @note set Dpx parameter
 */

DPXParaSetDialog::DPXParaSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DPXParaSetDialog)
{
    setWindowFlags(Qt::Window);
    setFixedSize(700, 300);
    ui->setupUi(this);

    ui->dpxEnablecomboBox->insertItem(0,tr("Close"));
    ui->dpxEnablecomboBox->insertItem(1,tr("Open"));

    ui->persistenceModecomboBox->insertItem(0,tr("Infinite"));
    ui->persistenceModecomboBox->insertItem(1,tr("Variable"));

    ui->bitmapCtrlcomboBox->insertItem(0,tr("Not Clear"));
    ui->bitmapCtrlcomboBox->insertItem(1,tr("Clear"));

    ui->bitmapExtraccomboBox->insertItem(0,tr("Not Extract"));
    ui->bitmapExtraccomboBox->insertItem(1,tr("Extract"));
}

DPXParaSetDialog::~DPXParaSetDialog()
{
    delete ui;
}

void DPXParaSetDialog::on_OKbutton_clicked()
{
    if(ui->dpxEnablecomboBox->currentIndex() == DPX_CLOSE) {
        setDpxEn(DPX_CLOSE);
    }
    else if(ui->dpxEnablecomboBox->currentIndex() == DPX_OPEN) {
        setDpxEn(DPX_OPEN);
    }

    if(ui->persistenceModecomboBox->currentIndex() == DPX_INFINITEPERSISTENCE) {
        setDpxPersistence(DPX_INFINITEPERSISTENCE);
    }
    else if(ui->persistenceModecomboBox->currentIndex() == DPX_VARIABLEPERSISTENCE) {
        setDpxPersistence(DPX_VARIABLEPERSISTENCE);
    }

    if(ui->bitmapCtrlcomboBox->currentIndex() == DPX_NOTCLEARZERO) {
        setDpxClearFlag(DPX_NOTCLEARZERO);
    }
    else if(ui->bitmapCtrlcomboBox->currentIndex() == DPX_CLEARZERO) {
        setDpxClearFlag(DPX_CLEARZERO);
    }

    if(ui->bitmapExtraccomboBox->currentIndex() == DPX_NOTEXTRACT) {
        setDpxExtract(DPX_NOTEXTRACT);
    }
    else if(ui->bitmapExtraccomboBox->currentIndex() == DPX_EXTRACT) {
        setDpxExtract(DPX_EXTRACT);
    }

    double dAcqTime,dPersistenceTime,dMaxDensity,dMinDensity;
    dPersistenceTime = ui->persistenceTimelineEdit->text().toDouble();
    dAcqTime         = ui->acquireTimelineEdit->text().toDouble();
    dMaxDensity      = ui->highestDensitylineEdit->text().toDouble();
    dMinDensity      = ui->lowestDensitylineEdit->text().toDouble();
    dMaxDensity      = dMaxDensity/100.;
    dMinDensity      = dMinDensity/100.;

    setDpxBitAttenStep(dPersistenceTime,dAcqTime);
    setDpxDensityStep(dMaxDensity,dMinDensity);
    setDpxBlueColorStep(dMaxDensity,dMinDensity);
    setDpxGreenColorStep(dMaxDensity,dMinDensity);
    setDpxRedColorStep(dMaxDensity,dMinDensity);
    setDpxCounterMaxValue(dPersistenceTime,dAcqTime);

    emit QDialog::accept();
    this->close();
}

void DPXParaSetDialog::on_Cancelbutton_clicked()
{
    emit QDialog::accept();
    this->close();
}
void DPXParaSetDialog::setDpxEn(uint uDpxEn)
{

}
void DPXParaSetDialog::setDpxPersistence(uint uDpxPersistence)
{

}
void DPXParaSetDialog::setDpxClearFlag(uint uDpxClearFlag)
{

}
void DPXParaSetDialog::setDpxExtract(uint uDpxExtract)
{

}
void DPXParaSetDialog::setDpxBitAttenStep(double dPersistenceTime, double dAcqTime)
{

}
void DPXParaSetDialog::setDpxDensityStep(double dMaxDensity, double dMinDensity)
{

}
void DPXParaSetDialog::setDpxBlueColorStep(double dMaxDensity, double dMinDensity, double dCurve)
{

}
void DPXParaSetDialog::setDpxGreenColorStep(double dMaxDensity, double dMinDensity, double dCurve)
{

}
void DPXParaSetDialog::setDpxRedColorStep(double dMaxDensity, double dMinDensity, double dCurve)
{

}
void DPXParaSetDialog::setDpxCounterMaxValue(double dPersistenceTime, double dAcqTime)
{

}
