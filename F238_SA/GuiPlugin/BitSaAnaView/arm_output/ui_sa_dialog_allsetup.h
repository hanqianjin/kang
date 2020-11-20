/********************************************************************************
** Form generated from reading UI file 'sa_dialog_allsetup.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_ALLSETUP_H
#define UI_SA_DIALOG_ALLSETUP_H

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
#include "sa_clickedwidget.h"
#include "sa_combobox.h"

QT_BEGIN_NAMESPACE

class Ui_SA_Dialog_AllSetup
{
public:
    QWidget *widget_title;
    QLabel *lblTitle;
    QPushButton *pb_cancel;
    QStackedWidget *stackedWidget;
    QWidget *page_3;
    QWidget *page;
    QWidget *widget;
    SA_ClickedWidget *VBW_RBW;
    QLabel *Title_VBW_RBW;
    SA_Combobox *value_VBW_RBW;
    SA_ClickedWidget *Freq_Offset;
    QLabel *Title_FreqOffset;
    QLabel *value_FreqOffset;
    SA_ClickedWidget *Detectors;
    QLabel *Title_Detectors;
    SA_Combobox *value_Detectors;
    SA_ClickedWidget *Auto_Scale;
    QLabel *Title_AutoScale;
    QPushButton *pb_AutoScale;
    QLabel *Title_Ampt;
    QLabel *Title_Freq;
    SA_ClickedWidget *Freq_Center;
    QLabel *Title_CenterFreq;
    QLabel *value_CenterFreq;
    SA_ClickedWidget *Span_Last;
    QLabel *label_36;
    QPushButton *pb_LastSpan;
    SA_ClickedWidget *Atten;
    QLabel *Title_Atten;
    QPushButton *Atten_Auto;
    QPushButton *Atten_Manual;
    SA_ClickedWidget *VBW_Btn;
    QLabel *Title_VBW_Btn;
    QPushButton *VBW_Auto;
    QPushButton *VBW_Manual;
    SA_ClickedWidget *Channel_Step;
    QLabel *Title_ChannelStep;
    QLabel *value_ChannelStep;
    SA_ClickedWidget *RBW_Btn;
    QLabel *Title_RBW_Btn;
    QPushButton *RBW_Auto;
    QPushButton *RBW_Manual;
    SA_ClickedWidget *Span_Full;
    QLabel *label_30;
    QPushButton *pb_FullSpan;
    QLabel *Title_Sweep;
    SA_ClickedWidget *Sweep_Time;
    QLabel *Title_Time;
    QLabel *value_SweepTime;
    SA_ClickedWidget *Ref_Level;
    QLabel *Title_Ref_Level;
    QLabel *value_Ref_Level;
    SA_ClickedWidget *Channel_STD;
    QLabel *Title_Channel;
    QLabel *value_Channel;
    QLabel *Title_Trace;
    SA_ClickedWidget *Average;
    QLabel *Title_Average;
    QLabel *value_Average;
    SA_ClickedWidget *RBW_Freq;
    QLabel *Title_RBW;
    SA_Combobox *value_RBW;
    SA_ClickedWidget *Trace_View;
    QLabel *Title_TraceView;
    QPushButton *btn_TraceView;
    SA_ClickedWidget *Freq_Step;
    QLabel *Title_FreqStep;
    QLabel *value_FreqStep;
    SA_ClickedWidget *Freq_Stop;
    QLabel *Title_StopFreq;
    QLabel *value_StopFreq;
    SA_ClickedWidget *Scale_Division;
    QLabel *Title_Scale;
    QLabel *value_Scale;
    QLabel *Title_Trigger;
    SA_ClickedWidget *Trace_Select;
    QLabel *Title_TraceSelect;
    SA_Combobox *value_Trace;
    SA_ClickedWidget *Channel_Num;
    QLabel *Title_ChannelNum;
    QLabel *value_ChannelNum;
    QLabel *Title_Bw;
    SA_ClickedWidget *Span_Zero;
    QLabel *label_32;
    QPushButton *pb_ZeroSpan;
    SA_ClickedWidget *Span;
    QLabel *Title_Span;
    QLabel *value_Span;
    SA_ClickedWidget *VBW_Freq;
    QLabel *title_VBW;
    SA_Combobox *value_VBW;
    SA_ClickedWidget *Ref_Offset;
    QLabel *Title_RefOffset;
    QLabel *value_RefOffset;
    SA_ClickedWidget *Preamp;
    QLabel *Title_Preamp;
    QPushButton *btn_Preamp;
    SA_ClickedWidget *Trace_Type;
    QLabel *Title_TraceType;
    SA_Combobox *value_TraceType;
    SA_ClickedWidget *Sweep_Mode;
    QLabel *Title_SweepType;
    QPushButton *Sweep_Conti;
    QPushButton *Sweep_Single;
    SA_ClickedWidget *Auto_SweepTime;
    QLabel *Title_AutoSweepTime;
    QPushButton *SweepTime_Manual;
    QPushButton *SweepTime_Auto;
    SA_ClickedWidget *Freq_Start;
    QLabel *Title_StartFreq;
    QLabel *value_StartFreq;
    SA_ClickedWidget *Scale_Unit;
    QLabel *Title_Unit;
    SA_Combobox *value_Unit;
    SA_ClickedWidget *Channel_Type;
    QLabel *Title_ChannelType;
    QPushButton *Channel_Uplink;
    QPushButton *Channel_Downlink;
    SA_ClickedWidget *Atten_Value;
    QLabel *Title_AttenValue;
    QLabel *value_AttenValue;
    SA_ClickedWidget *Average_Toggle;
    QLabel *Title_AverageToggle;
    QPushButton *btn_Average;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QFrame *line_5;
    QFrame *line_6;
    QPushButton *pb_prePage;
    QPushButton *pb_nextPage;
    SA_ClickedWidget *Sweep_Once;
    QLabel *Title_SweepOnce;
    QPushButton *pb_SweepOnce;
    SA_ClickedWidget *Trace_AllOn;
    QLabel *Title_TraceAllOn;
    QPushButton *pb_TraceAllOn;
    SA_ClickedWidget *Trace_AllClear;
    QLabel *Title_Trace_ClearAll;
    QPushButton *pb_TraceAllClear;
    SA_ClickedWidget *Trigger_Source;
    QLabel *Title_TriggerSource;
    SA_Combobox *value_TriggerSource;
    QStackedWidget *Trigger_SubMenu;
    QWidget *FreeRun;
    QWidget *External;
    SA_ClickedWidget *External_DelayTime;
    QLabel *Title_External_DelayTime;
    QLabel *value_External_DelayTime;
    SA_ClickedWidget *External_Slope;
    QLabel *Title_External_Slope;
    QPushButton *pb_External_Pos;
    QPushButton *pb_External_Neg;
    SA_ClickedWidget *External_Level;
    QLabel *Title_External_Level;
    QLabel *value_External_Level;
    SA_ClickedWidget *External_DelayOn;
    QLabel *Title_External_DelayOn;
    QPushButton *value_External_DelayOn;
    QWidget *Video;
    SA_ClickedWidget *Video_Slope;
    QLabel *Title_Video_Slope;
    QPushButton *pb_Video_Pos;
    QPushButton *pb_Video_Neg;
    SA_ClickedWidget *Video_DelayOn;
    QLabel *Title_Video_DelayOn;
    QPushButton *value_Video_DelayOn;
    SA_ClickedWidget *Video_DelayTime;
    QLabel *Title_Video_DelayTime;
    QLabel *value_Video_DelayTime;
    SA_ClickedWidget *Video_Level;
    QLabel *Title_Video_Level;
    QLabel *value_Video_Level;
    QWidget *PerTimer;
    SA_ClickedWidget *Peri_Timer;
    QLabel *Title_Peri_Timer;
    QLabel *value_Peri_Timer;
    SA_ClickedWidget *Peri_DelayOn;
    QLabel *Title_Peri_DelayOn;
    QPushButton *value_Peri_DelayOn;
    SA_ClickedWidget *Peri_DelayTime;
    QLabel *Title_Peri_DelayTime;
    QLabel *value_Peri_DelayTime;
    QWidget *RFBurst;
    SA_ClickedWidget *RFBurst_DelayTime;
    QLabel *Title_RFBurst_DelayTime;
    QLabel *value_RFBurst_DelayTime;
    SA_ClickedWidget *RFBurst_Slope;
    QLabel *Title_RFBurst_Slope;
    QPushButton *pb_RFBurst_Pos;
    QPushButton *pb_RFBurst_Neg;
    SA_ClickedWidget *RFBurst_Level;
    QLabel *Title_RFBurst_Level;
    QLabel *value_RFBurst_Level;
    SA_ClickedWidget *RFBurst_DelayOn;
    QLabel *Title_RFBurst_DelayOn;
    QPushButton *value_RFBurst_DelayOn;
    QWidget *GPS;
    QWidget *page_2;
    QWidget *widget_2;
    SA_ClickedWidget *Limit_Test;
    QLabel *Title_Limit_Test;
    QPushButton *Value_Limit_Test;
    QPushButton *pb_nextPage_2;
    SA_ClickedWidget *Noise_Marker;
    QLabel *Title_NoiseMarker;
    QPushButton *btn_NoiseMarker;
    SA_ClickedWidget *Limit_Edge_Toggle;
    QLabel *Title_MarkerTable_2;
    QPushButton *value_Limit_Edge_Toggle;
    SA_ClickedWidget *Limit_Type;
    QLabel *Title_ChannelType_2;
    QPushButton *btn_Upper;
    QPushButton *btn_Lower;
    SA_ClickedWidget *Limit_Edge;
    QLabel *Title_Limit_Edge;
    QLabel *Value_Limit_Edge;
    QPushButton *pb_prePage_2;
    SA_ClickedWidget *Limit_Toggle;
    QLabel *Title_Limit_Toggle;
    QPushButton *Value_Limit_Toggle;
    QLabel *Title_Marker;
    SA_ClickedWidget *Limit_Select;
    QLabel *Title_LimitSelect;
    SA_Combobox *value_LimitSelect;
    SA_ClickedWidget *Freq_Count;
    QLabel *Title_FreqCount;
    QPushButton *btn_FreqCount;
    SA_ClickedWidget *Marker_Type;
    QLabel *Title_MarkerType;
    QPushButton *Marker_Normal;
    QPushButton *Marker_Delta;
    QLabel *Title_Limit;
    SA_ClickedWidget *Marker_View;
    QLabel *Title_MarkerView;
    QPushButton *btn_MarkerView;
    SA_ClickedWidget *Marker_Select;
    QLabel *Title_MarkerSelect;
    SA_Combobox *value_MarkerSelect;
    QFrame *line_7;
    QFrame *line_8;
    SA_ClickedWidget *Marker_AllOn;
    QLabel *Title_MarkerView_AllOn;
    QPushButton *pb_MkrAllOn;
    SA_ClickedWidget *Marker_To;
    QLabel *Title_MarkerTo;
    SA_Combobox *value_MarkerTo;
    SA_ClickedWidget *Limit_AllClear;
    QLabel *Title_Limit_AllClear;
    QPushButton *pb_LimitAllDelete;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *SA_Dialog_AllSetup)
    {
        if (SA_Dialog_AllSetup->objectName().isEmpty())
            SA_Dialog_AllSetup->setObjectName(QStringLiteral("SA_Dialog_AllSetup"));
        SA_Dialog_AllSetup->resize(1278, 763);
        SA_Dialog_AllSetup->setFocusPolicy(Qt::NoFocus);
        SA_Dialog_AllSetup->setStyleSheet(QLatin1String("#SA_Dialog_AllSetup\n"
"{\n"
"	background-color: rgba(255, 255, 255,1);\n"
"	border-style:solid;\n"
"}\n"
"\n"
"\n"
"\n"
"#widget>SA_ClickedWidget>QLabel,\n"
"#widget_2>SA_ClickedWidget>QLabel\n"
"{\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] #widget, \n"
"#SA_Dialog_AllSetup[status=\"indoor\"] #widget_2\n"
"{\n"
"	background-color:white;\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] #widget SA_ClickedWidget,\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] #widget_2 SA_ClickedWidget\n"
"{\n"
"	background-color:rgb(238,238,238);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"/*SA_ClickedWidget*/\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] #widget>QWidget QLabel,\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] #widget_2>QWidget QLabel\n"
"{	\n"
"	font:75 13px \"Arial\";\n"
"	color: rgba(57, 57, 57, 1);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"ind"
                        "oor\"] QFrame[style = \"1\"]\n"
"{\n"
"	background-color:rgba(6, 62, 97, 1);\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] #widget>QLabel,\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] #widget_2>QLabel\n"
"{\n"
"	font:75 17px \"Arial\";\n"
"   font-weight:bold;\n"
"	color:rgb(6, 62, 97);\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QComboBox\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color: rgba(31, 118, 170, 1);\n"
"	padding:35px 23px 4px 5px;\n"
"	combobox-popup: 0;\n"
"	border-style:flat;\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QComboBox::drop-down {\n"
"	width: 0px;	\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QComboBox QAbstractItemView{\n"
"	width:180px;\n"
"   font: 75 14px \"Arial\";\n"
"	color:rgba(0, 0, 0, 1);\n"
"	background:rgba(255,255,255,1);\n"
" 	outline:0px;\n"
"	border-style:solid;\n"
"	border-color:rgba(151, 151, 151, 1);\n"
"	border-width:1px;\n"
"}\n"
"#SA_Dialog_AllSe"
                        "tup[status=\"indoor\"] QAbstractItemView::item{\n"
"	padding-left:7px;\n"
"	height:32px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(240, 179, 29, 1); \n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton[style=\"left\"]\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	color:rgba(101, 101, 101, 1);\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/btn_opt_2_w125.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton[style=\"left\"]:checked\n"
"{\n"
"	color:rgba(57, 57, 57, 1);\n"
"	background-image: url(:/sa/image/btn_opt_1_w125.png);\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton[style=\"right\"]\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	color:rgba(101, 101, 101, 1);\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/btn_opt_1_w125.png);\n"
"	background-position:right;\n"
"}\n"
"#SA_Dialog_AllSetup[status=\""
                        "indoor\"] QPushButton[style=\"right\"]:checked\n"
"{\n"
"	color:rgba(57, 57, 57, 1);\n"
"	background-image: url(:/sa/image/btn_opt_2_w125.png);\n"
"	background-position:right;\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] #widget,\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] #widget_2 \n"
"{\n"
"	background-color:rgba(255,255,255,1);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] #widget SA_ClickedWidget,\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] #widget_2 SA_ClickedWidget\n"
"{\n"
"	background-color:rgb(238,238,238);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"/*SA_ClickedWidget*/\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] #widget>QWidget QLabel,\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] #widget_2>QWidget QLabel\n"
"{	\n"
"	font:75 13px \"Arial\";\n"
"	color: rgba(57, 57, 57, 1);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QFrame[style = \"1\"]\n"
"{\n"
""
                        "	background-color:rgba(6, 62, 97, 1);\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] #widget>QLabel,\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] #widget_2>QLabel\n"
"{\n"
"	font:75 17px \"Arial\";\n"
"   font-weight:bold;\n"
"	color:rgb(6, 62, 97);\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QComboBox\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color: rgba(31, 118, 170, 1);\n"
"	padding:35px 23px 4px 5px;\n"
"	combobox-popup: 0;\n"
"	border-style:flat;\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QComboBox::drop-down {\n"
"	width: 0px;	\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QComboBox QAbstractItemView{\n"
"	width:180px;\n"
"   font: 75 14px \"Arial\";\n"
"	color:rgba(0, 0, 0, 1);\n"
"	background:rgba(255,255,255,1);\n"
" 	outline:0px;\n"
"	border-style:solid;\n"
"	border-color:rgba(151, 151, 151, 1);\n"
"	border-width:1px;\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QAbstractI"
                        "temView::item{\n"
"	padding-left:7px;\n"
"	height:32px;\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(240, 179, 29, 1); \n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton[style=\"left\"]\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	color:rgba(101, 101, 101, 1);\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/btn_opt_2_w125.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton[style=\"left\"]:checked\n"
"{\n"
"	color:rgba(57, 57, 57, 1);\n"
"	background-image: url(:/sa/image/btn_opt_1_w125.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton[style=\"right\"]\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	color:rgba(101, 101, 101, 1);\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/btn_opt_1_w125.png);\n"
"	background-position:right;\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton[style=\"right\""
                        "]:checked\n"
