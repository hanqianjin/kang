/********************************************************************************
** Form generated from reading UI file 'dsdtset.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DSDTSET_H
#define UI_DSDTSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include <focuslinedit.h>

QT_BEGIN_NAMESPACE

class Ui_dsdtset
{
public:
    QWidget *widget_2;
    QFrame *line_4;
    QLabel *label_4;
    QFrame *line_5;
    QLabel *label_5;
    QFrame *line_6;
    QLabel *label_6;
    QFrame *line_7;
    QLabel *label_7;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QLabel *label_9;
    QFrame *line_9;
    QPushButton *soundswithbtn;
    QSlider *horizontalSlider;
    QPushButton *date1btn;
    QPushButton *date2btn;
    QPushButton *date3btn;
    QSlider *horizontalSlider_2;
    QPushButton *keybeepbtn;
    QLabel *label_10;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    focuslinedit *DateEdit;
    focuslinedit *TimeEdit;
    QButtonGroup *buttonGroup_2;
    QButtonGroup *buttonGroup;
    QButtonGroup *buttonGroup_3;

    void setupUi(QWidget *dsdtset)
    {
        if (dsdtset->objectName().isEmpty())
            dsdtset->setObjectName(QStringLiteral("dsdtset"));
        dsdtset->resize(996, 598);
        dsdtset->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255,1);"));
        widget_2 = new QWidget(dsdtset);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(0, 0, 996, 598));
        widget_2->setStyleSheet(QLatin1String("QLabel{font: 11pt \"Arial\";font-weight:Bold;}\n"
"QPushButton{border: none;}\n"
"\n"
"#horizontalSlider_2::groove:horizontal {\n"
"border: flat;\n"
"background: transparent;\n"
"height: 40px;\n"
"}\n"
"#horizontalSlider_2{\n"
"   border: flat;\n"
"background-color: transparent;\n"
"}\n"
"#horizontalSlider_2::handle:horizontal {\n"
"border: flat;\n"
"width: 14px;\n"
"height:35px;\n"
"margin-top: 2px;\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] #widget_2\n"
"{	\n"
"background-color: rgb(0, 0, 0);\n"
"}\n"
"#dsdtset[pltdismode=\"indoor\"] #widget_2\n"
"{	\n"
"background-color:white;\n"
"}"));
        line_4 = new QFrame(widget_2);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(22, 47, 250, 2));
        line_4->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] #line_4\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] #line_4\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_4->setLineWidth(0);
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(22, 26, 153, 17));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(11);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        label_4->setFont(font);
        label_4->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(6,62,97,1);\n"
"	background-color: white;\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}"));
        line_5 = new QFrame(widget_2);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(322, 47, 250, 2));
        line_5->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] #line_5\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] #line_5\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_5->setLineWidth(0);
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(widget_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(322, 26, 111, 17));
        label_5->setFont(font);
        label_5->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(6,62,97,1);\n"
"	background-color: white;\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}"));
        line_6 = new QFrame(widget_2);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(622, 47, 250, 2));
        line_6->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] #line_6\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] #line_6\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_6->setLineWidth(0);
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(widget_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(622, 27, 161, 17));
        label_6->setFont(font);
        label_6->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(6,62,97,1);\n"
"	background-color: white;\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}"));
        line_7 = new QFrame(widget_2);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setGeometry(QRect(22, 311, 250, 2));
        line_7->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] #line_7\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] #line_7\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_7->setLineWidth(0);
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(widget_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(22, 290, 61, 17));
        label_7->setFont(font);
        label_7->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(6,62,97,1);\n"
"	background-color: white;\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}"));
        pushButton_7 = new QPushButton(widget_2);
        buttonGroup_2 = new QButtonGroup(dsdtset);
        buttonGroup_2->setObjectName(QStringLiteral("buttonGroup_2"));
        buttonGroup_2->addButton(pushButton_7);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(30, 68, 160, 34));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        pushButton_7->setFont(font1);
        pushButton_7->setLayoutDirection(Qt::LeftToRight);
        pushButton_7->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#dsdtset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"QPushButton{\n"
"padding-left:10px;text-align:left;\n"
"font: 10pt \"Arial\";\n"
"font-weight:Bold;\n"
"}"));
        pushButton_7->setCheckable(true);
        pushButton_7->setChecked(true);
        pushButton_8 = new QPushButton(widget_2);
        buttonGroup_2->addButton(pushButton_8);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(30, 105, 160, 34));
        pushButton_8->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#dsdtset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"QPushButton{\n"
"padding-left:10px;text-align:left;\n"
"font: 10pt \"Arial\";\n"
"font-weight:Bold;\n"
"}"));
        pushButton_8->setCheckable(true);
        pushButton_9 = new QPushButton(widget_2);
        buttonGroup_2->addButton(pushButton_9);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setGeometry(QRect(30, 142, 160, 34));
        pushButton_9->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#dsdtset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"QPushButton{\n"
"padding-left:10px;text-align:left;\n"
"font: 10pt \"Arial\";\n"
"font-weight:Bold;\n"
"}"));
        pushButton_9->setCheckable(true);
        pushButton_10 = new QPushButton(widget_2);
        buttonGroup_2->addButton(pushButton_10);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        pushButton_10->setGeometry(QRect(30, 179, 160, 34));
        pushButton_10->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#dsdtset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"QPushButton{\n"
"padding-left:10px;text-align:left;\n"
"font: 10pt \"Arial\";\n"
"font-weight:Bold;\n"
"}"));
        pushButton_10->setCheckable(true);
        pushButton_12 = new QPushButton(widget_2);
        buttonGroup_3 = new QButtonGroup(dsdtset);
        buttonGroup_3->setObjectName(QStringLiteral("buttonGroup_3"));
        buttonGroup_3->addButton(pushButton_12);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));
        pushButton_12->setGeometry(QRect(330, 68, 160, 34));
        pushButton_12->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#dsdtset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"QPushButton{\n"
"padding-left:10px;text-align:left;\n"
"font: 10pt \"Arial\";\n"
"font-weight:Bold;\n"
"}"));
        pushButton_12->setCheckable(true);
        pushButton_12->setChecked(true);
        pushButton_13 = new QPushButton(widget_2);
        buttonGroup_3->addButton(pushButton_13);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));
        pushButton_13->setGeometry(QRect(330, 105, 160, 34));
        pushButton_13->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#dsdtset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"QPushButton{\n"
"padding-left:10px;text-align:left;\n"
"font: 10pt \"Arial\";\n"
"font-weight:Bold;\n"
"}"));
        pushButton_13->setCheckable(true);
        pushButton_14 = new QPushButton(widget_2);
        buttonGroup_3->addButton(pushButton_14);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));
        pushButton_14->setGeometry(QRect(330, 142, 160, 34));
        pushButton_14->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#dsdtset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"QPushButton{\n"
"padding-left:10px;text-align:left;\n"
"font: 10pt \"Arial\";\n"
"font-weight:Bold;\n"
"}"));
        pushButton_14->setCheckable(true);
        label_9 = new QLabel(widget_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(622, 290, 77, 17));
        label_9->setFont(font);
        label_9->setStyleSheet(QLatin1String(" #dsdtset[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(6,62,97,1);\n"
"	background-color: white;\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}"));
        line_9 = new QFrame(widget_2);
        line_9->setObjectName(QStringLiteral("line_9"));
        line_9->setGeometry(QRect(622, 311, 250, 2));
        line_9->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] #line_9\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] #line_9\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_9->setLineWidth(0);
        line_9->setFrameShape(QFrame::HLine);
        line_9->setFrameShadow(QFrame::Sunken);
        soundswithbtn = new QPushButton(widget_2);
        soundswithbtn->setObjectName(QStringLiteral("soundswithbtn"));
        soundswithbtn->setGeometry(QRect(630, 346, 46, 46));
        soundswithbtn->setLayoutDirection(Qt::LeftToRight);
        soundswithbtn->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	border-image: url(:/bit/image/icn_sound.png);\n"
"}"));
        horizontalSlider = new QSlider(widget_2);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(630, 69, 250, 40));
        horizontalSlider->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] QSlider\n"
"{border-image: url(:/bit/image/brightness_bar.png);}\n"
"#dsdtset[pltdismode=\"night\"] QSlider\n"
"{border-image: url(:/bit/image/brightness_night_bar.png);}\n"
"\n"
"QSlider::groove:horizontal {\n"
"/*border: 1px solid #bbb;*/\n"
"background: transparent;\n"
"height: 40px;\n"
"border-radius: 4px;\n"
"}\n"
"#dsdtset[pltdismode=\"indoor\"] QSlider::handle:horizontal {\n"
"border: flat;\n"
"width: 7px;\n"
"height:35px;\n"
"margin-top: 2px;\n"
"background-image: url(:/bit/image/handler_nor.png);\n"
"}\n"
"#dsdtset[pltdismode=\"indoor\"] QSlider::handle:horizontal:pressed{\n"
"background-image: url(:/bit/image/handler_click.png);\n"
"}\n"
"\n"
"#dsdtset[pltdismode=\"night\"] QSlider::handle:horizontal {\n"
"border: flat;\n"
"width: 7px;\n"
"height:35px;\n"
"margin-top: 2px;\n"
"background-image: url(:/bit/image/hand_night_nor.png);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QSlider::handle:horizontal:pressed{\n"
"background-image: url(:/bit/image/hand_night_click.png);\n"
""
                        "}"));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(5);
        horizontalSlider->setPageStep(1);
        horizontalSlider->setValue(2);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::NoTicks);
        horizontalSlider->setTickInterval(0);
        date1btn = new QPushButton(widget_2);
        buttonGroup = new QButtonGroup(dsdtset);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(date1btn);
        date1btn->setObjectName(QStringLiteral("date1btn"));
        date1btn->setGeometry(QRect(30, 333, 160, 34));
        date1btn->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#dsdtset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"QPushButton{\n"
