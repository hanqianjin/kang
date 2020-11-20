/********************************************************************************
** Form generated from reading UI file 'sa_dialog_amptsetup.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_AMPTSETUP_H
#define UI_SA_DIALOG_AMPTSETUP_H

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

class Ui_SA_Dialog_AmptSetup
{
public:
    QWidget *widget;
    QPushButton *pb_Scale_Auto;
    QLabel *label_3;
    SA_LineEdit *edit_level;
    QLabel *lblOffset;
    SA_LineEdit *edit_offset;
    QLabel *label_4;
    SA_LineEdit *edit_scale;
    QLabel *lblAtten;
    QLabel *lblUnit;
    QLabel *lblPreamp;
    QPushButton *pb_Preamp;
    SA_LineEdit *edit_Atten;
    QPushButton *pb_cancel;
    QFrame *line;
    QLabel *lblTitle;
    SA_Combobox *pb_unitSelect;
    QPushButton *pb_Manual;
    QPushButton *pb_Auto;
    SA_LineEdit *edit_ZeroRestrainAtten;
    QLabel *label_5;
    SA_LineEdit *edit_ZeroRestrainPhase;
    QLabel *label_6;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *SA_Dialog_AmptSetup)
    {
        if (SA_Dialog_AmptSetup->objectName().isEmpty())
            SA_Dialog_AmptSetup->setObjectName(QStringLiteral("SA_Dialog_AmptSetup"));
        SA_Dialog_AmptSetup->resize(252, 646);
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        SA_Dialog_AmptSetup->setFont(font);
        SA_Dialog_AmptSetup->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"#widget\n"
"{\n"
"	background-color:rgba(221,221,221,0.9);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"#widget>QPushButton\n"
"{\n"
"\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"#pb_Preamp\n"
"{\n"
"	text-align:left;\n"
"	padding:8px 23px 7px 10px;\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"#widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"		color:rgba(46,46,46,1);\n"
"}\n"
"	\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"#widget>#pb_cancel\n"
"{\n"
"	border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"#widget>#pb_cancel:pressed\n"
"{\n"
"	border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"#widget>#line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[stat"
                        "us  =  \"indoor\"] \n"
"#AttenType_widget{\n"
"	policy:nofocus;\n"
"	background-image: url(:/sa/image/dropdown_box.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"#AttenType_widget>QPushButton\n"
"{\n"
"	policy:nofocus;\n"
"	font: 14px \"Arial\";\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"#AttenType_widget>QPushButton:checked\n"
"{\n"
"\n"
"	color:rgba(240, 179, 29, 1);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"#AttenType_widget>QPushButton:!checked\n"
"{\n"
"	color:rgba(0, 0, 0, 1)\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"#pb_Atten_Type\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(162, 115, 0, 1);\n"
"	background-image: url(:/sa/image/dropdown_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"#pb_Atten_Type:focus\n"
"{	\n"
"	background-image: url(:/sa/image/dropdown_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"SA_LineEdit\n"
"{\n"
"	col"
                        "or:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"SA_LineEdit:disable\n"
"{\n"
"	color:rgba(133,133,133,0.6);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"QComboBox\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(162, 115, 0, 1);\n"
"	padding:8px 23px 7px 10px;\n"
"	combobox-popup: 0;\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/dropdown_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"QComboBox:focus\n"
"{\n"
"	background-image: url(:/sa/image/dropdown_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"QComboBox::drop-down \n"
"{\n"
"	width: 0px;	\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"]"
                        " \n"
"QComboBox QAbstractItemView{\n"
"   font: 75 14px \"Arial\";\n"
"	color:rgba(0, 0, 0, 1);\n"
"	background:rgba(255,255,255,1);\n"
" 	outline:0px;\n"
"	border-style:solid;\n"
"	border-color:rgba(151, 151, 151, 1);\n"
"	border-width:1px;\n"
"}\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"QAbstractItemView::item{\n"
"	padding-left:8px;\n"
"	width:140px;\n"
"	height:32px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(240, 179, 29, 1); \n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"#pb_Auto:checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"#pb_Auto\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/"
                        "image/fre_checked_right.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"#pb_Manual:checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"#pb_Manual\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"#pb_Scale_Auto\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(255, 255, 255, 1);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"	text-align:center;\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] \n"
"#pb_Scale_Auto:pressed\n"
"{\n"
"	\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"/***********"
                        "********outdoor**********************/\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"#widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"#widget>QPushButton\n"
