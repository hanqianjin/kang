/********************************************************************************
** Form generated from reading UI file 'bitsa.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BITSA_H
#define UI_BITSA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <sa_customedTablewidget.h>
#include "sa_clickedlabel.h"
#include "sa_clickedwidget.h"

QT_BEGIN_NAMESPACE

class Ui_BitSA
{
public:
    ClickableTableWidget *tableWidget;
    QWidget *topButtonBar;
    QPushButton *topButton5;
    QPushButton *topButton8;
    QPushButton *topButton7;
    QPushButton *topButton1;
    QPushButton *topButton6;
    QPushButton *topButton2;
    QPushButton *topButton3;
    QPushButton *topButton4;
    QPushButton *topButton9;
    QPushButton *topButton10;
    QPushButton *topButton11;
    QWidget *rightButtonBar;
    QVBoxLayout *verticalLayout;
    QPushButton *rightButton1;
    QPushButton *rightButton2;
    QPushButton *rightButton3;
    QPushButton *rightButton4;
    QPushButton *rightButton5;
    QPushButton *rightButton6;
    QPushButton *rightButton7;
    QPushButton *rightButton8;
    QPushButton *rightButton9;
    QSpacerItem *verticalSpacer;
    QPushButton *rightButton10;
    QWidget *buttomMarker;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pb_marker_AllOff;
    QPushButton *pb_marker_1;
    QPushButton *pb_marker_2;
    QPushButton *pb_marker_3;
    QPushButton *pb_marker_4;
    QPushButton *pb_marker_5;
    QPushButton *pb_marker_6;
    QWidget *leftWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *leftInfoWidget;
    SA_ClickedWidget *widget_mode;
    QLabel *lblmeasure;
    QLabel *lblmode;
    QLabel *lblmodetitle;
    SA_ClickedWidget *widget_Freq;
    QLabel *lblCenterFreq;
    QLabel *lblChannel;
    QLabel *lblCHStandard;
    QLabel *lblCenterFreqValue;
    QLabel *lblChannelValue;
    QLabel *lblCHStandardValue;
    SA_ClickedWidget *widget_Ampt;
    QLabel *lblOffset;
    QLabel *lblAtten;
    QLabel *lblPreamp;
    QLabel *lblAttenType;
    QLabel *lblAttenValue;
    QLabel *lblOffsetValue;
    QLabel *lblOffsetType;
    QLabel *lblPreampValue;
    SA_ClickedWidget *widget_BW;
    SA_ClickedLabel *lblAverage;
    QLabel *lblVBW;
    QLabel *lblRBW;
    QLabel *lblRBWType;
    QLabel *lblVBWType;
    SA_ClickedLabel *lblAverageValue;
    QLabel *lblVBWValue;
    QLabel *lblRBWValue;
    QLabel *lblAveOn;
    SA_ClickedWidget *widget_Sweep;
    SA_ClickedLabel *lblDetectors;
    QLabel *label_25;
    QLabel *lblSweepTime;
    QLabel *label_27;
    QLabel *lblSweepMode;
    SA_ClickedLabel *lblDetectorValue;
    SA_ClickedWidget *widget_Trigger;
    SA_ClickedLabel *lblIFOutPut;
    QLabel *label_31;
    SA_ClickedLabel *lblIFOutPutValue;
    SA_ClickedLabel *label_33;
    SA_ClickedLabel *lblFreqRef;
    QLabel *lblTrigger;
    SA_ClickedWidget *widget_Trace;
    QLabel *lblT2;
    QLabel *lblT3;
    QLabel *lblT4;
    QLabel *lblT5;
    QLabel *lblT6;
    QLabel *lblTypeT4;
    QLabel *lblTypeT2;
    QLabel *lblTypeT5;
    QLabel *lblTypeT3;
    QLabel *lblTypeT6;
    QLabel *lblT1;
    QLabel *lblTypeT1;
    QLabel *lblbgT1;
    QLabel *lblbgT4;
    QLabel *lblbgT3;
    QLabel *lblbgT6;
    QLabel *lblbgT2;
    QLabel *lblbgT5;
    SA_ClickedWidget *widget_Limit;
    QLabel *lblLimit;
    QLabel *lblLimitStatus;
    QPushButton *pb_left_hide;
    QWidget *wgT1;

    void setupUi(QWidget *BitSA)
    {
        if (BitSA->objectName().isEmpty())
            BitSA->setObjectName(QStringLiteral("BitSA"));
        BitSA->setWindowModality(Qt::NonModal);
        BitSA->resize(1280, 715);
        BitSA->setFocusPolicy(Qt::ClickFocus);
        BitSA->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#BitSA[status = \"indoor\"] #BitSA\n"
"{\n"
"    background-color:rgb(76, 76, 76);\n"
"}\n"
"#BitSA[status = \"indoor\"] QPushButton\n"
"{\n"
"     outline:none;\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButtonBar\n"
"{\n"
"    background-image: url(:/sa/image/top_bar_normal.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButtonBar>QPushButton\n"
"{\n"
"    border-style:flat;\n"
"    text-align:center;\n"
"    font: 75 18px \"Arial\";\n"
"    font-weight:bold;\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButtonBar>QPushButton:disable\n"
"{\n"
"    color:rgb(112, 112, 112);\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButton1:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_normal.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButton1:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_click.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButton2:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_normal.png);\n"
""
                        "}\n"
"#BitSA[status = \"indoor\"] #topButton2:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_click.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButton3:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_normal.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButton3:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_click.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButton4:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_normal.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButton4:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_click.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButton5:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_normal.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButton5:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_click.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButton6:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_no"
                        "rmal.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButton6:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_click.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButton7:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_normal.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButton7:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_click.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButton8:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_normal.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButton8:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_click.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButton9:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_normal.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButton9:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_click.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButton10:!checked\n"
"{\n"
"    background-image: url(:/sa/imag"
                        "e/btn_top_m_setup_normal.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButton10:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_m_setup_click.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButton11:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_all_set_normal.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #topButton11:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_all_set_click.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #rightButtonBar\n"
"{\n"
"    background-color:rgb(0,0,0);\n"
"    background-image: url(:/sa/image/right-bar-click.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #rightButtonBar>QPushButton\n"
"{\n"
"    border-style:flat;\n"
"}\n"
"#BitSA[status = \"indoor\"] #rightButton1\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-1.png);\n"
"}\n"
"\n"
"#BitSA[status = \"indoor\"] #rightButton1:pressed\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-1-click.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #rightButton2\n"
"{\n"
"    background-i"
                        "mage: url(:/sa/image/btn-right-2.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #rightButton2:pressed\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-2-click.png);\n"
"}\n"
"\n"
"#BitSA[status = \"indoor\"] #rightButton3\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-3.png);\n"
"}\n"
"\n"
"#BitSA[status = \"indoor\"] #rightButton3:pressed\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-3-click.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #rightButton4\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-4.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #rightButton4:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-4-click.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #rightButton5:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-5.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #rightButton5:pressed\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-5-click.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #rightButton6:!checked\n"
"{\n"
"    background-image:"
                        " url(:/sa/image/btn-right-6.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #rightButton6:pressed\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-6-click.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #rightButton7:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-7.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #rightButton7:pressed\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-7-click.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #rightButton8:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-8.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #rightButton8:checked,\n"
"#BitSA[status = \"indoor\"] #rightButton8:pressed\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-8-click.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #rightButton9\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-9.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #rightButton9:pressed\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-9-click.png);\n"
"}\n"
"\n"
"\n"
"#BitSA[status = \"indoo"
                        "r\"] #rightButton10:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-10.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #rightButton10:!checked:pressed\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-10-click.png);\n"
"}\n"
"\n"
"#BitSA[status = \"indoor\"] #rightButton10:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-10-full.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #rightButton10:checked:pressed\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-10-full-click.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #leftInfoWidget\n"
"{\n"
"background-color:rgba(0,0,0,1);\n"
"}\n"
"#BitSA[status = \"indoor\"] #buttomMarker\n"
"{\n"
"/*background-color:rgb(76,76,76);*/\n"
"}\n"
"#BitSA[status = \"indoor\"] #leftWidget\n"
"{\n"
"    background-color:rgba(76,76,76,0);\n"
"}\n"
"#BitSA[status = \"indoor\"] #leftWidget>QPushButton\n"
"{\n"
"    border-radius:0px 3px 3px 0px;\n"
"}\n"
"#BitSA[status = \"indoor\"] #leftWidget>QPushButton:checked\n"
"{\n"
"    background-position:r"
                        "ight;\n"
"    background-image: url(:/sa/image/btn_expand_normal.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #leftWidget>QPushButton:!checked\n"
"{\n"
"    background-position:right;\n"
"    background-image: url(:/sa/image/btn_collapse_normal.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #leftWidget>#lblT1\n"
"{\n"
"    color:rgba(0, 255, 47, 1);\n"
"}\n"
"#BitSA[status = \"indoor\"] #leftWidget>#lblT2\n"
"{\n"
"    color:rgba(255, 159, 0, 1);\n"
"}\n"
"#BitSA[status = \"indoor\"] #leftWidget>#lblT3\n"
"{\n"
"    color:rgba(0, 112, 255, 1);\n"
"}\n"
"#BitSA[status = \"indoor\"] #leftWidget>#lblT4\n"
"{\n"
"    color:rgba(255, 144, 144, 1);\n"
"}\n"
"#BitSA[status = \"indoor\"] #leftWidget>#lblT5\n"
"{\n"
"    color:rgba(180, 121, 255, 1);\n"
"}\n"
"#BitSA[status = \"indoor\"] #leftWidget>#lblT6\n"
"{\n"
"    color:rgba(39, 255, 252, 1);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#BitSA[status = \"outdoor\"] #BitSA\n"
"{\n"
"    background-color:rgb(76, 76, 76);\n"
"}\n"
"#BitSA[status"
                        " = \"outdoor\"] QPushButton\n"
"{\n"
"     outline:none;\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButtonBar\n"
"{\n"
"    background-image: url(:/sa/image/top_bar_normal.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButtonBar>QPushButton\n"
"{\n"
"    border-style:flat;\n"
"    text-align:center;\n"
"    font: 75 18px \"Arial\";\n"
"    font-weight:bold;\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButtonBar>QPushButton:disable\n"
"{\n"
"    color:rgb(112, 112, 112);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButton1:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_normal.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButton1:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_click.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButton2:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_normal.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButton2:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_click.png);\n"
"}\n"
"#BitSA[status = "
                        "\"outdoor\"] #topButton3:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_normal.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButton3:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_click.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButton4:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_normal.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButton4:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_click.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButton5:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_normal.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButton5:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_click.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButton6:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_normal.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButton6:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_click.png);\n"
""
                        "}\n"
"#BitSA[status = \"outdoor\"] #topButton7:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_normal.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButton7:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_click.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButton8:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_normal.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButton8:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_click.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButton9:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_normal.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButton9:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_bar_click.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButton10:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_m_setup_normal.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButton10:checked\n"
"{\n"
"    background-image: url(:/sa/image"
                        "/btn_top_m_setup_click.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButton11:!checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_all_set_normal.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #topButton11:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn_top_all_set_click.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #rightButtonBar\n"
