#ifndef CLICKABLETABLEWIDGET_H
#define CLICKABLETABLEWIDGET_H

#include <QTableWidget>
#include <QWidget>
#include "bvctrlmana.h"
class BVTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit BVTableWidget(BIT_FREQ_INFO *freqinfo, ctrlmana *mctrlmana, QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
signals:
    void editFinish();
    void tabelClicked();
private:
    char newDataString[20];
    bool blNumberInput;
    bool blFirstIn;
    bool blDotInput;

    quint32 currentRowIndex;
    quint32 currentColumnIndex;

    qreal dFreq[1000];
    qreal dAmplitude[1000];
    ctrlmana *gctrlmana;
    BIT_FREQ_INFO *gfreqinfo;
private slots:
    void headerClicked(qint32 index);
public:
    void getTableWidgetValue(void);
    void initTableWidgetValue(void);
    void resetAllParam(void);
    void sortAllItems(void);

    //KeyPress processing application
    void numberProcess(char *number, QString qShowStr, QTableWidgetItem *widgetItem);
    void leftKeyProcess(void);
    void rightKeyProcess(void);
    void upKeyProcess(void);
    void downKeyProcess(void);
    void dotKeyProcess(QString qShowStr, QTableWidgetItem *widgetItem);
    void espKeyProcess(void);
    void enterKeyProcess(void);
    void minusKeyProcess(QString qShowStr, QTableWidgetItem *widgetItem);
    void backSpaceKeyProcess(QString qShowStr, QTableWidgetItem *widgetItem);

    void judgeTableContent(QTableWidget *tableWidget,qreal startFreq,qreal stopFreq,bool bFlag = true);

    bool bUpdateLimit;
};

#endif // CLICKABLETABLEWIDGET_H
