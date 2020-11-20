/********************************************************************************
** Form generated from reading UI file 'networkset.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETWORKSET_H
#define UI_NETWORKSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include <focuslinedit.h>
#include <plugin/iplineedit.h>

QT_BEGIN_NAMESPACE

class Ui_networkset
{
public:
    QWidget *widget_2;
    QFrame *line_4;
    QLabel *label_4;
    QFrame *line_5;
    QLabel *label_5;
    QFrame *line_6;
    QLabel *label_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *gpsbtn;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label_12;
    QLabel *label_11;
    IPLineEdit *lineEdit;
    QLabel *label_13;
    QPushButton *netsetbtn;
    QLabel *label_14;
    QPushButton *netsetbtn_2;
    QLabel *label_10;
    IPLineEdit *lineEdit_4;
    IPLineEdit *lineEdit_5;
    IPLineEdit *lineEdit_6;
    QLabel *label_15;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    IPLineEdit *lineEdit_7;
    IPLineEdit *lineEdit_8;
    IPLineEdit *lineEdit_9;
    QLabel *label_23;
    IPLineEdit *lineEdit_2;
    QLabel *label_24;
    QLabel *label_25;
    IPLineEdit *lineEdit_10;
    IPLineEdit *lineEdit_11;
    IPLineEdit *lineEdit_12;
    QLabel *label_26;
    IPLineEdit *lineEdit_3;
    focuslinedit *lineEdit_14;
    QWidget *page_2;
    QPushButton *blutoothofbtn;
    QLabel *lblBluMode;
    QPushButton *blu_4;
    focuslinedit *EditDevName_2;
    QPushButton *blu_3;
    QLabel *lblBluList;
    QPushButton *blu_1;
    QPushButton *blu_5;
    QPushButton *blu_2;
    QPushButton *pb_blu_refresh;
    QLabel *lblDevName;
    QPushButton *pb_AMP;
    QPushButton *pb_BLE;
    QWidget *page_3;
    QPushButton *wifiofbtn;
    QPushButton *pb_wifi_refresh;
    QLabel *lblWifiLIst;
    focuslinedit *EditDevName;
    QLabel *lblWifiLIst_4;
    QTableWidget *tableWidget;
    QLabel *lblCurWifi;
    QLabel *label_28;
    QLabel *label_29;
    QLabel *label_30;
    QLabel *label_31;
    QLabel *label_32;
    QLabel *label_33;
    QLabel *label_34;
    QLabel *label_35;
    QLabel *label_36;
    QLabel *label_37;
    QLabel *label_38;
    QLabel *label_39;
    QLabel *label_40;
    QLabel *label_41;
    QLabel *label_42;
    QLabel *label_43;
    QLabel *label_44;
    QLabel *label_45;
    QLineEdit *lineEdit_13;
    QLabel *label_27;
    QPushButton *usbTest;
    QLabel *lblwS;
    QLabel *lblrSpeed;
    QLabel *lblrS;
    QLabel *lblwSpeed;
    QWidget *usbErrorWid;
    QLabel *label_16;
    QLabel *label_46;
    QFrame *line_7;
    QButtonGroup *buttonGroup_2;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *networkset)
    {
        if (networkset->objectName().isEmpty())
            networkset->setObjectName(QStringLiteral("networkset"));
        networkset->resize(996, 598);
        networkset->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255,1);"));
        widget_2 = new QWidget(networkset);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(0, 0, 996, 598));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        font.setKerning(true);
        widget_2->setFont(font);
        widget_2->setCursor(QCursor(Qt::BlankCursor));
        widget_2->setStyleSheet(QLatin1String("QPushButton{font: 10pt \"Arial\";font-weight:Bold;}\n"
"QLabel{background-color:rgba(0,0,0,0);}\n"
"QPushButton{border: none;}\n"
"#networkset[pltdismode=\"night\"] #widget_2\n"
"{	\n"
"background-color: rgb(0, 0, 0);\n"
"}\n"
"#networkset[pltdismode=\"indoor\"] #widget_2\n"
"{	\n"
"background-color:white;\n"
"}\n"
"#networkset[pltdismode=\"indoor\"] QLabel[mod=\"1\"]\n"
"{\n"
" color:rgba(127,127,127,1);\n"
"}\n"
"#networkset[pltdismode=\"night\"] QLabel[mod=\"1\"]\n"
"{\n"
" color:rgba(88,77,58,1);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"indoor\"] QLabel[mod=\"2\"]\n"
"{\n"
"color: rgba(0, 42, 94, 1);\n"
"}\n"
"#networkset[pltdismode=\"night\"] QLabel[mod=\"2\"]\n"
"{\n"
"color: rgba(7,97,116, 1); \n"
"}\n"
"\n"
"#networkset[pltdismode=\"indoor\"] QLabel[mod=\"3\"]\n"
"{\n"
"border-image: url(:/bit/image/input_box_w180.png);\n"
"}\n"
"#networkset[pltdismode=\"night\"] QLabel[mod=\"3\"]\n"
"{\n"
"background-color: rgba(24,23,20,1);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"indoor\"] QLabel[mod=\"4\"]\n"
"{\n"
""
                        "border-image: url(:/bit/image/input_box_w180.png);\n"
"padding-left:10px;\n"
"color: rgba(161, 161, 161, 1);\n"
"}\n"
"#networkset[pltdismode=\"night\"] QLabel[mod=\"4\"]\n"
"{\n"
"background-color: rgba(24,23,20,1);\n"
"padding-left:10px;\n"
"color: rgba(88,77,58, 1);\n"
"}\n"
"\n"
""));
        line_4 = new QFrame(widget_2);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(22, 47, 250, 2));
        line_4->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] #line_4\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#networkset[pltdismode=\"night\"] #line_4\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(22, 26, 153, 17));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        label_4->setFont(font1);
        label_4->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(6,62,97,1);\n"
"	background-color: white;\n"
"}\n"
"#networkset[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}"));
        line_5 = new QFrame(widget_2);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(322, 47, 250, 2));
        line_5->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] #line_5\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#networkset[pltdismode=\"night\"] #line_5\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(widget_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(322, 26, 171, 17));
        label_5->setFont(font1);
        label_5->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(6,62,97,1);\n"
"	background-color: white;\n"
"}\n"
"#networkset[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}"));
        line_6 = new QFrame(widget_2);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(622, 47, 250, 2));
        line_6->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] #line_6\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#networkset[pltdismode=\"night\"] #line_6\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);
        label_6 = new QLabel(widget_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(622, 27, 161, 17));
        label_6->setFont(font1);
        label_6->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(6,62,97,1);\n"
"	background-color: white;\n"
"}\n"
"#networkset[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}"));
        pushButton_7 = new QPushButton(widget_2);
        buttonGroup = new QButtonGroup(networkset);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(pushButton_7);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(30, 68, 160, 34));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setItalic(false);
        font2.setWeight(75);
        pushButton_7->setFont(font2);
        pushButton_7->setLayoutDirection(Qt::LeftToRight);
        pushButton_7->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"border-style:flat;\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"}\n"
"#networkset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"border-style:flat;\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#networkset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"border-style:flat;\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#networkset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"QPushButton{\n"
"padding-left:10px;\n"
"text-align:left;\n"
"font: 10pt \"Arial\";\n"
"font-weight:Bold;\n"
"}"));
        pushButton_7->setCheckable(true);
        pushButton_7->setChecked(true);
        pushButton_8 = new QPushButton(widget_2);
        buttonGroup->addButton(pushButton_8);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setEnabled(false);
        pushButton_8->setGeometry(QRect(30, 105, 160, 34));
        pushButton_8->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"}\n"
"#networkset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#networkset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#networkset[pltdismode=\"night\"] QPushButton:checked\n"
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
        buttonGroup->addButton(pushButton_9);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setEnabled(true);
        pushButton_9->setGeometry(QRect(30, 142, 160, 34));
        pushButton_9->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"}\n"
"#networkset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#networkset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#networkset[pltdismode=\"night\"] QPushButton:checked\n"
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
        pushButton_9->setChecked(false);
        gpsbtn = new QPushButton(widget_2);
        gpsbtn->setObjectName(QStringLiteral("gpsbtn"));
        gpsbtn->setGeometry(QRect(630, 69, 90, 30));
        gpsbtn->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/btn_radio_off_w90.png);\n"
"}\n"
"QPushButton { border-style: flat;}"));
        label = new QLabel(widget_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(630, 119, 67, 17));
        QFont font3;
        font3.setFamily(QStringLiteral("Arial"));
        font3.setPointSize(10);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setWeight(50);
        label->setFont(font3);
        label->setStyleSheet(QStringLiteral(""));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(630, 137, 150, 34));
        QFont font4;
        font4.setFamily(QStringLiteral("Arial"));
        font4.setPointSize(14);
        label_2->setFont(font4);
        label_2->setStyleSheet(QStringLiteral(""));
        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(630, 179, 67, 17));
        label_3->setFont(font3);
        label_3->setStyleSheet(QStringLiteral(""));
        label_7 = new QLabel(widget_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(630, 201, 150, 34));
        label_7->setFont(font4);
        label_7->setStyleSheet(QStringLiteral(""));
        label_8 = new QLabel(widget_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(630, 243, 67, 17));
        label_8->setFont(font3);
        label_8->setStyleSheet(QStringLiteral(""));
        label_9 = new QLabel(widget_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(630, 265, 150, 34));
        label_9->setFont(font4);
        label_9->setStyleSheet(QStringLiteral(""));
        stackedWidget = new QStackedWidget(widget_2);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(322, 49, 259, 491));
        stackedWidget->setStyleSheet(QLatin1String("#networkset[pltdismode=\"night\"] #page,\n"
"#networkset[pltdismode=\"night\"] #page_2,\n"
"#networkset[pltdismode=\"night\"] #page_3\n"
"{	\n"
"background-color: rgb(0, 0, 0);\n"
"}\n"
"#networkset[pltdismode=\"indoor\"] #page,\n"
"#networkset[pltdismode=\"indoor\"] #page_2,\n"
"#networkset[pltdismode=\"indoor\"] #page_3\n"
"{	\n"
"background-color:white;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"indoor\"] QLineEdit\n"
"{	\n"
"border-style:flat;\n"
"background-color: rgba(243, 243, 243,0);\n"
"padding-left:10px;\n"
"color: rgba(0, 42, 94, 1);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QLineEdit\n"
"{	\n"
"border-style:flat;\n"
"background-color: rgba(24,23,20,0);\n"
"padding-left:10px;\n"
"color: rgb(7,97,116);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"indoor\"] #lineEdit_14\n"
"{\n"
"font:75 14pt \"Arial\";\n"
"border-image: url(:/bit/image/input_box_w180.png);\n"
"padding-left:10px;\n"
"color: rgba(0, 42, 94, 1);\n"
"}\n"
"#networkset[pltdismode=\"night\"] #lineEdit_14\n"
"{\n"
"font:75 14pt \"Arial\";\n"
""
                        "background-color: rgba(24,23,20,1);\n"
"padding-left:10px;\n"
"color: rgba(7,97,116, 1);\n"
"}"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setStyleSheet(QStringLiteral(""));
        label_12 = new QLabel(page);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(8, 83, 104, 15));
        label_12->setFont(font3);
        label_12->setStyleSheet(QStringLiteral(""));
        label_11 = new QLabel(page);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(8, 19, 104, 15));
        label_11->setFont(font3);
        label_11->setStyleSheet(QStringLiteral(""));
        lineEdit = new IPLineEdit(page);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(8, 37, 46, 34));
        lineEdit->setFont(font4);
        lineEdit->setCursor(QCursor(Qt::BlankCursor));
        lineEdit->setStyleSheet(QStringLiteral(""));
        label_13 = new QLabel(page);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(8, 147, 104, 15));
        label_13->setFont(font3);
        label_13->setStyleSheet(QStringLiteral(""));
        netsetbtn = new QPushButton(page);
        netsetbtn->setObjectName(QStringLiteral("netsetbtn"));
        netsetbtn->setGeometry(QRect(8, 226, 191, 34));
        netsetbtn->setFont(font2);
        netsetbtn->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(85, 87, 83);\n"
"text-align:center;\n"
"}\n"
"#networkset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"text-align:center;\n"
"border-image: url(:/bit/image/click_night.png);\n"
"}"));
        label_14 = new QLabel(page);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(10, 302, 104, 15));
        label_14->setFont(font3);
        label_14->setStyleSheet(QStringLiteral(""));
        netsetbtn_2 = new QPushButton(page);
        netsetbtn_2->setObjectName(QStringLiteral("netsetbtn_2"));
        netsetbtn_2->setGeometry(QRect(8, 380, 191, 34));
        netsetbtn_2->setFont(font2);
        netsetbtn_2->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(85, 87, 83);\n"
"text-align:center;\n"
"}\n"
"#networkset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"text-align:center;\n"
"border-image: url(:/bit/image/click_night.png);\n"
"}"));
        label_10 = new QLabel(page);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(8, 37, 191, 34));
        label_10->setStyleSheet(QStringLiteral(""));
        lineEdit_4 = new IPLineEdit(page);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(60, 37, 46, 34));
        lineEdit_4->setFont(font4);
        lineEdit_4->setCursor(QCursor(Qt::BlankCursor));
        lineEdit_4->setStyleSheet(QStringLiteral(""));
        lineEdit_5 = new IPLineEdit(page);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(106, 37, 46, 34));
        lineEdit_5->setFont(font4);
        lineEdit_5->setCursor(QCursor(Qt::BlankCursor));
        lineEdit_5->setStyleSheet(QStringLiteral(""));
        lineEdit_6 = new IPLineEdit(page);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(150, 37, 46, 34));
        lineEdit_6->setFont(font4);
        lineEdit_6->setCursor(QCursor(Qt::BlankCursor));
        lineEdit_6->setStyleSheet(QStringLiteral(""));
        label_15 = new QLabel(page);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(60, 37, 4, 34));
        QFont font5;
        font5.setPointSize(13);
        label_15->setFont(font5);
        label_15->setStyleSheet(QStringLiteral(""));
        label_17 = new QLabel(page);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(106, 37, 4, 34));
        label_17->setFont(font5);
        label_18 = new QLabel(page);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(150, 37, 4, 34));
        label_18->setFont(font5);
        label_19 = new QLabel(page);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(8, 101, 191, 34));
        label_19->setStyleSheet(QStringLiteral(""));
        label_20 = new QLabel(page);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(8, 165, 191, 34));
        label_20->setStyleSheet(QStringLiteral(""));
        label_21 = new QLabel(page);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(60, 101, 4, 34));
        label_21->setFont(font5);
        label_22 = new QLabel(page);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(106, 101, 4, 34));
        label_22->setFont(font5);
        lineEdit_7 = new IPLineEdit(page);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(106, 101, 46, 34));
        lineEdit_7->setFont(font4);
        lineEdit_7->setCursor(QCursor(Qt::BlankCursor));
        lineEdit_7->setStyleSheet(QStringLiteral(""));
        lineEdit_8 = new IPLineEdit(page);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));
        lineEdit_8->setGeometry(QRect(150, 101, 46, 34));
        lineEdit_8->setFont(font4);
        lineEdit_8->setCursor(QCursor(Qt::BlankCursor));
        lineEdit_8->setStyleSheet(QStringLiteral(""));
        lineEdit_9 = new IPLineEdit(page);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));
        lineEdit_9->setGeometry(QRect(60, 101, 46, 34));
        lineEdit_9->setFont(font4);
        lineEdit_9->setCursor(QCursor(Qt::BlankCursor));
        lineEdit_9->setStyleSheet(QStringLiteral(""));
        label_23 = new QLabel(page);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(150, 101, 4, 34));
        label_23->setFont(font5);
        lineEdit_2 = new IPLineEdit(page);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(8, 101, 46, 34));
        lineEdit_2->setFont(font4);
        lineEdit_2->setCursor(QCursor(Qt::BlankCursor));
        lineEdit_2->setStyleSheet(QStringLiteral(""));
        label_24 = new QLabel(page);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(60, 165, 4, 34));
        label_24->setFont(font5);
        label_25 = new QLabel(page);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(106, 165, 4, 34));
        label_25->setFont(font5);
        lineEdit_10 = new IPLineEdit(page);
        lineEdit_10->setObjectName(QStringLiteral("lineEdit_10"));
        lineEdit_10->setGeometry(QRect(106, 165, 46, 34));
        lineEdit_10->setFont(font4);
        lineEdit_10->setCursor(QCursor(Qt::BlankCursor));
        lineEdit_10->setStyleSheet(QStringLiteral(""));
        lineEdit_11 = new IPLineEdit(page);
        lineEdit_11->setObjectName(QStringLiteral("lineEdit_11"));
        lineEdit_11->setGeometry(QRect(150, 165, 46, 34));
        lineEdit_11->setFont(font4);
        lineEdit_11->setCursor(QCursor(Qt::BlankCursor));
        lineEdit_11->setStyleSheet(QStringLiteral(""));
        lineEdit_12 = new IPLineEdit(page);
        lineEdit_12->setObjectName(QStringLiteral("lineEdit_12"));
        lineEdit_12->setGeometry(QRect(60, 165, 46, 34));
        lineEdit_12->setFont(font4);
        lineEdit_12->setCursor(QCursor(Qt::BlankCursor));
        lineEdit_12->setStyleSheet(QStringLiteral(""));
        label_26 = new QLabel(page);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(150, 165, 4, 34));
        label_26->setFont(font5);
        lineEdit_3 = new IPLineEdit(page);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(8, 165, 46, 34));
        lineEdit_3->setFont(font4);
        lineEdit_3->setCursor(QCursor(Qt::BlankCursor));
        lineEdit_3->setStyleSheet(QStringLiteral(""));
        lineEdit_14 = new focuslinedit(page);
        lineEdit_14->setObjectName(QStringLiteral("lineEdit_14"));
        lineEdit_14->setGeometry(QRect(8, 320, 191, 34));
        QFont font6;
        font6.setFamily(QStringLiteral("Arial"));
        font6.setPointSize(14);
        font6.setBold(false);
        font6.setItalic(false);
        font6.setWeight(9);
        lineEdit_14->setFont(font6);
        lineEdit_14->setCursor(QCursor(Qt::BlankCursor));
        lineEdit_14->setStyleSheet(QStringLiteral(""));
        stackedWidget->addWidget(page);
        label_12->raise();
        label_11->raise();
        label_13->raise();
        netsetbtn->raise();
        label_14->raise();
        netsetbtn_2->raise();
        label_10->raise();
        lineEdit->raise();
        lineEdit_4->raise();
        lineEdit_5->raise();
        lineEdit_6->raise();
        label_15->raise();
        label_17->raise();
        label_18->raise();
        label_19->raise();
        label_20->raise();
        label_21->raise();
        label_22->raise();
        lineEdit_7->raise();
        lineEdit_8->raise();
        lineEdit_9->raise();
        label_23->raise();
        lineEdit_2->raise();
        label_24->raise();
        label_25->raise();
        lineEdit_10->raise();
        lineEdit_11->raise();
        lineEdit_12->raise();
        label_26->raise();
        lineEdit_3->raise();
        lineEdit_14->raise();
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        blutoothofbtn = new QPushButton(page_2);
        blutoothofbtn->setObjectName(QStringLiteral("blutoothofbtn"));
        blutoothofbtn->setGeometry(QRect(8, 21, 90, 30));
        blutoothofbtn->setStyleSheet(QLatin1String("QPushButton { border-style: flat;}\n"
"#networkset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"background-image: url(:/bit/image/btn_radio_off_w90.png);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"background-image: url(:/bit/image/btn_radio_off_w90.png);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"background-color:rgba(0,0,0,0);\n"
"background-image: url(:/bit/image/night_Off.png);\n"
"}"));
        blutoothofbtn->setCheckable(true);
        lblBluMode = new QLabel(page_2);
        lblBluMode->setObjectName(QStringLiteral("lblBluMode"));
        lblBluMode->setGeometry(QRect(10, 70, 104, 15));
        QFont font7;
        font7.setFamily(QStringLiteral("Arial"));
        font7.setBold(true);
        font7.setItalic(false);
        font7.setWeight(75);
        lblBluMode->setFont(font7);
        lblBluMode->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QLabel\n"
"{\n"
"color:rgba(127, 127, 127, 1);\n"
"font:75 13px \"Arial\";\n"
"font-weight:bold;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QLabel\n"
"{\n"
"color:rgba(127, 127, 127, 1);\n"
"font:75 13px \"Arial\";\n"
"font-weight:bold;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QLabel\n"
"{\n"
"color:rgba(88, 77, 58, 1);\n"
"font:75 13px \"Arial\";\n"
"font-weight:bold;\n"
"}\n"
"\n"
"\n"
"\n"
""));
        blu_4 = new QPushButton(page_2);
        blu_4->setObjectName(QStringLiteral("blu_4"));
        blu_4->setGeometry(QRect(8, 327, 250, 34));
        blu_4->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-color: rgba(211, 211, 211, 1);\n"
"	color:rgb(0,0,0);\n"
"	border:2px solid white;\n"
"	padding-left:10px;\n"
"}\n"
"#networkset[pltdismode=\"indoor\"]  QPushButton:checked\n"
"{\n"
"	font-weight:bold;	\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-color: rgba(211, 211, 211, 1);\n"
"	color:rgb(0,0,0);\n"
"	border:2px solid white;\n"
"	padding-left:10px;\n"
"}\n"
"#networkset[pltdismode=\"outdoor\"]  QPushButton:checked\n"
"{\n"
"	font-weight:bold;	\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color: rgba(24, 23, 20, 1);\n"
"	color:rgba(250, 218, 166, 1);\n"
"	border:2px solid black;\n"
"	padding-left:10px;\n"
"}\n"
"#networkset[pltdismode=\"night\"]  QPushButton:checked\n"
"{\n"
"	font-weight:bold;	\n"
"}\n"
"\n"
"\n"
""));
        EditDevName_2 = new focuslinedit(page_2);
        EditDevName_2->setObjectName(QStringLiteral("EditDevName_2"));
        EditDevName_2->setGeometry(QRect(8, 146, 250, 34));
        EditDevName_2->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QLineEdit\n"
"{\n"
"font:75 16px \"Arial\";\n"
"border-image: url(:/bit/image/input_box_w180.png);\n"
"padding-left:10px;\n"
"color: rgba(0, 42, 94, 1);\n"
"}\n"
"#networkset[pltdismode=\"outdoor\"] QLineEdit\n"
"{\n"
"font:75 16px \"Arial\";\n"
"border-image: url(:/bit/image/input_box_w180.png);\n"
"padding-left:10px;\n"
"color: rgba(0, 42, 94, 1);\n"
"}\n"
"#networkset[pltdismode=\"night\"] QLineEdit\n"
"{\n"
"font:75 16px \"Arial\";\n"
"background-color: rgba(24,23,20,1);\n"
"padding-left:10px;\n"
"color: rgba(7,97,116, 1);\n"
"}"));
        blu_3 = new QPushButton(page_2);
        blu_3->setObjectName(QStringLiteral("blu_3"));
        blu_3->setGeometry(QRect(8, 290, 250, 34));
        blu_3->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-color: rgba(211, 211, 211, 1);\n"
"	color:rgb(0,0,0);\n"
"	border:2px solid white;\n"
"	padding-left:10px;\n"
"}\n"
"#networkset[pltdismode=\"indoor\"]  QPushButton:checked\n"
"{\n"
"	font-weight:bold;	\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-color: rgba(211, 211, 211, 1);\n"
"	color:rgb(0,0,0);\n"
"	border:2px solid white;\n"
"	padding-left:10px;\n"
"}\n"
"#networkset[pltdismode=\"outdoor\"]  QPushButton:checked\n"
"{\n"
"	font-weight:bold;	\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color: rgba(24, 23, 20, 1);\n"
"	color:rgba(250, 218, 166, 1);\n"
"	border:2px solid black;\n"
"	padding-left:10px;\n"
"}\n"
"#networkset[pltdismode=\"night\"]  QPushButton:checked\n"
"{\n"
"	font-weight:bold;	\n"
"}\n"
"\n"
"\n"
""));
        lblBluList = new QLabel(page_2);
        lblBluList->setObjectName(QStringLiteral("lblBluList"));
        lblBluList->setGeometry(QRect(8, 198, 104, 15));
        lblBluList->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QLabel\n"
"{\n"
"color:rgba(127, 127, 127, 1);\n"
"font:75 13px \"Arial\";\n"
"font-weight:bold;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QLabel\n"
"{\n"
"color:rgba(127, 127, 127, 1);\n"
"font:75 13px \"Arial\";\n"
"font-weight:bold;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QLabel\n"
"{\n"
"color:rgba(88, 77, 58, 1);\n"
"font:75 13px \"Arial\";\n"
"font-weight:bold;\n"
"}\n"
"\n"
"\n"
"\n"
""));
        blu_1 = new QPushButton(page_2);
        blu_1->setObjectName(QStringLiteral("blu_1"));
        blu_1->setGeometry(QRect(8, 216, 250, 34));
        blu_1->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-color: rgba(211, 211, 211, 1);\n"
"	color:rgb(0,0,0);\n"
"	border:2px solid white;\n"
"	padding-left:10px;\n"
"}\n"
"#networkset[pltdismode=\"indoor\"]  QPushButton:checked\n"
"{\n"
"	font-weight:bold;	\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-color: rgba(211, 211, 211, 1);\n"
"	color:rgb(0,0,0);\n"
"	border:2px solid white;\n"
"	padding-left:10px;\n"
"}\n"
"#networkset[pltdismode=\"outdoor\"]  QPushButton:checked\n"
"{\n"
"	font-weight:bold;	\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color: rgba(24, 23, 20, 1);\n"
"	color:rgba(250, 218, 166, 1);\n"
"	border:2px solid black;\n"
"	padding-left:10px;\n"
"}\n"
"#networkset[pltdismode=\"night\"]  QPushButton:checked\n"
"{\n"
"	font-weight:bold;	\n"
"}\n"
"\n"
"\n"
""));
        blu_1->setFlat(false);
        blu_5 = new QPushButton(page_2);
        blu_5->setObjectName(QStringLiteral("blu_5"));
        blu_5->setGeometry(QRect(8, 364, 250, 34));
        blu_5->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-color: rgba(211, 211, 211, 1);\n"
"	color:rgb(0,0,0);\n"
"	border:2px solid white;\n"
"	padding-left:10px;\n"
"}\n"
"#networkset[pltdismode=\"indoor\"]  QPushButton:checked\n"
"{\n"
"	font-weight:bold;	\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-color: rgba(211, 211, 211, 1);\n"
"	color:rgb(0,0,0);\n"
"	border:2px solid white;\n"
"	padding-left:10px;\n"
"}\n"
"#networkset[pltdismode=\"outdoor\"]  QPushButton:checked\n"
"{\n"
"	font-weight:bold;	\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color: rgba(24, 23, 20, 1);\n"
"	color:rgba(250, 218, 166, 1);\n"
"	border:2px solid black;\n"
"	padding-left:10px;\n"
"}\n"
"#networkset[pltdismode=\"night\"]  QPushButton:checked\n"
"{\n"
"	font-weight:bold;	\n"
"}\n"
"\n"
"\n"
""));
        blu_2 = new QPushButton(page_2);
        blu_2->setObjectName(QStringLiteral("blu_2"));
        blu_2->setGeometry(QRect(8, 253, 250, 34));
        blu_2->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-color: rgba(211, 211, 211, 1);\n"
"	color:rgb(0,0,0);\n"
"	border:2px solid white;\n"
"	padding-left:10px;\n"
"}\n"
"#networkset[pltdismode=\"indoor\"]  QPushButton:checked\n"
"{\n"
"	font-weight:bold;	\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-color: rgba(211, 211, 211, 1);\n"
"	color:rgb(0,0,0);\n"
"	border:2px solid white;\n"
"	padding-left:10px;\n"
"}\n"
"#networkset[pltdismode=\"outdoor\"]  QPushButton:checked\n"
"{\n"
"	font-weight:bold;	\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color: rgba(24, 23, 20, 1);\n"
"	color:rgba(250, 218, 166, 1);\n"
"	border:2px solid black;\n"
"	padding-left:10px;\n"
"}\n"
"#networkset[pltdismode=\"night\"]  QPushButton:checked\n"
"{\n"
"	font-weight:bold;	\n"
"}\n"
"\n"
"\n"
""));
        blu_2->setCheckable(false);
        blu_2->setChecked(false);
        pb_blu_refresh = new QPushButton(page_2);
        pb_blu_refresh->setObjectName(QStringLiteral("pb_blu_refresh"));
        pb_blu_refresh->setGeometry(QRect(198, 198, 60, 15));
        pb_blu_refresh->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	color:rgba(6, 62, 97, 1);\n"
"	font:75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	color:rgba(6, 62, 97, 1);\n"
"	font:75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	color:rgba(7, 97, 116, 1);\n"
"	font:75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	background-color:rgba(0,0,0,0);\n"
"}"));
        lblDevName = new QLabel(page_2);
        lblDevName->setObjectName(QStringLiteral("lblDevName"));
        lblDevName->setGeometry(QRect(8, 130, 104, 15));
        lblDevName->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QLabel\n"
"{\n"
"color:rgba(127, 127, 127, 1);\n"
"font:75 13px \"Arial\";\n"
"font-weight:bold;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QLabel\n"
"{\n"
"color:rgba(127, 127, 127, 1);\n"
"font:75 13px \"Arial\";\n"
"font-weight:bold;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QLabel\n"
"{\n"
"color:rgba(88, 77, 58, 1);\n"
"font:75 13px \"Arial\";\n"
"font-weight:bold;\n"
"}\n"
"\n"
"\n"
"\n"
""));
        pb_AMP = new QPushButton(page_2);
        buttonGroup_2 = new QButtonGroup(networkset);
        buttonGroup_2->setObjectName(QStringLiteral("buttonGroup_2"));
        buttonGroup_2->addButton(pb_AMP);
        pb_AMP->setObjectName(QStringLiteral("pb_AMP"));
        pb_AMP->setGeometry(QRect(8, 86, 61, 30));
        pb_AMP->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QPushButton:checked{\n"
"	color:rgba(87, 87, 87,1);\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/bit/image/popup/btn_left.png);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/bit/image/popup/btn_right.png);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QPushButton:checked{\n"
"	color:rgba(87, 87, 87,1);\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/bit/image/popup/btn_left.png);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/bit/image/popup/btn_right.png);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"	background-color:rgba("
                        "0,0,0,0);\n"
"	color:rgba(57, 57, 57, 1);\n"
"	padding: 8px 14px 7px 15px;\n"
"	border-image: url(:/bit/image/popup/btn_left_click.png);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	color:rgba(145, 127, 96, 1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	padding: 8px 14px 7px 15px;\n"
"	border-image: url(:/bit/image/popup/btn_left_nor.png);\n"
"}\n"
""));
        pb_AMP->setCheckable(true);
        pb_AMP->setChecked(true);
        pb_AMP->setAutoRepeat(false);
        pb_AMP->setAutoExclusive(true);
        pb_BLE = new QPushButton(page_2);
        buttonGroup_2->addButton(pb_BLE);
        pb_BLE->setObjectName(QStringLiteral("pb_BLE"));
        pb_BLE->setGeometry(QRect(72, 86, 61, 30));
        pb_BLE->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/bit/image/popup/btn_left.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"indoor\"] QPushButton::checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/bit/image/popup/btn_right.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/bit/image/popup/btn_left.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QPushButton::checked\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	color:rgba(87, 87, 87,1);\n"
"	padding: 8px 5p"
                        "x 7px 6px;\n"
"	background-image: url(:/bit/image/popup/btn_right.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"	background-color:rgba(0,0,0);\n"
"	color:rgba(57, 57, 57, 1);\n"
"	padding: 8px 14px 7px 15px;\n"
"	border-image: url(:/bit/image/popup/btn_right_click.png);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	color:rgba(145, 127, 96, 1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	padding: 8px 14px 7px 15px;\n"
"	border-image: url(:/bit/image/popup/btn_right_nor.png);\n"
"}"));
        pb_BLE->setCheckable(true);
        pb_BLE->setChecked(false);
        pb_BLE->setAutoRepeat(false);
        pb_BLE->setAutoExclusive(true);
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        wifiofbtn = new QPushButton(page_3);
        wifiofbtn->setObjectName(QStringLiteral("wifiofbtn"));
        wifiofbtn->setGeometry(QRect(8, 20, 90, 30));
        wifiofbtn->setStyleSheet(QLatin1String("QPushButton { border-style: flat;}\n"
"#networkset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"background-image: url(:/bit/image/btn_radio_off_w90.png);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"background-image: url(:/bit/image/btn_radio_off_w90.png);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"background-image: url(:/bit/image/night_Off.png);\n"
"}\n"
"\n"
"\n"
"\n"
""));
        wifiofbtn->setCheckable(true);
        pb_wifi_refresh = new QPushButton(page_3);
        pb_wifi_refresh->setObjectName(QStringLiteral("pb_wifi_refresh"));
        pb_wifi_refresh->setGeometry(QRect(194, 140, 61, 15));
        pb_wifi_refresh->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	color:rgba(6, 62, 97, 1);\n"
"	font:75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	color:rgba(6, 62, 97, 1);\n"
"	font:75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	color:rgba(7, 97, 116, 1);\n"
"	font:75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	background-color:rgba(0,0,0,0);\n"
"}"));
        lblWifiLIst = new QLabel(page_3);
        lblWifiLIst->setObjectName(QStringLiteral("lblWifiLIst"));
        lblWifiLIst->setGeometry(QRect(8, 140, 70, 15));
        lblWifiLIst->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QLabel\n"
"{\n"
"color:rgba(127, 127, 127, 1);\n"
"font:75 13px \"Arial\";\n"
"font-weight:bold;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QLabel\n"
"{\n"
"color:rgba(127, 127, 127, 1);\n"
"font:75 13px \"Arial\";\n"
"font-weight:bold;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QLabel\n"
"{\n"
"color:rgba(88, 77, 58, 1);\n"
"font:75 13px \"Arial\";\n"
"font-weight:bold;\n"
"}\n"
"\n"
"\n"
"\n"
""));
        EditDevName = new focuslinedit(page_3);
        EditDevName->setObjectName(QStringLiteral("EditDevName"));
        EditDevName->setGeometry(QRect(8, 86, 250, 34));
        EditDevName->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QLineEdit\n"
"{\n"
"font:75 16px \"Arial\";\n"
"border-image: url(:/bit/image/input_box_w180.png);\n"
"padding-left:10px;\n"
"color: rgba(0, 42, 94, 1);\n"
"}\n"
"#networkset[pltdismode=\"outdoor\"] QLineEdit\n"
"{\n"
"font:75 16px \"Arial\";\n"
"border-image: url(:/bit/image/input_box_w180.png);\n"
"padding-left:10px;\n"
"color: rgba(0, 42, 94, 1);\n"
"}\n"
"#networkset[pltdismode=\"night\"] QLineEdit\n"
"{\n"
"font:75 16px \"Arial\";\n"
"background-color: rgba(24,23,20,1);\n"
"padding-left:10px;\n"
"color: rgba(7,97,116, 1);\n"
"}"));
        lblWifiLIst_4 = new QLabel(page_3);
        lblWifiLIst_4->setObjectName(QStringLiteral("lblWifiLIst_4"));
        lblWifiLIst_4->setGeometry(QRect(8, 70, 104, 15));
        lblWifiLIst_4->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QLabel\n"
"{\n"
"color:rgba(127, 127, 127, 1);\n"
"font:75 13px \"Arial\";\n"
"font-weight:bold;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QLabel\n"
"{\n"
"color:rgba(127, 127, 127, 1);\n"
"font:75 13px \"Arial\";\n"
"font-weight:bold;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QLabel\n"
"{\n"
"color:rgba(88, 77, 58, 1);\n"
"font:75 13px \"Arial\";\n"
"font-weight:bold;\n"
"}\n"
"\n"
"\n"
"\n"
""));
        tableWidget = new QTableWidget(page_3);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(8, 158, 250, 311));
        tableWidget->setFocusPolicy(Qt::NoFocus);
        tableWidget->setStyleSheet(QLatin1String("QScrollBar:vertical {\n"
"	background-color:rgba(145, 145, 145, 1);\n"
"	width:14px;\n"
"	border-radius:6px; \n"
"}\n"
"QScrollBar::handle:vertical {\n"
"	border:2px solid rgba(145, 145, 145, 1);\n"
"	background-color:rgba(235, 235, 235, 1);\n"
"	width:8px;\n"
"	border-radius:6px; \n"
"}\n"
"QScrollBar::add-line:vertical {\n"
"	height:0px;\n"
"	subcontrol-position:bottom;\n"
"	subcontrol-origin:margin;\n"
"}\n"
"QScrollBar::sub-line:vertical {\n"
"	height:0px;\n"
"	subcontrol-position:top;\n"
"	subcontrol-origin:margin;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"indoor\"] #tableWidget\n"
"{\n"
"	border-style:flat;\n"
"	outline:0px;\n"
"	font:75 13px \"Arial\";\n"
"	color:rgb(0,0,0);\n"
"}\n"
"#networkset[pltdismode=\"indoor\"] #tableWidget::item\n"
"{\n"
"	background-color: rgba(211, 211, 211, 1);\n"
"	color:rgb(0,0,0);\n"
"	border:2px solid white;\n"
"	padding-left:10px;\n"
"}\n"
"#networkset[pltdismode=\"indoor\"]  #tableWidget::item:selected\n"
"{\n"
"	font-weight:bold;	\n"
"	background-color: rgb(255, 181, 0)"
                        ";\n"
"}\n"
"#networkset[pltdismode  =  \"indoor\"] QScrollBar:vertical\n"
"{\n"
"	background-color:rgba(145, 145, 145, 1);\n"
"}\n"
"#networkset[pltdismode  =  \"indoor\"] QScrollBar::handle:vertical\n"
" {\n"
"	border:2px solid rgba(145, 145, 145, 1);\n"
"	background-color:rgba(235, 235, 235, 1);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] #tableWidget\n"
"{\n"
"	border-style:flat;\n"
"	outline:0px;\n"
"	font:75 13px \"Arial\";\n"
"	color:rgb(0,0,0);\n"
"}\n"
"#networkset[pltdismode=\"outdoor\"] #tableWidget::item\n"
"{\n"
"	background-color: rgba(211, 211, 211, 1);\n"
"	color:rgb(0,0,0);\n"
"	border:2px solid white;\n"
"	padding-left:10px;\n"
"}\n"
"#networkset[pltdismode=\"outdoor\"]  #tableWidget::item:selected\n"
"{\n"
"	background-color: rgb(255, 181, 0);\n"
"	font-weight:bold;	\n"
"}\n"
"#networkset[pltdismode  =  \"outdoor\"] QScrollBar:vertical\n"
"{\n"
"	background-color:rgba(145, 145, 145, 1);\n"
"}\n"
"#networkset[pltdismode  =  \"outdoor\"] QScrollBar::handle:vertical\n"
" {\n"
"	border:2px"
                        " solid rgba(145, 145, 145, 1);\n"
"	background-color:rgba(235, 235, 235, 1);\n"
"}\n"
"\n"
"\n"
"#networkset[pltdismode=\"night\"] #tableWidget\n"
"{\n"
"	border-style:flat;\n"
"	outline:0px;\n"
"	font:75 13px \"Arial\";\n"
"	background-color:black;\n"
"	color:rgba(250, 218, 166, 1);\n"
"}\n"
"#networkset[pltdismode=\"night\"] #tableWidget::item\n"
"{\n"
"	background-color: rgba(24, 23, 20, 1);\n"
"	color:rgba(250, 218, 166, 1);\n"
"	border:2px solid black;\n"
"	padding-left:10px;\n"
"}\n"
"#networkset[pltdismode=\"night\"]  #tableWidget::item:selected\n"
"{\n"
"	background-color: rgb(255, 156, 0);\n"
"	font-weight:bold;	\n"
"}\n"
"\n"
"#networkset[pltdismode  =  \"night\"] QScrollBar:vertical\n"
"{\n"
"	background-color:rgba(145, 145, 145, 1);\n"
"}\n"
"#networkset[pltdismode  =  \"night\"] QScrollBar::handle:vertical\n"
" {\n"
"	border:2px solid rgba(145, 145, 145, 1);\n"
"	background-color:rgba(235, 235, 235, 1);\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
""));
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
        tableWidget->setShowGrid(false);
        tableWidget->setGridStyle(Qt::SolidLine);
        tableWidget->setRowCount(0);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(250);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(34);
        tableWidget->verticalHeader()->setStretchLastSection(false);
        lblCurWifi = new QLabel(page_3);
        lblCurWifi->setObjectName(QStringLiteral("lblCurWifi"));
        lblCurWifi->setGeometry(QRect(80, 140, 104, 15));
        lblCurWifi->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QLabel\n"
"{\n"
"/*color:rgba(127, 127, 127, 1);*/\n"
"color:rgba(0, 0, 0, 1);\n"
"font:75 13px \"Arial\";\n"
"font-weight:bold;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QLabel\n"
"{\n"
"color:rgba(0, 0, 0, 1);\n"
"/*color:rgba(127, 127, 127, 1);*/\n"
"font:75 13px \"Arial\";\n"
"font-weight:bold;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QLabel\n"
"{\n"
"color:rgba(250, 218, 166, 1);\n"
"/*color:rgba(88, 77, 58, 1);*/\n"
"font:75 13px \"Arial\";\n"
"font-weight:bold;\n"
"}\n"
"\n"
"\n"
"\n"
""));
        stackedWidget->addWidget(page_3);
        label_28 = new QLabel(widget_2);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(630, 432, 121, 17));
        label_28->setFont(font3);
        label_28->setStyleSheet(QStringLiteral(""));
        label_29 = new QLabel(widget_2);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(630, 308, 141, 17));
        label_29->setFont(font3);
        label_29->setStyleSheet(QStringLiteral(""));
        label_30 = new QLabel(widget_2);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(630, 326, 150, 34));
        label_30->setFont(font4);
        label_30->setStyleSheet(QStringLiteral(""));
        label_31 = new QLabel(widget_2);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(630, 368, 101, 17));
        label_31->setFont(font3);
        label_31->setStyleSheet(QStringLiteral(""));
        label_32 = new QLabel(widget_2);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setGeometry(QRect(630, 454, 150, 34));
        label_32->setFont(font4);
        label_32->setStyleSheet(QStringLiteral(""));
        label_33 = new QLabel(widget_2);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setGeometry(QRect(630, 390, 150, 34));
        label_33->setFont(font4);
        label_33->setStyleSheet(QStringLiteral(""));
        label_34 = new QLabel(widget_2);
        label_34->setObjectName(QStringLiteral("label_34"));
        label_34->setGeometry(QRect(810, 242, 67, 17));
        label_34->setFont(font3);
        label_34->setStyleSheet(QStringLiteral(""));
        label_35 = new QLabel(widget_2);
        label_35->setObjectName(QStringLiteral("label_35"));
        label_35->setGeometry(QRect(810, 118, 67, 17));
        label_35->setFont(font3);
        label_35->setStyleSheet(QStringLiteral(""));
        label_36 = new QLabel(widget_2);
        label_36->setObjectName(QStringLiteral("label_36"));
        label_36->setGeometry(QRect(810, 367, 67, 17));
        label_36->setFont(font3);
        label_36->setStyleSheet(QStringLiteral(""));
        label_37 = new QLabel(widget_2);
        label_37->setObjectName(QStringLiteral("label_37"));
        label_37->setGeometry(QRect(810, 136, 150, 34));
        label_37->setFont(font4);
        label_37->setStyleSheet(QStringLiteral(""));
        label_38 = new QLabel(widget_2);
        label_38->setObjectName(QStringLiteral("label_38"));
        label_38->setGeometry(QRect(810, 178, 101, 17));
        label_38->setFont(font3);
        label_38->setStyleSheet(QStringLiteral(""));
        label_39 = new QLabel(widget_2);
        label_39->setObjectName(QStringLiteral("label_39"));
        label_39->setGeometry(QRect(810, 307, 121, 17));
        label_39->setFont(font3);
        label_39->setStyleSheet(QStringLiteral(""));
        label_40 = new QLabel(widget_2);
        label_40->setObjectName(QStringLiteral("label_40"));
        label_40->setGeometry(QRect(810, 389, 150, 34));
        label_40->setFont(font4);
        label_40->setStyleSheet(QStringLiteral(""));
        label_41 = new QLabel(widget_2);
        label_41->setObjectName(QStringLiteral("label_41"));
        label_41->setGeometry(QRect(810, 264, 150, 34));
        label_41->setFont(font4);
        label_41->setStyleSheet(QStringLiteral(""));
        label_42 = new QLabel(widget_2);
        label_42->setObjectName(QStringLiteral("label_42"));
        label_42->setGeometry(QRect(810, 325, 150, 34));
        label_42->setFont(font4);
        label_42->setStyleSheet(QStringLiteral(""));
        label_43 = new QLabel(widget_2);
        label_43->setObjectName(QStringLiteral("label_43"));
        label_43->setGeometry(QRect(810, 200, 150, 34));
        label_43->setFont(font4);
        label_43->setStyleSheet(QStringLiteral(""));
        label_44 = new QLabel(widget_2);
        label_44->setObjectName(QStringLiteral("label_44"));
        label_44->setGeometry(QRect(810, 454, 150, 34));
        label_44->setFont(font4);
        label_44->setStyleSheet(QStringLiteral(""));
        label_45 = new QLabel(widget_2);
        label_45->setObjectName(QStringLiteral("label_45"));
        label_45->setGeometry(QRect(810, 432, 67, 17));
        label_45->setFont(font3);
        label_45->setStyleSheet(QStringLiteral(""));
        lineEdit_13 = new QLineEdit(widget_2);
        lineEdit_13->setObjectName(QStringLiteral("lineEdit_13"));
        lineEdit_13->setGeometry(QRect(678, 535, 191, 34));
        lineEdit_13->setStyleSheet(QLatin1String("font:75 14pt \"Arial\";\n"
"border-image: url(:/bit/image/input_box_w180.png);\n"
"padding-left:10px;\n"
"color: rgba(0, 42, 94, 1);"));
        lineEdit_13->setMaxLength(51);
        lineEdit_13->setEchoMode(QLineEdit::Password);
        lineEdit_13->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_27 = new QLabel(widget_2);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(680, 510, 104, 15));
        label_27->setFont(font3);
        label_27->setStyleSheet(QStringLiteral(" color:rgba(127,127,127,1);"));
        usbTest = new QPushButton(widget_2);
        usbTest->setObjectName(QStringLiteral("usbTest"));
        usbTest->setEnabled(true);
        usbTest->setGeometry(QRect(40, 258, 90, 30));
        usbTest->setStyleSheet(QLatin1String("QPushButton { border-style: flat;}\n"
"#networkset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"background-image: url(:/bit/image/btn_radio_off_w90.png);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"background-image: url(:/bit/image/btn_radio_off_w90.png);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"background-image: url(:/bit/image/night_Off.png);\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
"#networkset[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/btn_radio_on_w90.png);\n"
"	border-style: flat;\n"
"    background-color: transparent;\n"
"}\n"
"#networkset[pltdismode=\"outdoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/btn_radio_on_w90.png);\n"
"	border-style: flat;\n"
"    background-color: transparent;\n"
"}\n"
"#networkset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/night_On.png);\n"
"	border-style: flat;               \n"
""
                        "	background-color: transparent;\n"
"}"));
        usbTest->setCheckable(true);
        usbTest->setChecked(false);
        lblwS = new QLabel(widget_2);
        lblwS->setObjectName(QStringLiteral("lblwS"));
        lblwS->setGeometry(QRect(40, 318, 91, 30));
        QFont font8;
        font8.setFamily(QStringLiteral("Arial"));
        lblwS->setFont(font8);
        lblwS->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
