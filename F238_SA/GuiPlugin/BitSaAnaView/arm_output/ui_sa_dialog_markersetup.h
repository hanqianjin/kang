/********************************************************************************
** Form generated from reading UI file 'sa_dialog_markersetup.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_MARKERSETUP_H
#define UI_SA_DIALOG_MARKERSETUP_H

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

class Ui_SA_Dialog_MarkerSetup
{
public:
    QWidget *widget;
    QLabel *lblTitle;
    QPushButton *pb_cancel;
    QLabel *label;
    QFrame *line;
    QPushButton *pb_M6;
    QPushButton *pb_M2;
    QPushButton *pb_M5;
    QPushButton *pb_M3;
    QPushButton *pb_M1;
    QPushButton *pb_M4;
    QPushButton *pb_toggle;
    QLabel *lblNoiseMkr;
    QPushButton *pb_MkrNoise;
    SA_LineEdit *edit_MkrFreq;
    QPushButton *pb_Normal;
    QPushButton *pb_Delta;
    QPushButton *pb_DeltaPair;
    QLabel *lblFreqCount;
    QLabel *lblMkrEdit;
    QPushButton *pb_FreqCount;
    QLabel *label_5;
    QPushButton *pb_Start;
    QPushButton *pb_Stop;
    QPushButton *pb_Center;
    QLabel *lblMarkerTo;
    QPushButton *pb_MkrAllOn;
    QButtonGroup *MkrTypeGrp;

    void setupUi(QWidget *SA_Dialog_MarkerSetup)
    {
        if (SA_Dialog_MarkerSetup->objectName().isEmpty())
            SA_Dialog_MarkerSetup->setObjectName(QStringLiteral("SA_Dialog_MarkerSetup"));
        SA_Dialog_MarkerSetup->resize(252, 646);
        SA_Dialog_MarkerSetup->setStyleSheet(QLatin1String("/*******************common**********************/\n"
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
"\n"
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
"QPushButton\n"
"{\n"
"	font:75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(123, 123, 12"
                        "3, 1);\n"
"	border-style:flat;\n"
"}\n"
"QPushButton:checked\n"
"{\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#pb_M1,\n"
"#pb_M2,\n"
"#pb_M3,\n"
"#pb_M4,\n"
"#pb_M5,\n"
"#pb_M6\n"
"{\n"
"text-align:left;\n"
"padding-left:10px;\n"
"}\n"
"\n"
"#pb_FreqCount,\n"
"#pb_MkrNoise,\n"
"#pb_toggle\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"#pb_FreqCount:checked,\n"
"#pb_MkrNoise:checked,\n"
"#pb_toggle:checked\n"
"{\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"#pb_FreqCount:!checked,\n"
"#pb_MkrNoise:!checked,\n"
"#pb_toggle:!checked\n"
"{\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"\n"
"#widget>#pb_Normal:checked,\n"
"#widget>#pb_Start:pressed\n"
"{\n"
"	background-image: url(:"
                        "/sa/image/fre_checked_left.png);\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"#widget>#pb_Normal:!checked,\n"
"#widget>#pb_Start\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"#widget>#pb_DeltaPair:checked,\n"
"#widget>#pb_Stop:pressed\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#widget>#pb_Stop,\n"
"#widget>#pb_DeltaPair:!checked\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-position:right;\n"
"}\n"
"#widget>#pb_DeltaPair,\n"
"#widget>#pb_Delta,\n"
"#widget>#pb_Normal\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #widget>QLabe"
                        "l\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #widget>#lblTitle\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_cancel\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_cancel:pressed\n"
"{\n"
"	border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] SA_LineEdit\n"
"{\n"
"	background-color:rgba(255,255,255,0.6);\n"
"	color:rgba(162, 115, 0,1);\n"
"}\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] SA_LineEdit:focus\n"
"{\n"
"	border:2px solid rgba(162,115,0,1);\n"
"}\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] QPushButton:checked\n"
""
                        "{\n"
"	color:rgba(87, 87, 87, 1);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_M1,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_M2,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_M3,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_M4,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_M5,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_M6,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_Delta,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_Center\n"
"{\n"
"	background-image: url(:/sa/image/btn_mkr_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_M1:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_M2:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_M3:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_M4:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_M5:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_M6:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"i"
                        "ndoor\"] #pb_Delta:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_Center:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_mkr_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_FreqCount,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_MkrNoise,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_toggle\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	color:rgba(87, 87, 87, 1);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_FreqCount:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_MkrNoise:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_toggle:checked\n"
