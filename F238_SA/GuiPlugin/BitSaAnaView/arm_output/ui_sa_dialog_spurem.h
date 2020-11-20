/********************************************************************************
** Form generated from reading UI file 'sa_dialog_spurem.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_SPUREM_H
#define UI_SA_DIALOG_SPUREM_H

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

class Ui_SA_Dialog_SpurEM
{
public:
    QWidget *widget;
    QLabel *lblTitle;
    QPushButton *pb_cancel;
    QFrame *line;
    QLabel *lbl_Speed;
    QPushButton *pb_Speed_Normal;
    QPushButton *pb_Speed_Fast;
    QPushButton *pb_Ave_1;
    QLabel *label;
    QPushButton *pb_Ave_2;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pb_Report_Mode1;
    QPushButton *pb_Report_Mode2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *RangePara;
    QLabel *label_6;
    QLabel *label_14;
    SA_LineEdit *LedSweepTime;
    SA_LineEdit *LedStopFreq;
    QLabel *label_11;
    SA_Combobox *VBWBox;
    QLabel *label_4;
    SA_LineEdit *LedStartFreq;
    QLabel *label_8;
    SA_Combobox *RBWBox;
    QWidget *page_2;
    SA_LineEdit *LedAtten;
    QLabel *label_13;
    QLabel *label_10;
    SA_LineEdit *LedPeakDefinition;
    SA_LineEdit *LedPeakThreshold;
    QLabel *label_15;
    QLabel *label_5;
    SA_LineEdit *LedStopLimit;
    QLabel *label_12;
    SA_LineEdit *LedStartLimit;
    QLabel *label_16;
    SA_LineEdit *LedSpurIndex;
    SA_LineEdit *LedRangeIndex;
    QPushButton *pb_RangePara_2;
    QPushButton *pb_RangePara_1;
    QPushButton *pb_ReMeasure;
    QPushButton *pb_RangeOn;
    QLabel *label_17;
    QFrame *line_2;
    QLabel *label_7;
    QLabel *label_9;
    QPushButton *VBWManualPB;
    QPushButton *RBWManualPB;
    QPushButton *RBWAutoPB;
    QPushButton *VBWAutoPB;
    QButtonGroup *VbwAutoBtG;
    QButtonGroup *SpurReportBtG;
    QButtonGroup *RangeParaBtG;
    QButtonGroup *RbwAutoBtG;
    QButtonGroup *AveTypeBtG;

    void setupUi(QWidget *SA_Dialog_SpurEM)
    {
        if (SA_Dialog_SpurEM->objectName().isEmpty())
            SA_Dialog_SpurEM->setObjectName(QStringLiteral("SA_Dialog_SpurEM"));
        SA_Dialog_SpurEM->resize(252, 646);
        SA_Dialog_SpurEM->setStyleSheet(QLatin1String("#RangePara>QLabel,\n"
"#widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#widget>QPushButton\n"
"{\n"
"	\n"
"	border-style:flat;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_SpurEM[status=\"indoor\"] SA_LineEdit,\n"
"#SA_Dialog_SpurEM[status=\"indoor\"] SA_LineEdit:disable\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 12px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"/*\n"
"#SA_Dialog_SpurEM[status=\"indoor\"] SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"*/\n"
"#SA_Dialog_SpurEM[status=\"indoor\"] QComboBox\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(162, 115, 0, 1);\n"
"	padding:8px 23px 7px 10px;\n"
"	combobox-popup: 0;\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/dropdown_"
                        "normal.png);\n"
