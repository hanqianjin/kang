/********************************************************************************
** Form generated from reading UI file 'smkeyboard.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMKEYBOARD_H
#define UI_SMKEYBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SmKeyBoard
{
public:
    QWidget *widget;
    QLabel *lblTitle;
    QPushButton *pb_7;
    QPushButton *pb_1;
    QPushButton *pb_8;
    QPushButton *pb_dot;
    QPushButton *pb_add;
    QPushButton *pb_3;
    QPushButton *pb_4;
    QPushButton *pb_clear;
    QPushButton *pb_enter;
    QPushButton *pb_2;
    QPushButton *pb_del;
    QPushButton *pb_6;
    QPushButton *pb_0;
    QPushButton *pb_5;
    QPushButton *pb_9;
    QPushButton *pb_cancel;

    void setupUi(QWidget *SmKeyBoard)
    {
        if (SmKeyBoard->objectName().isEmpty())
            SmKeyBoard->setObjectName(QStringLiteral("SmKeyBoard"));
        SmKeyBoard->resize(250, 440);
        SmKeyBoard->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"	font: 75 15px \"Arial\";\n"
"	font-weight:bold;\n"
"	background-color:rgba(251,219,167,0);\n"
"}\n"
"/*************************indoor*********************/\n"
"#SmKeyBoard[pltdismode=\"indoor\"] #widget\n"
"{\n"
"	background-color:rgba(255,255,255,1);\n"
"	border:1px solid gray;\n"
"}\n"
"#SmKeyBoard[pltdismode =\"indoor\"] #pb_cancel\n"
"{\n"
"	background-color:transparent;\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_close_w30_normal.png);\n"
"}\n"
"#SmKeyBoard[pltdismode =\"indoor\"] #pb_cancel:pressed\n"
"{\n"
"	background-color:transparent;\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_close_w30_click.png);\n"
"}\n"
"/*************************outdoor*********************/\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] #widget\n"
"{\n"
"	background-color:rgba(255,255,255,1);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] #pb_cancel\n"
"{\n"
"	background-color:transparent;\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_close_w30_normal.png);\n"
"}\n"
"#SmKeyBoard[pltdism"
                        "ode=\"outdoor\"] #pb_cancel:pressed\n"
"{\n"
"	background-color:transparent;\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_close_w30_click.png);\n"
"}\n"
"\n"
"/*************************night*********************/\n"
"#SmKeyBoard[pltdismode=\"night\"] #widget\n"
"{\n"
"	background-color:rgba(251,219,167,1);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"night\"] #pb_cancel\n"
"{\n"
"	background-color:transparent;\n"
"	border-image: url(:/bit/image/keyBoard/night/btn_close_normal.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"night\"] #pb_cancel:pressed\n"
"{\n"
"	background-color:transparent;\n"
"	border-image:url(:/bit/image/keyBoard/night/btn_close_click.png) ;\n"
"}\n"
"\n"
""));
        widget = new QWidget(SmKeyBoard);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 250, 440));
        widget->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	color:rgba(0,0,0,0);\n"
