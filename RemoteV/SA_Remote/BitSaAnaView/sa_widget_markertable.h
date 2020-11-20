#ifndef SA_WIDGET_MARKERTABLE_H
#define SA_WIDGET_MARKERTABLE_H

#include <QWidget>

#include "sa_user_variable.h"
#include "sa_user_limit.h"
#include "sa_applicationcontrol.h"

#define MARKER_LEFT_MARGIN  20
#define SA_MARKER_SPACE_LINES 10

namespace Ui {
class sa_widget_markerTable;
}

class sa_widget_markerTable : public QWidget
{
    Q_OBJECT

public:
    explicit sa_widget_markerTable(controlInterface &interface,user_variable &m_user_variable,user_limit &m_user_limit,QWidget *parent = 0);
    ~sa_widget_markerTable();
public:
    QPixmap MarkerTablePixmap;
    void refreshMarkerTable();
    void refreshPixmap();
    void setPixmapSize(qint32 mWidth,qint32 mHeight);
protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::sa_widget_markerTable *ui;
public:
    user_variable *globalUserVariable;
    user_limit    *globalUserLimit;
    controlInterface *pcontrolInterface;
};

#endif // SA_WIDGET_MARKERTABLE_H