" {\n"
"color:rgba(0,0,0,1);	\n"
"}\n"
"#sysinfo[pltdismode=\"night\"] QLabel\n"
" {\n"
"color:rgba(250, 218, 166,1);	\n"
"}\n"
"QLabel\n"
"{\n"
"font-size:15px;\n"
"font-family:\"Arial\";\n"
"}"));
        lblrSpeed = new QLabel(widget_2);
        lblrSpeed->setObjectName(QStringLiteral("lblrSpeed"));
        lblrSpeed->setGeometry(QRect(70, 458, 101, 30));
        QFont font9;
        font9.setFamily(QStringLiteral("Arial"));
        font9.setBold(true);
        font9.setWeight(75);
        lblrSpeed->setFont(font9);
        lblrSpeed->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
" {\n"
"color:rgba(0,0,0,1);	\n"
"}\n"
"#sysinfo[pltdismode=\"night\"] QLabel\n"
" {\n"
"color:rgba(250, 218, 166,1);	\n"
"}\n"
"QLabel\n"
"{\n"
"font-size:15px;\n"
"font-family:\"Arial\";\n"
"font-weight:bold;\n"
"}"));
        lblrS = new QLabel(widget_2);
        lblrS->setObjectName(QStringLiteral("lblrS"));
        lblrS->setGeometry(QRect(40, 418, 91, 30));
        lblrS->setFont(font8);
        lblrS->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
