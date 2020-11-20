/********************************************************************************
** Form generated from reading UI file 'sa_dialog_measuresetup.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_MEASURESETUP_H
#define UI_SA_DIALOG_MEASURESETUP_H

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

class Ui_SA_Dialog_MeasureSetup
{
public:
    QWidget *widget;
    QPushButton *pb_SpuriousEmssionMask;
    QPushButton *pb_Adjacent;
    QPushButton *pb_AudioDemodulation;
    QPushButton *pb_SpecEmissionMask;
    QPushButton *pb_FieldStrength;
    QPushButton *pb_Muti_Adjacent;
    QPushButton *pb_OccupiedBW;
    QFrame *line;
    QPushButton *pb_Spectrum;
    QLabel *lblTitle;
    QPushButton *pb_ChannelPower;
    QPushButton *pb_cancel;

    void setupUi(QWidget *SA_Dialog_MeasureSetup)
    {
        if (SA_Dialog_MeasureSetup->objectName().isEmpty())
            SA_Dialog_MeasureSetup->setObjectName(QStringLiteral("SA_Dialog_MeasureSetup"));
        SA_Dialog_MeasureSetup->resize(252, 646);
        SA_Dialog_MeasureSetup->setAutoFillBackground(false);
        SA_Dialog_MeasureSetup->setStyleSheet(QLatin1String("QPushButton:disabled\n"
"{\n"
"	color:rgb(100, 100, 100);\n"
"}\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_MeasureSetup[status  =  \"indoor\"] #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"indoor\"] QLabel\n"
"{\n"
"	color:rgb(9, 73, 108);\n"
"	background-color:rgba(0,0,0,0);\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	border-style:flat;\n"
"	text-align:left;\n"
"	padding-left:10px;\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"indoor\"] QPushButton::!checked\n"
"{\n"
"	font: 13px \"Arial\";\n"
"	font-weight:normal;\n"
"	background-color: rgba(237, 212, 0,0);\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"indoor\"] QPushButton::checked\n"
"{\n"
"font: 75 13px \"Arial\";\n"
"font-weight:bold;\n"
"background-color: rgb(255,181,0);\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"indoor\"] #lblTitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	l"
                        "ine-height:23px;\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"indoor\"] #pb_cancel\n"
"{\n"
"border-style:flat;\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"indoor\"] #pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"indoor\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_MeasureSetup[status  =  \"outdoor\"] #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"outdoor\"] QLabel\n"
"{\n"
"	color:rgb(9, 73, 108);\n"
"	background-color:rgba(0,0,0,0);\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	border-style:flat;\n"
"	text-align:left;\n"
"	padding-left:10px;\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"outdoor\"] QPushBut"
                        "ton::!checked\n"
"{\n"
"	font: 13px \"Arial\";\n"
"	font-weight:normal;\n"
"	background-color: rgba(237, 212, 0,0);\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"outdoor\"] QPushButton::checked\n"
"{\n"
"font: 75 13px \"Arial\";\n"
"font-weight:bold;\n"
"background-color: rgb(255,181,0);\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"outdoor\"] #lblTitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"outdoor\"] #pb_cancel\n"
"{\n"
"border-style:flat;\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"outdoor\"] #pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"outdoor\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"/*******************night**********************/\n"
"#SA_Dialog_MeasureSetup[status"
                        "  =  \"night\"] #widget\n"
