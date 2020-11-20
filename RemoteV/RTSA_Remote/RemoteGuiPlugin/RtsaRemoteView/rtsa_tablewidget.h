/**************Copyright (c)**************************************
 **
 **               INNO Instrument(China) Co.,Ltd.
 **
 **------------File Info------------------------------------------
 **Class name:              RtSa_TableWidget
 **Latest Version:          V1.0.0
 **Latest modified Date:
 **Created by:              Albert
 **Created date:            2019/03/25
 **Descriptions:            use to limit edit and FMT edit
 **/
#ifndef RTSA_TABLEWIDGET_H
#define RTSA_TABLEWIDGET_H

#include <QTableWidget>
#include <QWidget>
#include <Qt>
#include "rtsa_define.h"
class RtSa_TableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit RtSa_TableWidget(QWidget* parent = 0, Qt::WindowFlags f = Qt::WindowFlags());

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
signals:
    void editFinish();
    void contenJudge(qint32 rowIndex);
    void clicked();
    void KeySignal(QKeyEvent *event);
private:
    char newDataString[20];
    bool blNumberInput;
    bool blFirstIn;
    bool blDotInput;

    unsigned int currentRowIndex;
    unsigned int currentColumnIndex;

    double dFreq[1000];
    double dAmplitude[1000];
private slots:
    void headerClicked(int index);
public:
    void sortAllItems(void);
    void resetAllParam(void);
    void resortAllData(void);

    //Albert add 06/17
    void resetAllData(void);

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

    void judgeTableContent(QTableWidget *tableWidget,unsigned long long startFreq,unsigned long long stopFreq,bool bFlag = true);
    void judgeFmtTableContent(QTableWidget *tableWidget,unsigned long long startFreq,unsigned long long stopFreq,bool bFlag = true);

    bool bUpdateLimit;

    qreal* getLimitFreq();
    qreal* getLimitAmpt();
};

#endif // RTSA_TABLEWIDGET_H