"{\n"
"\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"#pb_Preamp\n"
"{\n"
"	text-align:left;\n"
"	padding:8px 23px 7px 10px;\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"#widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"	\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"#widget>#pb_cancel\n"
"{\n"
"	border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"#widget>#pb_cancel:pressed\n"
"{\n"
"	border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"#widget>#line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  ="
                        "  \"outdoor\"] \n"
"#AttenType_widget{\n"
"	policy:nofocus;\n"
"	background-image: url(:/sa/image/dropdown_box.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"#AttenType_widget>QPushButton\n"
"{\n"
"	policy:nofocus;\n"
"	font: 14px \"Arial\";\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"#AttenType_widget>QPushButton:checked\n"
"{\n"
"\n"
"	color:rgba(240, 179, 29, 1);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"#AttenType_widget>QPushButton:!checked\n"
"{\n"
"	color:rgba(0, 0, 0, 1)\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"#pb_Atten_Type\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(162, 115, 0, 1);\n"
"	background-image: url(:/sa/image/dropdown_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"#pb_Atten_Type:focus\n"
"{	\n"
"	background-image: url(:/sa/image/dropdown_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"SA_LineEdit\n"
"{\n"
"	c"
                        "olor:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"SA_LineEdit:disable\n"
"{\n"
"	color:rgba(133,133,133,0.6);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"QComboBox\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(162, 115, 0, 1);\n"
"	padding:8px 23px 7px 10px;\n"
"	combobox-popup: 0;\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/dropdown_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"QComboBox:focus\n"
"{\n"
"	background-image: url(:/sa/image/dropdown_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"QComboBox::drop-down \n"
"{\n"
"	width: 0px;	\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"ou"
                        "tdoor\"] \n"
"QComboBox QAbstractItemView{\n"
"   font: 75 14px \"Arial\";\n"
"	color:rgba(0, 0, 0, 1);\n"
"	background:rgba(255,255,255,1);\n"
" 	outline:0px;\n"
"	border-style:solid;\n"
"	border-color:rgba(151, 151, 151, 1);\n"
"	border-width:1px;\n"
"}\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"QAbstractItemView::item{\n"
"	padding-left:8px;\n"
"	width:140px;\n"
"	height:32px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(240, 179, 29, 1); \n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"#pb_Auto:checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"#pb_Auto\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-imag"
                        "e: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"#pb_Manual:checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"#pb_Manual\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"#pb_Scale_Auto\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(0, 0, 0, 1);\n"
"	\n"
"	border-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"	text-align:center;\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] \n"
"#pb_Scale_Auto:pressed\n"
"{\n"
"	border-image: url(:/sa/image/outdoor/btn_w216_click.png);\n"
""
                        "}\n"
"/*******************night**********************/\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"#widget\n"
"{\n"
"		background-color:rgba(208,182,139,0.9);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"#widget>QPushButton\n"
"{\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"#pb_Preamp\n"
"{\n"
"	text-align:left;\n"
"	padding:8px 23px 7px 10px;\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"#widget>QLabel\n"
"{\n"
"	   font: 75 13px \"Arial\";\n"
"		color:rgba(46,46,46,1);\n"
"}\n"
"	\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"#widget>#pb_cancel\n"
"{\n"
"	border-image: url(:/sa/image/night/btn_close_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"#widget>#pb_cancel:pressed\n"
"{\n"
"	border-image: url(:/sa/image/night/btn_close_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"#widget>#line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_AmptS"
                        "etup[status  =  \"night\"] \n"
