#ifndef PM_DIALOG_ERROR_H
#define PM_DIALOG_ERROR_H

#include <QDialog>

namespace Ui {
class Pm_Dialog_Error;
}

class Pm_Dialog_Error : public QDialog
{
    Q_OBJECT

public:
    explicit Pm_Dialog_Error(QString title,QString warning,QWidget *parent = 0, qint32 mDisplay = 0);
    ~Pm_Dialog_Error();
private slots:
    void on_pb_ok_clicked();

private:
    Ui::Pm_Dialog_Error *ui;
    QString mTitle;
    QString mWarning;

    void initDisplay();
};

#endif // PM_DIALOG_ERROR_H