"{\n"
"	color:rgba(57, 57, 57, 1);\n"
"	background-image: url(:/sa/image/btn_opt_2_w125.png);\n"
"	background-position:right;\n"
"}\n"
"/*******************night**********************/\n"
"#SA_Dialog_AllSetup[status=\"night\"] #widget,\n"
"#SA_Dialog_AllSetup[status=\"night\"] #widget_2\n"
"{\n"
"	background-color:rgba(0,0,0,1);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] #widget SA_ClickedWidget,\n"
"#SA_Dialog_AllSetup[status=\"night\"] #widget_2 SA_ClickedWidget\n"
"{\n"
"	background-color: rgba(24,23,20,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"/*SA_ClickedWidget*/\n"
"#SA_Dialog_AllSetup[status=\"night\"] #widget>QWidget .QLabel,\n"
"#SA_Dialog_AllSetup[status=\"night\"] #widget_2>QWidget .QLabel\n"
"{	\n"
"	font:75 13px \"Arial\";\n"
"	color: rgba(250,218,166,1);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] QFrame[style = \"1\"]\n"
"{\n"
"	height:3px;\n"
"	background-color:rgba(7,97,116,1);\n"
"}\n"
""
                        "#SA_Dialog_AllSetup[status=\"night\"] #widget>QLabel,\n"
"#SA_Dialog_AllSetup[status=\"night\"] #widget_2>QLabel\n"
"{\n"
"	font:75 17px \"Arial\";\n"
"   font-weight:bold;\n"
"	color:rgba(7,97,116,1);\n"
"}\n"
"\n"
"\n"
"#SA_Dialog_AllSetup[status=\"night\"] QComboBox\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color: rgba(30,101,111,1);\n"
"	padding:35px 23px 4px 5px;\n"
"	combobox-popup: 0;\n"
"	border-style:flat;\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"\n"
"#SA_Dialog_AllSetup[status=\"night\"] QComboBox::drop-down {\n"
"	width: 0px;	\n"
"	border-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"night\"] QComboBox QAbstractItemView{\n"
"	width:180px;\n"
"   font: 75 14px \"Arial\";\n"
"	color:rgba(0, 0, 0, 1);\n"
"	background-color:#FBDBA7;;\n"
" 	outline:0px;\n"
"	border-style:solid;\n"
"	border-color:rgba(151, 151, 151, 1);\n"
"	border-width:1px;\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] QAbstractItemView::item{\n"
"	padding-left:7px;\n"
"	height:32px;\n"
"	borde"
                        "r-style:flat;\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"night\"] QComboBox QAbstractItemView::item:selected\n"
"{\n"
" 	color:rgba(159,98,0,1);\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton[style=\"left\"]\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	color:rgba(121, 106, 81, 1);\n"
"	border-style:flat;\n"
"	border-image: url(:/sa/image/night/btn_left_nor.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton[style=\"left\"]:checked\n"
"{\n"
"	color:rgba(85, 74, 56, 1);\n"
"	border-image: url(:/sa/image/night/btn_left_click.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton[style=\"right\"]\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	color:rgba(121, 106, 81, 1);\n"
"	border-style:flat;\n"
"	border-image: url(:/sa/image/night/btn_right_nor.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton[style=\"right\"]:checked\n"
"{\n"
"	color:rgba(85, 74, 56, 1);\n"
"	border-image: url(:/sa/image/night/btn_right_click.png)"
                        ";\n"
"}"));
        widget_title = new QWidget(SA_Dialog_AllSetup);
        widget_title->setObjectName(QStringLiteral("widget_title"));
        widget_title->setGeometry(QRect(0, 0, 1278, 46));
        widget_title->setStyleSheet(QLatin1String("\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] #widget_title\n"
"{\n"
"	background-color:rgba(201,201,201,1);\n"
"   border:1px;\n"
"   border-bottom-style:solid;\n"
"	border-bottom-color:rgba(76,76,76,1);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] #widget_title>#pb_cancel\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/outdoor/btn_close_45_nor.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] #widget_title>#pb_cancel:pressed\n"
"{\n"
"	background-image: url(:/sa/image/outdoor/btn_close_45_click.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] #widget_title>#lblTitle\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	font:75 20px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] #widget_title\n"
"{\n"
"	background-color:rgba(201,201,201,1);\n"
"   border:1px;\n"
"   border-bottom-style:solid;\n"
"	border-bottom-color:rgba(76,76,76,1);\n"
"}\n"
"#SA_Dial"
                        "og_AllSetup[status=\"outdoor\"] #widget_title>#pb_cancel\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/outdoor/btn_close_45_nor.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] #widget_title>#pb_cancel:pressed\n"
"{\n"
"	background-image: url(:/sa/image/outdoor/btn_close_45_click.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] #widget_title>#lblTitle\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	font:75 20px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_AllSetup[status=\"night\"] #widget_title\n"
"{\n"
"	background-color:rgba(53,46,35,1);\n"
"   border:1px;\n"
"   border-bottom-style:solid;\n"
"	border-bottom-color:rgba(76,76,76,1);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] #widget_title>#pb_cancel\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/night/btn_close_45_normal.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] #widget_title>#pb_cancel:pressed\n"
"{\n"
"	background-image: url(:/sa/"
                        "image/night/btn_close_45_click.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] #widget_title>#lblTitle\n"
"{\n"
"	color:rgba(250,218,166,1);\n"
"	font:75 20px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
""));
        lblTitle = new QLabel(widget_title);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));
        lblTitle->setGeometry(QRect(29, 12, 228, 22));
        pb_cancel = new QPushButton(widget_title);
        pb_cancel->setObjectName(QStringLiteral("pb_cancel"));
        pb_cancel->setGeometry(QRect(1220, 0, 45, 45));
        stackedWidget = new QStackedWidget(SA_Dialog_AllSetup);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 46, 1278, 721));
        stackedWidget->setStyleSheet(QLatin1String("QLabel[style = \"1\"]\n"
"{\n"
"	font:75 13px \"Arial\";\n"
"   font-weight:bold;\n"
"	color: rgba(31, 118, 170, 1);\n"
"	background-color:rgba(0,0,0,0);\n"
"}\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QLabel[style = \"1\"]\n"
"{\n"
"	font:75 13px \"Arial\";\n"
"   font-weight:bold;\n"
"	color: rgba(31, 118, 170, 1);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QLabel[style = \"1\"]\n"
"{\n"
"	font:75 13px \"Arial\";\n"
"   font-weight:bold;\n"
"	color: rgba(31, 118, 170, 1);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_AllSetup[status=\"night\"] QLabel[style = \"1\"]\n"
"{\n"
"	font:75 13px \"Arial\";\n"
"   font-weight:bold;\n"
"	color: rgba(30,101,111,1);\n"
"}"));
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        stackedWidget->addWidget(page_3);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        widget = new QWidget(page);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 1278, 721));
        widget->setStyleSheet(QStringLiteral(""));
        VBW_RBW = new SA_ClickedWidget(widget);
        VBW_RBW->setObjectName(QStringLiteral("VBW_RBW"));
        VBW_RBW->setGeometry(QRect(719, 326, 140, 55));
        VBW_RBW->setFocusPolicy(Qt::StrongFocus);
        VBW_RBW->setStyleSheet(QStringLiteral(""));
        Title_VBW_RBW = new QLabel(VBW_RBW);
        Title_VBW_RBW->setObjectName(QStringLiteral("Title_VBW_RBW"));
        Title_VBW_RBW->setGeometry(QRect(5, 1, 121, 22));
        value_VBW_RBW = new SA_Combobox(VBW_RBW);
        value_VBW_RBW->setObjectName(QStringLiteral("value_VBW_RBW"));
        value_VBW_RBW->setEnabled(true);
        value_VBW_RBW->setGeometry(QRect(0, 0, 140, 55));
        value_VBW_RBW->setFocusPolicy(Qt::StrongFocus);
        value_VBW_RBW->setStyleSheet(QStringLiteral(""));
        value_VBW_RBW->setMaxVisibleItems(999);
        Freq_Offset = new SA_ClickedWidget(widget);
        Freq_Offset->setObjectName(QStringLiteral("Freq_Offset"));
        Freq_Offset->setGeometry(QRect(119, 326, 140, 55));
        Freq_Offset->setFocusPolicy(Qt::StrongFocus);
        Freq_Offset->setStyleSheet(QStringLiteral(""));
        Title_FreqOffset = new QLabel(Freq_Offset);
        Title_FreqOffset->setObjectName(QStringLiteral("Title_FreqOffset"));
        Title_FreqOffset->setGeometry(QRect(5, 1, 121, 22));
        value_FreqOffset = new QLabel(Freq_Offset);
        value_FreqOffset->setObjectName(QStringLiteral("value_FreqOffset"));
        value_FreqOffset->setGeometry(QRect(5, 28, 133, 22));
        value_FreqOffset->setStyleSheet(QStringLiteral(""));
        Detectors = new SA_ClickedWidget(widget);
        Detectors->setObjectName(QStringLiteral("Detectors"));
        Detectors->setGeometry(QRect(1019, 456, 140, 55));
        Detectors->setFocusPolicy(Qt::StrongFocus);
        Detectors->setStyleSheet(QStringLiteral(""));
        Title_Detectors = new QLabel(Detectors);
        Title_Detectors->setObjectName(QStringLiteral("Title_Detectors"));
        Title_Detectors->setGeometry(QRect(5, 1, 121, 22));
        value_Detectors = new SA_Combobox(Detectors);
        value_Detectors->setObjectName(QStringLiteral("value_Detectors"));
        value_Detectors->setEnabled(true);
        value_Detectors->setGeometry(QRect(0, 0, 140, 55));
        value_Detectors->setFocusPolicy(Qt::StrongFocus);
        value_Detectors->setStyleSheet(QStringLiteral(""));
        Auto_Scale = new SA_ClickedWidget(widget);
        Auto_Scale->setObjectName(QStringLiteral("Auto_Scale"));
        Auto_Scale->setGeometry(QRect(419, 66, 140, 55));
        Auto_Scale->setFocusPolicy(Qt::StrongFocus);
        Auto_Scale->setStyleSheet(QStringLiteral(""));
        Title_AutoScale = new QLabel(Auto_Scale);
        Title_AutoScale->setObjectName(QStringLiteral("Title_AutoScale"));
        Title_AutoScale->setGeometry(QRect(5, 1, 130, 22));
        pb_AutoScale = new QPushButton(Auto_Scale);
        pb_AutoScale->setObjectName(QStringLiteral("pb_AutoScale"));
        pb_AutoScale->setGeometry(QRect(123, 5, 12, 12));
        pb_AutoScale->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/inform_cir_r10_off.png);\n"
"}\n"
"QPushButton:checked\n"
"{\n"
"	background-image: url(:/sa/image/inform_cir_r10_on.png);\n"
"}"));
        pb_AutoScale->setCheckable(true);
        Title_Ampt = new QLabel(widget);
        Title_Ampt->setObjectName(QStringLiteral("Title_Ampt"));
        Title_Ampt->setGeometry(QRect(419, 30, 135, 19));
        Title_Ampt->setStyleSheet(QStringLiteral(""));
        Title_Freq = new QLabel(widget);
        Title_Freq->setObjectName(QStringLiteral("Title_Freq"));
        Title_Freq->setGeometry(QRect(119, 30, 281, 19));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        Title_Freq->setFont(font);
        Title_Freq->setStyleSheet(QStringLiteral(""));
        Title_Freq->setFrameShadow(QFrame::Plain);
        Title_Freq->setTextFormat(Qt::AutoText);
        Freq_Center = new SA_ClickedWidget(widget);
        Freq_Center->setObjectName(QStringLiteral("Freq_Center"));
        Freq_Center->setGeometry(QRect(119, 66, 140, 55));
        Freq_Center->setFocusPolicy(Qt::StrongFocus);
        Freq_Center->setStyleSheet(QStringLiteral(""));
        Title_CenterFreq = new QLabel(Freq_Center);
        Title_CenterFreq->setObjectName(QStringLiteral("Title_CenterFreq"));
        Title_CenterFreq->setGeometry(QRect(5, 1, 121, 22));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(9);
        Title_CenterFreq->setFont(font1);
        Title_CenterFreq->setStyleSheet(QStringLiteral(""));
        value_CenterFreq = new QLabel(Freq_Center);
        value_CenterFreq->setObjectName(QStringLiteral("value_CenterFreq"));
        value_CenterFreq->setGeometry(QRect(5, 28, 133, 22));
        value_CenterFreq->setFont(font);
        value_CenterFreq->setStyleSheet(QStringLiteral(""));
        Span_Last = new SA_ClickedWidget(widget);
        Span_Last->setObjectName(QStringLiteral("Span_Last"));
        Span_Last->setGeometry(QRect(119, 586, 140, 55));
        Span_Last->setFocusPolicy(Qt::StrongFocus);
        Span_Last->setStyleSheet(QStringLiteral(""));
        label_36 = new QLabel(Span_Last);
        label_36->setObjectName(QStringLiteral("label_36"));
        label_36->setGeometry(QRect(5, 1, 130, 22));
        pb_LastSpan = new QPushButton(Span_Last);
        pb_LastSpan->setObjectName(QStringLiteral("pb_LastSpan"));
        pb_LastSpan->setGeometry(QRect(123, 5, 12, 12));
        pb_LastSpan->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/inform_cir_r10_off.png);\n"