"{\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_FreqCount:!checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_MkrNoise:!checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #pb_toggle:!checked\n"
"{\n"
"	color:rgba(123, 123, 123, 1);\n"
"	b"
                        "order-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #widget>#pb_Normal:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #widget>#pb_Start:pressed\n"
"{\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #widget>#pb_Normal:!checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #widget>#pb_Start\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #widget>#pb_DeltaPair:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #widget>#pb_Stop:pressed\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #widget>#pb_Stop,\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] #widget>#pb_DeltaPair:!checked\n"
"{\n"
"	background-"
                        "color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #widget>QLabel\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #widget>#lblTitle\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_cancel\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_cancel:pressed\n"
"{\n"
"	border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] SA_LineEdit\n"
"{\n"
"	background-color:rgba(255,255,255,0.6);\n"
"	color:r"
                        "gba(162, 115, 0,1);\n"
"}\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] SA_LineEdit:focus\n"
"{\n"
"	border:2px solid rgba(162,115,0,1);\n"
"}\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] QPushButton:checked\n"
"{\n"
"	color:rgba(87, 87, 87, 1);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_M1,\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_M2,\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_M3,\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_M4,\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_M5,\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_M6,\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_Delta,\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_Center\n"
"{\n"
"	background-image: url(:/sa/image/btn_mkr_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_M1:checked,\n"
"#SA_Dialog_MarkerSetup[st"
                        "atus  =  \"outdoor\"] #pb_M2:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_M3:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_M4:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_M5:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_M6:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_Delta:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_Center:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_mkr_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_FreqCount,\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_MkrNoise,\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_toggle\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	color:rgba(87, 87, 87, 1);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_FreqCount:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_MkrNoise:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_toggle:checked\n"
"{\n"
""
                        "	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_FreqCount:!checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_MkrNoise:!checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #pb_toggle:!checked\n"
"{\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #widget>#pb_Normal:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #widget>#pb_Start:pressed\n"
"{\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #widget>#pb_Normal:!checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #widget>#pb_Start\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #widget>#pb_DeltaPair:checked,"
                        "\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #widget>#pb_Stop:pressed\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #widget>#pb_Stop,\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] #widget>#pb_DeltaPair:!checked\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"/*******************night**********************/\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #widget\n"
"{\n"
"		background-color:rgba(208,182,139,0.9);\n"
"}\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #widget>QLabel\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #widget>#lblTitle\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_cancel\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/sa/image/night/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_MarkerS"
                        "etup[status  =  \"night\"] #pb_cancel:pressed\n"
"{\n"
"	border-image: url(:/sa/image/night/btn_close_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] SA_LineEdit\n"
"{\n"
"	background-color:rgba(251,219,167,0.6);\n"
"	color:rgba(162, 115, 0,1);\n"
"}\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] SA_LineEdit:focus\n"
"{\n"
"	border:2px solid rgba(162,115,0,1);\n"
"}\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] QPushButton\n"
"{\n"
"	color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] QPushButton:checked\n"
"{\n"
"	color:rgba(87, 87, 87, 1);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_M1,\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_M2,\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_M3,\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_M4,\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_M5,\n"
"#SA"
                        "_Dialog_MarkerSetup[status  =  \"night\"] #pb_M6\n"
"{\n"
"	 background-color:rgb(74,65,50); \n"
"}\n"
"\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_M1:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_M2:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_M3:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_M4:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_M5:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_M6:checked\n"
"{\n"
"	background-color:rgb(251,155,0);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_FreqCount,\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_MkrNoise,\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_toggle\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"	color:rgba(121,106,80,1);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_FreqCount:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_MkrNoise:checked,"
                        "\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_toggle:checked\n"
"{\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_FreqCount:!checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_MkrNoise:!checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_toggle:!checked\n"
"{\n"
"	background-color:rgb(0,0,0,0);\n"
"	color:rgba(121,106,80,1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #widget>#pb_Normal:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #widget>#pb_Start:pressed\n"
"{\n"
"	background-image:url(:/sa/image/night/btn_left_click.png);\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #widget>#pb_Normal:!checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #widget>#pb_Start\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/nigh"
                        "t/btn_left_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #widget>#pb_DeltaPair:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #widget>#pb_Stop:pressed\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/night/btn_right_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #widget>#pb_Stop,\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #widget>#pb_DeltaPair:!checked\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/night/btn_right_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"]  #pb_Delta,\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"]  #pb_Center\n"