"{\n"
"	background-color:rgba(255,255,255,1);\n"
"    background-image: url(:/sa/image/right-bar-click.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #rightButtonBar>QPushButton\n"
"{\n"
"    border-style:flat;\n"
"}\n"
"#BitSA[status = \"outdoor\"] #rightButton1\n"
"{\n"
"    background-image: url(:/sa/image/outdoor/btn-right-1.png);\n"
"}\n"
"\n"
"#BitSA[status = \"outdoor\"] #rightButton1:pressed\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-1-click.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #rightButton2\n"
"{\n"
"    background-image: url(:/sa/image/outdoor/btn-right-2.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #rightButton2:pressed\n"
"{\n"
""
                        "    background-image: url(:/sa/image/btn-right-2-click.png);\n"
"}\n"
"\n"
"#BitSA[status = \"outdoor\"] #rightButton3\n"
"{\n"
"    background-image: url(:/sa/image/outdoor/btn-right-3.png);\n"
"}\n"
"\n"
"#BitSA[status = \"outdoor\"] #rightButton3:pressed\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-3-click.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #rightButton4\n"
"{\n"
"    background-image: url(:/sa/image/outdoor/btn-right-4.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #rightButton4:checked\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-4-click.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #rightButton5\n"
"{\n"
"    background-image: url(:/sa/image/outdoor/btn-right-5.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #rightButton5:pressed\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-5-click.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #rightButton6\n"
"{\n"
"    background-image: url(:/sa/image/outdoor/btn-right-6.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #rightButton6:p"
                        "ressed\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-6-click.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #rightButton7\n"
"{\n"
"    background-image: url(:/sa/image/outdoor/btn-right-7.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #rightButton7:pressed\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-7-click.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #rightButton8\n"
"{\n"
"    background-image: url(:/sa/image/outdoor/btn-right-8.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #rightButton8:checked,\n"
"#BitSA[status = \"outdoor\"] #rightButton8:pressed\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-8-click.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #rightButton9\n"
"{\n"
"    background-image: url(:/sa/image/outdoor/btn-right-9.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #rightButton9:pressed\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-9-click.png);\n"
"}\n"
"\n"
"\n"
"#BitSA[status = \"outdoor\"] #rightButton10\n"
"{\n"
"    background-image: url(:/sa/image/outdoo"
                        "r/btn-right-10.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #rightButton10:pressed\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-10-click.png);\n"
"}\n"
"\n"
"#BitSA[status = \"outdoor\"] #rightButton10:checked\n"
"{\n"
"    background-image: url(:/sa/image/outdoor/btn-right-10-full.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #rightButton10:checked:pressed\n"
"{\n"
"    background-image: url(:/sa/image/btn-right-10-full-click.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #leftInfoWidget\n"
"{\n"
"background-color:rgba(255,255,255,1);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #buttomMarker\n"
"{\n"
"/*background-color:rgb(76,76,76);*/\n"
"}\n"
"\n"
"#BitSA[status = \"outdoor\"] #leftWidget\n"
"{\n"
"    background-color:transparent;\n"
"}\n"
"#BitSA[status = \"outdoor\"] #leftWidget>QPushButton\n"
"{\n"
"    border-radius:0px 3px 3px 0px;\n"
"}\n"
"#BitSA[status = \"outdoor\"] #leftWidget>QPushButton:checked\n"
"{\n"
"    background-position:right;\n"
"    background-image: url(:/sa/image/outdoor/btn_ex"
                        "pand_normal.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #leftWidget>QPushButton\n"
"{\n"
"    background-position:right;\n"
"    background-image: url(:/sa/image/outdoor/btn_collapse_normal.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #leftWidget>#lblT1\n"
"{\n"
"    color:rgba(0, 255, 47, 1);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #leftWidget>#lblT2\n"
"{\n"
"    color:rgba(255, 159, 0, 1);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #leftWidget>#lblT3\n"
"{\n"
"    color:rgba(0, 112, 255, 1);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #leftWidget>#lblT4\n"
"{\n"
"    color:rgba(255, 144, 144, 1);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #leftWidget>#lblT5\n"
"{\n"
"    color:rgba(180, 121, 255, 1);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #leftWidget>#lblT6\n"
"{\n"
"    color:rgba(39, 255, 252, 1);\n"
"}\n"
"\n"
"\n"
"/*******************night**********************/\n"
"#BitSA[status = \"night\"] #BitSA\n"
"{\n"
"    background-color:rgb(76, 76, 76);\n"
"}\n"
"#BitSA[status = \"night\"] QPushButton\n"
"{\n"
"     outli"
                        "ne:none;\n"
"}\n"
"#BitSA[status = \"night\"] #topButtonBar\n"
"{\n"
"    background-image: url(:/sa/image/night/top_bar_normal.png);\n"
"}\n"
"#BitSA[status = \"night\"] #topButtonBar>QPushButton\n"
"{\n"
"    border-style:flat;\n"
"    text-align:center;\n"
"    font: 75 18px \"Arial\";\n"
"    font-weight:bold;\n"
"}\n"
"#BitSA[status = \"night\"] #topButtonBar>QPushButton:disable\n"
"{\n"
"    color:rgb(112, 112, 112);\n"
"}\n"
"#BitSA[status = \"night\"] #topButton1:!checked,\n"
"#BitSA[status = \"night\"] #topButton2:!checked,\n"
"#BitSA[status = \"night\"] #topButton3:!checked,\n"
"#BitSA[status = \"night\"] #topButton4:!checked,\n"
"#BitSA[status = \"night\"] #topButton5:!checked,\n"
"#BitSA[status = \"night\"] #topButton6:!checked,\n"
"#BitSA[status = \"night\"] #topButton7:!checked,\n"
"#BitSA[status = \"night\"] #topButton8:!checked,\n"
"#BitSA[status = \"night\"] #topButton9:!checked\n"
"{\n"
"    background-image: url(:/sa/image/night/btn_top_bar_normal.png);\n"
"}\n"
"#BitSA[status = \"night\"] #"
                        "topButton1:checked,\n"
"#BitSA[status = \"night\"] #topButton2:checked,\n"
"#BitSA[status = \"night\"] #topButton3:checked,\n"
"#BitSA[status = \"night\"] #topButton4:checked,\n"
"#BitSA[status = \"night\"] #topButton5:checked,\n"
"#BitSA[status = \"night\"] #topButton6:checked,\n"
"#BitSA[status = \"night\"] #topButton7:checked,\n"
"#BitSA[status = \"night\"] #topButton8:checked,\n"
"#BitSA[status = \"night\"] #topButton9:checked\n"
"{\n"
"    background-image: url(:/sa/image/night/btn_top_bar_click.png);\n"
"}\n"
"\n"
"#BitSA[status = \"night\"] #topButton10:!checked\n"
"{\n"
"    background-image: url(:/sa/image/night/btn_top_m_setup_normal.png);\n"
"}\n"
"#BitSA[status = \"night\"] #topButton10:checked\n"
"{\n"
"    background-image: url(:/sa/image/night/btn_top_m_setup_click.png);\n"
"}\n"
"#BitSA[status = \"night\"] #topButton11:!checked\n"
"{\n"
"    background-image: url(:/sa/image/night/btn_top_all_set_normal.png);\n"
"}\n"
"#BitSA[status = \"night\"] #topButton11:checked\n"
"{\n"
"    background-imag"
                        "e: url(:/sa/image/night/btn_top_all_set_click.png);\n"
"}\n"
"#BitSA[status = \"night\"] #rightButtonBar\n"
"{\n"
"    background-color:rgb(0,0,0);\n"
"    background-image: url(:/sa/image/right-bar-click.png);\n"
"}\n"
"#BitSA[status = \"night\"] #rightButtonBar>QPushButton\n"
"{\n"
"    border-style:flat;\n"
"}\n"
"#BitSA[status = \"night\"] #rightButton1\n"
"{\n"
"    background-image: url(:/sa/image/night/btn-right-1.png);\n"
"}\n"
"\n"
"#BitSA[status = \"night\"] #rightButton1:pressed\n"
"{\n"
"    background-image: url(:/sa/image/night/btn-right-1-click.png);\n"
"}\n"
"#BitSA[status = \"night\"] #rightButton2\n"
"{\n"
"    background-image: url(:/sa/image/night/btn-right-2.png);\n"
"}\n"
"#BitSA[status = \"night\"] #rightButton2:pressed\n"
"{\n"
"    background-image: url(:/sa/image/night/btn-right-2-click.png);\n"
"}\n"
"\n"
"#BitSA[status = \"night\"] #rightButton3\n"
"{\n"
"    background-image: url(:/sa/image/night/btn-right-3.png);\n"
"}\n"
"\n"
"#BitSA[status = \"night\"] #rightButton3:pressed\n"
""
                        "{\n"
"    background-image: url(:/sa/image/night/btn-right-3-click.png);\n"
"}\n"
"#BitSA[status = \"night\"] #rightButton4\n"
"{\n"
"    background-image: url(:/sa/image/night/btn-right-4.png);\n"
"}\n"
"#BitSA[status = \"night\"] #rightButton4:checked\n"
"{\n"
"    background-image: url(:/sa/image/night/btn-right-4-click.png);\n"
"}\n"
"#BitSA[status = \"night\"] #rightButton5:!checked\n"
"{\n"
"    background-image: url(:/sa/image/night/btn-right-5.png);\n"
"}\n"
"#BitSA[status = \"night\"] #rightButton5:pressed\n"
"{\n"
"    background-image: url(:/sa/image/night/btn-right-5-click.png);\n"
"}\n"
"#BitSA[status = \"night\"] #rightButton6:!checked\n"
"{\n"
"    background-image: url(:/sa/image/night/btn-right-6.png);\n"
"}\n"
"#BitSA[status = \"night\"] #rightButton6:pressed\n"
"{\n"
"    background-image: url(:/sa/image/night/btn-right-6-click.png);\n"
"}\n"
"#BitSA[status = \"night\"] #rightButton7:!checked\n"
"{\n"
"    background-image: url(:/sa/image/night/btn-right-7.png);\n"
"}\n"
"#BitSA[status = \"n"
                        "ight\"] #rightButton7:pressed\n"
"{\n"
"    background-image: url(:/sa/image/night/btn-right-7-click.png);\n"
"}\n"
"#BitSA[status = \"night\"] #rightButton8:!checked\n"
"{\n"
"    background-image: url(:/sa/image/night/btn-right-8.png);\n"
"}\n"
"#BitSA[status = \"night\"] #rightButton8:checked,\n"
"#BitSA[status = \"night\"] #rightButton8:pressed\n"
"{\n"
"    background-image: url(:/sa/image/night/btn-right-8-click.png);\n"
"}\n"
"#BitSA[status = \"night\"] #rightButton9\n"
"{\n"
"    background-image: url(:/sa/image/night/btn-right-9.png);\n"
"}\n"
"#BitSA[status = \"night\"] #rightButton9:pressed\n"
"{\n"
"    background-image: url(:/sa/image/night/btn-right-9-click.png);\n"
"}\n"
"\n"
"\n"
"#BitSA[status = \"night\"] #rightButton10:!checked\n"
"{\n"
"    background-image: url(:/sa/image/night/btn-right-10.png);\n"
"}\n"
"#BitSA[status = \"night\"] #rightButton10:!checked:pressed\n"
"{\n"
"    background-image: url(:/sa/image/night/btn-right-10-click.png);\n"
"}\n"
"\n"
"#BitSA[status = \"night\"] #rightB"
                        "utton10:checked\n"
