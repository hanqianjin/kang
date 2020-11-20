/********************************************************************************
** Form generated from reading UI file 'sa_dialog_markersingle.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_MARKERSINGLE_H
#define UI_SA_DIALOG_MARKERSINGLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SA_Dialog_MarkerSingle
{
public:
    QWidget *widget;
    QLabel *lblFreq;
    QPushButton *pb_PeakSearch;
    QPushButton *pb_Delta;
    QPushButton *pb_Start;
    QFrame *line_2;
    QPushButton *pb_Normal;
    QPushButton *pb_Stop;
    QPushButton *pb_close;
    QPushButton *pb_NextPeak;
    QLabel *lblTitle;
    QFrame *line;
    QPushButton *pb_MinSearch;
    QPushButton *pb_PeakLeft;
    QLabel *lblAmpt;
    QPushButton *pb_Center;
    QPushButton *pb_PeakRight;
    QLabel *lblPeak;
    QLabel *lblMarkerTo;
    QPushButton *pb_Delta_Pair;
    QPushButton *pb_Mkr_On;
    QPushButton *pb_PeakTrack;
    QLabel *lblPeakTrack;
    QButtonGroup *MkrTypeGroup;

    void setupUi(QWidget *SA_Dialog_MarkerSingle)
    {
        if (SA_Dialog_MarkerSingle->objectName().isEmpty())
            SA_Dialog_MarkerSingle->setObjectName(QStringLiteral("SA_Dialog_MarkerSingle"));
        SA_Dialog_MarkerSingle->resize(252, 646);
        SA_Dialog_MarkerSingle->setStyleSheet(QLatin1String("/*******************common**********************/\n"
"#widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"#line_2\n"
"{\n"
"	background-color:rgb(119,119,119);\n"
"}\n"
"QPushButton\n"
"{\n"
"	color:rgb(123, 123, 123);\n"
"	border-style:flat;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"QPushButton\n"
"{\n"
"	color:rgb(87, 87, 87);\n"
"}\n"
"#widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#widget>#lblTitle\n"
"{	\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#widget>#lblAmpt,\n"
"#widget>#lblFreq\n"
"{	\n"
"	/*font: 75 13px \"Arial\";*/\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"\n"
"\n"
"#widget>#pb_Start:pressed,\n"
"#widget>#pb_Normal:checked\n"
"{\n"
"	color:rgba(87, 87, 87, 1);\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	"
                        "background-color:transparent;\n"
"}\n"
"#widget>#pb_Start,\n"
"#widget>#pb_Normal\n"
"{\n"
"	color:rgba(123, 123, 123, 1);\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"#widget>#pb_Stop:pressed,\n"
"#widget>#pb_Delta_Pair:checked\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"	color:rgba(87, 87, 87, 1);\n"
"}\n"
"\n"
"#widget>#pb_Stop,\n"
"#widget>#pb_Delta_Pair\n"
"{\n"
"	color:rgba(123, 123, 123, 1);\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#widget>#pb_Mkr_On,\n"
"#widget>#pb_PeakTrack\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	background-color:transparent;\n"
"	padding:7px 44px 6px 25px;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"#widget>#pb_Mkr_On:!checked,\n"
"#widget>#pb_PeakTrack"
                        ":!checked\n"
"{\n"
"	background-color:transparent;\n"
"	padding:7px 17px 6px 36px;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"#widget>#pb_PeakSearch,\n"
"#widget>#pb_MinSearch,\n"
"#widget>#pb_NextPeak,\n"
"#widget>#pb_PeakLeft,\n"
"#widget>#pb_PeakRight\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(255, 255, 255, 1);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"	text-align:center;\n"
"}\n"
"\n"
"#widget>#pb_PeakSearch:pressed,\n"
"#widget>#pb_MinSearch:pressed,\n"
"#widget>#pb_NextPeak:pressed,\n"
"#widget>#pb_PeakLeft:pressed,\n"
"#widget>#pb_PeakRight:pressed\n"
"{\n"
"	\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Di"
                        "alog_MarkerSingle[status  =  \"indoor\"] #line_2\n"
"{\n"
"	background-color:rgb(119,119,119);\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	color:rgb(87, 87, 87);;\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>QLabel\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#lblTitle\n"
"{	\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#lblAmpt,\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#lblFreq\n"
"{	\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #pb_close\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #pb_close:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_Start:pressed,\n"
"#SA_Dialog_MarkerS"
                        "ingle[status  =  \"indoor\"] #widget>#pb_Normal:checked\n"
