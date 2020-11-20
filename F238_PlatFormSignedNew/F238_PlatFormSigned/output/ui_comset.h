/********************************************************************************
** Form generated from reading UI file 'comset.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMSET_H
#define UI_COMSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_comset
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
    QPushButton *interrefbtn;
    QPushButton *ext10btn;
    QPushButton *ext13btn;
    QPushButton *ext15btn;
    QPushButton *gpsrefbtn;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QPushButton *pushButton_15;
    QPushButton *pushButton_16;
    QPushButton *pushButton_17;
    QPushButton *pushButton_18;
    QPushButton *pushButton_19;
    QPushButton *pushButton_20;
    QButtonGroup *buttonGroup;
    QButtonGroup *buttonGroup_2;
    QButtonGroup *buttonGroup_3;

    void setupUi(QWidget *comset)
    {
        if (comset->objectName().isEmpty())
            comset->setObjectName(QStringLiteral("comset"));
        comset->resize(996, 589);
        comset->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255,1);"));
        widget_2 = new QWidget(comset);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(0, 0, 996, 720));
        widget_2->setStyleSheet(QLatin1String("QPushButton{\n"
"padding-left:10px;text-align:left;\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"font: 10pt \"Arial\";\n"
"font-weight:Bold;\n"
"border: none;\n"
"}\n"
"QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"QLabel{background-color:rgba(0,0,0,0);\n"
"font: 11pt \"Arial\";font-weight:Bold;}\n"
"\n"
"#comset[pltdismode=\"night\"] #widget_2\n"
"{	\n"
"background-color: rgb(0, 0, 0);\n"
"}\n"
"#comset[pltdismode=\"indoor\"] #widget_2\n"
"{	\n"
"background-color:white;\n"
"}"));
        line_4 = new QFrame(widget_2);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(22, 47, 250, 2));
        line_4->setStyleSheet(QLatin1String("#comset[pltdismode=\"indoor\"] #line_4\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#comset[pltdismode=\"night\"] #line_4\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(22, 26, 171, 17));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        label_4->setFont(font);
        label_4->setStyleSheet(QLatin1String("#comset[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(6,62,97,1);\n"
"	background-color: white;\n"
"}\n"
"#comset[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}"));
        line_5 = new QFrame(widget_2);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(322, 47, 250, 2));
        line_5->setStyleSheet(QLatin1String("#comset[pltdismode=\"indoor\"] #line_5\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#comset[pltdismode=\"night\"] #line_5\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(widget_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(322, 26, 121, 17));
        label_5->setFont(font);
        label_5->setStyleSheet(QLatin1String("#comset[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(6,62,97,1);\n"
"	background-color: white;\n"
"}\n"
"#comset[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}"));
        line_6 = new QFrame(widget_2);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(622, 47, 250, 2));
        line_6->setStyleSheet(QLatin1String("#comset[pltdismode=\"indoor\"] #line_6\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#comset[pltdismode=\"night\"] #line_6\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(widget_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(622, 27, 101, 17));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        label_6->setFont(font1);
        label_6->setStyleSheet(QLatin1String("#comset[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(6,62,97,1);\n"
"	background-color: white;\n"
"}\n"
"#comset[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}"));
        line_7 = new QFrame(widget_2);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setGeometry(QRect(22, 311, 250, 2));
        line_7->setStyleSheet(QLatin1String("#comset[pltdismode=\"indoor\"] #line_7\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#comset[pltdismode=\"night\"] #line_7\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(widget_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(22, 290, 81, 17));
        label_7->setFont(font1);
        label_7->setStyleSheet(QLatin1String("#comset[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(6,62,97,1);\n"
"	background-color: white;\n"
"}\n"
"#comset[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}"));
        interrefbtn = new QPushButton(widget_2);
        buttonGroup = new QButtonGroup(comset);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(interrefbtn);
        interrefbtn->setObjectName(QStringLiteral("interrefbtn"));
        interrefbtn->setGeometry(QRect(30, 68, 160, 34));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setItalic(false);
        font2.setWeight(75);
        interrefbtn->setFont(font2);
        interrefbtn->setLayoutDirection(Qt::LeftToRight);
        interrefbtn->setStyleSheet(QLatin1String("#comset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#comset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"QPushButton{\n"
"padding-left:10px;text-align:left;\n"
"font: 10pt \"Arial\";\n"
"font-weight:Bold;\n"
"}"));
        interrefbtn->setCheckable(true);
        interrefbtn->setChecked(true);
        ext10btn = new QPushButton(widget_2);
        buttonGroup->addButton(ext10btn);
        ext10btn->setObjectName(QStringLiteral("ext10btn"));
        ext10btn->setGeometry(QRect(30, 105, 160, 34));
        ext10btn->setStyleSheet(QLatin1String("#comset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#comset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"QPushButton{\n"
"padding-left:10px;text-align:left;\n"
"font: 10pt \"Arial\";\n"
"font-weight:Bold;\n"
"}"));
        ext10btn->setCheckable(true);
        ext13btn = new QPushButton(widget_2);
        buttonGroup->addButton(ext13btn);
        ext13btn->setObjectName(QStringLiteral("ext13btn"));
        ext13btn->setGeometry(QRect(30, 142, 160, 34));
        ext13btn->setStyleSheet(QLatin1String("#comset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#comset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"QPushButton{\n"
"padding-left:10px;text-align:left;\n"
"font: 10pt \"Arial\";\n"
"font-weight:Bold;\n"
"}"));
        ext13btn->setCheckable(true);
        ext15btn = new QPushButton(widget_2);
        buttonGroup->addButton(ext15btn);
        ext15btn->setObjectName(QStringLiteral("ext15btn"));
        ext15btn->setGeometry(QRect(30, 179, 160, 34));
        ext15btn->setStyleSheet(QLatin1String("#comset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#comset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"QPushButton{\n"
"padding-left:10px;text-align:left;\n"
"font: 10pt \"Arial\";\n"
"font-weight:Bold;\n"
"}"));
        ext15btn->setCheckable(true);
        gpsrefbtn = new QPushButton(widget_2);
        buttonGroup->addButton(gpsrefbtn);
        gpsrefbtn->setObjectName(QStringLiteral("gpsrefbtn"));
        gpsrefbtn->setGeometry(QRect(30, 216, 160, 34));
        gpsrefbtn->setStyleSheet(QLatin1String("#comset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#comset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"QPushButton{\n"
"padding-left:10px;text-align:left;\n"
"font: 10pt \"Arial\";\n"
"font-weight:Bold;\n"
"}"));
        gpsrefbtn->setCheckable(true);
        pushButton_12 = new QPushButton(widget_2);
        buttonGroup_2 = new QButtonGroup(comset);
        buttonGroup_2->setObjectName(QStringLiteral("buttonGroup_2"));
        buttonGroup_2->addButton(pushButton_12);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));
        pushButton_12->setGeometry(QRect(330, 68, 160, 34));
        pushButton_12->setStyleSheet(QLatin1String("#comset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#comset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton:checked\n"
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
        buttonGroup_2->addButton(pushButton_13);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));
        pushButton_13->setGeometry(QRect(330, 105, 160, 34));
        pushButton_13->setStyleSheet(QLatin1String("#comset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#comset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton:checked\n"
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
        buttonGroup_2->addButton(pushButton_14);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));
        pushButton_14->setGeometry(QRect(330, 142, 160, 34));
        pushButton_14->setStyleSheet(QLatin1String("#comset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#comset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton:checked\n"
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
        pushButton_15 = new QPushButton(widget_2);
        buttonGroup_3 = new QButtonGroup(comset);
        buttonGroup_3->setObjectName(QStringLiteral("buttonGroup_3"));
        buttonGroup_3->addButton(pushButton_15);
        pushButton_15->setObjectName(QStringLiteral("pushButton_15"));
        pushButton_15->setEnabled(false);
        pushButton_15->setGeometry(QRect(630, 68, 160, 34));
        pushButton_15->setStyleSheet(QLatin1String("#comset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"/*background-color: rgb(211, 211, 211);*/\n"