"{\n"
"    background-image: url(:/sa/image/night/btn-right-10-full.png);\n"
"}\n"
"#BitSA[status = \"night\"] #rightButton10:checked:pressed\n"
"{\n"
"    background-image: url(:/sa/image/night/btn-right-10-full-click.png);\n"
"}\n"
"#BitSA[status = \"night\"] #leftInfoWidget\n"
"{\n"
"	background-color:rgb(0,0,0);\n"
"}\n"
"#BitSA[status = \"night\"] #buttomMarker\n"
"{\n"
"/*background-color:rgb(76,76,76);*/\n"
"}\n"
"#BitSA[status = \"night\"] #leftWidget\n"
"{\n"
"    background-color:transparent;\n"
"}\n"
"#BitSA[status = \"night\"] #leftWidget>QPushButton\n"
"{\n"
"    border-radius:0px 3px 3px 0px;\n"
"}\n"
"#BitSA[status = \"night\"] #leftWidget>QPushButton:checked\n"
"{\n"
"    background-position:right;\n"
"    background-image: url(:/sa/image/night/btn_expand_normal.png);\n"
"}\n"
"#BitSA[status = \"night\"] #leftWidget>QPushButton:!checked\n"
"{\n"
"    background-position:right;\n"
"    background-image: url(:/sa/image/night/btn_collapse_normal.png);\n"
"}\n"
"#BitSA[status = \""
                        "night\"] #leftWidget>#lblT1\n"