"{\n"
"	color:rgba(87, 87, 87, 1);\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-color:transparent;\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_Start,\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_Normal\n"
"{\n"
"	color:rgba(123, 123, 123, 1);\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_Stop:pressed,\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_Delta_Pair:checked\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	color:rgba(87, 87, 87, 1);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_Stop,\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_Delta_Pair\n"
"{\n"
"	color:rgba(123, 123, 123, 1);\n"
"	background-color:transparent;\n"
"	background-image"
                        ": url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_Mkr_On,\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_PeakTrack\n"
"{\n"
"	background-color:transparent;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_Mkr_On:!checked,\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_PeakTrack:!checked\n"
"{\n"
"	background-color:transparent;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_PeakSearch,\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_MinSearch,\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_NextPeak,\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_PeakLeft,\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_PeakRight\n"
"{\n"
"	color:rgba(255, 2"
                        "55, 255, 1);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_PeakSearch:pressed,\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_MinSearch:pressed,\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_NextPeak:pressed,\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_PeakLeft:pressed,\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_PeakRight:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_Delta,\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_Center\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	background-image: url(:/sa/image/btn_peak_nor.png);\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_Center:pressed,\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] #widget>#pb_Delta:checked\n"
"{\n"
""
                        "	color:rgba(87, 87, 87, 1);\n"
"	background-image: url(:/sa/image/btn_peak_click.png);\n"
"} \n"
"\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget\n"
"{\n"
"		background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #line_2\n"
"{\n"
"	background-color:rgb(119,119,119);\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	color:rgb(87, 87, 87);;\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>QLabel\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#lblTitle\n"
"{	\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#lblAmpt,\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#lblFreq\n"
"{	\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#"
                        "SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #pb_close\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #pb_close:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_Start:pressed,\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_Normal:checked\n"
"{\n"
"	color:rgba(87, 87, 87, 1);\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-color:transparent;\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_Start,\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_Normal\n"
"{\n"
"	color:rgba(123, 123, 123, 1);\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_Stop:pressed,\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widge"
                        "t>#pb_Delta_Pair:checked\n"
"{\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	color:rgba(87, 87, 87, 1);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_Stop,\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_Delta_Pair\n"
"{\n"
"	color:rgba(123, 123, 123, 1);\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_Mkr_On,\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_PeakTrack\n"
"{\n"
"	background-color:transparent;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_Mkr_On:!checked,\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_PeakTrack:!checked\n"
"{\n"
"	background-color:transparent;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	border-image: url(:/sa/image/toggle_"
                        "off.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_PeakSearch,\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_MinSearch,\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_NextPeak,\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_PeakLeft,\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_PeakRight\n"
"{\n"
"	color:rgba(255, 255, 255, 1);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_PeakSearch:pressed,\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_MinSearch:pressed,\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_NextPeak:pressed,\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_PeakLeft:pressed,\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_PeakRight:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[statu"
                        "s  =  \"outdoor\"] #widget>#pb_Delta,\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_Center\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	background-image: url(:/sa/image/btn_peak_nor.png);\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_Center:pressed,\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] #widget>#pb_Delta:checked\n"
"{\n"
"	color:rgba(87, 87, 87, 1);\n"
"	background-image: url(:/sa/image/btn_peak_click.png);\n"
"} \n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget\n"
"{\n"
"	background-color:rgba(208,182,139,0.9);\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #line_2\n"
"{\n"
"	background-color:rgb(119,119,119);\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] QPushButton\n"
"{\n"
"	color:rgb(87, 87, 87);;\n"
"}\n"
""
                        "\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>QLabel\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#lblTitle\n"
"{	\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#lblAmpt,\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#lblFreq\n"
"{	\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #pb_close\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/sa/image/night/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #pb_close:pressed\n"
"{\n"
"	border-image: url(:/sa/image/night/btn_close_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_Start:pressed,\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_Normal:checked\n"
"{\n"
"	color:rgba(87, 87, 87, 1);\n"
"	background-image: url(:/sa/image/night/btn_left_click.png);\n"
"	background-color:transparent;\n"
"}\n"
""
                        "#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_Start,\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_Normal\n"
"{\n"
"	color:rgba(123, 123, 123, 1);\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/night/btn_left_nor.png);\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_Stop:pressed,\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_Delta_Pair:checked\n"
"{\n"
"	background-color:transparent;\n"
"	background-image:url(:/sa/image/night/btn_right_click.png);\n"
"	color:rgba(87, 87, 87, 1);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_Stop,\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_Delta_Pair\n"
"{\n"
"	color:rgba(123, 123, 123, 1);\n"
"	background-color:transparent;\n"
"	background-image: url(:/sa/image/night/btn_right_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_Mkr_On,\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_PeakTrack\n"
"{\n"
""
                        "	background-color:transparent;\n"
