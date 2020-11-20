#ifndef SA_WIDGET_OCCUPIEDXDBTABLE_H
#define SA_WIDGET_OCCUPIEDXDBTABLE_H

#include <QWidget>

#include "sa_user_variable.h"
#include "sa_user_limit.h"

#define OCCUPIEDXDB_LEFT_MARGIN  20
#define SA_OCC_SPACE_LINES 5

namespace Ui {
class sa_widget_OccupiedXdBTable;
}

class sa_widget_OccupiedXdBTable : public QWidget
{
    Q_OBJECT

public:
    explicit sa_widget_OccupiedXdBTable(user_variable &m_user_variable,user_limit &m_user_limit,QWidget *parent = 0);
    ~sa_widget_OccupiedXdBTable();
public:
    QPixmap OccupiedXdBTablePixmap;
    void refreshOccupiedXdBTable();
    void refreshPixmap();
    void setPixmapSize(qint32 mWidth,qint32 mHeight);
protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::sa_widget_OccupiedXdBTable *ui;
public:
    user_variable *globalUserVariable;
    user_limit    *globalUserLimit;
};

#endif // SA_WIDGET_OCCUPIEDXDBTABLE_H