"}\n"
"#SA_Dialog_SpurEM[status=\"indoor\"] QComboBox:focus\n"
"{\n"
"	background-image: url(:/sa/image/dropdown_click.png);\n"
"	\n"
"}\n"
"#SA_Dialog_SpurEM[status=\"indoor\"] QComboBox::drop-down {\n"
"width: 0px;	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_SpurEM[status=\"indoor\"] QComboBox QAbstractItemView{\n"
"   font: 75 14px \"Arial\";\n"
"	color:rgba(0, 0, 0, 1);\n"
"	background:rgba(255,255,255,1);\n"
" 	outline:0px;\n"
"	border-style:solid;\n"
"	border-color:rgba(151, 151, 151, 1);\n"
"	border-width:1px;\n"
"}\n"
"#SA_Dialog_SpurEM[status=\"indoor\"] QAbstractItemView::item{\n"
"	padding-left:8px;\n"
"	width:140px;\n"
"	height:32px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_SpurEM[status=\"indoor\"] QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(240, 179, 29, 1); \n"
"}\n"
"#SA_Dialog_SpurEM[status=\"indoor\"] #pb_RangePara_1:checked,\n"
"#SA_Dialog_SpurEM[status=\"indoor\"] #pb_Report_Mode1:checked,\n"
"#SA_Dialog_SpurEM[status=\"indoor\"] #pb_Ave_1:che"
                        "cked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"#SA_Dialog_SpurEM[status=\"indoor\"] #pb_RangePara_1:!checked,\n"
"#SA_Dialog_SpurEM[status=\"indoor\"] #pb_Report_Mode1:!checked,\n"
"#SA_Dialog_SpurEM[status=\"indoor\"] #pb_Ave_1:!checked\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"#SA_Dialog_SpurEM[status=\"indoor\"] #pb_RangePara_2:checked,\n"
"#SA_Dialog_SpurEM[status=\"indoor\"] #pb_Report_Mode2:checked,\n"
"#SA_Dialog_SpurEM[status=\"indoor\"] #pb_Ave_2:checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"}\n"
"#SA_Dialog_SpurEM[status=\"indoor\"] #pb_RangePara_2:!checked,\n"
"#SA_Dialog_SpurEM[status=\"indoor\"] #pb_Report_Mode2:!checked,\n"
"#SA_Dialog_SpurEM[status=\"indoor\"] #pb_Ave_2:!checked\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	background-image: url(:/sa/image/fre_checked"
                        "_left.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"] SA_LineEdit,\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"] SA_LineEdit:disable\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 12px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"/*\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"] SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"*/\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"] QComboBox\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(162, 115, 0, 1);\n"
"	padding:8px 23px 7px 10px;\n"
"	combobox-popup: 0;\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/dropdown_normal.png);\n"
"}\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"] QComboBox:focus\n"
"{\n"
"	background-image: url(:/sa/image/dropdown_click.png);\n"
"	\n"
"}\n"
"#SA_Dialog_SpurEM[status="
                        "\"outdoor\"] QComboBox::drop-down {\n"
"width: 0px;	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"] QComboBox QAbstractItemView{\n"
"   font: 75 14px \"Arial\";\n"
"	color:rgba(0, 0, 0, 1);\n"
"	background:rgba(255,255,255,1);\n"
" 	outline:0px;\n"
"	border-style:solid;\n"
"	border-color:rgba(151, 151, 151, 1);\n"
"	border-width:1px;\n"
"}\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"] QAbstractItemView::item{\n"
"	padding-left:8px;\n"
"	width:140px;\n"
"	height:32px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"] QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(240, 179, 29, 1); \n"
"}\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"] #pb_RangePara_1:checked,\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"] #pb_Report_Mode1:checked,\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"] #pb_Ave_1:checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"] #pb_RangePara_1:!checked"
                        ",\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"] #pb_Report_Mode1:!checked,\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"] #pb_Ave_1:!checked\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"] #pb_RangePara_2:checked,\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"] #pb_Report_Mode2:checked,\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"] #pb_Ave_2:checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"}\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"] #pb_RangePara_2:!checked,\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"] #pb_Report_Mode2:!checked,\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"] #pb_Ave_2:!checked\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-position:right;\n"
"}\n"
"/*******************night**********************/\n"
"\n"
"#SA_Dialog_SpurEM[status  =  \"night\"] SA_LineEdit,\n"
""
                        "#SA_Dialog_SpurEM[status  =  \"night\"] SA_LineEdit:disable\n"