"}\n"
"QPushButton:checked\n"
"{\n"
"	background-image: url(:/sa/image/inform_cir_r10_on.png);\n"
"}"));
        pb_LastSpan->setCheckable(true);
        Atten = new SA_ClickedWidget(widget);
        Atten->setObjectName(QStringLiteral("Atten"));
        Atten->setGeometry(QRect(419, 261, 140, 55));
        Atten->setFocusPolicy(Qt::StrongFocus);
        Atten->setStyleSheet(QStringLiteral(""));
        Title_Atten = new QLabel(Atten);
        Title_Atten->setObjectName(QStringLiteral("Title_Atten"));
        Title_Atten->setGeometry(QRect(10, 2, 121, 21));
        Atten_Auto = new QPushButton(Atten);
        Atten_Auto->setObjectName(QStringLiteral("Atten_Auto"));
        Atten_Auto->setGeometry(QRect(10, 25, 61, 25));
        Atten_Auto->setFocusPolicy(Qt::NoFocus);
        Atten_Auto->setStyleSheet(QStringLiteral(""));
        Atten_Auto->setCheckable(true);
        Atten_Auto->setChecked(false);
        Atten_Auto->setAutoExclusive(true);
        Atten_Auto->setFlat(false);
        Atten_Manual = new QPushButton(Atten);
        Atten_Manual->setObjectName(QStringLiteral("Atten_Manual"));
        Atten_Manual->setGeometry(QRect(74, 25, 61, 25));
        Atten_Manual->setFocusPolicy(Qt::NoFocus);
        Atten_Manual->setStyleSheet(QStringLiteral(""));
        Atten_Manual->setCheckable(true);
        Atten_Manual->setChecked(true);
        Atten_Manual->setAutoExclusive(true);
        Atten_Manual->setFlat(false);
        VBW_Btn = new SA_ClickedWidget(widget);
        VBW_Btn->setObjectName(QStringLiteral("VBW_Btn"));
        VBW_Btn->setGeometry(QRect(719, 261, 140, 55));
        VBW_Btn->setFocusPolicy(Qt::StrongFocus);
        VBW_Btn->setStyleSheet(QStringLiteral(""));
        Title_VBW_Btn = new QLabel(VBW_Btn);
        Title_VBW_Btn->setObjectName(QStringLiteral("Title_VBW_Btn"));
        Title_VBW_Btn->setGeometry(QRect(5, 1, 121, 22));
        VBW_Auto = new QPushButton(VBW_Btn);
        VBW_Auto->setObjectName(QStringLiteral("VBW_Auto"));
        VBW_Auto->setGeometry(QRect(10, 25, 61, 25));
        VBW_Auto->setFocusPolicy(Qt::NoFocus);
        VBW_Auto->setStyleSheet(QStringLiteral(""));
        VBW_Auto->setCheckable(true);
        VBW_Auto->setAutoExclusive(true);
        VBW_Manual = new QPushButton(VBW_Btn);
        VBW_Manual->setObjectName(QStringLiteral("VBW_Manual"));
        VBW_Manual->setGeometry(QRect(74, 25, 61, 25));
        VBW_Manual->setFocusPolicy(Qt::NoFocus);
        VBW_Manual->setStyleSheet(QStringLiteral(""));
        VBW_Manual->setCheckable(true);
        VBW_Manual->setChecked(true);
        VBW_Manual->setAutoExclusive(true);
        Channel_Step = new SA_ClickedWidget(widget);
        Channel_Step->setObjectName(QStringLiteral("Channel_Step"));
        Channel_Step->setGeometry(QRect(269, 196, 140, 55));
        Channel_Step->setFocusPolicy(Qt::StrongFocus);
        Channel_Step->setStyleSheet(QStringLiteral(""));
        Title_ChannelStep = new QLabel(Channel_Step);
        Title_ChannelStep->setObjectName(QStringLiteral("Title_ChannelStep"));
        Title_ChannelStep->setGeometry(QRect(5, 1, 121, 22));
        value_ChannelStep = new QLabel(Channel_Step);
        value_ChannelStep->setObjectName(QStringLiteral("value_ChannelStep"));
        value_ChannelStep->setEnabled(true);
        value_ChannelStep->setGeometry(QRect(5, 28, 121, 22));
        value_ChannelStep->setStyleSheet(QStringLiteral(""));
        RBW_Btn = new SA_ClickedWidget(widget);
        RBW_Btn->setObjectName(QStringLiteral("RBW_Btn"));
        RBW_Btn->setGeometry(QRect(719, 131, 140, 55));
        RBW_Btn->setFocusPolicy(Qt::StrongFocus);
        RBW_Btn->setStyleSheet(QStringLiteral(""));
        Title_RBW_Btn = new QLabel(RBW_Btn);
        Title_RBW_Btn->setObjectName(QStringLiteral("Title_RBW_Btn"));
        Title_RBW_Btn->setGeometry(QRect(5, 1, 121, 22));
        RBW_Auto = new QPushButton(RBW_Btn);
        RBW_Auto->setObjectName(QStringLiteral("RBW_Auto"));
        RBW_Auto->setGeometry(QRect(10, 25, 61, 25));
        RBW_Auto->setFocusPolicy(Qt::NoFocus);
        RBW_Auto->setStyleSheet(QStringLiteral(""));
        RBW_Auto->setCheckable(true);
        RBW_Auto->setAutoExclusive(true);
        RBW_Manual = new QPushButton(RBW_Btn);
        RBW_Manual->setObjectName(QStringLiteral("RBW_Manual"));
        RBW_Manual->setGeometry(QRect(74, 25, 61, 25));
        RBW_Manual->setFocusPolicy(Qt::NoFocus);
        RBW_Manual->setStyleSheet(QStringLiteral(""));
        RBW_Manual->setCheckable(true);
        RBW_Manual->setChecked(true);
        RBW_Manual->setAutoExclusive(true);
        Span_Full = new SA_ClickedWidget(widget);
        Span_Full->setObjectName(QStringLiteral("Span_Full"));
        Span_Full->setGeometry(QRect(119, 456, 140, 55));
        Span_Full->setFocusPolicy(Qt::StrongFocus);
        label_30 = new QLabel(Span_Full);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(5, 1, 130, 22));
        pb_FullSpan = new QPushButton(Span_Full);
        pb_FullSpan->setObjectName(QStringLiteral("pb_FullSpan"));
        pb_FullSpan->setGeometry(QRect(123, 5, 12, 12));
        pb_FullSpan->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/inform_cir_r10_off.png);\n"
"}\n"
"QPushButton:checked\n"
"{\n"
"	background-image: url(:/sa/image/inform_cir_r10_on.png);\n"
"}"));
        pb_FullSpan->setCheckable(true);
        pb_FullSpan->setChecked(false);
        Title_Sweep = new QLabel(widget);
        Title_Sweep->setObjectName(QStringLiteral("Title_Sweep"));
        Title_Sweep->setGeometry(QRect(569, 30, 140, 19));
        Sweep_Time = new SA_ClickedWidget(widget);
        Sweep_Time->setObjectName(QStringLiteral("Sweep_Time"));
        Sweep_Time->setGeometry(QRect(569, 131, 140, 55));
        Sweep_Time->setFocusPolicy(Qt::StrongFocus);
        Sweep_Time->setStyleSheet(QStringLiteral(""));
        Title_Time = new QLabel(Sweep_Time);
        Title_Time->setObjectName(QStringLiteral("Title_Time"));
        Title_Time->setGeometry(QRect(5, 1, 121, 22));
        value_SweepTime = new QLabel(Sweep_Time);
        value_SweepTime->setObjectName(QStringLiteral("value_SweepTime"));
        value_SweepTime->setGeometry(QRect(5, 28, 121, 22));
        value_SweepTime->setStyleSheet(QStringLiteral(""));
        Ref_Level = new SA_ClickedWidget(widget);
        Ref_Level->setObjectName(QStringLiteral("Ref_Level"));
        Ref_Level->setGeometry(QRect(419, 131, 140, 55));
        Ref_Level->setFocusPolicy(Qt::StrongFocus);
        Ref_Level->setStyleSheet(QStringLiteral(""));
        Title_Ref_Level = new QLabel(Ref_Level);
        Title_Ref_Level->setObjectName(QStringLiteral("Title_Ref_Level"));
        Title_Ref_Level->setGeometry(QRect(5, 1, 121, 22));
        value_Ref_Level = new QLabel(Ref_Level);
        value_Ref_Level->setObjectName(QStringLiteral("value_Ref_Level"));
        value_Ref_Level->setGeometry(QRect(5, 28, 121, 22));
        value_Ref_Level->setStyleSheet(QStringLiteral(""));
        Channel_STD = new SA_ClickedWidget(widget);
        Channel_STD->setObjectName(QStringLiteral("Channel_STD"));
        Channel_STD->setGeometry(QRect(269, 66, 140, 55));
        Channel_STD->setFocusPolicy(Qt::StrongFocus);
        Channel_STD->setStyleSheet(QStringLiteral(""));
        Title_Channel = new QLabel(Channel_STD);
        Title_Channel->setObjectName(QStringLiteral("Title_Channel"));
        Title_Channel->setGeometry(QRect(5, 1, 121, 22));
        value_Channel = new QLabel(Channel_STD);
        value_Channel->setObjectName(QStringLiteral("value_Channel"));
        value_Channel->setGeometry(QRect(5, 28, 131, 22));
        value_Channel->setStyleSheet(QStringLiteral(""));
        Title_Trace = new QLabel(widget);
        Title_Trace->setObjectName(QStringLiteral("Title_Trace"));
        Title_Trace->setGeometry(QRect(1019, 30, 131, 19));
        Average = new SA_ClickedWidget(widget);
        Average->setObjectName(QStringLiteral("Average"));
        Average->setGeometry(QRect(1019, 326, 140, 55));
        Average->setFocusPolicy(Qt::StrongFocus);
        Average->setStyleSheet(QStringLiteral(""));
        Title_Average = new QLabel(Average);
        Title_Average->setObjectName(QStringLiteral("Title_Average"));
        Title_Average->setGeometry(QRect(5, 1, 121, 22));
        value_Average = new QLabel(Average);
        value_Average->setObjectName(QStringLiteral("value_Average"));
        value_Average->setGeometry(QRect(5, 28, 121, 22));
        value_Average->setStyleSheet(QStringLiteral(""));
        RBW_Freq = new SA_ClickedWidget(widget);
        RBW_Freq->setObjectName(QStringLiteral("RBW_Freq"));
        RBW_Freq->setGeometry(QRect(719, 66, 140, 55));
        RBW_Freq->setFocusPolicy(Qt::StrongFocus);
        RBW_Freq->setStyleSheet(QStringLiteral(""));
        Title_RBW = new QLabel(RBW_Freq);
        Title_RBW->setObjectName(QStringLiteral("Title_RBW"));
        Title_RBW->setGeometry(QRect(5, 1, 121, 22));
        value_RBW = new SA_Combobox(RBW_Freq);
        value_RBW->setObjectName(QStringLiteral("value_RBW"));
        value_RBW->setEnabled(true);
        value_RBW->setGeometry(QRect(0, 0, 140, 55));
        value_RBW->setFocusPolicy(Qt::StrongFocus);
        value_RBW->setStyleSheet(QStringLiteral(""));
        value_RBW->setMaxVisibleItems(999);
        Trace_View = new SA_ClickedWidget(widget);
        Trace_View->setObjectName(QStringLiteral("Trace_View"));
        Trace_View->setGeometry(QRect(1019, 131, 140, 55));
        Trace_View->setFocusPolicy(Qt::StrongFocus);
        Trace_View->setStyleSheet(QStringLiteral(""));
        Title_TraceView = new QLabel(Trace_View);
        Title_TraceView->setObjectName(QStringLiteral("Title_TraceView"));
        Title_TraceView->setGeometry(QRect(5, 1, 121, 22));
        btn_TraceView = new QPushButton(Trace_View);
        btn_TraceView->setObjectName(QStringLiteral("btn_TraceView"));
        btn_TraceView->setGeometry(QRect(60, 25, 75, 25));
        btn_TraceView->setFocusPolicy(Qt::NoFocus);
        btn_TraceView->setStyleSheet(QLatin1String("\n"
"\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************nigh"
                        "t**********************/\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(56,49,37,1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}"));
        btn_TraceView->setCheckable(true);
        btn_TraceView->setChecked(true);
        Freq_Step = new SA_ClickedWidget(widget);
        Freq_Step->setObjectName(QStringLiteral("Freq_Step"));
        Freq_Step->setGeometry(QRect(119, 261, 140, 55));
        Freq_Step->setFocusPolicy(Qt::StrongFocus);
        Title_FreqStep = new QLabel(Freq_Step);
        Title_FreqStep->setObjectName(QStringLiteral("Title_FreqStep"));
        Title_FreqStep->setGeometry(QRect(5, 1, 121, 22));
        value_FreqStep = new QLabel(Freq_Step);
        value_FreqStep->setObjectName(QStringLiteral("value_FreqStep"));
        value_FreqStep->setGeometry(QRect(5, 28, 133, 22));
        value_FreqStep->setStyleSheet(QStringLiteral(""));
        Freq_Stop = new SA_ClickedWidget(widget);
        Freq_Stop->setObjectName(QStringLiteral("Freq_Stop"));
        Freq_Stop->setGeometry(QRect(119, 196, 140, 55));
        Freq_Stop->setFocusPolicy(Qt::StrongFocus);
        Title_StopFreq = new QLabel(Freq_Stop);
        Title_StopFreq->setObjectName(QStringLiteral("Title_StopFreq"));
        Title_StopFreq->setGeometry(QRect(5, 1, 121, 22));
        value_StopFreq = new QLabel(Freq_Stop);
        value_StopFreq->setObjectName(QStringLiteral("value_StopFreq"));
        value_StopFreq->setGeometry(QRect(5, 28, 133, 22));
        value_StopFreq->setStyleSheet(QStringLiteral(""));
        Scale_Division = new SA_ClickedWidget(widget);
        Scale_Division->setObjectName(QStringLiteral("Scale_Division"));
        Scale_Division->setGeometry(QRect(419, 196, 140, 55));
        Scale_Division->setFocusPolicy(Qt::StrongFocus);
        Scale_Division->setStyleSheet(QStringLiteral(""));
        Title_Scale = new QLabel(Scale_Division);
        Title_Scale->setObjectName(QStringLiteral("Title_Scale"));
        Title_Scale->setGeometry(QRect(5, 1, 121, 22));
        value_Scale = new QLabel(Scale_Division);
        value_Scale->setObjectName(QStringLiteral("value_Scale"));
        value_Scale->setGeometry(QRect(5, 28, 121, 22));
        value_Scale->setStyleSheet(QStringLiteral(""));
        Title_Trigger = new QLabel(widget);
        Title_Trigger->setObjectName(QStringLiteral("Title_Trigger"));
        Title_Trigger->setGeometry(QRect(869, 30, 131, 19));
        Trace_Select = new SA_ClickedWidget(widget);
        Trace_Select->setObjectName(QStringLiteral("Trace_Select"));
        Trace_Select->setGeometry(QRect(1019, 66, 140, 55));
        Trace_Select->setFocusPolicy(Qt::StrongFocus);
        Trace_Select->setStyleSheet(QStringLiteral(""));
        Title_TraceSelect = new QLabel(Trace_Select);
        Title_TraceSelect->setObjectName(QStringLiteral("Title_TraceSelect"));
        Title_TraceSelect->setGeometry(QRect(5, 1, 121, 22));
        value_Trace = new SA_Combobox(Trace_Select);
        value_Trace->setObjectName(QStringLiteral("value_Trace"));
        value_Trace->setEnabled(true);
        value_Trace->setGeometry(QRect(0, 0, 140, 55));
        value_Trace->setFocusPolicy(Qt::StrongFocus);
        value_Trace->setStyleSheet(QStringLiteral(""));
        Channel_Num = new SA_ClickedWidget(widget);
        Channel_Num->setObjectName(QStringLiteral("Channel_Num"));
        Channel_Num->setGeometry(QRect(269, 131, 140, 55));
        Channel_Num->setFocusPolicy(Qt::StrongFocus);
        Channel_Num->setStyleSheet(QStringLiteral(""));
        Title_ChannelNum = new QLabel(Channel_Num);
        Title_ChannelNum->setObjectName(QStringLiteral("Title_ChannelNum"));
        Title_ChannelNum->setGeometry(QRect(5, 1, 121, 22));
        value_ChannelNum = new QLabel(Channel_Num);
        value_ChannelNum->setObjectName(QStringLiteral("value_ChannelNum"));
        value_ChannelNum->setGeometry(QRect(5, 28, 121, 22));
        value_ChannelNum->setStyleSheet(QStringLiteral(""));
        Title_Bw = new QLabel(widget);
        Title_Bw->setObjectName(QStringLiteral("Title_Bw"));
        Title_Bw->setGeometry(QRect(719, 30, 140, 19));
        Span_Zero = new SA_ClickedWidget(widget);
        Span_Zero->setObjectName(QStringLiteral("Span_Zero"));
        Span_Zero->setGeometry(QRect(119, 521, 140, 55));
        Span_Zero->setFocusPolicy(Qt::StrongFocus);
        label_32 = new QLabel(Span_Zero);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setGeometry(QRect(5, 1, 130, 22));
        pb_ZeroSpan = new QPushButton(Span_Zero);
        pb_ZeroSpan->setObjectName(QStringLiteral("pb_ZeroSpan"));
        pb_ZeroSpan->setGeometry(QRect(123, 5, 12, 12));
        pb_ZeroSpan->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/inform_cir_r10_off.png);\n"
