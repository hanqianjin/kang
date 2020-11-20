#ifndef SA_DIALOG_CH_STD_H
#define SA_DIALOG_CH_STD_H

#include <QWidget>
#include <QButtonGroup>
#include <QFile>
#include <QKeyEvent>
#include "sa_applicationcontrol.h"
class controlInterface;
class user_variable;
namespace Ui {
class SA_Dialog_CH_Std;
}

class SA_Dialog_CH_Std : public QWidget
{
    Q_OBJECT

public:
    explicit SA_Dialog_CH_Std(controlInterface *interface, user_variable *puser_variable,QWidget *parent = 0);
    ~SA_Dialog_CH_Std();

protected:
    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_pb_cancel_clicked();

    void on_pb_up_clicked();

    void on_pb_down_clicked();

    void runBtnTypeFunction(qint32 index);

    void on_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void on_pb_close_clicked();

    void on_pb_ok_clicked();

private:
    controlInterface* mControl;
    user_variable *globalUserVariable;
    qint32 ChType;
    qint32 tabPageIndex;
    qint32 curCHIndex;
    QVector <__Standard__> ChannelRange;
    QVector <__Standard__> FreqRange;
    QVector <QString>  CHName;

    Ui::SA_Dialog_CH_Std *ui;

    QButtonGroup *mTypeGroup;
    void initWidget();
    void initDisplay();
    void initMap();
    void getBandInfo(qint32 STDIndex);
    void initTabContent(qint32 index);
    void analysisData(QString str);
    void initTabPage();
};

#endif // SA_DIALOG_CH_STD_H
