#ifndef SA_CUSTOMEDTABLEWIDGET_H
#define SA_CUSTOMEDTABLEWIDGET_H

#include <QTableWidget>
#include <QWidget>
#include <Qt>
#include <QCoreApplication>
#include "define.h"


class ClickableTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit ClickableTableWidget(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

protected:
    void keyPressEvent(QKeyEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
//    void mousePressEvent(QMouseEvent *event);
signals:
    void editFinish();
    void contenJudge();
    void clicked();
private:
    QWidget *mParent;
    char newDataString[20];
    bool blNumberInput;
    bool blFirstIn;
    bool blDotInput;

    int currentRowIndex;
    int currentColumnIndex;

    double dFreq[1000];
    double dAmplitude[1000];
private slots:
    void headerClicked(int index);
public:
    void sortAllItems(void);
    void resetAllParam(void);

    //KeyPress processing application
    void numberProcess(const char *number, QString qShowStr, QTableWidgetItem *widgetItem);
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

    bool bUpdateLimit;
};

#endif // SA_CUSTOMEDTABLEWIDGET_H
