/********************************************************************************
** Form generated from reading UI file 'sa_dialog_specem.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_SPECEM_H
#define UI_SA_DIALOG_SPECEM_H

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

class Ui_SA_Dialog_SpecEM
{
public:
    QWidget *widget;
    QLabel *lblTitle;
    QPushButton *pb_cancel;
    QFrame *line;
    QLabel *lbl_Speed;
    QPushButton *pb_Speed_Normal;
    QPushButton *pb_Speed_Fast;
    SA_Combobox *MaskBox;
    QLabel *lblVBWValue_3;
    SA_LineEdit *ChBwEdit;
    SA_LineEdit *BSPowerEdit;
    QLabel *lblBSPowerValue;
    QLabel *lblVBWValue_5;
    QPushButton *pb_Display_Abs;
    QPushButton *pb_Display_IntePwr;
    QPushButton *pb_Display_Ref;
    QPushButton *pb_ref_SpecPk;
    QPushButton *pb_ref_PSD;
    QPushButton *pb_ref_TotalPwr;
    QLabel *label_22;
    SA_Combobox *RefBox;
    QLabel *label_23;
    SA_Combobox *DisplayBox;
    QButtonGroup *buttonGroup_2;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *SA_Dialog_SpecEM)
    {
        if (SA_Dialog_SpecEM->objectName().isEmpty())
            SA_Dialog_SpecEM->setObjectName(QStringLiteral("SA_Dialog_SpecEM"));
        SA_Dialog_SpecEM->resize(251, 646);
        SA_Dialog_SpecEM->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_SpecEM[status  =  \"indoor\"] \n"
"QComboBox\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(162, 115, 0, 1);\n"
"	padding:8px 23px 7px 10px;\n"
"	combobox-popup: 0;\n"
"	border-style:flat;\n"
"	border-image: url(:/sa/image/dropdown_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"indoor\"] \n"
"QComboBox:focus\n"
"{\n"
"	border-image: url(:/sa/image/dropdown_click.png);\n"
"	\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"indoor\"] \n"
"QComboBox::drop-down {\n"
"width: 0px;	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"indoor\"] \n"
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
"#SA_Dialog_SpecEM[status  =  \"indoor\"] \n"
"QAbstractItemView::item{\n"
"	padding-left:8px;\n"
"	width:140px;\n"
""
                        "	height:32px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"indoor\"] \n"
"QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(240, 179, 29, 1); \n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"indoor\"] SA_LineEdit,\n"
"#SA_Dialog_SpecEM[status  =  \"indoor\"] SA_LineEdit:disable\n"
"{	\n"
"	background:rgba(255,255,255,1);	\n"
"	color:rgba(159,98,0,1);\n"
"	padding:8px 6px 7px 6px ;	\n"
"	font: 75 12px \"Arial\";	\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_SpecEM[status  =  \"indoor\"] SA_LineEdit:focus\n"
"{	\n"
"	outline: none;	\n"
"	border:2px solid rgba(162,115,0,1);	\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_SpecEM[status  =  \"outdoor\"] \n"
"QComboBox\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(162, 115, 0, 1);\n"
"	padding:8px 23px 7px 10px;\n"
"	combobox-popup: 0;\n"
"	border-style:flat;\n"
"	border-image: url(:/sa/image/dropdown_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_S"
                        "pecEM[status  =  \"outdoor\"] \n"
"QComboBox:focus\n"
"{\n"
"	border-image: url(:/sa/image/dropdown_click.png);\n"
"	\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"outdoor\"] \n"
"QComboBox::drop-down {\n"
"width: 0px;	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"outdoor\"] \n"
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
"#SA_Dialog_SpecEM[status  =  \"outdoor\"] \n"
"QAbstractItemView::item{\n"
"	padding-left:8px;\n"
"	width:140px;\n"
"	height:32px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"outdoor\"] \n"
"QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(240, 179, 29, 1); \n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"outdoor\"] SA_LineEdit,\n"
"#SA_Dialog_SpecEM[status  =  \"outdoor\"] SA_LineEdit:disable\n"
"{	\n"
"	background:rgba(255,255,"
                        "255,1);	\n"
"	color:rgba(162, 115, 0,1);	\n"
"	padding:8px 6px 7px 6px ;	\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"outdoor\"] SA_LineEdit:focus\n"
"{	\n"
"	outline: none;	\n"
"	border:2px solid rgba(162,115,0,1);	\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"/*******************night**********************/\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] \n"
"QComboBox\n"
"{\n"
"	background-color: rgba(251,220,167,0.60);\n"
"	color:rgba(159,98,0,1);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	padding:8px 23px 7px 10px;\n"
"	combobox-popup: 0;\n"
"	border-style:flat;\n"
"	border-image: url(:/sa/image/night/dropdown_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] \n"
"QComboBox:focus\n"
"{\n"
"	border-image: url(:/sa/image/night/dropdown_click.png);\n"
"	\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] \n"
"QComboBox::drop-down {\n"
"width: 0px;	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] \n"
""
                        "QComboBox QAbstractItemView{\n"