"{\n"
"	background-color:rgba(208,182,139,0.9);\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"night\"] QLabel\n"
"{\n"
"	color:rgb(9, 73, 108);\n"
"	background-color:rgba(0,0,0,0);\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"night\"] QPushButton\n"
"{\n"
"	border-style:flat;\n"
"	text-align:left;\n"
"	padding-left:10px;\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"night\"] QPushButton::!checked\n"
"{\n"
"	font: 13px \"Arial\";\n"
"	font-weight:normal;\n"
"	background-color: rgba(237, 212, 0,0);\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"night\"] QPushButton::checked\n"
"{\n"
"font: 75 13px \"Arial\";\n"
"font-weight:bold;\n"
"background-color:rgba(251,155,0,1);\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"night\"] #lblTitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"night\"] #pb_cancel\n"
"{\n"
"border-style:flat;\n"
"background-"
                        "color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/night/btn_close_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"night\"] #pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/night/btn_close_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_MeasureSetup[status  =  \"night\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}"));
        widget = new QWidget(SA_Dialog_MeasureSetup);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 252, 646));
        pb_SpuriousEmssionMask = new QPushButton(widget);
        pb_SpuriousEmssionMask->setObjectName(QStringLiteral("pb_SpuriousEmssionMask"));
        pb_SpuriousEmssionMask->setEnabled(true);
        pb_SpuriousEmssionMask->setGeometry(QRect(8, 338, 234, 45));
        pb_SpuriousEmssionMask->setCheckable(true);
        pb_SpuriousEmssionMask->setAutoExclusive(true);
        pb_Adjacent = new QPushButton(widget);
        pb_Adjacent->setObjectName(QStringLiteral("pb_Adjacent"));
        pb_Adjacent->setEnabled(true);
        pb_Adjacent->setGeometry(QRect(8, 246, 234, 45));
        pb_Adjacent->setCheckable(true);
        pb_Adjacent->setAutoExclusive(true);
        pb_AudioDemodulation = new QPushButton(widget);
        pb_AudioDemodulation->setObjectName(QStringLiteral("pb_AudioDemodulation"));
        pb_AudioDemodulation->setEnabled(false);
        pb_AudioDemodulation->setGeometry(QRect(8, 430, 234, 45));
        pb_AudioDemodulation->setStyleSheet(QLatin1String("QPushButton:disabled\n"
"{\n"
"	color:rgb(100, 100, 100);\n"
"}"));
        pb_AudioDemodulation->setCheckable(true);
        pb_AudioDemodulation->setAutoExclusive(true);
        pb_SpecEmissionMask = new QPushButton(widget);
        pb_SpecEmissionMask->setObjectName(QStringLiteral("pb_SpecEmissionMask"));
        pb_SpecEmissionMask->setEnabled(true);
        pb_SpecEmissionMask->setGeometry(QRect(8, 292, 234, 45));
        pb_SpecEmissionMask->setCheckable(true);
        pb_SpecEmissionMask->setAutoExclusive(true);
        pb_FieldStrength = new QPushButton(widget);
        pb_FieldStrength->setObjectName(QStringLiteral("pb_FieldStrength"));
        pb_FieldStrength->setEnabled(false);
        pb_FieldStrength->setGeometry(QRect(8, 384, 234, 45));
        pb_FieldStrength->setStyleSheet(QLatin1String("QPushButton:disabled\n"
"{\n"
"	color:rgb(100, 100, 100);\n"
"}"));
        pb_FieldStrength->setCheckable(true);
        pb_FieldStrength->setAutoExclusive(true);
        pb_Muti_Adjacent = new QPushButton(widget);
        pb_Muti_Adjacent->setObjectName(QStringLiteral("pb_Muti_Adjacent"));
        pb_Muti_Adjacent->setEnabled(true);
        pb_Muti_Adjacent->setGeometry(QRect(8, 200, 234, 45));
        pb_Muti_Adjacent->setCheckable(true);
        pb_Muti_Adjacent->setAutoExclusive(true);
        pb_OccupiedBW = new QPushButton(widget);
        pb_OccupiedBW->setObjectName(QStringLiteral("pb_OccupiedBW"));
        pb_OccupiedBW->setEnabled(true);
        pb_OccupiedBW->setGeometry(QRect(8, 154, 234, 45));
        pb_OccupiedBW->setCheckable(true);
        pb_OccupiedBW->setAutoExclusive(true);
        line = new QFrame(widget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(18, 46, 212, 2));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        pb_Spectrum = new QPushButton(widget);
        pb_Spectrum->setObjectName(QStringLiteral("pb_Spectrum"));
        pb_Spectrum->setGeometry(QRect(8, 62, 234, 45));
        pb_Spectrum->setCheckable(true);
        pb_Spectrum->setChecked(false);
        pb_Spectrum->setAutoExclusive(true);
        lblTitle = new QLabel(widget);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));
        lblTitle->setGeometry(QRect(17, 19, 98, 22));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        lblTitle->setFont(font);
        lblTitle->setStyleSheet(QStringLiteral(""));
        pb_ChannelPower = new QPushButton(widget);
        pb_ChannelPower->setObjectName(QStringLiteral("pb_ChannelPower"));
        pb_ChannelPower->setEnabled(true);
        pb_ChannelPower->setGeometry(QRect(8, 108, 234, 45));
        pb_ChannelPower->setCheckable(true);
        pb_ChannelPower->setAutoExclusive(true);
        pb_cancel = new QPushButton(widget);
        pb_cancel->setObjectName(QStringLiteral("pb_cancel"));
        pb_cancel->setGeometry(QRect(212, 6, 35, 35));
        pb_cancel->setStyleSheet(QStringLiteral(""));

        retranslateUi(SA_Dialog_MeasureSetup);

        QMetaObject::connectSlotsByName(SA_Dialog_MeasureSetup);
    } // setupUi

    void retranslateUi(QWidget *SA_Dialog_MeasureSetup)
    {
        SA_Dialog_MeasureSetup->setWindowTitle(QApplication::translate("SA_Dialog_MeasureSetup", "Form", 0));
        SA_Dialog_MeasureSetup->setProperty("status", QVariant(QApplication::translate("SA_Dialog_MeasureSetup", "indoor", 0)));
        pb_SpuriousEmssionMask->setText(QApplication::translate("SA_Dialog_MeasureSetup", "Spurious Emission", 0));
        pb_Adjacent->setText(QApplication::translate("SA_Dialog_MeasureSetup", "Multi-Adjacent Channel Power", 0));
        pb_AudioDemodulation->setText(QApplication::translate("SA_Dialog_MeasureSetup", "AM/FM Audio Demodulation", 0));
        pb_SpecEmissionMask->setText(QApplication::translate("SA_Dialog_MeasureSetup", "Spectrum Emission Mask", 0));
        pb_FieldStrength->setText(QApplication::translate("SA_Dialog_MeasureSetup", "Field Strength", 0));
        pb_Muti_Adjacent->setText(QApplication::translate("SA_Dialog_MeasureSetup", "Adjacent Channel Power", 0));
        pb_OccupiedBW->setText(QApplication::translate("SA_Dialog_MeasureSetup", "Occupied BW", 0));
        pb_Spectrum->setText(QApplication::translate("SA_Dialog_MeasureSetup", "Swept SA", 0));
        lblTitle->setText(QApplication::translate("SA_Dialog_MeasureSetup", "Measure", 0));
        pb_ChannelPower->setText(QApplication::translate("SA_Dialog_MeasureSetup", "Channel Power", 0));
        pb_cancel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SA_Dialog_MeasureSetup: public Ui_SA_Dialog_MeasureSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_MEASURESETUP_H
