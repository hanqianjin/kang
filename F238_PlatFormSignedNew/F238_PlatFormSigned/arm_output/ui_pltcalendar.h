/********************************************************************************
** Form generated from reading UI file 'pltcalendar.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLTCALENDAR_H
#define UI_PLTCALENDAR_H

#include <QtCore/QDate>
#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pltCalendar
{
public:
    QCalendarWidget *calendarWidget;
    QWidget *widget;
    QPushButton *pb_cancel;
    QPushButton *pb_ok;

    void setupUi(QDialog *pltCalendar)
    {
        if (pltCalendar->objectName().isEmpty())
            pltCalendar->setObjectName(QStringLiteral("pltCalendar"));
        pltCalendar->resize(383, 409);
        pltCalendar->setStyleSheet(QLatin1String("#pltCalendar[pltdismode =\"indoor\"] #widget,\n"
"#pltCalendar[pltdismode =\"indoor\"] #pltCalendar\n"
"{\n"
"	background-color:rgba(247, 247, 247, 1);\n"
"}\n"
"\n"
"#pltCalendar[pltdismode =\"outdoor\"] #widget,\n"
"#pltCalendar[pltdismode =\"outdoor\"] #pltCalendar\n"
"{\n"
"	background-color:rgba(247, 247, 247, 1);\n"
"}\n"
"\n"
"#pltCalendar[pltdismode =\"night\"] #widget,\n"
"#pltCalendar[pltdismode =\"night\"] #pltCalendar\n"
"{\n"
"	background-color:rgb(243,212,161);\n"
"}"));
        calendarWidget = new QCalendarWidget(pltCalendar);
        calendarWidget->setObjectName(QStringLiteral("calendarWidget"));
        calendarWidget->setGeometry(QRect(0, 0, 383, 354));
        calendarWidget->setStyleSheet(QLatin1String("\n"
"QCalendarWidget QWidget#qt_calendar_navigationbar\n"
"{\n"
"	background-color:rgba(44, 44, 44, 1);\n"
"}\n"
"\n"
"#qt_calendar_prevmonth\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/bit/image/PrevButton.png);\n"
"}\n"
"#qt_calendar_prevmonth:pressed\n"
"{\n"
"	background-image: url(:/bit/image/PrevButton_click.png);\n"
"}\n"
"#qt_calendar_nextmonth\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/bit/image/NextButton.png);\n"
"}\n"
"#qt_calendar_nextmonth:pressed\n"
"{\n"
"	background-image: url(:/bit/image/NextButton_click.png);\n"
"}\n"
"#qt_calendar_monthbutton\n"
"{\n"
"	border-style:flat;\n"
"	background-color:rgba(44, 44, 44, 1);\n"
"	color:rgba(186, 186, 186, 1);\n"
"	font:75 20px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"QCalendarWidget QTableView \n"
"{\n"
"	padding-left:10px;\n"
"	background-color:rgba(247, 247, 247, 1);\n"
"	font:75 15px \"Arial\";\n"
"	selection-background-color: rgba(255, 181, 0, 1);\n"
"	selection-color: black;\n"
"	\n"
"}\n"
"\n"
"QCalendarW"
                        "idget QTableView::item\n"
"{\n"
"	margin:10px 10px;\n"
"	color:red;\n"
"	background-color:red;\n"
"}\n"
"\n"
"#pltCalendar[pltdismode=\"indoor\"] QCalendarWidget QWidget#qt_calendar_navigationbar\n"
"{\n"
"	background-color:rgba(44, 44, 44, 1);\n"
"}\n"
"#pltCalendar[pltdismode=\"outdoor\"] QCalendarWidget QWidget#qt_calendar_navigationbar\n"
"{\n"
"	background-color:rgba(44, 44, 44, 1);\n"
"}\n"
"#pltCalendar[pltdismode=\"night\"] QCalendarWidget QWidget#qt_calendar_navigationbar\n"
"{\n"
"	background-color:rgba(44, 44, 44, 1);\n"
"}\n"
"\n"
"#pltCalendar[pltdismode=\"night\"] QCalendarWidget QTableView \n"
"{\n"
"	  background-color:rgb(243,212,161);\n"
"	  alternate-background-color: rgb(243,212,161);\n"
"}\n"
"\n"
"#pltCalendar[pltdismode=\"night\"] #qt_calendar_navigationbar\n"
"{\n"
"	background-color:rgb(243,212,161);\n"
"}\n"
"\n"
"\n"
"\n"
"QMenu \n"
"{\n"
"  background-color:rgb(89,87,87);\n"
"  width:100px;\n"
"}\n"
"QMenu::item \n"
"{          \n"
"	   width:120px;        \n"
"	   font:75 15px \"Ar"
                        "ial\";\n"
"      color: rgb(225,225,225);\n"
"      background-color:rgb(89,87,87);\n"
"      padding-left:20px;\n"
"	   padding:10px 10px;\n"
" }\n"
"QMenu::item:selected \n"
"{ \n"
"        background-color:rgb(235,110,36);\n"
" }\n"
"QMenu::item:pressed\n"
" {\n"
"          background-color: rgb(220,80,6); \n"
"}\n"
"\n"
"\n"
"#qt_calendar_yearbutton\n"
"{\n"
"	border-style:flat;\n"
"	background-color:rgba(44, 44, 44, 1);\n"
"	color:rgba(186, 186, 186, 1);\n"
"	font:75 20px \"Arial\";\n"
"	font-weight:bold;\n"
"	min-width:70px;\n"
"}\n"
"\n"
"QSpinBox:focus\n"
"{\n"
"	color:rgba(186, 186, 186, 1);\n"
"	font:75 20px \"Arial\";\n"
"	font-weight:bold;\n"
"	border-style:flat;\n"
"	background-color:rgba(0,0,0,0);\n"
"}\n"
"\n"
"QSpinBox::up-button \n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_up_w50_nor.png);\n"
"	margin:2px 2px;\n"
"	width:25px;\n"
"}\n"
" \n"
"QSpinBox::down-button\n"
"{\n"
"	border-image:url(:/bit/image/keyBoard/indoor/btn_down_w50_nor.png);\n"
"	margin:2px 2px;\n"
"	width:25p"
                        "x;\n"
"}\n"
""));
        calendarWidget->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        calendarWidget->setSelectedDate(QDate(2019, 10, 5));
        calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
        widget = new QWidget(pltCalendar);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 383, 409));
        widget->setStyleSheet(QStringLiteral(""));
        pb_cancel = new QPushButton(widget);
        pb_cancel->setObjectName(QStringLiteral("pb_cancel"));
        pb_cancel->setGeometry(QRect(205, 364, 80, 30));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(13);
        pb_cancel->setFont(font);
        pb_cancel->setStyleSheet(QLatin1String("/********************indoor**********************/\n"
