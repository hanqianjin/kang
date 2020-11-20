/********************************************************************************
** Form generated from reading UI file 'sa_dialog_digitinput.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_DIGITINPUT_H
#define UI_SA_DIALOG_DIGITINPUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SA_Dialog_DigitInput
{
public:
    QLabel *lblTitle;
    QPushButton *pb_cancel;
    QLabel *lblValue;
    QPushButton *pb_9;
    QPushButton *pb_8;
    QPushButton *pb_7;
    QPushButton *pb_0;
    QPushButton *pb_1;
    QPushButton *pb_2;
    QPushButton *pb_3;
    QPushButton *pb_4;
    QPushButton *pb_5;
    QPushButton *pb_6;
    QPushButton *pb_dot;
    QPushButton *pb_across;
    QPushButton *btnBackSpace;
    QPushButton *pb_clearAll;
    QWidget *FREQuNIT;
    QPushButton *freqBtnUnit4;
    QPushButton *freqBtnUnit1;
    QPushButton *freqBtnUnit3;
    QPushButton *freqBtnUnit2;
    QPushButton *pb_Up;
    QPushButton *pb_Left;
    QPushButton *pb_Down;
    QPushButton *pb_Right;
    QWidget *AmptUnit;
    QPushButton *amptBtnUnit1;
    QPushButton *amptBtnUnit2;
    QPushButton *amptBtnUnit3;
    QPushButton *amptBtnUnit4;
    QPushButton *amptBtnUnit5;
    QPushButton *amptBtnUnit6;
    QPushButton *amptBtnUnit7;

    void setupUi(QWidget *SA_Dialog_DigitInput)
    {
        if (SA_Dialog_DigitInput->objectName().isEmpty())
            SA_Dialog_DigitInput->setObjectName(QStringLiteral("SA_Dialog_DigitInput"));
        SA_Dialog_DigitInput->resize(252, 646);
        SA_Dialog_DigitInput->setFocusPolicy(Qt::StrongFocus);
        SA_Dialog_DigitInput->setStyleSheet(QLatin1String("\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] \n"
"{\n"
"		background-color:white;\n"
"		border:1px solid rgba(161,161,161,1);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] #lblTitle\n"
"{	\n"
"	font: 75 15px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] QWidget\n"
"{\n"
"	background-color:white;\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] #pb_cancel\n"
"{\n"
"	background-color:transparent;\n"
"	border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] #pb_cancel:pressed\n"
"{\n"
"	background-color:transparent;\n"
"	border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"]\n"
"{    \n"
"		background-color:rgb(255, 255, 255);\n"
"		border:1px solid rgba(161,161,161,1);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] #lblTitle\n"
"{	\n"
"	backgro"
                        "und-color:rgba(0,0,0,0);\n"
"	font: 75 15px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QWidget{\n"
"	background-color:rgb(255, 255, 255);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] #pb_cancel\n"
"{\n"
"	background-color:transparent;\n"
"	border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] #pb_cancel:pressed\n"
"{\n"
"	background-color:transparent;\n"
"	border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"/*******************night**********************/\n"
"#SA_Dialog_DigitInput[status =\"night\"]\n"
"{\n"
"		background-color:rgba(251,219,167,1);\n"
"		border:1px solid rgba(161,161,161,1);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] #lblTitle\n"
"{	\n"
"	background-color:rgba(251,219,167,1);\n"
"	color:rgba(46,46,46,1);\n"
"	font: 75 15px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] QWidget{\n"
"	background-color:rgba(251,219,167,1);\n"
"}\n"
"\n"
""
                        "#SA_Dialog_DigitInput[status =\"night\"] #pb_cancel\n"
"{\n"
"	background-color:transparent;\n"
"	border-image: url(:/sa/image/night/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] #pb_cancel:pressed\n"
"{\n"
"	background-color:transparent;\n"
"	border-image: url(:/sa/image/night/btn_close_click.png);\n"
"}\n"
"\n"
""));
        lblTitle = new QLabel(SA_Dialog_DigitInput);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));
        lblTitle->setGeometry(QRect(17, 19, 191, 22));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        lblTitle->setFont(font);
        pb_cancel = new QPushButton(SA_Dialog_DigitInput);
        pb_cancel->setObjectName(QStringLiteral("pb_cancel"));
        pb_cancel->setGeometry(QRect(212, 6, 35, 35));
        pb_cancel->setFocusPolicy(Qt::NoFocus);
        pb_cancel->setFlat(true);
        lblValue = new QLabel(SA_Dialog_DigitInput);
        lblValue->setObjectName(QStringLiteral("lblValue"));
        lblValue->setGeometry(QRect(10, 70, 233, 62));
        lblValue->setFont(font);
        lblValue->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] QLabel\n"