"	background-color: rgb(238, 238, 236);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#comset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"QPushButton{\n"
"padding-left:10px;text-align:left;\n"
"font: 10pt \"Arial\";\n"
"font-weight:Bold;\n"
"}"));
        pushButton_15->setCheckable(true);
        pushButton_16 = new QPushButton(widget_2);
        buttonGroup_3->addButton(pushButton_16);
        pushButton_16->setObjectName(QStringLiteral("pushButton_16"));
        pushButton_16->setGeometry(QRect(630, 105, 160, 34));
        pushButton_16->setStyleSheet(QLatin1String("#comset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#comset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"QPushButton{\n"
"padding-left:10px;text-align:left;\n"
"font: 10pt \"Arial\";\n"
"font-weight:Bold;\n"
"}"));
        pushButton_16->setCheckable(true);
        pushButton_16->setChecked(true);
        pushButton_17 = new QPushButton(widget_2);
        buttonGroup_3->addButton(pushButton_17);
        pushButton_17->setObjectName(QStringLiteral("pushButton_17"));
        pushButton_17->setEnabled(false);
        pushButton_17->setGeometry(QRect(630, 142, 160, 34));
        pushButton_17->setStyleSheet(QLatin1String("#comset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"/*background-color: rgb(211, 211, 211);*/\n"
"	background-color: rgb(238, 238, 236);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#comset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"QPushButton{\n"
"padding-left:10px;text-align:left;\n"
"font: 10pt \"Arial\";\n"
"font-weight:Bold;\n"
"}"));
        pushButton_17->setCheckable(true);
        pushButton_18 = new QPushButton(widget_2);
        buttonGroup_3->addButton(pushButton_18);
        pushButton_18->setObjectName(QStringLiteral("pushButton_18"));
        pushButton_18->setEnabled(false);
        pushButton_18->setGeometry(QRect(630, 179, 160, 34));
        pushButton_18->setStyleSheet(QLatin1String("#comset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"/*background-color: rgb(211, 211, 211);*/\n"
"	background-color: rgb(238, 238, 236);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#comset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"QPushButton{\n"
"padding-left:10px;text-align:left;\n"
"font: 10pt \"Arial\";\n"
"font-weight:Bold;\n"
"}"));
        pushButton_18->setCheckable(true);
        pushButton_19 = new QPushButton(widget_2);
        pushButton_19->setObjectName(QStringLiteral("pushButton_19"));
        pushButton_19->setEnabled(true);
        pushButton_19->setGeometry(QRect(30, 333, 180, 34));
        pushButton_19->setFont(font2);
        pushButton_19->setStyleSheet(QLatin1String("#comset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(85, 87, 83);\n"
"text-align:center;\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"border-image: url(:/bit/image/click_night.png);\n"
"text-align:center;\n"
"}"));
        pushButton_20 = new QPushButton(widget_2);
        pushButton_20->setObjectName(QStringLiteral("pushButton_20"));
        pushButton_20->setGeometry(QRect(330, 180, 160, 34));
        pushButton_20->setFont(font2);
        pushButton_20->setStyleSheet(QLatin1String("#comset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(85, 87, 83);\n"
"text-align:center;\n"
"}\n"
"#comset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"border-image: url(:/bit/image/click_night.png);\n"
"text-align:center;\n"
"}"));

        retranslateUi(comset);

        QMetaObject::connectSlotsByName(comset);
    } // setupUi

    void retranslateUi(QWidget *comset)
    {
        comset->setWindowTitle(QApplication::translate("comset", "Form", Q_NULLPTR));
        comset->setProperty("pltdismode", QVariant(QApplication::translate("comset", "indoor", Q_NULLPTR)));
        label_4->setText(QApplication::translate("comset", "Frequency Reference", Q_NULLPTR));
        label_5->setText(QApplication::translate("comset", "Power on/Preset ", Q_NULLPTR));
        label_6->setText(QApplication::translate("comset", "Language", Q_NULLPTR));
        label_7->setText(QApplication::translate("comset", "Upgrade", Q_NULLPTR));
        interrefbtn->setText(QApplication::translate("comset", "Internal", Q_NULLPTR));
        ext10btn->setText(QApplication::translate("comset", "External 10 MHz", Q_NULLPTR));
        ext13btn->setText(QApplication::translate("comset", "External 13 MHz", Q_NULLPTR));
        ext15btn->setText(QApplication::translate("comset", "External 15 MHz", Q_NULLPTR));
        gpsrefbtn->setText(QApplication::translate("comset", "GPS", Q_NULLPTR));
        pushButton_12->setText(QApplication::translate("comset", "Factory Default ", Q_NULLPTR));
        pushButton_13->setText(QApplication::translate("comset", "Last", Q_NULLPTR));
        pushButton_14->setText(QApplication::translate("comset", "User", Q_NULLPTR));
        pushButton_15->setText(QApplication::translate("comset", "Chinese ", Q_NULLPTR));
        pushButton_16->setText(QApplication::translate("comset", "English", Q_NULLPTR));
        pushButton_17->setText(QApplication::translate("comset", "Japanese ", Q_NULLPTR));
        pushButton_18->setText(QApplication::translate("comset", "Korean", Q_NULLPTR));
        pushButton_19->setText(QApplication::translate("comset", "Upgrade", Q_NULLPTR));
        pushButton_20->setText(QApplication::translate("comset", "Save User Preset", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class comset: public Ui_comset {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMSET_H
