#ifndef RTSA_DIALOG_ERROR_H
#define RTSA_DIALOG_ERROR_H

#include <QDialog>

namespace Ui {
class RtSa_Dialog_Error;
}

class RtSa_Dialog_Error : public QDialog
{
    Q_OBJECT

public:
    explicit RtSa_Dialog_Error(QString title,QString warning,QWidget *parent = 0, qint32 mDisplay = 0);
    ~RtSa_Dialog_Error();
private slots:
    void on_pb_ok_clicked();

private:
    Ui::RtSa_Dialog_Error *ui;
    QString mTitle;
    QString mWarning;

    void initDisplay();
};

#endif // RTSA_DIALOG_ERROR_H
