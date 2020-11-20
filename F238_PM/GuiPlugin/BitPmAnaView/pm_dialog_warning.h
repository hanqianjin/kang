#ifndef PM_DIALOG_WARNING_H
#define PM_DIALOG_WARNING_H

#include <QWidget>
#include <QDialog>
#include <QKeyEvent>
namespace Ui {
class Pm_Dialog_Warning;
}

class Pm_Dialog_Warning : public QDialog
{
    Q_OBJECT

public:
    explicit Pm_Dialog_Warning(QString title,QString warning,QWidget *parent = 0, qint32 mDisplay = 0);
    ~Pm_Dialog_Warning();

    void initDisplay();
    void ShowYesButtonOnly();
    void NoShowButton();
    void closeDlg();
    void SerWaringText(QString strWarning);
protected:
    void keyPressEvent(QKeyEvent *event) override;
private:
    Ui::Pm_Dialog_Warning *ui;
    QString mTitle;
    QString mWarning;
    QString strOK;
    QString strCancel;


};

#endif // PM_DIALOG_WARNING_H