"#AttenType_widget{\n"
"	policy:nofocus;\n"
"	background-image: url(:/sa/image/dropdown_box.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"#AttenType_widget>QPushButton\n"
"{\n"
"	policy:nofocus;\n"
"	font: 14px \"Arial\";\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"#AttenType_widget>QPushButton:checked\n"
"{\n"
"\n"
"	color:rgba(240, 179, 29, 1);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"#AttenType_widget>QPushButton:!checked\n"
"{\n"
"	color:rgba(0, 0, 0, 1)\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"#pb_Atten_Type\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(162, 115, 0, 1);\n"
"	background-image: url(:/sa/image/dropdown_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"#pb_Atten_Type:focus\n"
"{	\n"
"	background-image: url(:/sa/image/dropdown_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"SA_LineEdit\n"
"{\n"
"	b"
                        "ackground: rgba(251,220,167,0.60);\n"
"   color:rgba(159,98,0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"SA_LineEdit:disable\n"
"{\n"
"	color:rgba(133,133,133,0.6);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"}\n"
"\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"QComboBox\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"    background-color:rgba(251,220,167,0.60);\n"
"    color:rgba(159,98,0,1);\n"
"	padding:8px 23px 7px 10px;\n"
"	combobox-popup: 0;\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/night/dropdown_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"QComboBox:focus\n"
"{\n"
"	background-color:rgba(251,220,167,0.60);\n"
"	background-image: url(:/sa/image/night/dropdown_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status "
                        " =  \"night\"] \n"
"QComboBox::drop-down \n"
"{\n"
"	width: 0px;	\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"QComboBox QAbstractItemView{\n"
"   font: 75 14px \"Arial\";\n"
"	color:rgba(0, 0, 0, 1);\n"
"	background-color:#FBDBA7;;\n"
"    \n"
" 	outline:0px;\n"
"	border-style:solid;\n"
"	border-color:rgba(151, 151, 151, 1);\n"
"	border-width:1px;\n"
"}\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"QAbstractItemView::item{\n"
"	padding-left:8px;\n"
"	width:140px;\n"
"	height:32px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(159,98,0,1);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"#pb_Auto:checked\n"
"{\n"
"	color:rgba(85,74,56,1);\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/night/btn_left_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"#pb_Auto\n"
"{\n"
"	color:rgba(121,106,81,1);\n"
""
                        "	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/night/btn_left_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"#pb_Manual:checked\n"
"{\n"
"\n"
"	color:rgba(85,74,56,1);\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/night/btn_right_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"#pb_Manual\n"
"{\n"
"	color:rgba(121,106,81,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/night/btn_right_nor.png);\n"
"}\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"#pb_Scale_Auto\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color: #FBDBA7;\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"	text-align:center;\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] \n"
"#pb_Scale_Auto:pressed\n"
"{\n"
"	background-image: url(:"
                        "/sa/image/night/btn_w216_click.png);\n"
"}"));
        widget = new QWidget(SA_Dialog_AmptSetup);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 252, 646));
        widget->setStyleSheet(QStringLiteral(""));
        pb_Scale_Auto = new QPushButton(widget);
        pb_Scale_Auto->setObjectName(QStringLiteral("pb_Scale_Auto"));
        pb_Scale_Auto->setGeometry(QRect(17, 67, 216, 30));
        pb_Scale_Auto->setFocusPolicy(Qt::NoFocus);
        pb_Scale_Auto->setStyleSheet(QStringLiteral(""));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(18, 117, 66, 30));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(9);
        label_3->setFont(font1);
        edit_level = new SA_LineEdit(widget);
        edit_level->setObjectName(QStringLiteral("edit_level"));
        edit_level->setGeometry(QRect(94, 117, 140, 30));
        edit_level->setReadOnly(true);
        lblOffset = new QLabel(widget);
        lblOffset->setObjectName(QStringLiteral("lblOffset"));
        lblOffset->setGeometry(QRect(18, 362, 54, 30));
        edit_offset = new SA_LineEdit(widget);
        edit_offset->setObjectName(QStringLiteral("edit_offset"));
        edit_offset->setGeometry(QRect(94, 362, 140, 30));
        edit_offset->setReadOnly(true);
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(18, 167, 71, 30));
        edit_scale = new SA_LineEdit(widget);
        edit_scale->setObjectName(QStringLiteral("edit_scale"));
        edit_scale->setGeometry(QRect(94, 167, 140, 30));
        edit_scale->setReadOnly(true);
        lblAtten = new QLabel(widget);
        lblAtten->setObjectName(QStringLiteral("lblAtten"));
        lblAtten->setGeometry(QRect(18, 225, 72, 15));
        lblUnit = new QLabel(widget);
        lblUnit->setObjectName(QStringLiteral("lblUnit"));
        lblUnit->setGeometry(QRect(18, 420, 66, 15));
        lblUnit->setFont(font1);
        lblPreamp = new QLabel(widget);
        lblPreamp->setObjectName(QStringLiteral("lblPreamp"));
        lblPreamp->setGeometry(QRect(18, 322, 52, 15));
        pb_Preamp = new QPushButton(widget);
        pb_Preamp->setObjectName(QStringLiteral("pb_Preamp"));
        pb_Preamp->setGeometry(QRect(94, 312, 90, 30));
        pb_Preamp->setFocusPolicy(Qt::NoFocus);
        pb_Preamp->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] #pb_Preamp\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] #pb_Preamp:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"indoor\"] #pb_Preamp:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] #pb_Preamp\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] #pb_Preamp:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