"   font: 75 14px \"Arial\";\n"
"	color:rgba(0, 0, 0, 1);\n"
"	background-color: #FBDBA7;\n"
" 	outline:0px;\n"
"	border-style:solid;\n"
"	border-color:rgba(151, 151, 151, 1);\n"
"	border-width:1px;\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] \n"
"QAbstractItemView::item{\n"
"	padding-left:8px;\n"
"	width:140px;\n"
"	height:32px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] \n"
"QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(159,98,0,1);\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] SA_LineEdit,\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] SA_LineEdit:disable\n"
"{	\n"
"	background: rgba(251,220,167,0.60);	\n"
"	color:rgba(162, 115, 0,1);	\n"
"	padding:8px 6px 7px 6px ;	\n"
"	font: 75 13px \"Arial\";	\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] SA_LineEdit:focus\n"
"{	\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);	\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"\n"
""));
        widget = new QWidget(SA_Dialog_SpecEM);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 252, 646));
        widget->setStyleSheet(QLatin1String("\n"
"\n"
"#widget>QPushButton\n"
"{\n"
"	/*color:rgb(255,255,255);*/\n"
"}\n"
"\n"
"#widget>QPushButton\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	border-style:flat;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#widget>QPushButton:checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"}\n"
"\n"
"\n"
"#widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
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
"#SA_Dialog_SpecEM[status = \"indoor\"] #widget\n"
"{\n"
"background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#SA_Dialog_SpecEM[status = \"outdoor\"] #widget{\n"
"background-color:rgba"
                        "(211,211,211,0.9);\n"
"}\n"
"#SA_Dialog_SpecEM[status = \"night\"] #widget\n"
"{\n"
"	background-color:rgba(208,182,139,0.9);\n"
"}\n"
""));
        lblTitle = new QLabel(widget);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));
        lblTitle->setGeometry(QRect(17, 19, 158, 22));
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
"#SA_Dialog_SpecEM[status  =  \"indoor\"] QPushButton\n"
"{\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_SpecEM[status  =  \"indoor\"] QPushButton:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_SpecEM[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_SpecEM[status  =  \"outdoor\"] QPushButton:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] QPushButton\n"
"{\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/night/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] QPushButton:pressed\n"
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
        MaskBox = new SA_Combobox(widget);
        MaskBox->setObjectName(QStringLiteral("MaskBox"));
        MaskBox->setGeometry(QRect(20, 100, 201, 30));
        MaskBox->setStyleSheet(QStringLiteral(""));
        MaskBox->setEditable(false);
        MaskBox->setMaxVisibleItems(112);
        lblVBWValue_3 = new QLabel(widget);
        lblVBWValue_3->setObjectName(QStringLiteral("lblVBWValue_3"));
        lblVBWValue_3->setGeometry(QRect(10, 140, 81, 25));
        ChBwEdit = new SA_LineEdit(widget);
        ChBwEdit->setObjectName(QStringLiteral("ChBwEdit"));
        ChBwEdit->setGeometry(QRect(20, 170, 201, 31));
        BSPowerEdit = new SA_LineEdit(widget);
        BSPowerEdit->setObjectName(QStringLiteral("BSPowerEdit"));
        BSPowerEdit->setGeometry(QRect(20, 240, 201, 31));
        lblBSPowerValue = new QLabel(widget);
        lblBSPowerValue->setObjectName(QStringLiteral("lblBSPowerValue"));
        lblBSPowerValue->setGeometry(QRect(10, 210, 211, 25));
        lblVBWValue_5 = new QLabel(widget);
        lblVBWValue_5->setObjectName(QStringLiteral("lblVBWValue_5"));
        lblVBWValue_5->setGeometry(QRect(10, 70, 81, 25));
        pb_Display_Abs = new QPushButton(SA_Dialog_SpecEM);
        buttonGroup = new QButtonGroup(SA_Dialog_SpecEM);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(pb_Display_Abs);
        pb_Display_Abs->setObjectName(QStringLiteral("pb_Display_Abs"));
        pb_Display_Abs->setGeometry(QRect(260, 110, 216, 30));
        pb_Display_Abs->setFocusPolicy(Qt::NoFocus);
        pb_Display_Abs->setStyleSheet(QLatin1String("/**********************indoor************************/\n"
"#SA_Dialog_SpecEM[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	color:white;\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"indoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"/**********************outdoor************************/\n"
"#SA_Dialog_SpecEM[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	color:white;\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"outdoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"/**********************night************************/\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] QPushButton\n"
"{\n"
"	color: #FBDBA7;\n"
"	border-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] QPushButton:checked\n"
"{\n"
"	color:rgba(252, 220, 168, 1);\n"
"	border-image: url(:/sa/"
                        "image/night/btn_w216_click.png);\n"
"}"));
        pb_Display_Abs->setCheckable(true);
        pb_Display_IntePwr = new QPushButton(SA_Dialog_SpecEM);
        buttonGroup->addButton(pb_Display_IntePwr);
        pb_Display_IntePwr->setObjectName(QStringLiteral("pb_Display_IntePwr"));
        pb_Display_IntePwr->setGeometry(QRect(260, 190, 216, 30));
        pb_Display_IntePwr->setFocusPolicy(Qt::NoFocus);
        pb_Display_IntePwr->setStyleSheet(QLatin1String("/**********************indoor************************/\n"
"#SA_Dialog_SpecEM[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	color:white;\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"indoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"/**********************outdoor************************/\n"
"#SA_Dialog_SpecEM[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	color:white;\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"outdoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"/**********************night************************/\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] QPushButton\n"
"{\n"
"	color: #FBDBA7;\n"
"	border-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] QPushButton:checked\n"
"{\n"
"	color:rgba(252, 220, 168, 1);\n"
"	border-image: url(:/sa/"
                        "image/night/btn_w216_click.png);\n"
"}"));
        pb_Display_IntePwr->setCheckable(true);
        pb_Display_Ref = new QPushButton(SA_Dialog_SpecEM);
        buttonGroup->addButton(pb_Display_Ref);
        pb_Display_Ref->setObjectName(QStringLiteral("pb_Display_Ref"));
        pb_Display_Ref->setGeometry(QRect(260, 150, 216, 30));
        pb_Display_Ref->setFocusPolicy(Qt::NoFocus);
        pb_Display_Ref->setStyleSheet(QLatin1String("/**********************indoor************************/\n"
"#SA_Dialog_SpecEM[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	color:white;\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"indoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"/**********************outdoor************************/\n"
"#SA_Dialog_SpecEM[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	color:white;\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"outdoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"/**********************night************************/\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] QPushButton\n"
"{\n"
"	color: #FBDBA7;\n"
"	border-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] QPushButton:checked\n"
"{\n"
"	color:rgba(252, 220, 168, 1);\n"
"	border-image: url(:/sa/"
                        "image/night/btn_w216_click.png);\n"
"}"));
        pb_Display_Ref->setCheckable(true);
        pb_ref_SpecPk = new QPushButton(SA_Dialog_SpecEM);
        buttonGroup_2 = new QButtonGroup(SA_Dialog_SpecEM);
        buttonGroup_2->setObjectName(QStringLiteral("buttonGroup_2"));
        buttonGroup_2->addButton(pb_ref_SpecPk);
        pb_ref_SpecPk->setObjectName(QStringLiteral("pb_ref_SpecPk"));
        pb_ref_SpecPk->setGeometry(QRect(270, 350, 216, 30));
        pb_ref_SpecPk->setFocusPolicy(Qt::NoFocus);
        pb_ref_SpecPk->setStyleSheet(QLatin1String("/**********************indoor************************/\n"
"#SA_Dialog_SpecEM[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	color:white;\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"indoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"/**********************outdoor************************/\n"
"#SA_Dialog_SpecEM[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	color:white;\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"outdoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"/**********************night************************/\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] QPushButton\n"
"{\n"
"	color: #FBDBA7;\n"
"	border-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] QPushButton:checked\n"
"{\n"
"	color:rgba(252, 220, 168, 1);\n"
"	border-image: url(:/sa/"
                        "image/night/btn_w216_click.png);\n"
"}\n"
""));
        pb_ref_SpecPk->setCheckable(true);
        pb_ref_PSD = new QPushButton(SA_Dialog_SpecEM);
        buttonGroup_2->addButton(pb_ref_PSD);
        pb_ref_PSD->setObjectName(QStringLiteral("pb_ref_PSD"));
        pb_ref_PSD->setGeometry(QRect(270, 310, 216, 30));
        pb_ref_PSD->setFocusPolicy(Qt::NoFocus);
        pb_ref_PSD->setStyleSheet(QLatin1String("/**********************indoor************************/\n"
"#SA_Dialog_SpecEM[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	color:white;\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"indoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"/**********************outdoor************************/\n"
"#SA_Dialog_SpecEM[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	color:white;\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"outdoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"/**********************night************************/\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] QPushButton\n"
"{\n"
"	color: #FBDBA7;\n"
"	border-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] QPushButton:checked\n"
"{\n"
"	color:rgba(252, 220, 168, 1);\n"
"	border-image: url(:/sa/"
                        "image/night/btn_w216_click.png);\n"
"}"));
        pb_ref_PSD->setCheckable(true);
        pb_ref_TotalPwr = new QPushButton(SA_Dialog_SpecEM);
        buttonGroup_2->addButton(pb_ref_TotalPwr);
        pb_ref_TotalPwr->setObjectName(QStringLiteral("pb_ref_TotalPwr"));
        pb_ref_TotalPwr->setGeometry(QRect(270, 270, 216, 30));
        pb_ref_TotalPwr->setFocusPolicy(Qt::NoFocus);
        pb_ref_TotalPwr->setStyleSheet(QLatin1String("/**********************indoor************************/\n"
"#SA_Dialog_SpecEM[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	color:white;\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"indoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"/**********************outdoor************************/\n"
"#SA_Dialog_SpecEM[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	color:white;\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"outdoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"/**********************night************************/\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] QPushButton\n"
"{\n"
"	color: #FBDBA7;\n"
"	border-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_SpecEM[status  =  \"night\"] QPushButton:checked\n"
"{\n"
"	color:rgba(252, 220, 168, 1);\n"
"	border-image: url(:/sa/"
                        "image/night/btn_w216_click.png);\n"
"}"));
        pb_ref_TotalPwr->setCheckable(true);
        label_22 = new QLabel(SA_Dialog_SpecEM);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(290, 420, 111, 15));
        RefBox = new SA_Combobox(SA_Dialog_SpecEM);
        RefBox->setObjectName(QStringLiteral("RefBox"));
        RefBox->setGeometry(QRect(290, 490, 216, 30));
        RefBox->setStyleSheet(QStringLiteral(""));
        RefBox->setEditable(false);
        RefBox->setMaxVisibleItems(112);
        label_23 = new QLabel(SA_Dialog_SpecEM);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(288, 470, 111, 15));
        DisplayBox = new SA_Combobox(SA_Dialog_SpecEM);
        DisplayBox->setObjectName(QStringLiteral("DisplayBox"));
        DisplayBox->setGeometry(QRect(290, 440, 216, 30));
        DisplayBox->setStyleSheet(QStringLiteral(""));
        DisplayBox->setEditable(false);
        DisplayBox->setMaxVisibleItems(112);

        retranslateUi(SA_Dialog_SpecEM);

        QMetaObject::connectSlotsByName(SA_Dialog_SpecEM);
    } // setupUi

    void retranslateUi(QWidget *SA_Dialog_SpecEM)
    {
        SA_Dialog_SpecEM->setWindowTitle(QApplication::translate("SA_Dialog_SpecEM", "Form", 0));
        lblTitle->setText(QApplication::translate("SA_Dialog_SpecEM", "SEM", 0));
        pb_cancel->setText(QString());
        lbl_Speed->setText(QApplication::translate("SA_Dialog_SpecEM", "Sweep\n"
"Speed", 0));
        pb_Speed_Normal->setText(QApplication::translate("SA_Dialog_SpecEM", "Normal", 0));
        pb_Speed_Fast->setText(QApplication::translate("SA_Dialog_SpecEM", "Fast", 0));
        MaskBox->clear();
        MaskBox->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_SpecEM", "Cat A, > 3 GHz", 0)
         << QApplication::translate("SA_Dialog_SpecEM", "Cat B, > 3 GHz", 0)
         << QApplication::translate("SA_Dialog_SpecEM", " 31< P < 38 dBm, > 3 GHz", 0)
         << QApplication::translate("SA_Dialog_SpecEM", " P < 31 dBm, > 3 GHz", 0)
        );
        lblVBWValue_3->setText(QApplication::translate("SA_Dialog_SpecEM", "REF CH BW", 0));
        lblBSPowerValue->setText(QApplication::translate("SA_Dialog_SpecEM", "BS Power (31dBm <P<=38dBm)", 0));
        lblVBWValue_5->setText(QApplication::translate("SA_Dialog_SpecEM", "Select Mask", 0));
        pb_Display_Abs->setText(QApplication::translate("SA_Dialog_SpecEM", "Abs Peak Pwr && Freq", 0));
        pb_Display_IntePwr->setText(QApplication::translate("SA_Dialog_SpecEM", "Integrated Power", 0));
        pb_Display_Ref->setText(QApplication::translate("SA_Dialog_SpecEM", "Rel Peak Pwr && Freq", 0));
        pb_ref_SpecPk->setText(QApplication::translate("SA_Dialog_SpecEM", "Spectrum Pk Ref", 0));
        pb_ref_PSD->setText(QApplication::translate("SA_Dialog_SpecEM", "PSD Ref", 0));
        pb_ref_TotalPwr->setText(QApplication::translate("SA_Dialog_SpecEM", "Total Pwr Ref", 0));
        label_22->setText(QApplication::translate("SA_Dialog_SpecEM", "Display Type", 0));
        RefBox->clear();
        RefBox->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_SpecEM", "Total Pwr Ref", 0)
         << QApplication::translate("SA_Dialog_SpecEM", "PSD Ref", 0)
         << QApplication::translate("SA_Dialog_SpecEM", "Spectrum Pk Ref", 0)
        );
        label_23->setText(QApplication::translate("SA_Dialog_SpecEM", "Reference Type", 0));
        DisplayBox->clear();
        DisplayBox->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_SpecEM", "Abs Peak Pwr & Freq", 0)
         << QApplication::translate("SA_Dialog_SpecEM", "Rel Peak Pwr & Freq", 0)
         << QApplication::translate("SA_Dialog_SpecEM", "Integrated Power", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class SA_Dialog_SpecEM: public Ui_SA_Dialog_SpecEM {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_SPECEM_H
