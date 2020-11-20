#ifndef SA_CONTROLWIDGET_CHNLTABLE_H
#define SA_CONTROLWIDGET_CHNLTABLE_H

#include <QWidget>

#include "sa_user_variable.h"

namespace Ui {
class sa_controlWidget_ChnlTable;
}

class sa_controlWidget_ChnlTable : public QWidget
{
    Q_OBJECT

public:
    explicit sa_controlWidget_ChnlTable(user_variable &m_user_variable,QWidget *parent = 0);
    ~sa_controlWidget_ChnlTable();

private:
    Ui::sa_controlWidget_ChnlTable *ui;
public:
    user_variable *globalUserVariable;
signals:
    void signalHideTable(quint32 tableID);
private slots:
    void on_pushButton_clicked();
};

#endif // SA_CONTROLWIDGET_CHNLTABLE_H