"{\n"
"	font:75 26px \"Arial\";\n"
"	font-weight:bold;\n"
"	padding-left:4px;\n"
"	background-color:rgb(0,0,0);\n"
"	color: rgb(238, 183, 37);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QLabel\n"
"{\n"
"	font:75 26px \"Arial\";\n"
"	font-weight:bold;\n"
"	padding-left:4px;\n"
"	background-color:rgba(225,225,225,1);\n"
"	color:rgba(162,115,0,1);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_DigitInput[status =\"night\"] QLabel\n"
"{\n"
"	font:75 26px \"Arial\";\n"
"	font-weight:bold;\n"
"	padding-left:4px;\n"
"	background-color:rgb(0,0,0);\n"
"	color: rgb(238, 183, 37);\n"
"}"));
        pb_9 = new QPushButton(SA_Dialog_DigitInput);
        pb_9->setObjectName(QStringLiteral("pb_9"));
        pb_9->setGeometry(QRect(167, 442, 74, 50));
        pb_9->setFont(font);
        pb_9->setFocusPolicy(Qt::NoFocus);
        pb_9->setStyleSheet(QLatin1String("#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_9_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_9_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_9_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_9_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/night/9.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/9-click.png);\n"
"}"));
        pb_8 = new QPushButton(SA_Dialog_DigitInput);
        pb_8->setObjectName(QStringLiteral("pb_8"));
        pb_8->setGeometry(QRect(89, 442, 74, 50));
        pb_8->setFont(font);
        pb_8->setFocusPolicy(Qt::NoFocus);
        pb_8->setStyleSheet(QLatin1String("#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_8_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_8_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_8_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_8_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/night/8.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/8-click.png);\n"
"}"));
        pb_7 = new QPushButton(SA_Dialog_DigitInput);
        pb_7->setObjectName(QStringLiteral("pb_7"));
        pb_7->setGeometry(QRect(11, 442, 74, 50));
        pb_7->setFont(font);
        pb_7->setFocusPolicy(Qt::NoFocus);
        pb_7->setStyleSheet(QLatin1String("#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_7_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_7_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_7_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_7_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/night/7.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/7-click.png);\n"
"}"));
        pb_0 = new QPushButton(SA_Dialog_DigitInput);
        pb_0->setObjectName(QStringLiteral("pb_0"));
        pb_0->setGeometry(QRect(89, 496, 74, 50));
        pb_0->setFont(font);
        pb_0->setFocusPolicy(Qt::NoFocus);
        pb_0->setStyleSheet(QLatin1String("#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_0_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_0_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_0_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_0_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/night/0.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/0-click.png);\n"
"}"));
        pb_1 = new QPushButton(SA_Dialog_DigitInput);
        pb_1->setObjectName(QStringLiteral("pb_1"));
        pb_1->setGeometry(QRect(11, 334, 74, 50));
        pb_1->setFont(font);
        pb_1->setFocusPolicy(Qt::NoFocus);
        pb_1->setStyleSheet(QLatin1String("#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_1_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_1_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_1_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_1_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/night/1.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/1-click.png);\n"
"}"));
        pb_2 = new QPushButton(SA_Dialog_DigitInput);
        pb_2->setObjectName(QStringLiteral("pb_2"));
        pb_2->setGeometry(QRect(89, 334, 74, 50));
        pb_2->setFont(font);
        pb_2->setFocusPolicy(Qt::NoFocus);
        pb_2->setStyleSheet(QLatin1String("#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_2_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_2_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_2_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_2_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/night/2.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/2-click.png);\n"
"}"));
        pb_3 = new QPushButton(SA_Dialog_DigitInput);
        pb_3->setObjectName(QStringLiteral("pb_3"));
        pb_3->setGeometry(QRect(167, 334, 74, 50));
        pb_3->setFont(font);
        pb_3->setFocusPolicy(Qt::NoFocus);
        pb_3->setStyleSheet(QLatin1String("#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_3_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_3_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_3_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_3_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/night/3.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/3-click.png);\n"
"}"));
        pb_4 = new QPushButton(SA_Dialog_DigitInput);
        pb_4->setObjectName(QStringLiteral("pb_4"));
        pb_4->setGeometry(QRect(11, 388, 74, 50));
        pb_4->setFont(font);
        pb_4->setFocusPolicy(Qt::NoFocus);
        pb_4->setStyleSheet(QLatin1String("#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_4_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_4_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_4_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_4_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/night/4.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/4-click.png);\n"
"}"));
        pb_5 = new QPushButton(SA_Dialog_DigitInput);
        pb_5->setObjectName(QStringLiteral("pb_5"));
        pb_5->setGeometry(QRect(89, 388, 74, 50));
        pb_5->setFont(font);
        pb_5->setFocusPolicy(Qt::NoFocus);
        pb_5->setStyleSheet(QLatin1String("#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_5_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_5_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_5_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_5_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/night/5.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/5-click.png);\n"
"}"));
        pb_6 = new QPushButton(SA_Dialog_DigitInput);
        pb_6->setObjectName(QStringLiteral("pb_6"));
        pb_6->setGeometry(QRect(167, 388, 74, 50));
        pb_6->setFont(font);
        pb_6->setFocusPolicy(Qt::NoFocus);
        pb_6->setStyleSheet(QLatin1String("#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_6_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_6_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_6_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_6_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/night/6.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/6-click.png);\n"
"}"));
        pb_dot = new QPushButton(SA_Dialog_DigitInput);
        pb_dot->setObjectName(QStringLiteral("pb_dot"));
        pb_dot->setGeometry(QRect(11, 496, 74, 50));
        pb_dot->setFont(font);
        pb_dot->setFocusPolicy(Qt::NoFocus);
        pb_dot->setStyleSheet(QLatin1String("#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_dot_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_dot_w74_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_dot_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_dot_w74_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/night/dot.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/dot-click.png);\n"
"}"));
        pb_across = new QPushButton(SA_Dialog_DigitInput);
        pb_across->setObjectName(QStringLiteral("pb_across"));
        pb_across->setGeometry(QRect(167, 496, 74, 50));
        pb_across->setFont(font);
        pb_across->setFocusPolicy(Qt::NoFocus);
        pb_across->setStyleSheet(QLatin1String("#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_add_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_add_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_add_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_add_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/night/add.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/add-click.png);\n"
"}\n"
""));
        btnBackSpace = new QPushButton(SA_Dialog_DigitInput);
        btnBackSpace->setObjectName(QStringLiteral("btnBackSpace"));
        btnBackSpace->setGeometry(QRect(167, 279, 74, 50));
        btnBackSpace->setFont(font);
        btnBackSpace->setFocusPolicy(Qt::NoFocus);
        btnBackSpace->setStyleSheet(QLatin1String("#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_del_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_del_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_del_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_del_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/night/delete.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/delete-click.png);\n"
"}\n"
""));
        pb_clearAll = new QPushButton(SA_Dialog_DigitInput);
        pb_clearAll->setObjectName(QStringLiteral("pb_clearAll"));
        pb_clearAll->setGeometry(QRect(11, 279, 74, 50));
        pb_clearAll->setFont(font);
        pb_clearAll->setFocusPolicy(Qt::NoFocus);
        pb_clearAll->setStyleSheet(QLatin1String("#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_clear_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_clear_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_clear_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_clear_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/night/Clear.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/Clear-click.png);\n"
"}\n"
""));
        FREQuNIT = new QWidget(SA_Dialog_DigitInput);
        FREQuNIT->setObjectName(QStringLiteral("FREQuNIT"));
        FREQuNIT->setGeometry(QRect(5, 562, 245, 71));
        FREQuNIT->setStyleSheet(QLatin1String("/********************indoor************************/\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] \n"
"#FREQuNIT>QPushButton\n"
"{\n"
"	color:white;\n"
"	\n"
"   border-style:flat;\n"
"	border-image: url(:/sa/image/keyPad/btn_w55_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] \n"
"#FREQuNIT>QPushButton::pressed\n"
"{\n"
"	border-image: url(:/sa/image/keyPad/btn_w55_click.png);\n"
"}\n"
"\n"
"/********************outdoor************************/\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] \n"
"#FREQuNIT>QPushButton\n"
"{\n"
"	color:rgb(0,0,0);\n"
"   border-style:flat;\n"
"	border-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] \n"
"#FREQuNIT>QPushButton::pressed\n"
"{\n"
"	color:rgb(255,255,255);\n"
"	border-image: url(:/sa/image/keyPad/btn_w55_click.png);\n"
"}\n"
"\n"
"/********************night************************/\n"
"#SA_Dialog_DigitInput[status =\"night\"] \n"
"#FREQuNIT>QPushButton\n"
"{\n"
"	color:rgba(252,220,168,1);\n"
"  "
                        " border-style:flat;\n"
"	border-image: url(:/sa/image/keyPad/btn_w55_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] \n"
"#FREQuNIT>QPushButton::pressed\n"
"{\n"
"	border-image: url(:/sa/image/keyPad/btn_w55_click.png);\n"
"}"));
        freqBtnUnit4 = new QPushButton(FREQuNIT);
        freqBtnUnit4->setObjectName(QStringLiteral("freqBtnUnit4"));
        freqBtnUnit4->setGeometry(QRect(183, 5, 55, 50));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        freqBtnUnit4->setFont(font1);
        freqBtnUnit4->setFocusPolicy(Qt::NoFocus);
        freqBtnUnit4->setStyleSheet(QStringLiteral(""));
        freqBtnUnit1 = new QPushButton(FREQuNIT);
        freqBtnUnit1->setObjectName(QStringLiteral("freqBtnUnit1"));
        freqBtnUnit1->setGeometry(QRect(6, 5, 55, 50));
        freqBtnUnit1->setFont(font1);
        freqBtnUnit1->setFocusPolicy(Qt::NoFocus);
        freqBtnUnit1->setStyleSheet(QStringLiteral(""));
        freqBtnUnit3 = new QPushButton(FREQuNIT);
        freqBtnUnit3->setObjectName(QStringLiteral("freqBtnUnit3"));
        freqBtnUnit3->setGeometry(QRect(124, 5, 55, 50));
        freqBtnUnit3->setFont(font1);
        freqBtnUnit3->setFocusPolicy(Qt::NoFocus);
        freqBtnUnit3->setStyleSheet(QStringLiteral(""));
        freqBtnUnit2 = new QPushButton(FREQuNIT);
        freqBtnUnit2->setObjectName(QStringLiteral("freqBtnUnit2"));
        freqBtnUnit2->setGeometry(QRect(65, 5, 55, 50));
        freqBtnUnit2->setFont(font1);
        freqBtnUnit2->setFocusPolicy(Qt::NoFocus);
        freqBtnUnit2->setStyleSheet(QStringLiteral(""));
        pb_Up = new QPushButton(SA_Dialog_DigitInput);
        pb_Up->setObjectName(QStringLiteral("pb_Up"));
        pb_Up->setGeometry(QRect(89, 150, 74, 50));
        pb_Up->setFocusPolicy(Qt::NoFocus);
        pb_Up->setStyleSheet(QLatin1String("#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_up_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_up_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_up_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_up_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/night/up.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/up-click.png);\n"
"}"));
        pb_Left = new QPushButton(SA_Dialog_DigitInput);
        pb_Left->setObjectName(QStringLiteral("pb_Left"));
        pb_Left->setGeometry(QRect(11, 204, 74, 50));
        pb_Left->setFocusPolicy(Qt::NoFocus);
        pb_Left->setStyleSheet(QLatin1String("#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_left_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_left_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_left_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_left_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/night/left.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/left-click.png);\n"
"}\n"
""));
        pb_Down = new QPushButton(SA_Dialog_DigitInput);
        pb_Down->setObjectName(QStringLiteral("pb_Down"));
        pb_Down->setGeometry(QRect(89, 204, 74, 50));
        pb_Down->setFocusPolicy(Qt::NoFocus);
        pb_Down->setStyleSheet(QLatin1String("#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_down_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_down_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_down_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_down_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/night/down.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/down-click.png);\n"
"}\n"
""));
        pb_Right = new QPushButton(SA_Dialog_DigitInput);
        pb_Right->setObjectName(QStringLiteral("pb_Right"));
        pb_Right->setGeometry(QRect(167, 204, 74, 50));
        pb_Right->setFocusPolicy(Qt::NoFocus);
        pb_Right->setStyleSheet(QLatin1String("#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_right_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_right_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/keyPad/btn_right_w74_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/keyPad/btn_right_w74_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton\n"
"{\n"
"   border-style:flat;\n"
"	background-image: url(:/sa/image/night/right.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/right-click.png);\n"
"}\n"
""));
        AmptUnit = new QWidget(SA_Dialog_DigitInput);
        AmptUnit->setObjectName(QStringLiteral("AmptUnit"));
        AmptUnit->setGeometry(QRect(2, 550, 248, 93));
        AmptUnit->setStyleSheet(QLatin1String("/********************indoor************************/\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] \n"
"#AmptUnit>QPushButton\n"
"{\n"
"	color:white;\n"
"	\n"
"   border-style:flat;\n"
"	border-image: url(:/sa/image/keyPad/btn_w55_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"indoor\"] \n"
"#AmptUnit>QPushButton::pressed\n"
"{\n"
"	border-image: url(:/sa/image/keyPad/btn_w55_click.png);\n"
"}\n"
"\n"
"/********************outdoor************************/\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] \n"
"#AmptUnit>QPushButton\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	\n"
"   border-style:flat;\n"
"   border-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"outdoor\"] \n"
"#AmptUnit>QPushButton::pressed\n"
"{\n"
"	color:rgb(255,255,255);\n"
"	border-image: url(:/sa/image/keyPad/btn_w55_click.png);\n"
"}\n"
"\n"
"/********************night************************/\n"
"#SA_Dialog_DigitInput[status =\"night\"] \n"
"#AmptUnit>QPushButton\n"
"{\n"
"	color:rgba(252,220,168,1)"
                        ";\n"
"   border-style:flat;\n"
"	border-image: url(:/sa/image/keyPad/btn_w55_nor.png);\n"
"}\n"
"#SA_Dialog_DigitInput[status =\"night\"] \n"
"#AmptUnit>QPushButton::pressed\n"
"{\n"
"	border-image: url(:/sa/image/keyPad/btn_w55_click.png);\n"
"}"));
        amptBtnUnit1 = new QPushButton(AmptUnit);
        amptBtnUnit1->setObjectName(QStringLiteral("amptBtnUnit1"));
        amptBtnUnit1->setGeometry(QRect(8, 5, 55, 40));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setBold(true);
        font2.setWeight(75);
        amptBtnUnit1->setFont(font2);
        amptBtnUnit1->setFocusPolicy(Qt::NoFocus);
        amptBtnUnit1->setStyleSheet(QStringLiteral("font-weight:bold;"));
        amptBtnUnit2 = new QPushButton(AmptUnit);
        amptBtnUnit2->setObjectName(QStringLiteral("amptBtnUnit2"));
        amptBtnUnit2->setGeometry(QRect(70, 5, 55, 40));
        amptBtnUnit2->setFont(font2);
        amptBtnUnit2->setFocusPolicy(Qt::NoFocus);
        amptBtnUnit2->setStyleSheet(QStringLiteral("font-weight:bold;"));
        amptBtnUnit3 = new QPushButton(AmptUnit);
        amptBtnUnit3->setObjectName(QStringLiteral("amptBtnUnit3"));
        amptBtnUnit3->setGeometry(QRect(130, 5, 55, 40));
        amptBtnUnit3->setFont(font2);
        amptBtnUnit3->setFocusPolicy(Qt::NoFocus);
        amptBtnUnit3->setStyleSheet(QStringLiteral("font-weight:bold;"));
        amptBtnUnit4 = new QPushButton(AmptUnit);
        amptBtnUnit4->setObjectName(QStringLiteral("amptBtnUnit4"));
        amptBtnUnit4->setGeometry(QRect(190, 5, 55, 40));
        amptBtnUnit4->setFont(font2);
        amptBtnUnit4->setFocusPolicy(Qt::NoFocus);
        amptBtnUnit4->setStyleSheet(QStringLiteral("font-weight:bold;"));
        amptBtnUnit5 = new QPushButton(AmptUnit);
        amptBtnUnit5->setObjectName(QStringLiteral("amptBtnUnit5"));
        amptBtnUnit5->setGeometry(QRect(8, 50, 55, 40));
        amptBtnUnit5->setFont(font2);
        amptBtnUnit5->setFocusPolicy(Qt::NoFocus);
        amptBtnUnit5->setStyleSheet(QStringLiteral("font-weight:bold;"));
        amptBtnUnit6 = new QPushButton(AmptUnit);
        amptBtnUnit6->setObjectName(QStringLiteral("amptBtnUnit6"));
        amptBtnUnit6->setGeometry(QRect(68, 50, 55, 40));
        amptBtnUnit6->setFont(font2);
        amptBtnUnit6->setFocusPolicy(Qt::NoFocus);
        amptBtnUnit6->setStyleSheet(QStringLiteral("font-weight:bold;"));
        amptBtnUnit7 = new QPushButton(AmptUnit);
        amptBtnUnit7->setObjectName(QStringLiteral("amptBtnUnit7"));
        amptBtnUnit7->setGeometry(QRect(128, 50, 55, 40));
        amptBtnUnit7->setFont(font2);
        amptBtnUnit7->setFocusPolicy(Qt::NoFocus);
        amptBtnUnit7->setStyleSheet(QStringLiteral("font-weight:bold;"));

        retranslateUi(SA_Dialog_DigitInput);

        QMetaObject::connectSlotsByName(SA_Dialog_DigitInput);
    } // setupUi

    void retranslateUi(QWidget *SA_Dialog_DigitInput)
    {
        SA_Dialog_DigitInput->setWindowTitle(QApplication::translate("SA_Dialog_DigitInput", "Form", 0));
        SA_Dialog_DigitInput->setProperty("status", QVariant(QApplication::translate("SA_Dialog_DigitInput", "indoor", 0)));
        lblTitle->setText(QApplication::translate("SA_Dialog_DigitInput", "Frequency", 0));
        pb_cancel->setText(QString());
        lblValue->setText(QApplication::translate("SA_Dialog_DigitInput", "1000000.0 GHz", 0));
        pb_9->setText(QString());
        pb_8->setText(QString());
        pb_7->setText(QString());
        pb_0->setText(QString());
        pb_1->setText(QString());
        pb_2->setText(QString());
        pb_3->setText(QString());
        pb_4->setText(QString());
        pb_5->setText(QString());
        pb_6->setText(QString());
        pb_dot->setText(QString());
        pb_across->setText(QString());
        btnBackSpace->setText(QString());
        pb_clearAll->setText(QString());
        freqBtnUnit4->setText(QString());
        freqBtnUnit1->setText(QString());
        freqBtnUnit3->setText(QString());
        freqBtnUnit2->setText(QString());
        pb_Up->setText(QString());
        pb_Left->setText(QString());
        pb_Down->setText(QString());
        pb_Right->setText(QString());
        amptBtnUnit1->setText(QApplication::translate("SA_Dialog_DigitInput", "W", 0));
        amptBtnUnit2->setText(QApplication::translate("SA_Dialog_DigitInput", "mW", 0));
        amptBtnUnit3->setText(QApplication::translate("SA_Dialog_DigitInput", "uW", 0));
        amptBtnUnit4->setText(QApplication::translate("SA_Dialog_DigitInput", "nW", 0));
        amptBtnUnit5->setText(QApplication::translate("SA_Dialog_DigitInput", "pW", 0));
        amptBtnUnit6->setText(QApplication::translate("SA_Dialog_DigitInput", "fW", 0));
        amptBtnUnit7->setText(QApplication::translate("SA_Dialog_DigitInput", "aW", 0));
    } // retranslateUi

};

namespace Ui {
    class SA_Dialog_DigitInput: public Ui_SA_Dialog_DigitInput {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_DIGITINPUT_H
