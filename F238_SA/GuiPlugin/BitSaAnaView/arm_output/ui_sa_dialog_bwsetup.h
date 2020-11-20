/********************************************************************************
** Form generated from reading UI file 'sa_dialog_bwsetup.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_BWSETUP_H
#define UI_SA_DIALOG_BWSETUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "sa_combobox.h"

QT_BEGIN_NAMESPACE

class Ui_SA_Dialog_BWSetup
{
public:
    QWidget *widget;
    QPushButton *pb_cancel;
    QLabel *lblTitle;
    QFrame *line;
    QPushButton *RBWManualPB;
    QPushButton *RBWAutoPB;
    QLabel *lblRBWAuto;
    QLabel *lblRBWValue;
    QPushButton *VBWManualPB;
    QLabel *lblVBWAuto;
    QLabel *lblVBWValue;
    QPushButton *VBWAutoPB;
    QLabel *lblRatioValue;
    SA_Combobox *RBWBox;
    SA_Combobox *VBWBox;
    SA_Combobox *ratioBox;
    QLabel *lblIF;
    SA_Combobox *IF_OutPut_Box;
    QLabel *labelWarning;
    QButtonGroup *btnVBWgroup;
    QButtonGroup *btnRBWgroup;

    void setupUi(QWidget *SA_Dialog_BWSetup)
    {
        if (SA_Dialog_BWSetup->objectName().isEmpty())
            SA_Dialog_BWSetup->setObjectName(QStringLiteral("SA_Dialog_BWSetup"));
        SA_Dialog_BWSetup->resize(252, 646);
        SA_Dialog_BWSetup->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_BWSetup[status  =  \"indoor\"] \n"
"#widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"indoor\"] \n"
"#widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"indoor\"] \n"
"SA_LineEdit\n"
"{\n"
"	color:rgb(176,138,30);\n"
"	padding-left:10px;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"indoor\"] #RBWAutoPB:checked,\n"
"#SA_Dialog_BWSetup[status  =  \"indoor\"] #VBWAutoPB:checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"indoor\"] #RBWAutoPB,\n"
"#SA_Dialog_BWSetup[status  =  \"indoor\"] #VBWAutoPB\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	padding: 8px 14px"
                        " 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"indoor\"] #RBWManualPB:checked,\n"
"#SA_Dialog_BWSetup[status  =  \"indoor\"] #VBWManualPB:checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"indoor\"] #RBWManualPB,\n"
"#SA_Dialog_BWSetup[status  =  \"indoor\"] #VBWManualPB\n"
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
"#SA_Dialog_BWSetup[status  =  \"indoor\"] \n"
"#lblTitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"indoor\"] \n"
"#pb_cancel\n"
"{\n"
"border-"
                        "style:flat;\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"indoor\"] \n"
"#pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"indoor\"] \n"
"#line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"indoor\"] \n"
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
"#SA_Dialog_BWSetup[status  =  \"indoor\"] \n"
"QComboBox:focus\n"
"{\n"
"	background-image: url(:/sa/image/dropdown_click.png);\n"
"	\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"indoor\"] \n"
"QComboBox::drop-down {\n"
"width: 0px;	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"indoor\"] \n"
"QComboBox QAbstractItemView{\n"
""
                        "   font: 75 14px \"Arial\";\n"
"	color:rgba(0, 0, 0, 1);\n"
"	background:rgba(255,255,255,1);\n"
" 	outline:0px;\n"
"	border-style:solid;\n"
"	border-color:rgba(151, 151, 151, 1);\n"
"	border-width:1px;\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"indoor\"] \n"
"QAbstractItemView::item{\n"
"	padding-left:8px;\n"
"	width:140px;\n"
"	height:32px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"indoor\"] \n"
"QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(240, 179, 29, 1); \n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"indoor\"] \n"
"SA_LineEdit\n"
"{\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"indoor\"] \n"
"SA_LineEdit:disable\n"
"{\n"
"	color:rgba(133,133,133,0.6);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"indoor\"] \n"
"SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"}\n"
"/*******************outdoor**"
                        "********************/\n"
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] \n"
"#widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] \n"
"#widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] \n"
"SA_LineEdit\n"
"{\n"
"	color:rgb(176,138,30);\n"
"	padding-left:10px;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] #RBWAutoPB:checked,\n"
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] #VBWAutoPB:checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] #RBWAutoPB,\n"
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] #VBWAutoPB\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	padding: 8px 14px 7px 15px;\n"
"	backg"
                        "round-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] #RBWManualPB:checked,\n"
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] #VBWManualPB:checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] #RBWManualPB,\n"
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] #VBWManualPB\n"
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
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] \n"
"#lblTitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] \n"
"#pb_cancel\n"
"{\n"
"border-style:flat;\n"
""
                        "background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] \n"