""
                        "\n"
"#SA_Dialog_AmptSetup[status  =  \"outdoor\"] #pb_Preamp:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] #pb_Preamp\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] #pb_Preamp:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87,87,87,1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}\n"
"\n"
"#SA_Dialog_AmptSetup[status  =  \"night\"] #pb_Preamp:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"\n"
"	color:rgba(121,106,80,1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}"));
        pb_Preamp->setCheckable(true);
        pb_Preamp->setChecked(false);
        edit_Atten = new SA_LineEdit(widget);
        edit_Atten->setObjectName(QStringLiteral("edit_Atten"));
        edit_Atten->setEnabled(true);
        edit_Atten->setGeometry(QRect(94, 262, 140, 30));
        edit_Atten->setReadOnly(true);
        pb_cancel = new QPushButton(widget);
        pb_cancel->setObjectName(QStringLiteral("pb_cancel"));
        pb_cancel->setGeometry(QRect(212, 6, 35, 35));
        pb_cancel->setFocusPolicy(Qt::NoFocus);
        line = new QFrame(widget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(18, 46, 212, 2));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        lblTitle = new QLabel(widget);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));
        lblTitle->setGeometry(QRect(17, 19, 104, 22));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setBold(true);
        font2.setItalic(false);
        font2.setWeight(75);
        lblTitle->setFont(font2);
        lblTitle->setStyleSheet(QLatin1String("#lblTitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}"));
        pb_unitSelect = new SA_Combobox(widget);
        pb_unitSelect->setObjectName(QStringLiteral("pb_unitSelect"));
        pb_unitSelect->setGeometry(QRect(94, 412, 140, 30));
        pb_unitSelect->setFocusPolicy(Qt::WheelFocus);
        pb_unitSelect->setStyleSheet(QStringLiteral(""));
        pb_Manual = new QPushButton(widget);
        buttonGroup = new QButtonGroup(SA_Dialog_AmptSetup);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(pb_Manual);
        pb_Manual->setObjectName(QStringLiteral("pb_Manual"));
        pb_Manual->setGeometry(QRect(165, 217, 69, 30));
        pb_Manual->setFocusPolicy(Qt::NoFocus);
        pb_Manual->setStyleSheet(QStringLiteral(""));
        pb_Manual->setCheckable(true);
        pb_Manual->setChecked(false);
        pb_Auto = new QPushButton(widget);
        buttonGroup->addButton(pb_Auto);
        pb_Auto->setObjectName(QStringLiteral("pb_Auto"));
        pb_Auto->setGeometry(QRect(94, 217, 69, 30));
        pb_Auto->setFont(font2);
        pb_Auto->setFocusPolicy(Qt::NoFocus);
        pb_Auto->setCheckable(true);
        pb_Auto->setChecked(true);
        edit_ZeroRestrainAtten = new SA_LineEdit(widget);
        edit_ZeroRestrainAtten->setObjectName(QStringLiteral("edit_ZeroRestrainAtten"));
        edit_ZeroRestrainAtten->setGeometry(QRect(90, 520, 140, 30));
        edit_ZeroRestrainAtten->setReadOnly(true);
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(14, 520, 71, 30));
        edit_ZeroRestrainPhase = new SA_LineEdit(widget);
        edit_ZeroRestrainPhase->setObjectName(QStringLiteral("edit_ZeroRestrainPhase"));
        edit_ZeroRestrainPhase->setGeometry(QRect(90, 470, 140, 30));
        edit_ZeroRestrainPhase->setReadOnly(true);
        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(14, 470, 66, 30));
        label_6->setFont(font1);
        QWidget::setTabOrder(edit_level, edit_Atten);
        QWidget::setTabOrder(edit_Atten, edit_offset);
        QWidget::setTabOrder(edit_offset, edit_scale);
        QWidget::setTabOrder(edit_scale, pb_unitSelect);

        retranslateUi(SA_Dialog_AmptSetup);

        QMetaObject::connectSlotsByName(SA_Dialog_AmptSetup);
    } // setupUi

    void retranslateUi(QWidget *SA_Dialog_AmptSetup)
    {
        SA_Dialog_AmptSetup->setWindowTitle(QApplication::translate("SA_Dialog_AmptSetup", "Form", Q_NULLPTR));
        SA_Dialog_AmptSetup->setProperty("status", QVariant(QApplication::translate("SA_Dialog_AmptSetup", "night", Q_NULLPTR)));
        pb_Scale_Auto->setText(QApplication::translate("SA_Dialog_AmptSetup", "Auto Scale", Q_NULLPTR));
        label_3->setText(QApplication::translate("SA_Dialog_AmptSetup", "Reference\n"
"Level", Q_NULLPTR));
        lblOffset->setText(QApplication::translate("SA_Dialog_AmptSetup", "External\n"
"Offset", Q_NULLPTR));
        label_4->setText(QApplication::translate("SA_Dialog_AmptSetup", "Scale / Div", Q_NULLPTR));
        lblAtten->setText(QApplication::translate("SA_Dialog_AmptSetup", "Attenuation", Q_NULLPTR));
        lblUnit->setText(QApplication::translate("SA_Dialog_AmptSetup", "Scale Unit", Q_NULLPTR));
        lblPreamp->setText(QApplication::translate("SA_Dialog_AmptSetup", "Preamp", Q_NULLPTR));
        pb_Preamp->setText(QApplication::translate("SA_Dialog_AmptSetup", "On", Q_NULLPTR));
        pb_cancel->setText(QString());
        lblTitle->setText(QApplication::translate("SA_Dialog_AmptSetup", "Amplitude", Q_NULLPTR));
        pb_unitSelect->clear();
        pb_unitSelect->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_AmptSetup", "dBm", Q_NULLPTR)
         << QApplication::translate("SA_Dialog_AmptSetup", "dBV", Q_NULLPTR)
         << QApplication::translate("SA_Dialog_AmptSetup", "dBmV", Q_NULLPTR)
         << QApplication::translate("SA_Dialog_AmptSetup", "dBuV", Q_NULLPTR)
         << QApplication::translate("SA_Dialog_AmptSetup", "V", Q_NULLPTR)
         << QApplication::translate("SA_Dialog_AmptSetup", "W", Q_NULLPTR)
        );
        pb_Manual->setText(QApplication::translate("SA_Dialog_AmptSetup", "Manual", Q_NULLPTR));
        pb_Auto->setText(QApplication::translate("SA_Dialog_AmptSetup", "Auto", Q_NULLPTR));
        label_5->setText(QApplication::translate("SA_Dialog_AmptSetup", "Atten", Q_NULLPTR));
        label_6->setText(QApplication::translate("SA_Dialog_AmptSetup", "Phase", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SA_Dialog_AmptSetup: public Ui_SA_Dialog_AmptSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_AMPTSETUP_H