"{\n"
"	background: rgba(251,220,167,0.60);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 6px 7px 6px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"/*\n"
"#SA_Dialog_SpurEM[status  =  \"night\"] SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"*/\n"
"\n"
"#SA_Dialog_SpurEM[status  =  \"night\"] \n"
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
"#SA_Dialog_SpurEM[status  =  \"night\"] \n"
"QComboBox:focus\n"
"{\n"
"	background-color:rgba(251,220,167,0.60);\n"
"	background-image: url(:/sa/image/dropdown_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpurEM[status  =  \"night\"] \n"
"QComboBox::drop-dow"
                        "n \n"
"{\n"
"	width: 0px;	\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_SpurEM[status  =  \"night\"] \n"
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
"#SA_Dialog_SpurEM[status  =  \"night\"] \n"
"QAbstractItemView::item{\n"
"	padding-left:8px;\n"
"	width:140px;\n"
"	height:32px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_SpurEM[status  =  \"night\"] \n"
"QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(159,98,0,1);\n"
"}\n"
"\n"
"#SA_Dialog_SpurEM[status=\"night\"] #pb_RangePara_1:checked,\n"
"#SA_Dialog_SpurEM[status=\"night\"] #pb_Report_Mode1:checked,\n"
"#SA_Dialog_SpurEM[status=\"night\"] #pb_Ave_1:checked\n"
"{\n"
"	color:rgba(85,74,56,1);\n"
"	background-image: url(:/sa/image/night/btn_left_click.png);\n"
"}\n"
"#SA_Dialog_SpurEM[status=\"night\"] #pb_RangePara_1:!checked,\n"
""
                        "#SA_Dialog_SpurEM[status=\"night\"] #pb_Report_Mode1:!checked,\n"