"{\n"
"    color:rgba(0, 255, 47, 1);\n"
"}\n"
"#BitSA[status = \"night\"] #leftWidget>#lblT2\n"
"{\n"
"    color:rgba(255, 159, 0, 1);\n"
"}\n"
"#BitSA[status = \"night\"] #leftWidget>#lblT3\n"
"{\n"
"    color:rgba(0, 112, 255, 1);\n"
"}\n"
"#BitSA[status = \"night\"] #leftWidget>#lblT4\n"
"{\n"
"    color:rgba(255, 144, 144, 1);\n"
"}\n"
"#BitSA[status = \"night\"] #leftWidget>#lblT5\n"
"{\n"
"    color:rgba(180, 121, 255, 1);\n"
"}\n"
"#BitSA[status = \"night\"] #leftWidget>#lblT6\n"
"{\n"
"    color:rgba(39, 255, 252, 1);\n"
"}"));
        tableWidget = new ClickableTableWidget(BitSA);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(277, 66, 351, 570));
        tableWidget->setAutoFillBackground(true);
        tableWidget->setStyleSheet(QLatin1String("border-color: rgb(255, 0, 0);\n"
"selection-background-color: rgb(200, 200, 50);\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(100,100,100);"));
        tableWidget->setColumnCount(2);
        topButtonBar = new QWidget(BitSA);
        topButtonBar->setObjectName(QStringLiteral("topButtonBar"));
        topButtonBar->setGeometry(QRect(1, 0, 1278, 65));
        topButtonBar->setMinimumSize(QSize(0, 0));
        topButtonBar->setMaximumSize(QSize(16777215, 16777215));
        topButtonBar->setStyleSheet(QStringLiteral(""));
        topButton5 = new QPushButton(topButtonBar);
        topButton5->setObjectName(QStringLiteral("topButton5"));
        topButton5->setGeometry(QRect(502, 10, 120, 49));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        topButton5->setFont(font);
        topButton5->setFocusPolicy(Qt::StrongFocus);
        topButton5->setStyleSheet(QLatin1String("#topButtonBar{\n"
"    border:1px;\n"
"    border-left-style:solid;\n"
"    border-left-color:black;\n"
"}\n"
"QPushButton{\n"
" font-size:20px;\n"
"}"));
        topButton5->setCheckable(true);
        topButton5->setAutoExclusive(false);
        topButton8 = new QPushButton(topButtonBar);
        topButton8->setObjectName(QStringLiteral("topButton8"));
        topButton8->setGeometry(QRect(871, 10, 120, 49));
        topButton8->setFocusPolicy(Qt::StrongFocus);
        topButton8->setStyleSheet(QLatin1String("#topButtonBar{\n"
"    border:1px;\n"
"    border-left-style:solid;\n"
"    border-left-color:black;\n"
"}"));
        topButton8->setCheckable(true);
        topButton8->setAutoExclusive(false);
        topButton7 = new QPushButton(topButtonBar);
        topButton7->setObjectName(QStringLiteral("topButton7"));
        topButton7->setGeometry(QRect(748, 10, 120, 49));
        topButton7->setFocusPolicy(Qt::StrongFocus);
        topButton7->setStyleSheet(QLatin1String("#topButtonBar{\n"
"    border:1px;\n"
"    border-left-style:solid;\n"
"    border-left-color:black;\n"
"}"));
        topButton7->setCheckable(true);
        topButton7->setAutoExclusive(false);
        topButton1 = new QPushButton(topButtonBar);
        topButton1->setObjectName(QStringLiteral("topButton1"));
        topButton1->setGeometry(QRect(10, 10, 120, 49));
        topButton1->setFont(font);
        topButton1->setFocusPolicy(Qt::StrongFocus);
        topButton1->setStyleSheet(QStringLiteral(""));
        topButton1->setCheckable(true);
        topButton1->setChecked(false);
        topButton1->setAutoExclusive(false);
        topButton1->setFlat(true);
        topButton6 = new QPushButton(topButtonBar);
        topButton6->setObjectName(QStringLiteral("topButton6"));
        topButton6->setGeometry(QRect(625, 10, 120, 49));
        topButton6->setFocusPolicy(Qt::StrongFocus);
        topButton6->setStyleSheet(QLatin1String("#topButtonBar{\n"
"    border:1px;\n"
"    border-left-style:solid;\n"
"    border-left-color:black;\n"
"}"));
        topButton6->setCheckable(true);
        topButton6->setAutoExclusive(false);
        topButton2 = new QPushButton(topButtonBar);
        topButton2->setObjectName(QStringLiteral("topButton2"));
        topButton2->setGeometry(QRect(133, 10, 120, 49));
        topButton2->setFocusPolicy(Qt::StrongFocus);
        topButton2->setStyleSheet(QLatin1String("#topButtonBar{\n"
"    border:1px;\n"
"    border-left-style:solid;\n"
"    border-left-color:black;\n"
"}"));
        topButton2->setCheckable(true);
        topButton2->setAutoExclusive(false);
        topButton3 = new QPushButton(topButtonBar);
        topButton3->setObjectName(QStringLiteral("topButton3"));
        topButton3->setGeometry(QRect(256, 10, 120, 49));
        topButton3->setFont(font);
        topButton3->setFocusPolicy(Qt::StrongFocus);
        topButton3->setStyleSheet(QLatin1String("#topButtonBar{\n"
"    border:1px;\n"
"    border-left-style:solid;\n"
"    border-left-color:black;\n"
"}\n"
"QPushButton{\n"
" font-size:20px;\n"
"}"));
        topButton3->setCheckable(true);
        topButton3->setChecked(false);
        topButton3->setAutoExclusive(false);
        topButton4 = new QPushButton(topButtonBar);
        topButton4->setObjectName(QStringLiteral("topButton4"));
        topButton4->setGeometry(QRect(379, 10, 120, 49));
        topButton4->setFocusPolicy(Qt::StrongFocus);
        topButton4->setStyleSheet(QLatin1String("#topButtonBar{\n"
"    border:1px;\n"
"    border-left-style:solid;\n"
"    border-left-color:black;\n"
"}"));
        topButton4->setCheckable(true);
        topButton4->setAutoExclusive(false);
        topButton9 = new QPushButton(topButtonBar);
        topButton9->setObjectName(QStringLiteral("topButton9"));
        topButton9->setGeometry(QRect(994, 10, 120, 49));
        topButton9->setFont(font);
        topButton9->setFocusPolicy(Qt::StrongFocus);
        topButton9->setStyleSheet(QLatin1String("#topButtonBar{\n"
"    border:1px;\n"
"    border-left-style:solid;\n"
"    border-left-color:black;\n"
"}\n"
"QPushButton{\n"
" font-size:20px;\n"
"}"));
        topButton9->setCheckable(true);
        topButton9->setChecked(false);
        topButton9->setAutoExclusive(false);
        topButton10 = new QPushButton(topButtonBar);
        topButton10->setObjectName(QStringLiteral("topButton10"));
        topButton10->setGeometry(QRect(1116, 10, 70, 45));
        topButton10->setFocusPolicy(Qt::NoFocus);
        topButton10->setCheckable(true);
        topButton11 = new QPushButton(topButtonBar);
        topButton11->setObjectName(QStringLiteral("topButton11"));
        topButton11->setGeometry(QRect(1198, 10, 70, 45));
        topButton11->setFocusPolicy(Qt::NoFocus);
        topButton11->setCheckable(true);
        rightButtonBar = new QWidget(BitSA);
        rightButtonBar->setObjectName(QStringLiteral("rightButtonBar"));
        rightButtonBar->setGeometry(QRect(1196, 65, 83, 648));
        rightButtonBar->setMinimumSize(QSize(0, 0));
        rightButtonBar->setMaximumSize(QSize(16777215, 16777215));
        rightButtonBar->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(rightButtonBar);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 0, 0);
        rightButton1 = new QPushButton(rightButtonBar);
        rightButton1->setObjectName(QStringLiteral("rightButton1"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(rightButton1->sizePolicy().hasHeightForWidth());
        rightButton1->setSizePolicy(sizePolicy);
        rightButton1->setMinimumSize(QSize(80, 55));
        rightButton1->setMaximumSize(QSize(80, 55));
        rightButton1->setFocusPolicy(Qt::NoFocus);
        rightButton1->setCheckable(false);
        rightButton1->setAutoExclusive(false);
        rightButton1->setFlat(false);

        verticalLayout->addWidget(rightButton1);

        rightButton2 = new QPushButton(rightButtonBar);
        rightButton2->setObjectName(QStringLiteral("rightButton2"));
        sizePolicy.setHeightForWidth(rightButton2->sizePolicy().hasHeightForWidth());
        rightButton2->setSizePolicy(sizePolicy);
        rightButton2->setMinimumSize(QSize(80, 55));
        rightButton2->setMaximumSize(QSize(80, 55));
        rightButton2->setFocusPolicy(Qt::NoFocus);
        rightButton2->setCheckable(false);
        rightButton2->setAutoExclusive(false);
        rightButton2->setFlat(false);

        verticalLayout->addWidget(rightButton2);

        rightButton3 = new QPushButton(rightButtonBar);
        rightButton3->setObjectName(QStringLiteral("rightButton3"));
        sizePolicy.setHeightForWidth(rightButton3->sizePolicy().hasHeightForWidth());
        rightButton3->setSizePolicy(sizePolicy);
        rightButton3->setMinimumSize(QSize(80, 55));
        rightButton3->setMaximumSize(QSize(80, 55));
        rightButton3->setFocusPolicy(Qt::NoFocus);
        rightButton3->setCheckable(false);
        rightButton3->setAutoExclusive(false);
        rightButton3->setFlat(false);

        verticalLayout->addWidget(rightButton3);

        rightButton4 = new QPushButton(rightButtonBar);
        rightButton4->setObjectName(QStringLiteral("rightButton4"));
        sizePolicy.setHeightForWidth(rightButton4->sizePolicy().hasHeightForWidth());
        rightButton4->setSizePolicy(sizePolicy);
        rightButton4->setMinimumSize(QSize(80, 55));
        rightButton4->setMaximumSize(QSize(80, 55));
        rightButton4->setFocusPolicy(Qt::NoFocus);
        rightButton4->setStyleSheet(QStringLiteral(""));
        rightButton4->setCheckable(true);
        rightButton4->setAutoExclusive(false);
        rightButton4->setFlat(false);

        verticalLayout->addWidget(rightButton4);

        rightButton5 = new QPushButton(rightButtonBar);
        rightButton5->setObjectName(QStringLiteral("rightButton5"));
        sizePolicy.setHeightForWidth(rightButton5->sizePolicy().hasHeightForWidth());
        rightButton5->setSizePolicy(sizePolicy);
        rightButton5->setMinimumSize(QSize(80, 55));
        rightButton5->setMaximumSize(QSize(80, 55));
        rightButton5->setFocusPolicy(Qt::NoFocus);
        rightButton5->setCheckable(false);
        rightButton5->setAutoExclusive(false);
        rightButton5->setFlat(false);

        verticalLayout->addWidget(rightButton5);

        rightButton6 = new QPushButton(rightButtonBar);
        rightButton6->setObjectName(QStringLiteral("rightButton6"));
        sizePolicy.setHeightForWidth(rightButton6->sizePolicy().hasHeightForWidth());
        rightButton6->setSizePolicy(sizePolicy);
        rightButton6->setMinimumSize(QSize(80, 55));
        rightButton6->setMaximumSize(QSize(80, 55));
        rightButton6->setFocusPolicy(Qt::NoFocus);
        rightButton6->setCheckable(false);
        rightButton6->setAutoExclusive(false);
        rightButton6->setFlat(false);

        verticalLayout->addWidget(rightButton6);

        rightButton7 = new QPushButton(rightButtonBar);
        rightButton7->setObjectName(QStringLiteral("rightButton7"));
        sizePolicy.setHeightForWidth(rightButton7->sizePolicy().hasHeightForWidth());
        rightButton7->setSizePolicy(sizePolicy);
        rightButton7->setMinimumSize(QSize(80, 55));
        rightButton7->setMaximumSize(QSize(80, 55));
        rightButton7->setFocusPolicy(Qt::NoFocus);
        rightButton7->setCheckable(false);
        rightButton7->setAutoExclusive(false);
        rightButton7->setFlat(false);

        verticalLayout->addWidget(rightButton7);

        rightButton8 = new QPushButton(rightButtonBar);
        rightButton8->setObjectName(QStringLiteral("rightButton8"));
        sizePolicy.setHeightForWidth(rightButton8->sizePolicy().hasHeightForWidth());
        rightButton8->setSizePolicy(sizePolicy);
        rightButton8->setMinimumSize(QSize(80, 55));
        rightButton8->setMaximumSize(QSize(80, 55));
        rightButton8->setFocusPolicy(Qt::NoFocus);
        rightButton8->setCheckable(false);
        rightButton8->setChecked(false);
        rightButton8->setAutoExclusive(false);
        rightButton8->setFlat(false);

        verticalLayout->addWidget(rightButton8);

        rightButton9 = new QPushButton(rightButtonBar);
        rightButton9->setObjectName(QStringLiteral("rightButton9"));
        sizePolicy.setHeightForWidth(rightButton9->sizePolicy().hasHeightForWidth());
        rightButton9->setSizePolicy(sizePolicy);
        rightButton9->setMinimumSize(QSize(80, 55));
        rightButton9->setMaximumSize(QSize(80, 55));
        rightButton9->setFocusPolicy(Qt::NoFocus);
        rightButton9->setCheckable(true);
        rightButton9->setAutoExclusive(false);
        rightButton9->setFlat(false);

        verticalLayout->addWidget(rightButton9);

        verticalSpacer = new QSpacerItem(20, 83, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        rightButton10 = new QPushButton(rightButtonBar);
        rightButton10->setObjectName(QStringLiteral("rightButton10"));
        sizePolicy.setHeightForWidth(rightButton10->sizePolicy().hasHeightForWidth());
        rightButton10->setSizePolicy(sizePolicy);
        rightButton10->setMinimumSize(QSize(80, 55));
        rightButton10->setMaximumSize(QSize(80, 55));
        rightButton10->setFocusPolicy(Qt::NoFocus);
        rightButton10->setCheckable(true);
        rightButton10->setAutoExclusive(false);
        rightButton10->setFlat(false);

        verticalLayout->addWidget(rightButton10);

        buttomMarker = new QWidget(BitSA);
        buttomMarker->setObjectName(QStringLiteral("buttomMarker"));
        buttomMarker->setGeometry(QRect(255, 641, 941, 72));
        buttomMarker->setFocusPolicy(Qt::NoFocus);
        buttomMarker->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#BitSA[status  =  \"indoor\"] #buttomMarker\n"
"{\n"
"	background-color:rgb(76,76,76);\n"
"	border:2px;\n"
"    border-style:flat;\n"
"	border-bottom-style:solid;\n"
"	border-bottom-color: black;\n"
"	border-right-width:0px;\n"
"}\n"
"#BitSA[status  =  \"indoor\"] #buttomMarker>QPushButton\n"
"{\n"
"	font: 75 12px \"Arial\";\n"
"	text-align:left;\n"
"	font-size:12px;\n"
"	color:white;\n"
"	padding: 4px 7px 4px 8px;\n"
"	border:1px solid rgba(142,142,142,1);\n"
"	background-color:rgb(76,76,76);\n"
"}\n"
"\n"
"#BitSA[status  =  \"indoor\"] #buttomMarker>QPushButton:checked\n"
"{\n"
"	border:1px solid rgba(240,179,29,1);\n"
"}\n"
"\n"
"#BitSA[status  =  \"indoor\"] #buttomMarker>QPushButton>QLabel\n"
"{\n"
"	text-align:left;\n"
"	font: 75 12px \"Arial\";\n"
"	color:white;\n"
"	padding: 4px 7px 4px 6px;\n"
"    border-style:flat;\n"
"}\n"
"\n"
"#BitSA[status = \"indoor\"] #buttomMarker>#pb_marker_AllOff\n"
"{\n"
"	color:rgba(255,255,255,1);\n"
"    border-style"
                        ":flat;\n"
"	border-image: url(:/sa/image/btn_w70_normal.png);\n"
"}\n"
"#BitSA[status = \"indoor\"] #buttomMarker>#pb_marker_AllOff:pressed\n"
"{\n"
"	border-image: url(:/sa/image/btn_w70_click.png);\n"
"}\n"
"/*******************outdoor**********************/\n"
"#BitSA[status  =  \"outdoor\"] #buttomMarker\n"
"{\n"
"	background-color:rgb(255,255,255);\n"
"	border:2px;\n"
"    border-style:flat;\n"
"	border-bottom-style:solid;\n"
"	border-bottom-color: white;\n"
"	border-right-style:solid;\n"
"	border-right-color: white;\n"
"}\n"
"#BitSA[status  =  \"outdoor\"] #buttomMarker>QPushButton\n"
"{\n"
"	text-align:left;\n"
"	font-size:12px;	\n"
"	color:rgb(0,0,0);\n"
"	padding: 4px 7px 4px 8px;\n"
"	border: 1px solid rgb(174,174,174);\n"
"	background-color:rgb(255,255,255);\n"
"}\n"
"\n"
"#BitSA[status  =  \"outdoor\"] #buttomMarker>QPushButton:checked\n"
"{\n"
"	border:1px solid rgba(240,179,29,1);\n"
"}\n"
"\n"
"#BitSA[status  =  \"outdoor\"] #buttomMarker>QPushButton>QLabel\n"
"{\n"
"	text-align:left;\n"
"	font-"
                        "size:12px;\n"
"	color:black;\n"
"	padding: 4px 7px 4px 8px;\n"
"}\n"
"\n"
"#BitSA[status = \"outdoor\"] #buttomMarker>#pb_marker_AllOff\n"
"{\n"
"    border-style:flat;\n"
"	color: rgb(0, 0, 0);\n"
"	border-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"}\n"
"#BitSA[status = \"outdoor\"] #buttomMarker>#pb_marker_AllOff:pressed\n"
"{\n"
"	color: rgb(255, 255, 255);\n"
"	border-image: url(:/sa/image/outdoor/btn_w70_click.png);\n"
"}\n"
"/*******************night**********************/\n"
"#BitSA[status  =  \"night\"] #buttomMarker\n"
"{\n"
"	background-color:rgba(74,65,49,1);\n"
"	border:2px;\n"
"    border-style:flat;\n"
"	border-bottom-style:solid;\n"
"	border-bottom-color: black;\n"
"	border-right-style:solid;\n"
"	border-right-color: black;\n"
"}\n"
"#BitSA[status  =  \"night\"] #buttomMarker>QPushButton\n"
"{\n"
"	text-align:left;\n"
"	font-size:12px;\n"
"	color:white;\n"
"	padding: 4px 7px 4px 8px;\n"
"	border:1px solid rgba(139,121,92,1);\n"
"	background-color:rgba(255,255,255,0);\n"
"}\n"
"\n"
"#"
                        "BitSA[status  =  \"night\"] #buttomMarker>QPushButton:checked\n"
"{\n"
"	border:1px solid rgba(218,144,22,1);\n"
"}\n"
"\n"
"#BitSA[status  =  \"night\"] #buttomMarker>QPushButton>QLabel\n"
"{\n"
"	text-align:left;\n"
"	font-size:12px;\n"
"	color:white;\n"
"	padding: 4px 7px 4px 8px;\n"
"	color:#FBDBA7;\n"
"}\n"
"\n"
"\n"
"#BitSA[status = \"night\"] #buttomMarker>#pb_marker_AllOff\n"
"{\n"
"    border-style:flat;\n"
"	color:#FBDBA7;\n"
"    border-image: url(:/sa/image/night/btn_w70_normal.png);\n"
"}\n"
"#BitSA[status = \"night\"] #buttomMarker>#pb_marker_AllOff:pressed\n"
"{\n"
"	color:#FBDBA7;\n"
"    border-image: url(:/sa/image/night/btn_w70_click.png);\n"
"}\n"
""));
        horizontalLayout_2 = new QHBoxLayout(buttomMarker);
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(10, 10, 23, 12);
        pb_marker_AllOff = new QPushButton(buttomMarker);
        pb_marker_AllOff->setObjectName(QStringLiteral("pb_marker_AllOff"));
        sizePolicy.setHeightForWidth(pb_marker_AllOff->sizePolicy().hasHeightForWidth());
        pb_marker_AllOff->setSizePolicy(sizePolicy);
        pb_marker_AllOff->setMinimumSize(QSize(70, 50));
        pb_marker_AllOff->setMaximumSize(QSize(70, 50));
        pb_marker_AllOff->setFocusPolicy(Qt::NoFocus);
        pb_marker_AllOff->setStyleSheet(QLatin1String("font-weight:bold;\n"
"padding-top:18px; \n"
"/*padding-right:8px; */\n"
"padding-bottom:17px; \n"
"padding-left:12px;"));

        horizontalLayout_2->addWidget(pb_marker_AllOff);

        pb_marker_1 = new QPushButton(buttomMarker);
        pb_marker_1->setObjectName(QStringLiteral("pb_marker_1"));
        pb_marker_1->setMinimumSize(QSize(0, 50));
        pb_marker_1->setFocusPolicy(Qt::NoFocus);
        pb_marker_1->setContextMenuPolicy(Qt::DefaultContextMenu);
        pb_marker_1->setStyleSheet(QStringLiteral(""));
        pb_marker_1->setCheckable(true);
        pb_marker_1->setChecked(true);
        pb_marker_1->setAutoExclusive(true);

        horizontalLayout_2->addWidget(pb_marker_1);

        pb_marker_2 = new QPushButton(buttomMarker);
        pb_marker_2->setObjectName(QStringLiteral("pb_marker_2"));
        pb_marker_2->setMinimumSize(QSize(0, 50));
        pb_marker_2->setFocusPolicy(Qt::NoFocus);
        pb_marker_2->setStyleSheet(QStringLiteral(""));
        pb_marker_2->setCheckable(true);
        pb_marker_2->setChecked(false);
        pb_marker_2->setAutoExclusive(true);

        horizontalLayout_2->addWidget(pb_marker_2);

        pb_marker_3 = new QPushButton(buttomMarker);
        pb_marker_3->setObjectName(QStringLiteral("pb_marker_3"));
        pb_marker_3->setMinimumSize(QSize(0, 50));
        pb_marker_3->setFocusPolicy(Qt::NoFocus);
        pb_marker_3->setStyleSheet(QStringLiteral(""));
        pb_marker_3->setCheckable(true);
        pb_marker_3->setChecked(false);
        pb_marker_3->setAutoExclusive(true);

        horizontalLayout_2->addWidget(pb_marker_3);

        pb_marker_4 = new QPushButton(buttomMarker);
        pb_marker_4->setObjectName(QStringLiteral("pb_marker_4"));
        pb_marker_4->setMinimumSize(QSize(0, 50));
        pb_marker_4->setFocusPolicy(Qt::NoFocus);
        pb_marker_4->setStyleSheet(QStringLiteral(""));
        pb_marker_4->setCheckable(true);
        pb_marker_4->setChecked(false);
        pb_marker_4->setAutoExclusive(true);

        horizontalLayout_2->addWidget(pb_marker_4);

        pb_marker_5 = new QPushButton(buttomMarker);
        pb_marker_5->setObjectName(QStringLiteral("pb_marker_5"));
        pb_marker_5->setMinimumSize(QSize(0, 50));
        pb_marker_5->setFocusPolicy(Qt::NoFocus);
        pb_marker_5->setStyleSheet(QStringLiteral(""));
        pb_marker_5->setCheckable(true);
        pb_marker_5->setAutoExclusive(true);

        horizontalLayout_2->addWidget(pb_marker_5);

        pb_marker_6 = new QPushButton(buttomMarker);
        pb_marker_6->setObjectName(QStringLiteral("pb_marker_6"));
        pb_marker_6->setMinimumSize(QSize(0, 50));
        pb_marker_6->setFocusPolicy(Qt::NoFocus);
        pb_marker_6->setStyleSheet(QStringLiteral(""));
        pb_marker_6->setCheckable(true);
        pb_marker_6->setAutoExclusive(true);

        horizontalLayout_2->addWidget(pb_marker_6);

        horizontalLayout_2->setStretch(0, 7);
        horizontalLayout_2->setStretch(1, 13);
        horizontalLayout_2->setStretch(2, 13);
        horizontalLayout_2->setStretch(3, 13);
        horizontalLayout_2->setStretch(4, 13);
        horizontalLayout_2->setStretch(5, 13);
        horizontalLayout_2->setStretch(6, 13);
        leftWidget = new QWidget(BitSA);
        leftWidget->setObjectName(QStringLiteral("leftWidget"));
        leftWidget->setGeometry(QRect(1, 65, 283, 648));
        leftWidget->setStyleSheet(QStringLiteral(""));
        horizontalLayout = new QHBoxLayout(leftWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        leftInfoWidget = new QWidget(leftWidget);
        leftInfoWidget->setObjectName(QStringLiteral("leftInfoWidget"));
        leftInfoWidget->setMinimumSize(QSize(253, 0));
        leftInfoWidget->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#BitSA[status  =  \"indoor\"] #leftInfoWidget\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-size:13px;\n"
"   border:2px;\n"
"   border-right-style:solid;\n"
"	border-right-color:rgba(76,76,76,1);\n"
"}\n"
"#BitSA[status  =  \"indoor\"] #leftInfoWidget>QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid rgba(151,151,151,1);\n"
"}\n"
"\n"
"#BitSA[status  =  \"indoor\"] QLabel\n"
"{\n"
"	\n"
"	border-style:flat;\n"
"	font-size:12px;\n"
"}\n"
"#BitSA[status  =  \"indoor\"] QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"}\n"
"\n"
"\n"
"#BitSA[status  =  \"indoor\"] #lblT1\n"
"{\n"
"    color:rgba(255, 237, 0, 1);\n"
"}\n"
"#BitSA[status  =  \"indoor\"] #lblT2\n"
"{\n"
"    color:rgba(0, 255, 47, 1);\n"
"}\n"
"#BitSA[status  =  \"indoor\"] #lblT3\n"
"{\n"
"    color:rgba(0, 112, 255, 1);\n"
"}\n"
"#BitSA[status  =  \"indoor\"] #lblT4\n"
"{\n"
"    color:rgba(213, 135, 255, 1);\n"
"}\n"
"#BitSA[status  =  \"indoor\"] #lblT5\n"
"{\n"
""
                        "    color:rgba(39,255,252,1);\n"
