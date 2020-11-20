/********************************************************************************
** Form generated from reading UI file 'sa_dialog_freqsetup.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_FREQSETUP_H
#define UI_SA_DIALOG_FREQSETUP_H

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

class Ui_SA_Dialog_FreqSetup
{
public:
    QWidget *widget;
    QPushButton *pb_LastSpan;
    QLabel *lblStartFreq;
    QLabel *lblCenterFreq;
    QLabel *lblChNumber;
    SA_LineEdit *LedCHStandard;
    SA_LineEdit *LedStopFreq;
    QLabel *lblFreqStep;
    SA_LineEdit *LedCenterFreq;
    QLabel *lblChStep;
    QLabel *lblSpan;
    SA_LineEdit *LedStartFreq;
    SA_LineEdit *LedCHNum;
    SA_LineEdit *LedSpan;
    QLabel *lblFreqOffset;
    SA_LineEdit *LedFreqOffset;
    QPushButton *pb_FullSpan;
    SA_LineEdit *LedCHStep;
    QLabel *lblChStandard;
    QPushButton *pb_ZeroSpan;
    QLabel *lblStopFreq;
    SA_LineEdit *LedFreqStep;
    QLabel *lblChType;
    QPushButton *pb_Uplink;
    QPushButton *pb_Downlink;
    QLabel *lblTitle;
    QPushButton *pb_cancel;
    QFrame *line;
    QButtonGroup *SpanModebtnGp;
    QButtonGroup *ChannelType;

    void setupUi(QWidget *SA_Dialog_FreqSetup)
    {
        if (SA_Dialog_FreqSetup->objectName().isEmpty())
            SA_Dialog_FreqSetup->setObjectName(QStringLiteral("SA_Dialog_FreqSetup"));
        SA_Dialog_FreqSetup->resize(252, 646);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setBold(true);
        font.setWeight(75);
        SA_Dialog_FreqSetup->setFont(font);
        SA_Dialog_FreqSetup->setFocusPolicy(Qt::NoFocus);
        SA_Dialog_FreqSetup->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"] #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"] #widget>QPushButton\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"] #widget>QPushButton:checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"}\n"
"\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"] #pb_Uplink:checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"] #pb_Uplink:!checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"] #pb_Downlink:checked\n"
"{\n"
""
                        "	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"	\n"
"}\n"
"\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"] #pb_Downlink:!checked\n"
"{\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"] #widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"] SA_LineEdit,\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"] SA_LineEdit:disable\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(159,98,0,1);\n"
"	padding:8px 6px 7px 6px ;\n"
"	font: 75 12px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"] SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"]  #pb_cancel\n"
"{\n"
"backgr"
                        "ound-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"]  #pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_FreqSetup[status  =  \"outdoor\"] #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"outdoor\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_FreqSetup[status  =  \"outdoor\"] #widget>QPushButton\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"outdoor\"] #widget>QPushButton:checked\n"
"{\n"
"	color:rgba(87, 87, 87,1);\n"
"}\n"
"\n"
"#SA_Dialog_FreqSetup[status  =  \"outdoor\"] #pb_Uplink:checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"}\n"
"#SA_Dialog_FreqSetup[statu"
                        "s  =  \"outdoor\"] #pb_Uplink:!checked\n"
"{\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"}\n"
"\n"
"#SA_Dialog_FreqSetup[status  =  \"outdoor\"] #pb_Downlink:checked\n"
"{\n"
"padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_right.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#SA_Dialog_FreqSetup[status  =  \"outdoor\"] #pb_Downlink:!checked\n"
"{\n"
"padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/fre_checked_left.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"#SA_Dialog_FreqSetup[status  =  \"outdoor\"] #widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_FreqSetup[status  =  \"outdoor\"] SA_LineEdit,\n"
"#SA_Dialog_FreqSetup[status  =  \"outdoor\"] SA_LineEdit:disable\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 6px 7px 6px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_F"
                        "reqSetup[status  =  \"outdoor\"] SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"outdoor\"]  #pb_cancel\n"
"{\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"outdoor\"]  #pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"/*******************night**********************/\n"
"#SA_Dialog_FreqSetup[status  =  \"night\"] #widget\n"
"{\n"
"	background-color:rgba(208,182,139,0.9);\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"night\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_FreqSetup[status  =  \"night\"] #widget>QPushButton\n"
"{\n"
"	color:rgba(121,106,81,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"night\"] #widget>QPushButton:checked\n"
"{\n"
"	color:rgba(85,74,56,1"
                        ");\n"
"}\n"
"\n"
"#SA_Dialog_FreqSetup[status  =  \"night\"] #pb_Uplink\n"
"{\n"
"	color:rgba(121, 105, 80, 1);\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/night/btn_left_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_FreqSetup[status  =  \"night\"] #pb_Uplink:checked\n"
"{\n"
"	color:rgba(159, 98, 0, 1);\n"
"	padding: 8px 14px 7px 15px;\n"
"	background-image: url(:/sa/image/night/btn_left_click.png);\n"
"}\n"
"\n"
"\n"
"#SA_Dialog_FreqSetup[status  =  \"night\"] #pb_Downlink\n"
"{\n"
"	color:rgba(121, 105, 80, 1);\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image: url(:/sa/image/night/btn_right_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_FreqSetup[status  =  \"night\"] #pb_Downlink:checked\n"
"{\n"
"	color:rgba(159, 98, 0, 1);\n"
"	padding: 8px 5px 7px 6px;\n"
"	background-image:url(:/sa/image/night/btn_right_click.png);\n"
"}\n"
"\n"
"\n"
"\n"
"#SA_Dialog_FreqSetup[status  =  \"night\"] #widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_FreqSe"
                        "tup[status  =  \"night\"] SA_LineEdit,\n"
"#SA_Dialog_FreqSetup[status  =  \"night\"] SA_LineEdit:disable\n"
"{\n"
"	background: rgba(251,220,167,0.60);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 6px 7px 6px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"night\"] SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"night\"]  #pb_cancel\n"
"{\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/night/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"night\"]  #pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/night/btn_close_click.png);\n"
"}"));
        widget = new QWidget(SA_Dialog_FreqSetup);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 252, 646));
        widget->setStyleSheet(QStringLiteral(""));
        pb_LastSpan = new QPushButton(widget);
        SpanModebtnGp = new QButtonGroup(SA_Dialog_FreqSetup);
        SpanModebtnGp->setObjectName(QStringLiteral("SpanModebtnGp"));
        SpanModebtnGp->addButton(pb_LastSpan);
        pb_LastSpan->setObjectName(QStringLiteral("pb_LastSpan"));
        pb_LastSpan->setGeometry(QRect(163, 367, 70, 50));
        pb_LastSpan->setFocusPolicy(Qt::NoFocus);
        pb_LastSpan->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(255,255,255,1);\n"
