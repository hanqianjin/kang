#ifndef SA_DIALOG_ERROR_H
#define SA_DIALOG_ERROR_H

#include <QDialog>
#include <QKeyEvent>
namespace Ui {
class SA_Dialog_Error;
}

class SA_Dialog_Error : public QDialog
{
    Q_OBJECT

public:
    explicit SA_Dialog_Error(QString title,QString warning,QWidget *parent = 0);
    ~SA_Dialog_Error();

protected:
    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_pb_ok_clicked();

private:
    Ui::SA_Dialog_Error *ui;
    QString mTitle;
    QString mWarning;

    void initDisplay();
};

#endif // SA_DIALOG_ERROR_H