"}\n"
"#BitSA[status  =  \"indoor\"] #lblT6\n"
"{\n"
"    color:rgba(255,159,0,1);\n"
"}\n"
"#BitSA[status  =  \"indoor\"] #lblTypeT1,\n"
"#BitSA[status  =  \"indoor\"] #lblTypeT2,\n"
"#BitSA[status  =  \"indoor\"] #lblTypeT3,\n"
"#BitSA[status  =  \"indoor\"] #lblTypeT4,\n"
"#BitSA[status  =  \"indoor\"] #lblTypeT5,\n"
"#BitSA[status  =  \"indoor\"] #lblTypeT6\n"
"{\n"
"	color:rgba(138, 138, 138, 1);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#BitSA[status  =  \"outdoor\"] #leftInfoWidget\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-size:13px;\n"
"   border:2px;\n"
"   border-right-style:solid;\n"
"	border-right-color:rgba(151,151,151,1);\n"
"\n"
"}\n"
"#BitSA[status  =  \"outdoor\"] #leftInfoWidget>QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid rgba(151,151,151,1);\n"
"}\n"
"#BitSA[status  =  \"outdoor\"] QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#BitSA[status  =  \"outdoor\"] QLabel\n"
"{\n"
"	"
                        "border-style:flat;\n"
"	font-size:12px;\n"
"}\n"
"#BitSA[status  =  \"outdoor\"] #lblT1\n"
"{\n"
"    color:rgba(255, 237, 0, 1);\n"
"}\n"
"#BitSA[status  =  \"outdoor\"] #lblT2\n"
"{\n"
"    color:rgba(0, 255, 47, 1);\n"
"}\n"
"#BitSA[status  =  \"outdoor\"] #lblT3\n"
"{\n"
"    color:rgba(0, 112, 255, 1);\n"
"}\n"
"#BitSA[status  =  \"outdoor\"] #lblT4\n"
"{\n"
"    color:rgba(213, 135, 255, 1);\n"
"}\n"
"#BitSA[status  =  \"outdoor\"] #lblT5\n"
"{\n"
"    color:rgba(39,255,252,1);\n"
"}\n"
"#BitSA[status  =  \"outdoor\"] #lblT6\n"
"{\n"
"    color:rgba(255,159,0,1);\n"
"}\n"
"#BitSA[status  =  \"outdoor\"] #lblTypeT1,\n"
"#BitSA[status  =  \"outdoor\"] #lblTypeT2,\n"
"#BitSA[status  =  \"outdoor\"] #lblTypeT3,\n"
"#BitSA[status  =  \"outdoor\"] #lblTypeT4,\n"
"#BitSA[status  =  \"outdoor\"] #lblTypeT5,\n"
"#BitSA[status  =  \"outdoor\"] #lblTypeT6\n"
"{\n"
"	color:rgba(138, 138, 138, 1);\n"
"}\n"
"/*******************night**********************/\n"
"#BitSA[status  =  \"night\"] #leftInfoWidget\n"
"{\n"
"	fo"
                        "nt: 75 13px \"Arial\";\n"
"	font-size:13px;\n"
"   border:2px;\n"
"   border-right-style:solid;\n"
"	border-right-color:rgba(123,109,82,1);\n"
"}\n"
"#BitSA[status  =  \"night\"] #leftInfoWidget>QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid #948262;\n"
"}\n"
"#BitSA[status  =  \"night\"] QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#BitSA[status  =  \"night\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	font-size:12px;\n"
"}\n"
"#BitSA[status  =  \"night\"] #lblT1\n"
"{\n"
"    color:rgba(255, 237, 0, 1);\n"
"}\n"
"#BitSA[status  =  \"night\"] #lblT2\n"
"{\n"
"    color:rgba(0, 255, 47, 1);\n"
"}\n"
"#BitSA[status  =  \"night\"] #lblT3\n"
"{\n"
"    color:rgba(0, 112, 255, 1);\n"
"}\n"
"#BitSA[status  =  \"night\"] #lblT4\n"
"{\n"
"    color:rgba(213, 135, 255, 1);\n"
"}\n"
"#BitSA[status  =  \"night\"] #lblT5\n"
"{\n"
"    color:rgba(39,255,252,1);\n"
"}\n"
"#BitSA[status  =  \"night\"] #lblT6\n"
"{\n"
"    color:rgba(255,159,0,1);\n"
"}\n"
"#BitSA[status  =  "
                        "\"night\"] #lblTypeT1,\n"
"#BitSA[status  =  \"night\"] #lblTypeT2,\n"
"#BitSA[status  =  \"night\"] #lblTypeT3,\n"
"#BitSA[status  =  \"night\"] #lblTypeT4,\n"
"#BitSA[status  =  \"night\"] #lblTypeT5,\n"
"#BitSA[status  =  \"night\"] #lblTypeT6\n"
"{\n"
"	color:rgba(138, 138, 138, 1);\n"
"}\n"
""));
        widget_mode = new SA_ClickedWidget(leftInfoWidget);
        widget_mode->setObjectName(QStringLiteral("widget_mode"));
        widget_mode->setGeometry(QRect(14, 20, 224, 70));
        widget_mode->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#BitSA[status  =  \"indoor\"] QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid rgba(151,151,151,1);\n"
"}\n"
"#BitSA[status  =  \"indoor\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	font-size:13px;\n"
"	color:rgb(255, 255, 255);\n"
"}\n"
"#BitSA[status  =  \"indoor\"] #lblmode\n"
"{\n"
"	color:rgba(240, 179, 29, 1);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#BitSA[status  =  \"outdoor\"] QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid rgba(151,151,151,1);\n"
"}\n"
"#BitSA[status  =  \"outdoor\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	font-size:13px;\n"
"		color:rgb(1,1,1);\n"
"}\n"
"#BitSA[status  =  \"outdoor\"] #lblmode\n"
"{\n"
"	color:rgba(240, 179, 29, 1);\n"
"}\n"
"/*******************night**********************/\n"
"#BitSA[status  =  \"night\"] QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid #948262;\n"
"}\n"
"#BitSA[status  =  \"night\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	fo"
                        "nt-size:13px;\n"
