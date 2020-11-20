#ifndef SA_WIDGET_SPURIOUSEMTABLE_H
#define SA_WIDGET_SPURIOUSEMTABLE_H

#include <QWidget>
#include "sa_user_variable.h"
#include "sa_user_limit.h"
#include "sa_applicationcontrol.h"

//#define OCCUPIEDXDB_LEFT_MARGIN  20
#define SA_SPUREM_SPACE_LINES 20
#define SA_SPUREM_PAGESPUR_CNT 5
namespace Ui {
class sa_widget_SpuriousEMTable;
}

class sa_widget_SpuriousEMTable : public QWidget
{
    Q_OBJECT

public:
    explicit sa_widget_SpuriousEMTable(controlInterface &interface,user_variable &m_user_variable, user_limit &m_user_limit, QWidget *parent = 0);
    ~sa_widget_SpuriousEMTable();
    QPixmap SpuriousEMTablePixmap;
    void refreshSpuriousEMTable();
    void refreshPixmap();
    void setPixmapSize(qint32 mWidth,qint32 mHeight);
    void initDisplay();
private:
    Ui::sa_widget_SpuriousEMTable *ui;
protected:
    void paintEvent(QPaintEvent *event);

private:
    user_variable *globalUserVariable;
    user_limit    *globalUserLimit;
    controlInterface *mControl;


    void refreshSingleRangeTable();
    void refreshLimitSetTable();
    void refreshFreqSetTable();
    void spurSearch();
    void judgeSpurEMTestResult();
};

#endif // SA_WIDGET_SPURIOUSEMTABLE_H