"padding-left:10px;text-align:left;\n"
"font: 10pt \"Arial\";\n"
"font-weight:Bold;\n"
"}"));
        date1btn->setCheckable(true);
        date2btn = new QPushButton(widget_2);
        buttonGroup->addButton(date2btn);
        date2btn->setObjectName(QStringLiteral("date2btn"));
        date2btn->setGeometry(QRect(30, 370, 160, 34));
        date2btn->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#dsdtset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"QPushButton{\n"
"padding-left:10px;text-align:left;\n"
"font: 10pt \"Arial\";\n"
"font-weight:Bold;\n"
"}"));
        date2btn->setCheckable(true);
        date3btn = new QPushButton(widget_2);
        buttonGroup->addButton(date3btn);
        date3btn->setObjectName(QStringLiteral("date3btn"));
        date3btn->setGeometry(QRect(30, 407, 160, 34));
        date3btn->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#dsdtset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"QPushButton{\n"
"padding-left:10px;text-align:left;\n"
"font: 10pt \"Arial\";\n"
"font-weight:Bold;\n"
"}"));
        date3btn->setCheckable(true);
        date3btn->setChecked(true);
        horizontalSlider_2 = new QSlider(widget_2);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(676, 333, 190, 48));
        horizontalSlider_2->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] #horizontalSlider_2\n"
