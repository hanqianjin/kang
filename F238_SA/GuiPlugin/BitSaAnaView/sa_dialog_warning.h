#ifndef SA_DIALOG_WARNING_H
#define SA_DIALOG_WARNING_H

#include <QWidget>
#include <QDialog>
#include <QKeyEvent>
namespace Ui {
class SA_Dialog_Warning;
}

class SA_Dialog_Warning : public QDialog
{
    Q_OBJECT

public:
    explicit SA_Dialog_Warning(QString title,QString warning,QWidget *parent = 0);
    ~SA_Dialog_Warning();

protected:
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::SA_Dialog_Warning *ui;
    QString mTitle;
    QString mWarning;

    void initDisplay();
};

#endif // SA_DIALOG_WARNING_H