"#pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] \n"
"#line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] \n"
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
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] \n"
"QComboBox:focus\n"
"{\n"
"	background-image: url(:/sa/image/dropdown_click.png);\n"
"	\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] \n"
"QComboBox::drop-down {\n"
"width: 0px;	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] \n"
"QComboBox QAbstractItemView{\n"
"   font"
                        ": 75 14px \"Arial\";\n"
"	color:rgba(0, 0, 0, 1);\n"
"	background:rgba(255,255,255,1);\n"
" 	outline:0px;\n"
"	border-style:solid;\n"
"	border-color:rgba(151, 151, 151, 1);\n"
"	border-width:1px;\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] \n"
"QAbstractItemView::item{\n"
"	padding-left:8px;\n"
"	width:140px;\n"
"	height:32px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] \n"
"QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(240, 179, 29, 1); \n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] \n"
"SA_LineEdit\n"
"{\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] \n"
"SA_LineEdit:disable\n"
"{\n"
"	color:rgba(133,133,133,0.6);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"outdoor\"] \n"
"SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"}\n"
"/*******************night******"
                        "****************/\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] \n"
"#widget\n"
"{\n"
"		background-color:rgba(208,182,139,0.9);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] \n"
"#widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] \n"
"SA_LineEdit\n"
"{\n"
"	color:rgb(176,138,30);\n"
"	padding-left:10px;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] #RBWAutoPB:checked,\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] #VBWAutoPB:checked\n"
"{\n"
"	color:rgba(85,74,56,1);\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/night/btn_left_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] #RBWAutoPB,\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] #VBWAutoPB\n"
"{\n"
"	color:rgba(121,106,81,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:"
                        "/sa/image/night/btn_left_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] #RBWManualPB:checked,\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] #VBWManualPB:checked\n"
"{\n"
"	color:rgba(85,74,56,1);\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/night/btn_right_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] #RBWManualPB,\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] #VBWManualPB\n"
"{\n"
"	color:rgba(121,106,81,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/night/btn_right_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] \n"
"#lblTitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] \n"
"#pb_cancel\n"
"{\n"
"border-style:flat;\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/night/btn_close_normal.pn"
                        "g);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] \n"
"#pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/night/btn_close_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] \n"
"#line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] \n"
"QComboBox\n"
"{\n"
"	background-color: rgba(251,220,167,0.60);\n"
"	color:rgba(159,98,0,1);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	padding:8px 23px 7px 10px;\n"
"	combobox-popup: 0;\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/night/dropdown_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] \n"
"QComboBox:focus\n"
"{\n"
"	background-image: url(:/sa/image/night/dropdown_click.png);\n"
"	\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] \n"
"QComboBox::drop-down {\n"
"width: 0px;	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] \n"
"QComboBox QAbstractItemView{\n"
"   font: 75 14px \"Arial\";\n"
"	color:rgb"
                        "a(0, 0, 0, 1);\n"
