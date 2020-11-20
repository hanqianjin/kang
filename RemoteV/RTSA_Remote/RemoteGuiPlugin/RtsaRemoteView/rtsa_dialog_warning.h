#ifndef RTSA_DIALOG_WARNING_H
#define RTSA_DIALOG_WARNING_H

#include <QWidget>
#include <QDialog>
namespace Ui {
class RtSa_Dialog_Warning;
}

class RtSa_Dialog_Warning : public QDialog
{
    Q_OBJECT

public:
    explicit RtSa_Dialog_Warning(QString title,QString warning,QWidget *parent = 0, qint32 mDisplay = 0);
    ~RtSa_Dialog_Warning();

    void initDisplay();
    void ShowYesButtonOnly();

private:
    Ui::RtSa_Dialog_Warning *ui;
    QString mTitle;
    QString mWarning;
    QString strOK;
    QString strCancel;


};

#endif // RTSA_DIALOG_WARNING_H