"	padding:0px;\n"
"	text-align:center;\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	\n"
"	background-image: url(:/sa/image/btn_w70_normal.png);\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/sa/image/btn_w70_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_FreqSetup[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(0,0,0,1);\n"
"	padding:0px;\n"
"	text-align:center;\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"outdoor\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/s"
                        "a/image/outdoor/btn_w70_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_FreqSetup[status  =  \"night\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color: #FBDBA7;\n"
"	padding:0px;\n"
"	text-align:center;\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"night\"] QPushButton\n"
"{\n"
"	background-image: url(:/sa/image/night/btn_w70_normal.png);\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"night\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/sa/image/night/btn_w70_click.png);\n"
"}"));
        pb_LastSpan->setCheckable(true);
        lblStartFreq = new QLabel(widget);
        lblStartFreq->setObjectName(QStringLiteral("lblStartFreq"));
        lblStartFreq->setGeometry(QRect(18, 117, 68, 30));
        lblCenterFreq = new QLabel(widget);
        lblCenterFreq->setObjectName(QStringLiteral("lblCenterFreq"));
        lblCenterFreq->setGeometry(QRect(18, 67, 68, 30));
        lblChNumber = new QLabel(widget);
        lblChNumber->setObjectName(QStringLiteral("lblChNumber"));
        lblChNumber->setGeometry(QRect(18, 487, 55, 30));
        LedCHStandard = new SA_LineEdit(widget);
        LedCHStandard->setObjectName(QStringLiteral("LedCHStandard"));
        LedCHStandard->setGeometry(QRect(94, 437, 140, 30));
        LedCHStandard->setReadOnly(true);
        LedStopFreq = new SA_LineEdit(widget);
        LedStopFreq->setObjectName(QStringLiteral("LedStopFreq"));
        LedStopFreq->setGeometry(QRect(94, 167, 140, 30));
        LedStopFreq->setReadOnly(true);
        lblFreqStep = new QLabel(widget);
        lblFreqStep->setObjectName(QStringLiteral("lblFreqStep"));
        lblFreqStep->setGeometry(QRect(18, 217, 68, 30));
        LedCenterFreq = new SA_LineEdit(widget);
        LedCenterFreq->setObjectName(QStringLiteral("LedCenterFreq"));
        LedCenterFreq->setGeometry(QRect(94, 67, 140, 30));
        LedCenterFreq->setCursor(QCursor(Qt::BlankCursor));
        LedCenterFreq->setStyleSheet(QStringLiteral(""));
        LedCenterFreq->setMaxLength(13124124);
        LedCenterFreq->setReadOnly(true);
        lblChStep = new QLabel(widget);
        lblChStep->setObjectName(QStringLiteral("lblChStep"));
        lblChStep->setGeometry(QRect(18, 537, 55, 30));
        lblSpan = new QLabel(widget);
        lblSpan->setObjectName(QStringLiteral("lblSpan"));
        lblSpan->setGeometry(QRect(18, 325, 37, 15));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(9);
        lblSpan->setFont(font1);
        LedStartFreq = new SA_LineEdit(widget);
        LedStartFreq->setObjectName(QStringLiteral("LedStartFreq"));
        LedStartFreq->setGeometry(QRect(94, 117, 140, 30));
        LedStartFreq->setReadOnly(true);
        LedCHNum = new SA_LineEdit(widget);
        LedCHNum->setObjectName(QStringLiteral("LedCHNum"));
        LedCHNum->setGeometry(QRect(94, 487, 140, 30));
        LedCHNum->setReadOnly(true);
        LedSpan = new SA_LineEdit(widget);
        LedSpan->setObjectName(QStringLiteral("LedSpan"));
        LedSpan->setGeometry(QRect(94, 317, 140, 30));
        LedSpan->setReadOnly(true);
        lblFreqOffset = new QLabel(widget);
        lblFreqOffset->setObjectName(QStringLiteral("lblFreqOffset"));
        lblFreqOffset->setGeometry(QRect(18, 267, 68, 30));
        LedFreqOffset = new SA_LineEdit(widget);
        LedFreqOffset->setObjectName(QStringLiteral("LedFreqOffset"));
        LedFreqOffset->setGeometry(QRect(94, 267, 140, 30));
        LedFreqOffset->setStyleSheet(QStringLiteral(""));
        LedFreqOffset->setReadOnly(true);
        pb_FullSpan = new QPushButton(widget);
        SpanModebtnGp->addButton(pb_FullSpan);
        pb_FullSpan->setObjectName(QStringLiteral("pb_FullSpan"));
        pb_FullSpan->setGeometry(QRect(17, 367, 70, 50));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setBold(true);
        font2.setItalic(false);
        font2.setWeight(75);
        pb_FullSpan->setFont(font2);
        pb_FullSpan->setFocusPolicy(Qt::NoFocus);
        pb_FullSpan->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(255,255,255,1);\n"