"#SA_Dialog_SpurEM[status=\"night\"] #pb_Ave_1:!checked\n"
"{\n"
"	color:rgba(121, 105, 80, 1);\n"
"	background-image: url(:/sa/image/night/btn_left_nor.png);\n"
"}\n"
"#SA_Dialog_SpurEM[status=\"night\"] #pb_RangePara_2:checked,\n"
"#SA_Dialog_SpurEM[status=\"night\"] #pb_Report_Mode2:checked,\n"
"#SA_Dialog_SpurEM[status=\"night\"] #pb_Ave_2:checked\n"
"{\n"
"	color:rgba(85,74,56,1);\n"
"	background-image:url(:/sa/image/night/btn_right_click.png) ;\n"
"}\n"
"#SA_Dialog_SpurEM[status=\"night\"] #pb_RangePara_2:!checked,\n"
"#SA_Dialog_SpurEM[status=\"night\"] #pb_Report_Mode2:!checked,\n"
"#SA_Dialog_SpurEM[status=\"night\"] #pb_Ave_2:!checked\n"
"{\n"
"	color:rgba(121, 105, 80, 1);\n"
"	background-image: url(:/sa/image/night/btn_right_nor.png);\n"
"}\n"
""));
        widget = new QWidget(SA_Dialog_SpurEM);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 252, 646));
        widget->setStyleSheet(QLatin1String("#widget{\n"
"background-color:rgba(211,211,211,0.9);\n"
"}\n"
"\n"
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
"\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_SpurEM[status=\"indoor\"] #widget \n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"] #widget \n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_SpurEM[status=\"night\"] #widget \n"
"{\n"
"	background-color:rgba(208,182,139,0.9);\n"
"}"));
        lblTitle = new QLabel(widget);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));
        lblTitle->setGeometry(QRect(20, 19, 191, 22));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        lblTitle->setFont(font);
        pb_cancel = new QPushButton(widget);
        pb_cancel->setObjectName(QStringLiteral("pb_cancel"));
        pb_cancel->setGeometry(QRect(212, 6, 35, 35));
        pb_cancel->setFocusPolicy(Qt::NoFocus);
        pb_cancel->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_SpurEM[status  =  \"indoor\"] QPushButton\n"
"{\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_SpurEM[status  =  \"indoor\"] QPushButton:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_SpurEM[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_SpurEM[status  =  \"outdoor\"] QPushButton:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_SpurEM[status  =  \"night\"] QPushButton\n"
"{\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/night/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_SpurEM[status  =  \"night\"] QPushButton:pressed\n"
"{\n"
"border-image: url(:/sa/image/"
                        "night/btn_close_click.png);\n"
"}"));
        line = new QFrame(widget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(18, 46, 212, 2));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        lbl_Speed = new QLabel(widget);
        lbl_Speed->setObjectName(QStringLiteral("lbl_Speed"));
        lbl_Speed->setGeometry(QRect(284, 262, 68, 30));
        pb_Speed_Normal = new QPushButton(widget);
        pb_Speed_Normal->setObjectName(QStringLiteral("pb_Speed_Normal"));
        pb_Speed_Normal->setGeometry(QRect(360, 262, 69, 30));
        pb_Speed_Normal->setFocusPolicy(Qt::NoFocus);
        pb_Speed_Normal->setStyleSheet(QLatin1String("QPushButton:checked\n"
"{\n"
"	padding: 8px 14px 7px 10px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"QPushButton:!checked\n"
"{\n"
"	padding: 8px 14px 7px 10px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}"));
        pb_Speed_Normal->setCheckable(true);
        pb_Speed_Normal->setChecked(true);
        pb_Speed_Normal->setAutoExclusive(true);
        pb_Speed_Fast = new QPushButton(widget);
        pb_Speed_Fast->setObjectName(QStringLiteral("pb_Speed_Fast"));
        pb_Speed_Fast->setGeometry(QRect(431, 262, 69, 30));
        pb_Speed_Fast->setFocusPolicy(Qt::NoFocus);
        pb_Speed_Fast->setStyleSheet(QLatin1String("QPushButton:checked\n"
"{\n"
"padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"QPushButton:!checked\n"
"{\n"
"padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-position:right;\n"
"}"));
        pb_Speed_Fast->setCheckable(true);
        pb_Speed_Fast->setAutoExclusive(true);
        pb_Ave_1 = new QPushButton(widget);
        AveTypeBtG = new QButtonGroup(SA_Dialog_SpurEM);
        AveTypeBtG->setObjectName(QStringLiteral("AveTypeBtG"));
        AveTypeBtG->addButton(pb_Ave_1);
        pb_Ave_1->setObjectName(QStringLiteral("pb_Ave_1"));
        pb_Ave_1->setGeometry(QRect(94, 119, 69, 30));
        pb_Ave_1->setCheckable(true);
        pb_Ave_1->setChecked(true);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(18, 119, 67, 31));
        pb_Ave_2 = new QPushButton(widget);
        AveTypeBtG->addButton(pb_Ave_2);
        pb_Ave_2->setObjectName(QStringLiteral("pb_Ave_2"));
        pb_Ave_2->setGeometry(QRect(165, 119, 69, 30));
        pb_Ave_2->setCheckable(true);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(18, 209, 67, 31));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(18, 164, 81, 31));
        pb_Report_Mode1 = new QPushButton(widget);
        SpurReportBtG = new QButtonGroup(SA_Dialog_SpurEM);
        SpurReportBtG->setObjectName(QStringLiteral("SpurReportBtG"));
        SpurReportBtG->addButton(pb_Report_Mode1);
        pb_Report_Mode1->setObjectName(QStringLiteral("pb_Report_Mode1"));
        pb_Report_Mode1->setGeometry(QRect(94, 164, 69, 30));
        pb_Report_Mode1->setCheckable(true);
        pb_Report_Mode1->setChecked(true);
        pb_Report_Mode1->setAutoRepeat(false);
        pb_Report_Mode2 = new QPushButton(widget);
        SpurReportBtG->addButton(pb_Report_Mode2);
        pb_Report_Mode2->setObjectName(QStringLiteral("pb_Report_Mode2"));
        pb_Report_Mode2->setGeometry(QRect(165, 164, 69, 30));
        pb_Report_Mode2->setCheckable(true);
        stackedWidget = new QStackedWidget(widget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 393, 252, 241));
        stackedWidget->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#RBWAutoPB:checked,\n"
"#VBWAutoPB:checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"#RBWAutoPB,\n"
"#VBWAutoPB\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"#RBWManualPB:checked,\n"
"#VBWManualPB:checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#RBWManualPB,\n"
"#VBWManualPB\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-position:right;\n"
"}\n"
""
                        "\n"