"#pltCalendar[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	border-style:flat;\n"
"	background-image:url(:/bit/image/btn_cancel_w80_nor.png);\n"
"}\n"
"#pltCalendar[pltdismode=\"indoor\"] QPushButton:clicked\n"
"{\n"
"	border-style:flat;\n"
"	background-image:url(:/bit/image/btn_cancel_w80_click.png);\n"
"}\n"
"/********************outdoor**********************/\n"
"#pltCalendar[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	border-style:flat;\n"
"	background-image:url(:/bit/image/btn_cancel_w80_nor.png);\n"
"}\n"
"#pltCalendar[pltdismode=\"outdoor\"] QPushButton:clicked\n"
"{\n"
"	border-style:flat;\n"
"	background-image:url(:/bit/image/btn_cancel_w80_click.png);\n"
"}\n"
"/********************night**********************/\n"
"#pltCalendar[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	border-style:flat;\n"
"	background-image:url(:/bit/image/cancel-normal_night.png);\n"
"}\n"
"#pltCalendar[pltdismode=\"night\"] QPushButton:clicked\n"
"{\n"
"	border-style:flat"
                        ";\n"
"	background-image:url(:/bit/image/cancel-click_night.png);\n"
"}\n"
"QPushButton{padding-left:0px;text-align:center;\n"
"color: rgb(255, 255, 255);\n"
"}"));
        pb_ok = new QPushButton(widget);
        pb_ok->setObjectName(QStringLiteral("pb_ok"));
        pb_ok->setGeometry(QRect(287, 364, 80, 30));
        pb_ok->setFont(font);
        pb_ok->setStyleSheet(QLatin1String("/********************indoor**********************/\n"
"#pltCalendar[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/bit/image/btn_ok_w80_nor.png);\n"
"}\n"
"#pltCalendar[pltdismode=\"indoor\"] QPushButton:clicked\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/bit/image/btn_ok_w80_click.png);\n"
"}\n"
"/********************outdoor**********************/\n"
"#pltCalendar[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/bit/image/btn_ok_w80_nor.png);\n"
"}\n"
"#pltCalendar[pltdismode=\"outdoor\"] QPushButton:clicked\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/bit/image/btn_ok_w80_click.png);\n"
"}\n"
"/********************night**********************/\n"
"#pltCalendar[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	border-style:flat;\n"
"	background-image:url(:/bit/image/oK-normal_night.png);\n"
"}\n"
"#pltCalendar[pltdismode=\"night\"] QPushButton:clicked\n"
"{\n"
"	border-style:flat;\n"
"	backgroun"
                        "d-image:url(:/bit/image/oK-click_night.png);\n"
"}\n"
"QPushButton{padding-left:0px;text-align:center;\n"
"color: rgb(255, 255, 255);\n"
"}"));
        widget->raise();
        calendarWidget->raise();

        retranslateUi(pltCalendar);

        QMetaObject::connectSlotsByName(pltCalendar);
    } // setupUi

    void retranslateUi(QDialog *pltCalendar)
    {
        pltCalendar->setWindowTitle(QApplication::translate("pltCalendar", "Dialog", 0));
        pltCalendar->setProperty("pltdismode", QVariant(QApplication::translate("pltCalendar", "indoor", 0)));
        pb_cancel->setText(QApplication::translate("pltCalendar", "Cancel", 0));
        pb_ok->setText(QApplication::translate("pltCalendar", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class pltCalendar: public Ui_pltCalendar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLTCALENDAR_H
