/********************************************************************************
** Form generated from reading UI file 'sa_dialog_displaysetup.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_DISPLAYSETUP_H
#define UI_SA_DIALOG_DISPLAYSETUP_H

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

class Ui_SA_Dialog_DisplaySetup
{
public:
    QWidget *widget;
    QLabel *lblTitle;
    QPushButton *pb_cancel;
    QFrame *line;
    QPushButton *pb_conti;
    QPushButton *pb_single;
    QLabel *lblSweepMode;
    QPushButton *pb_Sweep_Once;
    QLabel *lbl_Speed;
    QPushButton *pb_Speed_Normal;
    QPushButton *pb_Speed_Fast;
    SA_LineEdit *edit_SweepTime;
    QLabel *lblSweepTime;
    QPushButton *pb_SweepTime_Auto;
    QPushButton *pb_SweepTime_Manual;
    QLabel *lblSweepTime_2;
    SA_LineEdit *edit_DotSweepTime;
    QPushButton *pb_DotSweepTime_Manual;
    QPushButton *pb_DotSweepTime_Auto;
    QPushButton *pb_FixedDotSweepTime;
    QLabel *lblFixedDotSweepTime;
    QPushButton *pb_DoorCtrlSweep;
    QButtonGroup *buttonGroup_2;
    QButtonGroup *buttonGroup;
    QButtonGroup *TypeGroup;

    void setupUi(QWidget *SA_Dialog_DisplaySetup)
    {
        if (SA_Dialog_DisplaySetup->objectName().isEmpty())
            SA_Dialog_DisplaySetup->setObjectName(QStringLiteral("SA_Dialog_DisplaySetup"));
        SA_Dialog_DisplaySetup->resize(252, 645);
        SA_Dialog_DisplaySetup->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] \n"
"#widget>#pb_Sweep_Once\n"
"{\n"
"	background-color:rgb(0,0,0);\n"
"	color:rgb(255,255,255);\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] \n"
"#widget>QPushButton\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	border-style:flat;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] \n"
"#widget>QPushButton:checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] \n"
"#widget{\n"
"background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] \n"
"#widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] \n"
"#widget>#lblTitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"i"
                        "ndoor\"] \n"
"#pb_cancel\n"
"{\n"
"border-style:flat;\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] \n"
"#pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] \n"
"#line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] \n"
"SA_LineEdit\n"
"{\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] \n"
"SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] \n"
"QComboBox\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(162, 115, 0, 1);\n"
"	padding:8px 23px 7px 10px;\n"
"	combobox-popup: 0;\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/ima"
                        "ge/dropdown_normal.png);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] \n"
"QComboBox:focus\n"
"{\n"
"	background-image: url(:/sa/image/dropdown_click.png);\n"
"	\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] \n"
"QComboBox::drop-down {\n"
"width:30px;	\n"
"border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] \n"
"QComboBox QAbstractItemView{\n"
"   font: 75 14px \"Arial\";\n"
"	color:rgba(0, 0, 0, 1);\n"
"	background:rgba(255,255,255,1);\n"
" outline:0px;\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] \n"
"QAbstractItemView::item{\n"
"	padding-left:8px;\n"
"	width:140px;\n"
"	height:33px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] \n"
"QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(240, 179, 29, 1); \n"
"}\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] \n"
"#widget>#pb_Sweep_Once\n"
"{\n"
"	background-color:rgb(0,0,0);\n"
"	c"
                        "olor:rgb(255,255,255);\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] \n"
"#widget>QPushButton\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	border-style:flat;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] \n"
"#widget>QPushButton:checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] \n"
"#widget{\n"
"background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] \n"
"#widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] \n"
"#widget>#lblTitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] \n"
"#pb_cancel\n"
"{\n"
"border-style:flat;\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_Di"
                        "splaySetup[status  =  \"outdoor\"] \n"
"#pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] \n"
"#line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] \n"
"SA_LineEdit\n"
"{\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] \n"
"SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] \n"
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
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] \n"
"QComboBox:focus\n"
"{\n"
"	background-image: url(:/sa/image/dropdown_click.p"
                        "ng);\n"
"	\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] \n"
"QComboBox::drop-down {\n"
"width:30px;	\n"
"border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] \n"
"QComboBox QAbstractItemView{\n"
"   font: 75 14px \"Arial\";\n"
"	color:rgba(0, 0, 0, 1);\n"
"	background:rgba(255,255,255,1);\n"
" outline:0px;\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] \n"
"QAbstractItemView::item{\n"
"	padding-left:8px;\n"
"	width:140px;\n"
"	height:33px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] \n"
"QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(240, 179, 29, 1); \n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] \n"
"#widget>#pb_Sweep_Once\n"
"{\n"
"	background-color:rgb(0,0,0);\n"
"	color:rgb(255,255,255);\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] \n"
"#widget>QPushButton\n"
"{\n"
"	color:rgba(121,106,81,1);\n"
"	border-"
                        "style:flat;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] \n"
"#widget>QPushButton:checked\n"
"{\n"
"	color:rgba(85,74,56,1);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] \n"
"#widget{\n"
"	background-color:rgba(208,182,139,0.9);\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] \n"
"#widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] \n"
"#widget>#lblTitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] \n"
"#pb_cancel\n"
"{\n"
"border-style:flat;\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/night/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] \n"
"#pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/night/btn_close_click.png);\n"
"}\n"
"#SA_Dialog_DisplaySetup[statu"
                        "s  =  \"night\"] \n"
"#line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] \n"
"SA_LineEdit\n"
"{\n"
"	background-color: rgba(251,220,167,0.60);\n"
"	color:rgba(159,98,0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] \n"
"SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] \n"
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
"#SA_Dialog_DisplaySetup[status  =  \"night\"] \n"
"QComboBox:focus\n"
"{\n"
"	background-image: url(:/sa/image/dropdown_click.png);\n"
"	\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] \n"
"QComboBox::drop-down {\n"
"width:30px;	\n"
"border-st"
                        "yle:flat;\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] \n"
"QComboBox QAbstractItemView{\n"
"   font: 75 14px \"Arial\";\n"
"	color:rgba(0, 0, 0, 1);\n"
"	background:rgba(255,255,255,1);\n"
" outline:0px;\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] \n"
"QAbstractItemView::item{\n"
"	padding-left:8px;\n"
"	width:140px;\n"
"	height:33px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] \n"
"QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(240, 179, 29, 1); \n"
"}\n"
"\n"
""));
        widget = new QWidget(SA_Dialog_DisplaySetup);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 252, 646));
        widget->setStyleSheet(QStringLiteral(""));
        lblTitle = new QLabel(widget);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));
        lblTitle->setGeometry(QRect(17, 19, 98, 22));
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
        line = new QFrame(widget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(18, 46, 212, 2));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        pb_conti = new QPushButton(widget);
        TypeGroup = new QButtonGroup(SA_Dialog_DisplaySetup);
        TypeGroup->setObjectName(QStringLiteral("TypeGroup"));
        TypeGroup->addButton(pb_conti);
        pb_conti->setObjectName(QStringLiteral("pb_conti"));
        pb_conti->setGeometry(QRect(94, 162, 69, 30));
        pb_conti->setFocusPolicy(Qt::NoFocus);
        pb_conti->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] QPushButton:checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] QPushButton:!checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] QPushButton:checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] QPushButton:!checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] QPushButton:checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/im"
                        "age/night/btn_left_click.png);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] QPushButton:!checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/night/btn_left_nor.png);\n"
"}"));
        pb_conti->setCheckable(true);
        pb_conti->setChecked(true);
        pb_conti->setAutoExclusive(true);
        pb_single = new QPushButton(widget);
        TypeGroup->addButton(pb_single);
        pb_single->setObjectName(QStringLiteral("pb_single"));
        pb_single->setGeometry(QRect(165, 162, 69, 30));
        pb_single->setFocusPolicy(Qt::NoFocus);
        pb_single->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] QPushButton:checked\n"
"{\n"
"padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] QPushButton:!checked\n"
"{\n"
"padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] QPushButton:checked\n"
"{\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] QPushButton:!checked\n"
"{\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_"
                        "DisplaySetup[status  =  \"night\"] QPushButton:checked\n"
"{\n"
"padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/night/btn_right_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] QPushButton:!checked\n"
"{\n"
"padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/night/btn_right_nor.png);\n"
"}"));
        pb_single->setCheckable(true);
        pb_single->setAutoExclusive(true);
        lblSweepMode = new QLabel(widget);
        lblSweepMode->setObjectName(QStringLiteral("lblSweepMode"));
        lblSweepMode->setGeometry(QRect(18, 162, 68, 30));
        lblSweepMode->setStyleSheet(QStringLiteral(""));
        pb_Sweep_Once = new QPushButton(widget);
        pb_Sweep_Once->setObjectName(QStringLiteral("pb_Sweep_Once"));
        pb_Sweep_Once->setGeometry(QRect(17, 212, 216, 30));
        pb_Sweep_Once->setFocusPolicy(Qt::NoFocus);
        pb_Sweep_Once->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(255, 255, 255, 1);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"	text-align:center;\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(0, 0, 0, 1);\n"
"	border-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"	text-align:center;\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/sa/image/outdoor/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] QPushButton\n"
"{\n"
""
                        "	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color: #FBDBA7;\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"	text-align:center;\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/btn_w216_click.png);\n"
"}"));
        lbl_Speed = new QLabel(widget);
        lbl_Speed->setObjectName(QStringLiteral("lbl_Speed"));
        lbl_Speed->setGeometry(QRect(284, 262, 68, 30));
        pb_Speed_Normal = new QPushButton(widget);
        buttonGroup_2 = new QButtonGroup(SA_Dialog_DisplaySetup);
        buttonGroup_2->setObjectName(QStringLiteral("buttonGroup_2"));
        buttonGroup_2->addButton(pb_Speed_Normal);
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
        buttonGroup_2->addButton(pb_Speed_Fast);
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
        edit_SweepTime = new SA_LineEdit(widget);
        edit_SweepTime->setObjectName(QStringLiteral("edit_SweepTime"));
        edit_SweepTime->setGeometry(QRect(94, 112, 140, 30));
        edit_SweepTime->setReadOnly(true);
        lblSweepTime = new QLabel(widget);
        lblSweepTime->setObjectName(QStringLiteral("lblSweepTime"));
        lblSweepTime->setGeometry(QRect(18, 67, 68, 30));
        pb_SweepTime_Auto = new QPushButton(widget);
        buttonGroup = new QButtonGroup(SA_Dialog_DisplaySetup);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(pb_SweepTime_Auto);
        pb_SweepTime_Auto->setObjectName(QStringLiteral("pb_SweepTime_Auto"));
        pb_SweepTime_Auto->setGeometry(QRect(94, 68, 69, 30));
        pb_SweepTime_Auto->setFocusPolicy(Qt::NoFocus);
        pb_SweepTime_Auto->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] QPushButton:checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] QPushButton:!checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] QPushButton:checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] QPushButton:!checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] QPushButton:checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/im"
                        "age/night/btn_left_click.png);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] QPushButton:!checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/night/btn_left_nor.png);\n"
"}"));
        pb_SweepTime_Auto->setCheckable(true);
        pb_SweepTime_Auto->setChecked(true);
        pb_SweepTime_Auto->setAutoExclusive(true);
        pb_SweepTime_Manual = new QPushButton(widget);
        buttonGroup->addButton(pb_SweepTime_Manual);
        pb_SweepTime_Manual->setObjectName(QStringLiteral("pb_SweepTime_Manual"));
        pb_SweepTime_Manual->setGeometry(QRect(165, 68, 69, 30));
        pb_SweepTime_Manual->setFocusPolicy(Qt::NoFocus);
        pb_SweepTime_Manual->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] QPushButton:checked\n"
"{\n"
"padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] QPushButton:!checked\n"
"{\n"
"padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] QPushButton:checked\n"
"{\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] QPushButton:!checked\n"
"{\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_"
                        "DisplaySetup[status  =  \"night\"] QPushButton:checked\n"
"{\n"
"padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/night/btn_right_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] QPushButton:!checked\n"
"{\n"
"padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/night/btn_right_nor.png);\n"
"}"));
        pb_SweepTime_Manual->setCheckable(true);
        pb_SweepTime_Manual->setAutoExclusive(true);
        lblSweepTime_2 = new QLabel(widget);
        lblSweepTime_2->setObjectName(QStringLiteral("lblSweepTime_2"));
        lblSweepTime_2->setGeometry(QRect(18, 333, 68, 51));
        edit_DotSweepTime = new SA_LineEdit(widget);
        edit_DotSweepTime->setObjectName(QStringLiteral("edit_DotSweepTime"));
        edit_DotSweepTime->setGeometry(QRect(94, 388, 140, 30));
        edit_DotSweepTime->setReadOnly(true);
        pb_DotSweepTime_Manual = new QPushButton(widget);
        pb_DotSweepTime_Manual->setObjectName(QStringLiteral("pb_DotSweepTime_Manual"));
        pb_DotSweepTime_Manual->setGeometry(QRect(165, 343, 69, 30));
        pb_DotSweepTime_Manual->setFocusPolicy(Qt::NoFocus);
        pb_DotSweepTime_Manual->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] QPushButton:checked\n"
"{\n"
"padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] QPushButton:!checked\n"
"{\n"
"padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] QPushButton:checked\n"
"{\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] QPushButton:!checked\n"
"{\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_"
                        "DisplaySetup[status  =  \"night\"] QPushButton:checked\n"
"{\n"
"padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/night/btn_right_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] QPushButton:!checked\n"
"{\n"
"padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/night/btn_right_nor.png);\n"
"}"));
        pb_DotSweepTime_Manual->setCheckable(true);
        pb_DotSweepTime_Manual->setAutoExclusive(true);
        pb_DotSweepTime_Auto = new QPushButton(widget);
        pb_DotSweepTime_Auto->setObjectName(QStringLiteral("pb_DotSweepTime_Auto"));
        pb_DotSweepTime_Auto->setGeometry(QRect(94, 343, 69, 30));
        pb_DotSweepTime_Auto->setFocusPolicy(Qt::NoFocus);
        pb_DotSweepTime_Auto->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] QPushButton:checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] QPushButton:!checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] QPushButton:checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] QPushButton:!checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] QPushButton:checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/im"
                        "age/night/btn_left_click.png);\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] QPushButton:!checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/night/btn_left_nor.png);\n"
"}"));
        pb_DotSweepTime_Auto->setCheckable(true);
        pb_DotSweepTime_Auto->setChecked(true);
        pb_DotSweepTime_Auto->setAutoExclusive(true);
        pb_FixedDotSweepTime = new QPushButton(widget);
        pb_FixedDotSweepTime->setObjectName(QStringLiteral("pb_FixedDotSweepTime"));
        pb_FixedDotSweepTime->setGeometry(QRect(94, 280, 90, 30));
        pb_FixedDotSweepTime->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] #pb_FixedDotSweepTime\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] #pb_FixedDotSweepTime:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] #pb_FixedDotSweepTime:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] #pb_FixedDotSweepTime\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] #pb_FixedDotSweepTime:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, "
                        "87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] #pb_FixedDotSweepTime:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] #pb_FixedDotSweepTime\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] #pb_FixedDotSweepTime:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] #pb_FixedDotSweepTime:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(121,106,80,1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}"));
        pb_FixedDotSweepTime->setCheckable(true);
        lblFixedDotSweepTime = new QLabel(widget);
        lblFixedDotSweepTime->setObjectName(QStringLiteral("lblFixedDotSweepTime"));
        lblFixedDotSweepTime->setGeometry(QRect(18, 277, 68, 41));
        lblFixedDotSweepTime->setStyleSheet(QStringLiteral(""));
        pb_DoorCtrlSweep = new QPushButton(widget);
        pb_DoorCtrlSweep->setObjectName(QStringLiteral("pb_DoorCtrlSweep"));
        pb_DoorCtrlSweep->setGeometry(QRect(20, 510, 216, 30));
        pb_DoorCtrlSweep->setFocusPolicy(Qt::NoFocus);
        pb_DoorCtrlSweep->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(255, 255, 255, 1);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"	text-align:center;\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"indoor\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(0, 0, 0, 1);\n"
"	border-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"	text-align:center;\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/sa/image/outdoor/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] QPushButton\n"
"{\n"
""
                        "	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color: #FBDBA7;\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"	text-align:center;\n"
"}\n"
"\n"
"#SA_Dialog_DisplaySetup[status  =  \"night\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/btn_w216_click.png);\n"
"}"));

        retranslateUi(SA_Dialog_DisplaySetup);

        QMetaObject::connectSlotsByName(SA_Dialog_DisplaySetup);
    } // setupUi

    void retranslateUi(QWidget *SA_Dialog_DisplaySetup)
    {
        SA_Dialog_DisplaySetup->setWindowTitle(QApplication::translate("SA_Dialog_DisplaySetup", "Form", 0));
        SA_Dialog_DisplaySetup->setProperty("status", QVariant(QApplication::translate("SA_Dialog_DisplaySetup", "night", 0)));
        lblTitle->setText(QApplication::translate("SA_Dialog_DisplaySetup", "Sweep", 0));
        pb_cancel->setText(QString());
        pb_conti->setText(QApplication::translate("SA_Dialog_DisplaySetup", "Cont", 0));
        pb_single->setText(QApplication::translate("SA_Dialog_DisplaySetup", "Single", 0));
        lblSweepMode->setText(QApplication::translate("SA_Dialog_DisplaySetup", "Sweep\n"
"Mode", 0));
        pb_Sweep_Once->setText(QApplication::translate("SA_Dialog_DisplaySetup", "Sweep Once", 0));
        lbl_Speed->setText(QApplication::translate("SA_Dialog_DisplaySetup", "Sweep\n"
"Speed", 0));
        pb_Speed_Normal->setText(QApplication::translate("SA_Dialog_DisplaySetup", "Normal", 0));
        pb_Speed_Fast->setText(QApplication::translate("SA_Dialog_DisplaySetup", "Fast", 0));
        edit_SweepTime->setText(QApplication::translate("SA_Dialog_DisplaySetup", "40 ms", 0));
        lblSweepTime->setText(QApplication::translate("SA_Dialog_DisplaySetup", "Sweep\n"
"Time", 0));
        pb_SweepTime_Auto->setText(QApplication::translate("SA_Dialog_DisplaySetup", "Auto", 0));
        pb_SweepTime_Manual->setText(QApplication::translate("SA_Dialog_DisplaySetup", "Manual", 0));
        lblSweepTime_2->setText(QApplication::translate("SA_Dialog_DisplaySetup", "Dot\n"
"Sweep\n"
"Time", 0));
        edit_DotSweepTime->setText(QString());
        pb_DotSweepTime_Manual->setText(QApplication::translate("SA_Dialog_DisplaySetup", "Manual", 0));
        pb_DotSweepTime_Auto->setText(QApplication::translate("SA_Dialog_DisplaySetup", "Auto", 0));
        pb_FixedDotSweepTime->setText(QApplication::translate("SA_Dialog_DisplaySetup", "Off", 0));
        lblFixedDotSweepTime->setText(QApplication::translate("SA_Dialog_DisplaySetup", "Fast\n"
"Sweep\n"
"Mode", 0));
        pb_DoorCtrlSweep->setText(QApplication::translate("SA_Dialog_DisplaySetup", "Gated Sweep", 0));
    } // retranslateUi

};

namespace Ui {
    class SA_Dialog_DisplaySetup: public Ui_SA_Dialog_DisplaySetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_DISPLAYSETUP_H