"	padding:0px;\n"
"	text-align:center;\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	\n"
"	background-image: url(:/sa/image/btn_w70_normal.png);\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/sa/image/btn_w70_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_FreqSetup[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(0,0,0,1);\n"
"	padding:0px;\n"
"	text-align:center;\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	border-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"outdoor\"] QPushButton:pressed\n"
"{	\n"
"	border-image: url(:/sa/image/"
                        "outdoor/btn_w70_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_FreqSetup[status  =  \"night\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color: #FBDBA7;\n"
"	padding:0px;\n"
"	text-align:center;\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"night\"] QPushButton\n"
"{\n"
"	background-image: url(:/sa/image/night/btn_w70_normal.png);\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"night\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/sa/image/night/btn_w70_click.png);\n"
"}"));
        pb_FullSpan->setCheckable(true);
        LedCHStep = new SA_LineEdit(widget);
        LedCHStep->setObjectName(QStringLiteral("LedCHStep"));
        LedCHStep->setEnabled(true);
        LedCHStep->setGeometry(QRect(94, 537, 140, 30));
        LedCHStep->setFocusPolicy(Qt::NoFocus);
        LedCHStep->setStyleSheet(QStringLiteral(""));
        LedCHStep->setReadOnly(true);
        lblChStandard = new QLabel(widget);
        lblChStandard->setObjectName(QStringLiteral("lblChStandard"));
        lblChStandard->setGeometry(QRect(18, 437, 59, 30));
        pb_ZeroSpan = new QPushButton(widget);
        SpanModebtnGp->addButton(pb_ZeroSpan);
        pb_ZeroSpan->setObjectName(QStringLiteral("pb_ZeroSpan"));
        pb_ZeroSpan->setGeometry(QRect(90, 367, 70, 50));
        pb_ZeroSpan->setFocusPolicy(Qt::NoFocus);
        pb_ZeroSpan->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(255,255,255,1);\n"