"}\n"
"QPushButton:checked\n"
"{\n"
"	background-image: url(:/sa/image/inform_cir_r10_on.png);\n"
"}"));
        pb_ZeroSpan->setCheckable(true);
        Span = new SA_ClickedWidget(widget);
        Span->setObjectName(QStringLiteral("Span"));
        Span->setGeometry(QRect(119, 391, 140, 55));
        Span->setFocusPolicy(Qt::StrongFocus);
        Title_Span = new QLabel(Span);
        Title_Span->setObjectName(QStringLiteral("Title_Span"));
        Title_Span->setGeometry(QRect(5, 1, 121, 22));
        value_Span = new QLabel(Span);
        value_Span->setObjectName(QStringLiteral("value_Span"));
        value_Span->setGeometry(QRect(5, 28, 133, 22));
        value_Span->setStyleSheet(QStringLiteral(""));
        VBW_Freq = new SA_ClickedWidget(widget);
        VBW_Freq->setObjectName(QStringLiteral("VBW_Freq"));
        VBW_Freq->setGeometry(QRect(719, 196, 140, 55));
        VBW_Freq->setFocusPolicy(Qt::StrongFocus);
        VBW_Freq->setStyleSheet(QStringLiteral(""));
        title_VBW = new QLabel(VBW_Freq);
        title_VBW->setObjectName(QStringLiteral("title_VBW"));
        title_VBW->setGeometry(QRect(5, 1, 121, 22));
        value_VBW = new SA_Combobox(VBW_Freq);
        value_VBW->setObjectName(QStringLiteral("value_VBW"));
        value_VBW->setEnabled(true);
        value_VBW->setGeometry(QRect(0, 0, 140, 55));
        value_VBW->setFocusPolicy(Qt::StrongFocus);
        value_VBW->setStyleSheet(QStringLiteral(""));
        value_VBW->setEditable(false);
        value_VBW->setMaxVisibleItems(112);
        Ref_Offset = new SA_ClickedWidget(widget);
        Ref_Offset->setObjectName(QStringLiteral("Ref_Offset"));
        Ref_Offset->setGeometry(QRect(419, 456, 140, 55));
        Ref_Offset->setFocusPolicy(Qt::StrongFocus);
        Ref_Offset->setStyleSheet(QStringLiteral(""));
        Title_RefOffset = new QLabel(Ref_Offset);
        Title_RefOffset->setObjectName(QStringLiteral("Title_RefOffset"));
        Title_RefOffset->setGeometry(QRect(5, 1, 121, 22));
        value_RefOffset = new QLabel(Ref_Offset);
        value_RefOffset->setObjectName(QStringLiteral("value_RefOffset"));
        value_RefOffset->setGeometry(QRect(5, 28, 133, 22));
        value_RefOffset->setStyleSheet(QStringLiteral(""));
        Preamp = new SA_ClickedWidget(widget);
        Preamp->setObjectName(QStringLiteral("Preamp"));
        Preamp->setGeometry(QRect(419, 391, 140, 55));
        Preamp->setFocusPolicy(Qt::StrongFocus);
        Preamp->setStyleSheet(QStringLiteral(""));
        Title_Preamp = new QLabel(Preamp);
        Title_Preamp->setObjectName(QStringLiteral("Title_Preamp"));
        Title_Preamp->setGeometry(QRect(5, 1, 121, 22));
        btn_Preamp = new QPushButton(Preamp);
        btn_Preamp->setObjectName(QStringLiteral("btn_Preamp"));
        btn_Preamp->setGeometry(QRect(60, 25, 75, 25));
        btn_Preamp->setFocusPolicy(Qt::NoFocus);
        btn_Preamp->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************night*********"
                        "*************/\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(56,49,37,1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}"));
        btn_Preamp->setCheckable(true);
        btn_Preamp->setChecked(true);
        Trace_Type = new SA_ClickedWidget(widget);
        Trace_Type->setObjectName(QStringLiteral("Trace_Type"));
        Trace_Type->setGeometry(QRect(1019, 261, 140, 55));
        Trace_Type->setFocusPolicy(Qt::StrongFocus);
        Trace_Type->setStyleSheet(QStringLiteral(""));
        Title_TraceType = new QLabel(Trace_Type);
        Title_TraceType->setObjectName(QStringLiteral("Title_TraceType"));
        Title_TraceType->setGeometry(QRect(5, 1, 121, 22));
        value_TraceType = new SA_Combobox(Trace_Type);
        value_TraceType->setObjectName(QStringLiteral("value_TraceType"));
        value_TraceType->setEnabled(true);
        value_TraceType->setGeometry(QRect(0, 0, 140, 55));
        value_TraceType->setFocusPolicy(Qt::StrongFocus);
        value_TraceType->setStyleSheet(QStringLiteral(""));
        Sweep_Mode = new SA_ClickedWidget(widget);
        Sweep_Mode->setObjectName(QStringLiteral("Sweep_Mode"));
        Sweep_Mode->setGeometry(QRect(569, 196, 140, 55));
        Sweep_Mode->setFocusPolicy(Qt::StrongFocus);
        Sweep_Mode->setStyleSheet(QStringLiteral(""));
        Title_SweepType = new QLabel(Sweep_Mode);
        Title_SweepType->setObjectName(QStringLiteral("Title_SweepType"));
        Title_SweepType->setGeometry(QRect(5, 1, 121, 22));
        Sweep_Conti = new QPushButton(Sweep_Mode);
        Sweep_Conti->setObjectName(QStringLiteral("Sweep_Conti"));
        Sweep_Conti->setGeometry(QRect(10, 25, 61, 25));
        Sweep_Conti->setFocusPolicy(Qt::NoFocus);
        Sweep_Conti->setStyleSheet(QStringLiteral(""));
        Sweep_Conti->setCheckable(true);
        Sweep_Conti->setAutoExclusive(true);
        Sweep_Conti->setFlat(false);
        Sweep_Single = new QPushButton(Sweep_Mode);
        Sweep_Single->setObjectName(QStringLiteral("Sweep_Single"));
        Sweep_Single->setGeometry(QRect(74, 25, 61, 25));
        Sweep_Single->setFocusPolicy(Qt::NoFocus);
        Sweep_Single->setStyleSheet(QStringLiteral(""));
        Sweep_Single->setCheckable(true);
        Sweep_Single->setChecked(true);
        Sweep_Single->setAutoExclusive(true);
        Sweep_Single->setFlat(false);
        Auto_SweepTime = new SA_ClickedWidget(widget);
        Auto_SweepTime->setObjectName(QStringLiteral("Auto_SweepTime"));
        Auto_SweepTime->setGeometry(QRect(569, 66, 140, 55));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        Auto_SweepTime->setFont(font2);
        Auto_SweepTime->setFocusPolicy(Qt::StrongFocus);
        Auto_SweepTime->setStyleSheet(QStringLiteral(""));
        Title_AutoSweepTime = new QLabel(Auto_SweepTime);
        Title_AutoSweepTime->setObjectName(QStringLiteral("Title_AutoSweepTime"));
        Title_AutoSweepTime->setGeometry(QRect(5, 1, 121, 22));
        SweepTime_Manual = new QPushButton(Auto_SweepTime);
        buttonGroup = new QButtonGroup(SA_Dialog_AllSetup);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(SweepTime_Manual);
        SweepTime_Manual->setObjectName(QStringLiteral("SweepTime_Manual"));
        SweepTime_Manual->setGeometry(QRect(74, 25, 61, 25));
        SweepTime_Manual->setFocusPolicy(Qt::NoFocus);
        SweepTime_Manual->setStyleSheet(QStringLiteral(""));
        SweepTime_Manual->setCheckable(true);
        SweepTime_Manual->setChecked(true);
        SweepTime_Manual->setAutoExclusive(true);
        SweepTime_Manual->setFlat(false);
        SweepTime_Auto = new QPushButton(Auto_SweepTime);
        buttonGroup->addButton(SweepTime_Auto);
        SweepTime_Auto->setObjectName(QStringLiteral("SweepTime_Auto"));
        SweepTime_Auto->setGeometry(QRect(10, 25, 61, 25));
        SweepTime_Auto->setFocusPolicy(Qt::NoFocus);
        SweepTime_Auto->setStyleSheet(QStringLiteral(""));
        SweepTime_Auto->setCheckable(true);
        SweepTime_Auto->setAutoExclusive(true);
        SweepTime_Auto->setFlat(false);
        Freq_Start = new SA_ClickedWidget(widget);
        Freq_Start->setObjectName(QStringLiteral("Freq_Start"));
        Freq_Start->setGeometry(QRect(119, 131, 140, 55));
        Freq_Start->setFocusPolicy(Qt::StrongFocus);
        Title_StartFreq = new QLabel(Freq_Start);
        Title_StartFreq->setObjectName(QStringLiteral("Title_StartFreq"));
        Title_StartFreq->setGeometry(QRect(5, 1, 121, 22));
        value_StartFreq = new QLabel(Freq_Start);
        value_StartFreq->setObjectName(QStringLiteral("value_StartFreq"));
        value_StartFreq->setGeometry(QRect(5, 28, 133, 22));
        value_StartFreq->setStyleSheet(QStringLiteral(""));
        Scale_Unit = new SA_ClickedWidget(widget);
        Scale_Unit->setObjectName(QStringLiteral("Scale_Unit"));
        Scale_Unit->setGeometry(QRect(419, 521, 140, 55));
        Scale_Unit->setFocusPolicy(Qt::StrongFocus);
        Scale_Unit->setStyleSheet(QStringLiteral(""));
        Title_Unit = new QLabel(Scale_Unit);
        Title_Unit->setObjectName(QStringLiteral("Title_Unit"));
        Title_Unit->setGeometry(QRect(5, 1, 121, 22));
        value_Unit = new SA_Combobox(Scale_Unit);
        value_Unit->setObjectName(QStringLiteral("value_Unit"));
        value_Unit->setEnabled(true);
        value_Unit->setGeometry(QRect(0, 0, 140, 55));
        value_Unit->setFocusPolicy(Qt::StrongFocus);
        value_Unit->setStyleSheet(QStringLiteral(""));
        Channel_Type = new SA_ClickedWidget(widget);
        Channel_Type->setObjectName(QStringLiteral("Channel_Type"));
        Channel_Type->setGeometry(QRect(269, 261, 140, 55));
        Channel_Type->setFocusPolicy(Qt::StrongFocus);
        Channel_Type->setStyleSheet(QStringLiteral(""));
        Title_ChannelType = new QLabel(Channel_Type);
        Title_ChannelType->setObjectName(QStringLiteral("Title_ChannelType"));
        Title_ChannelType->setGeometry(QRect(5, 1, 121, 22));
        Channel_Uplink = new QPushButton(Channel_Type);
        Channel_Uplink->setObjectName(QStringLiteral("Channel_Uplink"));
        Channel_Uplink->setGeometry(QRect(10, 25, 61, 25));
        Channel_Uplink->setFocusPolicy(Qt::NoFocus);
        Channel_Uplink->setStyleSheet(QStringLiteral(""));
        Channel_Uplink->setCheckable(true);
        Channel_Uplink->setChecked(false);
        Channel_Uplink->setAutoExclusive(true);
        Channel_Uplink->setFlat(false);
        Channel_Downlink = new QPushButton(Channel_Type);
        Channel_Downlink->setObjectName(QStringLiteral("Channel_Downlink"));
        Channel_Downlink->setGeometry(QRect(74, 25, 61, 25));
        Channel_Downlink->setFocusPolicy(Qt::NoFocus);
        Channel_Downlink->setCheckable(true);
        Channel_Downlink->setChecked(true);
        Channel_Downlink->setAutoExclusive(true);
        Channel_Downlink->setFlat(false);
        Atten_Value = new SA_ClickedWidget(widget);
        Atten_Value->setObjectName(QStringLiteral("Atten_Value"));
        Atten_Value->setGeometry(QRect(419, 326, 140, 55));
        Atten_Value->setFocusPolicy(Qt::StrongFocus);
        Atten_Value->setStyleSheet(QStringLiteral(""));
        Title_AttenValue = new QLabel(Atten_Value);
        Title_AttenValue->setObjectName(QStringLiteral("Title_AttenValue"));
        Title_AttenValue->setGeometry(QRect(5, 1, 121, 22));
        value_AttenValue = new QLabel(Atten_Value);
        value_AttenValue->setObjectName(QStringLiteral("value_AttenValue"));
        value_AttenValue->setGeometry(QRect(5, 28, 121, 22));
        value_AttenValue->setStyleSheet(QStringLiteral(""));
        Average_Toggle = new SA_ClickedWidget(widget);
        Average_Toggle->setObjectName(QStringLiteral("Average_Toggle"));
        Average_Toggle->setGeometry(QRect(710, 590, 140, 55));
        Average_Toggle->setFont(font2);
        Average_Toggle->setFocusPolicy(Qt::StrongFocus);
        Average_Toggle->setStyleSheet(QStringLiteral(""));
        Title_AverageToggle = new QLabel(Average_Toggle);
        Title_AverageToggle->setObjectName(QStringLiteral("Title_AverageToggle"));
        Title_AverageToggle->setGeometry(QRect(5, 1, 121, 22));
        btn_Average = new QPushButton(Average_Toggle);
        btn_Average->setObjectName(QStringLiteral("btn_Average"));
        btn_Average->setGeometry(QRect(60, 25, 75, 25));
        btn_Average->setFocusPolicy(Qt::NoFocus);
        btn_Average->setStyleSheet(QLatin1String("\n"
"\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************nigh"
                        "t**********************/\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(56,49,37,1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}"));
        btn_Average->setCheckable(true);
        btn_Average->setChecked(true);
        line = new QFrame(widget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(121, 60, 287, 3));
        line->setStyleSheet(QStringLiteral(""));
        line->setLineWidth(3);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(widget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(1021, 61, 137, 3));
        line_2->setStyleSheet(QStringLiteral(""));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(widget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(871, 61, 137, 3));
        line_3->setStyleSheet(QStringLiteral(""));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(widget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(421, 61, 137, 3));
        line_4->setStyleSheet(QStringLiteral(""));
        line_4->setLineWidth(3);
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(widget);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(721, 61, 137, 3));
        line_5->setStyleSheet(QStringLiteral(""));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        line_6 = new QFrame(widget);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(569, 61, 137, 3));
        line_6->setStyleSheet(QStringLiteral(""));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);
        pb_prePage = new QPushButton(widget);
        pb_prePage->setObjectName(QStringLiteral("pb_prePage"));
        pb_prePage->setEnabled(false);
        pb_prePage->setGeometry(QRect(30, 334, 52, 52));
        pb_prePage->setStyleSheet(QLatin1String("/******************indoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton\n"
"{\n"
"	border-radius:25px;\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/btn_left_r50_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_left_r50_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton:!enabled\n"
"{\n"
"	background-image: url(:/sa/image/btn_left_r50_disable.png);\n"
"}\n"
"/******************outdoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton\n"
"{\n"
"	border-radius:25px;\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/btn_left_r50_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_left_r50_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton:!enabled\n"
"{\n"
"	background-image: url(:/sa/image/btn_left_r50_disable"
                        ".png);\n"
"}\n"
"\n"
"/********************night********************/\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton\n"
"{\n"
"	border-radius:25px;\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/night/btn_left_w52_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton:pressed\n"
"{\n"
"	background-image:url(:/sa/image/night/btn_left_w52_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton:!enabled\n"
"{\n"
"	background-image: url(:/sa/image/night/btn_left_w52_disable.png);\n"
"}"));
        pb_nextPage = new QPushButton(widget);
        pb_nextPage->setObjectName(QStringLiteral("pb_nextPage"));
        pb_nextPage->setGeometry(QRect(1198, 334, 52, 52));
        pb_nextPage->setStyleSheet(QLatin1String("/********************indoor*******************/\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton\n"
"{\n"
"	border-radius:25px;\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/btn_right_r50_nor.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_right_r50_click.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton::disable\n"
"{\n"
"	background-image: url(:/sa/image/btn_right_r50_disable.png);\n"
"}\n"
"\n"
"/********************outdoor*******************/\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton\n"
"{\n"
"	border-radius:25px;\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/btn_right_r50_nor.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_right_r50_click.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton::disable\n"
"{\n"
"	background-image: url(:/sa/image/btn_right_r50_disable.png);\n"
""
                        "}\n"
"\n"
"/********************night*******************/\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton\n"
"{\n"
"	border-radius:25px;\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/night/btn_right_w52_normal.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/btn_right_w52_click.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton::disable\n"
"{\n"
"	background-image: url(:/sa/image/night/btn_right_w52_disable.png);\n"
"}"));
        Sweep_Once = new SA_ClickedWidget(widget);
        Sweep_Once->setObjectName(QStringLiteral("Sweep_Once"));
        Sweep_Once->setGeometry(QRect(569, 261, 140, 55));
        Sweep_Once->setFocusPolicy(Qt::StrongFocus);
        Sweep_Once->setStyleSheet(QStringLiteral(""));
        Title_SweepOnce = new QLabel(Sweep_Once);
        Title_SweepOnce->setObjectName(QStringLiteral("Title_SweepOnce"));
        Title_SweepOnce->setGeometry(QRect(5, 1, 130, 22));
        pb_SweepOnce = new QPushButton(Sweep_Once);
        pb_SweepOnce->setObjectName(QStringLiteral("pb_SweepOnce"));
        pb_SweepOnce->setGeometry(QRect(123, 5, 12, 12));
        pb_SweepOnce->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/inform_cir_r10_off.png);\n"
