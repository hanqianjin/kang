#include "pltcalendar.h"
#include "ui_pltcalendar.h"



pltCalendar::pltCalendar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pltCalendar)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | /*Qt::Tool | Qt::WindowDoesNotAcceptFocus| */Qt::Dialog);
    setWindowModality(Qt::ApplicationModal);
    initCalendar();
}

pltCalendar::~pltCalendar()
{
    delete ui;
}


void pltCalendar::initCalendar()
{
    QDate pDate = QDate::currentDate();
    QCalendarWidget *pCalendarWidget = static_cast<QCalendarWidget *>(ui->calendarWidget);
    QWidget *pTitle = pCalendarWidget->findChild<QWidget*>(QLatin1String("qt_calendar_navigationbar"));
    QToolButton *preBtn = ui->calendarWidget->findChild<QToolButton*>(QLatin1String("qt_calendar_prevmonth"));
    QToolButton *nextBtn = ui->calendarWidget->findChild<QToolButton*>(QLatin1String("qt_calendar_nextmonth"));
    QTableView  *table = ui->calendarWidget->findChild<QTableView*>();

    QVBoxLayout *vBodyLayout = pCalendarWidget->findChild<QVBoxLayout *>();
    vBodyLayout->removeWidget(table);
    vBodyLayout->removeWidget(pTitle);

    QSpinBox *pYearEdit = pCalendarWidget->findChild<QSpinBox*>(QLatin1String("qt_calendar_yearedit"));
    pYearSpin = pYearEdit;
    //QSpinBox *spinBox = pCalendarWidget->findChild<QSpinBox*>(QLatin1String("qt_calendar_mouthedit"));
    QListView *pMouthEdit = pCalendarWidget->findChild<QListView*>(QLatin1String("qt_calendar_yearedit"));
    pCalendarWidget->setSelectedDate(pDate);
    //pMouthEdit->setView(new QListView());
    pCalendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    pCalendarWidget->setLocale( QLocale::English);
    pCalendarWidget->setFixedSize(383,364);


    table->resize(383,312);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->horizontalHeader()->setDefaultSectionSize(52);
    table->verticalHeader()->setDefaultSectionSize(45);
    table->setRowHeight(0,19);
    table->move(0,60);
    table->setStyleSheet("QTableView::item{border:10px solid red}");

    pTitle->setGeometry(0,0,383,52);
    preBtn->setToolButtonStyle(Qt::ToolButtonTextOnly);
    preBtn->setParent(pCalendarWidget);
    preBtn->setGeometry(14,4,42,42);

    nextBtn->setToolButtonStyle(Qt::ToolButtonTextOnly);
    nextBtn->setParent(pCalendarWidget);
    nextBtn->setGeometry(327,4,42,42);

   //将周日放到前面
   pCalendarWidget->setFirstDayOfWeek(Qt::Sunday);
   pCalendarWidget->setGridVisible(false);

}

void pltCalendar::keyPressEvent(QKeyEvent *e)
{
    if(pYearSpin->hasFocus())
    {
        qint32 pYear = pYearSpin->value();
        qint32 keyVal = e->key();
        switch (keyVal) {
        case Qt::Key_F3:
            pYearSpin->setValue(pYear+1);
            break;
        case Qt::Key_F4:
            pYearSpin->setValue(pYear-1);
            break;
        default:
            break;
        }
    }
    return QDialog::keyPressEvent(e);
}

void pltCalendar::on_pb_ok_clicked()
{
    QString dstr = this->ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");
    QString tdstr = "date -s " + QString(" \" ") +dstr + QString(" \" ");
    system(tdstr.toStdString().c_str());
    system("hwclock -w");
    this->close();
    return;
}

void pltCalendar::on_pb_cancel_clicked()
{
    this->close();
}