"	background-color: #FBDBA7;\n"
" 	outline:0px;\n"
"	border-style:solid;\n"
"	border-color:rgba(151, 151, 151, 1);\n"
"	border-width:1px;\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] \n"
"QAbstractItemView::item{\n"
"	padding-left:8px;\n"
"	width:140px;\n"
"	height:32px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] \n"
"QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(159,98,0,1);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] \n"
"SA_LineEdit\n"
"{\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] \n"
"SA_LineEdit:disable\n"
"{\n"
"	color:rgba(133,133,133,0.6);\n"
"}\n"
"\n"
"#SA_Dialog_BWSetup[status  =  \"night\"] \n"
"SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"}"));
        widget = new QWidget(SA_Dialog_BWSetup);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 252, 646));
        widget->setStyleSheet(QStringLiteral(""));
        pb_cancel = new QPushButton(widget);
        pb_cancel->setObjectName(QStringLiteral("pb_cancel"));
        pb_cancel->setGeometry(QRect(212, 6, 35, 35));
        pb_cancel->setFocusPolicy(Qt::NoFocus);
        lblTitle = new QLabel(widget);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));
        lblTitle->setGeometry(QRect(17, 19, 121, 22));
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
        RBWManualPB = new QPushButton(widget);
        btnRBWgroup = new QButtonGroup(SA_Dialog_BWSetup);
        btnRBWgroup->setObjectName(QStringLiteral("btnRBWgroup"));
        btnRBWgroup->addButton(RBWManualPB);
        RBWManualPB->setObjectName(QStringLiteral("RBWManualPB"));
        RBWManualPB->setGeometry(QRect(166, 117, 69, 30));
        RBWManualPB->setFocusPolicy(Qt::NoFocus);
        RBWManualPB->setCheckable(true);
        RBWAutoPB = new QPushButton(widget);
        btnRBWgroup->addButton(RBWAutoPB);
        RBWAutoPB->setObjectName(QStringLiteral("RBWAutoPB"));
        RBWAutoPB->setGeometry(QRect(95, 117, 69, 30));
        RBWAutoPB->setFocusPolicy(Qt::NoFocus);
        RBWAutoPB->setCheckable(true);
        RBWAutoPB->setChecked(true);
        lblRBWAuto = new QLabel(widget);
        lblRBWAuto->setObjectName(QStringLiteral("lblRBWAuto"));
        lblRBWAuto->setGeometry(QRect(18, 120, 67, 25));
        lblRBWValue = new QLabel(widget);
        lblRBWValue->setObjectName(QStringLiteral("lblRBWValue"));
        lblRBWValue->setGeometry(QRect(18, 67, 61, 25));
        VBWManualPB = new QPushButton(widget);
        btnVBWgroup = new QButtonGroup(SA_Dialog_BWSetup);
        btnVBWgroup->setObjectName(QStringLiteral("btnVBWgroup"));
        btnVBWgroup->addButton(VBWManualPB);
        VBWManualPB->setObjectName(QStringLiteral("VBWManualPB"));
        VBWManualPB->setGeometry(QRect(166, 217, 69, 30));
        VBWManualPB->setFocusPolicy(Qt::NoFocus);
        VBWManualPB->setCheckable(true);
        lblVBWAuto = new QLabel(widget);
        lblVBWAuto->setObjectName(QStringLiteral("lblVBWAuto"));
        lblVBWAuto->setGeometry(QRect(18, 217, 67, 25));
        lblVBWValue = new QLabel(widget);
        lblVBWValue->setObjectName(QStringLiteral("lblVBWValue"));
        lblVBWValue->setGeometry(QRect(18, 167, 61, 25));
        VBWAutoPB = new QPushButton(widget);
        btnVBWgroup->addButton(VBWAutoPB);
        VBWAutoPB->setObjectName(QStringLiteral("VBWAutoPB"));
        VBWAutoPB->setGeometry(QRect(95, 217, 69, 30));
        VBWAutoPB->setFocusPolicy(Qt::NoFocus);
        VBWAutoPB->setCheckable(true);
        VBWAutoPB->setChecked(true);
        lblRatioValue = new QLabel(widget);
        lblRatioValue->setObjectName(QStringLiteral("lblRatioValue"));
        lblRatioValue->setGeometry(QRect(18, 268, 71, 25));
        RBWBox = new SA_Combobox(widget);
        RBWBox->setObjectName(QStringLiteral("RBWBox"));
        RBWBox->setGeometry(QRect(95, 67, 140, 30));
        RBWBox->setStyleSheet(QStringLiteral(""));
        RBWBox->setMaxVisibleItems(999);
        VBWBox = new SA_Combobox(widget);
        VBWBox->setObjectName(QStringLiteral("VBWBox"));
        VBWBox->setGeometry(QRect(95, 167, 140, 30));
        VBWBox->setStyleSheet(QStringLiteral(""));
        VBWBox->setEditable(false);
        VBWBox->setMaxVisibleItems(112);
        ratioBox = new SA_Combobox(widget);
        ratioBox->setObjectName(QStringLiteral("ratioBox"));
        ratioBox->setGeometry(QRect(95, 267, 140, 30));
        ratioBox->setStyleSheet(QStringLiteral(""));
        ratioBox->setMaxVisibleItems(999);
        lblIF = new QLabel(widget);
        lblIF->setObjectName(QStringLiteral("lblIF"));
        lblIF->setGeometry(QRect(18, 324, 71, 25));
        IF_OutPut_Box = new SA_Combobox(widget);
        IF_OutPut_Box->setObjectName(QStringLiteral("IF_OutPut_Box"));
        IF_OutPut_Box->setGeometry(QRect(95, 323, 140, 30));
        IF_OutPut_Box->setStyleSheet(QStringLiteral(""));
        IF_OutPut_Box->setMaxVisibleItems(999);
        labelWarning = new QLabel(widget);
        labelWarning->setObjectName(QStringLiteral("labelWarning"));
        labelWarning->setGeometry(QRect(20, 50, 211, 71));
        QWidget::setTabOrder(RBWBox, VBWBox);
        QWidget::setTabOrder(VBWBox, ratioBox);
        QWidget::setTabOrder(ratioBox, RBWManualPB);
        QWidget::setTabOrder(RBWManualPB, RBWAutoPB);
        QWidget::setTabOrder(RBWAutoPB, VBWManualPB);
        QWidget::setTabOrder(VBWManualPB, VBWAutoPB);
        QWidget::setTabOrder(VBWAutoPB, pb_cancel);

        retranslateUi(SA_Dialog_BWSetup);

        QMetaObject::connectSlotsByName(SA_Dialog_BWSetup);
    } // setupUi

    void retranslateUi(QWidget *SA_Dialog_BWSetup)
    {
        SA_Dialog_BWSetup->setWindowTitle(QApplication::translate("SA_Dialog_BWSetup", "Form", 0));
        SA_Dialog_BWSetup->setProperty("status", QVariant(QApplication::translate("SA_Dialog_BWSetup", "night", 0)));
        pb_cancel->setText(QString());
        lblTitle->setText(QApplication::translate("SA_Dialog_BWSetup", "Bandwidth", 0));
        RBWManualPB->setText(QApplication::translate("SA_Dialog_BWSetup", "Manual", 0));
        RBWAutoPB->setText(QApplication::translate("SA_Dialog_BWSetup", "Auto", 0));
        lblRBWAuto->setText(QApplication::translate("SA_Dialog_BWSetup", "RBW", 0));
        lblRBWValue->setText(QApplication::translate("SA_Dialog_BWSetup", "RBW", 0));
        VBWManualPB->setText(QApplication::translate("SA_Dialog_BWSetup", "Manual", 0));
        lblVBWAuto->setText(QApplication::translate("SA_Dialog_BWSetup", "VBW", 0));
        lblVBWValue->setText(QApplication::translate("SA_Dialog_BWSetup", "VBW", 0));
        VBWAutoPB->setText(QApplication::translate("SA_Dialog_BWSetup", "Auto", 0));
        lblRatioValue->setText(QApplication::translate("SA_Dialog_BWSetup", "VBW/RBW", 0));
        RBWBox->clear();
        RBWBox->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_BWSetup", "5 MHz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "3 MHz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "1 MHz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "300 kHz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "100 kHz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "30 kHz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "10 kHz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "3 kHz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "1 kHz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "300 Hz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "100 Hz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "30 Hz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "10 Hz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "3 Hz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "1 Hz", 0)
        );
        VBWBox->clear();
        VBWBox->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_BWSetup", "5 MHz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "3 MHz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "1 MHz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "300 kHz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "100 kHz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "30 kHz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "10 kHz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "3 kHz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "1 kHz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "300 Hz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "100 Hz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "30 Hz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "10 Hz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "3 Hz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "1 Hz", 0)
        );
        ratioBox->clear();
        ratioBox->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_BWSetup", "1", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "0.1", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "0.01", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "0.001", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "0.0001", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "0.00001", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "0.000001", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "0.0000001", 0)
        );
        lblIF->setText(QApplication::translate("SA_Dialog_BWSetup", "IF OutPut", 0));
        IF_OutPut_Box->clear();
        IF_OutPut_Box->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_BWSetup", "OFF", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "Narrow 10MHz", 0)
         << QApplication::translate("SA_Dialog_BWSetup", "Wide 100MHz", 0)
        );
        labelWarning->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SA_Dialog_BWSetup: public Ui_SA_Dialog_BWSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_BWSETUP_H