" {\n"
"color:rgba(0,0,0,1);	\n"
"}\n"
"#sysinfo[pltdismode=\"night\"] QLabel\n"
" {\n"
"color:rgba(250, 218, 166,1);	\n"
"}\n"
"QLabel\n"
"{\n"
"font-size:15px;\n"
"font-family:\"Arial\";\n"
"}"));
        lblwSpeed = new QLabel(widget_2);
        lblwSpeed->setObjectName(QStringLiteral("lblwSpeed"));
        lblwSpeed->setGeometry(QRect(70, 358, 101, 30));
        lblwSpeed->setFont(font9);
        lblwSpeed->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
" {\n"
"color:rgba(0,0,0,1);	\n"
"}\n"
"#sysinfo[pltdismode=\"night\"] QLabel\n"
" {\n"
"color:rgba(250, 218, 166,1);	\n"
"}\n"
"QLabel\n"
"{\n"
"font-size:15px;\n"
"font-family:\"Arial\";\n"
"font-weight:bold;\n"
"}"));
        usbErrorWid = new QWidget(widget_2);
        usbErrorWid->setObjectName(QStringLiteral("usbErrorWid"));
        usbErrorWid->setGeometry(QRect(40, 308, 171, 211));
        label_16 = new QLabel(usbErrorWid);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(10, 10, 121, 17));
        label_46 = new QLabel(widget_2);
        label_46->setObjectName(QStringLiteral("label_46"));
        label_46->setGeometry(QRect(20, 227, 153, 17));
        label_46->setFont(font1);
        label_46->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(6,62,97,1);\n"