"}\n"
"QPushButton:checked\n"
"{\n"
"	background-image: url(:/sa/image/inform_cir_r10_on.png);\n"
"}"));
        pb_SweepOnce->setCheckable(true);
        Trace_AllOn = new SA_ClickedWidget(widget);
        Trace_AllOn->setObjectName(QStringLiteral("Trace_AllOn"));
        Trace_AllOn->setGeometry(QRect(1019, 196, 140, 55));
        Trace_AllOn->setFocusPolicy(Qt::StrongFocus);
        Trace_AllOn->setStyleSheet(QStringLiteral(""));
        Title_TraceAllOn = new QLabel(Trace_AllOn);
        Title_TraceAllOn->setObjectName(QStringLiteral("Title_TraceAllOn"));
        Title_TraceAllOn->setGeometry(QRect(5, 1, 130, 22));
        pb_TraceAllOn = new QPushButton(Trace_AllOn);
        pb_TraceAllOn->setObjectName(QStringLiteral("pb_TraceAllOn"));
        pb_TraceAllOn->setGeometry(QRect(123, 5, 12, 12));
        pb_TraceAllOn->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/inform_cir_r10_off.png);\n"
"}\n"
"QPushButton:checked\n"
"{\n"
"	background-image: url(:/sa/image/inform_cir_r10_on.png);\n"
"}"));
        pb_TraceAllOn->setCheckable(true);
        Trace_AllClear = new SA_ClickedWidget(widget);
        Trace_AllClear->setObjectName(QStringLiteral("Trace_AllClear"));
        Trace_AllClear->setGeometry(QRect(1019, 391, 140, 55));
        Trace_AllClear->setFont(font2);
        Trace_AllClear->setFocusPolicy(Qt::StrongFocus);
        Trace_AllClear->setStyleSheet(QStringLiteral(""));
        Title_Trace_ClearAll = new QLabel(Trace_AllClear);
        Title_Trace_ClearAll->setObjectName(QStringLiteral("Title_Trace_ClearAll"));
        Title_Trace_ClearAll->setGeometry(QRect(5, 1, 130, 22));
        pb_TraceAllClear = new QPushButton(Trace_AllClear);
        pb_TraceAllClear->setObjectName(QStringLiteral("pb_TraceAllClear"));
        pb_TraceAllClear->setGeometry(QRect(123, 5, 12, 12));
        pb_TraceAllClear->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/inform_cir_r10_off.png);\n"
"}\n"
"QPushButton:checked\n"
"{\n"
"	background-image: url(:/sa/image/inform_cir_r10_on.png);\n"
"}"));
        pb_TraceAllClear->setCheckable(true);
        Trigger_Source = new SA_ClickedWidget(widget);
        Trigger_Source->setObjectName(QStringLiteral("Trigger_Source"));
        Trigger_Source->setGeometry(QRect(869, 66, 140, 55));
        Trigger_Source->setFocusPolicy(Qt::StrongFocus);
        Trigger_Source->setStyleSheet(QStringLiteral(""));
        Title_TriggerSource = new QLabel(Trigger_Source);
        Title_TriggerSource->setObjectName(QStringLiteral("Title_TriggerSource"));
        Title_TriggerSource->setGeometry(QRect(5, 1, 121, 22));
        value_TriggerSource = new SA_Combobox(Trigger_Source);
        value_TriggerSource->setObjectName(QStringLiteral("value_TriggerSource"));
        value_TriggerSource->setEnabled(true);
        value_TriggerSource->setGeometry(QRect(0, 0, 140, 55));
        value_TriggerSource->setFocusPolicy(Qt::StrongFocus);
        value_TriggerSource->setStyleSheet(QStringLiteral(""));
        Trigger_SubMenu = new QStackedWidget(widget);
        Trigger_SubMenu->setObjectName(QStringLiteral("Trigger_SubMenu"));
        Trigger_SubMenu->setGeometry(QRect(869, 131, 140, 391));
        Trigger_SubMenu->setStyleSheet(QStringLiteral(""));
        FreeRun = new QWidget();
        FreeRun->setObjectName(QStringLiteral("FreeRun"));
        Trigger_SubMenu->addWidget(FreeRun);
        External = new QWidget();
        External->setObjectName(QStringLiteral("External"));
        External_DelayTime = new SA_ClickedWidget(External);
        External_DelayTime->setObjectName(QStringLiteral("External_DelayTime"));
        External_DelayTime->setGeometry(QRect(0, 195, 140, 55));
        External_DelayTime->setFocusPolicy(Qt::StrongFocus);
        External_DelayTime->setStyleSheet(QStringLiteral(""));
        Title_External_DelayTime = new QLabel(External_DelayTime);
        Title_External_DelayTime->setObjectName(QStringLiteral("Title_External_DelayTime"));
        Title_External_DelayTime->setGeometry(QRect(5, 1, 121, 22));
        value_External_DelayTime = new QLabel(External_DelayTime);
        value_External_DelayTime->setObjectName(QStringLiteral("value_External_DelayTime"));
        value_External_DelayTime->setGeometry(QRect(5, 28, 121, 22));
        value_External_DelayTime->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"	font:75 13px \"Arial\";\n"
"   font-weight:bold;\n"
"	color: rgba(31, 118, 170, 1);\n"
"}\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QLabel\n"
"{\n"
"	font:75 13px \"Arial\";\n"
"   font-weight:bold;\n"
"	color: rgba(31, 118, 170, 1);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QLabel\n"
"{\n"
"	font:75 13px \"Arial\";\n"
"   font-weight:bold;\n"
"	color: rgba(31, 118, 170, 1);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_AllSetup[status=\"night\"] QLabel\n"
"{\n"
"	font:75 13px \"Arial\";\n"
"   font-weight:bold;\n"
"	color: rgba(30,101,111,1);\n"
"}"));
        External_Slope = new SA_ClickedWidget(External);
        External_Slope->setObjectName(QStringLiteral("External_Slope"));
        External_Slope->setGeometry(QRect(0, 65, 140, 55));
        External_Slope->setFocusPolicy(Qt::StrongFocus);
        External_Slope->setStyleSheet(QStringLiteral(""));
        Title_External_Slope = new QLabel(External_Slope);
        Title_External_Slope->setObjectName(QStringLiteral("Title_External_Slope"));
        Title_External_Slope->setGeometry(QRect(10, 2, 121, 21));
        pb_External_Pos = new QPushButton(External_Slope);
        pb_External_Pos->setObjectName(QStringLiteral("pb_External_Pos"));
        pb_External_Pos->setGeometry(QRect(10, 25, 61, 25));
        pb_External_Pos->setFocusPolicy(Qt::NoFocus);
        pb_External_Pos->setStyleSheet(QStringLiteral(""));
        pb_External_Pos->setCheckable(true);
        pb_External_Pos->setAutoExclusive(true);
        pb_External_Pos->setFlat(false);
        pb_External_Neg = new QPushButton(External_Slope);
        pb_External_Neg->setObjectName(QStringLiteral("pb_External_Neg"));
        pb_External_Neg->setGeometry(QRect(74, 25, 61, 25));
        pb_External_Neg->setFocusPolicy(Qt::NoFocus);
        pb_External_Neg->setStyleSheet(QStringLiteral(""));
        pb_External_Neg->setCheckable(true);
        pb_External_Neg->setChecked(true);
        pb_External_Neg->setAutoExclusive(true);
        pb_External_Neg->setFlat(false);
        External_Level = new SA_ClickedWidget(External);
        External_Level->setObjectName(QStringLiteral("External_Level"));
        External_Level->setGeometry(QRect(0, 0, 140, 55));
        External_Level->setFocusPolicy(Qt::StrongFocus);
        External_Level->setStyleSheet(QStringLiteral(""));
        Title_External_Level = new QLabel(External_Level);
        Title_External_Level->setObjectName(QStringLiteral("Title_External_Level"));
        Title_External_Level->setGeometry(QRect(5, 1, 121, 22));
        Title_External_Level->setStyleSheet(QStringLiteral(""));
        value_External_Level = new QLabel(External_Level);
        value_External_Level->setObjectName(QStringLiteral("value_External_Level"));
        value_External_Level->setGeometry(QRect(5, 28, 121, 22));
        value_External_Level->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"	font:75 13px \"Arial\";\n"
"   font-weight:bold;\n"
"	color: rgba(31, 118, 170, 1);\n"
"}\n"
""));
        External_DelayOn = new SA_ClickedWidget(External);
        External_DelayOn->setObjectName(QStringLiteral("External_DelayOn"));
        External_DelayOn->setGeometry(QRect(0, 130, 140, 55));
        External_DelayOn->setFocusPolicy(Qt::StrongFocus);
        External_DelayOn->setStyleSheet(QStringLiteral(""));
        Title_External_DelayOn = new QLabel(External_DelayOn);
        Title_External_DelayOn->setObjectName(QStringLiteral("Title_External_DelayOn"));
        Title_External_DelayOn->setGeometry(QRect(5, 1, 121, 22));
        value_External_DelayOn = new QPushButton(External_DelayOn);
        value_External_DelayOn->setObjectName(QStringLiteral("value_External_DelayOn"));
        value_External_DelayOn->setGeometry(QRect(60, 25, 75, 25));
        value_External_DelayOn->setFocusPolicy(Qt::NoFocus);
        value_External_DelayOn->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************night*********"
                        "*************/\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(56,49,37,1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}"));
        value_External_DelayOn->setCheckable(true);
        value_External_DelayOn->setChecked(false);
        Trigger_SubMenu->addWidget(External);
        Video = new QWidget();
        Video->setObjectName(QStringLiteral("Video"));
        Video_Slope = new SA_ClickedWidget(Video);
        Video_Slope->setObjectName(QStringLiteral("Video_Slope"));
        Video_Slope->setGeometry(QRect(0, 65, 140, 55));
        Video_Slope->setFocusPolicy(Qt::StrongFocus);
        Video_Slope->setStyleSheet(QStringLiteral(""));
        Title_Video_Slope = new QLabel(Video_Slope);
        Title_Video_Slope->setObjectName(QStringLiteral("Title_Video_Slope"));
        Title_Video_Slope->setGeometry(QRect(10, 2, 121, 21));
        pb_Video_Pos = new QPushButton(Video_Slope);
        pb_Video_Pos->setObjectName(QStringLiteral("pb_Video_Pos"));
        pb_Video_Pos->setGeometry(QRect(10, 25, 61, 25));
        pb_Video_Pos->setFocusPolicy(Qt::NoFocus);
        pb_Video_Pos->setStyleSheet(QStringLiteral(""));
        pb_Video_Pos->setCheckable(true);
        pb_Video_Pos->setAutoExclusive(true);
        pb_Video_Pos->setFlat(false);
        pb_Video_Neg = new QPushButton(Video_Slope);
        pb_Video_Neg->setObjectName(QStringLiteral("pb_Video_Neg"));
        pb_Video_Neg->setGeometry(QRect(74, 25, 61, 25));
        pb_Video_Neg->setFocusPolicy(Qt::NoFocus);
        pb_Video_Neg->setStyleSheet(QStringLiteral(""));
        pb_Video_Neg->setCheckable(true);
        pb_Video_Neg->setChecked(true);
        pb_Video_Neg->setAutoExclusive(true);
        pb_Video_Neg->setFlat(false);
        Video_DelayOn = new SA_ClickedWidget(Video);
        Video_DelayOn->setObjectName(QStringLiteral("Video_DelayOn"));
        Video_DelayOn->setGeometry(QRect(0, 130, 140, 55));
        Video_DelayOn->setFocusPolicy(Qt::StrongFocus);
        Video_DelayOn->setStyleSheet(QStringLiteral(""));
        Title_Video_DelayOn = new QLabel(Video_DelayOn);
        Title_Video_DelayOn->setObjectName(QStringLiteral("Title_Video_DelayOn"));
        Title_Video_DelayOn->setGeometry(QRect(5, 1, 121, 22));
        value_Video_DelayOn = new QPushButton(Video_DelayOn);
        value_Video_DelayOn->setObjectName(QStringLiteral("value_Video_DelayOn"));
        value_Video_DelayOn->setGeometry(QRect(60, 25, 75, 25));
        value_Video_DelayOn->setFocusPolicy(Qt::NoFocus);
        value_Video_DelayOn->setStyleSheet(QLatin1String("\n"
"\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************nigh"
                        "t**********************/\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(56,49,37,1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}"));
        value_Video_DelayOn->setCheckable(true);
        value_Video_DelayOn->setChecked(true);
        Video_DelayTime = new SA_ClickedWidget(Video);
        Video_DelayTime->setObjectName(QStringLiteral("Video_DelayTime"));
        Video_DelayTime->setGeometry(QRect(0, 195, 140, 55));
        Video_DelayTime->setFocusPolicy(Qt::StrongFocus);
        Video_DelayTime->setStyleSheet(QStringLiteral(""));
        Title_Video_DelayTime = new QLabel(Video_DelayTime);
        Title_Video_DelayTime->setObjectName(QStringLiteral("Title_Video_DelayTime"));
        Title_Video_DelayTime->setGeometry(QRect(5, 1, 121, 22));
        value_Video_DelayTime = new QLabel(Video_DelayTime);
        value_Video_DelayTime->setObjectName(QStringLiteral("value_Video_DelayTime"));
        value_Video_DelayTime->setGeometry(QRect(5, 28, 121, 22));
        value_Video_DelayTime->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"	font:75 13px \"Arial\";\n"
"   font-weight:bold;\n"
"	color: rgba(31, 118, 170, 1);\n"
"}\n"
""));
        Video_Level = new SA_ClickedWidget(Video);
        Video_Level->setObjectName(QStringLiteral("Video_Level"));
        Video_Level->setGeometry(QRect(0, 0, 140, 55));
        Video_Level->setFocusPolicy(Qt::StrongFocus);
        Video_Level->setStyleSheet(QStringLiteral(""));
        Title_Video_Level = new QLabel(Video_Level);
        Title_Video_Level->setObjectName(QStringLiteral("Title_Video_Level"));
        Title_Video_Level->setGeometry(QRect(5, 1, 121, 22));
        value_Video_Level = new QLabel(Video_Level);
        value_Video_Level->setObjectName(QStringLiteral("value_Video_Level"));
        value_Video_Level->setGeometry(QRect(5, 28, 121, 22));
        value_Video_Level->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"	font:75 13px \"Arial\";\n"
"   font-weight:bold;\n"
"	color: rgba(31, 118, 170, 1);\n"
"}\n"
""));
        Trigger_SubMenu->addWidget(Video);
        PerTimer = new QWidget();
        PerTimer->setObjectName(QStringLiteral("PerTimer"));
        Peri_Timer = new SA_ClickedWidget(PerTimer);
        Peri_Timer->setObjectName(QStringLiteral("Peri_Timer"));
        Peri_Timer->setGeometry(QRect(0, 0, 140, 55));
        Peri_Timer->setFocusPolicy(Qt::StrongFocus);
        Peri_Timer->setStyleSheet(QStringLiteral(""));
        Title_Peri_Timer = new QLabel(Peri_Timer);
        Title_Peri_Timer->setObjectName(QStringLiteral("Title_Peri_Timer"));
        Title_Peri_Timer->setGeometry(QRect(5, 1, 121, 22));
        value_Peri_Timer = new QLabel(Peri_Timer);
        value_Peri_Timer->setObjectName(QStringLiteral("value_Peri_Timer"));
        value_Peri_Timer->setGeometry(QRect(5, 28, 121, 22));
        value_Peri_Timer->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"	font:75 13px \"Arial\";\n"