"{\n"
"	background-image: url(:/bit/image/sound_3.png);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] #horizontalSlider_2\n"
"{\n"
"	background-image: url(:/bit/image/VOICE3.png);\n"
"}"));
        horizontalSlider_2->setMaximum(9);
        horizontalSlider_2->setPageStep(1);
        horizontalSlider_2->setValue(4);
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        keybeepbtn = new QPushButton(widget_2);
        keybeepbtn->setObjectName(QStringLiteral("keybeepbtn"));
        keybeepbtn->setGeometry(QRect(630, 470, 90, 30));
        keybeepbtn->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/btn_radio_off_w90.png);\n"
"border-style: flat;\n"
"	background-color: transparent;\n"
"}\n"
"\n"
""));
        keybeepbtn->setFlat(false);
        label_10 = new QLabel(widget_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(630, 440, 77, 17));
        label_10->setFont(font);
        label_10->setStyleSheet(QLatin1String(" #dsdtset[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(6,62,97,1);\n"
"	background-color: white;\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}"));
        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(188, 472, 80, 34));
        pushButton->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	font:75 15px \"Arial\";\n"
"	color:white;\n"
"	border-image: url(:/bit/image/keyBoard/night/btn_w70_normal.png);\n"
"}\n"
"QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_w55_click.png);\n"
"}\n"
"\n"
"#dsdtset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	font:75 15px \"Arial\";\n"
"	color: rgb(250,218,166);\n"
"	border-image: url(:/bit/image/click_night.png);\n"
"}"));
        pushButton->setFlat(false);
        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(488, 472, 80, 34));
        pushButton_2->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	font:75 15px \"Arial\";\n"
"	color:white;\n"
"	border-image: url(:/bit/image/keyBoard/night/btn_w70_normal.png);\n"
"}\n"
"QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_w55_click.png);\n"
"}\n"
"\n"
"#dsdtset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	font:75 15px \"Arial\";\n"
"	color: rgb(250,218,166);\n"
"	border-image: url(:/bit/image/click_night.png);\n"
"}"));
        DateEdit = new focuslinedit(widget_2);
        DateEdit->setObjectName(QStringLiteral("DateEdit"));
        DateEdit->setGeometry(QRect(28, 472, 160, 34));
        DateEdit->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] QLineEdit\n"