"}"));
        lblTitle = new QLabel(widget);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));
        lblTitle->setGeometry(QRect(10, 20, 196, 22));
        pb_7 = new QPushButton(widget);
        pb_7->setObjectName(QStringLiteral("pb_7"));
        pb_7->setGeometry(QRect(10, 233, 74, 50));
        pb_7->setFocusPolicy(Qt::NoFocus);
        pb_7->setStyleSheet(QLatin1String("/*************************indoor*********************/\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_7_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_7_w74_click.png);\n"
"}\n"
"/*************************outdoor*********************/\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_7_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_7_w74_click.png);\n"
"}\n"
"/*************************night*********************/\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/night/7.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton:pressed\n"
"{"
                        "\n"
"	border-image: url(:/bit/image/keyBoard/night/7-click.png);\n"
"}"));
        pb_1 = new QPushButton(widget);
        pb_1->setObjectName(QStringLiteral("pb_1"));
        pb_1->setGeometry(QRect(10, 125, 74, 50));
        pb_1->setFocusPolicy(Qt::NoFocus);
        pb_1->setStyleSheet(QLatin1String("/*************************indoor*********************/\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_1_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_1_w74_click.png);\n"
"}\n"
"/*************************outdoor*********************/\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_1_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_1_w74_click.png);\n"
"}\n"
"/*************************night*********************/\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/night/1.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton:pressed\n"
"{"
                        "\n"
"	border-image: url(:/bit/image/keyBoard/night/1-click.png);\n"
"}"));
        pb_8 = new QPushButton(widget);
        pb_8->setObjectName(QStringLiteral("pb_8"));
        pb_8->setGeometry(QRect(88, 233, 74, 50));
        pb_8->setFocusPolicy(Qt::NoFocus);
        pb_8->setStyleSheet(QLatin1String("/*************************indoor*********************/\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_8_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_8_w74_click.png);\n"
"}\n"
"/*************************outdoor*********************/\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_8_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_8_w74_click.png);\n"
"}\n"
"/*************************night*********************/\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/night/8.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton:pressed\n"
"{"
                        "\n"
"	border-image: url(:/bit/image/keyBoard/night/8-click.png);\n"
"}"));
        pb_dot = new QPushButton(widget);
        pb_dot->setObjectName(QStringLiteral("pb_dot"));
        pb_dot->setGeometry(QRect(10, 287, 74, 50));
        pb_dot->setFocusPolicy(Qt::NoFocus);
        pb_dot->setStyleSheet(QLatin1String("/*************************indoor*********************/\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_dot_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{\n"
"	border-image:url(:/bit/image/keyBoard/indoor/btn_dot_w74_click.png);\n"
"}\n"
"/*************************outdoor*********************/\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_dot_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image:url(:/bit/image/keyBoard/indoor/btn_dot_w74_click.png);\n"
"}\n"
"/*************************night*********************/\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/night/dot.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton:press"
                        "ed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/night/dot-click.png);\n"
"}"));
        pb_add = new QPushButton(widget);
        pb_add->setObjectName(QStringLiteral("pb_add"));
        pb_add->setGeometry(QRect(166, 287, 74, 50));
        pb_add->setFocusPolicy(Qt::NoFocus);
        pb_add->setStyleSheet(QLatin1String("/*************************indoor*********************/\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_add_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{\n"
"	border-image:url(:/bit/image/keyBoard/indoor/btn_add_w74_click.png);\n"
"}\n"
"/*************************outdoor*********************/\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_add_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image:url(:/bit/image/keyBoard/indoor/btn_add_w74_click.png);\n"
"}\n"
"/*************************night*********************/\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/night/add.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton:press"
                        "ed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/night/add-click.png);\n"
"}"));
        pb_3 = new QPushButton(widget);
        pb_3->setObjectName(QStringLiteral("pb_3"));
        pb_3->setGeometry(QRect(166, 125, 74, 50));
        pb_3->setFocusPolicy(Qt::NoFocus);
        pb_3->setStyleSheet(QLatin1String("/*************************indoor*********************/\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_3_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_3_w74_click.png);\n"
"}\n"
"/*************************outdoor*********************/\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_3_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_3_w74_click.png);\n"
"}\n"
"/*************************night*********************/\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/night/3.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton:pressed\n"
"{"
                        "\n"
"	border-image: url(:/bit/image/keyBoard/night/3-click.png);\n"
"}"));
        pb_4 = new QPushButton(widget);
        pb_4->setObjectName(QStringLiteral("pb_4"));
        pb_4->setGeometry(QRect(10, 179, 74, 50));
        pb_4->setFocusPolicy(Qt::NoFocus);
        pb_4->setStyleSheet(QLatin1String("/*************************indoor*********************/\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_4_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_4_w74_click.png);\n"
"}\n"
"/*************************outdoor*********************/\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_4_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_4_w74_click.png);\n"
"}\n"
"/*************************night*********************/\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/night/4.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton:pressed\n"
"{"
                        "\n"
"	border-image: url(:/bit/image/keyBoard/night/4-click.png);\n"
"}"));
        pb_clear = new QPushButton(widget);
        pb_clear->setObjectName(QStringLiteral("pb_clear"));
        pb_clear->setGeometry(QRect(10, 70, 74, 50));
        pb_clear->setFocusPolicy(Qt::NoFocus);
        pb_clear->setStyleSheet(QLatin1String("/*************************indoor*********************/\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image:url(:/bit/image/keyBoard/indoor/btn_clear_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_clear_w74_click.png);\n"
"}\n"
"/*************************outdoor*********************/\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image:url(:/bit/image/keyBoard/indoor/btn_clear_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_clear_w74_click.png);\n"
"}\n"
"/*************************night*********************/\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image:url(:/bit/image/keyBoard/night/Clear.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushBut"
                        "ton:pressed\n"
"{\n"
"	border-image:url(:/bit/image/keyBoard/night/Clear-click.png);\n"
"}"));
        pb_enter = new QPushButton(widget);
        pb_enter->setObjectName(QStringLiteral("pb_enter"));
        pb_enter->setGeometry(QRect(186, 367, 55, 50));
        pb_enter->setFocusPolicy(Qt::NoFocus);
        pb_enter->setStyleSheet(QLatin1String("/*************************indoor*********************/\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"f	ont-weight:bold;\n"
"	font-family:\"Arial\";\n"
"	color:white;\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_w55_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{\n"
"	border-image:url(:/bit/image/keyBoard/indoor/btn_w55_click.png);\n"
"}\n"
"/*************************outdoor*********************/\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	font-weight:bold;\n"
"	font-family:\"Arial\";\n"
"	color:white;\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_w55_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image:url(:/bit/image/keyBoard/indoor/btn_w55_click.png);\n"
"}\n"
"/*************************night*********************/\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	font-weight:bold;\n"
"	font-fam"
                        "ily:\"Arial\";\n"
"	color:rgba(252, 220, 168, 1);\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image:url(:/bit/image/keyBoard/night/btn_w70_normal.png) ;\n"
"}\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/night/btn_w70_click.png);\n"
"}"));
        pb_2 = new QPushButton(widget);
        pb_2->setObjectName(QStringLiteral("pb_2"));
        pb_2->setGeometry(QRect(88, 125, 74, 50));
        pb_2->setFocusPolicy(Qt::NoFocus);
        pb_2->setStyleSheet(QLatin1String("/*************************indoor*********************/\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_2_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_2_w74_click.png);\n"
"}\n"
"/*************************outdoor*********************/\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_2_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_2_w74_click.png);\n"
"}\n"
"/*************************night*********************/\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/night/2.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton:pressed\n"
"{"
                        "\n"
"	border-image: url(:/bit/image/keyBoard/night/2-click.png);\n"
"}"));
        pb_del = new QPushButton(widget);
        pb_del->setObjectName(QStringLiteral("pb_del"));
        pb_del->setGeometry(QRect(166, 70, 74, 50));
        pb_del->setFocusPolicy(Qt::NoFocus);
        pb_del->setStyleSheet(QLatin1String("/*************************indoor*********************/\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_del_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_del_w74_click.png);\n"
"}\n"
"/*************************outdoor*********************/\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_del_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_del_w74_click.png);\n"
"}\n"
"/*************************night*********************/\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image:url(:/bit/image/keyBoard/night/delete.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton:p"
                        "ressed\n"
"{\n"
"	border-image:url(:/bit/image/keyBoard/night/delete-click.png);\n"
"}"));
        pb_6 = new QPushButton(widget);
        pb_6->setObjectName(QStringLiteral("pb_6"));
        pb_6->setGeometry(QRect(166, 179, 74, 50));
        pb_6->setFocusPolicy(Qt::NoFocus);
        pb_6->setStyleSheet(QLatin1String("/*************************indoor*********************/\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_6_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_6_w74_click.png);\n"
"}\n"
"/*************************outdoor*********************/\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_6_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_6_w74_click.png);\n"
"}\n"
"/*************************night*********************/\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/night/6.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton:pressed\n"
"{"
                        "\n"
"	border-image: url(:/bit/image/keyBoard/night/6-click.png);\n"
"}"));
        pb_0 = new QPushButton(widget);
        pb_0->setObjectName(QStringLiteral("pb_0"));
        pb_0->setGeometry(QRect(88, 287, 74, 50));
        pb_0->setFocusPolicy(Qt::NoFocus);
        pb_0->setStyleSheet(QLatin1String("/*************************indoor*********************/\n"
"#SmKeyBoard[pltdismode = \"indoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_0_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_0_w74_click.png);\n"
"}\n"
"/*************************outdoor*********************/\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_0_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_0_w74_click.png);\n"
"}\n"
"/*************************night*********************/\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/night/0.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton:pressed\n"
""
                        "{\n"
"	border-image: url(:/bit/image/keyBoard/night/0-click.png);\n"
"}"));
        pb_5 = new QPushButton(widget);
        pb_5->setObjectName(QStringLiteral("pb_5"));
        pb_5->setGeometry(QRect(88, 179, 74, 50));
        pb_5->setFocusPolicy(Qt::NoFocus);
        pb_5->setStyleSheet(QLatin1String("/*************************indoor*********************/\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_5_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_5_w74_click.png);\n"
"}\n"
"/*************************outdoor*********************/\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_5_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_5_w74_click.png);\n"
"}\n"
"/*************************night*********************/\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/night/5.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton:pressed\n"
"{"
                        "\n"
"	border-image: url(:/bit/image/keyBoard/night/5-click.png);\n"
"}"));
        pb_9 = new QPushButton(widget);
        pb_9->setObjectName(QStringLiteral("pb_9"));
        pb_9->setGeometry(QRect(166, 233, 74, 50));
        pb_9->setFocusPolicy(Qt::NoFocus);
        pb_9->setStyleSheet(QLatin1String("/*************************indoor*********************/\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_9_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_9_w74_click.png);\n"
"}\n"
"/*************************outdoor*********************/\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_9_w74_nor.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/bit/image/keyBoard/indoor/btn_9_w74_click.png);\n"
"}\n"
"/*************************night*********************/\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/bit/image/keyBoard/night/9.png);\n"
"}\n"
"#SmKeyBoard[pltdismode=\"night\"] QPushButton:pressed\n"
"{"
                        "\n"
"	border-image: url(:/bit/image/keyBoard/night/9-click.png);\n"
"}"));
        pb_cancel = new QPushButton(widget);
        pb_cancel->setObjectName(QStringLiteral("pb_cancel"));
        pb_cancel->setGeometry(QRect(211, 15, 30, 30));
        pb_cancel->setFocusPolicy(Qt::NoFocus);

        retranslateUi(SmKeyBoard);

        QMetaObject::connectSlotsByName(SmKeyBoard);
    } // setupUi

    void retranslateUi(QWidget *SmKeyBoard)
    {
        SmKeyBoard->setWindowTitle(QApplication::translate("SmKeyBoard", "Form", 0));
        SmKeyBoard->setProperty("pltdismode", QVariant(QApplication::translate("SmKeyBoard", "indoor", 0)));
        lblTitle->setText(QApplication::translate("SmKeyBoard", "IP Address", 0));
        pb_7->setText(QApplication::translate("SmKeyBoard", "7", 0));
        pb_1->setText(QApplication::translate("SmKeyBoard", "1", 0));
        pb_8->setText(QApplication::translate("SmKeyBoard", "8", 0));
        pb_dot->setText(QApplication::translate("SmKeyBoard", ".", 0));
        pb_add->setText(QString());
        pb_3->setText(QApplication::translate("SmKeyBoard", "3", 0));
        pb_4->setText(QApplication::translate("SmKeyBoard", "4", 0));
        pb_clear->setText(QString());
        pb_enter->setText(QApplication::translate("SmKeyBoard", "Enter", 0));
        pb_2->setText(QApplication::translate("SmKeyBoard", "2", 0));
        pb_del->setText(QString());
        pb_6->setText(QApplication::translate("SmKeyBoard", "6", 0));
        pb_0->setText(QApplication::translate("SmKeyBoard", "0", 0));
        pb_5->setText(QApplication::translate("SmKeyBoard", "5", 0));
        pb_9->setText(QApplication::translate("SmKeyBoard", "9", 0));
        pb_cancel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SmKeyBoard: public Ui_SmKeyBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMKEYBOARD_H