"   font-weight:bold;\n"
"	color: rgba(31, 118, 170, 1);\n"
"}\n"
""));
        Peri_DelayOn = new SA_ClickedWidget(PerTimer);
        Peri_DelayOn->setObjectName(QStringLiteral("Peri_DelayOn"));
        Peri_DelayOn->setGeometry(QRect(0, 65, 140, 55));
        Peri_DelayOn->setFocusPolicy(Qt::StrongFocus);
        Peri_DelayOn->setStyleSheet(QStringLiteral(""));
        Title_Peri_DelayOn = new QLabel(Peri_DelayOn);
        Title_Peri_DelayOn->setObjectName(QStringLiteral("Title_Peri_DelayOn"));
        Title_Peri_DelayOn->setGeometry(QRect(5, 1, 121, 22));
        value_Peri_DelayOn = new QPushButton(Peri_DelayOn);
        value_Peri_DelayOn->setObjectName(QStringLiteral("value_Peri_DelayOn"));
        value_Peri_DelayOn->setGeometry(QRect(60, 25, 75, 25));
        value_Peri_DelayOn->setFocusPolicy(Qt::NoFocus);
        value_Peri_DelayOn->setStyleSheet(QLatin1String("\n"
"\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************nigh"
                        "t**********************/\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(56,49,37,1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}"));
        value_Peri_DelayOn->setCheckable(true);
        value_Peri_DelayOn->setChecked(true);
        Peri_DelayTime = new SA_ClickedWidget(PerTimer);
        Peri_DelayTime->setObjectName(QStringLiteral("Peri_DelayTime"));
        Peri_DelayTime->setGeometry(QRect(0, 130, 140, 55));
        Peri_DelayTime->setFocusPolicy(Qt::StrongFocus);
        Peri_DelayTime->setStyleSheet(QStringLiteral(""));
        Title_Peri_DelayTime = new QLabel(Peri_DelayTime);
        Title_Peri_DelayTime->setObjectName(QStringLiteral("Title_Peri_DelayTime"));
        Title_Peri_DelayTime->setGeometry(QRect(5, 1, 121, 22));
        value_Peri_DelayTime = new QLabel(Peri_DelayTime);
        value_Peri_DelayTime->setObjectName(QStringLiteral("value_Peri_DelayTime"));
        value_Peri_DelayTime->setGeometry(QRect(5, 28, 121, 22));
        value_Peri_DelayTime->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"	font:75 13px \"Arial\";\n"
"   font-weight:bold;\n"
"	color: rgba(31, 118, 170, 1);\n"
"}\n"
""));
        Trigger_SubMenu->addWidget(PerTimer);
        RFBurst = new QWidget();
        RFBurst->setObjectName(QStringLiteral("RFBurst"));
        RFBurst_DelayTime = new SA_ClickedWidget(RFBurst);
        RFBurst_DelayTime->setObjectName(QStringLiteral("RFBurst_DelayTime"));
        RFBurst_DelayTime->setGeometry(QRect(0, 195, 140, 55));
        RFBurst_DelayTime->setFocusPolicy(Qt::StrongFocus);
        RFBurst_DelayTime->setStyleSheet(QStringLiteral(""));
        Title_RFBurst_DelayTime = new QLabel(RFBurst_DelayTime);
        Title_RFBurst_DelayTime->setObjectName(QStringLiteral("Title_RFBurst_DelayTime"));
        Title_RFBurst_DelayTime->setGeometry(QRect(5, 1, 121, 22));
        value_RFBurst_DelayTime = new QLabel(RFBurst_DelayTime);
        value_RFBurst_DelayTime->setObjectName(QStringLiteral("value_RFBurst_DelayTime"));
        value_RFBurst_DelayTime->setGeometry(QRect(5, 28, 121, 22));
        value_RFBurst_DelayTime->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"	font:75 13px \"Arial\";\n"
"   font-weight:bold;\n"
"	color: rgba(31, 118, 170, 1);\n"
"}\n"
""));
        RFBurst_Slope = new SA_ClickedWidget(RFBurst);
        RFBurst_Slope->setObjectName(QStringLiteral("RFBurst_Slope"));
        RFBurst_Slope->setGeometry(QRect(0, 65, 140, 55));
        RFBurst_Slope->setFocusPolicy(Qt::StrongFocus);
        RFBurst_Slope->setStyleSheet(QStringLiteral(""));
        Title_RFBurst_Slope = new QLabel(RFBurst_Slope);
        Title_RFBurst_Slope->setObjectName(QStringLiteral("Title_RFBurst_Slope"));
        Title_RFBurst_Slope->setGeometry(QRect(10, 2, 121, 21));
        pb_RFBurst_Pos = new QPushButton(RFBurst_Slope);
        pb_RFBurst_Pos->setObjectName(QStringLiteral("pb_RFBurst_Pos"));
        pb_RFBurst_Pos->setGeometry(QRect(10, 25, 61, 25));
        pb_RFBurst_Pos->setFocusPolicy(Qt::NoFocus);
        pb_RFBurst_Pos->setStyleSheet(QStringLiteral(""));
        pb_RFBurst_Pos->setCheckable(true);
        pb_RFBurst_Pos->setAutoExclusive(true);
        pb_RFBurst_Pos->setFlat(false);
        pb_RFBurst_Neg = new QPushButton(RFBurst_Slope);
        pb_RFBurst_Neg->setObjectName(QStringLiteral("pb_RFBurst_Neg"));
        pb_RFBurst_Neg->setGeometry(QRect(74, 25, 61, 25));
        pb_RFBurst_Neg->setFocusPolicy(Qt::NoFocus);
        pb_RFBurst_Neg->setStyleSheet(QStringLiteral(""));
        pb_RFBurst_Neg->setCheckable(true);
        pb_RFBurst_Neg->setChecked(true);
        pb_RFBurst_Neg->setAutoExclusive(true);
        pb_RFBurst_Neg->setFlat(false);
        RFBurst_Level = new SA_ClickedWidget(RFBurst);
        RFBurst_Level->setObjectName(QStringLiteral("RFBurst_Level"));
        RFBurst_Level->setGeometry(QRect(0, 0, 140, 55));
        RFBurst_Level->setFocusPolicy(Qt::StrongFocus);
        RFBurst_Level->setStyleSheet(QStringLiteral(""));
        Title_RFBurst_Level = new QLabel(RFBurst_Level);
        Title_RFBurst_Level->setObjectName(QStringLiteral("Title_RFBurst_Level"));
        Title_RFBurst_Level->setGeometry(QRect(5, 1, 121, 22));
        value_RFBurst_Level = new QLabel(RFBurst_Level);
        value_RFBurst_Level->setObjectName(QStringLiteral("value_RFBurst_Level"));
        value_RFBurst_Level->setGeometry(QRect(5, 28, 121, 22));
        value_RFBurst_Level->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"	font:75 13px \"Arial\";\n"
"   font-weight:bold;\n"
"	color: rgba(31, 118, 170, 1);\n"
"}\n"
""));
        RFBurst_DelayOn = new SA_ClickedWidget(RFBurst);
        RFBurst_DelayOn->setObjectName(QStringLiteral("RFBurst_DelayOn"));
        RFBurst_DelayOn->setGeometry(QRect(0, 130, 140, 55));
        RFBurst_DelayOn->setFocusPolicy(Qt::StrongFocus);
        RFBurst_DelayOn->setStyleSheet(QStringLiteral(""));
        Title_RFBurst_DelayOn = new QLabel(RFBurst_DelayOn);
        Title_RFBurst_DelayOn->setObjectName(QStringLiteral("Title_RFBurst_DelayOn"));
        Title_RFBurst_DelayOn->setGeometry(QRect(5, 1, 121, 22));
        value_RFBurst_DelayOn = new QPushButton(RFBurst_DelayOn);
        value_RFBurst_DelayOn->setObjectName(QStringLiteral("value_RFBurst_DelayOn"));
        value_RFBurst_DelayOn->setGeometry(QRect(60, 25, 75, 25));
        value_RFBurst_DelayOn->setFocusPolicy(Qt::NoFocus);
        value_RFBurst_DelayOn->setStyleSheet(QLatin1String("\n"
"\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************nigh"
                        "t**********************/\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(56,49,37,1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}"));
        value_RFBurst_DelayOn->setCheckable(true);
        value_RFBurst_DelayOn->setChecked(true);
        Trigger_SubMenu->addWidget(RFBurst);
        GPS = new QWidget();
        GPS->setObjectName(QStringLiteral("GPS"));
        Trigger_SubMenu->addWidget(GPS);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setStyleSheet(QStringLiteral(""));
        widget_2 = new QWidget(page_2);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(0, 0, 1278, 721));
        Limit_Test = new SA_ClickedWidget(widget_2);
        Limit_Test->setObjectName(QStringLiteral("Limit_Test"));
        Limit_Test->setGeometry(QRect(269, 326, 140, 55));
        Limit_Test->setFocusPolicy(Qt::StrongFocus);
        Limit_Test->setStyleSheet(QStringLiteral(""));
        Title_Limit_Test = new QLabel(Limit_Test);
        Title_Limit_Test->setObjectName(QStringLiteral("Title_Limit_Test"));
        Title_Limit_Test->setGeometry(QRect(5, 1, 121, 22));
        Value_Limit_Test = new QPushButton(Limit_Test);
        Value_Limit_Test->setObjectName(QStringLiteral("Value_Limit_Test"));
        Value_Limit_Test->setGeometry(QRect(60, 25, 75, 25));
        Value_Limit_Test->setFocusPolicy(Qt::NoFocus);
        Value_Limit_Test->setStyleSheet(QLatin1String("\n"
"\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************nigh"
                        "t**********************/\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(56,49,37,1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}"));
        Value_Limit_Test->setCheckable(true);
        Value_Limit_Test->setChecked(false);
        pb_nextPage_2 = new QPushButton(widget_2);
        pb_nextPage_2->setObjectName(QStringLiteral("pb_nextPage_2"));
        pb_nextPage_2->setEnabled(false);
        pb_nextPage_2->setGeometry(QRect(1198, 334, 50, 50));
        pb_nextPage_2->setStyleSheet(QLatin1String("/********************indoor*******************/\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton\n"
"{\n"
"	border-radius:25px;\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/btn_right_r50_nor.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_right_r50_click.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton::disable\n"
"{\n"
"	background-image: url(:/sa/image/btn_right_r50_disable.png);\n"
"}\n"
"\n"
"/********************outdoor*******************/\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton\n"
"{\n"
"	border-radius:25px;\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/btn_right_r50_nor.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_right_r50_click.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton::disable\n"
"{\n"
"	background-image: url(:/sa/image/btn_right_r50_disable.png);\n"
""
                        "}\n"
"\n"
"/********************night*******************/\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton\n"
"{\n"
"	border-radius:25px;\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/night/btn_right_w52_normal.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton::pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/btn_right_w52_click.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton::disable\n"
"{\n"
"	background-image: url(:/sa/image/night/btn_right_w52_disable.png);\n"
"}"));
        Noise_Marker = new SA_ClickedWidget(widget_2);
        Noise_Marker->setObjectName(QStringLiteral("Noise_Marker"));
        Noise_Marker->setGeometry(QRect(119, 391, 140, 55));
        Noise_Marker->setFocusPolicy(Qt::StrongFocus);
        Noise_Marker->setStyleSheet(QStringLiteral(""));
        Title_NoiseMarker = new QLabel(Noise_Marker);
        Title_NoiseMarker->setObjectName(QStringLiteral("Title_NoiseMarker"));
        Title_NoiseMarker->setGeometry(QRect(5, 1, 121, 22));
        btn_NoiseMarker = new QPushButton(Noise_Marker);
        btn_NoiseMarker->setObjectName(QStringLiteral("btn_NoiseMarker"));
        btn_NoiseMarker->setGeometry(QRect(60, 25, 75, 25));
        btn_NoiseMarker->setFocusPolicy(Qt::NoFocus);
        btn_NoiseMarker->setStyleSheet(QLatin1String("\n"
"\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************nigh"
                        "t**********************/\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(56,49,37,1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}"));
        btn_NoiseMarker->setCheckable(true);
        btn_NoiseMarker->setChecked(false);
        Limit_Edge_Toggle = new SA_ClickedWidget(widget_2);
        Limit_Edge_Toggle->setObjectName(QStringLiteral("Limit_Edge_Toggle"));
        Limit_Edge_Toggle->setGeometry(QRect(269, 196, 140, 55));
        Limit_Edge_Toggle->setFocusPolicy(Qt::StrongFocus);
        Limit_Edge_Toggle->setStyleSheet(QStringLiteral(""));
        Title_MarkerTable_2 = new QLabel(Limit_Edge_Toggle);
        Title_MarkerTable_2->setObjectName(QStringLiteral("Title_MarkerTable_2"));
        Title_MarkerTable_2->setGeometry(QRect(5, 1, 121, 21));
        value_Limit_Edge_Toggle = new QPushButton(Limit_Edge_Toggle);
        value_Limit_Edge_Toggle->setObjectName(QStringLiteral("value_Limit_Edge_Toggle"));
        value_Limit_Edge_Toggle->setGeometry(QRect(60, 25, 75, 25));
        value_Limit_Edge_Toggle->setFocusPolicy(Qt::NoFocus);
        value_Limit_Edge_Toggle->setStyleSheet(QLatin1String("\n"
"\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************nigh"
                        "t**********************/\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(56,49,37,1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}"));
        value_Limit_Edge_Toggle->setCheckable(true);
        value_Limit_Edge_Toggle->setChecked(false);
        Limit_Type = new SA_ClickedWidget(widget_2);
        Limit_Type->setObjectName(QStringLiteral("Limit_Type"));
        Limit_Type->setGeometry(QRect(269, 391, 140, 55));
        Limit_Type->setFocusPolicy(Qt::StrongFocus);
        Limit_Type->setStyleSheet(QStringLiteral(""));
        Title_ChannelType_2 = new QLabel(Limit_Type);
        Title_ChannelType_2->setObjectName(QStringLiteral("Title_ChannelType_2"));
        Title_ChannelType_2->setGeometry(QRect(5, 1, 121, 22));
        btn_Upper = new QPushButton(Limit_Type);
        btn_Upper->setObjectName(QStringLiteral("btn_Upper"));
        btn_Upper->setGeometry(QRect(10, 25, 61, 25));
        btn_Upper->setFocusPolicy(Qt::NoFocus);
        btn_Upper->setStyleSheet(QStringLiteral(""));
        btn_Upper->setCheckable(true);
        btn_Upper->setAutoExclusive(true);
        btn_Upper->setFlat(false);
        btn_Lower = new QPushButton(Limit_Type);
        btn_Lower->setObjectName(QStringLiteral("btn_Lower"));
        btn_Lower->setGeometry(QRect(74, 25, 61, 25));
        btn_Lower->setFocusPolicy(Qt::NoFocus);
        btn_Lower->setStyleSheet(QStringLiteral(""));
        btn_Lower->setCheckable(true);
        btn_Lower->setChecked(true);
        btn_Lower->setAutoExclusive(true);
        btn_Lower->setFlat(false);
        Limit_Edge = new SA_ClickedWidget(widget_2);
        Limit_Edge->setObjectName(QStringLiteral("Limit_Edge"));
        Limit_Edge->setGeometry(QRect(269, 261, 140, 60));
        Limit_Edge->setFocusPolicy(Qt::StrongFocus);
        Limit_Edge->setStyleSheet(QStringLiteral(""));
        Title_Limit_Edge = new QLabel(Limit_Edge);
        Title_Limit_Edge->setObjectName(QStringLiteral("Title_Limit_Edge"));
        Title_Limit_Edge->setGeometry(QRect(5, 1, 121, 22));
        Value_Limit_Edge = new QLabel(Limit_Edge);
        Value_Limit_Edge->setObjectName(QStringLiteral("Value_Limit_Edge"));
        Value_Limit_Edge->setGeometry(QRect(10, 30, 121, 21));
        Value_Limit_Edge->setStyleSheet(QStringLiteral(""));
        pb_prePage_2 = new QPushButton(widget_2);
        pb_prePage_2->setObjectName(QStringLiteral("pb_prePage_2"));
        pb_prePage_2->setEnabled(true);
        pb_prePage_2->setGeometry(QRect(30, 334, 50, 50));
        pb_prePage_2->setStyleSheet(QLatin1String("/******************indoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton\n"
"{\n"
"	border-radius:25px;\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/btn_left_r50_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_left_r50_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton:!enabled\n"
"{\n"
"	background-image: url(:/sa/image/btn_left_r50_disable.png);\n"
"}\n"
"/******************outdoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton\n"
"{\n"
"	border-radius:25px;\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/btn_left_r50_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_left_r50_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton:!enabled\n"
"{\n"
"	background-image: url(:/sa/image/btn_left_r50_disable"
                        ".png);\n"
"}\n"
"\n"
"/********************night********************/\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton\n"
"{\n"
"	border-radius:25px;\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/night/btn_left_w52_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton:pressed\n"
"{\n"
"	background-image:url(:/sa/image/night/btn_left_w52_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton:!enabled\n"
"{\n"
"	background-image: url(:/sa/image/night/btn_left_w52_disable.png);\n"
"}"));
        Limit_Toggle = new SA_ClickedWidget(widget_2);
        Limit_Toggle->setObjectName(QStringLiteral("Limit_Toggle"));
        Limit_Toggle->setGeometry(QRect(269, 131, 140, 55));
        Limit_Toggle->setFocusPolicy(Qt::StrongFocus);
        Limit_Toggle->setStyleSheet(QStringLiteral(""));
        Title_Limit_Toggle = new QLabel(Limit_Toggle);
        Title_Limit_Toggle->setObjectName(QStringLiteral("Title_Limit_Toggle"));
        Title_Limit_Toggle->setGeometry(QRect(5, 1, 121, 21));
        Value_Limit_Toggle = new QPushButton(Limit_Toggle);
        Value_Limit_Toggle->setObjectName(QStringLiteral("Value_Limit_Toggle"));
        Value_Limit_Toggle->setGeometry(QRect(60, 25, 75, 25));
        Value_Limit_Toggle->setFocusPolicy(Qt::NoFocus);
        Value_Limit_Toggle->setStyleSheet(QLatin1String("\n"
"\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************nigh"
                        "t**********************/\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(56,49,37,1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}"));
        Value_Limit_Toggle->setCheckable(true);
        Value_Limit_Toggle->setChecked(false);
        Title_Marker = new QLabel(widget_2);
        Title_Marker->setObjectName(QStringLiteral("Title_Marker"));
        Title_Marker->setGeometry(QRect(119, 30, 131, 19));
        Limit_Select = new SA_ClickedWidget(widget_2);
        Limit_Select->setObjectName(QStringLiteral("Limit_Select"));
        Limit_Select->setGeometry(QRect(269, 66, 140, 55));
        Limit_Select->setFocusPolicy(Qt::StrongFocus);
        Limit_Select->setStyleSheet(QStringLiteral(""));
        Title_LimitSelect = new QLabel(Limit_Select);
        Title_LimitSelect->setObjectName(QStringLiteral("Title_LimitSelect"));
        Title_LimitSelect->setGeometry(QRect(5, 1, 121, 21));
        value_LimitSelect = new SA_Combobox(Limit_Select);
        value_LimitSelect->setObjectName(QStringLiteral("value_LimitSelect"));
        value_LimitSelect->setEnabled(true);
        value_LimitSelect->setGeometry(QRect(0, 0, 140, 55));
        value_LimitSelect->setFocusPolicy(Qt::StrongFocus);
        value_LimitSelect->setStyleSheet(QStringLiteral(""));
        Freq_Count = new SA_ClickedWidget(widget_2);
        Freq_Count->setObjectName(QStringLiteral("Freq_Count"));
        Freq_Count->setGeometry(QRect(119, 456, 140, 60));
        Freq_Count->setFocusPolicy(Qt::StrongFocus);
        Freq_Count->setStyleSheet(QStringLiteral(""));
        Title_FreqCount = new QLabel(Freq_Count);
        Title_FreqCount->setObjectName(QStringLiteral("Title_FreqCount"));
        Title_FreqCount->setGeometry(QRect(5, 1, 121, 22));
        btn_FreqCount = new QPushButton(Freq_Count);
        btn_FreqCount->setObjectName(QStringLiteral("btn_FreqCount"));
        btn_FreqCount->setGeometry(QRect(60, 25, 75, 25));
        btn_FreqCount->setFocusPolicy(Qt::NoFocus);
        btn_FreqCount->setStyleSheet(QLatin1String("\n"
"\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************nigh"
                        "t**********************/\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(56,49,37,1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}"));
        btn_FreqCount->setCheckable(true);
        btn_FreqCount->setChecked(false);
        Marker_Type = new SA_ClickedWidget(widget_2);
        Marker_Type->setObjectName(QStringLiteral("Marker_Type"));
        Marker_Type->setGeometry(QRect(119, 261, 140, 55));
        Marker_Type->setFocusPolicy(Qt::StrongFocus);
        Marker_Type->setStyleSheet(QStringLiteral(""));
        Title_MarkerType = new QLabel(Marker_Type);
        Title_MarkerType->setObjectName(QStringLiteral("Title_MarkerType"));
        Title_MarkerType->setGeometry(QRect(5, 1, 121, 22));
        Marker_Normal = new QPushButton(Marker_Type);
        Marker_Normal->setObjectName(QStringLiteral("Marker_Normal"));
        Marker_Normal->setGeometry(QRect(10, 25, 61, 25));
        Marker_Normal->setFocusPolicy(Qt::NoFocus);
        Marker_Normal->setStyleSheet(QStringLiteral(""));
        Marker_Normal->setCheckable(true);
        Marker_Normal->setAutoExclusive(true);
        Marker_Normal->setFlat(false);
        Marker_Delta = new QPushButton(Marker_Type);
        Marker_Delta->setObjectName(QStringLiteral("Marker_Delta"));
        Marker_Delta->setGeometry(QRect(74, 25, 61, 25));
        Marker_Delta->setFocusPolicy(Qt::NoFocus);
        Marker_Delta->setStyleSheet(QStringLiteral(""));
        Marker_Delta->setCheckable(true);
        Marker_Delta->setChecked(true);
        Marker_Delta->setAutoExclusive(true);
        Marker_Delta->setFlat(false);
        Title_Limit = new QLabel(widget_2);
        Title_Limit->setObjectName(QStringLiteral("Title_Limit"));
        Title_Limit->setGeometry(QRect(269, 30, 131, 19));
        Marker_View = new SA_ClickedWidget(widget_2);
        Marker_View->setObjectName(QStringLiteral("Marker_View"));
        Marker_View->setGeometry(QRect(119, 131, 140, 55));
        Marker_View->setFocusPolicy(Qt::StrongFocus);
        Marker_View->setStyleSheet(QStringLiteral(""));
        Title_MarkerView = new QLabel(Marker_View);
        Title_MarkerView->setObjectName(QStringLiteral("Title_MarkerView"));
        Title_MarkerView->setGeometry(QRect(5, 1, 121, 22));
        btn_MarkerView = new QPushButton(Marker_View);
        btn_MarkerView->setObjectName(QStringLiteral("btn_MarkerView"));
        btn_MarkerView->setGeometry(QRect(60, 25, 75, 25));
        btn_MarkerView->setFocusPolicy(Qt::NoFocus);
        btn_MarkerView->setStyleSheet(QLatin1String("\n"
"\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"indoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"outdoor\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(57, 57, 57, 1);\n"
"	border-image: url(:/sa/image/toggle_on.png);\n"
"}\n"
"\n"
"/*******************nigh"
                        "t**********************/\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton\n"
"{\n"
"	font:75 12px \"Arial\";\n"
"   font-weight:bold;\n"
"	text-align:left;\n"
"	padding-left:36px;\n"
"	color:rgba(148, 148, 148, 1);\n"
"	border-image: url(:/sa/image/night/toggle_off.png);\n"
"}\n"
"#SA_Dialog_AllSetup[status=\"night\"] QPushButton:checked\n"
"{	\n"
"	padding-left:20px;\n"
"	color:rgba(56,49,37,1);\n"
"	border-image: url(:/sa/image/night/toggle_on.png);\n"
"}"));
        btn_MarkerView->setCheckable(true);
        btn_MarkerView->setChecked(false);
        Marker_Select = new SA_ClickedWidget(widget_2);
        Marker_Select->setObjectName(QStringLiteral("Marker_Select"));
        Marker_Select->setGeometry(QRect(119, 66, 140, 55));
        Marker_Select->setFocusPolicy(Qt::StrongFocus);
        Marker_Select->setStyleSheet(QStringLiteral(""));
        Title_MarkerSelect = new QLabel(Marker_Select);
        Title_MarkerSelect->setObjectName(QStringLiteral("Title_MarkerSelect"));
        Title_MarkerSelect->setGeometry(QRect(5, 1, 121, 22));
        value_MarkerSelect = new SA_Combobox(Marker_Select);
        value_MarkerSelect->setObjectName(QStringLiteral("value_MarkerSelect"));
        value_MarkerSelect->setEnabled(true);
        value_MarkerSelect->setGeometry(QRect(0, 0, 140, 55));
        value_MarkerSelect->setFocusPolicy(Qt::StrongFocus);
        value_MarkerSelect->setStyleSheet(QStringLiteral(""));
        line_7 = new QFrame(widget_2);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setGeometry(QRect(121, 61, 137, 3));
        line_7->setStyleSheet(QStringLiteral(""));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);
        line_8 = new QFrame(widget_2);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setGeometry(QRect(271, 61, 137, 3));
        line_8->setStyleSheet(QStringLiteral(""));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);
        Marker_AllOn = new SA_ClickedWidget(widget_2);
        Marker_AllOn->setObjectName(QStringLiteral("Marker_AllOn"));
        Marker_AllOn->setGeometry(QRect(119, 196, 140, 55));
        Marker_AllOn->setFocusPolicy(Qt::StrongFocus);
        Marker_AllOn->setStyleSheet(QStringLiteral(""));
        Title_MarkerView_AllOn = new QLabel(Marker_AllOn);
        Title_MarkerView_AllOn->setObjectName(QStringLiteral("Title_MarkerView_AllOn"));
        Title_MarkerView_AllOn->setGeometry(QRect(5, 1, 130, 22));
        pb_MkrAllOn = new QPushButton(Marker_AllOn);
        pb_MkrAllOn->setObjectName(QStringLiteral("pb_MkrAllOn"));
        pb_MkrAllOn->setGeometry(QRect(123, 5, 12, 12));
        pb_MkrAllOn->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/inform_cir_r10_off.png);\n"
