/********************************************************************************
** Form generated from reading UI file 'sa_dialog_tracesetup.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_TRACESETUP_H
#define UI_SA_DIALOG_TRACESETUP_H

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
#include "sa_combobox.h"

QT_BEGIN_NAMESPACE

class Ui_SA_Dialog_TraceSetup
{
public:
    QWidget *widget;
    QPushButton *pb_cancel;
    QLabel *lblTitle;
    QFrame *line;
    QLabel *lblTraceType;
    QLabel *lblDete;
    SA_Combobox *TR_Type;
    QPushButton *pb_toggle;
    QLabel *lblTrace;
    QPushButton *pb_T1;
    QPushButton *pb_T2;
    QPushButton *pb_T3;
    QPushButton *pb_T5;
    QPushButton *pb_T4;
    QPushButton *pb_T6;
    SA_Combobox *TR_Detector;
    QLabel *lblAveCount;
    SA_LineEdit *averageEdit;
    QLabel *lblTraceView;
    QPushButton *pb_clearall;
    QPushButton *pb_traceAllOn;
    QPushButton *pb_toggle_Ave;
    QLabel *lblAveToggle;

    void setupUi(QWidget *SA_Dialog_TraceSetup)
    {
        if (SA_Dialog_TraceSetup->objectName().isEmpty())
            SA_Dialog_TraceSetup->setObjectName(QStringLiteral("SA_Dialog_TraceSetup"));
        SA_Dialog_TraceSetup->resize(252, 646);
        SA_Dialog_TraceSetup->setStyleSheet(QLatin1String("#pb_T1,\n"
"#pb_T2,\n"
"#pb_T3,\n"
"#pb_T4,\n"
"#pb_T5,\n"
"#pb_T6\n"
"{\n"
"	font:75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:10px;\n"
"	color:rgb(131, 131, 131);\n"
"	border-style:flat;\n"
"}\n"
"#pb_T1:checked,\n"
"#pb_T2:checked,\n"
"#pb_T3:checked,\n"
"#pb_T4:checked,\n"
"#pb_T5:checked,\n"
"#pb_T6:checked\n"
"{\n"
"	color:rgb(87, 87, 87);\n"
"}\n"
"#widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
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
"\n"
"#line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"QComboBox\n"
"{\n"
"	font: 75 13p"
                        "x \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(162, 115, 0, 1);\n"
"	padding:8px 23px 7px 7px;\n"
"	combobox-popup: 0;\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/dropdown_normal.png);\n"
"}\n"
"QComboBox:focus\n"
"{\n"
"	background-image: url(:/sa/image/dropdown_click.png);\n"
"	\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"width:5px;	\n"
"border-style:flat;\n"
"}\n"
"\n"
"\n"
"QComboBox QAbstractItemView{\n"
"   font: 75 14px \"Arial\";\n"
"	color:rgba(0, 0, 0, 1);\n"
"	background:rgba(255,255,255,1);\n"
" 	outline:0px;\n"
"	border-style:solid;\n"
"	border-color:rgba(151, 151, 151, 1);\n"
"	border-width:1px;\n"
"}\n"
"QAbstractItemView::item{\n"
"	padding-left:8px;\n"
"	width:140px;\n"
"	height:32px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(240, 179, 29, 1); \n"
"}\n"
"\n"
"#pb_toggle,\n"
"#pb_toggle_Ave\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	padding:7px 17px 6px 3"
                        "6px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#pb_toggle:checked,\n"
"#pb_toggle_Ave:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"SA_LineEdit\n"
"{\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 7px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"SA_LineEdit:disable\n"
"{\n"
"	color:rgba(133,133,133,0.6);\n"
"}\n"
"SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"}\n"
"#pb_traceAllOn,\n"
"#pb_clearall\n"
"{	\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgb(255,255,255);\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"#pb_traceAllOn:pressed,\n"
"#pb_clearall:pressed\n"
"{	\n"
"	\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #pb_T1,\n"
"#S"
                        "A_Dialog_TraceSetup[status = \"indoor\"]  #pb_T2,\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #pb_T3,\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #pb_T4,\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #pb_T5,\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #pb_T6\n"
"{\n"
"	color:rgb(131, 131, 131);\n"
"	background-image: url(:/sa/image/btn_mkr_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #pb_T1:checked,\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #pb_T2:checked,\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #pb_T3:checked,\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #pb_T4:checked,\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #pb_T5:checked,\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #pb_T6:checked\n"
"{\n"
"	color:rgb(87, 87, 87);\n"
"	background-image: url(:/sa/image/btn_mkr_click.png);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #widge"
                        "t>QLabel\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #widget>#lblTitle\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #pb_cancel\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #pb_cancel:pressed\n"
"{\n"
"	border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  QComboBox\n"
"{\n"
"	color:rgba(162, 115, 0, 1);\n"
"	background-image: url(:/sa/image/dropdown_normal.png);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  QComboBox:focus\n"
"{\n"
"	background-image: url(:/sa/image/dropdown_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  QComboBox QAbstractItemView\n"
"{\n"
"	color:rgba(0, 0, 0, 1);\n"
"	background:rgba(255,255,255,1);\n"
"	b"
                        "order-color:rgba(151, 151, 151, 1);\n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(240, 179, 29, 1); \n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #pb_toggle,\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #pb_toggle_Ave\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #pb_toggle:checked,\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #pb_toggle_Ave:checked\n"
"{\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  SA_LineEdit\n"
"{\n"
"	color:rgba(162, 115, 0,1);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  SA_LineEdit:disable\n"
"{\n"
"	color:rgba(133,133,133,0.6);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  SA_LineEdit:focus\n"
"{\n"
"	border:2px solid rgba(162,115,0,1);\n"
""
                        "}\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #pb_traceAllOn,\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #pb_clearall\n"
"{	\n"
"	color:rgb(255,255,255);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #pb_traceAllOn:pressed,\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"]  #pb_clearall:pressed\n"
"{	\n"
"	\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #pb_T1,\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #pb_T2,\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #pb_T3,\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #pb_T4,\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #pb_T5,\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #pb_T6\n"
"{\n"
"	color:rgb(131, 131, 131);\n"
"	background-image: url(:/sa/image/btn_mkr_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #pb_T1:checked,\n"
"#"
                        "SA_Dialog_TraceSetup[status = \"outdoor\"]  #pb_T2:checked,\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #pb_T3:checked,\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #pb_T4:checked,\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #pb_T5:checked,\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #pb_T6:checked\n"
"{\n"
"	color:rgb(87, 87, 87);\n"
"	background-image: url(:/sa/image/btn_mkr_click.png);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #widget>QLabel\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #widget>#lblTitle\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #pb_cancel\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #pb_cancel:pressed\n"
"{\n"
"	border-image: url(:/sa/image/btn_clo"
                        "se_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  QComboBox\n"
"{\n"
"	color:rgba(162, 115, 0, 1);\n"
"	background-image: url(:/sa/image/dropdown_normal.png);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  QComboBox:focus\n"
"{\n"
"	background-image: url(:/sa/image/dropdown_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  QComboBox QAbstractItemView\n"
"{\n"
"	color:rgba(0, 0, 0, 1);\n"
"	background:rgba(255,255,255,1);\n"
"	border-color:rgba(151, 151, 151, 1);\n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(240, 179, 29, 1); \n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #pb_toggle,\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #pb_toggle_Ave\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/tog"
                        "gle_off.png);\n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #pb_toggle:checked,\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #pb_toggle_Ave:checked\n"
"{\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  SA_LineEdit\n"
"{\n"
"	color:rgba(162, 115, 0,1);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  SA_LineEdit:disable\n"
"{\n"
"	color:rgba(133,133,133,0.6);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  SA_LineEdit:focus\n"
"{\n"
"	border:2px solid rgba(162,115,0,1);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #pb_traceAllOn,\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #pb_clearall\n"
"{	\n"
"	color:rgb(255,255,255);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #pb_traceAllOn:pressed,\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"]  #pb_clearall:pressed\n"
"{	\n"
"	\n"
"	background-image: url(:/sa/i"
                        "mage/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #pb_T1,\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #pb_T2,\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #pb_T3,\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #pb_T4,\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #pb_T5,\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #pb_T6\n"
"{\n"
"	color:rgb(131, 131, 131);\n"
"   background-color:rgb(74,65,50);\n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #pb_T1:checked,\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #pb_T2:checked,\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #pb_T3:checked,\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #pb_T4:checked,\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #pb_T5:checked,\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #pb_T6:checked\n"
"{\n"
"	color:rgb(87, 87, 87);\n"
"	background-color:rgb(251,155,0);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #widget\n"
"{\n"
""
                        "	background-color:rgba(208,182,139,0.9);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #widget>QLabel\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #widget>#lblTitle\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #pb_cancel\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/sa/image/night/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #pb_cancel:pressed\n"
"{\n"
"	border-image: url(:/sa/image/night/btn_close_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  QComboBox\n"
"{\n"
"	background-color: rgba(251,220,167,0.60);\n"
"	color:rgba(159,98,0,1);\n"
"	background-image: url(:/sa/image/night/dropdown_normal.png);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  QComboBox:focus\n"
"{\n"
"	background-image: url(:/sa/image/night/dropdown_click.png);\n"
""
                        "}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  QComboBox QAbstractItemView\n"
"{\n"
"	color:rgba(0, 0, 0, 1);\n"
"	background-color: #FBDBA7;\n"
"	border-color:rgba(151, 151, 151, 1);\n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  QComboBox QAbstractItemView::item:selected\n"
"{\n"
"		color:rgba(159,98,0,1);\n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #pb_toggle,\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #pb_toggle_Ave\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	color:rgba(121,106,80,1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #pb_toggle:checked,\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #pb_toggle_Ave:checked\n"
"{\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  SA_LineEdit\n"
"{\n"
"		background-color: rgba(251,219,167,0.6);\n"
"		color:rgba(159,98,0,1);\n"
"}\n"
"#SA_Dialog_TraceSetup[status "
                        "= \"night\"]  SA_LineEdit:disable\n"
"{\n"
"		background-color: rgba(130,114,87,0.60);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  SA_LineEdit:focus\n"
"{\n"
"	border:2px solid rgba(162,115,0,1);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #pb_traceAllOn,\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #pb_clearall\n"
"{	\n"
"	color:rgba(251,219,167,1);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #pb_traceAllOn:pressed,\n"
"#SA_Dialog_TraceSetup[status = \"night\"]  #pb_clearall:pressed\n"
"{	\n"
"	\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}"));
        widget = new QWidget(SA_Dialog_TraceSetup);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 252, 646));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        widget->setFont(font);
        widget->setStyleSheet(QStringLiteral(""));
        pb_cancel = new QPushButton(widget);
        pb_cancel->setObjectName(QStringLiteral("pb_cancel"));
        pb_cancel->setGeometry(QRect(212, 6, 35, 35));
        pb_cancel->setCheckable(false);
        lblTitle = new QLabel(widget);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));
        lblTitle->setGeometry(QRect(17, 19, 98, 22));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        lblTitle->setFont(font1);
        line = new QFrame(widget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(18, 46, 212, 2));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        lblTraceType = new QLabel(widget);
        lblTraceType->setObjectName(QStringLiteral("lblTraceType"));
        lblTraceType->setGeometry(QRect(18, 382, 71, 30));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(9);
        lblTraceType->setFont(font2);
        lblDete = new QLabel(widget);
        lblDete->setObjectName(QStringLiteral("lblDete"));
        lblDete->setGeometry(QRect(18, 482, 71, 30));
        lblDete->setFont(font2);
        TR_Type = new SA_Combobox(widget);
        TR_Type->setObjectName(QStringLiteral("TR_Type"));
        TR_Type->setGeometry(QRect(94, 382, 140, 30));
        TR_Type->setFont(font1);
        TR_Type->setStyleSheet(QStringLiteral(""));
        TR_Type->setEditable(false);
        TR_Type->setDuplicatesEnabled(false);
        TR_Type->setFrame(true);
        pb_toggle = new QPushButton(widget);
        pb_toggle->setObjectName(QStringLiteral("pb_toggle"));
        pb_toggle->setGeometry(QRect(94, 282, 90, 30));
        pb_toggle->setFocusPolicy(Qt::NoFocus);
        pb_toggle->setStyleSheet(QStringLiteral(""));
        pb_toggle->setCheckable(true);
        lblTrace = new QLabel(widget);
        lblTrace->setObjectName(QStringLiteral("lblTrace"));
        lblTrace->setGeometry(QRect(18, 75, 71, 15));
        lblTrace->setFont(font2);
        pb_T1 = new QPushButton(widget);
        pb_T1->setObjectName(QStringLiteral("pb_T1"));
        pb_T1->setGeometry(QRect(94, 67, 140, 30));
        pb_T1->setFocusPolicy(Qt::NoFocus);
        pb_T1->setCheckable(true);
        pb_T1->setChecked(true);
        pb_T2 = new QPushButton(widget);
        pb_T2->setObjectName(QStringLiteral("pb_T2"));
        pb_T2->setGeometry(QRect(94, 100, 140, 30));
        pb_T2->setFocusPolicy(Qt::NoFocus);
        pb_T2->setCheckable(true);
        pb_T2->setChecked(false);
        pb_T3 = new QPushButton(widget);
        pb_T3->setObjectName(QStringLiteral("pb_T3"));
        pb_T3->setGeometry(QRect(94, 133, 140, 30));
        pb_T3->setFocusPolicy(Qt::NoFocus);
        pb_T3->setCheckable(true);
        pb_T3->setChecked(false);
        pb_T5 = new QPushButton(widget);
        pb_T5->setObjectName(QStringLiteral("pb_T5"));
        pb_T5->setGeometry(QRect(94, 199, 140, 30));
        pb_T5->setFocusPolicy(Qt::NoFocus);
        pb_T5->setCheckable(true);
        pb_T4 = new QPushButton(widget);
        pb_T4->setObjectName(QStringLiteral("pb_T4"));
        pb_T4->setGeometry(QRect(94, 166, 140, 30));
        pb_T4->setFocusPolicy(Qt::NoFocus);
        pb_T4->setCheckable(true);
        pb_T6 = new QPushButton(widget);
        pb_T6->setObjectName(QStringLiteral("pb_T6"));
        pb_T6->setGeometry(QRect(94, 232, 140, 30));
        pb_T6->setFocusPolicy(Qt::NoFocus);
        pb_T6->setCheckable(true);
        TR_Detector = new SA_Combobox(widget);
        TR_Detector->setObjectName(QStringLiteral("TR_Detector"));
        TR_Detector->setGeometry(QRect(94, 482, 140, 30));
        TR_Detector->setFont(font1);
        TR_Detector->setStyleSheet(QStringLiteral(""));
        TR_Detector->setEditable(false);
        TR_Detector->setMaxVisibleItems(123);
        TR_Detector->setDuplicatesEnabled(false);
        TR_Detector->setFrame(true);
        lblAveCount = new QLabel(widget);
        lblAveCount->setObjectName(QStringLiteral("lblAveCount"));
        lblAveCount->setGeometry(QRect(18, 432, 71, 25));
        averageEdit = new SA_LineEdit(widget);
        averageEdit->setObjectName(QStringLiteral("averageEdit"));
        averageEdit->setGeometry(QRect(94, 432, 140, 30));
        averageEdit->setReadOnly(true);
        lblTraceView = new QLabel(widget);
        lblTraceView->setObjectName(QStringLiteral("lblTraceView"));
        lblTraceView->setGeometry(QRect(18, 280, 71, 30));
        lblTraceView->setFont(font2);
        pb_clearall = new QPushButton(widget);
        pb_clearall->setObjectName(QStringLiteral("pb_clearall"));
        pb_clearall->setGeometry(QRect(18, 532, 216, 30));
        pb_clearall->setFont(font1);
        pb_clearall->setFocusPolicy(Qt::NoFocus);
        pb_clearall->setStyleSheet(QLatin1String("/*******************common**********************/\n"
"QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(255, 255, 255, 1);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"	text-align:center;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"] QPushButton\n"
"{\n"
"	color:rgba(255, 255, 255, 1);\n"
"	border-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"] QPushButton\n"
"{\n"
"	color:rgba(0, 0, 0, 1);\n"
"	border-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:"
                        "/sa/image/outdoor/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_TraceSetup[status = \"night\"] QPushButton\n"
"{\n"
"	color: #FBDBA7;\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"night\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/btn_w216_click.png);\n"
"}"));
        pb_traceAllOn = new QPushButton(widget);
        pb_traceAllOn->setObjectName(QStringLiteral("pb_traceAllOn"));
        pb_traceAllOn->setGeometry(QRect(18, 332, 216, 30));
        pb_traceAllOn->setFont(font1);
        pb_traceAllOn->setFocusPolicy(Qt::NoFocus);
        pb_traceAllOn->setStyleSheet(QLatin1String("/*******************common**********************/\n"
"QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(255, 255, 255, 1);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"	text-align:center;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"] QPushButton\n"
"{\n"
"	color:rgba(255, 255, 255, 1);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"indoor\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"] QPushButton\n"
"{\n"
"	color:rgba(0, 0, 0, 1);\n"
"	border-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: u"
                        "rl(:/sa/image/outdoor/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_TraceSetup[status = \"night\"] QPushButton\n"
"{\n"
"	color: #FBDBA7;\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"#SA_Dialog_TraceSetup[status = \"night\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/btn_w216_click.png);\n"
"}"));
        pb_toggle_Ave = new QPushButton(widget);
        pb_toggle_Ave->setObjectName(QStringLiteral("pb_toggle_Ave"));
        pb_toggle_Ave->setGeometry(QRect(140, 573, 90, 30));
        pb_toggle_Ave->setFocusPolicy(Qt::NoFocus);
        pb_toggle_Ave->setStyleSheet(QStringLiteral(""));
        pb_toggle_Ave->setCheckable(true);
        lblAveToggle = new QLabel(widget);
        lblAveToggle->setObjectName(QStringLiteral("lblAveToggle"));
        lblAveToggle->setGeometry(QRect(20, 573, 71, 30));
        lblAveToggle->setFont(font2);
        QWidget::setTabOrder(TR_Type, pb_cancel);
        QWidget::setTabOrder(pb_cancel, pb_clearall);
        QWidget::setTabOrder(pb_clearall, pb_toggle);
        QWidget::setTabOrder(pb_toggle, pb_T1);
        QWidget::setTabOrder(pb_T1, pb_T2);
        QWidget::setTabOrder(pb_T2, pb_T3);
        QWidget::setTabOrder(pb_T3, pb_T5);
        QWidget::setTabOrder(pb_T5, pb_T4);
        QWidget::setTabOrder(pb_T4, pb_T6);

        retranslateUi(SA_Dialog_TraceSetup);

        QMetaObject::connectSlotsByName(SA_Dialog_TraceSetup);
    } // setupUi

    void retranslateUi(QWidget *SA_Dialog_TraceSetup)
    {
        SA_Dialog_TraceSetup->setWindowTitle(QApplication::translate("SA_Dialog_TraceSetup", "Form", Q_NULLPTR));
        SA_Dialog_TraceSetup->setProperty("status", QVariant(QApplication::translate("SA_Dialog_TraceSetup", "night", Q_NULLPTR)));
        pb_cancel->setText(QString());
        lblTitle->setText(QApplication::translate("SA_Dialog_TraceSetup", "Trace  ", Q_NULLPTR));
        lblTraceType->setText(QApplication::translate("SA_Dialog_TraceSetup", "Trace\n"
"Type", Q_NULLPTR));
        lblDete->setText(QApplication::translate("SA_Dialog_TraceSetup", "Detector", Q_NULLPTR));
        TR_Type->clear();
        TR_Type->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_TraceSetup", "Clear Write", Q_NULLPTR)
         << QApplication::translate("SA_Dialog_TraceSetup", "Max Hold", Q_NULLPTR)
         << QApplication::translate("SA_Dialog_TraceSetup", "Min Hold", Q_NULLPTR)
         << QApplication::translate("SA_Dialog_TraceSetup", "View", Q_NULLPTR)
         << QApplication::translate("SA_Dialog_TraceSetup", "Average", Q_NULLPTR)
        );
        pb_toggle->setText(QApplication::translate("SA_Dialog_TraceSetup", "On", Q_NULLPTR));
        lblTrace->setText(QApplication::translate("SA_Dialog_TraceSetup", "Trace", Q_NULLPTR));
        pb_T1->setText(QApplication::translate("SA_Dialog_TraceSetup", "T1", Q_NULLPTR));
        pb_T2->setText(QApplication::translate("SA_Dialog_TraceSetup", "T2", Q_NULLPTR));
        pb_T3->setText(QApplication::translate("SA_Dialog_TraceSetup", "T3", Q_NULLPTR));
        pb_T5->setText(QApplication::translate("SA_Dialog_TraceSetup", "T5", Q_NULLPTR));
        pb_T4->setText(QApplication::translate("SA_Dialog_TraceSetup", "T4", Q_NULLPTR));
        pb_T6->setText(QApplication::translate("SA_Dialog_TraceSetup", "T6", Q_NULLPTR));
        TR_Detector->clear();
        TR_Detector->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_TraceSetup", "Auto", Q_NULLPTR)
         << QApplication::translate("SA_Dialog_TraceSetup", "Positive Peak", Q_NULLPTR)
         << QApplication::translate("SA_Dialog_TraceSetup", "Negative Peak", Q_NULLPTR)
         << QApplication::translate("SA_Dialog_TraceSetup", "Sample", Q_NULLPTR)
         << QApplication::translate("SA_Dialog_TraceSetup", "Normal", Q_NULLPTR)
         << QApplication::translate("SA_Dialog_TraceSetup", "Average Voltage", Q_NULLPTR)
         << QApplication::translate("SA_Dialog_TraceSetup", "RMS", Q_NULLPTR)
        );
        lblAveCount->setText(QApplication::translate("SA_Dialog_TraceSetup", "Average\n"
"Count", Q_NULLPTR));
        averageEdit->setText(QString());
        lblTraceView->setText(QApplication::translate("SA_Dialog_TraceSetup", "Trace View", Q_NULLPTR));
        pb_clearall->setText(QApplication::translate("SA_Dialog_TraceSetup", "Trace Clear All", Q_NULLPTR));
        pb_traceAllOn->setText(QApplication::translate("SA_Dialog_TraceSetup", "Trace  All On", Q_NULLPTR));
        pb_toggle_Ave->setText(QApplication::translate("SA_Dialog_TraceSetup", "On", Q_NULLPTR));
        lblAveToggle->setText(QApplication::translate("SA_Dialog_TraceSetup", "Average", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SA_Dialog_TraceSetup: public Ui_SA_Dialog_TraceSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_TRACESETUP_H