"	color:#FBDBA7;\n"
"}\n"
"#BitSA[status  =  \"night\"] #lblmode\n"
"{\n"
"	color:#EB9912;\n"
"}"));
        lblmeasure = new QLabel(widget_mode);
        lblmeasure->setObjectName(QStringLiteral("lblmeasure"));
        lblmeasure->setGeometry(QRect(7, 45, 201, 17));
        lblmeasure->setStyleSheet(QStringLiteral("font-weight:bold;"));
        lblmode = new QLabel(widget_mode);
        lblmode->setObjectName(QStringLiteral("lblmode"));
        lblmode->setGeometry(QRect(7, 25, 201, 17));
        lblmode->setStyleSheet(QStringLiteral("font-weight:bold;"));
        lblmodetitle = new QLabel(widget_mode);
        lblmodetitle->setObjectName(QStringLiteral("lblmodetitle"));
        lblmodetitle->setGeometry(QRect(7, 5, 201, 17));
        widget_Freq = new SA_ClickedWidget(leftInfoWidget);
        widget_Freq->setObjectName(QStringLiteral("widget_Freq"));
        widget_Freq->setGeometry(QRect(14, 100, 224, 70));
        widget_Freq->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#BitSA[status  =  \"indoor\"] QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid rgba(151,151,151,1);\n"
"}\n"
"#BitSA[status  =  \"indoor\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	font-size:13px;\n"
"	color:rgba(255, 255, 255, 1);\n"
"}\n"
"\n"
"\n"
"/*******************outdoor**********************/\n"
"#BitSA[status  =  \"outdoor\"] QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid rgba(151,151,151,1);\n"
"}\n"
"#BitSA[status  =  \"outdoor\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	font-size:13px;\n"
"   color:rgb(1,1,1);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#BitSA[status  =  \"night\"] QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid #948262;\n"
"}\n"
"#BitSA[status  =  \"night\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	font-size:13px;\n"
"	color:#FBDBA7;\n"
"}\n"
""));
        lblCenterFreq = new QLabel(widget_Freq);
        lblCenterFreq->setObjectName(QStringLiteral("lblCenterFreq"));
        lblCenterFreq->setGeometry(QRect(7, 5, 101, 17));
        lblChannel = new QLabel(widget_Freq);
        lblChannel->setObjectName(QStringLiteral("lblChannel"));
        lblChannel->setGeometry(QRect(7, 25, 101, 17));
        lblCHStandard = new QLabel(widget_Freq);
        lblCHStandard->setObjectName(QStringLiteral("lblCHStandard"));
        lblCHStandard->setGeometry(QRect(7, 45, 101, 17));
        lblCenterFreqValue = new QLabel(widget_Freq);
        lblCenterFreqValue->setObjectName(QStringLiteral("lblCenterFreqValue"));
        lblCenterFreqValue->setGeometry(QRect(99, 5, 121, 20));
        lblCenterFreqValue->setStyleSheet(QStringLiteral("font-weight:bold;"));
        lblCenterFreqValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblChannelValue = new QLabel(widget_Freq);
        lblChannelValue->setObjectName(QStringLiteral("lblChannelValue"));
        lblChannelValue->setGeometry(QRect(109, 25, 111, 17));
        lblChannelValue->setStyleSheet(QStringLiteral("font-weight:bold;"));
        lblChannelValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblCHStandardValue = new QLabel(widget_Freq);
        lblCHStandardValue->setObjectName(QStringLiteral("lblCHStandardValue"));
        lblCHStandardValue->setGeometry(QRect(109, 45, 111, 17));
        lblCHStandardValue->setStyleSheet(QStringLiteral("font-weight:bold;"));
        lblCHStandardValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        widget_Ampt = new SA_ClickedWidget(leftInfoWidget);
        widget_Ampt->setObjectName(QStringLiteral("widget_Ampt"));
        widget_Ampt->setGeometry(QRect(14, 180, 224, 70));
        widget_Ampt->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#BitSA[status  =  \"indoor\"] QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid rgba(151,151,151,1);\n"
"}\n"
"#BitSA[status  =  \"indoor\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	font-size:13px;\n"
"	color:rgba(255, 255, 255, 1);\n"
"}\n"
"#BitSA[status  =  \"indoor\"] #lblOffsetType,\n"
"#BitSA[status  =  \"indoor\"] #lblAttenType\n"
"{\n"
"	color:rgba(240, 179, 29, 1);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#BitSA[status  =  \"outdoor\"] QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid rgba(151,151,151,1);\n"
"}\n"
"#BitSA[status  =  \"outdoor\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	font-size:13px;\n"
"   color:rgb(1,1,1);\n"
"}\n"
"#BitSA[status  =  \"outdoor\"] #lblOffsetType,\n"
"#BitSA[status  =  \"outdoor\"] #lblAttenType\n"
"{\n"
"	color:rgba(240, 179, 29, 1);\n"
"}\n"
"/*******************night**********************/\n"
"#BitSA[status  =  \"night\"] QWidget\n"
"{\n"
"	border-radius:2px;"
                        "	\n"
"	border:1px solid #948262;\n"
"}\n"
"#BitSA[status  =  \"night\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	font-size:13px;\n"
"	color:#FBDBA7;\n"
"}\n"
"#BitSA[status  =  \"night\"] #lblOffsetType,\n"
"#BitSA[status  =  \"night\"] #lblAttenType\n"
"{\n"
"	color:#EB9912;\n"
"}"));
        lblOffset = new QLabel(widget_Ampt);
        lblOffset->setObjectName(QStringLiteral("lblOffset"));
        lblOffset->setGeometry(QRect(7, 45, 111, 17));
        lblAtten = new QLabel(widget_Ampt);
        lblAtten->setObjectName(QStringLiteral("lblAtten"));
        lblAtten->setGeometry(QRect(7, 25, 81, 17));
        lblPreamp = new QLabel(widget_Ampt);
        lblPreamp->setObjectName(QStringLiteral("lblPreamp"));
        lblPreamp->setGeometry(QRect(7, 5, 101, 17));
        lblAttenType = new QLabel(widget_Ampt);
        lblAttenType->setObjectName(QStringLiteral("lblAttenType"));
        lblAttenType->setGeometry(QRect(97, 25, 61, 17));
        lblAttenType->setStyleSheet(QStringLiteral("font-weight:bold;"));
        lblAttenValue = new QLabel(widget_Ampt);
        lblAttenValue->setObjectName(QStringLiteral("lblAttenValue"));
        lblAttenValue->setGeometry(QRect(157, 25, 61, 17));
        lblAttenValue->setStyleSheet(QStringLiteral("font-weight:bold;"));
        lblAttenValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblOffsetValue = new QLabel(widget_Ampt);
        lblOffsetValue->setObjectName(QStringLiteral("lblOffsetValue"));
        lblOffsetValue->setGeometry(QRect(157, 45, 61, 17));
        lblOffsetValue->setStyleSheet(QStringLiteral("font-weight:bold;"));
        lblOffsetValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblOffsetType = new QLabel(widget_Ampt);
        lblOffsetType->setObjectName(QStringLiteral("lblOffsetType"));
        lblOffsetType->setGeometry(QRect(107, 45, 61, 17));
        lblOffsetType->setStyleSheet(QStringLiteral("font-weight:bold;"));
        lblPreampValue = new QLabel(widget_Ampt);
        lblPreampValue->setObjectName(QStringLiteral("lblPreampValue"));
        lblPreampValue->setGeometry(QRect(157, 5, 61, 17));
        lblPreampValue->setStyleSheet(QStringLiteral("font-weight:bold;"));
        lblPreampValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        widget_BW = new SA_ClickedWidget(leftInfoWidget);
        widget_BW->setObjectName(QStringLiteral("widget_BW"));
        widget_BW->setGeometry(QRect(14, 260, 224, 70));
        widget_BW->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#BitSA[status  =  \"indoor\"] QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid rgba(151,151,151,1);\n"
"}\n"
"#BitSA[status  =  \"indoor\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	font-size:13px;\n"
"	color:rgba(255, 255, 255, 1);\n"
"}\n"
"#BitSA[status  =  \"indoor\"] #lblRBWType,   \n"
"#BitSA[status  =  \"indoor\"] #lblVBWType,   \n"
"#BitSA[status  =  \"indoor\"] #lblAveOn\n"
"{\n"
"	color:rgba(240, 179, 29, 1);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#BitSA[status  =  \"outdoor\"] QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid rgba(151,151,151,1);\n"
"}\n"
"#BitSA[status  =  \"outdoor\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	font-size:13px;\n"
"    color:rgb(1,1,1);\n"
"}\n"
"#BitSA[status  =  \"outdoor\"] #lblRBWType,   \n"
"#BitSA[status  =  \"outdoor\"] #lblVBWType,   \n"
"#BitSA[status  =  \"outdoor\"] #lblAveOn\n"
"{\n"
"	color:rgba(240, 179, 29, 1);\n"
"}\n"
"/*******************night"
                        "**********************/\n"
"#BitSA[status  =  \"night\"] QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid #948262;\n"
"}\n"
"#BitSA[status  =  \"night\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	font-size:13px;\n"
"	color:#FBDBA7;\n"
"}\n"
"#BitSA[status  =  \"night\"] #lblRBWType,   \n"
"#BitSA[status  =  \"night\"] #lblVBWType,   \n"
"#BitSA[status  =  \"night\"] #lblAveOn\n"
"{\n"
"	color:#EB9912;\n"
"}"));
        lblAverage = new SA_ClickedLabel(widget_BW);
        lblAverage->setObjectName(QStringLiteral("lblAverage"));
        lblAverage->setGeometry(QRect(7, 45, 71, 17));
        lblVBW = new QLabel(widget_BW);
        lblVBW->setObjectName(QStringLiteral("lblVBW"));
        lblVBW->setGeometry(QRect(7, 25, 41, 17));
        lblRBW = new QLabel(widget_BW);
        lblRBW->setObjectName(QStringLiteral("lblRBW"));
        lblRBW->setGeometry(QRect(7, 5, 41, 17));
        lblRBWType = new QLabel(widget_BW);
        lblRBWType->setObjectName(QStringLiteral("lblRBWType"));
        lblRBWType->setGeometry(QRect(57, 5, 61, 17));
        lblRBWType->setStyleSheet(QStringLiteral("font-weight:bold;"));
        lblVBWType = new QLabel(widget_BW);
        lblVBWType->setObjectName(QStringLiteral("lblVBWType"));
        lblVBWType->setGeometry(QRect(57, 25, 61, 17));
        lblVBWType->setStyleSheet(QStringLiteral("font-weight:bold;"));
        lblAverageValue = new SA_ClickedLabel(widget_BW);
        lblAverageValue->setObjectName(QStringLiteral("lblAverageValue"));
        lblAverageValue->setGeometry(QRect(117, 45, 101, 17));
        lblAverageValue->setStyleSheet(QStringLiteral("font-weight:bold;"));
        lblAverageValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblVBWValue = new QLabel(widget_BW);
        lblVBWValue->setObjectName(QStringLiteral("lblVBWValue"));
        lblVBWValue->setGeometry(QRect(117, 25, 101, 17));
        lblVBWValue->setStyleSheet(QStringLiteral("font-weight:bold;"));
        lblVBWValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblRBWValue = new QLabel(widget_BW);
        lblRBWValue->setObjectName(QStringLiteral("lblRBWValue"));
        lblRBWValue->setGeometry(QRect(117, 5, 101, 17));
        lblRBWValue->setStyleSheet(QStringLiteral("font-weight:bold;"));
        lblRBWValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblAveOn = new QLabel(widget_BW);
        lblAveOn->setObjectName(QStringLiteral("lblAveOn"));
        lblAveOn->setGeometry(QRect(81, 45, 61, 17));
        lblAveOn->setStyleSheet(QStringLiteral("font-weight:bold;"));
        widget_Sweep = new SA_ClickedWidget(leftInfoWidget);
        widget_Sweep->setObjectName(QStringLiteral("widget_Sweep"));
        widget_Sweep->setGeometry(QRect(14, 340, 224, 70));
        widget_Sweep->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#BitSA[status  =  \"indoor\"] QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid rgba(151,151,151,1);\n"
