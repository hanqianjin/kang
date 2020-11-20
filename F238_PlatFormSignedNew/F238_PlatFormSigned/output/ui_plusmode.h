/********************************************************************************
** Form generated from reading UI file 'plusmode.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLUSMODE_H
#define UI_PLUSMODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_plusmode
{
public:
    QLabel *label_2;
    QLabel *label_8;
    QPushButton *pushButton_15;
    QPushButton *pushButton_17;
    QPushButton *pushButton_16;
    QWidget *pmmeawid;
    QPushButton *pushButton_49;
    QPushButton *pushButton_53;
    QLabel *label_4;
    QFrame *line_4;
    QWidget *fivegnrmeawid;
    QPushButton *pushButton_52;
    QPushButton *pushButton_105;
    QLabel *label_11;
    QFrame *line_12;
    QPushButton *pushButton_106;
    QPushButton *pushButton_107;
    QPushButton *pushButton_108;
    QPushButton *pushButton_109;
    QPushButton *pushButton_110;
    QPushButton *pushButton_111;
    QPushButton *pushButton_112;
    QWidget *intermeawid;
    QPushButton *pushButton_43;
    QPushButton *pushButton_45;
    QPushButton *pushButton_46;
    QPushButton *pushButton_47;
    QPushButton *pushButton_48;
    QPushButton *pushButton_51;
    QLabel *label_6;
    QFrame *line_5;
    QWidget *backwid;
    QPushButton *pushButton_4;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QLabel *label;
    QPushButton *pushButton_2;
    QPushButton *pushButton_5;
    QFrame *line;
    QFrame *line_3;
    QPushButton *pushButton_18;
    QPushButton *pushButton_19;
    QWidget *ltefddmeawid;
    QPushButton *pushButton_54;
    QPushButton *pushButton_55;
    QPushButton *pushButton_56;
    QPushButton *pushButton_59;
    QPushButton *pushButton_60;
    QPushButton *pushButton_61;
    QPushButton *pushButton_63;
    QPushButton *pushButton_57;
    QLabel *label_7;
    QFrame *line_6;
    QPushButton *pushButton_62;
    QPushButton *pushButton_64;
    QPushButton *pushButton_66;
    QPushButton *pushButton_67;
    QPushButton *pushButton_68;
    QPushButton *pushButton_69;
    QPushButton *pushButton_70;
    QPushButton *pushButton_71;
    QPushButton *pushButton_72;
    QPushButton *pushButton_73;
    QFrame *line_8;
    QPushButton *pushButton_94;
    QPushButton *pushButton_95;
    QPushButton *pushButton_96;
    QPushButton *pushButton_97;
    QPushButton *pushButton_98;
    QWidget *rtsameawid;
    QPushButton *pushButton_30;
    QPushButton *pushButton_37;
    QLabel *label_5;
    QFrame *line_7;
    QPushButton *pushButton_38;
    QPushButton *pushButton_39;
    QWidget *sameawid;
    QPushButton *pushButton_11;
    QPushButton *pushButton_13;
    QPushButton *pushButton_6;
    QPushButton *pushButton_12;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_14;
    QLabel *label_3;
    QPushButton *pushButton_7;
    QFrame *line_2;
    QWidget *ltetddmeawid;
    QPushButton *pushButton_74;
    QPushButton *pushButton_75;
    QPushButton *pushButton_76;
    QPushButton *pushButton_77;
    QPushButton *pushButton_78;
    QPushButton *pushButton_79;
    QPushButton *pushButton_80;
    QPushButton *pushButton_81;
    QPushButton *pushButton_82;
    QLabel *label_9;
    QFrame *line_9;
    QPushButton *pushButton_83;
    QPushButton *pushButton_84;
    QPushButton *pushButton_85;
    QPushButton *pushButton_86;
    QPushButton *pushButton_87;
    QPushButton *pushButton_88;
    QPushButton *pushButton_89;
    QPushButton *pushButton_90;
    QPushButton *pushButton_91;
    QPushButton *pushButton_92;
    QPushButton *pushButton_93;
    QFrame *line_10;
    QPushButton *pushButton_99;
    QPushButton *pushButton_100;
    QPushButton *pushButton_101;
    QPushButton *pushButton_102;
    QPushButton *pushButton_103;

    void setupUi(QDialog *plusmode)
    {
        if (plusmode->objectName().isEmpty())
            plusmode->setObjectName(QStringLiteral("plusmode"));
        plusmode->resize(1280, 800);
        plusmode->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] \n"
"{\n"
"background-color: rgba(255, 255, 255,1);\n"
"}\n"
"#plusmode[pltdismode=\"night\"]\n"
"{\n"
"background-color: rgba(0, 0, 0,1);\n"
"}"));
        label_2 = new QLabel(plusmode);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(1, 1, 1278, 45));
        label_2->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] QLabel\n"
"{\n"
"background-color: rgba(201, 201, 201,1);\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QLabel\n"
"{\n"
"background-color: rgba(53, 46, 35,1);\n"
"}"));
        label_8 = new QLabel(plusmode);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(30, 13, 261, 22));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        label_8->setFont(font);
        label_8->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] QLabel\n"
"{\n"
"color: rgba(0, 0, 0,1);\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QLabel\n"
"{\n"
"background-color: rgba(53,46,35,1);\n"
"color: rgba(250,218,166,1);\n"
"}"));
        pushButton_15 = new QPushButton(plusmode);
        pushButton_15->setObjectName(QStringLiteral("pushButton_15"));
        pushButton_15->setGeometry(QRect(1211, 1, 45, 45));
        pushButton_15->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/btn_close_30_nor.png);\n"
"}\n"
"#plusmode[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/btn_close_30_click.png);\n"
"}\n"
"\n"
"#plusmode[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/night_close_nor.png);\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/night_close_click.png);\n"
"}\n"
"QPushButton { border-style: flat;}\n"
""));
        pushButton_15->setFlat(true);
        pushButton_17 = new QPushButton(plusmode);
        pushButton_17->setObjectName(QStringLiteral("pushButton_17"));
        pushButton_17->setGeometry(QRect(1072, 679, 80, 30));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(13);
        pushButton_17->setFont(font1);
        pushButton_17->setLayoutDirection(Qt::LeftToRight);
        pushButton_17->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/btn_cancel_w80_nor.png);\n"
"}\n"
"#plusmode[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/btn_cancel_w80_click.png);\n"
"}\n"
"\n"
"#plusmode[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/cancel-normal_night.png);\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/cancel-click_night.png);\n"
"}\n"
"\n"
"\n"
"QPushButton { border-style: flat;}\n"
"QPushButton{padding-left:0px;text-align:center;\n"
"color: rgb(255, 255, 255);\n"
"}"));
        pushButton_17->setFlat(true);
        pushButton_16 = new QPushButton(plusmode);
        pushButton_16->setObjectName(QStringLiteral("pushButton_16"));
        pushButton_16->setGeometry(QRect(1154, 679, 80, 30));
        pushButton_16->setFont(font1);
        pushButton_16->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/btn_ok_w80_nor.png);\n"
"}\n"
"#plusmode[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/btn_ok_w80_click.png);\n"
"}\n"
"\n"
"#plusmode[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/oK-normal_night.png);\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/oK-click_night.png);\n"
"}\n"
"QPushButton { border-style: flat;}\n"
"QPushButton{padding-left:0px;text-align:center;\n"
"color: rgb(255, 255, 255);\n"
"}\n"
""));
        pushButton_16->setFlat(true);
        pmmeawid = new QWidget(plusmode);
        pmmeawid->setObjectName(QStringLiteral("pmmeawid"));
        pmmeawid->setGeometry(QRect(940, 430, 331, 231));
        pmmeawid->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"night\"] #pmmeawid\n"
"{	\n"
"background-color: rgba(0, 0, 0,1);\n"
"}\n"
"#plusmode[pltdismode=\"indoor\"] #pmmeawid\n"
"{	\n"
"background-color:rgba(255,255,255,1);\n"
"}\n"
"\n"
"#plusmode[pltdismode=\"indoor\"] QPushButton:!checked\n"
"{\n"
"font: 11pt \"Arial\";\n"
"font-weight:normal;\n"
"background-color: rgba(237, 212, 0,0);\n"
"color: rgb(105, 105, 105);\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QPushButton:!checked\n"
"{\n"
"font: 11pt \"Arial\";\n"
"font-weight:normal;\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#plusmode[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"font: 75 11pt \"Arial\";\n"
"font-weight:bold;\n"
"background-color: rgb(255,181,0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"font: 75 11pt \"Arial\";\n"
"font-weight:bold;\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"\n"
"QPushButton{border-style:flat;text-align:left;}\n"
"QPushButton{pa"
                        "dding-left:10px}"));
        pushButton_49 = new QPushButton(pmmeawid);
        pushButton_49->setObjectName(QStringLiteral("pushButton_49"));
        pushButton_49->setGeometry(QRect(20, 55, 300, 30));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        pushButton_49->setFont(font2);
        pushButton_49->setCheckable(true);
        pushButton_49->setChecked(true);
        pushButton_49->setAutoExclusive(true);
        pushButton_53 = new QPushButton(pmmeawid);
        pushButton_53->setObjectName(QStringLiteral("pushButton_53"));
        pushButton_53->setGeometry(QRect(20, 100, 300, 30));
        pushButton_53->setFont(font2);
        pushButton_53->setCheckable(true);
        pushButton_53->setAutoExclusive(true);
        label_4 = new QLabel(pmmeawid);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(22, 28, 111, 17));
        QFont font3;
        font3.setFamily(QStringLiteral("Arial"));
        font3.setPointSize(11);
        font3.setBold(true);
        font3.setWeight(75);
        label_4->setFont(font3);
        label_4->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(9, 73, 108,1);\n"
"	background-color: white;\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}\n"
""));
        line_4 = new QFrame(pmmeawid);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(22, 48, 400, 2));
        line_4->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] #line_4\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#plusmode[pltdismode=\"night\"] #line_4\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        fivegnrmeawid = new QWidget(plusmode);
        fivegnrmeawid->setObjectName(QStringLiteral("fivegnrmeawid"));
        fivegnrmeawid->setGeometry(QRect(300, 50, 321, 451));
        fivegnrmeawid->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"night\"] #fivegnrmeawid\n"
"{	\n"
"background-color: rgba(0, 0, 0,1);\n"
"}\n"
"#plusmode[pltdismode=\"indoor\"] #fivegnrmeawid\n"
"{	\n"
"background-color:rgba(255,255,255,1);\n"
"}\n"
"\n"
"#plusmode[pltdismode=\"indoor\"] QPushButton:!checked\n"
"{\n"
"font: 11pt \"Arial\";\n"
"font-weight:normal;\n"
"background-color: rgba(237, 212, 0,0);\n"
"color: rgb(105, 105, 105);\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QPushButton:!checked\n"
"{\n"
"font: 11pt \"Arial\";\n"
"font-weight:normal;\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#plusmode[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"font: 75 11pt \"Arial\";\n"
"font-weight:bold;\n"
"background-color: rgb(255,181,0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"font: 75 11pt \"Arial\";\n"
"font-weight:bold;\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"\n"
"QPushButton{border-style:flat;text-align:left;}\n"
"QPus"
                        "hButton{padding-left:10px}"));
        pushButton_52 = new QPushButton(fivegnrmeawid);
        pushButton_52->setObjectName(QStringLiteral("pushButton_52"));
        pushButton_52->setGeometry(QRect(20, 55, 300, 30));
        pushButton_52->setFont(font2);
        pushButton_52->setCheckable(true);
        pushButton_52->setChecked(true);
        pushButton_52->setAutoExclusive(true);
        pushButton_105 = new QPushButton(fivegnrmeawid);
        pushButton_105->setObjectName(QStringLiteral("pushButton_105"));
        pushButton_105->setGeometry(QRect(20, 100, 300, 30));
        pushButton_105->setFont(font2);
        pushButton_105->setCheckable(true);
        pushButton_105->setAutoExclusive(true);
        label_11 = new QLabel(fivegnrmeawid);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(22, 28, 111, 17));
        label_11->setFont(font3);
        label_11->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(9, 73, 108,1);\n"
"	background-color: white;\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}\n"
""));
        line_12 = new QFrame(fivegnrmeawid);
        line_12->setObjectName(QStringLiteral("line_12"));
        line_12->setGeometry(QRect(22, 48, 400, 2));
        line_12->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] #line_12\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#plusmode[pltdismode=\"night\"] #line_12\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_12->setFrameShape(QFrame::HLine);
        line_12->setFrameShadow(QFrame::Sunken);
        pushButton_106 = new QPushButton(fivegnrmeawid);
        pushButton_106->setObjectName(QStringLiteral("pushButton_106"));
        pushButton_106->setGeometry(QRect(20, 145, 300, 30));
        pushButton_106->setFont(font2);
        pushButton_106->setCheckable(true);
        pushButton_106->setAutoExclusive(true);
        pushButton_107 = new QPushButton(fivegnrmeawid);
        pushButton_107->setObjectName(QStringLiteral("pushButton_107"));
        pushButton_107->setGeometry(QRect(20, 190, 300, 30));
        pushButton_107->setFont(font2);
        pushButton_107->setCheckable(true);
        pushButton_107->setAutoExclusive(true);
        pushButton_108 = new QPushButton(fivegnrmeawid);
        pushButton_108->setObjectName(QStringLiteral("pushButton_108"));
        pushButton_108->setGeometry(QRect(20, 235, 300, 30));
        pushButton_108->setFont(font2);
        pushButton_108->setCheckable(true);
        pushButton_108->setAutoExclusive(true);
        pushButton_109 = new QPushButton(fivegnrmeawid);
        pushButton_109->setObjectName(QStringLiteral("pushButton_109"));
        pushButton_109->setGeometry(QRect(20, 325, 300, 30));
        pushButton_109->setFont(font2);
        pushButton_109->setCheckable(true);
        pushButton_109->setAutoExclusive(true);
        pushButton_110 = new QPushButton(fivegnrmeawid);
        pushButton_110->setObjectName(QStringLiteral("pushButton_110"));
        pushButton_110->setGeometry(QRect(20, 370, 300, 30));
        pushButton_110->setFont(font2);
        pushButton_110->setCheckable(true);
        pushButton_110->setAutoExclusive(true);
        pushButton_111 = new QPushButton(fivegnrmeawid);
        pushButton_111->setObjectName(QStringLiteral("pushButton_111"));
        pushButton_111->setGeometry(QRect(20, 280, 300, 30));
        pushButton_111->setFont(font2);
        pushButton_111->setCheckable(true);
        pushButton_111->setAutoExclusive(true);
        pushButton_112 = new QPushButton(fivegnrmeawid);
        pushButton_112->setObjectName(QStringLiteral("pushButton_112"));
        pushButton_112->setGeometry(QRect(20, 415, 300, 30));
        pushButton_112->setFont(font2);
        pushButton_112->setCheckable(true);
        pushButton_112->setAutoExclusive(true);
        intermeawid = new QWidget(plusmode);
        intermeawid->setObjectName(QStringLiteral("intermeawid"));
        intermeawid->setGeometry(QRect(620, 50, 261, 241));
        intermeawid->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"night\"] #intermeawid\n"
"{	\n"
"background-color: rgba(0, 0, 0,1);\n"
"}\n"
"#plusmode[pltdismode=\"indoor\"] #intermeawid\n"
"{	\n"
"background-color:rgba(255,255,255,1);\n"
"}\n"
"\n"
"#plusmode[pltdismode=\"indoor\"] QPushButton:!checked\n"
"{\n"
"font: 11pt \"Arial\";\n"
"font-weight:normal;\n"
"background-color: rgba(237, 212, 0,0);\n"
"color: rgb(105, 105, 105);\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QPushButton:!checked\n"
"{\n"
"font: 11pt \"Arial\";\n"
"font-weight:normal;\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#plusmode[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"font: 75 11pt \"Arial\";\n"
"font-weight:bold;\n"
"background-color: rgb(255,181,0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"font: 75 11pt \"Arial\";\n"
"font-weight:bold;\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"\n"
"QPushButton{border-style:flat;text-align:left;}\n"
"QPushBut"
                        "ton{padding-left:10px}"));
        pushButton_43 = new QPushButton(intermeawid);
        pushButton_43->setObjectName(QStringLiteral("pushButton_43"));
        pushButton_43->setGeometry(QRect(20, 55, 300, 30));
        pushButton_43->setFont(font2);
        pushButton_43->setCheckable(true);
        pushButton_43->setChecked(true);
        pushButton_43->setAutoExclusive(true);
        pushButton_45 = new QPushButton(intermeawid);
        pushButton_45->setObjectName(QStringLiteral("pushButton_45"));
        pushButton_45->setGeometry(QRect(20, 145, 300, 30));
        pushButton_45->setFont(font2);
        pushButton_45->setCheckable(true);
        pushButton_45->setAutoExclusive(true);
        pushButton_46 = new QPushButton(intermeawid);
        pushButton_46->setObjectName(QStringLiteral("pushButton_46"));
        pushButton_46->setGeometry(QRect(20, 190, 300, 30));
        pushButton_46->setFont(font2);
        pushButton_46->setCheckable(true);
        pushButton_46->setAutoExclusive(true);
        pushButton_47 = new QPushButton(intermeawid);
        pushButton_47->setObjectName(QStringLiteral("pushButton_47"));
        pushButton_47->setGeometry(QRect(20, 235, 300, 30));
        pushButton_47->setFont(font2);
        pushButton_47->setCheckable(true);
        pushButton_47->setAutoExclusive(true);
        pushButton_48 = new QPushButton(intermeawid);
        pushButton_48->setObjectName(QStringLiteral("pushButton_48"));
        pushButton_48->setGeometry(QRect(20, 100, 300, 30));
        pushButton_48->setFont(font2);
        pushButton_48->setCheckable(true);
        pushButton_48->setAutoExclusive(true);
        pushButton_51 = new QPushButton(intermeawid);
        pushButton_51->setObjectName(QStringLiteral("pushButton_51"));
        pushButton_51->setGeometry(QRect(20, 280, 300, 30));
        pushButton_51->setFont(font2);
        pushButton_51->setCheckable(true);
        pushButton_51->setAutoExclusive(true);
        label_6 = new QLabel(intermeawid);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(22, 28, 121, 17));
        label_6->setFont(font3);
        label_6->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(9, 73, 108,1);\n"
"	background-color: white;\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}\n"
""));
        line_5 = new QFrame(intermeawid);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(22, 48, 400, 2));
        line_5->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] #line_5\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#plusmode[pltdismode=\"night\"] #line_5\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        backwid = new QWidget(plusmode);
        backwid->setObjectName(QStringLiteral("backwid"));
        backwid->setGeometry(QRect(10, 50, 281, 371));
        QFont font4;
        font4.setBold(false);
        font4.setWeight(50);
        backwid->setFont(font4);
        backwid->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"night\"] #backwid\n"
"{	\n"
"background-color: rgba(0, 0, 0,1);\n"
"}\n"
"#plusmode[pltdismode=\"indoor\"] #backwid\n"
"{	\n"
"background-color:rgba(255,255,255,1);\n"
"}\n"
"\n"
"#plusmode[pltdismode=\"indoor\"] QPushButton:!checked\n"
"{\n"
"font: 11pt \"Arial\";\n"
"font-weight:normal;\n"
"background-color: rgba(237, 212, 0,0);\n"
"color: rgb(105, 105, 105);\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QPushButton:!checked\n"
"{\n"
"font: 11pt \"Arial\";\n"
"font-weight:normal;\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#plusmode[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"font: 75 11pt \"Arial\";\n"
"font-weight:bold;\n"
"background-color: rgb(255,181,0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"font: 75 11pt \"Arial\";\n"
"font-weight:bold;\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"\n"
"QPushButton{border-style:flat;text-align:left;}\n"
"QPushButton{padd"
                        "ing-left:10px}"));
        pushButton_4 = new QPushButton(backwid);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setEnabled(false);
        pushButton_4->setGeometry(QRect(20, 190, 237, 30));
        QFont font5;
        font5.setFamily(QStringLiteral("Arial"));
        font5.setPointSize(11);
        font5.setBold(false);
        font5.setItalic(false);
        font5.setWeight(50);
        pushButton_4->setFont(font5);
        pushButton_4->setStyleSheet(QStringLiteral("background-color: rgb(238, 238, 236);"));
        pushButton_4->setCheckable(true);
        pushButton_4->setAutoExclusive(true);
        pushButton_4->setFlat(false);
        pushButton = new QPushButton(backwid);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(20, 55, 237, 30));
        pushButton->setFont(font5);
        pushButton->setStyleSheet(QStringLiteral(""));
        pushButton->setCheckable(true);
        pushButton->setChecked(true);
        pushButton->setAutoExclusive(true);
        pushButton->setFlat(false);
        pushButton_3 = new QPushButton(backwid);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setEnabled(false);
        pushButton_3->setGeometry(QRect(20, 145, 237, 30));
        pushButton_3->setFont(font5);
        pushButton_3->setStyleSheet(QStringLiteral("background-color: rgb(238, 238, 236);"));
        pushButton_3->setCheckable(true);
        pushButton_3->setChecked(false);
        pushButton_3->setAutoExclusive(true);
        pushButton_3->setFlat(false);
        label = new QLabel(backwid);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(22, 28, 81, 17));
        label->setFont(font3);
        label->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(9, 73, 108,1);\n"
"	background-color: white;\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}"));
        pushButton_2 = new QPushButton(backwid);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(20, 100, 237, 30));
        pushButton_2->setFont(font5);
        pushButton_2->setStyleSheet(QStringLiteral(""));
        pushButton_2->setCheckable(true);
        pushButton_2->setAutoExclusive(true);
        pushButton_2->setFlat(false);
        pushButton_5 = new QPushButton(backwid);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setEnabled(true);
        pushButton_5->setGeometry(QRect(20, 235, 237, 30));
        pushButton_5->setFont(font5);
        pushButton_5->setCheckable(true);
        pushButton_5->setAutoExclusive(true);
        pushButton_5->setFlat(false);
        line = new QFrame(backwid);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(280, 0, 2, 800));
        line->setSizeIncrement(QSize(0, 0));
        line->setBaseSize(QSize(0, 0));
        line->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] #line\n"
"{\n"
"background-color: rgba(181, 181, 181,1);\n"
"}\n"
"#plusmode[pltdismode=\"night\"] #line\n"
"{\n"
"background-color: rgba(64, 64, 64,1);\n"
"}"));
        line->setLineWidth(1);
        line->setMidLineWidth(0);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(backwid);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(22, 48, 237, 2));
        line_3->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] #line_3\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#plusmode[pltdismode=\"night\"] #line_3\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        pushButton_18 = new QPushButton(backwid);
        pushButton_18->setObjectName(QStringLiteral("pushButton_18"));
        pushButton_18->setEnabled(true);
        pushButton_18->setGeometry(QRect(20, 280, 237, 30));
        pushButton_18->setFont(font5);
        pushButton_18->setCheckable(true);
        pushButton_18->setAutoExclusive(true);
        pushButton_18->setFlat(false);
        pushButton_19 = new QPushButton(backwid);
        pushButton_19->setObjectName(QStringLiteral("pushButton_19"));
        pushButton_19->setGeometry(QRect(20, 325, 237, 30));
        pushButton_19->setFont(font5);
        pushButton_19->setStyleSheet(QStringLiteral(""));
        pushButton_19->setCheckable(true);
        pushButton_19->setAutoExclusive(true);
        pushButton_19->setFlat(false);
        ltefddmeawid = new QWidget(plusmode);
        ltefddmeawid->setObjectName(QStringLiteral("ltefddmeawid"));
        ltefddmeawid->setGeometry(QRect(890, 50, 381, 361));
        ltefddmeawid->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"night\"] #ltefddmeawid\n"
"{	\n"
"background-color: rgba(0, 0, 0,1);\n"
"}\n"
"#plusmode[pltdismode=\"indoor\"] #ltefddmeawid\n"
"{	\n"
"background-color:rgba(255,255,255,1);\n"
"}\n"
"\n"
"#plusmode[pltdismode=\"indoor\"] QPushButton:!checked\n"
"{\n"
"font: 11pt \"Arial\";\n"
"font-weight:normal;\n"
"background-color: rgba(237, 212, 0,0);\n"
"color: rgb(105, 105, 105);\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QPushButton:!checked\n"
"{\n"
"font: 11pt \"Arial\";\n"
"font-weight:normal;\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#plusmode[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"font: 75 11pt \"Arial\";\n"
"font-weight:bold;\n"
"background-color: rgb(255,181,0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"font: 75 11pt \"Arial\";\n"
"font-weight:bold;\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"\n"
"QPushButton{border-style:flat;text-align:left;}\n"
"QPushB"
                        "utton{padding-left:10px}"));
        pushButton_54 = new QPushButton(ltefddmeawid);
        pushButton_54->setObjectName(QStringLiteral("pushButton_54"));
        pushButton_54->setGeometry(QRect(20, 190, 300, 30));
        pushButton_54->setFont(font2);
        pushButton_54->setCheckable(true);
        pushButton_54->setAutoExclusive(true);
        pushButton_55 = new QPushButton(ltefddmeawid);
        pushButton_55->setObjectName(QStringLiteral("pushButton_55"));
        pushButton_55->setGeometry(QRect(20, 235, 300, 30));
        pushButton_55->setFont(font2);
        pushButton_55->setCheckable(true);
        pushButton_55->setAutoExclusive(true);
        pushButton_56 = new QPushButton(ltefddmeawid);
        pushButton_56->setObjectName(QStringLiteral("pushButton_56"));
        pushButton_56->setGeometry(QRect(20, 55, 300, 30));
        QFont font6;
        font6.setFamily(QStringLiteral("Arial"));
        font6.setBold(false);
        font6.setWeight(50);
        pushButton_56->setFont(font6);
        pushButton_56->setCheckable(true);
        pushButton_56->setChecked(true);
        pushButton_56->setAutoExclusive(true);
        pushButton_59 = new QPushButton(ltefddmeawid);
        pushButton_59->setObjectName(QStringLiteral("pushButton_59"));
        pushButton_59->setGeometry(QRect(20, 145, 300, 30));
        pushButton_59->setFont(font2);
        pushButton_59->setCheckable(true);
        pushButton_59->setAutoExclusive(true);
        pushButton_60 = new QPushButton(ltefddmeawid);
        pushButton_60->setObjectName(QStringLiteral("pushButton_60"));
        pushButton_60->setGeometry(QRect(20, 505, 300, 30));
        pushButton_60->setFont(font2);
        pushButton_60->setCheckable(true);
        pushButton_60->setAutoExclusive(true);
        pushButton_61 = new QPushButton(ltefddmeawid);
        pushButton_61->setObjectName(QStringLiteral("pushButton_61"));
        pushButton_61->setGeometry(QRect(20, 550, 300, 30));
        pushButton_61->setFont(font2);
        pushButton_61->setCheckable(true);
        pushButton_61->setAutoExclusive(true);
        pushButton_63 = new QPushButton(ltefddmeawid);
        pushButton_63->setObjectName(QStringLiteral("pushButton_63"));
        pushButton_63->setGeometry(QRect(20, 100, 300, 30));
        pushButton_63->setFont(font6);
        pushButton_63->setCheckable(true);
        pushButton_63->setAutoExclusive(true);
        pushButton_57 = new QPushButton(ltefddmeawid);
        pushButton_57->setObjectName(QStringLiteral("pushButton_57"));
        pushButton_57->setGeometry(QRect(20, 280, 300, 30));
        pushButton_57->setFont(font2);
        pushButton_57->setCheckable(true);
        pushButton_57->setAutoExclusive(true);
        label_7 = new QLabel(ltefddmeawid);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(22, 28, 91, 17));
        label_7->setFont(font3);
        label_7->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(9, 73, 108,1);\n"
"	background-color: white;\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}\n"
""));
        line_6 = new QFrame(ltefddmeawid);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(22, 48, 400, 2));
        line_6->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] #line_6\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#plusmode[pltdismode=\"night\"] #line_6\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);
        pushButton_62 = new QPushButton(ltefddmeawid);
        pushButton_62->setObjectName(QStringLiteral("pushButton_62"));
        pushButton_62->setGeometry(QRect(20, 325, 300, 30));
        pushButton_62->setFont(font2);
        pushButton_62->setCheckable(true);
        pushButton_62->setAutoExclusive(true);
        pushButton_64 = new QPushButton(ltefddmeawid);
        pushButton_64->setObjectName(QStringLiteral("pushButton_64"));
        pushButton_64->setGeometry(QRect(20, 370, 300, 30));
        pushButton_64->setFont(font6);
        pushButton_64->setCheckable(true);
        pushButton_64->setChecked(false);
        pushButton_64->setAutoExclusive(true);
        pushButton_66 = new QPushButton(ltefddmeawid);
        pushButton_66->setObjectName(QStringLiteral("pushButton_66"));
        pushButton_66->setGeometry(QRect(20, 415, 300, 30));
        pushButton_66->setFont(font6);
        pushButton_66->setCheckable(true);
        pushButton_66->setAutoExclusive(true);
        pushButton_67 = new QPushButton(ltefddmeawid);
        pushButton_67->setObjectName(QStringLiteral("pushButton_67"));
        pushButton_67->setGeometry(QRect(20, 460, 300, 30));
        pushButton_67->setFont(font6);
        pushButton_67->setCheckable(true);
        pushButton_67->setAutoExclusive(true);
        pushButton_68 = new QPushButton(ltefddmeawid);
        pushButton_68->setObjectName(QStringLiteral("pushButton_68"));
        pushButton_68->setGeometry(QRect(465, 55, 300, 30));
        pushButton_68->setFont(font6);
        pushButton_68->setCheckable(true);
        pushButton_68->setAutoExclusive(true);
        pushButton_69 = new QPushButton(ltefddmeawid);
        pushButton_69->setObjectName(QStringLiteral("pushButton_69"));
        pushButton_69->setGeometry(QRect(465, 100, 300, 30));
        pushButton_69->setFont(font6);
        pushButton_69->setCheckable(true);
        pushButton_69->setAutoExclusive(true);
        pushButton_70 = new QPushButton(ltefddmeawid);
        pushButton_70->setObjectName(QStringLiteral("pushButton_70"));
        pushButton_70->setGeometry(QRect(465, 145, 300, 30));
        pushButton_70->setFont(font6);
        pushButton_70->setCheckable(true);
        pushButton_70->setAutoExclusive(true);
        pushButton_71 = new QPushButton(ltefddmeawid);
        pushButton_71->setObjectName(QStringLiteral("pushButton_71"));
        pushButton_71->setGeometry(QRect(465, 190, 300, 30));
        pushButton_71->setFont(font6);
        pushButton_71->setCheckable(true);
        pushButton_71->setAutoExclusive(true);
        pushButton_72 = new QPushButton(ltefddmeawid);
        pushButton_72->setObjectName(QStringLiteral("pushButton_72"));
        pushButton_72->setGeometry(QRect(465, 235, 300, 30));
        pushButton_72->setFont(font2);
        pushButton_72->setCheckable(true);
        pushButton_72->setAutoExclusive(true);
        pushButton_73 = new QPushButton(ltefddmeawid);
        pushButton_73->setObjectName(QStringLiteral("pushButton_73"));
        pushButton_73->setGeometry(QRect(465, 280, 300, 30));
        pushButton_73->setFont(font2);
        pushButton_73->setCheckable(true);
        pushButton_73->setAutoExclusive(true);
        line_8 = new QFrame(ltefddmeawid);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setGeometry(QRect(465, 48, 400, 2));
        line_8->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] #line_8\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#plusmode[pltdismode=\"night\"] #line_8\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);
        pushButton_94 = new QPushButton(ltefddmeawid);
        pushButton_94->setObjectName(QStringLiteral("pushButton_94"));
        pushButton_94->setGeometry(QRect(465, 325, 300, 30));
        pushButton_94->setFont(font2);
        pushButton_94->setCheckable(true);
        pushButton_94->setAutoExclusive(true);
        pushButton_95 = new QPushButton(ltefddmeawid);
        pushButton_95->setObjectName(QStringLiteral("pushButton_95"));
        pushButton_95->setGeometry(QRect(465, 370, 300, 30));
        pushButton_95->setFont(font2);
        pushButton_95->setCheckable(true);
        pushButton_95->setAutoExclusive(true);
        pushButton_96 = new QPushButton(ltefddmeawid);
        pushButton_96->setObjectName(QStringLiteral("pushButton_96"));
        pushButton_96->setGeometry(QRect(465, 415, 300, 30));
        pushButton_96->setFont(font2);
        pushButton_96->setCheckable(true);
        pushButton_96->setAutoExclusive(true);
        pushButton_97 = new QPushButton(ltefddmeawid);
        pushButton_97->setObjectName(QStringLiteral("pushButton_97"));
        pushButton_97->setGeometry(QRect(465, 460, 300, 30));
        pushButton_97->setFont(font2);
        pushButton_97->setCheckable(true);
        pushButton_97->setAutoExclusive(true);
        pushButton_98 = new QPushButton(ltefddmeawid);
        pushButton_98->setObjectName(QStringLiteral("pushButton_98"));
        pushButton_98->setGeometry(QRect(465, 505, 300, 30));
        pushButton_98->setFont(font2);
        pushButton_98->setCheckable(true);
        pushButton_98->setAutoExclusive(true);
        rtsameawid = new QWidget(plusmode);
        rtsameawid->setObjectName(QStringLiteral("rtsameawid"));
        rtsameawid->setGeometry(QRect(300, 500, 331, 281));
        rtsameawid->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"night\"] #rtsameawid\n"
"{	\n"
"background-color: rgba(0, 0, 0,1);\n"
"}\n"
"#plusmode[pltdismode=\"indoor\"] #rtsameawid\n"
"{	\n"
"background-color:rgba(255,255,255,1);\n"
"}\n"
"\n"
"#plusmode[pltdismode=\"indoor\"] QPushButton:!checked\n"
"{\n"
"font: 11pt \"Arial\";\n"
"font-weight:normal;\n"
"background-color: rgba(237, 212, 0,0);\n"
"color: rgb(105, 105, 105);\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QPushButton:!checked\n"
"{\n"
"font: 11pt \"Arial\";\n"
"font-weight:normal;\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#plusmode[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"font: 75 11pt \"Arial\";\n"
"font-weight:bold;\n"
"background-color: rgb(255,181,0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"font: 75 11pt \"Arial\";\n"
"font-weight:bold;\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"\n"
"QPushButton{border-style:flat;text-align:left;}\n"
"QPushButto"
                        "n{padding-left:10px}\n"
""));
        pushButton_30 = new QPushButton(rtsameawid);
        pushButton_30->setObjectName(QStringLiteral("pushButton_30"));
        pushButton_30->setGeometry(QRect(20, 55, 300, 30));
        pushButton_30->setFont(font2);
        pushButton_30->setCheckable(true);
        pushButton_30->setChecked(true);
        pushButton_30->setAutoExclusive(true);
        pushButton_37 = new QPushButton(rtsameawid);
        pushButton_37->setObjectName(QStringLiteral("pushButton_37"));
        pushButton_37->setGeometry(QRect(20, 100, 300, 30));
        pushButton_37->setFont(font2);
        pushButton_37->setCheckable(true);
        pushButton_37->setAutoExclusive(true);
        label_5 = new QLabel(rtsameawid);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(22, 28, 101, 17));
        label_5->setFont(font3);
        label_5->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(9, 73, 108,1);\n"
"	background-color: white;\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}"));
        line_7 = new QFrame(rtsameawid);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setGeometry(QRect(22, 48, 400, 2));
        line_7->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] #line_7\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#plusmode[pltdismode=\"night\"] #line_7\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);
        pushButton_38 = new QPushButton(rtsameawid);
        pushButton_38->setObjectName(QStringLiteral("pushButton_38"));
        pushButton_38->setGeometry(QRect(20, 145, 300, 30));
        pushButton_38->setFont(font2);
        pushButton_38->setCheckable(true);
        pushButton_38->setAutoExclusive(true);
        pushButton_39 = new QPushButton(rtsameawid);
        pushButton_39->setObjectName(QStringLiteral("pushButton_39"));
        pushButton_39->setGeometry(QRect(20, 190, 300, 41));
        pushButton_39->setFont(font2);
        pushButton_39->setCheckable(true);
        pushButton_39->setAutoExclusive(true);
        sameawid = new QWidget(plusmode);
        sameawid->setObjectName(QStringLiteral("sameawid"));
        sameawid->setGeometry(QRect(640, 290, 251, 501));
        sameawid->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"night\"] #sameawid\n"
"{	\n"
"background-color: rgba(0, 0, 0,1);\n"
"}\n"
"#plusmode[pltdismode=\"indoor\"] #sameawid\n"
"{	\n"
"background-color:rgba(255,255,255,1);\n"
"}\n"
"\n"
"#plusmode[pltdismode=\"indoor\"] QPushButton:!checked\n"
"{\n"
"font: 11pt \"Arial\";\n"
"font-weight:normal;\n"
"background-color: rgba(237, 212, 0,0);\n"
"color: rgb(105, 105, 105);\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QPushButton:!checked\n"
"{\n"
"font: 11pt \"Arial\";\n"
"font-weight:normal;\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#plusmode[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"font: 75 11pt \"Arial\";\n"
"font-weight:bold;\n"
"background-color: rgb(255,181,0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"font: 75 11pt \"Arial\";\n"
"font-weight:bold;\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"\n"
"QPushButton{border-style:flat;text-align:left;}\n"
"QPushButton{pa"
                        "dding-left:10px}"));
        pushButton_11 = new QPushButton(sameawid);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));
        pushButton_11->setEnabled(true);
        pushButton_11->setGeometry(QRect(20, 190, 300, 30));
        pushButton_11->setFont(font2);
        pushButton_11->setCheckable(true);
        pushButton_11->setAutoExclusive(true);
        pushButton_13 = new QPushButton(sameawid);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));
        pushButton_13->setEnabled(false);
        pushButton_13->setGeometry(QRect(20, 370, 300, 30));
        pushButton_13->setFont(font2);
        pushButton_13->setCheckable(true);
        pushButton_13->setAutoExclusive(true);
        pushButton_6 = new QPushButton(sameawid);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(20, 55, 300, 30));
        pushButton_6->setFont(font6);
        pushButton_6->setCheckable(true);
        pushButton_6->setChecked(true);
        pushButton_6->setAutoExclusive(true);
        pushButton_12 = new QPushButton(sameawid);
        pushButton_12->setObjectName(QStringLiteral("pushButton_12"));
        pushButton_12->setEnabled(true);
        pushButton_12->setGeometry(QRect(20, 325, 300, 30));
        pushButton_12->setFont(font2);
        pushButton_12->setCheckable(true);
        pushButton_12->setAutoExclusive(true);
        pushButton_8 = new QPushButton(sameawid);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setEnabled(true);
        pushButton_8->setGeometry(QRect(20, 145, 300, 30));
        pushButton_8->setFont(font2);
        pushButton_8->setCheckable(true);
        pushButton_8->setAutoExclusive(true);
        pushButton_9 = new QPushButton(sameawid);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setEnabled(true);
        pushButton_9->setGeometry(QRect(20, 280, 300, 30));
        pushButton_9->setFont(font2);
        pushButton_9->setCheckable(true);
        pushButton_9->setAutoExclusive(true);
        pushButton_10 = new QPushButton(sameawid);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        pushButton_10->setEnabled(true);
        pushButton_10->setGeometry(QRect(20, 235, 300, 30));
        pushButton_10->setFont(font2);
        pushButton_10->setCheckable(true);
        pushButton_10->setAutoExclusive(true);
        pushButton_14 = new QPushButton(sameawid);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));
        pushButton_14->setEnabled(false);
        pushButton_14->setGeometry(QRect(20, 415, 300, 30));
        pushButton_14->setFont(font2);
        pushButton_14->setCheckable(true);
        pushButton_14->setAutoExclusive(true);
        label_3 = new QLabel(sameawid);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(22, 28, 111, 17));
        label_3->setFont(font3);
        label_3->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(9, 73, 108,1);\n"
"	background-color: white;\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}\n"
""));
        pushButton_7 = new QPushButton(sameawid);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setEnabled(true);
        pushButton_7->setGeometry(QRect(20, 100, 300, 30));
        pushButton_7->setFont(font2);
        pushButton_7->setCheckable(true);
        pushButton_7->setAutoExclusive(true);
        line_2 = new QFrame(sameawid);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(22, 48, 400, 2));
        line_2->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] #line_2\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#plusmode[pltdismode=\"night\"] #line_2\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        ltetddmeawid = new QWidget(plusmode);
        ltetddmeawid->setObjectName(QStringLiteral("ltetddmeawid"));
        ltetddmeawid->setGeometry(QRect(20, 430, 271, 391));
        ltetddmeawid->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"night\"] #ltetddmeawid\n"
"{	\n"
"background-color: rgba(0, 0, 0,1);\n"
"}\n"
"#plusmode[pltdismode=\"indoor\"] #ltetddmeawid\n"
"{	\n"
"background-color:rgba(255,255,255,1);\n"
"}\n"
"\n"
"#plusmode[pltdismode=\"indoor\"] QPushButton:!checked\n"
"{\n"
"font: 11pt \"Arial\";\n"
"font-weight:normal;\n"
"background-color: rgba(237, 212, 0,0);\n"
"color: rgb(105, 105, 105);\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QPushButton:!checked\n"
"{\n"
"font: 11pt \"Arial\";\n"
"font-weight:normal;\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#plusmode[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"font: 75 11pt \"Arial\";\n"
"font-weight:bold;\n"
"background-color: rgb(255,181,0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"font: 75 11pt \"Arial\";\n"
"font-weight:bold;\n"
"background-color: rgb(255, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
"\n"
"QPushButton{border-style:flat;text-align:left;}\n"
"QPushB"
                        "utton{padding-left:10px}\n"
""));
        pushButton_74 = new QPushButton(ltetddmeawid);
        pushButton_74->setObjectName(QStringLiteral("pushButton_74"));
        pushButton_74->setGeometry(QRect(20, 190, 300, 30));
        pushButton_74->setFont(font2);
        pushButton_74->setCheckable(true);
        pushButton_74->setAutoExclusive(true);
        pushButton_75 = new QPushButton(ltetddmeawid);
        pushButton_75->setObjectName(QStringLiteral("pushButton_75"));
        pushButton_75->setGeometry(QRect(20, 280, 300, 30));
        pushButton_75->setFont(font2);
        pushButton_75->setCheckable(true);
        pushButton_75->setAutoExclusive(true);
        pushButton_76 = new QPushButton(ltetddmeawid);
        pushButton_76->setObjectName(QStringLiteral("pushButton_76"));
        pushButton_76->setGeometry(QRect(20, 55, 300, 30));
        pushButton_76->setFont(font6);
        pushButton_76->setCheckable(true);
        pushButton_76->setChecked(true);
        pushButton_76->setAutoExclusive(true);
        pushButton_77 = new QPushButton(ltetddmeawid);
        pushButton_77->setObjectName(QStringLiteral("pushButton_77"));
        pushButton_77->setGeometry(QRect(20, 235, 300, 30));
        pushButton_77->setFont(font2);
        pushButton_77->setCheckable(true);
        pushButton_77->setAutoExclusive(true);
        pushButton_78 = new QPushButton(ltetddmeawid);
        pushButton_78->setObjectName(QStringLiteral("pushButton_78"));
        pushButton_78->setGeometry(QRect(20, 145, 300, 30));
        pushButton_78->setFont(font2);
        pushButton_78->setCheckable(true);
        pushButton_78->setAutoExclusive(true);
        pushButton_79 = new QPushButton(ltetddmeawid);
        pushButton_79->setObjectName(QStringLiteral("pushButton_79"));
        pushButton_79->setGeometry(QRect(20, 505, 300, 30));
        pushButton_79->setFont(font2);
        pushButton_79->setCheckable(true);
        pushButton_79->setAutoExclusive(true);
        pushButton_80 = new QPushButton(ltetddmeawid);
        pushButton_80->setObjectName(QStringLiteral("pushButton_80"));
        pushButton_80->setGeometry(QRect(20, 550, 300, 30));
        pushButton_80->setFont(font2);
        pushButton_80->setCheckable(true);
        pushButton_80->setAutoExclusive(true);
        pushButton_81 = new QPushButton(ltetddmeawid);
        pushButton_81->setObjectName(QStringLiteral("pushButton_81"));
        pushButton_81->setGeometry(QRect(20, 100, 300, 30));
        pushButton_81->setFont(font6);
        pushButton_81->setCheckable(true);
        pushButton_81->setAutoExclusive(true);
        pushButton_82 = new QPushButton(ltetddmeawid);
        pushButton_82->setObjectName(QStringLiteral("pushButton_82"));
        pushButton_82->setGeometry(QRect(20, 325, 300, 30));
        pushButton_82->setFont(font2);
        pushButton_82->setCheckable(true);
        pushButton_82->setAutoExclusive(true);
        label_9 = new QLabel(ltetddmeawid);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(22, 28, 91, 17));
        label_9->setFont(font3);
        label_9->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(9, 73, 108,1);\n"
"	background-color: white;\n"
"}\n"
"#plusmode[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}\n"
""));
        line_9 = new QFrame(ltetddmeawid);
        line_9->setObjectName(QStringLiteral("line_9"));
        line_9->setGeometry(QRect(22, 48, 400, 2));
        line_9->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] #line_9\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#plusmode[pltdismode=\"night\"] #line_9\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_9->setFrameShape(QFrame::HLine);
        line_9->setFrameShadow(QFrame::Sunken);
        pushButton_83 = new QPushButton(ltetddmeawid);
        pushButton_83->setObjectName(QStringLiteral("pushButton_83"));
        pushButton_83->setGeometry(QRect(20, 370, 300, 30));
        pushButton_83->setFont(font2);
        pushButton_83->setCheckable(true);
        pushButton_83->setAutoExclusive(true);
        pushButton_84 = new QPushButton(ltetddmeawid);
        pushButton_84->setObjectName(QStringLiteral("pushButton_84"));
        pushButton_84->setGeometry(QRect(20, 415, 300, 30));
        pushButton_84->setFont(font6);
        pushButton_84->setCheckable(true);
        pushButton_84->setChecked(false);
        pushButton_84->setAutoExclusive(true);
        pushButton_85 = new QPushButton(ltetddmeawid);
        pushButton_85->setObjectName(QStringLiteral("pushButton_85"));
        pushButton_85->setGeometry(QRect(20, 460, 300, 30));
        pushButton_85->setFont(font6);
        pushButton_85->setCheckable(true);
        pushButton_85->setAutoExclusive(true);
        pushButton_86 = new QPushButton(ltetddmeawid);
        pushButton_86->setObjectName(QStringLiteral("pushButton_86"));
        pushButton_86->setGeometry(QRect(465, 55, 300, 30));
        pushButton_86->setFont(font6);
        pushButton_86->setCheckable(true);
        pushButton_86->setAutoExclusive(true);
        pushButton_87 = new QPushButton(ltetddmeawid);
        pushButton_87->setObjectName(QStringLiteral("pushButton_87"));
        pushButton_87->setGeometry(QRect(465, 100, 300, 30));
        pushButton_87->setFont(font6);
        pushButton_87->setCheckable(true);
        pushButton_87->setAutoExclusive(true);
        pushButton_88 = new QPushButton(ltetddmeawid);
        pushButton_88->setObjectName(QStringLiteral("pushButton_88"));
        pushButton_88->setGeometry(QRect(465, 145, 300, 30));
        pushButton_88->setFont(font6);
        pushButton_88->setCheckable(true);
        pushButton_88->setAutoExclusive(true);
        pushButton_89 = new QPushButton(ltetddmeawid);
        pushButton_89->setObjectName(QStringLiteral("pushButton_89"));
        pushButton_89->setGeometry(QRect(465, 190, 300, 30));
        pushButton_89->setFont(font6);
        pushButton_89->setCheckable(true);
        pushButton_89->setAutoExclusive(true);
        pushButton_90 = new QPushButton(ltetddmeawid);
        pushButton_90->setObjectName(QStringLiteral("pushButton_90"));
        pushButton_90->setGeometry(QRect(465, 235, 300, 30));
        pushButton_90->setFont(font6);
        pushButton_90->setCheckable(true);
        pushButton_90->setAutoExclusive(true);
        pushButton_91 = new QPushButton(ltetddmeawid);
        pushButton_91->setObjectName(QStringLiteral("pushButton_91"));
        pushButton_91->setGeometry(QRect(465, 280, 300, 30));
        pushButton_91->setFont(font6);
        pushButton_91->setCheckable(true);
        pushButton_91->setAutoExclusive(true);
        pushButton_92 = new QPushButton(ltetddmeawid);
        pushButton_92->setObjectName(QStringLiteral("pushButton_92"));
        pushButton_92->setGeometry(QRect(465, 325, 300, 30));
        pushButton_92->setFont(font2);
        pushButton_92->setCheckable(true);
        pushButton_92->setAutoExclusive(true);
        pushButton_93 = new QPushButton(ltetddmeawid);
        pushButton_93->setObjectName(QStringLiteral("pushButton_93"));
        pushButton_93->setGeometry(QRect(465, 370, 300, 30));
        pushButton_93->setFont(font2);
        pushButton_93->setCheckable(true);
        pushButton_93->setAutoExclusive(true);
        line_10 = new QFrame(ltetddmeawid);
        line_10->setObjectName(QStringLiteral("line_10"));
        line_10->setGeometry(QRect(465, 48, 400, 2));
        line_10->setStyleSheet(QLatin1String("#plusmode[pltdismode=\"indoor\"] #line_10\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#plusmode[pltdismode=\"night\"] #line_10\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_10->setFrameShape(QFrame::HLine);
        line_10->setFrameShadow(QFrame::Sunken);
        pushButton_99 = new QPushButton(ltetddmeawid);
        pushButton_99->setObjectName(QStringLiteral("pushButton_99"));
        pushButton_99->setGeometry(QRect(465, 415, 300, 30));
        pushButton_99->setFont(font2);
        pushButton_99->setCheckable(true);
        pushButton_99->setAutoExclusive(true);
        pushButton_100 = new QPushButton(ltetddmeawid);
        pushButton_100->setObjectName(QStringLiteral("pushButton_100"));
        pushButton_100->setGeometry(QRect(465, 460, 300, 30));
        pushButton_100->setFont(font2);
        pushButton_100->setCheckable(true);
        pushButton_100->setAutoExclusive(true);
        pushButton_101 = new QPushButton(ltetddmeawid);
        pushButton_101->setObjectName(QStringLiteral("pushButton_101"));
        pushButton_101->setGeometry(QRect(465, 505, 300, 30));
        pushButton_101->setFont(font2);
        pushButton_101->setCheckable(true);
        pushButton_101->setAutoExclusive(true);
        pushButton_102 = new QPushButton(ltetddmeawid);
        pushButton_102->setObjectName(QStringLiteral("pushButton_102"));
        pushButton_102->setGeometry(QRect(465, 550, 300, 30));
        pushButton_102->setFont(font2);
        pushButton_102->setCheckable(true);
        pushButton_102->setAutoExclusive(true);
        pushButton_103 = new QPushButton(ltetddmeawid);
        pushButton_103->setObjectName(QStringLiteral("pushButton_103"));
        pushButton_103->setGeometry(QRect(465, 595, 300, 30));
        pushButton_103->setFont(font2);
        pushButton_103->setCheckable(true);
        pushButton_103->setAutoExclusive(true);

        retranslateUi(plusmode);

        QMetaObject::connectSlotsByName(plusmode);
    } // setupUi

    void retranslateUi(QDialog *plusmode)
    {
        plusmode->setWindowTitle(QApplication::translate("plusmode", "Dialog", Q_NULLPTR));
        plusmode->setProperty("pltdismode", QVariant(QApplication::translate("plusmode", "indoor", Q_NULLPTR)));
        label_2->setText(QString());
        label_8->setText(QApplication::translate("plusmode", "Mode - Measure", Q_NULLPTR));
        pushButton_15->setText(QString());
        pushButton_17->setText(QApplication::translate("plusmode", "Cancel", Q_NULLPTR));
        pushButton_16->setText(QApplication::translate("plusmode", "OK", Q_NULLPTR));
        pushButton_49->setText(QApplication::translate("plusmode", "Internal Power Meter", Q_NULLPTR));
        pushButton_53->setText(QApplication::translate("plusmode", "External Power Meter", Q_NULLPTR));
        label_4->setText(QApplication::translate("plusmode", "Measure", Q_NULLPTR));
        pushButton_52->setText(QApplication::translate("plusmode", "Spectrum", Q_NULLPTR));
        pushButton_105->setText(QApplication::translate("plusmode", "Channel Power", Q_NULLPTR));
        label_11->setText(QApplication::translate("plusmode", "Measure", Q_NULLPTR));
        pushButton_106->setText(QApplication::translate("plusmode", "Occupied BW", Q_NULLPTR));
        pushButton_107->setText(QApplication::translate("plusmode", "Multi-Beam", Q_NULLPTR));
        pushButton_108->setText(QApplication::translate("plusmode", "Single Beam", Q_NULLPTR));
        pushButton_109->setText(QApplication::translate("plusmode", "EIRP Normal View", Q_NULLPTR));
        pushButton_110->setText(QApplication::translate("plusmode", "EIRP Quick View", Q_NULLPTR));
        pushButton_111->setText(QApplication::translate("plusmode", "PCI Scanner", Q_NULLPTR));
        pushButton_112->setText(QApplication::translate("plusmode", "Route Map", Q_NULLPTR));
        pushButton_43->setText(QApplication::translate("plusmode", "Spectrum", Q_NULLPTR));
        pushButton_45->setText(QApplication::translate("plusmode", "RSSI", Q_NULLPTR));
        pushButton_46->setText(QApplication::translate("plusmode", "Coverage Mapping", Q_NULLPTR));
        pushButton_47->setText(QApplication::translate("plusmode", "Persistent Spectrum", Q_NULLPTR));
        pushButton_48->setText(QApplication::translate("plusmode", "Spectrogarm", Q_NULLPTR));
        pushButton_51->setText(QApplication::translate("plusmode", "Persistent Spectrogram", Q_NULLPTR));
        label_6->setText(QApplication::translate("plusmode", "Measure", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("plusmode", "Power Meter", Q_NULLPTR));
        pushButton->setText(QApplication::translate("plusmode", "Spectrum Analyzer", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("plusmode", "Interference Analyzer", Q_NULLPTR));
        label->setText(QApplication::translate("plusmode", "Mode", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("plusmode", "Realtime Spectrum Analyzer", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("plusmode", "LTE-A FDD", Q_NULLPTR));
        pushButton_18->setText(QApplication::translate("plusmode", "LTE-A TDD", Q_NULLPTR));
        pushButton_19->setText(QApplication::translate("plusmode", "5G-NR Analyzer", Q_NULLPTR));
        pushButton_54->setText(QApplication::translate("plusmode", "Power vs Time(Frame)", Q_NULLPTR));
        pushButton_55->setText(QApplication::translate("plusmode", "Constellation", Q_NULLPTR));
        pushButton_56->setText(QApplication::translate("plusmode", "Spectrum", Q_NULLPTR));
        pushButton_59->setText(QApplication::translate("plusmode", "Occupied BW", Q_NULLPTR));
        pushButton_60->setText(QApplication::translate("plusmode", "Spurious EM", Q_NULLPTR));
        pushButton_61->setText(QApplication::translate("plusmode", "ACLR", Q_NULLPTR));
        pushButton_63->setText(QApplication::translate("plusmode", "Channel Power", Q_NULLPTR));
        pushButton_57->setText(QApplication::translate("plusmode", "Data Channel", Q_NULLPTR));
        label_7->setText(QApplication::translate("plusmode", "Measure", Q_NULLPTR));
        pushButton_62->setText(QApplication::translate("plusmode", "Control Channel", Q_NULLPTR));
        pushButton_64->setText(QApplication::translate("plusmode", "Frame Analysis", Q_NULLPTR));
        pushButton_66->setText(QApplication::translate("plusmode", "Data Allocation Map", Q_NULLPTR));
        pushButton_67->setText(QApplication::translate("plusmode", "Channel Scanner", Q_NULLPTR));
        pushButton_68->setText(QApplication::translate("plusmode", "ID Scanner", Q_NULLPTR));
        pushButton_69->setText(QApplication::translate("plusmode", "Route Map", Q_NULLPTR));
        pushButton_70->setText(QApplication::translate("plusmode", "Control Channel", Q_NULLPTR));
        pushButton_71->setText(QApplication::translate("plusmode", "Datagram", Q_NULLPTR));
        pushButton_72->setText(QApplication::translate("plusmode", "Multipath Profile", Q_NULLPTR));
        pushButton_73->setText(QApplication::translate("plusmode", "Carrier Aggregation", Q_NULLPTR));
        pushButton_94->setText(QApplication::translate("plusmode", "Conformance Test", Q_NULLPTR));
        pushButton_95->setText(QApplication::translate("plusmode", "Maintenance Test", Q_NULLPTR));
        pushButton_96->setText(QApplication::translate("plusmode", "Signal Performance", Q_NULLPTR));
        pushButton_97->setText(QApplication::translate("plusmode", "DAS Test", Q_NULLPTR));
        pushButton_98->setText(QApplication::translate("plusmode", "Power Statistics CCDF", Q_NULLPTR));
        pushButton_30->setText(QApplication::translate("plusmode", "Realtime Spectrogram", Q_NULLPTR));
        pushButton_37->setText(QApplication::translate("plusmode", "Persistent Density", Q_NULLPTR));
        label_5->setText(QApplication::translate("plusmode", "Measure", Q_NULLPTR));
        pushButton_38->setText(QApplication::translate("plusmode", "Persistent Spectrogram", Q_NULLPTR));
        pushButton_39->setText(QApplication::translate("plusmode", "Persistent Density Spectrogram", Q_NULLPTR));
        pushButton_11->setText(QApplication::translate("plusmode", "Adjacent Channel Power ", Q_NULLPTR));
        pushButton_13->setText(QApplication::translate("plusmode", "Field Strength", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("plusmode", "Swept SA", Q_NULLPTR));
        pushButton_12->setText(QApplication::translate("plusmode", "Spurious Emission", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("plusmode", "Occupied Bandwidth", Q_NULLPTR));
        pushButton_9->setText(QApplication::translate("plusmode", "Spectrum Emission Mask ", Q_NULLPTR));
        pushButton_10->setText(QApplication::translate("plusmode", "Multi-Adjacent Channel Power", Q_NULLPTR));
        pushButton_14->setText(QApplication::translate("plusmode", "AM/FM Audio Demodulation", Q_NULLPTR));
        label_3->setText(QApplication::translate("plusmode", "Measure", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("plusmode", "Channel Power", Q_NULLPTR));
        pushButton_74->setText(QApplication::translate("plusmode", "Power vs Time(Frame)", Q_NULLPTR));
        pushButton_75->setText(QApplication::translate("plusmode", "Constellation", Q_NULLPTR));
        pushButton_76->setText(QApplication::translate("plusmode", "Spectrum", Q_NULLPTR));
        pushButton_77->setText(QApplication::translate("plusmode", "Power vs Time(Slot)", Q_NULLPTR));
        pushButton_78->setText(QApplication::translate("plusmode", "Occupied BW", Q_NULLPTR));
        pushButton_79->setText(QApplication::translate("plusmode", "Spurious EM", Q_NULLPTR));
        pushButton_80->setText(QApplication::translate("plusmode", "ACLR", Q_NULLPTR));
        pushButton_81->setText(QApplication::translate("plusmode", "Channel Power", Q_NULLPTR));
        pushButton_82->setText(QApplication::translate("plusmode", "Data Channel", Q_NULLPTR));
        label_9->setText(QApplication::translate("plusmode", "Measure", Q_NULLPTR));
        pushButton_83->setText(QApplication::translate("plusmode", "Control Channel", Q_NULLPTR));
        pushButton_84->setText(QApplication::translate("plusmode", "Frame Analysis", Q_NULLPTR));
        pushButton_85->setText(QApplication::translate("plusmode", "Time Alignment Error", Q_NULLPTR));
        pushButton_86->setText(QApplication::translate("plusmode", "Data Allocation Map", Q_NULLPTR));
        pushButton_87->setText(QApplication::translate("plusmode", "Channel Scanner", Q_NULLPTR));
        pushButton_88->setText(QApplication::translate("plusmode", "ID Scanner", Q_NULLPTR));
        pushButton_89->setText(QApplication::translate("plusmode", "Route Map", Q_NULLPTR));
        pushButton_90->setText(QApplication::translate("plusmode", "Control Channel", Q_NULLPTR));
        pushButton_91->setText(QApplication::translate("plusmode", "Datagram", Q_NULLPTR));
        pushButton_92->setText(QApplication::translate("plusmode", "Multipath Profile", Q_NULLPTR));
        pushButton_93->setText(QApplication::translate("plusmode", "Carrier Aggregation", Q_NULLPTR));
        pushButton_99->setText(QApplication::translate("plusmode", "Conformance Test", Q_NULLPTR));
        pushButton_100->setText(QApplication::translate("plusmode", "Maintenance Test", Q_NULLPTR));
        pushButton_101->setText(QApplication::translate("plusmode", "Signal Performance", Q_NULLPTR));
        pushButton_102->setText(QApplication::translate("plusmode", "DAS Test", Q_NULLPTR));
        pushButton_103->setText(QApplication::translate("plusmode", "Power Statistics CCDF", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class plusmode: public Ui_plusmode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLUSMODE_H
