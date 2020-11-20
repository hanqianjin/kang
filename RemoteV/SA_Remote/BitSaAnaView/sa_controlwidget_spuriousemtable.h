#ifndef SA_CONTROLWIDGET_SPURIOUSEMTABLE_H
#define SA_CONTROLWIDGET_SPURIOUSEMTABLE_H

#include <QWidget>
#include "sa_user_variable.h"

namespace Ui {
class sa_ControlWidget_SpuriousEMTable;
}

class sa_ControlWidget_SpuriousEMTable : public QWidget
{
    Q_OBJECT

public:
    explicit sa_ControlWidget_SpuriousEMTable(user_variable &m_user_variable,QWidget *parent = 0);
    ~sa_ControlWidget_SpuriousEMTable();

private:
    Ui::sa_ControlWidget_SpuriousEMTable *ui;
public:
    user_variable *globalUserVariable;
private slots:
    void on_pushButton_clicked();
signals:
    void signalHideTable(quint32 tableID);
};

#endif // SA_CONTROLWIDGET_SPURIOUSEMTABLE_H
