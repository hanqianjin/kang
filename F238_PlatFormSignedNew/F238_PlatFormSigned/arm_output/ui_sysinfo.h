/********************************************************************************
** Form generated from reading UI file 'sysinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSINFO_H
#define UI_SYSINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sysinfo
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_15;
    QLabel *label_11;
    QLabel *label_8;
    QLabel *label_18;
    QLabel *label_14;
    QLabel *label_7;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_19;
    QLabel *label_28;
    QLabel *label_27;
    QLabel *label_23;
    QLabel *label_26;
    QLabel *label_24;
    QLabel *label_22;
    QLabel *label_29;
    QLabel *label_25;

    void setupUi(QWidget *sysinfo)
    {
        if (sysinfo->objectName().isEmpty())
            sysinfo->setObjectName(QStringLiteral("sysinfo"));
        sysinfo->resize(996, 598);
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        font.setPointSize(1);
        sysinfo->setFont(font);
        sysinfo->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"night\"]\n"
"{	\n"
"background-color: rgb(0, 0, 0);\n"
"}\n"
"#sysinfo[pltdismode=\"indoor\"]\n"
"{	\n"
"background-color:white;\n"
"}\n"
"\n"
"#sysinfo[pltdismode=\"indoor\"] #label_3,\n"
"#sysinfo[pltdismode=\"indoor\"] #label_4,\n"
"#sysinfo[pltdismode=\"indoor\"] #label_19\n"
" {\n"
"background-color: rgb(238, 238, 236);\n"
"}\n"
"\n"
"#sysinfo[pltdismode=\"night\"] #label_3,\n"
"#sysinfo[pltdismode=\"night\"] #label_4,\n"
"#sysinfo[pltdismode=\"night\"] #label_19\n"
" {\n"
"background-color: rgb(24, 23, 20);\n"
"}\n"
"\n"
"#sysinfo[pltdismode=\"indoor\"] #label, #sysinfo[pltdismode=\"indoor\"] #label_2\n"
" {\n"
"color:rgb(6,62,97);	\n"
"}\n"
"#sysinfo[pltdismode=\"night\"] #label ,\n"
"#sysinfo[pltdismode=\"night\"] #label_2\n"
" {\n"
"color:rgb(7,97,116);	\n"
"}"));
        label = new QLabel(sysinfo);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 46, 351, 50));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(36);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(sysinfo);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(230, 67, 350, 30));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        label_2->setFont(font2);
        label_3 = new QLabel(sysinfo);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 154, 793, 30));
        label_4 = new QLabel(sysinfo);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 214, 793, 30));
        label_5 = new QLabel(sysinfo);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(60, 154, 125, 30));
        QFont font3;
        font3.setFamily(QStringLiteral("Arial"));
        label_5->setFont(font3);
        label_5->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_6 = new QLabel(sysinfo);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(475, 154, 111, 30));
        label_6->setFont(font3);
        label_6->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_9 = new QLabel(sysinfo);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(60, 184, 137, 30));
        label_9->setFont(font3);
        label_9->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_10 = new QLabel(sysinfo);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(475, 184, 140, 30));
        label_10->setFont(font3);
        label_10->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_12 = new QLabel(sysinfo);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(194, 154, 101, 30));
        QFont font4;
        font4.setFamily(QStringLiteral("Arial"));
        font4.setBold(true);
        font4.setWeight(75);
        label_12->setFont(font4);
        label_12->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_13 = new QLabel(sysinfo);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(590, 154, 150, 30));
        label_13->setFont(font4);
        label_13->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_16 = new QLabel(sysinfo);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(200, 184, 150, 30));
        label_16->setFont(font4);
        label_16->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_17 = new QLabel(sysinfo);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(620, 184, 150, 30));
        label_17->setFont(font4);
        label_17->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_15 = new QLabel(sysinfo);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(220, 214, 191, 30));
        label_15->setFont(font4);
        label_15->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_11 = new QLabel(sysinfo);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(475, 214, 151, 30));
        label_11->setFont(font3);
        label_11->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_8 = new QLabel(sysinfo);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(60, 214, 151, 30));
        label_8->setFont(font3);
        label_8->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_18 = new QLabel(sysinfo);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(630, 214, 181, 30));
        label_18->setFont(font4);
        label_18->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_14 = new QLabel(sysinfo);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(590, 244, 150, 30));
        label_14->setFont(font4);
        label_14->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_7 = new QLabel(sysinfo);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(475, 244, 111, 30));
        label_7->setFont(font3);
        label_7->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_20 = new QLabel(sysinfo);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(180, 244, 201, 30));
        label_20->setFont(font4);
        label_20->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_21 = new QLabel(sysinfo);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(60, 244, 141, 30));
        label_21->setFont(font3);
        label_21->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_19 = new QLabel(sysinfo);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(30, 300, 793, 141));
        label_28 = new QLabel(sysinfo);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(60, 400, 171, 30));
        label_28->setFont(font3);
        label_28->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_27 = new QLabel(sysinfo);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(280, 370, 150, 30));
        label_27->setFont(font4);
        label_27->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_23 = new QLabel(sysinfo);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(280, 310, 150, 30));
        label_23->setFont(font4);
        label_23->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_26 = new QLabel(sysinfo);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(60, 370, 191, 30));
        label_26->setFont(font3);
        label_26->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_24 = new QLabel(sysinfo);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(280, 340, 150, 30));
        label_24->setFont(font4);
        label_24->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_22 = new QLabel(sysinfo);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(60, 310, 211, 30));
        label_22->setFont(font3);
        label_22->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_29 = new QLabel(sysinfo);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(280, 400, 150, 30));
        label_29->setFont(font4);
        label_29->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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
        label_25 = new QLabel(sysinfo);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(60, 340, 201, 30));
        label_25->setFont(font3);
        label_25->setStyleSheet(QLatin1String("#sysinfo[pltdismode=\"indoor\"] QLabel\n"
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

        retranslateUi(sysinfo);

        QMetaObject::connectSlotsByName(sysinfo);
    } // setupUi

    void retranslateUi(QWidget *sysinfo)
    {
        sysinfo->setWindowTitle(QApplication::translate("sysinfo", "Form", 0));
        sysinfo->setProperty("pltdismode", QVariant(QApplication::translate("sysinfo", "indoor", 0)));
        label->setText(QApplication::translate("sysinfo", "5G SMART 15", 0));
        label_2->setText(QString());
        label_3->setText(QString());
        label_4->setText(QString());
        label_5->setText(QApplication::translate("sysinfo", "Product Number", 0));
        label_6->setText(QApplication::translate("sysinfo", "Serial Number", 0));
        label_9->setText(QApplication::translate("sysinfo", "S/W Version ", 0));
        label_10->setText(QApplication::translate("sysinfo", "H/W Version", 0));
        label_12->setText(QApplication::translate("sysinfo", "1500", 0));
        label_13->setText(QApplication::translate("sysinfo", "D19051100E7CN", 0));
        label_16->setText(QApplication::translate("sysinfo", "V0.0.8", 0));
        label_17->setText(QApplication::translate("sysinfo", "A1.0.0", 0));
        label_15->setText(QApplication::translate("sysinfo", "2.0.1", 0));
        label_11->setText(QApplication::translate("sysinfo", "SPA FPGA Version", 0));
        label_8->setText(QApplication::translate("sysinfo", "Main FPGA Version", 0));
        label_18->setText(QApplication::translate("sysinfo", "1.0.0", 0));
        label_14->setText(QApplication::translate("sysinfo", "20191122", 0));
        label_7->setText(QApplication::translate("sysinfo", "Test Time", 0));
        label_20->setText(QApplication::translate("sysinfo", "0.3.1", 0));
        label_21->setText(QApplication::translate("sysinfo", "CPLD Version", 0));
        label_19->setText(QString());
        label_28->setText(QApplication::translate("sysinfo", "Battery Temperature", 0));
        label_27->setText(QApplication::translate("sysinfo", "60 deg", 0));
        label_23->setText(QApplication::translate("sysinfo", "50 deg", 0));
        label_26->setText(QApplication::translate("sysinfo", "Main FPGA Temperature", 0));
        label_24->setText(QApplication::translate("sysinfo", "60 deg", 0));
        label_22->setText(QApplication::translate("sysinfo", "Main Board Temperature", 0));
        label_29->setText(QApplication::translate("sysinfo", "37 deg", 0));
        label_25->setText(QApplication::translate("sysinfo", "RF Board Temperature", 0));
    } // retranslateUi

};

namespace Ui {
    class sysinfo: public Ui_sysinfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSINFO_H
