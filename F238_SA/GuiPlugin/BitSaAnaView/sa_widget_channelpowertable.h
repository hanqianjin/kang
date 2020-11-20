#ifndef SA_WIDGET_CHANNELPOWERTABLE_H
#define SA_WIDGET_CHANNELPOWERTABLE_H

#include <QWidget>

#include "sa_user_variable.h"
#include "sa_user_limit.h"
#include "sa_applicationcontrol.h"

#define CHANNELPOWER_LEFT_MARGIN  20
#define SPACE_BETWEEN_LINES 5

namespace Ui {
class sa_widget_ChannelPowerTable;
}

class sa_widget_ChannelPowerTable : public QWidget
{
    Q_OBJECT

public:
    explicit sa_widget_ChannelPowerTable(controlInterface &interface,user_variable &m_user_variable,user_limit &m_user_limit,QWidget *parent = 0);
    ~sa_widget_ChannelPowerTable();
public:
    QPixmap ChannelPowerTablePixmap;
    void refreshChannelPowerTable();
    void refreshPixmap();
    void setPixmapSize(qint32 mWidth,qint32 mHeight);
protected:
    void paintEvent(QPaintEvent *event);
private:
    Ui::sa_widget_ChannelPowerTable *ui;
public:
    user_variable *globalUserVariable;
    user_limit    *globalUserLimit;
    controlInterface *pcontrolInterface;
};

#endif // SA_WIDGET_CHANNELPOWERTABLE_H