"}\n"
"#BitSA[status  =  \"indoor\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	font-size:13px;\n"
"	color:rgba(255, 255, 255, 1);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#BitSA[status  =  \"outdoor\"] QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid rgba(151,151,151,1);\n"
"}\n"
"#BitSA[status  =  \"outdoor\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	font-size:13px;\n"
"	color:rgb(1,1,1);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#BitSA[status  =  \"night\"] QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid #948262;\n"
"}\n"
"#BitSA[status  =  \"night\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	font-size:13px;\n"
"	color:#FBDBA7;\n"
"}\n"
""));
        lblDetectors = new SA_ClickedLabel(widget_Sweep);
        lblDetectors->setObjectName(QStringLiteral("lblDetectors"));
        lblDetectors->setGeometry(QRect(7, 45, 110, 17));
        label_25 = new QLabel(widget_Sweep);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(7, 25, 101, 17));
        lblSweepTime = new QLabel(widget_Sweep);
        lblSweepTime->setObjectName(QStringLiteral("lblSweepTime"));
        lblSweepTime->setGeometry(QRect(117, 25, 101, 17));
        lblSweepTime->setStyleSheet(QStringLiteral("font-weight:bold;"));
        lblSweepTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_27 = new QLabel(widget_Sweep);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(7, 5, 101, 17));
        lblSweepMode = new QLabel(widget_Sweep);
        lblSweepMode->setObjectName(QStringLiteral("lblSweepMode"));
        lblSweepMode->setGeometry(QRect(117, 5, 101, 17));
        lblSweepMode->setStyleSheet(QStringLiteral("font-weight:bold;"));
        lblSweepMode->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblDetectorValue = new SA_ClickedLabel(widget_Sweep);
        lblDetectorValue->setObjectName(QStringLiteral("lblDetectorValue"));
        lblDetectorValue->setGeometry(QRect(112, 45, 106, 17));
        lblDetectorValue->setStyleSheet(QStringLiteral("font-weight:bold;"));
        lblDetectorValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        widget_Trigger = new SA_ClickedWidget(leftInfoWidget);
        widget_Trigger->setObjectName(QStringLiteral("widget_Trigger"));
        widget_Trigger->setGeometry(QRect(14, 420, 224, 70));
        widget_Trigger->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#BitSA[status  =  \"indoor\"] QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid rgba(151,151,151,1);\n"
"}\n"
"#BitSA[status  =  \"indoor\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	font-size:13px;\n"
"	color:rgba(255, 255, 255, 1);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#BitSA[status  =  \"outdoor\"] QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid rgba(151,151,151,1);\n"
"}\n"
"#BitSA[status  =  \"outdoor\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	font-size:13px;\n"
"	color:rgb(1,1,1);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#BitSA[status  =  \"night\"] QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid #948262;\n"
"}\n"
"#BitSA[status  =  \"night\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	font-size:13px;\n"
"	color:#FBDBA7;\n"
"}\n"
""));
        lblIFOutPut = new SA_ClickedLabel(widget_Trigger);
        lblIFOutPut->setObjectName(QStringLiteral("lblIFOutPut"));
        lblIFOutPut->setGeometry(QRect(7, 45, 111, 17));
        label_31 = new QLabel(widget_Trigger);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(7, 25, 121, 17));
        lblIFOutPutValue = new SA_ClickedLabel(widget_Trigger);
        lblIFOutPutValue->setObjectName(QStringLiteral("lblIFOutPutValue"));
        lblIFOutPutValue->setGeometry(QRect(97, 45, 121, 17));
        lblIFOutPutValue->setStyleSheet(QStringLiteral("font-weight:bold;"));
        lblIFOutPutValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_33 = new SA_ClickedLabel(widget_Trigger);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setGeometry(QRect(7, 5, 121, 17));
        lblFreqRef = new SA_ClickedLabel(widget_Trigger);
        lblFreqRef->setObjectName(QStringLiteral("lblFreqRef"));
        lblFreqRef->setGeometry(QRect(107, 5, 111, 17));
        lblFreqRef->setStyleSheet(QStringLiteral("font-weight:bold;"));
        lblFreqRef->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblTrigger = new QLabel(widget_Trigger);
        lblTrigger->setObjectName(QStringLiteral("lblTrigger"));
        lblTrigger->setGeometry(QRect(97, 25, 121, 17));
        lblTrigger->setStyleSheet(QStringLiteral("font-weight:bold;"));
        lblTrigger->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        widget_Trace = new SA_ClickedWidget(leftInfoWidget);
        widget_Trace->setObjectName(QStringLiteral("widget_Trace"));
        widget_Trace->setGeometry(QRect(14, 560, 224, 49));
        widget_Trace->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#BitSA[status  =  \"indoor\"] QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid rgba(151,151,151,1);\n"
"}\n"
"#BitSA[status  =  \"indoor\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	/*font-size:13px;*/\n"
"    font:75 13px \"Arial\";\n"
"	color:rgba(255, 255, 255, 1);\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#BitSA[status  =  \"outdoor\"] QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid rgba(151,151,151,1);\n"
"}\n"
"#BitSA[status  =  \"outdoor\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	font:75 13px \"Arial\";\n"
"	/*font-size:13px;*/\n"
"	color:rgb(1,1,1);\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#BitSA[status  =  \"night\"] QWidget{\n"
"	border-radius:2px;	\n"
"	border:1px solid #948262;\n"
"}\n"
"#BitSA[status  =  \"night\"] QLabel{\n"
"	border-style:flat;\n"
"	font:75 13px \"Arial\";\n"
"	/*font-size:13px;*/\n"
"	color:#FBDBA7;"
                        "\n"
"	font-weight:bold;\n"
"}\n"
""));
        lblT2 = new QLabel(widget_Trace);
        lblT2->setObjectName(QStringLiteral("lblT2"));
        lblT2->setGeometry(QRect(83, 9, 17, 12));
        lblT2->setStyleSheet(QStringLiteral(""));
        lblT2->setAlignment(Qt::AlignCenter);
        lblT3 = new QLabel(widget_Trace);
        lblT3->setObjectName(QStringLiteral("lblT3"));
        lblT3->setGeometry(QRect(158, 9, 17, 12));
        lblT3->setStyleSheet(QStringLiteral(""));
        lblT3->setAlignment(Qt::AlignCenter);
        lblT4 = new QLabel(widget_Trace);
        lblT4->setObjectName(QStringLiteral("lblT4"));
        lblT4->setGeometry(QRect(8, 30, 17, 12));
        lblT4->setStyleSheet(QStringLiteral(""));
        lblT4->setAlignment(Qt::AlignCenter);
        lblT5 = new QLabel(widget_Trace);
        lblT5->setObjectName(QStringLiteral("lblT5"));
        lblT5->setGeometry(QRect(83, 30, 17, 12));
        lblT5->setStyleSheet(QStringLiteral(""));
        lblT5->setAlignment(Qt::AlignCenter);
        lblT6 = new QLabel(widget_Trace);
        lblT6->setObjectName(QStringLiteral("lblT6"));
        lblT6->setGeometry(QRect(158, 30, 17, 12));
        lblT6->setStyleSheet(QStringLiteral(""));
        lblT6->setAlignment(Qt::AlignCenter);
        lblTypeT4 = new QLabel(widget_Trace);
        lblTypeT4->setObjectName(QStringLiteral("lblTypeT4"));
        lblTypeT4->setGeometry(QRect(31, 30, 15, 12));
        lblTypeT4->setAlignment(Qt::AlignCenter);
        lblTypeT2 = new QLabel(widget_Trace);
        lblTypeT2->setObjectName(QStringLiteral("lblTypeT2"));
        lblTypeT2->setGeometry(QRect(105, 9, 15, 12));
        lblTypeT2->setAlignment(Qt::AlignCenter);
        lblTypeT5 = new QLabel(widget_Trace);
        lblTypeT5->setObjectName(QStringLiteral("lblTypeT5"));
        lblTypeT5->setGeometry(QRect(105, 30, 15, 12));
        lblTypeT5->setAlignment(Qt::AlignCenter);
        lblTypeT3 = new QLabel(widget_Trace);
        lblTypeT3->setObjectName(QStringLiteral("lblTypeT3"));
        lblTypeT3->setGeometry(QRect(181, 9, 15, 12));
        lblTypeT3->setAlignment(Qt::AlignCenter);
        lblTypeT6 = new QLabel(widget_Trace);
        lblTypeT6->setObjectName(QStringLiteral("lblTypeT6"));
        lblTypeT6->setGeometry(QRect(181, 30, 15, 12));
        lblTypeT6->setAlignment(Qt::AlignCenter);
        lblT1 = new QLabel(widget_Trace);
        lblT1->setObjectName(QStringLiteral("lblT1"));
        lblT1->setGeometry(QRect(8, 9, 17, 12));
        lblT1->setFont(font);
        lblT1->setStyleSheet(QStringLiteral(""));
        lblT1->setAlignment(Qt::AlignCenter);
        lblTypeT1 = new QLabel(widget_Trace);
        lblTypeT1->setObjectName(QStringLiteral("lblTypeT1"));
        lblTypeT1->setGeometry(QRect(31, 9, 15, 12));
        lblTypeT1->setAlignment(Qt::AlignCenter);
        lblbgT1 = new QLabel(widget_Trace);
        lblbgT1->setObjectName(QStringLiteral("lblbgT1"));
        lblbgT1->setGeometry(QRect(5, 7, 50, 15));
        lblbgT1->setStyleSheet(QStringLiteral(""));
        lblbgT4 = new QLabel(widget_Trace);
        lblbgT4->setObjectName(QStringLiteral("lblbgT4"));
        lblbgT4->setGeometry(QRect(5, 28, 50, 15));
        lblbgT4->setStyleSheet(QStringLiteral(""));
        lblbgT3 = new QLabel(widget_Trace);
        lblbgT3->setObjectName(QStringLiteral("lblbgT3"));
        lblbgT3->setGeometry(QRect(154, 7, 50, 15));
        lblbgT3->setStyleSheet(QStringLiteral(""));
        lblbgT6 = new QLabel(widget_Trace);
        lblbgT6->setObjectName(QStringLiteral("lblbgT6"));
        lblbgT6->setGeometry(QRect(154, 28, 50, 15));
        lblbgT6->setStyleSheet(QStringLiteral(""));
        lblbgT2 = new QLabel(widget_Trace);
        lblbgT2->setObjectName(QStringLiteral("lblbgT2"));
        lblbgT2->setGeometry(QRect(79, 7, 50, 15));
        lblbgT2->setStyleSheet(QStringLiteral(""));
        lblbgT5 = new QLabel(widget_Trace);
        lblbgT5->setObjectName(QStringLiteral("lblbgT5"));
        lblbgT5->setGeometry(QRect(79, 28, 50, 15));
        lblbgT5->setStyleSheet(QStringLiteral(""));
        lblbgT5->raise();
        lblbgT2->raise();
        lblbgT6->raise();
        lblbgT3->raise();
        lblbgT4->raise();
        lblbgT1->raise();
        lblT2->raise();
        lblT3->raise();
        lblT4->raise();
        lblT5->raise();
        lblT6->raise();
        lblTypeT4->raise();
        lblTypeT2->raise();
        lblTypeT5->raise();
        lblTypeT3->raise();
        lblTypeT6->raise();
        lblT1->raise();
        lblTypeT1->raise();
        widget_Limit = new SA_ClickedWidget(leftInfoWidget);
        widget_Limit->setObjectName(QStringLiteral("widget_Limit"));
        widget_Limit->setGeometry(QRect(14, 500, 224, 49));
        widget_Limit->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#BitSA[status  =  \"indoor\"] QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid rgba(151,151,151,1);\n"
