#ifndef SA_CONTROLWIDGET_OCCUPIEDXDBTABLE_H
#define SA_CONTROLWIDGET_OCCUPIEDXDBTABLE_H

#include <QWidget>

#include "sa_user_variable.h"

namespace Ui {
class sa_controlWidget_OccupiedXdBTable;
}

class sa_controlWidget_OccupiedXdBTable : public QWidget
{
    Q_OBJECT

public:
    explicit sa_controlWidget_OccupiedXdBTable(user_variable &m_user_variable,QWidget *parent = 0);
    ~sa_controlWidget_OccupiedXdBTable();

private:
    Ui::sa_controlWidget_OccupiedXdBTable *ui;
public:
    user_variable *globalUserVariable;
private slots:
    void on_pushButton_clicked();
signals:
    void signalHideTable(quint32 tableID);
};

#endif // SA_CONTROLWIDGET_OCCUPIEDXDBTABLE_H
