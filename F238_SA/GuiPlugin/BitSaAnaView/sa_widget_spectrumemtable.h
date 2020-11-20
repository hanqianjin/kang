#ifndef SA_WIDGET_SPECTRUMEMTABLE_H
#define SA_WIDGET_SPECTRUMEMTABLE_H

#include <QWidget>

#include "sa_user_variable.h"
#include "sa_user_limit.h"
#include "sa_applicationcontrol.h"

#define OCCUPIEDXDB_LEFT_MARGIN  20
#define SA_SPECEM_SPACE_LINES 20

namespace Ui {
class sa_widget_SpectrumEMTable;
}

class sa_widget_SpectrumEMTable : public QWidget
{
    Q_OBJECT

public:
    explicit sa_widget_SpectrumEMTable(controlInterface &interface,user_variable &m_user_variable, user_limit &m_user_limit, QWidget *parent = 0);
    ~sa_widget_SpectrumEMTable();

public:
    QPixmap SpectrumEMTablePixmap;
    void refreshSpectrumEMTable();
    void refreshPixmap();
    void setPixmapSize(qint32 mWidth,qint32 mHeight);
    void initDisplay();
protected:
    void paintEvent(QPaintEvent *event);

private:
    qint32 firstDisplay;
    user_variable *globalUserVariable;
    user_limit    *globalUserLimit;
    controlInterface *mControl;
    typedef struct
    {
        qreal Freq;
        qreal Power;
    }__PeakPoint__ ;
    Ui::sa_widget_SpectrumEMTable *ui;
    qreal calculateTotalPwr(qreal startFreq, qreal mBandWidth);
    qreal calculatePSD(qreal mPower,qreal mBandWidth);
    qint32 calculateSpecPeak(qreal SEMStartFreq,qreal mBandWidth);
};

#endif // SA_WIDGET_SPECTRUMEMTABLE_H