"}\n"
"QPushButton:checked\n"
"{\n"
"	background-image: url(:/sa/image/inform_cir_r10_on.png);\n"
"}"));
        pb_MkrAllOn->setCheckable(true);
        Marker_To = new SA_ClickedWidget(widget_2);
        Marker_To->setObjectName(QStringLiteral("Marker_To"));
        Marker_To->setGeometry(QRect(119, 326, 140, 55));
        Marker_To->setFocusPolicy(Qt::StrongFocus);
        Marker_To->setStyleSheet(QStringLiteral(""));
        Title_MarkerTo = new QLabel(Marker_To);
        Title_MarkerTo->setObjectName(QStringLiteral("Title_MarkerTo"));
        Title_MarkerTo->setGeometry(QRect(5, 1, 121, 22));
        value_MarkerTo = new SA_Combobox(Marker_To);
        value_MarkerTo->setObjectName(QStringLiteral("value_MarkerTo"));
        value_MarkerTo->setEnabled(true);
        value_MarkerTo->setGeometry(QRect(0, 0, 140, 55));
        value_MarkerTo->setFocusPolicy(Qt::StrongFocus);
        value_MarkerTo->setStyleSheet(QStringLiteral(""));
        Limit_AllClear = new SA_ClickedWidget(widget_2);
        Limit_AllClear->setObjectName(QStringLiteral("Limit_AllClear"));
        Limit_AllClear->setGeometry(QRect(269, 456, 140, 55));
        Limit_AllClear->setFocusPolicy(Qt::StrongFocus);
        Limit_AllClear->setStyleSheet(QStringLiteral(""));
        Title_Limit_AllClear = new QLabel(Limit_AllClear);
        Title_Limit_AllClear->setObjectName(QStringLiteral("Title_Limit_AllClear"));
        Title_Limit_AllClear->setGeometry(QRect(5, 1, 130, 22));
        pb_LimitAllDelete = new QPushButton(Limit_AllClear);
        pb_LimitAllDelete->setObjectName(QStringLiteral("pb_LimitAllDelete"));
        pb_LimitAllDelete->setGeometry(QRect(123, 5, 12, 12));
        pb_LimitAllDelete->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/inform_cir_r10_off.png);\n"
