/********************************************************************************
** Form generated from reading UI file 'sa_dialog_triggersetup.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_TRIGGERSETUP_H
#define UI_SA_DIALOG_TRIGGERSETUP_H

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

class Ui_SA_Dialog_TriggerSetup
{
public:
    QWidget *widget;
    QLabel *label_2;
    QPushButton *pb_cancel;
    QFrame *line;
    QLabel *lblTitle;
    SA_Combobox *TriggerTypeBox;
    QStackedWidget *subWidget;
    QWidget *FreeRunControl;
    QWidget *ExternalPage;
    QLabel *label_9;
    SA_LineEdit *edit_External_DelayValue;
    SA_LineEdit *edit_External_level;
    QPushButton *pb_External_DelayOn;
    QLabel *label_10;
    QPushButton *pb_External_Neg;
    QLabel *label_11;
    QLabel *label_12;
    QPushButton *pb_External_Pos;
    QWidget *VideoControl;
    SA_LineEdit *edit_Video_DelayValue;
    QLabel *label;
    SA_LineEdit *edit_Video_level;
    QPushButton *pb_Video_Neg;
    QPushButton *pb_Video_DelayOn;
    QLabel *label_7;
    QLabel *label_5;
    QLabel *label_3;
    QPushButton *pb_Video_Pos;
    QWidget *PeriodicTimerControl;
    SA_LineEdit *edit_Peri_time;
    QLabel *label_4;
    QLabel *label_6;
    SA_LineEdit *edit_PeriTime_DelayValue;
    QLabel *label_8;
    QPushButton *pb_PeriTime_DelayOn;
    QWidget *RFBurst;
    QPushButton *pb_RFBurst_Neg;
    SA_LineEdit *edit_RFBurst_level;
    SA_LineEdit *edit_RFBurst_DelayValue;
    QLabel *label_13;
    QPushButton *pb_RFBurst_DelayOn;
    QLabel *label_14;
    QLabel *label_15;
    QPushButton *pb_RFBurst_Pos;
    QLabel *label_16;
    QWidget *GPS;
    QLabel *label_warning;
    QPushButton *pb_Internal;
    QPushButton *pb_External_Rise;
    QPushButton *pb_Trigger_Time;
    QPushButton *pb_Video;
    QPushButton *pb_External_Fall;
    QPushButton *pb_GPS;
    QPushButton *pb_FreeRun;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *SA_Dialog_TriggerSetup)
    {
        if (SA_Dialog_TriggerSetup->objectName().isEmpty())
            SA_Dialog_TriggerSetup->setObjectName(QStringLiteral("SA_Dialog_TriggerSetup"));
        SA_Dialog_TriggerSetup->resize(251, 646);
        SA_Dialog_TriggerSetup->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
" #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"#widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"#widget>#lblTitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"#pb_cancel\n"
"{\n"
"border-style:flat;\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"#pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"#line\n"
"{\n"
""
                        "	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
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
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QComboBox:focus\n"
"{\n"
"	background-image: url(:/sa/image/dropdown_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QComboBox::drop-down\n"
" {\n"
"	width: 0px;	\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
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
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QAbstractItemView::item\n"
""
                        "{\n"
"	padding-left:8px;\n"
"	width:140px;\n"
"	height:32px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(240, 179, 29, 1); \n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] SA_LineEdit,\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] SA_LineEdit:disable\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
" #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"#widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\""
                        ";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"#widget>#lblTitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"#pb_cancel\n"
"{\n"
"border-style:flat;\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"#pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"#line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
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
"#SA_"
                        "Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QComboBox:focus\n"
"{\n"
"	background-image: url(:/sa/image/dropdown_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QComboBox::drop-down\n"
" {\n"
"	width: 0px;	\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
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
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QAbstractItemView::item\n"
"{\n"
"	padding-left:8px;\n"
"	width:140px;\n"
"	height:32px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(240, 179, 29, 1); \n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] SA_LineEdit,\n"
"#SA_Dialog_TriggerSetup[status  =  \"ou"
                        "tdoor\"] SA_LineEdit:disable\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
" #widget\n"
"{\n"
"	background-color:rgba(208,182,139,0.9);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"#widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"#widget>#lblTitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"#pb_cancel\n"
"{\n"
"border-style:flat;\n"
"background-color:rgba("
                        "0,0,0,0);\n"
"border-image: url(:/sa/image/night/btn_close_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"#pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/night/btn_close_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"#line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QComboBox\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	background-color: rgba(251,220,167,0.60);\n"
"	color:rgba(159,98,0,1);\n"
"	padding:8px 23px 7px 10px;\n"
"	combobox-popup: 0;\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/night/dropdown_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QComboBox:focus\n"
"{\n"
"	background-image: url(:/sa/image/night/dropdown_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QComboBox::drop-down\n"
" {\n"
"	width: 0px;	\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetu"
                        "p[status  =  \"night\"] \n"
"QComboBox QAbstractItemView{\n"
"   font: 75 14px \"Arial\";\n"
"	color:rgba(0, 0, 0, 1);\n"
"	background-color: #FBDBA7;;\n"
" 	outline:0px;\n"
"	border-style:solid;\n"
"	border-color:rgba(151, 151, 151, 1);\n"
"	border-width:1px;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QAbstractItemView::item\n"
"{\n"
"	padding-left:8px;\n"
"	width:140px;\n"
"	height:32px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(159,98,0,1);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] SA_LineEdit,\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] SA_LineEdit:disable\n"
"{\n"
"	background-color: rgba(251,220,167,0.60);\n"
"	color:rgba(159,98,0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px sol"
                        "id rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}"));
        widget = new QWidget(SA_Dialog_TriggerSetup);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 252, 646));
        widget->setStyleSheet(QStringLiteral(""));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(18, 67, 61, 30));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        label_2->setFont(font);
        pb_cancel = new QPushButton(widget);
        pb_cancel->setObjectName(QStringLiteral("pb_cancel"));
        pb_cancel->setGeometry(QRect(212, 6, 35, 35));
        line = new QFrame(widget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(18, 46, 212, 2));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        lblTitle = new QLabel(widget);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));
        lblTitle->setGeometry(QRect(17, 19, 102, 22));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        lblTitle->setFont(font1);
        lblTitle->setStyleSheet(QLatin1String("#lblTitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}"));
        TriggerTypeBox = new SA_Combobox(widget);
        TriggerTypeBox->setObjectName(QStringLiteral("TriggerTypeBox"));
        TriggerTypeBox->setGeometry(QRect(94, 67, 140, 30));
        subWidget = new QStackedWidget(widget);
        subWidget->setObjectName(QStringLiteral("subWidget"));
        subWidget->setGeometry(QRect(0, 117, 252, 251));
        subWidget->setStyleSheet(QLatin1String("\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] SA_LineEdit,\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] SA_LineEdit:disable\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] SA_LineEdit,\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] SA_LineEdit:disable\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px s"
                        "olid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] SA_LineEdit,\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] SA_LineEdit:disable\n"
"{\n"
"	background-color: rgba(251,220,167,0.60);\n"
"	color:rgba(159,98,0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}"));
        FreeRunControl = new QWidget();
        FreeRunControl->setObjectName(QStringLiteral("FreeRunControl"));
        subWidget->addWidget(FreeRunControl);
        ExternalPage = new QWidget();
        ExternalPage->setObjectName(QStringLiteral("ExternalPage"));
        label_9 = new QLabel(ExternalPage);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(18, 150, 54, 45));
        edit_External_DelayValue = new SA_LineEdit(ExternalPage);
        edit_External_DelayValue->setObjectName(QStringLiteral("edit_External_DelayValue"));
        edit_External_DelayValue->setGeometry(QRect(94, 150, 140, 30));
        edit_External_DelayValue->setReadOnly(true);
        edit_External_level = new SA_LineEdit(ExternalPage);
        edit_External_level->setObjectName(QStringLiteral("edit_External_level"));
        edit_External_level->setGeometry(QRect(94, 0, 140, 30));
        edit_External_level->setReadOnly(true);
        pb_External_DelayOn = new QPushButton(ExternalPage);
        pb_External_DelayOn->setObjectName(QStringLiteral("pb_External_DelayOn"));
        pb_External_DelayOn->setGeometry(QRect(94, 100, 90, 30));
        pb_External_DelayOn->setFocusPolicy(Qt::NoFocus);
        pb_External_DelayOn->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image:"
                        " url(:/sa/image/toggle_on.png);\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(121,106,80,1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}"));
        pb_External_DelayOn->setCheckable(true);
        pb_External_DelayOn->setChecked(false);
        label_10 = new QLabel(ExternalPage);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(18, 100, 52, 30));
        pb_External_Neg = new QPushButton(ExternalPage);
        pb_External_Neg->setObjectName(QStringLiteral("pb_External_Neg"));
        pb_External_Neg->setGeometry(QRect(164, 50, 68, 30));
        pb_External_Neg->setFocusPolicy(Qt::NoFocus);
        pb_External_Neg->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton:checked{\n"
"background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"color:rgba(87, 87, 87, 1);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"\n"
"color:rgba(123, 123, 123, 1);\n"
"background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton:checked{\n"
"background-color:transparent;\n"
"	background-image: url(:/sa/im"
                        "age/fre_checked_right.png);\n"
"	background-position:right;\n"
"color:rgba(87, 87, 87, 1);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"\n"
"color:rgba(123, 123, 123, 1);\n"
"background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton:checked{\n"
"	background-color:transparent;\n"
"	border-image: url(:/sa/image/night/btn_right_click.png);\n"
"	color:rgba(85,74,56,1);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton:!checked\n"
"{\n"
"	color:rgba(121,106,81,1);\n"
"	background-color:transparent;\n"
"	border-image: url(:/sa/image/night/btn_right_nor.png);\n"
"}"));
        pb_External_Neg->setCheckable(true);
        pb_External_Neg->setChecked(false);
        pb_External_Neg->setAutoExclusive(true);
        pb_External_Neg->setFlat(true);
        label_11 = new QLabel(ExternalPage);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(18, 50, 72, 30));
        label_12 = new QLabel(ExternalPage);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(18, 0, 66, 30));
        label_12->setFont(font);
        pb_External_Pos = new QPushButton(ExternalPage);
        pb_External_Pos->setObjectName(QStringLiteral("pb_External_Pos"));
        pb_External_Pos->setGeometry(QRect(94, 50, 68, 30));
        pb_External_Pos->setFont(font1);
        pb_External_Pos->setFocusPolicy(Qt::NoFocus);
        pb_External_Pos->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton:checked{\n"
"	color:rgba(87, 87, 87, 1);\n"
"	background-color:transparent;\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"color:rgba(123, 123, 123, 1);\n"
"background-color:transparent;\n"
"padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton:checked{\n"
"	color:rgba(87, 87, 87, 1);\n"
"	background-color:transparent;\n"
"	padding: 8px "
                        "14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"color:rgba(123, 123, 123, 1);\n"
"background-color:transparent;\n"
"padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton:checked\n"
"{\n"
"	color:rgba(85,74,56,1);\n"
"	background-color:transparent;\n"
"	padding: 8px 14px 7px 15px;\n"
"	border-image: url(:/sa/image/night/btn_left_click.png);\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton:!checked\n"
"{\n"
"	color:rgba(121,106,81,1);\n"
"	background-color:transparent;\n"
"	padding: 8px 14px 7px 15px;\n"
"	border-image: url(:/sa/image/night/btn_left_nor.png);\n"
"}\n"
""));
        pb_External_Pos->setCheckable(true);
        pb_External_Pos->setChecked(true);
        pb_External_Pos->setAutoExclusive(true);
        pb_External_Pos->setFlat(true);
        subWidget->addWidget(ExternalPage);
        VideoControl = new QWidget();
        VideoControl->setObjectName(QStringLiteral("VideoControl"));
        edit_Video_DelayValue = new SA_LineEdit(VideoControl);
        edit_Video_DelayValue->setObjectName(QStringLiteral("edit_Video_DelayValue"));
        edit_Video_DelayValue->setGeometry(QRect(94, 150, 140, 30));
        edit_Video_DelayValue->setReadOnly(true);
        label = new QLabel(VideoControl);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(18, 150, 54, 45));
        edit_Video_level = new SA_LineEdit(VideoControl);
        edit_Video_level->setObjectName(QStringLiteral("edit_Video_level"));
        edit_Video_level->setGeometry(QRect(94, 0, 140, 30));
        edit_Video_level->setReadOnly(true);
        pb_Video_Neg = new QPushButton(VideoControl);
        buttonGroup = new QButtonGroup(SA_Dialog_TriggerSetup);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(pb_Video_Neg);
        pb_Video_Neg->setObjectName(QStringLiteral("pb_Video_Neg"));
        pb_Video_Neg->setGeometry(QRect(164, 50, 68, 30));
        pb_Video_Neg->setFocusPolicy(Qt::NoFocus);
        pb_Video_Neg->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton:checked{\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"color:rgba(87, 87, 87, 1);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"\n"
"color:rgba(123, 123, 123, 1);\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"background-color:transparent;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton:checked{\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	"
                        "background-position:right;\n"
"color:rgba(87, 87, 87, 1);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"color:rgba(123, 123, 123, 1);\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"background-color:transparent;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton:checked{\n"
"	background-color:transparent;\n"
"	border-image: url(:/sa/image/night/btn_right_click.png);\n"
"	color:rgba(85,74,56,1);\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton\n"
"{\n"
"	color:rgba(121,106,81,1);\n"
"	background-color:transparent;\n"
"	border-image: url(:/sa/image/night/btn_right_nor.png);\n"
"}"));
        pb_Video_Neg->setCheckable(true);
        pb_Video_Neg->setChecked(false);
        pb_Video_Neg->setAutoExclusive(true);
        pb_Video_Neg->setFlat(true);
        pb_Video_DelayOn = new QPushButton(VideoControl);
        pb_Video_DelayOn->setObjectName(QStringLiteral("pb_Video_DelayOn"));
        pb_Video_DelayOn->setGeometry(QRect(94, 100, 90, 30));
        pb_Video_DelayOn->setFocusPolicy(Qt::NoFocus);
        pb_Video_DelayOn->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image:"
                        " url(:/sa/image/toggle_on.png);\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(121,106,80,1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}"));
        pb_Video_DelayOn->setCheckable(true);
        pb_Video_DelayOn->setChecked(false);
        label_7 = new QLabel(VideoControl);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(18, 100, 52, 30));
        label_5 = new QLabel(VideoControl);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(18, 50, 72, 30));
        label_3 = new QLabel(VideoControl);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(18, 0, 66, 30));
        label_3->setFont(font);
        pb_Video_Pos = new QPushButton(VideoControl);
        buttonGroup->addButton(pb_Video_Pos);
        pb_Video_Pos->setObjectName(QStringLiteral("pb_Video_Pos"));
        pb_Video_Pos->setGeometry(QRect(94, 50, 68, 30));
        pb_Video_Pos->setFont(font1);
        pb_Video_Pos->setFocusPolicy(Qt::NoFocus);
        pb_Video_Pos->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton:checked{\n"
"	color:rgba(87, 87, 87, 1);\n"
"	background-color:transparent;\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"color:rgba(123, 123, 123, 1);\n"
"background-color:transparent;\n"
"padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton:checked{\n"
"	color:rgba(87, 87, 87, 1);\n"
"	background-color:transparent;\n"
"	padding: 8px "
                        "14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"color:rgba(123, 123, 123, 1);\n"
"background-color:transparent;\n"
"padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton:checked{\n"
"	color:rgba(85,74,56,1);\n"
"	background-color:transparent;\n"
"	padding: 8px 14px 7px 15px;\n"
"	border-image: url(:/sa/image/night/btn_left_click.png);\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton:!checked\n"
"{\n"
"	color:rgba(121,106,81,1);	\n"
"	background-color:transparent;\n"
"	padding: 8px 14px 7px 15px;\n"
"	border-image:url(:/sa/image/night/btn_left_nor.png);\n"
"}\n"
""));
        pb_Video_Pos->setCheckable(true);
        pb_Video_Pos->setChecked(true);
        pb_Video_Pos->setAutoExclusive(true);
        pb_Video_Pos->setFlat(true);
        subWidget->addWidget(VideoControl);
        PeriodicTimerControl = new QWidget();
        PeriodicTimerControl->setObjectName(QStringLiteral("PeriodicTimerControl"));
        edit_Peri_time = new SA_LineEdit(PeriodicTimerControl);
        edit_Peri_time->setObjectName(QStringLiteral("edit_Peri_time"));
        edit_Peri_time->setGeometry(QRect(94, 0, 140, 30));
        edit_Peri_time->setReadOnly(true);
        label_4 = new QLabel(PeriodicTimerControl);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(18, 0, 66, 30));
        label_4->setFont(font);
        label_6 = new QLabel(PeriodicTimerControl);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(18, 100, 54, 45));
        edit_PeriTime_DelayValue = new SA_LineEdit(PeriodicTimerControl);
        edit_PeriTime_DelayValue->setObjectName(QStringLiteral("edit_PeriTime_DelayValue"));
        edit_PeriTime_DelayValue->setGeometry(QRect(94, 100, 140, 30));
        edit_PeriTime_DelayValue->setReadOnly(true);
        label_8 = new QLabel(PeriodicTimerControl);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(18, 50, 52, 30));
        pb_PeriTime_DelayOn = new QPushButton(PeriodicTimerControl);
        pb_PeriTime_DelayOn->setObjectName(QStringLiteral("pb_PeriTime_DelayOn"));
        pb_PeriTime_DelayOn->setGeometry(QRect(94, 50, 90, 30));
        pb_PeriTime_DelayOn->setFocusPolicy(Qt::NoFocus);
        pb_PeriTime_DelayOn->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image:"
                        " url(:/sa/image/toggle_on.png);\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(121,106,80,1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}"));
        pb_PeriTime_DelayOn->setCheckable(true);
        pb_PeriTime_DelayOn->setChecked(false);
        subWidget->addWidget(PeriodicTimerControl);
        RFBurst = new QWidget();
        RFBurst->setObjectName(QStringLiteral("RFBurst"));
        pb_RFBurst_Neg = new QPushButton(RFBurst);
        pb_RFBurst_Neg->setObjectName(QStringLiteral("pb_RFBurst_Neg"));
        pb_RFBurst_Neg->setGeometry(QRect(164, 50, 68, 30));
        pb_RFBurst_Neg->setFocusPolicy(Qt::NoFocus);
        pb_RFBurst_Neg->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton:checked{\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"color:rgba(87, 87, 87, 1);\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"color:rgba(123, 123, 123, 1);\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-position:right;\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton:checked{\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	back"
                        "ground-position:right;\n"
"color:rgba(87, 87, 87, 1);\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"color:rgba(123, 123, 123, 1);\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-position:right;\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton:checked{\n"
"	background-image: url(:/sa/image/night/btn_right_click.png);\n"
"	color:rgba(85,74,56,1);\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton:!checked\n"
"{\n"
"	color:rgba(121,106,81,1);\n"
"	border-image:url(:/sa/image/night/btn_right_nor.png);\n"
"	background-color:transparent;\n"
"}"));
        pb_RFBurst_Neg->setCheckable(true);
        pb_RFBurst_Neg->setChecked(false);
        pb_RFBurst_Neg->setAutoExclusive(true);
        pb_RFBurst_Neg->setFlat(true);
        edit_RFBurst_level = new SA_LineEdit(RFBurst);
        edit_RFBurst_level->setObjectName(QStringLiteral("edit_RFBurst_level"));
        edit_RFBurst_level->setGeometry(QRect(94, 0, 140, 30));
        edit_RFBurst_level->setReadOnly(true);
        edit_RFBurst_DelayValue = new SA_LineEdit(RFBurst);
        edit_RFBurst_DelayValue->setObjectName(QStringLiteral("edit_RFBurst_DelayValue"));
        edit_RFBurst_DelayValue->setGeometry(QRect(94, 150, 140, 30));
        edit_RFBurst_DelayValue->setReadOnly(true);
        label_13 = new QLabel(RFBurst);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(18, 50, 72, 30));
        pb_RFBurst_DelayOn = new QPushButton(RFBurst);
        pb_RFBurst_DelayOn->setObjectName(QStringLiteral("pb_RFBurst_DelayOn"));
        pb_RFBurst_DelayOn->setGeometry(QRect(94, 100, 90, 30));
        pb_RFBurst_DelayOn->setFocusPolicy(Qt::NoFocus);
        pb_RFBurst_DelayOn->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image:"
                        " url(:/sa/image/toggle_on.png);\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(121,106,81,1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}"));
        pb_RFBurst_DelayOn->setCheckable(true);
        pb_RFBurst_DelayOn->setChecked(false);
        label_14 = new QLabel(RFBurst);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(18, 100, 52, 30));
        label_15 = new QLabel(RFBurst);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(18, 0, 66, 30));
        label_15->setFont(font);
        pb_RFBurst_Pos = new QPushButton(RFBurst);
        pb_RFBurst_Pos->setObjectName(QStringLiteral("pb_RFBurst_Pos"));
        pb_RFBurst_Pos->setGeometry(QRect(94, 50, 68, 30));
        pb_RFBurst_Pos->setFont(font1);
        pb_RFBurst_Pos->setFocusPolicy(Qt::NoFocus);
        pb_RFBurst_Pos->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton:checked{\n"
"	color:rgba(87, 87, 87, 1);\n"
"	background-color:transparent;\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"color:rgba(123, 123, 123, 1);\n"
"background-color:transparent;\n"
"padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton:checked{\n"
"	color:rgba(87, 87, 87, 1);\n"
"	background-color:transparent;\n"
"	padding: 8px "
                        "14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QPushButton:!checked\n"
"{\n"
"color:rgba(123, 123, 123, 1);\n"
"background-color:transparent;\n"
"padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton:checked{\n"
"	color:rgba(85,74,56,1);\n"
"	background-color:transparent;\n"
"	padding: 8px 14px 7px 15px;\n"
"	border-image:url(:/sa/image/night/btn_left_click.png);\n"
"}\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QPushButton:!checked\n"
"{\n"
"color:rgba(121,106,81,1);\n"
"background-color:transparent;\n"
"padding: 8px 14px 7px 15px;\n"
"	border-image: url(:/sa/image/night/btn_left_nor.png);\n"
"}\n"
""));
        pb_RFBurst_Pos->setCheckable(true);
        pb_RFBurst_Pos->setChecked(true);
        pb_RFBurst_Pos->setAutoExclusive(true);
        pb_RFBurst_Pos->setFlat(true);
        label_16 = new QLabel(RFBurst);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(18, 150, 54, 45));
        subWidget->addWidget(RFBurst);
        GPS = new QWidget();
        GPS->setObjectName(QStringLiteral("GPS"));
        subWidget->addWidget(GPS);
        label_warning = new QLabel(widget);
        label_warning->setObjectName(QStringLiteral("label_warning"));
        label_warning->setGeometry(QRect(10, 40, 231, 71));
        label_warning->setStyleSheet(QLatin1String("#SA_Dialog_TriggerSetup[status  =  \"indoor\"] \n"
"QLabel\n"
"{\n"
"	color:rgba(162, 115, 0,1);\n"
"	font: 80 15px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"outdoor\"] \n"
"QLabel\n"
"{\n"
"	color:rgba(162, 115, 0,1);\n"
"	font: 80 15px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_TriggerSetup[status  =  \"night\"] \n"
"QLabel\n"
"{\n"
"	color:rgba(159,98,0,1);\n"
"	font: 80 15px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
""));
        pb_Internal = new QPushButton(SA_Dialog_TriggerSetup);
        pb_Internal->setObjectName(QStringLiteral("pb_Internal"));
        pb_Internal->setGeometry(QRect(280, 85, 216, 30));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        pb_Internal->setFont(font2);
        pb_Internal->setFocusPolicy(Qt::NoFocus);
        pb_Internal->setCheckable(true);
        pb_Internal->setChecked(false);
        pb_Internal->setAutoExclusive(true);
        pb_Internal->setFlat(false);
        pb_External_Rise = new QPushButton(SA_Dialog_TriggerSetup);
        pb_External_Rise->setObjectName(QStringLiteral("pb_External_Rise"));
        pb_External_Rise->setGeometry(QRect(280, 117, 216, 30));
        pb_External_Rise->setFont(font2);
        pb_External_Rise->setFocusPolicy(Qt::NoFocus);
        pb_External_Rise->setCheckable(true);
        pb_External_Rise->setAutoExclusive(true);
        pb_External_Rise->setFlat(false);
        pb_Trigger_Time = new QPushButton(SA_Dialog_TriggerSetup);
        pb_Trigger_Time->setObjectName(QStringLiteral("pb_Trigger_Time"));
        pb_Trigger_Time->setGeometry(QRect(280, 183, 216, 30));
        pb_Trigger_Time->setFont(font2);
        pb_Trigger_Time->setFocusPolicy(Qt::NoFocus);
        pb_Trigger_Time->setCheckable(true);
        pb_Trigger_Time->setAutoExclusive(true);
        pb_Trigger_Time->setFlat(false);
        pb_Video = new QPushButton(SA_Dialog_TriggerSetup);
        pb_Video->setObjectName(QStringLiteral("pb_Video"));
        pb_Video->setGeometry(QRect(280, 249, 216, 30));
        pb_Video->setFont(font2);
        pb_Video->setFocusPolicy(Qt::NoFocus);
        pb_Video->setCheckable(true);
        pb_Video->setAutoExclusive(true);
        pb_Video->setFlat(false);
        pb_External_Fall = new QPushButton(SA_Dialog_TriggerSetup);
        pb_External_Fall->setObjectName(QStringLiteral("pb_External_Fall"));
        pb_External_Fall->setGeometry(QRect(280, 150, 216, 30));
        pb_External_Fall->setFont(font2);
        pb_External_Fall->setFocusPolicy(Qt::NoFocus);
        pb_External_Fall->setCheckable(true);
        pb_External_Fall->setAutoExclusive(true);
        pb_External_Fall->setFlat(false);
        pb_GPS = new QPushButton(SA_Dialog_TriggerSetup);
        pb_GPS->setObjectName(QStringLiteral("pb_GPS"));
        pb_GPS->setGeometry(QRect(280, 216, 216, 30));
        pb_GPS->setFont(font2);
        pb_GPS->setFocusPolicy(Qt::NoFocus);
        pb_GPS->setCheckable(true);
        pb_GPS->setAutoExclusive(true);
        pb_GPS->setFlat(false);
        pb_FreeRun = new QPushButton(SA_Dialog_TriggerSetup);
        pb_FreeRun->setObjectName(QStringLiteral("pb_FreeRun"));
        pb_FreeRun->setGeometry(QRect(280, 53, 216, 30));
        pb_FreeRun->setFont(font2);
        pb_FreeRun->setCheckable(true);
        pb_FreeRun->setChecked(true);
        pb_FreeRun->setAutoExclusive(true);
        pb_FreeRun->setFlat(false);

        retranslateUi(SA_Dialog_TriggerSetup);

        subWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(SA_Dialog_TriggerSetup);
    } // setupUi

    void retranslateUi(QWidget *SA_Dialog_TriggerSetup)
    {
        SA_Dialog_TriggerSetup->setWindowTitle(QApplication::translate("SA_Dialog_TriggerSetup", "Form", Q_NULLPTR));
        SA_Dialog_TriggerSetup->setProperty("status", QVariant(QApplication::translate("SA_Dialog_TriggerSetup", "indoor", Q_NULLPTR)));
        label_2->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Trigger\n"
"Source", Q_NULLPTR));
        pb_cancel->setText(QString());
        lblTitle->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Trigger", Q_NULLPTR));
        TriggerTypeBox->clear();
        TriggerTypeBox->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_TriggerSetup", "Free Run", Q_NULLPTR)
         << QApplication::translate("SA_Dialog_TriggerSetup", "External", Q_NULLPTR)
         << QApplication::translate("SA_Dialog_TriggerSetup", "Video", Q_NULLPTR)
         << QApplication::translate("SA_Dialog_TriggerSetup", "Periodic timer", Q_NULLPTR)
         << QApplication::translate("SA_Dialog_TriggerSetup", "RF Burst", Q_NULLPTR)
        );
        label_9->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Trigger\n"
"Delay\n"
"Time", Q_NULLPTR));
        edit_External_DelayValue->setText(QApplication::translate("SA_Dialog_TriggerSetup", "200 ms", Q_NULLPTR));
        edit_External_level->setText(QApplication::translate("SA_Dialog_TriggerSetup", "3 V", Q_NULLPTR));
        pb_External_DelayOn->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Off", Q_NULLPTR));
        label_10->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Trigger\n"
"Delay", Q_NULLPTR));
        pb_External_Neg->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Neg", Q_NULLPTR));
        label_11->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Trigger\n"
"Slope", Q_NULLPTR));
        label_12->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Trigger\n"
"Level", Q_NULLPTR));
        pb_External_Pos->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Pos", Q_NULLPTR));
        edit_Video_DelayValue->setText(QApplication::translate("SA_Dialog_TriggerSetup", "200 ms", Q_NULLPTR));
        label->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Trigger\n"
"Delay\n"
"Time", Q_NULLPTR));
        edit_Video_level->setText(QApplication::translate("SA_Dialog_TriggerSetup", "20 dBm", Q_NULLPTR));
        pb_Video_Neg->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Neg", Q_NULLPTR));
        pb_Video_DelayOn->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Off", Q_NULLPTR));
        label_7->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Trigger\n"
"Delay", Q_NULLPTR));
        label_5->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Trigger\n"
"Slope", Q_NULLPTR));
        label_3->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Trigger\n"
"Level", Q_NULLPTR));
        pb_Video_Pos->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Pos", Q_NULLPTR));
        edit_Peri_time->setText(QApplication::translate("SA_Dialog_TriggerSetup", "100 ms", Q_NULLPTR));
        label_4->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Trigger\n"
"Peri time", Q_NULLPTR));
        label_6->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Trigger\n"
"Delay\n"
"Time", Q_NULLPTR));
        edit_PeriTime_DelayValue->setText(QApplication::translate("SA_Dialog_TriggerSetup", "200 ms", Q_NULLPTR));
        label_8->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Trigger\n"
"Delay", Q_NULLPTR));
        pb_PeriTime_DelayOn->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Off", Q_NULLPTR));
        pb_RFBurst_Neg->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Neg", Q_NULLPTR));
        edit_RFBurst_level->setText(QApplication::translate("SA_Dialog_TriggerSetup", "15 dBm", Q_NULLPTR));
        edit_RFBurst_DelayValue->setText(QApplication::translate("SA_Dialog_TriggerSetup", "200 ms", Q_NULLPTR));
        label_13->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Trigger\n"
"Slope", Q_NULLPTR));
        pb_RFBurst_DelayOn->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Off", Q_NULLPTR));
        label_14->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Trigger\n"
"Delay", Q_NULLPTR));
        label_15->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Trigger\n"
"Level", Q_NULLPTR));
        pb_RFBurst_Pos->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Pos", Q_NULLPTR));
        label_16->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Trigger\n"
"Delay\n"
"Time", Q_NULLPTR));
        label_warning->setText(QString());
        pb_Internal->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Internal", Q_NULLPTR));
        pb_External_Rise->setText(QApplication::translate("SA_Dialog_TriggerSetup", "External Rise", Q_NULLPTR));
        pb_Trigger_Time->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Trigger Time", Q_NULLPTR));
        pb_Video->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Video", Q_NULLPTR));
        pb_External_Fall->setText(QApplication::translate("SA_Dialog_TriggerSetup", "External Fall", Q_NULLPTR));
        pb_GPS->setText(QApplication::translate("SA_Dialog_TriggerSetup", "GPS", Q_NULLPTR));
        pb_FreeRun->setText(QApplication::translate("SA_Dialog_TriggerSetup", "Free Run", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SA_Dialog_TriggerSetup: public Ui_SA_Dialog_TriggerSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_TRIGGERSETUP_H