"	color:rgba(87, 87, 87, 1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_Mkr_On:!checked,\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_PeakTrack:!checked\n"
"{\n"
"	background-color:transparent;\n"
"	color:rgba(121,106,80,1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_PeakSearch,\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_MinSearch,\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_NextPeak,\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_PeakLeft,\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_PeakRight\n"
"{\n"
"	color:rgba(255, 255, 255, 1);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_PeakSearch:pressed,\n"
"#SA_Dialog_MarkerSingle[status  =  \""
                        "night\"] #widget>#pb_MinSearch:pressed,\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_NextPeak:pressed,\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_PeakLeft:pressed,\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_PeakRight:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_Delta,\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_Center\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(123, 123, 123, 1);\n"
"	background-image: url(:/sa/image/night/btn_center_nor.png);\n"
"}\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_Center:pressed,\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] #widget>#pb_Delta:checked\n"
"{\n"
"	color:rgba(87, 87, 87, 1);\n"
"	background-image: url(:/sa/image/night/btn_center_click.png);	\n"
"	\n"
"} \n"
""));
        widget = new QWidget(SA_Dialog_MarkerSingle);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 252, 646));
        lblFreq = new QLabel(widget);
        lblFreq->setObjectName(QStringLiteral("lblFreq"));
        lblFreq->setGeometry(QRect(5, 54, 131, 17));
        lblFreq->setLayoutDirection(Qt::LeftToRight);
        lblFreq->setAlignment(Qt::AlignCenter);
        pb_PeakSearch = new QPushButton(widget);
        pb_PeakSearch->setObjectName(QStringLiteral("pb_PeakSearch"));
        pb_PeakSearch->setGeometry(QRect(18, 277, 216, 30));
        pb_PeakSearch->setStyleSheet(QLatin1String("/*******************common**********************/\n"
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
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	color:rgba(255, 255, 255, 1);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	color:rgba(0, 0, 0, 1);\n"
"	border-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] QPushButton:pressed"
                        "\n"
"{\n"
"	border-image: url(:/sa/image/outdoor/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] QPushButton\n"
"{\n"
"	color: #FBDBA7;\n"
"	border-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] QPushButton:pressed\n"
"{	\n"
"	color:rgba(252, 220, 168, 1);\n"
"	border-image: url(:/sa/image/night/btn_w216_click.png);\n"
"}"));
        pb_Delta = new QPushButton(widget);
        MkrTypeGroup = new QButtonGroup(SA_Dialog_MarkerSingle);
        MkrTypeGroup->setObjectName(QStringLiteral("MkrTypeGroup"));
        MkrTypeGroup->addButton(pb_Delta);
        pb_Delta->setObjectName(QStringLiteral("pb_Delta"));
        pb_Delta->setGeometry(QRect(91, 141, 69, 30));
        pb_Delta->setCheckable(true);
        pb_Start = new QPushButton(widget);
        pb_Start->setObjectName(QStringLiteral("pb_Start"));
        pb_Start->setGeometry(QRect(18, 209, 69, 30));
        line_2 = new QFrame(widget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(140, 54, 2, 16));
        line_2->setLineWidth(0);
        line_2->setMidLineWidth(0);
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        pb_Normal = new QPushButton(widget);
        MkrTypeGroup->addButton(pb_Normal);
        pb_Normal->setObjectName(QStringLiteral("pb_Normal"));
        pb_Normal->setGeometry(QRect(18, 141, 69, 30));
        pb_Normal->setStyleSheet(QStringLiteral(""));
        pb_Normal->setCheckable(true);
        pb_Normal->setChecked(true);
        pb_Stop = new QPushButton(widget);
        pb_Stop->setObjectName(QStringLiteral("pb_Stop"));
        pb_Stop->setGeometry(QRect(164, 209, 69, 30));
        pb_close = new QPushButton(widget);
        pb_close->setObjectName(QStringLiteral("pb_close"));
        pb_close->setGeometry(QRect(212, 6, 35, 35));
        pb_NextPeak = new QPushButton(widget);
        pb_NextPeak->setObjectName(QStringLiteral("pb_NextPeak"));
        pb_NextPeak->setGeometry(QRect(18, 343, 216, 30));
        pb_NextPeak->setStyleSheet(QLatin1String("/*******************common**********************/\n"
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
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	color:rgba(255, 255, 255, 1);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	color:rgba(0, 0, 0, 1);\n"
"	border-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] QPushButton:pressed"
                        "\n"
"{\n"
"	border-image: url(:/sa/image/outdoor/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] QPushButton\n"
"{\n"
"	color: #FBDBA7;\n"
"	border-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] QPushButton:pressed\n"
"{\n"
"	color:rgba(252, 220, 168, 1);\n"
"	border-image: url(:/sa/image/night/btn_w216_click.png);\n"
"}"));
        lblTitle = new QLabel(widget);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));
        lblTitle->setGeometry(QRect(17, 19, 61, 22));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        lblTitle->setFont(font);
        line = new QFrame(widget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(18, 46, 212, 2));
        line->setLineWidth(0);
        line->setMidLineWidth(0);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        pb_MinSearch = new QPushButton(widget);
        pb_MinSearch->setObjectName(QStringLiteral("pb_MinSearch"));
        pb_MinSearch->setGeometry(QRect(18, 310, 216, 30));
        pb_MinSearch->setStyleSheet(QLatin1String("/*******************common**********************/\n"
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
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	color:rgba(255, 255, 255, 1);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	color:rgba(0, 0, 0, 1);\n"
"	border-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] QPushButton:pressed"
                        "\n"
"{\n"
"	border-image: url(:/sa/image/outdoor/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] QPushButton\n"
"{\n"
"	color: #FBDBA7;\n"
"	border-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] QPushButton:pressed\n"
"{\n"
"	color:rgba(252, 220, 168, 1);\n"
"	border-image: url(:/sa/image/night/btn_w216_click.png);\n"
"}"));
        pb_PeakLeft = new QPushButton(widget);
        pb_PeakLeft->setObjectName(QStringLiteral("pb_PeakLeft"));
        pb_PeakLeft->setGeometry(QRect(18, 376, 216, 30));
        pb_PeakLeft->setStyleSheet(QLatin1String("/*******************common**********************/\n"
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
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	color:rgba(255, 255, 255, 1);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	color:rgba(0, 0, 0, 1);\n"
"	border-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] QPushButton:pressed"
                        "\n"
"{\n"
"	border-image: url(:/sa/image/outdoor/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] QPushButton\n"
"{\n"
"	color: #FBDBA7;\n"
"	border-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] QPushButton:pressed\n"
"{	\n"
"	color:rgba(252, 220, 168, 1);\n"
"	border-image: url(:/sa/image/night/btn_w216_click.png);\n"
"}"));
        lblAmpt = new QLabel(widget);
        lblAmpt->setObjectName(QStringLiteral("lblAmpt"));
        lblAmpt->setGeometry(QRect(148, 53, 100, 20));
        lblAmpt->setAlignment(Qt::AlignCenter);
        pb_Center = new QPushButton(widget);
        pb_Center->setObjectName(QStringLiteral("pb_Center"));
        pb_Center->setGeometry(QRect(91, 209, 69, 30));
        pb_PeakRight = new QPushButton(widget);
        pb_PeakRight->setObjectName(QStringLiteral("pb_PeakRight"));
        pb_PeakRight->setGeometry(QRect(18, 409, 216, 30));
        pb_PeakRight->setStyleSheet(QLatin1String("/*******************common**********************/\n"
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
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	color:rgba(255, 255, 255, 1);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"indoor\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	color:rgba(0, 0, 0, 1);\n"
"	border-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"outdoor\"] QPushButton:pressed"
                        "\n"
"{\n"
"	border-image: url(:/sa/image/outdoor/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] QPushButton\n"
"{\n"
"	color: #FBDBA7;\n"
"	border-image: url(:/sa/image/btn_w216_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_MarkerSingle[status  =  \"night\"] QPushButton:pressed\n"
"{\n"
"	color:rgba(252, 220, 168, 1);\n"
"	border-image: url(:/sa/image/night/btn_w216_click.png);\n"
"}"));
        lblPeak = new QLabel(widget);
        lblPeak->setObjectName(QStringLiteral("lblPeak"));
        lblPeak->setGeometry(QRect(18, 259, 67, 15));
        lblMarkerTo = new QLabel(widget);
        lblMarkerTo->setObjectName(QStringLiteral("lblMarkerTo"));
        lblMarkerTo->setGeometry(QRect(18, 191, 75, 17));
        pb_Delta_Pair = new QPushButton(widget);
        MkrTypeGroup->addButton(pb_Delta_Pair);
        pb_Delta_Pair->setObjectName(QStringLiteral("pb_Delta_Pair"));
        pb_Delta_Pair->setGeometry(QRect(164, 141, 69, 30));
        pb_Delta_Pair->setCheckable(true);
        pb_Mkr_On = new QPushButton(widget);
        pb_Mkr_On->setObjectName(QStringLiteral("pb_Mkr_On"));
        pb_Mkr_On->setGeometry(QRect(17, 91, 90, 30));
        pb_Mkr_On->setCheckable(true);
        pb_PeakTrack = new QPushButton(widget);
        pb_PeakTrack->setObjectName(QStringLiteral("pb_PeakTrack"));
        pb_PeakTrack->setGeometry(QRect(94, 459, 90, 30));
        pb_PeakTrack->setFocusPolicy(Qt::NoFocus);
        pb_PeakTrack->setStyleSheet(QStringLiteral(""));
        pb_PeakTrack->setCheckable(true);
        lblPeakTrack = new QLabel(widget);
        lblPeakTrack->setObjectName(QStringLiteral("lblPeakTrack"));
        lblPeakTrack->setGeometry(QRect(18, 459, 71, 30));

        retranslateUi(SA_Dialog_MarkerSingle);

        QMetaObject::connectSlotsByName(SA_Dialog_MarkerSingle);
    } // setupUi

    void retranslateUi(QWidget *SA_Dialog_MarkerSingle)
    {
        SA_Dialog_MarkerSingle->setWindowTitle(QApplication::translate("SA_Dialog_MarkerSingle", "Form", 0));
#ifndef QT_NO_STATUSTIP
        SA_Dialog_MarkerSingle->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        SA_Dialog_MarkerSingle->setProperty("status", QVariant(QApplication::translate("SA_Dialog_MarkerSingle", "night", 0)));
        lblFreq->setText(QApplication::translate("SA_Dialog_MarkerSingle", "1.000 000 000 GHz", 0));
        pb_PeakSearch->setText(QApplication::translate("SA_Dialog_MarkerSingle", "Peak Search", 0));
        pb_PeakSearch->setShortcut(QString());
        pb_Delta->setText(QApplication::translate("SA_Dialog_MarkerSingle", "Delta", 0));
        pb_Start->setText(QApplication::translate("SA_Dialog_MarkerSingle", "Start", 0));
        pb_Normal->setText(QApplication::translate("SA_Dialog_MarkerSingle", "Normal", 0));
        pb_Stop->setText(QApplication::translate("SA_Dialog_MarkerSingle", "Stop", 0));
        pb_close->setText(QString());
        pb_NextPeak->setText(QApplication::translate("SA_Dialog_MarkerSingle", "Next Peak", 0));
        lblTitle->setText(QApplication::translate("SA_Dialog_MarkerSingle", "M2", 0));
        pb_MinSearch->setText(QApplication::translate("SA_Dialog_MarkerSingle", "Min Search", 0));
        pb_MinSearch->setShortcut(QString());
        pb_PeakLeft->setText(QApplication::translate("SA_Dialog_MarkerSingle", "Next Peak Left", 0));
        lblAmpt->setText(QApplication::translate("SA_Dialog_MarkerSingle", "-10.01 dB", 0));
        pb_Center->setText(QApplication::translate("SA_Dialog_MarkerSingle", "Center", 0));
        pb_PeakRight->setText(QApplication::translate("SA_Dialog_MarkerSingle", "Next Peak Right", 0));
        pb_PeakRight->setShortcut(QString());
        lblPeak->setText(QApplication::translate("SA_Dialog_MarkerSingle", "Peak", 0));
        lblMarkerTo->setText(QApplication::translate("SA_Dialog_MarkerSingle", "Marker to", 0));
        pb_Delta_Pair->setText(QApplication::translate("SA_Dialog_MarkerSingle", "Delta Pair", 0));
        pb_Mkr_On->setText(QApplication::translate("SA_Dialog_MarkerSingle", "Off", 0));
        pb_PeakTrack->setText(QApplication::translate("SA_Dialog_MarkerSingle", "Off", 0));
        lblPeakTrack->setText(QApplication::translate("SA_Dialog_MarkerSingle", "Peak\n"
"Track", 0));
    } // retranslateUi

};

namespace Ui {
    class SA_Dialog_MarkerSingle: public Ui_SA_Dialog_MarkerSingle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_MARKERSINGLE_H