"}\n"
"QPushButton:checked\n"
"{\n"
"	background-image: url(:/sa/image/inform_cir_r10_on.png);\n"
"}"));
        pb_LimitAllDelete->setCheckable(true);
        stackedWidget->addWidget(page_2);

        retranslateUi(SA_Dialog_AllSetup);

        stackedWidget->setCurrentIndex(1);
        Trigger_SubMenu->setCurrentIndex(5);


        QMetaObject::connectSlotsByName(SA_Dialog_AllSetup);
    } // setupUi

    void retranslateUi(QWidget *SA_Dialog_AllSetup)
    {
        SA_Dialog_AllSetup->setWindowTitle(QApplication::translate("SA_Dialog_AllSetup", "Form", 0));
        SA_Dialog_AllSetup->setProperty("status", QVariant(QApplication::translate("SA_Dialog_AllSetup", "indoor", 0)));
        lblTitle->setText(QApplication::translate("SA_Dialog_AllSetup", "All Setting", 0));
        pb_cancel->setText(QString());
        Title_VBW_RBW->setText(QApplication::translate("SA_Dialog_AllSetup", "VBW / RBW", 0));
        value_VBW_RBW->clear();
        value_VBW_RBW->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_AllSetup", "1", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "0.1", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "0.01", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "0.001", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "0.0001", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "0.00001", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "0.000001", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "0.0000001", 0)
        );
        Title_FreqOffset->setText(QApplication::translate("SA_Dialog_AllSetup", "Frequency Offset", 0));
        value_FreqOffset->setText(QApplication::translate("SA_Dialog_AllSetup", "0.000 MHz", 0));
        value_FreqOffset->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        Title_Detectors->setText(QApplication::translate("SA_Dialog_AllSetup", "Detector", 0));
        value_Detectors->clear();
        value_Detectors->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_AllSetup", "Auto", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "Positive Peak", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "Negative Peak", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "Sample", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "Normal", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "Average Voltage", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "RMS", 0)
        );
        Title_AutoScale->setText(QApplication::translate("SA_Dialog_AllSetup", "Auto Scale", 0));
        pb_AutoScale->setText(QString());
        Title_Ampt->setText(QApplication::translate("SA_Dialog_AllSetup", "Amplitude", 0));
        Title_Freq->setText(QApplication::translate("SA_Dialog_AllSetup", "Frequency", 0));
        Title_CenterFreq->setText(QApplication::translate("SA_Dialog_AllSetup", "Center Frequency", 0));
        value_CenterFreq->setText(QApplication::translate("SA_Dialog_AllSetup", "1,000.000 MHz", 0));
        value_CenterFreq->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        label_36->setText(QApplication::translate("SA_Dialog_AllSetup", "Last Span", 0));
        pb_LastSpan->setText(QString());
        Title_Atten->setText(QApplication::translate("SA_Dialog_AllSetup", "Attenuation", 0));
        Atten_Auto->setText(QApplication::translate("SA_Dialog_AllSetup", "Auto", 0));
        Atten_Auto->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "left", 0)));
        Atten_Manual->setText(QApplication::translate("SA_Dialog_AllSetup", "Manual", 0));
        Atten_Manual->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "right", 0)));
        Title_VBW_Btn->setText(QApplication::translate("SA_Dialog_AllSetup", "VBW", 0));
        VBW_Auto->setText(QApplication::translate("SA_Dialog_AllSetup", "Auto", 0));
        VBW_Auto->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "left", 0)));
        VBW_Manual->setText(QApplication::translate("SA_Dialog_AllSetup", "Manual", 0));
        VBW_Manual->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "right", 0)));
        Title_ChannelStep->setText(QApplication::translate("SA_Dialog_AllSetup", "Channel Step", 0));
        value_ChannelStep->setText(QApplication::translate("SA_Dialog_AllSetup", "1", 0));
        value_ChannelStep->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        Title_RBW_Btn->setText(QApplication::translate("SA_Dialog_AllSetup", "RBW", 0));
        RBW_Auto->setText(QApplication::translate("SA_Dialog_AllSetup", "Auto", 0));
        RBW_Auto->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "left", 0)));
        RBW_Manual->setText(QApplication::translate("SA_Dialog_AllSetup", "Manual", 0));
        RBW_Manual->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "right", 0)));
        label_30->setText(QApplication::translate("SA_Dialog_AllSetup", "Full Span", 0));
        pb_FullSpan->setText(QString());
        Title_Sweep->setText(QApplication::translate("SA_Dialog_AllSetup", "Sweep", 0));
        Title_Time->setText(QApplication::translate("SA_Dialog_AllSetup", "Sweep Time", 0));
        value_SweepTime->setText(QApplication::translate("SA_Dialog_AllSetup", "100 ms", 0));
        value_SweepTime->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        Title_Ref_Level->setText(QApplication::translate("SA_Dialog_AllSetup", "Reference Level", 0));
        value_Ref_Level->setText(QApplication::translate("SA_Dialog_AllSetup", "0.0 dBm", 0));
        value_Ref_Level->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        Title_Channel->setText(QApplication::translate("SA_Dialog_AllSetup", "Channel Standard", 0));
        value_Channel->setText(QApplication::translate("SA_Dialog_AllSetup", "CDMA-Band 0(800)", 0));
        value_Channel->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        Title_Trace->setText(QApplication::translate("SA_Dialog_AllSetup", "Trace", 0));
        Title_Average->setText(QApplication::translate("SA_Dialog_AllSetup", "Average Count", 0));
        value_Average->setText(QApplication::translate("SA_Dialog_AllSetup", "1", 0));
        value_Average->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        Title_RBW->setText(QApplication::translate("SA_Dialog_AllSetup", "RBW", 0));
        value_RBW->clear();
        value_RBW->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_AllSetup", "5 MHz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "3 MHz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "1 MHz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "300 kHz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "100 kHz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "30 kHz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "10 kHz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "3 kHz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "1 kHz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "300 Hz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "100 Hz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "30 Hz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "10 Hz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "3 Hz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "1 Hz", 0)
        );
        Title_TraceView->setText(QApplication::translate("SA_Dialog_AllSetup", "Trace View", 0));
        btn_TraceView->setText(QApplication::translate("SA_Dialog_AllSetup", "On", 0));
        Title_FreqStep->setText(QApplication::translate("SA_Dialog_AllSetup", "Frequency Step", 0));
        value_FreqStep->setText(QApplication::translate("SA_Dialog_AllSetup", "1.000 MHz", 0));
        value_FreqStep->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        Title_StopFreq->setText(QApplication::translate("SA_Dialog_AllSetup", "Stop Frequency", 0));
        value_StopFreq->setText(QApplication::translate("SA_Dialog_AllSetup", "1,000.000 MHz", 0));
        value_StopFreq->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        Title_Scale->setText(QApplication::translate("SA_Dialog_AllSetup", "Scale / Div", 0));
        value_Scale->setText(QApplication::translate("SA_Dialog_AllSetup", "10.0 dB", 0));
        value_Scale->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        Title_Trigger->setText(QApplication::translate("SA_Dialog_AllSetup", "Trigger", 0));
        Title_TraceSelect->setText(QApplication::translate("SA_Dialog_AllSetup", "Select Trace", 0));
        value_Trace->clear();
        value_Trace->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_AllSetup", "T1", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "T2", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "T3", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "T4", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "T5", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "T6", 0)
        );
        Title_ChannelNum->setText(QApplication::translate("SA_Dialog_AllSetup", "Channel Number", 0));
        value_ChannelNum->setText(QApplication::translate("SA_Dialog_AllSetup", "1", 0));
        value_ChannelNum->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        Title_Bw->setText(QApplication::translate("SA_Dialog_AllSetup", "Bandwidth", 0));
        label_32->setText(QApplication::translate("SA_Dialog_AllSetup", "Zero Span", 0));
        pb_ZeroSpan->setText(QString());
        Title_Span->setText(QApplication::translate("SA_Dialog_AllSetup", "Span", 0));
        value_Span->setText(QApplication::translate("SA_Dialog_AllSetup", "1,000.000 MHz", 0));
        value_Span->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        title_VBW->setText(QApplication::translate("SA_Dialog_AllSetup", "VBW", 0));
        value_VBW->clear();
        value_VBW->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_AllSetup", "3 MHz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "1 MHz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "300 kHz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "100 kHz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "30 kHz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "10 kHz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "3 kHz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "1 kHz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "300 Hz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "100 Hz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "30 Hz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "10 Hz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "3 Hz", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "1 Hz", 0)
        );
        Title_RefOffset->setText(QApplication::translate("SA_Dialog_AllSetup", "External Offset", 0));
        value_RefOffset->setText(QApplication::translate("SA_Dialog_AllSetup", "1,000.000 MHZ", 0));
        value_RefOffset->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        Title_Preamp->setText(QApplication::translate("SA_Dialog_AllSetup", "Preamp", 0));
        btn_Preamp->setText(QApplication::translate("SA_Dialog_AllSetup", "On", 0));
        Title_TraceType->setText(QApplication::translate("SA_Dialog_AllSetup", "Trace Type", 0));
        value_TraceType->clear();
        value_TraceType->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_AllSetup", "Clear Write", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "Max Hold", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "Min Hold", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "View", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "Average", 0)
        );
        Title_SweepType->setText(QApplication::translate("SA_Dialog_AllSetup", "Sweep Mode", 0));
        Sweep_Conti->setText(QApplication::translate("SA_Dialog_AllSetup", "Conti", 0));
        Sweep_Conti->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "left", 0)));
        Sweep_Single->setText(QApplication::translate("SA_Dialog_AllSetup", "Single", 0));
        Sweep_Single->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "right", 0)));
        Title_AutoSweepTime->setText(QApplication::translate("SA_Dialog_AllSetup", "Auto Sweep Time", 0));
        SweepTime_Manual->setText(QApplication::translate("SA_Dialog_AllSetup", "Manual", 0));
        SweepTime_Manual->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "right", 0)));
        SweepTime_Auto->setText(QApplication::translate("SA_Dialog_AllSetup", "Auto", 0));
        SweepTime_Auto->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "left", 0)));
        Title_StartFreq->setText(QApplication::translate("SA_Dialog_AllSetup", "Start Frequency", 0));
        value_StartFreq->setText(QApplication::translate("SA_Dialog_AllSetup", "1,000.000 MHz", 0));
        value_StartFreq->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        Title_Unit->setText(QApplication::translate("SA_Dialog_AllSetup", "Scale Unit", 0));
        value_Unit->clear();
        value_Unit->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_AllSetup", "dBm", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "dBV", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "dBmV", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "dBuV", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "V", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "W", 0)
        );
        Title_ChannelType->setText(QApplication::translate("SA_Dialog_AllSetup", "Channel Type", 0));
        Channel_Uplink->setText(QApplication::translate("SA_Dialog_AllSetup", "Uplink", 0));
        Channel_Uplink->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "left", 0)));
        Channel_Downlink->setText(QApplication::translate("SA_Dialog_AllSetup", "Downlk", 0));
        Channel_Downlink->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "right", 0)));
        Title_AttenValue->setText(QApplication::translate("SA_Dialog_AllSetup", "Attenuation", 0));
        value_AttenValue->setText(QApplication::translate("SA_Dialog_AllSetup", "10 dBm", 0));
        value_AttenValue->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        Title_AverageToggle->setText(QApplication::translate("SA_Dialog_AllSetup", "Average                                    ", 0));
        btn_Average->setText(QApplication::translate("SA_Dialog_AllSetup", "On", 0));
        line->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        line_2->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        line_3->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        line_4->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        line_5->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        line_6->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        pb_prePage->setText(QString());
        pb_nextPage->setText(QString());
        Title_SweepOnce->setText(QApplication::translate("SA_Dialog_AllSetup", "Sweep Once", 0));
        pb_SweepOnce->setText(QString());
        Title_TraceAllOn->setText(QApplication::translate("SA_Dialog_AllSetup", "Trace All On", 0));
        pb_TraceAllOn->setText(QString());
        Title_Trace_ClearAll->setText(QApplication::translate("SA_Dialog_AllSetup", "Trace Clear All", 0));
        pb_TraceAllClear->setText(QString());
        Title_TriggerSource->setText(QApplication::translate("SA_Dialog_AllSetup", "Trace Source", 0));
        value_TriggerSource->clear();
        value_TriggerSource->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_AllSetup", "Free Run", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "External", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "Video", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "Periodic Timer", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "RF Burst", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "GPS", 0)
        );
        Title_External_DelayTime->setText(QApplication::translate("SA_Dialog_AllSetup", "Trigger Delay Time", 0));
        value_External_DelayTime->setText(QApplication::translate("SA_Dialog_AllSetup", "100 ms", 0));
        Title_External_Slope->setText(QApplication::translate("SA_Dialog_AllSetup", "Trigger Slope", 0));
        pb_External_Pos->setText(QApplication::translate("SA_Dialog_AllSetup", "Pos", 0));
        pb_External_Pos->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "left", 0)));
        pb_External_Neg->setText(QApplication::translate("SA_Dialog_AllSetup", "Neg", 0));
        pb_External_Neg->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "right", 0)));
        Title_External_Level->setText(QApplication::translate("SA_Dialog_AllSetup", "Trigger Level", 0));
        Title_External_Level->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "title", 0)));
        value_External_Level->setText(QApplication::translate("SA_Dialog_AllSetup", "0.0 dBm", 0));
        Title_External_DelayOn->setText(QApplication::translate("SA_Dialog_AllSetup", "Trigger Delay", 0));
        value_External_DelayOn->setText(QApplication::translate("SA_Dialog_AllSetup", "On", 0));
        Title_Video_Slope->setText(QApplication::translate("SA_Dialog_AllSetup", "Trigger Slope", 0));
        pb_Video_Pos->setText(QApplication::translate("SA_Dialog_AllSetup", "Pos", 0));
        pb_Video_Pos->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "left", 0)));
        pb_Video_Neg->setText(QApplication::translate("SA_Dialog_AllSetup", "Neg", 0));
        pb_Video_Neg->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "right", 0)));
        Title_Video_DelayOn->setText(QApplication::translate("SA_Dialog_AllSetup", "Trigger Delay", 0));
        value_Video_DelayOn->setText(QApplication::translate("SA_Dialog_AllSetup", "On", 0));
        Title_Video_DelayTime->setText(QApplication::translate("SA_Dialog_AllSetup", "Trigger Delay Time", 0));
        value_Video_DelayTime->setText(QApplication::translate("SA_Dialog_AllSetup", "100 ms", 0));
        Title_Video_Level->setText(QApplication::translate("SA_Dialog_AllSetup", "Trigger Level", 0));
        value_Video_Level->setText(QApplication::translate("SA_Dialog_AllSetup", "0.0 dBm", 0));
        Title_Peri_Timer->setText(QApplication::translate("SA_Dialog_AllSetup", "Perioudic Timer", 0));
        value_Peri_Timer->setText(QApplication::translate("SA_Dialog_AllSetup", "12 ms", 0));
        Title_Peri_DelayOn->setText(QApplication::translate("SA_Dialog_AllSetup", "Trigger Delay", 0));
        value_Peri_DelayOn->setText(QApplication::translate("SA_Dialog_AllSetup", "On", 0));
        Title_Peri_DelayTime->setText(QApplication::translate("SA_Dialog_AllSetup", "Trigger Delay Time", 0));
        value_Peri_DelayTime->setText(QApplication::translate("SA_Dialog_AllSetup", "100 ms", 0));
        Title_RFBurst_DelayTime->setText(QApplication::translate("SA_Dialog_AllSetup", "Trigger Delay Time", 0));
        value_RFBurst_DelayTime->setText(QApplication::translate("SA_Dialog_AllSetup", "100 ms", 0));
        Title_RFBurst_Slope->setText(QApplication::translate("SA_Dialog_AllSetup", "Trigger Slope", 0));
        pb_RFBurst_Pos->setText(QApplication::translate("SA_Dialog_AllSetup", "Pos", 0));
        pb_RFBurst_Pos->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "left", 0)));
        pb_RFBurst_Neg->setText(QApplication::translate("SA_Dialog_AllSetup", "Neg", 0));
        pb_RFBurst_Neg->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "right", 0)));
        Title_RFBurst_Level->setText(QApplication::translate("SA_Dialog_AllSetup", "Trigger Level", 0));
        value_RFBurst_Level->setText(QApplication::translate("SA_Dialog_AllSetup", "0.0 dBm", 0));
        Title_RFBurst_DelayOn->setText(QApplication::translate("SA_Dialog_AllSetup", "Trigger Delay", 0));
        value_RFBurst_DelayOn->setText(QApplication::translate("SA_Dialog_AllSetup", "On", 0));
        Title_Limit_Test->setText(QApplication::translate("SA_Dialog_AllSetup", "Limit Test", 0));
        Value_Limit_Test->setText(QApplication::translate("SA_Dialog_AllSetup", "Off", 0));
        pb_nextPage_2->setText(QString());
        Title_NoiseMarker->setText(QApplication::translate("SA_Dialog_AllSetup", "Noise Marker", 0));
        btn_NoiseMarker->setText(QApplication::translate("SA_Dialog_AllSetup", "Off", 0));
        Title_MarkerTable_2->setText(QApplication::translate("SA_Dialog_AllSetup", "Limit Edge", 0));
        value_Limit_Edge_Toggle->setText(QApplication::translate("SA_Dialog_AllSetup", "Off", 0));
        Title_ChannelType_2->setText(QApplication::translate("SA_Dialog_AllSetup", "Limit Type", 0));
        btn_Upper->setText(QApplication::translate("SA_Dialog_AllSetup", "Upper", 0));
        btn_Upper->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "left", 0)));
        btn_Lower->setText(QApplication::translate("SA_Dialog_AllSetup", "Lower", 0));
        btn_Lower->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "right", 0)));
        Title_Limit_Edge->setText(QApplication::translate("SA_Dialog_AllSetup", "Limit Edge", 0));
        Value_Limit_Edge->setText(QApplication::translate("SA_Dialog_AllSetup", "0.0 dBm", 0));
        Value_Limit_Edge->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        pb_prePage_2->setText(QString());
        Title_Limit_Toggle->setText(QApplication::translate("SA_Dialog_AllSetup", "Limit Line", 0));
        Value_Limit_Toggle->setText(QApplication::translate("SA_Dialog_AllSetup", "Off", 0));
        Title_Marker->setText(QApplication::translate("SA_Dialog_AllSetup", "Marker", 0));
        Title_LimitSelect->setText(QApplication::translate("SA_Dialog_AllSetup", "Select Limit", 0));
        value_LimitSelect->clear();
        value_LimitSelect->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_AllSetup", "Limit1", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "Limit2", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "Limit3", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "Limit4", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "Limit5", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "Limit6", 0)
        );
        Title_FreqCount->setText(QApplication::translate("SA_Dialog_AllSetup", "Frequency Count", 0));
        btn_FreqCount->setText(QApplication::translate("SA_Dialog_AllSetup", "Off", 0));
        Title_MarkerType->setText(QApplication::translate("SA_Dialog_AllSetup", "Marker Type", 0));
        Marker_Normal->setText(QApplication::translate("SA_Dialog_AllSetup", "Normal", 0));
        Marker_Normal->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "left", 0)));
        Marker_Delta->setText(QApplication::translate("SA_Dialog_AllSetup", "Delta", 0));
        Marker_Delta->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "right", 0)));
        Title_Limit->setText(QApplication::translate("SA_Dialog_AllSetup", "Limit", 0));
        Title_MarkerView->setText(QApplication::translate("SA_Dialog_AllSetup", "Marker View", 0));
        btn_MarkerView->setText(QApplication::translate("SA_Dialog_AllSetup", "Off", 0));
        Title_MarkerSelect->setText(QApplication::translate("SA_Dialog_AllSetup", "Select Marker", 0));
        value_MarkerSelect->clear();
        value_MarkerSelect->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_AllSetup", "M1", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "M2", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "M3", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "M4", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "M5", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "M6", 0)
        );
        line_7->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        line_8->setProperty("style", QVariant(QApplication::translate("SA_Dialog_AllSetup", "1", 0)));
        Title_MarkerView_AllOn->setText(QApplication::translate("SA_Dialog_AllSetup", "Marker All On", 0));
        pb_MkrAllOn->setText(QString());
        Title_MarkerTo->setText(QApplication::translate("SA_Dialog_AllSetup", "Marker To", 0));
        value_MarkerTo->clear();
        value_MarkerTo->insertItems(0, QStringList()
         << QApplication::translate("SA_Dialog_AllSetup", "Start", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "Center", 0)
         << QApplication::translate("SA_Dialog_AllSetup", "Stop", 0)
        );
        Title_Limit_AllClear->setText(QApplication::translate("SA_Dialog_AllSetup", "Delete All Limits", 0));
        pb_LimitAllDelete->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SA_Dialog_AllSetup: public Ui_SA_Dialog_AllSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_ALLSETUP_H