"\n"
""));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        stackedWidget->addWidget(page);
        RangePara = new QWidget();
        RangePara->setObjectName(QStringLiteral("RangePara"));
        label_6 = new QLabel(RangePara);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(18, 150, 61, 25));
        label_14 = new QLabel(RangePara);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(18, 200, 68, 30));
        LedSweepTime = new SA_LineEdit(RangePara);
        LedSweepTime->setObjectName(QStringLiteral("LedSweepTime"));
        LedSweepTime->setGeometry(QRect(94, 200, 140, 30));
        LedSweepTime->setStyleSheet(QStringLiteral(""));
        LedSweepTime->setReadOnly(true);
        LedStopFreq = new SA_LineEdit(RangePara);
        LedStopFreq->setObjectName(QStringLiteral("LedStopFreq"));
        LedStopFreq->setGeometry(QRect(94, 50, 140, 30));
        LedStopFreq->setReadOnly(true);
        label_11 = new QLabel(RangePara);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(18, 50, 68, 30));
        VBWBox = new SA_Combobox(RangePara);
        VBWBox->setObjectName(QStringLiteral("VBWBox"));
        VBWBox->setGeometry(QRect(94, 150, 140, 30));
        VBWBox->setStyleSheet(QStringLiteral(""));
        VBWBox->setEditable(false);
        VBWBox->setMaxVisibleItems(112);
        label_4 = new QLabel(RangePara);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(18, 0, 68, 30));
        LedStartFreq = new SA_LineEdit(RangePara);
        LedStartFreq->setObjectName(QStringLiteral("LedStartFreq"));
        LedStartFreq->setGeometry(QRect(94, 0, 140, 30));
        LedStartFreq->setReadOnly(true);
        label_8 = new QLabel(RangePara);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(18, 100, 61, 25));
        RBWBox = new SA_Combobox(RangePara);
        RBWBox->setObjectName(QStringLiteral("RBWBox"));
        RBWBox->setGeometry(QRect(94, 100, 140, 30));
        RBWBox->setStyleSheet(QStringLiteral(""));
        RBWBox->setMaxVisibleItems(999);
        stackedWidget->addWidget(RangePara);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        LedAtten = new SA_LineEdit(page_2);
        LedAtten->setObjectName(QStringLiteral("LedAtten"));
        LedAtten->setGeometry(QRect(94, 180, 140, 30));
        LedAtten->setReadOnly(true);
        label_13 = new QLabel(page_2);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(18, 135, 68, 30));
        label_10 = new QLabel(page_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(18, 90, 68, 30));
        LedPeakDefinition = new SA_LineEdit(page_2);
        LedPeakDefinition->setObjectName(QStringLiteral("LedPeakDefinition"));
        LedPeakDefinition->setGeometry(QRect(94, 90, 140, 30));
        LedPeakDefinition->setReadOnly(true);
        LedPeakThreshold = new SA_LineEdit(page_2);
        LedPeakThreshold->setObjectName(QStringLiteral("LedPeakThreshold"));
        LedPeakThreshold->setGeometry(QRect(94, 135, 140, 30));
        LedPeakThreshold->setReadOnly(true);
        label_15 = new QLabel(page_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(18, 180, 68, 30));
        label_5 = new QLabel(page_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(18, 0, 68, 30));
        LedStopLimit = new SA_LineEdit(page_2);
        LedStopLimit->setObjectName(QStringLiteral("LedStopLimit"));
        LedStopLimit->setGeometry(QRect(94, 50, 140, 30));
        LedStopLimit->setReadOnly(true);
        label_12 = new QLabel(page_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(18, 50, 68, 30));
        LedStartLimit = new SA_LineEdit(page_2);
        LedStartLimit->setObjectName(QStringLiteral("LedStartLimit"));
        LedStartLimit->setGeometry(QRect(94, 0, 140, 30));
        LedStartLimit->setReadOnly(true);
        stackedWidget->addWidget(page_2);
        label_16 = new QLabel(widget);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(18, 308, 67, 31));
        LedSpurIndex = new SA_LineEdit(widget);
        LedSpurIndex->setObjectName(QStringLiteral("LedSpurIndex"));
        LedSpurIndex->setGeometry(QRect(94, 209, 140, 30));
        LedSpurIndex->setReadOnly(true);
        LedRangeIndex = new SA_LineEdit(widget);
        LedRangeIndex->setObjectName(QStringLiteral("LedRangeIndex"));
        LedRangeIndex->setGeometry(QRect(94, 308, 140, 30));
        LedRangeIndex->setReadOnly(true);
        pb_RangePara_2 = new QPushButton(widget);
        RangeParaBtG = new QButtonGroup(SA_Dialog_SpurEM);
        RangeParaBtG->setObjectName(QStringLiteral("RangeParaBtG"));
        RangeParaBtG->addButton(pb_RangePara_2);
        pb_RangePara_2->setObjectName(QStringLiteral("pb_RangePara_2"));
        pb_RangePara_2->setGeometry(QRect(140, 270, 69, 30));
        pb_RangePara_2->setCheckable(true);
        pb_RangePara_1 = new QPushButton(widget);
        RangeParaBtG->addButton(pb_RangePara_1);
        pb_RangePara_1->setObjectName(QStringLiteral("pb_RangePara_1"));
        pb_RangePara_1->setGeometry(QRect(40, 270, 69, 30));
        pb_RangePara_1->setCheckable(true);
        pb_RangePara_1->setChecked(true);
        pb_RangePara_1->setAutoRepeat(false);
        pb_ReMeasure = new QPushButton(widget);
        pb_ReMeasure->setObjectName(QStringLiteral("pb_ReMeasure"));
        pb_ReMeasure->setGeometry(QRect(18, 73, 216, 30));
        pb_ReMeasure->setFocusPolicy(Qt::NoFocus);
        pb_ReMeasure->setStyleSheet(QLatin1String("/*******************common**********************/\n"
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
"	\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_SpurEM[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	color:rgba(255, 255, 255, 1);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpurEM[status  =  \"indoor\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_SpurEM[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	color:rgba(0, 0, 0, 1);\n"
"	border-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpurEM[status  =  \"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image"
                        ": url(:/sa/image/outdoor/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_SpurEM[status  =  \"night\"] QPushButton\n"
"{\n"
"	color: #FBDBA7; \n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpurEM[status  =  \"night\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/btn_w216_click.png);\n"
"}"));
        pb_ReMeasure->setCheckable(true);
        pb_RangeOn = new QPushButton(widget);
        pb_RangeOn->setObjectName(QStringLiteral("pb_RangeOn"));
        pb_RangeOn->setGeometry(QRect(94, 348, 90, 30));
        pb_RangeOn->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_SpurEM[status=\"indoor\"]  QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"#SA_Dialog_SpurEM[status=\"indoor\"]  QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"]  QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"#SA_Dialog_SpurEM[status=\"outdoor\"]  QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpurEM[status=\"night\"]  QPushButton:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/nigh"
                        "t/toggle_on.png);\n"
"}\n"
"#SA_Dialog_SpurEM[status=\"night\"]  QPushButton:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(121,106,81,1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}\n"
"\n"
""));
        pb_RangeOn->setCheckable(true);
        pb_RangeOn->setFlat(false);
        label_17 = new QLabel(widget);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(18, 345, 67, 31));
        line_2 = new QFrame(widget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(18, 253, 212, 2));
        line_2->setStyleSheet(QLatin1String("#line_2\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(SA_Dialog_SpurEM);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(290, 430, 67, 25));
        label_9 = new QLabel(SA_Dialog_SpurEM);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(290, 520, 67, 25));
        VBWManualPB = new QPushButton(SA_Dialog_SpurEM);
        VbwAutoBtG = new QButtonGroup(SA_Dialog_SpurEM);
        VbwAutoBtG->setObjectName(QStringLiteral("VbwAutoBtG"));
        VbwAutoBtG->addButton(VBWManualPB);
        VBWManualPB->setObjectName(QStringLiteral("VBWManualPB"));
        VBWManualPB->setGeometry(QRect(437, 520, 69, 30));
        VBWManualPB->setFocusPolicy(Qt::NoFocus);
        VBWManualPB->setCheckable(true);
        RBWManualPB = new QPushButton(SA_Dialog_SpurEM);
        RbwAutoBtG = new QButtonGroup(SA_Dialog_SpurEM);
        RbwAutoBtG->setObjectName(QStringLiteral("RbwAutoBtG"));
        RbwAutoBtG->addButton(RBWManualPB);
        RBWManualPB->setObjectName(QStringLiteral("RBWManualPB"));
        RBWManualPB->setGeometry(QRect(437, 430, 69, 30));
        RBWManualPB->setFocusPolicy(Qt::NoFocus);
        RBWManualPB->setCheckable(true);
        RBWAutoPB = new QPushButton(SA_Dialog_SpurEM);
        RbwAutoBtG->addButton(RBWAutoPB);
        RBWAutoPB->setObjectName(QStringLiteral("RBWAutoPB"));
        RBWAutoPB->setGeometry(QRect(366, 430, 69, 30));
        RBWAutoPB->setFocusPolicy(Qt::NoFocus);
        RBWAutoPB->setCheckable(true);
        RBWAutoPB->setChecked(true);
        VBWAutoPB = new QPushButton(SA_Dialog_SpurEM);
        VbwAutoBtG->addButton(VBWAutoPB);
        VBWAutoPB->setObjectName(QStringLiteral("VBWAutoPB"));
        VBWAutoPB->setGeometry(QRect(366, 520, 69, 30));
        VBWAutoPB->setFocusPolicy(Qt::NoFocus);
        VBWAutoPB->setCheckable(true);
        VBWAutoPB->setChecked(true);

        retranslateUi(SA_Dialog_SpurEM);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SA_Dialog_SpurEM);
    } // setupUi

    void retranslateUi(QWidget *SA_Dialog_SpurEM)
    {
        SA_Dialog_SpurEM->setWindowTitle(QApplication::translate("SA_Dialog_SpurEM", "Form", 0));
        SA_Dialog_SpurEM->setProperty("status", QVariant(QApplication::translate("SA_Dialog_SpurEM", "indoor", 0)));
        lblTitle->setText(QApplication::translate("SA_Dialog_SpurEM", "Spurious Emission", 0));
        pb_cancel->setText(QString());
        lbl_Speed->setText(QApplication::translate("SA_Dialog_SpurEM", "Sweep\n"
"Speed", 0));
        pb_Speed_Normal->setText(QApplication::translate("SA_Dialog_SpurEM", "Normal", 0));
        pb_Speed_Fast->setText(QApplication::translate("SA_Dialog_SpurEM", "Fast", 0));
        pb_Ave_1->setText(QApplication::translate("SA_Dialog_SpurEM", "Once", 0));
        label->setText(QApplication::translate("SA_Dialog_SpurEM", "Scan\n"
"Type", 0));
        pb_Ave_2->setText(QApplication::translate("SA_Dialog_SpurEM", "Repeat", 0));
        label_2->setText(QApplication::translate("SA_Dialog_SpurEM", "Spur\n"
"Index", 0));
        label_3->setText(QApplication::translate("SA_Dialog_SpurEM", "Spur Report\n"
"Mode", 0));
        pb_Report_Mode1->setText(QApplication::translate("SA_Dialog_SpurEM", "All Spurs", 0));
        pb_Report_Mode2->setText(QApplication::translate("SA_Dialog_SpurEM", "Limit Test\n"
"Spurs", 0));
        label_6->setText(QApplication::translate("SA_Dialog_SpurEM", "VBW", 0));
        label_14->setText(QApplication::translate("SA_Dialog_SpurEM", "Sweep\n"
"Time", 0));
        LedSweepTime->setText(QApplication::translate("SA_Dialog_SpurEM", "1,000.000 MHz", 0));
        LedStopFreq->setStyleSheet(QString());
        LedStopFreq->setText(QApplication::translate("SA_Dialog_SpurEM", "1,000.000 MHz", 0));
        label_11->setText(QApplication::translate("SA_Dialog_SpurEM", "Stop\n"
"Frequency", 0));
        VBWBox->clear();
        VBWBox->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_SpurEM", "3 MHz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "1 MHz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "300 kHz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "100 kHz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "30 kHz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "10 kHz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "3 kHz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "1 kHz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "300 Hz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "100 Hz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "30 Hz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "10 Hz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "3 Hz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "1 Hz", 0)
        );
        label_4->setText(QApplication::translate("SA_Dialog_SpurEM", "Start\n"
"Frequency", 0));
        LedStartFreq->setStyleSheet(QString());
        LedStartFreq->setText(QApplication::translate("SA_Dialog_SpurEM", "1,000.000 MHz", 0));
        label_8->setText(QApplication::translate("SA_Dialog_SpurEM", "RBW", 0));
        RBWBox->clear();
        RBWBox->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_SpurEM", "5 MHz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "3 MHz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "1 MHz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "300 kHz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "100 kHz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "30 kHz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "10 kHz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "3 kHz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "1 kHz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "300 Hz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "100 Hz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "30 Hz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "10 Hz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "3 Hz", 0)
         << QApplication::translate("SA_Dialog_SpurEM", "1 Hz", 0)
        );
        LedAtten->setText(QApplication::translate("SA_Dialog_SpurEM", "1,000.000 MHz", 0));
        label_13->setText(QApplication::translate("SA_Dialog_SpurEM", "Peak\n"
"Threshold", 0));
        label_10->setText(QApplication::translate("SA_Dialog_SpurEM", "Peak\n"
"Definition", 0));
        LedPeakDefinition->setText(QApplication::translate("SA_Dialog_SpurEM", "1,000.000 MHz", 0));
        LedPeakThreshold->setText(QApplication::translate("SA_Dialog_SpurEM", "1,000.000 MHz", 0));
        label_15->setText(QApplication::translate("SA_Dialog_SpurEM", "Atten", 0));
        label_5->setText(QApplication::translate("SA_Dialog_SpurEM", "Start\n"
"Limit", 0));
        LedStopLimit->setText(QApplication::translate("SA_Dialog_SpurEM", "dBm", 0));
        label_12->setText(QApplication::translate("SA_Dialog_SpurEM", "Stop\n"
"Limit", 0));
        LedStartLimit->setText(QApplication::translate("SA_Dialog_SpurEM", "dBm", 0));
        label_16->setText(QApplication::translate("SA_Dialog_SpurEM", "Range\n"
"Index", 0));
        LedSpurIndex->setText(QApplication::translate("SA_Dialog_SpurEM", "1", 0));
        LedRangeIndex->setText(QApplication::translate("SA_Dialog_SpurEM", "1", 0));
        pb_RangePara_2->setText(QApplication::translate("SA_Dialog_SpurEM", "Limit\n"
"Condition", 0));
        pb_RangePara_1->setText(QApplication::translate("SA_Dialog_SpurEM", "Range\n"
"Config", 0));
        pb_ReMeasure->setText(QApplication::translate("SA_Dialog_SpurEM", "Scan", 0));
        pb_RangeOn->setText(QApplication::translate("SA_Dialog_SpurEM", "Off", 0));
        label_17->setText(QApplication::translate("SA_Dialog_SpurEM", "Range\n"
"Index", 0));
        label_7->setText(QApplication::translate("SA_Dialog_SpurEM", "RBW", 0));
        label_9->setText(QApplication::translate("SA_Dialog_SpurEM", "VBW", 0));
        VBWManualPB->setText(QApplication::translate("SA_Dialog_SpurEM", "Manual", 0));
        RBWManualPB->setText(QApplication::translate("SA_Dialog_SpurEM", "Manual", 0));
        RBWAutoPB->setText(QApplication::translate("SA_Dialog_SpurEM", "Auto", 0));
        VBWAutoPB->setText(QApplication::translate("SA_Dialog_SpurEM", "Auto", 0));
    } // retranslateUi

};

namespace Ui {
    class SA_Dialog_SpurEM: public Ui_SA_Dialog_SpurEM {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_SPUREM_H
