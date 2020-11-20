#ifndef PLTCALENDAR_H
#define PLTCALENDAR_H

#include <QDialog>
#include <QLayout>
#include <QKeyEvent>
#include <QSpinBox>
#include <QToolButton>
#include <QTableView>
#include <QHeaderView>
#include <QComboBox>
#include <QListView>

namespace Ui {
class pltCalendar;
}

class pltCalendar : public QDialog
{
    Q_OBJECT

public:
    explicit pltCalendar(QWidget *parent = 0);
    ~pltCalendar();

private slots:
    void on_pb_ok_clicked();

    void on_pb_cancel_clicked();

private:
    Ui::pltCalendar *ui;
    //QDate* pDate;
    void initCalendar();
    void keyPressEvent(QKeyEvent *e);
    QSpinBox *pYearSpin;
};

#endif // PLTCALENDAR_H
