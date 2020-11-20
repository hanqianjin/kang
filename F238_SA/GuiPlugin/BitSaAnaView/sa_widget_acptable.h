#ifndef SA_WIDGET_ACPTABLE_H
#define SA_WIDGET_ACPTABLE_H

#include <QWidget>

#include "sa_user_variable.h"
#include "sa_user_limit.h"
#include "sa_applicationcontrol.h"

//#define ACP_LEFT_MARGIN     20
//#define SPACE_BETWEEN_LINES 8
//#define ACP_BETWEEN_COLUMN  10
#define ACP_LEFT_MARGIN     20
#define SPACE_BETWEEN_LINES 10//5
#define ACP_BETWEEN_COLUMN  10


namespace Ui {
class sa_widget_ACPTable;
}

class sa_widget_ACPTable : public QWidget
{
    Q_OBJECT

public:
    explicit sa_widget_ACPTable(controlInterface &interface,user_variable &m_user_variable,user_limit &m_user_limit,QWidget *parent = 0);
    ~sa_widget_ACPTable();

public:
    QPixmap ACPTablePixmap;
    void refreshAcpTable();
    void refreshPixmap();
    void setPixmapSize(qint32 mWidth,qint32 mHeight);
protected:
    void paintEvent(QPaintEvent *event);
private:
    Ui::sa_widget_ACPTable *ui;
public:
    user_variable *globalUserVariable;
    user_limit    *globalUserLimit;
    controlInterface *pcontrolInterface;
};

#endif // SA_WIDGET_ACPTABLE_H