"	padding:0px;\n"
"	text-align:center;\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	\n"
"	background-image: url(:/sa/image/btn_w70_normal.png);\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"indoor\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/sa/image/btn_w70_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_FreqSetup[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(0,0,0,1);\n"
"	padding:0px;\n"
"	text-align:center;\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"outdoor\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/s"
                        "a/image/outdoor/btn_w70_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_FreqSetup[status  =  \"night\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color: #FBDBA7;\n"
"	padding:0px;\n"
"	text-align:center;\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"night\"] QPushButton\n"
"{\n"
"	background-image: url(:/sa/image/night/btn_w70_normal.png);\n"
"}\n"
"#SA_Dialog_FreqSetup[status  =  \"night\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/sa/image/night/btn_w70_click.png);\n"
"}"));
        pb_ZeroSpan->setCheckable(true);
        lblStopFreq = new QLabel(widget);
        lblStopFreq->setObjectName(QStringLiteral("lblStopFreq"));
        lblStopFreq->setGeometry(QRect(18, 167, 68, 30));
        LedFreqStep = new SA_LineEdit(widget);
        LedFreqStep->setObjectName(QStringLiteral("LedFreqStep"));
        LedFreqStep->setGeometry(QRect(94, 217, 140, 30));
        LedFreqStep->setReadOnly(true);
        lblChType = new QLabel(widget);
        lblChType->setObjectName(QStringLiteral("lblChType"));
        lblChType->setGeometry(QRect(18, 587, 55, 30));
        lblChType->setFont(font1);
        pb_Uplink = new QPushButton(widget);
        ChannelType = new QButtonGroup(SA_Dialog_FreqSetup);
        ChannelType->setObjectName(QStringLiteral("ChannelType"));
        ChannelType->addButton(pb_Uplink);
        pb_Uplink->setObjectName(QStringLiteral("pb_Uplink"));
        pb_Uplink->setGeometry(QRect(94, 587, 69, 30));
        pb_Uplink->setFont(font2);
        pb_Uplink->setFocusPolicy(Qt::NoFocus);
        pb_Uplink->setStyleSheet(QStringLiteral(""));
        pb_Uplink->setCheckable(true);
        pb_Uplink->setChecked(true);
        pb_Downlink = new QPushButton(widget);
        ChannelType->addButton(pb_Downlink);
        pb_Downlink->setObjectName(QStringLiteral("pb_Downlink"));
        pb_Downlink->setGeometry(QRect(165, 587, 69, 30));
        pb_Downlink->setFocusPolicy(Qt::NoFocus);
        pb_Downlink->setStyleSheet(QStringLiteral(""));
        pb_Downlink->setCheckable(true);
        lblTitle = new QLabel(widget);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));
        lblTitle->setGeometry(QRect(17, 19, 108, 22));
        lblTitle->setFont(font2);
        lblTitle->setStyleSheet(QLatin1String("#lblTitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}"));
        pb_cancel = new QPushButton(widget);
        pb_cancel->setObjectName(QStringLiteral("pb_cancel"));
        pb_cancel->setGeometry(QRect(212, 6, 35, 35));
        pb_cancel->setFocusPolicy(Qt::NoFocus);
        pb_cancel->setStyleSheet(QStringLiteral(""));
        line = new QFrame(widget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(18, 46, 212, 2));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        QWidget::setTabOrder(LedCenterFreq, LedStartFreq);
        QWidget::setTabOrder(LedStartFreq, LedStopFreq);
        QWidget::setTabOrder(LedStopFreq, LedFreqStep);
        QWidget::setTabOrder(LedFreqStep, LedFreqOffset);
        QWidget::setTabOrder(LedFreqOffset, LedSpan);
        QWidget::setTabOrder(LedSpan, LedCHStandard);
        QWidget::setTabOrder(LedCHStandard, LedCHNum);
        QWidget::setTabOrder(LedCHNum, LedCHStep);

        retranslateUi(SA_Dialog_FreqSetup);

        QMetaObject::connectSlotsByName(SA_Dialog_FreqSetup);
    } // setupUi

    void retranslateUi(QWidget *SA_Dialog_FreqSetup)
    {
        SA_Dialog_FreqSetup->setWindowTitle(QApplication::translate("SA_Dialog_FreqSetup", "Form", 0));
        SA_Dialog_FreqSetup->setProperty("status", QVariant(QApplication::translate("SA_Dialog_FreqSetup", "night", 0)));
        pb_LastSpan->setText(QApplication::translate("SA_Dialog_FreqSetup", "Last\n"
"Span", 0));
        lblStartFreq->setText(QApplication::translate("SA_Dialog_FreqSetup", "Start\n"
"Frequency", 0));
        lblCenterFreq->setText(QApplication::translate("SA_Dialog_FreqSetup", "Center\n"
"Frequency", 0));
        lblChNumber->setText(QApplication::translate("SA_Dialog_FreqSetup", "Channel\n"
"Number", 0));
        LedCHStandard->setText(QApplication::translate("SA_Dialog_FreqSetup", "CDMA-Band 0(800)", 0));
        LedStopFreq->setText(QApplication::translate("SA_Dialog_FreqSetup", "1,000.000 MHz", 0));
        lblFreqStep->setText(QApplication::translate("SA_Dialog_FreqSetup", "Frequency\n"
"Step", 0));
        LedCenterFreq->setText(QApplication::translate("SA_Dialog_FreqSetup", "1,000.000 MHz", 0));
        LedCenterFreq->setProperty("status", QVariant(QApplication::translate("SA_Dialog_FreqSetup", "outdoor", 0)));
        lblChStep->setText(QApplication::translate("SA_Dialog_FreqSetup", "Channel\n"
"Step", 0));
        lblSpan->setText(QApplication::translate("SA_Dialog_FreqSetup", "Span", 0));
        LedStartFreq->setText(QApplication::translate("SA_Dialog_FreqSetup", "1,000.000 MHz", 0));
        LedCHNum->setText(QApplication::translate("SA_Dialog_FreqSetup", "1", 0));
        LedSpan->setText(QApplication::translate("SA_Dialog_FreqSetup", "1,000.000 MHz", 0));
        lblFreqOffset->setText(QApplication::translate("SA_Dialog_FreqSetup", "Frequency\n"
"Offset", 0));
        LedFreqOffset->setText(QApplication::translate("SA_Dialog_FreqSetup", "0.000 MHz", 0));
        pb_FullSpan->setText(QApplication::translate("SA_Dialog_FreqSetup", "Full\n"
"Span", 0));
        LedCHStep->setText(QApplication::translate("SA_Dialog_FreqSetup", "1", 0));
        lblChStandard->setText(QApplication::translate("SA_Dialog_FreqSetup", "Channel\n"
"Standard", 0));
        pb_ZeroSpan->setText(QApplication::translate("SA_Dialog_FreqSetup", "Zero\n"
"Span", 0));
        lblStopFreq->setText(QApplication::translate("SA_Dialog_FreqSetup", "Stop\n"
"Frequency", 0));
        LedFreqStep->setText(QApplication::translate("SA_Dialog_FreqSetup", "1.000 MHz", 0));
        lblChType->setText(QApplication::translate("SA_Dialog_FreqSetup", "Channel\n"
"Type", 0));
        pb_Uplink->setText(QApplication::translate("SA_Dialog_FreqSetup", "Uplink", 0));
        pb_Downlink->setText(QApplication::translate("SA_Dialog_FreqSetup", "Downlink", 0));
        lblTitle->setText(QApplication::translate("SA_Dialog_FreqSetup", "Frequency", 0));
        pb_cancel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SA_Dialog_FreqSetup: public Ui_SA_Dialog_FreqSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_FREQSETUP_H