"{\n"
"background-image: url(:/sa/image/night/btn_center_nor.png);\n"
"}\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_Delta:checked,\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] #pb_Center:pressed\n"
"{\n"
"	\n"
"	background-image: url(:/sa/image/night/btn_center_click.png);\n"
"}"));
        widget = new QWidget(SA_Dialog_MarkerSetup);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 252, 646));
        widget->setStyleSheet(QStringLiteral(""));
        lblTitle = new QLabel(widget);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));
        lblTitle->setGeometry(QRect(17, 19, 75, 22));
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
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(18, 75, 71, 15));
        line = new QFrame(widget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(18, 46, 212, 2));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        pb_M6 = new QPushButton(widget);
        pb_M6->setObjectName(QStringLiteral("pb_M6"));
        pb_M6->setGeometry(QRect(94, 232, 140, 30));
        pb_M6->setFont(font);
        pb_M6->setFocusPolicy(Qt::NoFocus);
        pb_M6->setStyleSheet(QStringLiteral(""));
        pb_M6->setCheckable(true);
        pb_M2 = new QPushButton(widget);
        pb_M2->setObjectName(QStringLiteral("pb_M2"));
        pb_M2->setGeometry(QRect(94, 100, 140, 30));
        pb_M2->setFont(font);
        pb_M2->setFocusPolicy(Qt::NoFocus);
        pb_M2->setStyleSheet(QStringLiteral(""));
        pb_M2->setCheckable(true);
        pb_M5 = new QPushButton(widget);
        pb_M5->setObjectName(QStringLiteral("pb_M5"));
        pb_M5->setGeometry(QRect(94, 199, 140, 30));
        pb_M5->setFont(font);
        pb_M5->setFocusPolicy(Qt::NoFocus);
        pb_M5->setStyleSheet(QStringLiteral(""));
        pb_M5->setCheckable(true);
        pb_M3 = new QPushButton(widget);
        pb_M3->setObjectName(QStringLiteral("pb_M3"));
        pb_M3->setGeometry(QRect(94, 133, 140, 30));
        pb_M3->setFont(font);
        pb_M3->setFocusPolicy(Qt::NoFocus);
        pb_M3->setStyleSheet(QStringLiteral(""));
        pb_M3->setCheckable(true);
        pb_M1 = new QPushButton(widget);
        pb_M1->setObjectName(QStringLiteral("pb_M1"));
        pb_M1->setGeometry(QRect(94, 67, 140, 30));
        pb_M1->setFont(font);
        pb_M1->setFocusPolicy(Qt::NoFocus);
        pb_M1->setCheckable(true);
        pb_M1->setChecked(true);
        pb_M4 = new QPushButton(widget);
        pb_M4->setObjectName(QStringLiteral("pb_M4"));
        pb_M4->setGeometry(QRect(94, 166, 140, 30));
        pb_M4->setFont(font);
        pb_M4->setFocusPolicy(Qt::NoFocus);
        pb_M4->setStyleSheet(QStringLiteral(""));
        pb_M4->setCheckable(true);
        pb_toggle = new QPushButton(widget);
        pb_toggle->setObjectName(QStringLiteral("pb_toggle"));
        pb_toggle->setGeometry(QRect(94, 282, 90, 30));
        pb_toggle->setFocusPolicy(Qt::NoFocus);
        pb_toggle->setStyleSheet(QStringLiteral(""));
        pb_toggle->setCheckable(true);
        pb_toggle->setChecked(false);
        pb_toggle->setFlat(false);
        lblNoiseMkr = new QLabel(widget);
        lblNoiseMkr->setObjectName(QStringLiteral("lblNoiseMkr"));
        lblNoiseMkr->setGeometry(QRect(18, 550, 71, 31));
        pb_MkrNoise = new QPushButton(widget);
        pb_MkrNoise->setObjectName(QStringLiteral("pb_MkrNoise"));
        pb_MkrNoise->setGeometry(QRect(94, 550, 90, 30));
        pb_MkrNoise->setFocusPolicy(Qt::NoFocus);
        pb_MkrNoise->setStyleSheet(QStringLiteral(""));
        pb_MkrNoise->setCheckable(true);
        edit_MkrFreq = new SA_LineEdit(widget);
        edit_MkrFreq->setObjectName(QStringLiteral("edit_MkrFreq"));
        edit_MkrFreq->setGeometry(QRect(94, 500, 140, 30));
        edit_MkrFreq->setStyleSheet(QLatin1String("SA_LineEdit\n"
"{\n"
"	color:rgba(162, 115, 0,1);\n"
"	font: 75 12px \"Arial\";\n"
"	font-weight:bold;\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
""));
        edit_MkrFreq->setReadOnly(true);
        pb_Normal = new QPushButton(widget);
        MkrTypeGrp = new QButtonGroup(SA_Dialog_MarkerSetup);
        MkrTypeGrp->setObjectName(QStringLiteral("MkrTypeGrp"));
        MkrTypeGrp->addButton(pb_Normal);
        pb_Normal->setObjectName(QStringLiteral("pb_Normal"));
        pb_Normal->setGeometry(QRect(18, 382, 69, 30));
        pb_Normal->setFocusPolicy(Qt::NoFocus);
        pb_Normal->setCheckable(true);
        pb_Normal->setChecked(true);
        pb_Delta = new QPushButton(widget);
        MkrTypeGrp->addButton(pb_Delta);
        pb_Delta->setObjectName(QStringLiteral("pb_Delta"));
        pb_Delta->setGeometry(QRect(91, 382, 69, 30));
        pb_Delta->setFocusPolicy(Qt::NoFocus);
        pb_Delta->setStyleSheet(QStringLiteral(""));
        pb_Delta->setCheckable(true);
        pb_Delta->setChecked(false);
        pb_DeltaPair = new QPushButton(widget);
        MkrTypeGrp->addButton(pb_DeltaPair);
        pb_DeltaPair->setObjectName(QStringLiteral("pb_DeltaPair"));
        pb_DeltaPair->setGeometry(QRect(164, 382, 69, 30));
        pb_DeltaPair->setFocusPolicy(Qt::NoFocus);
        pb_DeltaPair->setCheckable(true);
        pb_DeltaPair->setFlat(false);
        lblFreqCount = new QLabel(widget);
        lblFreqCount->setObjectName(QStringLiteral("lblFreqCount"));
        lblFreqCount->setGeometry(QRect(18, 600, 81, 31));
        lblMkrEdit = new QLabel(widget);
        lblMkrEdit->setObjectName(QStringLiteral("lblMkrEdit"));
        lblMkrEdit->setGeometry(QRect(18, 500, 71, 31));
        pb_FreqCount = new QPushButton(widget);
        pb_FreqCount->setObjectName(QStringLiteral("pb_FreqCount"));
        pb_FreqCount->setGeometry(QRect(94, 600, 90, 30));
        pb_FreqCount->setFocusPolicy(Qt::NoFocus);
        pb_FreqCount->setStyleSheet(QStringLiteral(""));
        pb_FreqCount->setCheckable(true);
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(18, 282, 71, 30));
        pb_Start = new QPushButton(widget);
        pb_Start->setObjectName(QStringLiteral("pb_Start"));
        pb_Start->setGeometry(QRect(20, 450, 69, 30));
        pb_Stop = new QPushButton(widget);
        pb_Stop->setObjectName(QStringLiteral("pb_Stop"));
        pb_Stop->setGeometry(QRect(166, 450, 69, 30));
        pb_Center = new QPushButton(widget);
        pb_Center->setObjectName(QStringLiteral("pb_Center"));
        pb_Center->setGeometry(QRect(93, 450, 69, 30));
        lblMarkerTo = new QLabel(widget);
        lblMarkerTo->setObjectName(QStringLiteral("lblMarkerTo"));
        lblMarkerTo->setGeometry(QRect(20, 432, 75, 17));
        pb_MkrAllOn = new QPushButton(widget);
        pb_MkrAllOn->setObjectName(QStringLiteral("pb_MkrAllOn"));
        pb_MkrAllOn->setGeometry(QRect(18, 332, 216, 30));
        pb_MkrAllOn->setStyleSheet(QLatin1String("/*******************common**********************/\n"
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
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	color:rgba(255, 255, 255, 1);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"indoor\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	color:rgba(0, 0, 0, 1);\n"
"	border-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"outdoor\"] QPushButton:pressed\n"
""
                        "{\n"
"	border-image: url(:/sa/image/outdoor/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] QPushButton\n"
"{\n"
"	color: #FBDBA7;\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSetup[status  =  \"night\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/btn_w216_click.png);\n"
"}"));
        QWidget::setTabOrder(pb_M6, pb_M2);
        QWidget::setTabOrder(pb_M2, pb_cancel);
        QWidget::setTabOrder(pb_cancel, pb_M5);
        QWidget::setTabOrder(pb_M5, pb_M3);
        QWidget::setTabOrder(pb_M3, pb_M1);
        QWidget::setTabOrder(pb_M1, pb_M4);
        QWidget::setTabOrder(pb_M4, pb_toggle);
        QWidget::setTabOrder(pb_toggle, pb_MkrNoise);
        QWidget::setTabOrder(pb_MkrNoise, edit_MkrFreq);
        QWidget::setTabOrder(edit_MkrFreq, pb_Normal);
        QWidget::setTabOrder(pb_Normal, pb_Delta);
        QWidget::setTabOrder(pb_Delta, pb_DeltaPair);
        QWidget::setTabOrder(pb_DeltaPair, pb_FreqCount);

        retranslateUi(SA_Dialog_MarkerSetup);

        QMetaObject::connectSlotsByName(SA_Dialog_MarkerSetup);
    } // setupUi

    void retranslateUi(QWidget *SA_Dialog_MarkerSetup)
    {
        SA_Dialog_MarkerSetup->setWindowTitle(QApplication::translate("SA_Dialog_MarkerSetup", "Form", 0));
        SA_Dialog_MarkerSetup->setProperty("status", QVariant(QApplication::translate("SA_Dialog_MarkerSetup", "night", 0)));
        lblTitle->setText(QApplication::translate("SA_Dialog_MarkerSetup", "Marker", 0));
        pb_cancel->setText(QString());
        label->setText(QApplication::translate("SA_Dialog_MarkerSetup", "Marker", 0));
        pb_M6->setText(QApplication::translate("SA_Dialog_MarkerSetup", "M6", 0));
        pb_M2->setText(QApplication::translate("SA_Dialog_MarkerSetup", "M2", 0));
        pb_M5->setText(QApplication::translate("SA_Dialog_MarkerSetup", "M5", 0));
        pb_M3->setText(QApplication::translate("SA_Dialog_MarkerSetup", "M3", 0));
        pb_M1->setText(QApplication::translate("SA_Dialog_MarkerSetup", "M1", 0));
        pb_M4->setText(QApplication::translate("SA_Dialog_MarkerSetup", "M4", 0));
        pb_toggle->setText(QApplication::translate("SA_Dialog_MarkerSetup", "Off", 0));
        lblNoiseMkr->setText(QApplication::translate("SA_Dialog_MarkerSetup", "Noise\n"
"Marker", 0));
        pb_MkrNoise->setText(QApplication::translate("SA_Dialog_MarkerSetup", "Off", 0));
        pb_Normal->setText(QApplication::translate("SA_Dialog_MarkerSetup", "Normal", 0));
        pb_Delta->setText(QApplication::translate("SA_Dialog_MarkerSetup", "Delta", 0));
        pb_DeltaPair->setText(QApplication::translate("SA_Dialog_MarkerSetup", "Delta Pair", 0));
        lblFreqCount->setText(QApplication::translate("SA_Dialog_MarkerSetup", "Frequency\n"
"Count", 0));
        lblMkrEdit->setText(QApplication::translate("SA_Dialog_MarkerSetup", "Marker\n"
"Edit", 0));
        pb_FreqCount->setText(QApplication::translate("SA_Dialog_MarkerSetup", "Off", 0));
        label_5->setText(QApplication::translate("SA_Dialog_MarkerSetup", "Marker\n"
"View", 0));
        pb_Start->setText(QApplication::translate("SA_Dialog_MarkerSetup", "Start", 0));
        pb_Stop->setText(QApplication::translate("SA_Dialog_MarkerSetup", "Stop", 0));
        pb_Center->setText(QApplication::translate("SA_Dialog_MarkerSetup", "Center", 0));
        lblMarkerTo->setText(QApplication::translate("SA_Dialog_MarkerSetup", "Marker to", 0));
        pb_MkrAllOn->setText(QApplication::translate("SA_Dialog_MarkerSetup", "Marker All On", 0));
    } // retranslateUi

};

namespace Ui {
    class SA_Dialog_MarkerSetup: public Ui_SA_Dialog_MarkerSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_MARKERSETUP_H