"	background-color: white;\n"
"}\n"
"#networkset[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}"));
        line_7 = new QFrame(widget_2);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setGeometry(QRect(20, 248, 250, 2));
        line_7->setStyleSheet(QLatin1String("#networkset[pltdismode=\"indoor\"] #line_4\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#networkset[pltdismode=\"night\"] #line_4\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);

        retranslateUi(networkset);

        stackedWidget->setCurrentIndex(0);
        blu_1->setDefault(false);


        QMetaObject::connectSlotsByName(networkset);
    } // setupUi

    void retranslateUi(QWidget *networkset)
    {
        networkset->setWindowTitle(QApplication::translate("networkset", "Form", Q_NULLPTR));
        networkset->setProperty("pltdismode", QVariant(QApplication::translate("networkset", "indoor", Q_NULLPTR)));
        label_4->setText(QApplication::translate("networkset", "Remote Interface", Q_NULLPTR));
        label_5->setText(QApplication::translate("networkset", "Ethernet Configration", Q_NULLPTR));
        label_6->setText(QApplication::translate("networkset", "GPS", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("networkset", "LAN", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("networkset", "Bluetooth", Q_NULLPTR));
        pushButton_9->setText(QApplication::translate("networkset", "Wi-Fi", Q_NULLPTR));
        gpsbtn->setText(QString());
        label->setText(QApplication::translate("networkset", "Latitude", Q_NULLPTR));
        label->setProperty("mod", QVariant(QApplication::translate("networkset", "1", Q_NULLPTR)));
        label_2->setText(QApplication::translate("networkset", "-- --", Q_NULLPTR));
        label_2->setProperty("mod", QVariant(QApplication::translate("networkset", "4", Q_NULLPTR)));
        label_3->setText(QApplication::translate("networkset", "Elevation", Q_NULLPTR));
        label_3->setProperty("mod", QVariant(QApplication::translate("networkset", "1", Q_NULLPTR)));
        label_7->setText(QApplication::translate("networkset", "-- --", Q_NULLPTR));
        label_7->setProperty("mod", QVariant(QApplication::translate("networkset", "4", Q_NULLPTR)));
        label_8->setText(QApplication::translate("networkset", "Speed", Q_NULLPTR));
        label_8->setProperty("mod", QVariant(QApplication::translate("networkset", "1", Q_NULLPTR)));
        label_9->setText(QApplication::translate("networkset", "-- --", Q_NULLPTR));
        label_9->setProperty("mod", QVariant(QApplication::translate("networkset", "4", Q_NULLPTR)));
        label_12->setText(QApplication::translate("networkset", "Net Mask", Q_NULLPTR));
        label_12->setProperty("mod", QVariant(QApplication::translate("networkset", "1", Q_NULLPTR)));
        label_11->setText(QApplication::translate("networkset", "IP Address", Q_NULLPTR));
        label_11->setProperty("mod", QVariant(QApplication::translate("networkset", "1", Q_NULLPTR)));
        lineEdit->setText(QApplication::translate("networkset", "192", Q_NULLPTR));
        label_13->setText(QApplication::translate("networkset", "Gateway", Q_NULLPTR));
        label_13->setProperty("mod", QVariant(QApplication::translate("networkset", "1", Q_NULLPTR)));
        netsetbtn->setText(QApplication::translate("networkset", "Setting", Q_NULLPTR));
        label_14->setText(QApplication::translate("networkset", "Port", Q_NULLPTR));
        label_14->setProperty("mod", QVariant(QApplication::translate("networkset", "1", Q_NULLPTR)));
        netsetbtn_2->setText(QApplication::translate("networkset", "Setting", Q_NULLPTR));
        label_10->setText(QString());
        label_10->setProperty("mod", QVariant(QApplication::translate("networkset", "3", Q_NULLPTR)));
        lineEdit_4->setText(QApplication::translate("networkset", "168", Q_NULLPTR));
        lineEdit_5->setText(QApplication::translate("networkset", "26", Q_NULLPTR));
        lineEdit_6->setText(QApplication::translate("networkset", "238", Q_NULLPTR));
        label_15->setText(QApplication::translate("networkset", ".", Q_NULLPTR));
        label_15->setProperty("mod", QVariant(QApplication::translate("networkset", "2", Q_NULLPTR)));
        label_17->setText(QApplication::translate("networkset", ".", Q_NULLPTR));
        label_17->setProperty("mod", QVariant(QApplication::translate("networkset", "2", Q_NULLPTR)));
        label_18->setText(QApplication::translate("networkset", ".", Q_NULLPTR));
        label_18->setProperty("mod", QVariant(QApplication::translate("networkset", "2", Q_NULLPTR)));
        label_19->setText(QString());
        label_19->setProperty("mod", QVariant(QApplication::translate("networkset", "3", Q_NULLPTR)));
        label_20->setText(QString());
        label_20->setProperty("mod", QVariant(QApplication::translate("networkset", "3", Q_NULLPTR)));
        label_21->setText(QApplication::translate("networkset", ".", Q_NULLPTR));
        label_21->setProperty("mod", QVariant(QApplication::translate("networkset", "2", Q_NULLPTR)));
        label_22->setText(QApplication::translate("networkset", ".", Q_NULLPTR));
        label_22->setProperty("mod", QVariant(QApplication::translate("networkset", "2", Q_NULLPTR)));
        lineEdit_7->setText(QApplication::translate("networkset", "255", Q_NULLPTR));
        lineEdit_8->setText(QApplication::translate("networkset", "0", Q_NULLPTR));
        lineEdit_9->setText(QApplication::translate("networkset", "255", Q_NULLPTR));
        label_23->setText(QApplication::translate("networkset", ".", Q_NULLPTR));
        label_23->setProperty("mod", QVariant(QApplication::translate("networkset", "2", Q_NULLPTR)));
        lineEdit_2->setText(QApplication::translate("networkset", "255", Q_NULLPTR));
        label_24->setText(QApplication::translate("networkset", ".", Q_NULLPTR));
        label_24->setProperty("mod", QVariant(QApplication::translate("networkset", "2", Q_NULLPTR)));
        label_25->setText(QApplication::translate("networkset", ".", Q_NULLPTR));
        label_25->setProperty("mod", QVariant(QApplication::translate("networkset", "2", Q_NULLPTR)));
        lineEdit_10->setText(QApplication::translate("networkset", "1", Q_NULLPTR));
        lineEdit_11->setText(QApplication::translate("networkset", "26", Q_NULLPTR));
        lineEdit_12->setText(QApplication::translate("networkset", "168", Q_NULLPTR));
        label_26->setText(QApplication::translate("networkset", ".", Q_NULLPTR));
        label_26->setProperty("mod", QVariant(QApplication::translate("networkset", "2", Q_NULLPTR)));
        lineEdit_3->setText(QApplication::translate("networkset", "192", Q_NULLPTR));
        lineEdit_14->setText(QApplication::translate("networkset", "5025", Q_NULLPTR));
        blutoothofbtn->setText(QString());
        lblBluMode->setText(QApplication::translate("networkset", "Mode", Q_NULLPTR));
        blu_4->setText(QApplication::translate("networkset", "Blue 4", Q_NULLPTR));
        EditDevName_2->setText(QApplication::translate("networkset", "5G smart SA", Q_NULLPTR));
        blu_3->setText(QApplication::translate("networkset", "Blue 3", Q_NULLPTR));
        lblBluList->setText(QApplication::translate("networkset", "Wi-fi List", Q_NULLPTR));
        blu_1->setText(QApplication::translate("networkset", "Blue 1", Q_NULLPTR));
        blu_5->setText(QApplication::translate("networkset", "Blue 5", Q_NULLPTR));
        blu_2->setText(QApplication::translate("networkset", "Blue 2", Q_NULLPTR));
        pb_blu_refresh->setText(QApplication::translate("networkset", "refresh", Q_NULLPTR));
        lblDevName->setText(QApplication::translate("networkset", "Device name", Q_NULLPTR));
        pb_AMP->setText(QApplication::translate("networkset", "AMP", Q_NULLPTR));
        pb_BLE->setText(QApplication::translate("networkset", "BLE", Q_NULLPTR));
        wifiofbtn->setText(QString());
#ifndef QT_NO_WHATSTHIS
        pb_wifi_refresh->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        pb_wifi_refresh->setText(QApplication::translate("networkset", "refresh", Q_NULLPTR));
        lblWifiLIst->setText(QApplication::translate("networkset", "Wi-fi List", Q_NULLPTR));
        EditDevName->setText(QApplication::translate("networkset", "5G smart SA", Q_NULLPTR));
        lblWifiLIst_4->setText(QApplication::translate("networkset", "Device name", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("networkset", "Wi-fi 1", Q_NULLPTR));
        lblCurWifi->setText(QString());
        label_28->setText(QApplication::translate("networkset", "Operation Mode", Q_NULLPTR));
        label_28->setProperty("mod", QVariant(QApplication::translate("networkset", "1", Q_NULLPTR)));
        label_29->setText(QApplication::translate("networkset", "Satellites In Use", Q_NULLPTR));
        label_29->setProperty("mod", QVariant(QApplication::translate("networkset", "1", Q_NULLPTR)));
        label_30->setText(QApplication::translate("networkset", "-- --", Q_NULLPTR));
        label_30->setProperty("mod", QVariant(QApplication::translate("networkset", "4", Q_NULLPTR)));
        label_31->setText(QApplication::translate("networkset", "PRN Number", Q_NULLPTR));
        label_31->setProperty("mod", QVariant(QApplication::translate("networkset", "1", Q_NULLPTR)));
        label_32->setText(QApplication::translate("networkset", "-- --", Q_NULLPTR));
        label_32->setProperty("mod", QVariant(QApplication::translate("networkset", "4", Q_NULLPTR)));
        label_33->setText(QApplication::translate("networkset", "-- --", Q_NULLPTR));
        label_33->setProperty("mod", QVariant(QApplication::translate("networkset", "4", Q_NULLPTR)));
        label_34->setText(QApplication::translate("networkset", "Direction", Q_NULLPTR));
        label_34->setProperty("mod", QVariant(QApplication::translate("networkset", "1", Q_NULLPTR)));
        label_35->setText(QApplication::translate("networkset", "Longitude", Q_NULLPTR));
        label_35->setProperty("mod", QVariant(QApplication::translate("networkset", "1", Q_NULLPTR)));
        label_36->setText(QApplication::translate("networkset", "Utc Date", Q_NULLPTR));
        label_36->setProperty("mod", QVariant(QApplication::translate("networkset", "1", Q_NULLPTR)));
        label_37->setText(QApplication::translate("networkset", "-- --", Q_NULLPTR));
        label_37->setProperty("mod", QVariant(QApplication::translate("networkset", "4", Q_NULLPTR)));
        label_38->setText(QApplication::translate("networkset", "Quality", Q_NULLPTR));
        label_38->setProperty("mod", QVariant(QApplication::translate("networkset", "1", Q_NULLPTR)));
        label_39->setText(QApplication::translate("networkset", "Satellites In View", Q_NULLPTR));
        label_39->setProperty("mod", QVariant(QApplication::translate("networkset", "1", Q_NULLPTR)));
        label_40->setText(QApplication::translate("networkset", "-- --", Q_NULLPTR));
        label_40->setProperty("mod", QVariant(QApplication::translate("networkset", "4", Q_NULLPTR)));
        label_41->setText(QApplication::translate("networkset", "-- --", Q_NULLPTR));
        label_41->setProperty("mod", QVariant(QApplication::translate("networkset", "4", Q_NULLPTR)));
        label_42->setText(QApplication::translate("networkset", "-- --", Q_NULLPTR));
        label_42->setProperty("mod", QVariant(QApplication::translate("networkset", "4", Q_NULLPTR)));
        label_43->setText(QApplication::translate("networkset", "-- --", Q_NULLPTR));
        label_43->setProperty("mod", QVariant(QApplication::translate("networkset", "4", Q_NULLPTR)));
        label_44->setText(QApplication::translate("networkset", "-- --", Q_NULLPTR));
        label_44->setProperty("mod", QVariant(QApplication::translate("networkset", "4", Q_NULLPTR)));
        label_45->setText(QApplication::translate("networkset", "Utc Time", Q_NULLPTR));
        label_45->setProperty("mod", QVariant(QApplication::translate("networkset", "1", Q_NULLPTR)));
        lineEdit_13->setText(QApplication::translate("networkset", "123456", Q_NULLPTR));
        label_27->setText(QApplication::translate("networkset", "Password", Q_NULLPTR));
        usbTest->setText(QString());
        lblwS->setText(QApplication::translate("networkset", "Write Speed:", Q_NULLPTR));
        lblrSpeed->setText(QApplication::translate("networkset", "-- --", Q_NULLPTR));
        lblrS->setText(QApplication::translate("networkset", "Read Speed:", Q_NULLPTR));
        lblwSpeed->setText(QApplication::translate("networkset", "-- --", Q_NULLPTR));
        label_16->setText(QApplication::translate("networkset", "No USB find.", Q_NULLPTR));
        label_46->setText(QApplication::translate("networkset", "USB Speed Test", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class networkset: public Ui_networkset {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETWORKSET_H
