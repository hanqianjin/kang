/********************************************************************************
** Form generated from reading UI file 'sa_dialog_doorcontrol.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_DOORCONTROL_H
#define UI_SA_DIALOG_DOORCONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include <sa_lineedit.h>
#include "sa_combobox.h"

QT_BEGIN_NAMESPACE

class Ui_sa_dialog_doorcontrol
{
public:
    QWidget *widget;
    QLabel *label_2;
    QLabel *lblTitle;
    QFrame *line;
    SA_Combobox *DoorControlSourceBox;
    QPushButton *pb_cancel;
    QStackedWidget *subWidget;
    QWidget *page;
    QWidget *Extern_Trigger_Source;
    QPushButton *pb_External_High;
    QLabel *label_3;
    QPushButton *pb_External_Low;
    QLabel *label_10;
    QPushButton *pb_Extern_Sweep_Switch;
    QLabel *label_11;
    QLabel *label_12;
    SA_LineEdit *edit_External_PreventTime;
    QLabel *label_13;
    QLabel *label_14;
    QPushButton *pb_Extern_PreventStatus;
    QLabel *label_22;
    QPushButton *pb_Extern_GateViewStatus;
    SA_LineEdit *edit_External_TriggerDelay;
    SA_LineEdit *edit_External_DoorWidth;
    QPushButton *pb_extern_gatedelay_left;
    QPushButton *pb_extern_gatedelay_right;
    QPushButton *pb_extern_gatelength_right;
    QPushButton *pb_extern_gatelength_left;
    QWidget *RFBurst_Trigger_Source;
    QLabel *label_5;
    QPushButton *pb_RFBurst_Low;
    QLabel *label_15;
    QLabel *label_16;
    QPushButton *pb_RFBurst_High;
    QLabel *label_17;
    QPushButton *pb_RFBurst_PreventStatus;
    QLabel *label_18;
    QLabel *label_19;
    QPushButton *pb_RFBurst_Sweep_Switch;
    SA_LineEdit *edit_RFBurst_PreventTime;
    SA_LineEdit *edit_RFBurst_TriggerLevel;
    QLabel *label_20;
    QLabel *label_24;
    QPushButton *pb_RFBurst_GateViewStatus;
    SA_LineEdit *edit_RFBurst_TriggerDelay;
    SA_LineEdit *edit_RFBurst_DoorWidth;
    QPushButton *pb_RF_gatedelay_left;
    QPushButton *pb_RF_gatedelay_right;
    QPushButton *pb_RF_gatelength_right;
    QPushButton *pb_RF_gatelength_left;
    QWidget *Period_Trigger_Source;
    SA_LineEdit *edit_Period_Period;
    QLabel *label_50;
    QLabel *label_45;
    QLabel *label_44;
    QPushButton *Period_Sweep_Switch;
    QLabel *label_46;
    QLabel *label_54;
    QPushButton *pb_Period_GateViewStatus;
    SA_LineEdit *edit_Period_TriggerDelay;
    SA_LineEdit *edit_Period_DoorWidth;
    QPushButton *pb_Peri_gatedelay_left;
    QPushButton *pb_Peri_gatedelay_right;
    QPushButton *pb_Peri_gatelength_right;
    QPushButton *pb_Peri_gatelength_left;

    void setupUi(QWidget *sa_dialog_doorcontrol)
    {
        if (sa_dialog_doorcontrol->objectName().isEmpty())
            sa_dialog_doorcontrol->setObjectName(QStringLiteral("sa_dialog_doorcontrol"));
        sa_dialog_doorcontrol->resize(251, 646);
        sa_dialog_doorcontrol->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#BitSA[status  =  \"indoor\"] \n"
" #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"\n"
"#BitSA[status  =  \"indoor\"] #spinbox_PerGateDelay,\n"
"#BitSA[status  =  \"indoor\"] #spinbox_PerGateLength,\n"
"#BitSA[status  =  \"indoor\"] #spinbox_ExternGateDelay,\n"
"#BitSA[status  =  \"indoor\"] #spinbox_ExternGateLength,\n"
"#BitSA[status  =  \"indoor\"] #spinbox_RFGateDelay,\n"
"#BitSA[status  =  \"indoor\"] #spinbox_RFGateLength\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#BitSA[status  =  \"indoor\"] #pb_External_Edge:checked,\n"
"#BitSA[status  =  \"indoor\"] #pb_External_Low:checked,\n"
"#BitSA[status  =  \"indoor\"] #pb_RFBurst_Edge:checked,\n"
"#BitSA[status  =  \"indoor\"] #pb_RFBurst_Low:checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/"
                        "fre_checked_left.png);\n"
"}\n"
"\n"
"#BitSA[status  =  \"indoor\"] #pb_External_Edge,\n"
"#BitSA[status  =  \"indoor\"] #pb_External_Low,\n"
"#BitSA[status  =  \"indoor\"] #pb_RFBurst_Edge,\n"
"#BitSA[status  =  \"indoor\"] #pb_RFBurst_Low\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"#BitSA[status  =  \"indoor\"] #pb_External_Level:checked,\n"
"#BitSA[status  =  \"indoor\"] #pb_External_High:checked,\n"
"#BitSA[status  =  \"indoor\"] #pb_RFBurst_Level:checked,\n"
"#BitSA[status  =  \"indoor\"] #pb_RFBurst_High:checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#BitSA[status  =  \"indoor\"] #pb_External_Level,\n"
"#BitSA[status  =  \"indoor\"] #pb_External_High,\n"
"#BitSA[status  =  \"indoor\"] #pb_"
                        "RFBurst_Level,\n"
"#BitSA[status  =  \"indoor\"] #pb_RFBurst_High\n"
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
"#BitSA[status  =  \"indoor\"] \n"
"#widget>#lblTitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#BitSA[status  =  \"indoor\"] \n"
"#pb_cancel\n"
"{\n"
"border-style:flat;\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"\n"
"#BitSA[status  =  \"indoor\"] \n"
"#pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"#BitSA[status  =  \"indoor\"] #pb_extern_gatedelay_left,\n"
"#BitSA[status  =  \"indoor\"] #pb_extern_gatelength_left,\n"
"#BitSA[status  =  \"indoor\"] #pb_RF_gatedelay_left,\n"
"#BitSA[status  =  \"indoor\"] #p"
                        "b_RF_gatelength_left,\n"
"#BitSA[status  =  \"indoor\"] #pb_Peri_gatedelay_left,\n"
"#BitSA[status  =  \"indoor\"] #pb_Peri_gatelength_left\n"
"{\n"
"background-position:right;\n"
"border-style:flat;\n"
"border-radius:0px 3px 3px 0px;\n"
"background-color:rgba(76,76,76,0);\n"
"background-image: url(:/sa/image/btn_collapse_normal.png);\n"
"}\n"
"\n"
"#BitSA[status  =  \"indoor\"] #pb_extern_gatedelay_right,\n"
"#BitSA[status  =  \"indoor\"] #pb_extern_gatelength_right,\n"
"#BitSA[status  =  \"indoor\"] #pb_RF_gatedelay_right,\n"
"#BitSA[status  =  \"indoor\"] #pb_RF_gatelength_right,\n"
"#BitSA[status  =  \"indoor\"] #pb_Peri_gatedelay_right,\n"
"#BitSA[status  =  \"indoor\"] #pb_Peri_gatelength_right\n"
"{\n"
"background-position:left;\n"
"border-style:flat;\n"
"border-radius:0px 3px 3px 0px;\n"
"background-color:rgba(76,76,76,0);\n"
"background-image: url(:/sa/image/btn_expand_normal.png);\n"
"}\n"
"\n"
"#BitSA[status  =  \"indoor\"] \n"
"#line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#Bit"
                        "SA[status  =  \"indoor\"] \n"
"#widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#BitSA[status  =  \"indoor\"] \n"
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
"#BitSA[status  =  \"indoor\"] \n"
"QComboBox:focus\n"
"{\n"
"	background-image: url(:/sa/image/dropdown_click.png);\n"
"}\n"
"\n"
"#BitSA[status  =  \"indoor\"] \n"
"QComboBox::drop-down\n"
" {\n"
"	width: 0px;	\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#BitSA[status  =  \"indoor\"] \n"
"QComboBox QAbstractItemView{\n"
"   font: 75 14px \"Arial\";\n"
"	color:rgba(0, 0, 0, 1);\n"
"	background:rgba(255,255,255,1);\n"
" 	outline:0px;\n"
"	border-style:solid;\n"
"	border-color:rgba(151, 151, 151, 1);\n"
"	border-width:1px;\n"
"}\n"
"\n"
"#BitSA[status  =  \"indoor\"] \n"
"QAbstractItemView::item\n"
"{\n"
"	paddi"
                        "ng-left:8px;\n"
"	width:140px;\n"
"	height:32px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#BitSA[status  =  \"indoor\"] \n"
"QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(240, 179, 29, 1); \n"
"}\n"
"\n"
"#BitSA[status  =  \"indoor\"] SA_LineEdit,\n"
"#BitSA[status  =  \"indoor\"] SA_LineEdit:disable\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#BitSA[status  =  \"indoor\"] \n"
"SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#BitSA[status  =  \"outdoor\"] \n"
" #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"\n"
"#BitSA[status  =  \"outdoor\"] #spinbox_PerGateDelay,\n"
"#BitSA[status  =  \"outdoor\"] #spinbox_PerGateLength,\n"
"#BitSA[status  =  \"outdoor\"] #spinbox_ExternGateDelay,\n"
"#BitSA[status  =  \""
                        "outdoor\"] #spinbox_ExternGateLength,\n"
"#BitSA[status  =  \"outdoor\"] #spinbox_RFGateDelay,\n"
"#BitSA[status  =  \"outdoor\"] #spinbox_RFGateLength\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#BitSA[status  =  \"outdoor\"] #pb_External_Edge:checked,\n"
"#BitSA[status  =  \"outdoor\"] #pb_External_Low:checked,\n"
"#BitSA[status  =  \"outdoor\"] #pb_RFBurst_Edge:checked,\n"
"#BitSA[status  =  \"outdoor\"] #pb_RFBurst_Low:checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"\n"
"#BitSA[status  =  \"outdoor\"] #pb_External_Edge,\n"
"#BitSA[status  =  \"outdoor\"] #pb_External_Low,\n"
"#BitSA[status  =  \"outdoor\"] #pb_RFBurst_Edge,\n"
"#BitSA[status  =  \"outdoor\"] #pb_RFBurst_Low\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-wei"
                        "ght:bold;\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"#BitSA[status  =  \"outdoor\"] #pb_External_Level:checked,\n"
"#BitSA[status  =  \"outdoor\"] #pb_External_High:checked,\n"
"#BitSA[status  =  \"outdoor\"] #pb_RFBurst_Level:checked,\n"
"#BitSA[status  =  \"outdoor\"] #pb_RFBurst_High:checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#BitSA[status  =  \"outdoor\"] #pb_External_Level,\n"
"#BitSA[status  =  \"outdoor\"] #pb_External_High,\n"
"#BitSA[status  =  \"outdoor\"] #pb_RFBurst_Level,\n"
"#BitSA[status  =  \"outdoor\"] #pb_RFBurst_High\n"
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
"\n"
"#BitSA[status"
                        "  =  \"outdoor\"] \n"
"#widget>#lblTitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#BitSA[status  =  \"outdoor\"] \n"
"#pb_cancel\n"
"{\n"
"border-style:flat;\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"\n"
"#BitSA[status  =  \"outdoor\"] \n"
"#pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"#BitSA[status  =  \"outdoor\"] #pb_extern_gatedelay_left,\n"
"#BitSA[status  =  \"outdoor\"] #pb_extern_gatelength_left,\n"
"#BitSA[status  =  \"outdoor\"] #pb_RF_gatedelay_left,\n"
"#BitSA[status  =  \"outdoor\"] #pb_RF_gatelength_left,\n"
"#BitSA[status  =  \"outdoor\"] #pb_Peri_gatedelay_left,\n"
"#BitSA[status  =  \"outdoor\"] #pb_Peri_gatelength_left\n"
"{\n"
"background-position:right;\n"
"border-style:flat;\n"
"border-radius:0px 3px 3px 0px;\n"
"background-color:rgba(76,76,76,0);\n"
"background-image: url(:/sa/image/btn_collapse_no"
                        "rmal.png);\n"
"}\n"
"\n"
"#BitSA[status  =  \"outdoor\"] #pb_extern_gatedelay_right,\n"
"#BitSA[status  =  \"outdoor\"] #pb_extern_gatelength_right,\n"
"#BitSA[status  =  \"outdoor\"] #pb_RF_gatedelay_right,\n"
"#BitSA[status  =  \"outdoor\"] #pb_RF_gatelength_right,\n"
"#BitSA[status  =  \"outdoor\"] #pb_Peri_gatedelay_right,\n"
"#BitSA[status  =  \"outdoor\"] #pb_Peri_gatelength_right\n"
"{\n"
"background-position:left;\n"
"border-style:flat;\n"
"border-radius:0px 3px 3px 0px;\n"
"background-color:rgba(76,76,76,0);\n"
"background-image: url(:/sa/image/btn_expand_normal.png);\n"
"}\n"
"\n"
"#BitSA[status  =  \"outdoor\"] \n"
"#line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"\n"
"#BitSA[status  =  \"outdoor\"] \n"
"#widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#BitSA[status=\"outdoor\"] SA_LineEdit,\n"
"#BitSA[status=\"outdoor\"] SA_LineEdit:disable\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px "
                        "7px 10px ;\n"
"	font: 75 12px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#BitSA[status=\"outdoor\"] SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"#BitSA[status=\"outdoor\"] QComboBox\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(162, 115, 0, 1);\n"
"	padding:8px 23px 7px 10px;\n"
"	combobox-popup: 0;\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/dropdown_normal.png);\n"
"}\n"
"#BitSA[status=\"outdoor\"] QComboBox:focus\n"
"{\n"
"	background-image: url(:/sa/image/dropdown_click.png);\n"
"	\n"
"}\n"
"#BitSA[status=\"outdoor\"] QComboBox::drop-down {\n"
"width: 0px;	border-style:flat;\n"
"}\n"
"\n"
"#BitSA[status=\"outdoor\"] QComboBox QAbstractItemView{\n"
"   font: 75 14px \"Arial\";\n"
"	color:rgba(0, 0, 0, 1);\n"
"	background:rgba(255,255,255,1);\n"
" 	outline:0px;\n"
"	border-style:solid;\n"
"	border-color:rgba(151, 151, 151, 1);\n"
"	border-width:1px;\n"
"}\n"
"#BitSA[status=\"outdoo"
                        "r\"] QAbstractItemView::item{\n"
"	padding-left:8px;\n"
"	width:140px;\n"
"	height:32px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#BitSA[status=\"outdoor\"] QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(240, 179, 29, 1); \n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#BitSA[status  =  \"night\"] \n"
" #widget\n"
"{\n"
"	background-color:rgba(208,182,139,0.9);\n"
"}\n"
"\n"
"#BitSA[status  =  \"night\"] #spinbox_PerGateDelay,\n"
"#BitSA[status  =  \"night\"] #spinbox_PerGateLength,\n"
"#BitSA[status  =  \"night\"] #spinbox_ExternGateDelay,\n"
"#BitSA[status  =  \"night\"] #spinbox_ExternGateLength,\n"
"#BitSA[status  =  \"night\"] #spinbox_RFGateDelay,\n"
"#BitSA[status  =  \"night\"] #spinbox_RFGateLength\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#BitSA[status  =  \"night\"] #pb_External_Edge:checked,\n"
"#BitSA[status  =  \"night\"] #pb_Ext"
                        "ernal_Low:checked,\n"
"#BitSA[status  =  \"night\"] #pb_RFBurst_Edge:checked,\n"
"#BitSA[status  =  \"night\"] #pb_RFBurst_Low:checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"    color:rgba(85,74,56,1);\n"
"	background-image: url(:/sa/image/night/btn_left_click.png);\n"
"}\n"
"\n"
"#BitSA[status  =  \"night\"] #pb_External_Edge,\n"
"#BitSA[status  =  \"night\"] #pb_External_Low,\n"
"#BitSA[status  =  \"night\"] #pb_RFBurst_Edge,\n"
"#BitSA[status  =  \"night\"] #pb_RFBurst_Low\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	padding: 8px 14px 7px 15px;\n"
"	color:rgba(121, 105, 80, 1);\n"
"	background-image: url(:/sa/image/night/btn_left_nor.png);\n"
"}\n"
"\n"
"#BitSA[status  =  \"night\"] #pb_External_Level:checked,\n"
"#BitSA[status  =  \"night\"] #pb_External_High:checked,\n"
"#BitSA[status  =  \"night\"] #pb_RFBurst_Level:checked,\n"
"#BitSA[status  =  \"night\"] #pb_RFBurst_High:checked\n"
"{\n"
"   color:rgba(85,74,56,1);\n"
"	background-image:url(:/sa/image/nig"
                        "ht/btn_right_click.png) ;\n"
"	padding: 8px 5px 7px 6px;\n"
"}\n"
"\n"
"#BitSA[status  =  \"night\"] #pb_External_Level,\n"
"#BitSA[status  =  \"night\"] #pb_External_High,\n"
"#BitSA[status  =  \"night\"] #pb_RFBurst_Level,\n"
"#BitSA[status  =  \"night\"] #pb_RFBurst_High\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	padding: 8px 5px 7px 6px;\n"
"	color:rgba(121, 105, 80, 1);\n"
"	background-image: url(:/sa/image/night/btn_right_nor.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"\n"
"#BitSA[status  =  \"night\"] \n"
"#widget>#lblTitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#BitSA[status  =  \"night\"] \n"
"#pb_cancel\n"
"{\n"
"border-style:flat;\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/night/btn_close_normal.png);\n"
"}\n"
"\n"
"#BitSA[status  =  \"night\"] \n"
"#pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/night/btn_close_click.png);\n"
""
                        "}\n"
"\n"
"#BitSA[status  =  \"night\"] #pb_extern_gatedelay_left,\n"
"#BitSA[status  =  \"night\"] #pb_extern_gatelength_left,\n"
"#BitSA[status  =  \"night\"] #pb_RF_gatedelay_left,\n"
"#BitSA[status  =  \"night\"] #pb_RF_gatelength_left,\n"
"#BitSA[status  =  \"night\"] #pb_Peri_gatedelay_left,\n"
"#BitSA[status  =  \"night\"] #pb_Peri_gatelength_left\n"
"{\n"
"background-position:right;\n"
"border-style:flat;\n"
"border-radius:0px 3px 3px 0px;\n"
"background-color:rgba(0,0,0,0);\n"
"background-image: url(:/sa/image/btn_collapse_normal.png);\n"
"}\n"
"\n"
"#BitSA[status  =  \"night\"] #pb_extern_gatedelay_right,\n"
"#BitSA[status  =  \"night\"] #pb_extern_gatelength_right,\n"
"#BitSA[status  =  \"night\"] #pb_RF_gatedelay_right,\n"
"#BitSA[status  =  \"night\"] #pb_RF_gatelength_right,\n"
"#BitSA[status  =  \"night\"] #pb_Peri_gatedelay_right,\n"
"#BitSA[status  =  \"night\"] #pb_Peri_gatelength_right\n"
"{\n"
"background-position:left;\n"
"border-style:flat;\n"
"border-radius:0px 3px 3px 0px;\n"
"backgroun"
                        "d-color:rgba(76,76,76,0);\n"
"background-image: url(:/sa/image/btn_expand_normal.png);\n"
"}\n"
"\n"
"#BitSA[status  =  \"night\"] \n"
"#line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#BitSA[status  =  \"night\"] \n"
"#widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#BitSA[status  =  \"night\"] SA_LineEdit,\n"
"#BitSA[status  =  \"night\"] SA_LineEdit:disable\n"
"{\n"
"	background: rgba(251,220,167,0.60);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 6px 7px 6px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#BitSA[status  =  \"night\"] SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"\n"
"\n"
"#BitSA[status  =  \"night\"] \n"
"QComboBox\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"    background-color:rgba(251,220,167,0.60);\n"
"    color:rgba(159,98,0,1);\n"
"	padding:8px 23px 7px 10px;\n"
"	combobox-popup: 0;\n"
"	border-style:fl"
                        "at;\n"
"	background-image: url(:/sa/image/night/dropdown_normal.png);\n"
"}\n"
"\n"
"#BitSA[status  =  \"night\"] \n"
"QComboBox:focus\n"
"{\n"
"	background-color:rgba(251,220,167,0.60);\n"
"	background-image: url(:/sa/image/night/dropdown_click.png);\n"
"}\n"
"\n"
"#BitSA[status  =  \"night\"] \n"
"QComboBox::drop-down \n"
"{\n"
"	width: 0px;	\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#BitSA[status  =  \"night\"] \n"
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
"#BitSA[status  =  \"night\"] \n"
"QAbstractItemView::item{\n"
"	padding-left:8px;\n"
"	width:140px;\n"
"	height:32px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#BitSA[status  =  \"night\"] \n"
"QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(159,98,0,1);\n"
"}"));
        widget = new QWidget(sa_dialog_doorcontrol);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 252, 646));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(18, 57, 61, 41));
        lblTitle = new QLabel(widget);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));
        lblTitle->setGeometry(QRect(17, 19, 131, 22));
        lblTitle->setStyleSheet(QLatin1String("#lblTitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}"));
        line = new QFrame(widget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(18, 46, 212, 2));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        DoorControlSourceBox = new SA_Combobox(widget);
        DoorControlSourceBox->setObjectName(QStringLiteral("DoorControlSourceBox"));
        DoorControlSourceBox->setGeometry(QRect(80, 60, 141, 31));
        pb_cancel = new QPushButton(widget);
        pb_cancel->setObjectName(QStringLiteral("pb_cancel"));
        pb_cancel->setGeometry(QRect(212, 6, 35, 35));
        subWidget = new QStackedWidget(widget);
        subWidget->setObjectName(QStringLiteral("subWidget"));
        subWidget->setGeometry(QRect(0, 110, 252, 511));
        subWidget->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"#stackedWidget\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"}\n"
"\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"#stackedWidget\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"#stackedWidget\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        subWidget->addWidget(page);
        Extern_Trigger_Source = new QWidget();
        Extern_Trigger_Source->setObjectName(QStringLiteral("Extern_Trigger_Source"));
        pb_External_High = new QPushButton(Extern_Trigger_Source);
        pb_External_High->setObjectName(QStringLiteral("pb_External_High"));
        pb_External_High->setGeometry(QRect(150, 70, 69, 30));
        pb_External_High->setFocusPolicy(Qt::NoFocus);
        pb_External_High->setCheckable(true);
        pb_External_High->setChecked(false);
        pb_External_High->setAutoExclusive(false);
        label_3 = new QLabel(Extern_Trigger_Source);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 70, 61, 41));
        pb_External_Low = new QPushButton(Extern_Trigger_Source);
        pb_External_Low->setObjectName(QStringLiteral("pb_External_Low"));
        pb_External_Low->setGeometry(QRect(80, 70, 69, 30));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        pb_External_Low->setFont(font);
        pb_External_Low->setFocusPolicy(Qt::NoFocus);
        pb_External_Low->setCheckable(true);
        pb_External_Low->setChecked(true);
        pb_External_Low->setAutoExclusive(false);
        label_10 = new QLabel(Extern_Trigger_Source);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(20, 10, 52, 30));
        pb_Extern_Sweep_Switch = new QPushButton(Extern_Trigger_Source);
        pb_Extern_Sweep_Switch->setObjectName(QStringLiteral("pb_Extern_Sweep_Switch"));
        pb_Extern_Sweep_Switch->setGeometry(QRect(80, 10, 90, 30));
        pb_Extern_Sweep_Switch->setFocusPolicy(Qt::NoFocus);
        pb_Extern_Sweep_Switch->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url("
                        ":/sa/image/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}"));
        pb_Extern_Sweep_Switch->setCheckable(true);
        pb_Extern_Sweep_Switch->setChecked(false);
        label_11 = new QLabel(Extern_Trigger_Source);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(20, 130, 52, 41));
        label_12 = new QLabel(Extern_Trigger_Source);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(20, 190, 52, 41));
        edit_External_PreventTime = new SA_LineEdit(Extern_Trigger_Source);
        edit_External_PreventTime->setObjectName(QStringLiteral("edit_External_PreventTime"));
        edit_External_PreventTime->setGeometry(QRect(80, 370, 140, 30));
        edit_External_PreventTime->setReadOnly(true);
        label_13 = new QLabel(Extern_Trigger_Source);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(20, 310, 52, 41));
        label_14 = new QLabel(Extern_Trigger_Source);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(20, 370, 52, 41));
        pb_Extern_PreventStatus = new QPushButton(Extern_Trigger_Source);
        pb_Extern_PreventStatus->setObjectName(QStringLiteral("pb_Extern_PreventStatus"));
        pb_Extern_PreventStatus->setGeometry(QRect(80, 310, 90, 30));
        pb_Extern_PreventStatus->setFocusPolicy(Qt::NoFocus);
        pb_Extern_PreventStatus->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url("
                        ":/sa/image/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}"));
        pb_Extern_PreventStatus->setCheckable(true);
        pb_Extern_PreventStatus->setChecked(false);
        label_22 = new QLabel(Extern_Trigger_Source);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(20, 250, 61, 41));
        pb_Extern_GateViewStatus = new QPushButton(Extern_Trigger_Source);
        pb_Extern_GateViewStatus->setObjectName(QStringLiteral("pb_Extern_GateViewStatus"));
        pb_Extern_GateViewStatus->setGeometry(QRect(80, 250, 90, 30));
        pb_Extern_GateViewStatus->setFocusPolicy(Qt::NoFocus);
        pb_Extern_GateViewStatus->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url("
                        ":/sa/image/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}"));
        pb_Extern_GateViewStatus->setCheckable(true);
        pb_Extern_GateViewStatus->setChecked(false);
        edit_External_TriggerDelay = new SA_LineEdit(Extern_Trigger_Source);
        edit_External_TriggerDelay->setObjectName(QStringLiteral("edit_External_TriggerDelay"));
        edit_External_TriggerDelay->setGeometry(QRect(100, 130, 90, 30));
        edit_External_DoorWidth = new SA_LineEdit(Extern_Trigger_Source);
        edit_External_DoorWidth->setObjectName(QStringLiteral("edit_External_DoorWidth"));
        edit_External_DoorWidth->setGeometry(QRect(100, 190, 90, 30));
        pb_extern_gatedelay_left = new QPushButton(Extern_Trigger_Source);
        pb_extern_gatedelay_left->setObjectName(QStringLiteral("pb_extern_gatedelay_left"));
        pb_extern_gatedelay_left->setGeometry(QRect(80, 130, 20, 30));
        pb_extern_gatedelay_right = new QPushButton(Extern_Trigger_Source);
        pb_extern_gatedelay_right->setObjectName(QStringLiteral("pb_extern_gatedelay_right"));
        pb_extern_gatedelay_right->setGeometry(QRect(190, 130, 20, 30));
        pb_extern_gatelength_right = new QPushButton(Extern_Trigger_Source);
        pb_extern_gatelength_right->setObjectName(QStringLiteral("pb_extern_gatelength_right"));
        pb_extern_gatelength_right->setGeometry(QRect(190, 190, 20, 30));
        pb_extern_gatelength_left = new QPushButton(Extern_Trigger_Source);
        pb_extern_gatelength_left->setObjectName(QStringLiteral("pb_extern_gatelength_left"));
        pb_extern_gatelength_left->setGeometry(QRect(80, 190, 20, 30));
        subWidget->addWidget(Extern_Trigger_Source);
        RFBurst_Trigger_Source = new QWidget();
        RFBurst_Trigger_Source->setObjectName(QStringLiteral("RFBurst_Trigger_Source"));
        label_5 = new QLabel(RFBurst_Trigger_Source);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 70, 51, 30));
        pb_RFBurst_Low = new QPushButton(RFBurst_Trigger_Source);
        pb_RFBurst_Low->setObjectName(QStringLiteral("pb_RFBurst_Low"));
        pb_RFBurst_Low->setGeometry(QRect(80, 70, 69, 30));
        pb_RFBurst_Low->setFont(font);
        pb_RFBurst_Low->setFocusPolicy(Qt::NoFocus);
        pb_RFBurst_Low->setCheckable(true);
        pb_RFBurst_Low->setChecked(true);
        pb_RFBurst_Low->setAutoExclusive(false);
        label_15 = new QLabel(RFBurst_Trigger_Source);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(20, 10, 52, 30));
        label_16 = new QLabel(RFBurst_Trigger_Source);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(20, 130, 52, 30));
        pb_RFBurst_High = new QPushButton(RFBurst_Trigger_Source);
        pb_RFBurst_High->setObjectName(QStringLiteral("pb_RFBurst_High"));
        pb_RFBurst_High->setGeometry(QRect(150, 70, 69, 30));
        pb_RFBurst_High->setFocusPolicy(Qt::NoFocus);
        pb_RFBurst_High->setCheckable(true);
        pb_RFBurst_High->setChecked(false);
        pb_RFBurst_High->setAutoExclusive(false);
        label_17 = new QLabel(RFBurst_Trigger_Source);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(20, 370, 52, 30));
        pb_RFBurst_PreventStatus = new QPushButton(RFBurst_Trigger_Source);
        pb_RFBurst_PreventStatus->setObjectName(QStringLiteral("pb_RFBurst_PreventStatus"));
        pb_RFBurst_PreventStatus->setGeometry(QRect(80, 310, 90, 30));
        pb_RFBurst_PreventStatus->setFocusPolicy(Qt::NoFocus);
        pb_RFBurst_PreventStatus->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url("
                        ":/sa/image/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}"));
        pb_RFBurst_PreventStatus->setCheckable(true);
        pb_RFBurst_PreventStatus->setChecked(false);
        label_18 = new QLabel(RFBurst_Trigger_Source);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(20, 190, 52, 30));
        label_19 = new QLabel(RFBurst_Trigger_Source);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(20, 310, 52, 30));
        pb_RFBurst_Sweep_Switch = new QPushButton(RFBurst_Trigger_Source);
        pb_RFBurst_Sweep_Switch->setObjectName(QStringLiteral("pb_RFBurst_Sweep_Switch"));
        pb_RFBurst_Sweep_Switch->setGeometry(QRect(80, 10, 90, 30));
        pb_RFBurst_Sweep_Switch->setFocusPolicy(Qt::NoFocus);
        pb_RFBurst_Sweep_Switch->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url("
                        ":/sa/image/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}"));
        pb_RFBurst_Sweep_Switch->setCheckable(true);
        pb_RFBurst_Sweep_Switch->setChecked(false);
        edit_RFBurst_PreventTime = new SA_LineEdit(RFBurst_Trigger_Source);
        edit_RFBurst_PreventTime->setObjectName(QStringLiteral("edit_RFBurst_PreventTime"));
        edit_RFBurst_PreventTime->setGeometry(QRect(80, 370, 140, 30));
        edit_RFBurst_PreventTime->setReadOnly(true);
        edit_RFBurst_TriggerLevel = new SA_LineEdit(RFBurst_Trigger_Source);
        edit_RFBurst_TriggerLevel->setObjectName(QStringLiteral("edit_RFBurst_TriggerLevel"));
        edit_RFBurst_TriggerLevel->setGeometry(QRect(80, 430, 140, 30));
        edit_RFBurst_TriggerLevel->setReadOnly(true);
        label_20 = new QLabel(RFBurst_Trigger_Source);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(20, 430, 52, 30));
        label_24 = new QLabel(RFBurst_Trigger_Source);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(20, 250, 52, 30));
        pb_RFBurst_GateViewStatus = new QPushButton(RFBurst_Trigger_Source);
        pb_RFBurst_GateViewStatus->setObjectName(QStringLiteral("pb_RFBurst_GateViewStatus"));
        pb_RFBurst_GateViewStatus->setGeometry(QRect(80, 250, 90, 30));
        pb_RFBurst_GateViewStatus->setFocusPolicy(Qt::NoFocus);
        pb_RFBurst_GateViewStatus->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url("
                        ":/sa/image/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}"));
        pb_RFBurst_GateViewStatus->setCheckable(true);
        pb_RFBurst_GateViewStatus->setChecked(false);
        edit_RFBurst_TriggerDelay = new SA_LineEdit(RFBurst_Trigger_Source);
        edit_RFBurst_TriggerDelay->setObjectName(QStringLiteral("edit_RFBurst_TriggerDelay"));
        edit_RFBurst_TriggerDelay->setGeometry(QRect(100, 130, 90, 30));
        edit_RFBurst_DoorWidth = new SA_LineEdit(RFBurst_Trigger_Source);
        edit_RFBurst_DoorWidth->setObjectName(QStringLiteral("edit_RFBurst_DoorWidth"));
        edit_RFBurst_DoorWidth->setGeometry(QRect(100, 190, 90, 30));
        pb_RF_gatedelay_left = new QPushButton(RFBurst_Trigger_Source);
        pb_RF_gatedelay_left->setObjectName(QStringLiteral("pb_RF_gatedelay_left"));
        pb_RF_gatedelay_left->setGeometry(QRect(80, 130, 20, 30));
        pb_RF_gatedelay_right = new QPushButton(RFBurst_Trigger_Source);
        pb_RF_gatedelay_right->setObjectName(QStringLiteral("pb_RF_gatedelay_right"));
        pb_RF_gatedelay_right->setGeometry(QRect(190, 130, 20, 30));
        pb_RF_gatelength_right = new QPushButton(RFBurst_Trigger_Source);
        pb_RF_gatelength_right->setObjectName(QStringLiteral("pb_RF_gatelength_right"));
        pb_RF_gatelength_right->setGeometry(QRect(190, 190, 20, 30));
        pb_RF_gatelength_left = new QPushButton(RFBurst_Trigger_Source);
        pb_RF_gatelength_left->setObjectName(QStringLiteral("pb_RF_gatelength_left"));
        pb_RF_gatelength_left->setGeometry(QRect(80, 190, 20, 30));
        subWidget->addWidget(RFBurst_Trigger_Source);
        Period_Trigger_Source = new QWidget();
        Period_Trigger_Source->setObjectName(QStringLiteral("Period_Trigger_Source"));
        edit_Period_Period = new SA_LineEdit(Period_Trigger_Source);
        edit_Period_Period->setObjectName(QStringLiteral("edit_Period_Period"));
        edit_Period_Period->setGeometry(QRect(80, 250, 140, 30));
        edit_Period_Period->setReadOnly(true);
        label_50 = new QLabel(Period_Trigger_Source);
        label_50->setObjectName(QStringLiteral("label_50"));
        label_50->setGeometry(QRect(20, 250, 71, 30));
        label_45 = new QLabel(Period_Trigger_Source);
        label_45->setObjectName(QStringLiteral("label_45"));
        label_45->setGeometry(QRect(20, 70, 61, 30));
        label_44 = new QLabel(Period_Trigger_Source);
        label_44->setObjectName(QStringLiteral("label_44"));
        label_44->setGeometry(QRect(20, 10, 71, 30));
        Period_Sweep_Switch = new QPushButton(Period_Trigger_Source);
        Period_Sweep_Switch->setObjectName(QStringLiteral("Period_Sweep_Switch"));
        Period_Sweep_Switch->setGeometry(QRect(80, 10, 90, 30));
        Period_Sweep_Switch->setFocusPolicy(Qt::NoFocus);
        Period_Sweep_Switch->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url("
                        ":/sa/image/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}"));
        Period_Sweep_Switch->setCheckable(true);
        Period_Sweep_Switch->setChecked(false);
        label_46 = new QLabel(Period_Trigger_Source);
        label_46->setObjectName(QStringLiteral("label_46"));
        label_46->setGeometry(QRect(20, 130, 52, 30));
        label_54 = new QLabel(Period_Trigger_Source);
        label_54->setObjectName(QStringLiteral("label_54"));
        label_54->setGeometry(QRect(20, 190, 81, 30));
        pb_Period_GateViewStatus = new QPushButton(Period_Trigger_Source);
        pb_Period_GateViewStatus->setObjectName(QStringLiteral("pb_Period_GateViewStatus"));
        pb_Period_GateViewStatus->setGeometry(QRect(80, 190, 90, 30));
        pb_Period_GateViewStatus->setFocusPolicy(Qt::NoFocus);
        pb_Period_GateViewStatus->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"indoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url("
                        ":/sa/image/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"outdoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}\n"
"#sa_dialog_doorcontrol[status  =  \"night\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}"));
        pb_Period_GateViewStatus->setCheckable(true);
        pb_Period_GateViewStatus->setChecked(false);
        edit_Period_TriggerDelay = new SA_LineEdit(Period_Trigger_Source);
        edit_Period_TriggerDelay->setObjectName(QStringLiteral("edit_Period_TriggerDelay"));
        edit_Period_TriggerDelay->setGeometry(QRect(100, 70, 90, 30));
        edit_Period_DoorWidth = new SA_LineEdit(Period_Trigger_Source);
        edit_Period_DoorWidth->setObjectName(QStringLiteral("edit_Period_DoorWidth"));
        edit_Period_DoorWidth->setGeometry(QRect(100, 130, 90, 30));
        pb_Peri_gatedelay_left = new QPushButton(Period_Trigger_Source);
        pb_Peri_gatedelay_left->setObjectName(QStringLiteral("pb_Peri_gatedelay_left"));
        pb_Peri_gatedelay_left->setGeometry(QRect(80, 70, 20, 30));
        pb_Peri_gatedelay_right = new QPushButton(Period_Trigger_Source);
        pb_Peri_gatedelay_right->setObjectName(QStringLiteral("pb_Peri_gatedelay_right"));
        pb_Peri_gatedelay_right->setGeometry(QRect(190, 70, 20, 30));
        pb_Peri_gatelength_right = new QPushButton(Period_Trigger_Source);
        pb_Peri_gatelength_right->setObjectName(QStringLiteral("pb_Peri_gatelength_right"));
        pb_Peri_gatelength_right->setGeometry(QRect(190, 130, 20, 30));
        pb_Peri_gatelength_left = new QPushButton(Period_Trigger_Source);
        pb_Peri_gatelength_left->setObjectName(QStringLiteral("pb_Peri_gatelength_left"));
        pb_Peri_gatelength_left->setGeometry(QRect(80, 130, 20, 30));
        subWidget->addWidget(Period_Trigger_Source);

        retranslateUi(sa_dialog_doorcontrol);

        subWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(sa_dialog_doorcontrol);
    } // setupUi

    void retranslateUi(QWidget *sa_dialog_doorcontrol)
    {
        sa_dialog_doorcontrol->setWindowTitle(QApplication::translate("sa_dialog_doorcontrol", "Form", Q_NULLPTR));
        sa_dialog_doorcontrol->setProperty("status", QVariant(QApplication::translate("sa_dialog_doorcontrol", "indoor", Q_NULLPTR)));
        label_2->setText(QApplication::translate("sa_dialog_doorcontrol", "Gate\n"
"Source", Q_NULLPTR));
        lblTitle->setText(QApplication::translate("sa_dialog_doorcontrol", "Gate Sweep", Q_NULLPTR));
        DoorControlSourceBox->clear();
        DoorControlSourceBox->insertItems(0, QStringList()
         << QApplication::translate("sa_dialog_doorcontrol", "Periodic", Q_NULLPTR)
         << QApplication::translate("sa_dialog_doorcontrol", "External", Q_NULLPTR)
        );
        pb_cancel->setText(QString());
        pb_External_High->setText(QApplication::translate("sa_dialog_doorcontrol", "Pos", Q_NULLPTR));
        label_3->setText(QApplication::translate("sa_dialog_doorcontrol", "Control\n"
"Value", Q_NULLPTR));
        pb_External_Low->setText(QApplication::translate("sa_dialog_doorcontrol", "Neg", Q_NULLPTR));
        label_10->setText(QApplication::translate("sa_dialog_doorcontrol", "Gate", Q_NULLPTR));
        pb_Extern_Sweep_Switch->setText(QApplication::translate("sa_dialog_doorcontrol", "Off", Q_NULLPTR));
        label_11->setText(QApplication::translate("sa_dialog_doorcontrol", "Gate\n"
"Delay", Q_NULLPTR));
        label_12->setText(QApplication::translate("sa_dialog_doorcontrol", "Gate\n"
"Length", Q_NULLPTR));
        edit_External_PreventTime->setText(QApplication::translate("sa_dialog_doorcontrol", "0 s", Q_NULLPTR));
        label_13->setText(QApplication::translate("sa_dialog_doorcontrol", "Holdoff\n"
"Status", Q_NULLPTR));
        label_14->setText(QApplication::translate("sa_dialog_doorcontrol", "Holdoff\n"
"Time", Q_NULLPTR));
        pb_Extern_PreventStatus->setText(QApplication::translate("sa_dialog_doorcontrol", "Off", Q_NULLPTR));
        label_22->setText(QApplication::translate("sa_dialog_doorcontrol", "Gate \n"
"View", Q_NULLPTR));
        pb_Extern_GateViewStatus->setText(QApplication::translate("sa_dialog_doorcontrol", "Off", Q_NULLPTR));
        pb_extern_gatedelay_left->setText(QString());
        pb_extern_gatedelay_right->setText(QString());
        pb_extern_gatelength_right->setText(QString());
        pb_extern_gatelength_left->setText(QString());
        label_5->setText(QApplication::translate("sa_dialog_doorcontrol", "Control\n"
"Value", Q_NULLPTR));
        pb_RFBurst_Low->setText(QApplication::translate("sa_dialog_doorcontrol", "Neg", Q_NULLPTR));
        label_15->setText(QApplication::translate("sa_dialog_doorcontrol", "Gate", Q_NULLPTR));
        label_16->setText(QApplication::translate("sa_dialog_doorcontrol", "Gate\n"
"Delay", Q_NULLPTR));
        pb_RFBurst_High->setText(QApplication::translate("sa_dialog_doorcontrol", "Pos", Q_NULLPTR));
        label_17->setText(QApplication::translate("sa_dialog_doorcontrol", "Holdoff\n"
"Time", Q_NULLPTR));
        pb_RFBurst_PreventStatus->setText(QApplication::translate("sa_dialog_doorcontrol", "Off", Q_NULLPTR));
        label_18->setText(QApplication::translate("sa_dialog_doorcontrol", "Gate\n"
"Length", Q_NULLPTR));
        label_19->setText(QApplication::translate("sa_dialog_doorcontrol", "Holdoff\n"
"Status", Q_NULLPTR));
        pb_RFBurst_Sweep_Switch->setText(QApplication::translate("sa_dialog_doorcontrol", "Off", Q_NULLPTR));
        edit_RFBurst_PreventTime->setText(QApplication::translate("sa_dialog_doorcontrol", "0 s", Q_NULLPTR));
        edit_RFBurst_TriggerLevel->setText(QApplication::translate("sa_dialog_doorcontrol", "0 dBm", Q_NULLPTR));
        label_20->setText(QApplication::translate("sa_dialog_doorcontrol", "Trigger\n"
"Level", Q_NULLPTR));
        label_24->setText(QApplication::translate("sa_dialog_doorcontrol", "Gate\n"
"View", Q_NULLPTR));
        pb_RFBurst_GateViewStatus->setText(QApplication::translate("sa_dialog_doorcontrol", "Off", Q_NULLPTR));
        pb_RF_gatedelay_left->setText(QString());
        pb_RF_gatedelay_right->setText(QString());
        pb_RF_gatelength_right->setText(QString());
        pb_RF_gatelength_left->setText(QString());
        edit_Period_Period->setText(QApplication::translate("sa_dialog_doorcontrol", "0 s", Q_NULLPTR));
        label_50->setText(QApplication::translate("sa_dialog_doorcontrol", "Period", Q_NULLPTR));
        label_45->setText(QApplication::translate("sa_dialog_doorcontrol", "Gate\n"
"Delay", Q_NULLPTR));
        label_44->setText(QApplication::translate("sa_dialog_doorcontrol", "Gate", Q_NULLPTR));
        Period_Sweep_Switch->setText(QApplication::translate("sa_dialog_doorcontrol", "Off", Q_NULLPTR));
        label_46->setText(QApplication::translate("sa_dialog_doorcontrol", "Gate \n"
"Length", Q_NULLPTR));
        label_54->setText(QApplication::translate("sa_dialog_doorcontrol", "Gate \n"
"View", Q_NULLPTR));
        pb_Period_GateViewStatus->setText(QApplication::translate("sa_dialog_doorcontrol", "Off", Q_NULLPTR));
        pb_Peri_gatedelay_left->setText(QString());
        pb_Peri_gatedelay_right->setText(QString());
        pb_Peri_gatelength_right->setText(QString());
        pb_Peri_gatelength_left->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class sa_dialog_doorcontrol: public Ui_sa_dialog_doorcontrol {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_DOORCONTROL_H