"{\n"
"font:75 18px \"Arial\";\n"
"border-image: url(:/bit/image/input_box_w180.png);\n"
"padding-left:10px;\n"
"color: rgba(0, 42, 94, 1);\n"
"}\n"
"#dsdtset[pltdismode=\"outdoor\"] QLineEdit\n"
"{\n"
"font:75 18px \"Arial\";\n"
"border-image: url(:/bit/image/input_box_w180.png);\n"
"padding-left:10px;\n"
"color: rgba(0, 42, 94, 1);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QLineEdit\n"
"{\n"
"border-image: url(:/bit/image/input_box_night.png);\n"
"font:75 18px \"Arial\";\n"
"padding-left:10px;\n"
"color: rgba(7,97,116, 1);\n"
"}"));
        DateEdit->setReadOnly(true);
        TimeEdit = new focuslinedit(widget_2);
        TimeEdit->setObjectName(QStringLiteral("TimeEdit"));
        TimeEdit->setGeometry(QRect(328, 472, 160, 34));
        TimeEdit->setStyleSheet(QLatin1String("#dsdtset[pltdismode=\"indoor\"] QLineEdit\n"
"{\n"
"font:75 18px \"Arial\";\n"
"border-image: url(:/bit/image/input_box_w180.png);\n"
"padding-left:10px;\n"
"color: rgba(0, 42, 94, 1);\n"
"}\n"
"#dsdtset[pltdismode=\"outdoor\"] QLineEdit\n"
"{\n"
"font:75 18px \"Arial\";\n"
"border-image: url(:/bit/image/input_box_w180.png);\n"
"padding-left:10px;\n"
"color: rgba(0, 42, 94, 1);\n"
"}\n"
"#dsdtset[pltdismode=\"night\"] QLineEdit\n"
"{\n"
"font:75 18px \"Arial\";\n"
"border-image: url(:/bit/image/input_box_night.png);\n"
"padding-left:10px;\n"
"color: rgba(7,97,116, 1);\n"
"}"));
        TimeEdit->setReadOnly(true);

        retranslateUi(dsdtset);

        QMetaObject::connectSlotsByName(dsdtset);
    } // setupUi

    void retranslateUi(QWidget *dsdtset)
    {
        dsdtset->setWindowTitle(QApplication::translate("dsdtset", "Form", Q_NULLPTR));
        dsdtset->setProperty("pltdismode", QVariant(QApplication::translate("dsdtset", "indoor", Q_NULLPTR)));
        label_4->setText(QApplication::translate("dsdtset", "Sleep Time", Q_NULLPTR));
        label_5->setText(QApplication::translate("dsdtset", "Display Mode", Q_NULLPTR));
        label_6->setText(QApplication::translate("dsdtset", "LCD Brightness", Q_NULLPTR));
        label_7->setText(QApplication::translate("dsdtset", "Date", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("dsdtset", "Off", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("dsdtset", "10 min", Q_NULLPTR));
        pushButton_9->setText(QApplication::translate("dsdtset", "20 min", Q_NULLPTR));
        pushButton_10->setText(QApplication::translate("dsdtset", "30 min", Q_NULLPTR));
        pushButton_12->setText(QApplication::translate("dsdtset", "Indoor", Q_NULLPTR));
        pushButton_13->setText(QApplication::translate("dsdtset", "Outdoor", Q_NULLPTR));
        pushButton_14->setText(QApplication::translate("dsdtset", "Night", Q_NULLPTR));
        label_9->setText(QApplication::translate("dsdtset", "Sound", Q_NULLPTR));
        soundswithbtn->setText(QString());
        date1btn->setText(QApplication::translate("dsdtset", "Day - Month - Year", Q_NULLPTR));
        date2btn->setText(QApplication::translate("dsdtset", "Month - Day - Year", Q_NULLPTR));
        date3btn->setText(QApplication::translate("dsdtset", "Year - Month - Day", Q_NULLPTR));
        keybeepbtn->setText(QString());
        label_10->setText(QApplication::translate("dsdtset", "Key Beep", Q_NULLPTR));
        pushButton->setText(QApplication::translate("dsdtset", "Clear", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("dsdtset", "Clear", Q_NULLPTR));
        DateEdit->setText(QApplication::translate("dsdtset", "2019 - 07 - 09", Q_NULLPTR));
        TimeEdit->setText(QApplication::translate("dsdtset", "01 : 02 : 01", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class dsdtset: public Ui_dsdtset {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DSDTSET_H
