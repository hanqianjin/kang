/********************************************************************************
** Form generated from reading UI file 'sa_dialog_limit.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_LIMIT_H
#define UI_SA_DIALOG_LIMIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <sa_lineedit.h>

QT_BEGIN_NAMESPACE

class Ui_SA_Dialog_Limit
{
public:
    QWidget *widget;
    QLabel *lblTitle;
    QFrame *line;
    QPushButton *pb_cancel;
    QLabel *lblLimitLine;
    QPushButton *pb_toggle;
    QPushButton *pb_EditMask;
    QPushButton *pb_LM1;
    QPushButton *pb_LM2;
    QPushButton *pb_LM3;
    QPushButton *pb_LM4;
    QPushButton *pb_LM5;
    QPushButton *pb_LM6;
    QPushButton *pb_Edge;
    QLabel *lblLimitEdge;
    SA_LineEdit *lineEdit;
    QPushButton *pb_LimitTest;
    QLabel *lblLimitTest;
    QPushButton *pb_Upper;
    QPushButton *pb_Lower;
    QLabel *lblLimitType;
    QPushButton *pb_DeleteAll;
    QLabel *lblEditLimitEdge;
    QLabel *lblLimit;
    QLabel *labelWarning;
    QLabel *lblUpperLimit;
    QLabel *lblLowerLimit;
    QPushButton *pb_UpperLimit;
    QPushButton *pb_LowerLimit;
    SA_LineEdit *UpperLimitEdit;
    SA_LineEdit *LowerLimitEdit;
    SA_LineEdit *ATLdbcLimitEdit;
    QPushButton *pb_ATLdbcLimit;
    QLabel *lblLATLdbcLimit;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *SA_Dialog_Limit)
    {
        if (SA_Dialog_Limit->objectName().isEmpty())
            SA_Dialog_Limit->setObjectName(QStringLiteral("SA_Dialog_Limit"));
        SA_Dialog_Limit->resize(507, 646);
        SA_Dialog_Limit->setStyleSheet(QLatin1String("#widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#widget>#lblTitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}\n"
"#pb_cancel\n"
"{\n"
"border-style:flat;\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"#line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"QPushButton\n"
"{\n"
"	background-color:black;\n"
"	color:rgb(130, 130, 130);\n"
"	border-style:flat;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#pb_LimitTest,\n"
"#pb_Edge,\n"
"#pb_toggle,\n"
"#pb_UpperLimit,\n"
"#pb_LowerLimit,\n"
"#pb_ATLdbcLimit\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#pb_LimitTest:checked,\n"
"#pb_Edge::checked,\n"
"#pb_toggle:checked,\n"
"#pb_UpperLimit:checked,\n"
"#pb_LowerLimit:checked,\n"
"#pb_ATLdbcLimit:c"
                        "hecked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"#pb_LimitTest:!checked,\n"
"#pb_Edge:!checked,\n"
"#pb_toggle:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"#pb_Upper:checked\n"
"{\n"
"	background-color:transparent;\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"#pb_Upper:!checked\n"
"{\n"
"background-color:transparent;\n"
"padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"#pb_Lower:checked\n"
"{\n"
"background-color:transparent;\n"
"padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#pb_Lower:!checked\n"
"{\n"
"background-color:transparent;\n"
"padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
""
                        "	background-position:right;\n"
"}\n"
"\n"
"#widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#widget>QLabel\n"
"{\n"
"font: 75 13px \"Arial\";\n"
"color:rgb(46,46,46);\n"
"}\n"
"SA_LineEdit\n"
"{\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"#pb_LM1,\n"
"#pb_LM2,\n"
"#pb_LM3,\n"
"#pb_LM4,\n"
"#pb_LM5,\n"
"#pb_LM6\n"
"{\n"
"text-align:left;\n"
"padding-left:10px;\n"
"}\n"
"#pb_LM1:checked,\n"
"#pb_LM2:checked,\n"
"#pb_LM3:checked,\n"
"#pb_LM4:checked,\n"
"#pb_LM5:checked,\n"
"#pb_LM6:checked\n"
"{\n"
"	color:rgba(87, 87, 87, 1);\n"
"}\n"
"\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_Limit[status= \"indoor\"] #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #widget>#lblTitle\n"
"{\n"
"	color:rgba(46,46,46,1"
                        ");\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_cancel\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_cancel:pressed\n"
"{\n"
"	border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	background-color:black;\n"
"	color:rgb(130, 130, 130);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_LimitTest,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_Edge,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_toggle,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_UpperLimit,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_LowerLimit,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_ATLdbcLimit\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_LimitTest:checked,\n"
"#SA_Dialog_Limit[status  "
                        "=  \"indoor\"] #pb_Edge::checked,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_toggle:checked,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_LowerLimit:checked,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_UpperLimit:checked,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_ATLdbcLimit:checked\n"
"{\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_LimitTest:!checked,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_Edge:!checked,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_toggle:!checked,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_LowerLimit:!checked,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_UpperLimit:!checked,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_ATLdbcLimit:!checked\n"
"{\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_Upper:checked\n"
"{\n"
"	background-color:transparent;\n"
"	background-imag"
                        "e: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_Upper:!checked\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_Lower:checked\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_Lower:!checked\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #widget>QLabel\n"
"{\n"
"	color:rgb(46,46,46);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] SA_LineEdit\n"
"{\n"
"	background-color:rgba(255,255,255,0.6);\n"
"	color:rgba(162, 115, 0,1);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] SA_LineEdit:focus\n"
"{\n"
"	border:2px solid rgba(162,115,0,1);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_LM1,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] "
                        "#pb_LM2,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_LM3,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_LM4,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_LM5,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_LM6\n"
"{\n"
"	background-image: url(:/sa/image/btn_mkr_nor.png);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_LM1:checked,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_LM2:checked,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_LM3:checked,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_LM4:checked,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_LM5:checked,\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] #pb_LM6:checked\n"
"{\n"
"	background-image: url(:/sa/image/btn_mkr_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_Limit[status  =\"outdoor\"] #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#SA_Dialog_Limit[status  =\"outdoor\"] #widget>#lblTitle\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_Limit[status  = \""
                        "outdoor\"] #pb_cancel\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_cancel:pressed\n"
"{\n"
"	border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	background-color:black;\n"
"	color:rgb(130, 130, 130);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_LimitTest,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_Edge,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_toggle,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_LowerLimit,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_UpperLimit,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_ATLdbcLimit\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_LimitTest:checked,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_Edge::checke"
                        "d,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_toggle:checked,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_LowerLimit:checked,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_UpperLimit:checked,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_ATLdbcLimit:checked\n"
"{\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_LimitTest:!checked,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_Edge:!checked,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_toggle:!checked,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_LowerLimit:!checked,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_UpperLimit:!checked,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_ATLdbcLimit:!checked\n"
"{\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_Upper:checked\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fr"
                        "e_checked_left.png);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_Upper:!checked\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_Lower:checked\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_Lower:!checked\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #widget>QLabel\n"
"{\n"
"	color:rgb(46,46,46);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] SA_LineEdit\n"
"{\n"
"	background-color:rgba(255,255,255,0.6);\n"
"	color:rgba(162, 115, 0,1);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] SA_LineEdit:focus\n"
"{\n"
"	border:2px solid rgba(162,115,0,1);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_LM1,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_LM2,\n"
""
                        "#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_LM3,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_LM4,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_LM5,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_LM6\n"
"{\n"
"	background-image: url(:/sa/image/btn_mkr_nor.png);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_LM1:checked,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_LM2:checked,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_LM3:checked,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_LM4:checked,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_LM5:checked,\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] #pb_LM6:checked\n"
"{\n"
"	background-image: url(:/sa/image/btn_mkr_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_Limit[status = \"night\"] #widget\n"
"{\n"
"		background-color:rgba(208,182,139,0.9);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"night\"] #widget>#lblTitle\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"nigh"
                        "t\"] #pb_cancel\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/sa/image/night/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_cancel:pressed\n"
"{\n"
"	border-image: url(:/sa/image/night/btn_close_click.png);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"night\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"night\"] QPushButton\n"
"{\n"
"	background-color:black;\n"
"	color:rgb(130, 130, 130);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_LimitTest,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_Edge,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_toggle,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_LowerLimit,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_UpperLimit,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_ATLdbcLimit\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_LimitTest:checked,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_Edge::checked,\n"
"#SA_Dialo"
                        "g_Limit[status  =  \"night\"] #pb_toggle:checked,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_LowerLimit:checked,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_UpperLimit:checked,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_ATLdbcLimit:checked\n"
"{\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_LimitTest:!checked,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_Edge:!checked,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_toggle:!checked,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_LowerLimit:!checked,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_UpperLimit:!checked,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_ATLdbcLimit:!checked\n"
"{\n"
"	color:rgba(121,106,80,1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}\n"
"\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_Upper:checked\n"
"{\n"
"	background-color:transparent;\n"
"	background-image:url(:/sa/image/night/btn_left_click.png);\n"
"}\n"
""
                        "#SA_Dialog_Limit[status  =  \"night\"] #pb_Upper:!checked\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/night/btn_left_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_Lower:checked\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/night/btn_right_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_Lower:!checked\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/night/btn_right_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_Limit[status  =  \"night\"] #widget>QLabel\n"
"{\n"
"	color:rgb(46,46,46);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"night\"] SA_LineEdit\n"
"{\n"
"	background-color:rgba(251,219,167,0.6);\n"
"	color:rgba(162, 115, 0,1);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"night\"] SA_LineEdit:focus\n"
"{\n"
"	border:2px solid rgba(162,115,0,1);\n"
"}\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_LM1,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_LM2,\n"
"#SA_Dialog_Limit[status  =  \"nig"
                        "ht\"] #pb_LM3,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_LM4,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_LM5,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_LM6\n"
"{\n"
"	 background-color:rgb(74,65,50); \n"
"}\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_LM1:checked,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_LM2:checked,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_LM3:checked,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_LM4:checked,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_LM5:checked,\n"
"#SA_Dialog_Limit[status  =  \"night\"] #pb_LM6:checked\n"
"{\n"
"	 background-color:rgb(251,155,0);\n"
"}"));
        widget = new QWidget(SA_Dialog_Limit);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 501, 646));
        lblTitle = new QLabel(widget);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));
        lblTitle->setGeometry(QRect(17, 19, 102, 22));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        lblTitle->setFont(font);
        lblTitle->setStyleSheet(QStringLiteral(""));
        line = new QFrame(widget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(18, 46, 212, 2));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        pb_cancel = new QPushButton(widget);
        pb_cancel->setObjectName(QStringLiteral("pb_cancel"));
        pb_cancel->setGeometry(QRect(212, 6, 35, 35));
        pb_cancel->setStyleSheet(QStringLiteral(""));
        lblLimitLine = new QLabel(widget);
        lblLimitLine->setObjectName(QStringLiteral("lblLimitLine"));
        lblLimitLine->setGeometry(QRect(18, 290, 67, 15));
        pb_toggle = new QPushButton(widget);
        pb_toggle->setObjectName(QStringLiteral("pb_toggle"));
        pb_toggle->setGeometry(QRect(94, 282, 90, 30));
        pb_toggle->setStyleSheet(QStringLiteral(""));
        pb_toggle->setCheckable(true);
        pb_EditMask = new QPushButton(widget);
        pb_EditMask->setObjectName(QStringLiteral("pb_EditMask"));
        pb_EditMask->setGeometry(QRect(18, 332, 216, 30));
        pb_EditMask->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(255, 255, 255, 1);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"	text-align:center;\n"
"}\n"
"\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(0, 0, 0, 1);\n"
"	border-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"	text-align:center;\n"
"}\n"
"\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_Limit[status  =  \"night\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font"
                        "-weight:bold;\n"
"	color: #FBDBA7;\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"	text-align:center;\n"
"}\n"
"\n"
"#SA_Dialog_Limit[status  =  \"night\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/btn_w216_click.png);\n"
"}"));
        pb_LM1 = new QPushButton(widget);
        pb_LM1->setObjectName(QStringLiteral("pb_LM1"));
        pb_LM1->setGeometry(QRect(94, 67, 140, 30));
        pb_LM1->setCheckable(true);
        pb_LM2 = new QPushButton(widget);
        pb_LM2->setObjectName(QStringLiteral("pb_LM2"));
        pb_LM2->setGeometry(QRect(94, 100, 140, 30));
        pb_LM2->setCheckable(true);
        pb_LM3 = new QPushButton(widget);
        pb_LM3->setObjectName(QStringLiteral("pb_LM3"));
        pb_LM3->setGeometry(QRect(94, 133, 140, 30));
        pb_LM3->setCheckable(true);
        pb_LM4 = new QPushButton(widget);
        pb_LM4->setObjectName(QStringLiteral("pb_LM4"));
        pb_LM4->setGeometry(QRect(94, 166, 140, 30));
        pb_LM4->setCheckable(true);
        pb_LM5 = new QPushButton(widget);
        pb_LM5->setObjectName(QStringLiteral("pb_LM5"));
        pb_LM5->setGeometry(QRect(94, 199, 140, 30));
        pb_LM5->setCheckable(true);
        pb_LM6 = new QPushButton(widget);
        pb_LM6->setObjectName(QStringLiteral("pb_LM6"));
        pb_LM6->setGeometry(QRect(94, 232, 140, 30));
        pb_LM6->setCheckable(true);
        pb_Edge = new QPushButton(widget);
        pb_Edge->setObjectName(QStringLiteral("pb_Edge"));
        pb_Edge->setGeometry(QRect(94, 382, 90, 30));
        pb_Edge->setStyleSheet(QStringLiteral(""));
        pb_Edge->setCheckable(true);
        lblLimitEdge = new QLabel(widget);
        lblLimitEdge->setObjectName(QStringLiteral("lblLimitEdge"));
        lblLimitEdge->setGeometry(QRect(18, 390, 71, 15));
        lineEdit = new SA_LineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(94, 432, 140, 30));
        lineEdit->setStyleSheet(QLatin1String("SA_LineEdit\n"
"{\n"
"	color:rgba(162, 115, 0,1);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
""));
        lineEdit->setReadOnly(true);
        pb_LimitTest = new QPushButton(widget);
        pb_LimitTest->setObjectName(QStringLiteral("pb_LimitTest"));
        pb_LimitTest->setGeometry(QRect(94, 482, 90, 30));
        pb_LimitTest->setStyleSheet(QStringLiteral(""));
        pb_LimitTest->setCheckable(true);
        lblLimitTest = new QLabel(widget);
        lblLimitTest->setObjectName(QStringLiteral("lblLimitTest"));
        lblLimitTest->setGeometry(QRect(18, 482, 71, 30));
        pb_Upper = new QPushButton(widget);
        buttonGroup = new QButtonGroup(SA_Dialog_Limit);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(pb_Upper);
        pb_Upper->setObjectName(QStringLiteral("pb_Upper"));
        pb_Upper->setGeometry(QRect(94, 532, 69, 30));
        pb_Upper->setFont(font);
        pb_Upper->setFocusPolicy(Qt::NoFocus);
        pb_Upper->setCheckable(true);
        pb_Upper->setChecked(true);
        pb_Lower = new QPushButton(widget);
        buttonGroup->addButton(pb_Lower);
        pb_Lower->setObjectName(QStringLiteral("pb_Lower"));
        pb_Lower->setGeometry(QRect(165, 532, 69, 30));
        pb_Lower->setFocusPolicy(Qt::NoFocus);
        pb_Lower->setCheckable(true);
        lblLimitType = new QLabel(widget);
        lblLimitType->setObjectName(QStringLiteral("lblLimitType"));
        lblLimitType->setGeometry(QRect(18, 532, 71, 30));
        pb_DeleteAll = new QPushButton(widget);
        pb_DeleteAll->setObjectName(QStringLiteral("pb_DeleteAll"));
        pb_DeleteAll->setGeometry(QRect(18, 582, 216, 30));
        pb_DeleteAll->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(255, 255, 255, 1);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"	text-align:center;\n"
"}\n"
"\n"
"#SA_Dialog_Limit[status  =  \"indoor\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(0, 0, 0, 1);\n"
"	border-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"	text-align:center;\n"
"}\n"
"\n"
"#SA_Dialog_Limit[status  =  \"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_Limit[status  =  \"night\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font"
                        "-weight:bold;\n"
"	color: #FBDBA7;\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"	text-align:center;\n"
"}\n"
"\n"
"#SA_Dialog_Limit[status  =  \"night\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/btn_w216_click.png);\n"
"}"));
        lblEditLimitEdge = new QLabel(widget);
        lblEditLimitEdge->setObjectName(QStringLiteral("lblEditLimitEdge"));
        lblEditLimitEdge->setGeometry(QRect(18, 432, 67, 30));
        lblLimit = new QLabel(widget);
        lblLimit->setObjectName(QStringLiteral("lblLimit"));
        lblLimit->setGeometry(QRect(18, 75, 51, 15));
        labelWarning = new QLabel(widget);
        labelWarning->setObjectName(QStringLiteral("labelWarning"));
        labelWarning->setGeometry(QRect(20, 50, 211, 71));
        lblUpperLimit = new QLabel(widget);
        lblUpperLimit->setObjectName(QStringLiteral("lblUpperLimit"));
        lblUpperLimit->setGeometry(QRect(290, 70, 67, 30));
        lblLowerLimit = new QLabel(widget);
        lblLowerLimit->setObjectName(QStringLiteral("lblLowerLimit"));
        lblLowerLimit->setGeometry(QRect(290, 190, 67, 30));
        pb_UpperLimit = new QPushButton(widget);
        pb_UpperLimit->setObjectName(QStringLiteral("pb_UpperLimit"));
        pb_UpperLimit->setGeometry(QRect(340, 70, 90, 30));
        pb_UpperLimit->setStyleSheet(QStringLiteral(""));
        pb_UpperLimit->setCheckable(true);
        pb_LowerLimit = new QPushButton(widget);
        pb_LowerLimit->setObjectName(QStringLiteral("pb_LowerLimit"));
        pb_LowerLimit->setGeometry(QRect(340, 190, 90, 30));
        pb_LowerLimit->setStyleSheet(QStringLiteral(""));
        pb_LowerLimit->setCheckable(true);
        UpperLimitEdit = new SA_LineEdit(widget);
        UpperLimitEdit->setObjectName(QStringLiteral("UpperLimitEdit"));
        UpperLimitEdit->setGeometry(QRect(340, 120, 140, 30));
        UpperLimitEdit->setStyleSheet(QLatin1String("SA_LineEdit\n"
"{\n"
"	color:rgba(162, 115, 0,1);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
""));
        UpperLimitEdit->setReadOnly(true);
        LowerLimitEdit = new SA_LineEdit(widget);
        LowerLimitEdit->setObjectName(QStringLiteral("LowerLimitEdit"));
        LowerLimitEdit->setGeometry(QRect(340, 240, 140, 30));
        LowerLimitEdit->setStyleSheet(QLatin1String("SA_LineEdit\n"
"{\n"
"	color:rgba(162, 115, 0,1);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
""));
        LowerLimitEdit->setReadOnly(true);
        ATLdbcLimitEdit = new SA_LineEdit(widget);
        ATLdbcLimitEdit->setObjectName(QStringLiteral("ATLdbcLimitEdit"));
        ATLdbcLimitEdit->setGeometry(QRect(340, 360, 140, 30));
        ATLdbcLimitEdit->setStyleSheet(QLatin1String("SA_LineEdit\n"
"{\n"
"	color:rgba(162, 115, 0,1);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
""));
        ATLdbcLimitEdit->setReadOnly(true);
        pb_ATLdbcLimit = new QPushButton(widget);
        pb_ATLdbcLimit->setObjectName(QStringLiteral("pb_ATLdbcLimit"));
        pb_ATLdbcLimit->setGeometry(QRect(340, 310, 90, 30));
        pb_ATLdbcLimit->setStyleSheet(QStringLiteral(""));
        pb_ATLdbcLimit->setCheckable(true);
        lblLATLdbcLimit = new QLabel(widget);
        lblLATLdbcLimit->setObjectName(QStringLiteral("lblLATLdbcLimit"));
        lblLATLdbcLimit->setGeometry(QRect(290, 310, 67, 30));

        retranslateUi(SA_Dialog_Limit);

        QMetaObject::connectSlotsByName(SA_Dialog_Limit);
    } // setupUi

    void retranslateUi(QWidget *SA_Dialog_Limit)
    {
        SA_Dialog_Limit->setWindowTitle(QApplication::translate("SA_Dialog_Limit", "Form", 0));
        SA_Dialog_Limit->setProperty("status", QVariant(QApplication::translate("SA_Dialog_Limit", "night", 0)));
        lblTitle->setText(QApplication::translate("SA_Dialog_Limit", "Limit", 0));
        pb_cancel->setText(QString());
        lblLimitLine->setText(QApplication::translate("SA_Dialog_Limit", "Limit Line", 0));
        pb_toggle->setText(QApplication::translate("SA_Dialog_Limit", "Off", 0));
        pb_EditMask->setText(QApplication::translate("SA_Dialog_Limit", "Edit Limit Line Table", 0));
        pb_EditMask->setProperty("status", QVariant(QApplication::translate("SA_Dialog_Limit", "outdoor", 0)));
        pb_LM1->setText(QApplication::translate("SA_Dialog_Limit", "Limit1", 0));
        pb_LM2->setText(QApplication::translate("SA_Dialog_Limit", "Limit2", 0));
        pb_LM3->setText(QApplication::translate("SA_Dialog_Limit", "Limit3", 0));
        pb_LM4->setText(QApplication::translate("SA_Dialog_Limit", "Limit4", 0));
        pb_LM5->setText(QApplication::translate("SA_Dialog_Limit", "Limit5", 0));
        pb_LM6->setText(QApplication::translate("SA_Dialog_Limit", "Limit6", 0));
        pb_Edge->setText(QApplication::translate("SA_Dialog_Limit", "Off", 0));
        lblLimitEdge->setText(QApplication::translate("SA_Dialog_Limit", "Limit Edge", 0));
        lineEdit->setInputMask(QString());
        lineEdit->setPlaceholderText(QString());
        pb_LimitTest->setText(QApplication::translate("SA_Dialog_Limit", "Off", 0));
        lblLimitTest->setText(QApplication::translate("SA_Dialog_Limit", "Limit Test", 0));
        pb_Upper->setText(QApplication::translate("SA_Dialog_Limit", "Upper", 0));
        pb_Lower->setText(QApplication::translate("SA_Dialog_Limit", "Lower", 0));
        lblLimitType->setText(QApplication::translate("SA_Dialog_Limit", "Limit Type", 0));
        pb_DeleteAll->setText(QApplication::translate("SA_Dialog_Limit", "Delete All  Limits", 0));
        lblEditLimitEdge->setText(QApplication::translate("SA_Dialog_Limit", "Edit Limit\n"
"Edge", 0));
        lblLimit->setText(QApplication::translate("SA_Dialog_Limit", "Limit", 0));
        labelWarning->setText(QString());
        lblUpperLimit->setText(QApplication::translate("SA_Dialog_Limit", "Upper\n"
"Limit", 0));
        lblLowerLimit->setText(QApplication::translate("SA_Dialog_Limit", "Lower\n"
"Limit", 0));
        pb_UpperLimit->setText(QApplication::translate("SA_Dialog_Limit", "Off", 0));
        pb_LowerLimit->setText(QApplication::translate("SA_Dialog_Limit", "Off", 0));
        UpperLimitEdit->setInputMask(QString());
        UpperLimitEdit->setPlaceholderText(QString());
        LowerLimitEdit->setInputMask(QString());
        LowerLimitEdit->setPlaceholderText(QString());
        ATLdbcLimitEdit->setInputMask(QString());
        ATLdbcLimitEdit->setPlaceholderText(QString());
        pb_ATLdbcLimit->setText(QApplication::translate("SA_Dialog_Limit", "Off", 0));
        lblLATLdbcLimit->setText(QApplication::translate("SA_Dialog_Limit", "ALT CH\n"
"Limit", 0));
    } // retranslateUi

};

namespace Ui {
    class SA_Dialog_Limit: public Ui_SA_Dialog_Limit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_LIMIT_H