"}\n"
"#BitSA[status  =  \"indoor\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	font-size:13px;\n"
"	color:rgba(255, 255, 255, 1);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#BitSA[status  =  \"outdoor\"] QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid rgba(151,151,151,1);\n"
"}\n"
"#BitSA[status  =  \"outdoor\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	font-size:13px;\n"
"	color:rgb(1,1,1);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#BitSA[status  =  \"night\"] QWidget\n"
"{\n"
"	border-radius:2px;	\n"
"	border:1px solid #948262;\n"
"}\n"
"#BitSA[status  =  \"night\"] QLabel\n"
"{\n"
"	border-style:flat;\n"
"	font-size:13px;\n"
"	color:#FBDBA7;\n"
"}\n"
""));
        lblLimit = new QLabel(widget_Limit);
        lblLimit->setObjectName(QStringLiteral("lblLimit"));
        lblLimit->setGeometry(QRect(7, 10, 101, 17));
        lblLimitStatus = new QLabel(widget_Limit);
        lblLimitStatus->setObjectName(QStringLiteral("lblLimitStatus"));
        lblLimitStatus->setGeometry(QRect(117, 10, 101, 17));
        lblLimitStatus->setStyleSheet(QStringLiteral("font-weight:bold;"));
        lblLimitStatus->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(leftInfoWidget);

        pb_left_hide = new QPushButton(leftWidget);
        pb_left_hide->setObjectName(QStringLiteral("pb_left_hide"));
        pb_left_hide->setMinimumSize(QSize(19, 80));
        pb_left_hide->setMaximumSize(QSize(29, 80));
        pb_left_hide->setStyleSheet(QStringLiteral(""));
        pb_left_hide->setCheckable(true);

        horizontalLayout->addWidget(pb_left_hide);

        wgT1 = new QWidget(BitSA);
        wgT1->setObjectName(QStringLiteral("wgT1"));
        wgT1->setGeometry(QRect(660, 430, 50, 15));

        retranslateUi(BitSA);

        QMetaObject::connectSlotsByName(BitSA);
    } // setupUi

    void retranslateUi(QWidget *BitSA)
    {
        BitSA->setWindowTitle(QApplication::translate("BitSA", "Form", Q_NULLPTR));
        BitSA->setProperty("status", QVariant(QApplication::translate("BitSA", "outdoor", Q_NULLPTR)));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("BitSA", "Frequency(MHz)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("BitSA", "Amplitude(dBm)", Q_NULLPTR));
        topButton5->setText(QApplication::translate("BitSA", "Trigger", Q_NULLPTR));
        topButton8->setText(QApplication::translate("BitSA", "Limit", Q_NULLPTR));
        topButton7->setText(QApplication::translate("BitSA", "Marker", Q_NULLPTR));
        topButton1->setText(QApplication::translate("BitSA", "Frequency", Q_NULLPTR));
        topButton6->setText(QApplication::translate("BitSA", "Trace", Q_NULLPTR));
        topButton2->setText(QApplication::translate("BitSA", "Amplitude", Q_NULLPTR));
        topButton3->setText(QApplication::translate("BitSA", "Sweep", Q_NULLPTR));
        topButton4->setText(QApplication::translate("BitSA", "Bandwidth", Q_NULLPTR));
        topButton9->setText(QApplication::translate("BitSA", "Measure", Q_NULLPTR));
        topButton10->setText(QString());
        topButton11->setText(QString());
        rightButton1->setText(QString());
        rightButton2->setText(QString());
        rightButton3->setText(QString());
        rightButton4->setText(QString());
        rightButton5->setText(QString());
        rightButton6->setText(QString());
        rightButton7->setText(QString());
        rightButton8->setText(QString());
        rightButton9->setText(QString());
        rightButton10->setText(QString());
        buttomMarker->setProperty("check", QVariant(QApplication::translate("BitSA", "true", Q_NULLPTR)));
        pb_marker_AllOff->setText(QApplication::translate("BitSA", "Clear All", Q_NULLPTR));
        pb_marker_1->setText(QString());
        pb_marker_1->setProperty("mode", QVariant(QApplication::translate("BitSA", "1", Q_NULLPTR)));
        pb_marker_2->setText(QString());
        pb_marker_2->setProperty("mode", QVariant(QApplication::translate("BitSA", "1", Q_NULLPTR)));
        pb_marker_3->setText(QString());
        pb_marker_3->setProperty("mode", QVariant(QApplication::translate("BitSA", "1", Q_NULLPTR)));
        pb_marker_4->setText(QString());
        pb_marker_4->setProperty("mode", QVariant(QApplication::translate("BitSA", "1", Q_NULLPTR)));
        pb_marker_5->setText(QString());
        pb_marker_5->setProperty("mode", QVariant(QApplication::translate("BitSA", "1", Q_NULLPTR)));
        pb_marker_6->setText(QString());
        pb_marker_6->setProperty("mode", QVariant(QApplication::translate("BitSA", "1", Q_NULLPTR)));
#ifndef QT_NO_WHATSTHIS
        leftInfoWidget->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        lblmeasure->setText(QApplication::translate("BitSA", "> Occupied BW", Q_NULLPTR));
        lblmode->setText(QApplication::translate("BitSA", "Spectrum Analyzer", Q_NULLPTR));
        lblmodetitle->setText(QApplication::translate("BitSA", "Mode", Q_NULLPTR));
        lblCenterFreq->setText(QApplication::translate("BitSA", "Center Freq", Q_NULLPTR));
        lblChannel->setText(QApplication::translate("BitSA", "Channel", Q_NULLPTR));
        lblCHStandard->setText(QApplication::translate("BitSA", "CH Standard", Q_NULLPTR));
        lblCenterFreqValue->setText(QApplication::translate("BitSA", "1.000 000 000 GHz", Q_NULLPTR));
        lblChannelValue->setText(QApplication::translate("BitSA", "----", Q_NULLPTR));
        lblCHStandardValue->setText(QApplication::translate("BitSA", "Band 0 (800)", Q_NULLPTR));
        lblOffset->setText(QApplication::translate("BitSA", "External Offset", Q_NULLPTR));
        lblAtten->setText(QApplication::translate("BitSA", "Attenuation", Q_NULLPTR));
        lblPreamp->setText(QApplication::translate("BitSA", "Preamp", Q_NULLPTR));
        lblAttenType->setText(QApplication::translate("BitSA", "Couple", Q_NULLPTR));
        lblAttenValue->setText(QApplication::translate("BitSA", "20 dB", Q_NULLPTR));
        lblOffsetValue->setText(QApplication::translate("BitSA", "0.00 dB", Q_NULLPTR));
        lblOffsetType->setText(QApplication::translate("BitSA", "On", Q_NULLPTR));
        lblPreampValue->setText(QApplication::translate("BitSA", "Off", Q_NULLPTR));
        lblAverage->setText(QApplication::translate("BitSA", "Average", Q_NULLPTR));
        lblVBW->setText(QApplication::translate("BitSA", "VBW", Q_NULLPTR));
        lblRBW->setText(QApplication::translate("BitSA", "RBW", Q_NULLPTR));
        lblRBWType->setText(QApplication::translate("BitSA", "Auto", Q_NULLPTR));
        lblVBWType->setText(QApplication::translate("BitSA", "Auto", Q_NULLPTR));
        lblAverageValue->setText(QApplication::translate("BitSA", "1/1", Q_NULLPTR));
        lblVBWValue->setText(QApplication::translate("BitSA", "100 kHz", Q_NULLPTR));
        lblRBWValue->setText(QApplication::translate("BitSA", "100 kHz", Q_NULLPTR));
        lblAveOn->setText(QApplication::translate("BitSA", "On", Q_NULLPTR));
        lblDetectors->setText(QApplication::translate("BitSA", "Detector", Q_NULLPTR));
        label_25->setText(QApplication::translate("BitSA", "Sweep Time", Q_NULLPTR));
        lblSweepTime->setText(QApplication::translate("BitSA", "50 ms", Q_NULLPTR));
        label_27->setText(QApplication::translate("BitSA", "Sweep Mode", Q_NULLPTR));
        lblSweepMode->setText(QApplication::translate("BitSA", "Continuous", Q_NULLPTR));
        lblDetectorValue->setText(QApplication::translate("BitSA", "Sample", Q_NULLPTR));
        lblIFOutPut->setText(QApplication::translate("BitSA", "IF OutPut", Q_NULLPTR));
        label_31->setText(QApplication::translate("BitSA", "Trigger Source", Q_NULLPTR));
        lblIFOutPutValue->setText(QApplication::translate("BitSA", "Internal", Q_NULLPTR));
        label_33->setText(QApplication::translate("BitSA", "Freq Reference", Q_NULLPTR));
        lblFreqRef->setText(QApplication::translate("BitSA", "Internal", Q_NULLPTR));
        lblTrigger->setText(QApplication::translate("BitSA", "Free Run", Q_NULLPTR));
        lblT2->setText(QApplication::translate("BitSA", "T2", Q_NULLPTR));
        lblT3->setText(QApplication::translate("BitSA", "T3", Q_NULLPTR));
        lblT4->setText(QApplication::translate("BitSA", "T4", Q_NULLPTR));
        lblT5->setText(QApplication::translate("BitSA", "T5", Q_NULLPTR));
        lblT6->setText(QApplication::translate("BitSA", "T6", Q_NULLPTR));
        lblTypeT4->setText(QString());
        lblTypeT2->setText(QString());
        lblTypeT5->setText(QString());
        lblTypeT3->setText(QString());
        lblTypeT6->setText(QString());
        lblT1->setText(QApplication::translate("BitSA", "T1", Q_NULLPTR));
        lblTypeT1->setText(QString());
        lblbgT1->setText(QString());
        lblbgT4->setText(QString());
        lblbgT3->setText(QString());
        lblbgT6->setText(QString());
        lblbgT2->setText(QString());
        lblbgT5->setText(QString());
        lblLimit->setText(QApplication::translate("BitSA", "Limit", Q_NULLPTR));
        lblLimitStatus->setText(QApplication::translate("BitSA", "Off", Q_NULLPTR));
        pb_left_hide->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BitSA: public Ui_BitSA {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BITSA_H
