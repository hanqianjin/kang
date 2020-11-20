/********************************************************************************
** Form generated from reading UI file 'sa_dialog_quicksave.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_QUICKSAVE_H
#define UI_SA_DIALOG_QUICKSAVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <sa_lineedit.h>
#include "sa_dialog_virtualkeyboard.h"

QT_BEGIN_NAMESPACE

class Ui_SA_Dialog_QuickSave
{
public:
    QWidget *widget;
    SA_Dialog_VirtualKeyboard *widget_2;
    QWidget *inputBox;
    QPushButton *pb_clear;
    SA_LineEdit *inputEdit;
    QPushButton *pb_cancel;
    QPushButton *pb_ok;
    QPushButton *pb_Cancel;

    void setupUi(QDialog *SA_Dialog_QuickSave)
    {
        if (SA_Dialog_QuickSave->objectName().isEmpty())
            SA_Dialog_QuickSave->setObjectName(QStringLiteral("SA_Dialog_QuickSave"));
        SA_Dialog_QuickSave->resize(1010, 490);
        SA_Dialog_QuickSave->setStyleSheet(QStringLiteral(""));
        widget = new QWidget(SA_Dialog_QuickSave);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 1010, 490));
        widget->setStyleSheet(QLatin1String("/***********************indoor****************************/\n"
"#SA_Dialog_QuickSave[status = \"indoor\"] #widget\n"
"{\n"
"background-color: rgb(255, 255, 255);\n"
"}\n"
"#SA_Dialog_QuickSave[status = \"indoor\"] #inputBox\n"
"{\n"
"background-color: rgb(0, 0, 0);\n"
"}\n"
"#SA_Dialog_QuickSave[status = \"indoor\"] #inputBox>QLineEdit{\n"
"	font:75 26px \"Arial\";\n"
"	font-weight:bold;\n"
"	padding-left:4px;\n"
"	background-color:rgb(0,0,0);\n"
"	color: rgb(238, 183, 37);\n"
"	border-style:flat;\n"
"}\n"
"#SA_Dialog_QuickSave[status = \"indoor\"] #inputBox>QPushButton\n"
"{\n"
"	color:rgba(0,0,0,0);\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/KeyBoard/btn_clear_w100_nor.png);\n"
"}\n"
"#SA_Dialog_QuickSave[status = \"indoor\"] #inputBox>QPushButton::pressed\n"
"{\n"
"	\n"
"	background-image: url(:/sa/image/KeyBoard/btn_clear_w100_click.png);\n"
"}\n"
"/***********************outdoor****************************/\n"
"#SA_Dialog_QuickSave[status = \"outdoor\"] #widget\n"
"{\n"
"background-colo"
                        "r: rgb(255, 255, 255);\n"
"}\n"
"#SA_Dialog_QuickSave[status = \"outdoor\"] #inputBox\n"
"{\n"
"background-color: rgb(0, 0, 0);\n"
"}\n"
"#SA_Dialog_QuickSave[status = \"outdoor\"] #inputBox>QLineEdit{\n"
"	font:75 26px \"Arial\";\n"
"	font-weight:bold;\n"
"	padding-left:4px;\n"
"	background-color:rgb(0,0,0);\n"
"	color: rgb(238, 183, 37);\n"
"	border-style:flat;\n"
"}\n"
"#SA_Dialog_QuickSave[status = \"outdoor\"] #inputBox>QPushButton\n"
"{\n"
"	color:rgba(0,0,0,0);\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/KeyBoard/btn_clear_w100_nor.png);\n"
"}\n"
"#SA_Dialog_QuickSave[status = \"outdoor\"] #inputBox>QPushButton::pressed\n"
"{\n"
"	\n"
"	background-image: url(:/sa/image/KeyBoard/btn_clear_w100_click.png);\n"
"}\n"
"/***********************night****************************/\n"
"#SA_Dialog_QuickSave[status = \"night\"] #widget\n"
"{\n"
"background-color: rgb(0, 0, 0);\n"
"}\n"
"#SA_Dialog_QuickSave[status = \"night\"] #inputBox\n"
"{\n"
"	background-color: rgb(40, 34, 26);\n"
"	border: 1p"
                        "x solid rgba(147,128,98,1);\n"
"}\n"
"#SA_Dialog_QuickSave[status = \"night\"] #inputBox>QLineEdit{\n"
"	font:75 26px \"Arial\";\n"
"	font-weight:bold;\n"
"	padding-left:4px;\n"
"	background-color: rgb(40, 34, 26);\n"
"	color:rgba(231,149,20,1);\n"
"	border-style:flat;\n"
"}\n"
"#SA_Dialog_QuickSave[status = \"night\"] #inputBox>QPushButton\n"
"{\n"
"	background-color:rgba(228,199,151,1);\n"
"	font:75 16px \"Arial\";\n"
"	font-weight:bold;\n"
"	border-style:flat;\n"
"}\n"
"#SA_Dialog_QuickSave[status = \"night\"] #inputBox>QPushButton::pressed\n"
"{\n"
"	\n"
"	border-image: url(:/sa/image/night/btn_w70_click.png);\n"
"	/*background-image: url(:/sa/image/KeyBoard/btn_clear_w100_click.png);*/\n"
"}"));
        widget_2 = new SA_Dialog_VirtualKeyboard(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(30, 100, 950, 290));
        inputBox = new QWidget(widget);
        inputBox->setObjectName(QStringLiteral("inputBox"));
        inputBox->setGeometry(QRect(260, 20, 490, 50));
        inputBox->setStyleSheet(QStringLiteral(""));
        pb_clear = new QPushButton(inputBox);
        pb_clear->setObjectName(QStringLiteral("pb_clear"));
        pb_clear->setGeometry(QRect(387, 3, 100, 44));
        pb_clear->setStyleSheet(QStringLiteral(""));
        inputEdit = new SA_LineEdit(inputBox);
        inputEdit->setObjectName(QStringLiteral("inputEdit"));
        inputEdit->setGeometry(QRect(1, 1, 378, 48));
        inputEdit->setStyleSheet(QStringLiteral(""));
        inputEdit->setMaxLength(20);
        inputEdit->setReadOnly(false);
        pb_cancel = new QPushButton(widget);
        pb_cancel->setObjectName(QStringLiteral("pb_cancel"));
        pb_cancel->setGeometry(QRect(818, 430, 80, 30));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        pb_cancel->setFont(font);
        pb_cancel->setFocusPolicy(Qt::NoFocus);
        pb_cancel->setStyleSheet(QLatin1String("\n"
"#SA_Dialog_QuickSave[status=\"indoor\"] QPushButton\n"
"{\n"
"	border-style: flat;\n"
"	color:rgba(0,0,0,0);\n"
"	background-image: url(:/sa/image/btn_cancel_w80_nor.png);\n"
"}\n"
"#SA_Dialog_QuickSave[status=\"indoor\"] QPushButton:pressed\n"
"{	\n"
"	color:rgba(0,0,0,0);\n"
"	background-image: url(:/sa/image/btn_cancel_w80_click.png);\n"
"}\n"
"#SA_Dialog_QuickSave[status=\"outdoor\"] QPushButton\n"
"{\n"
"	border-style: flat;\n"
"	color:rgba(0,0,0,0);\n"
"	background-image: url(:/sa/image/btn_cancel_w80_nor.png);\n"
"}\n"
"#SA_Dialog_QuickSave[status=\"outdoor\"] QPushButton:pressed\n"
"{	\n"
"	color:rgba(0,0,0,0);\n"
"	background-image: url(:/sa/image/btn_cancel_w80_click.png);\n"
"}\n"
"#SA_Dialog_QuickSave[status=\"night\"] QPushButton\n"
"{\n"
"  color:rgba(251, 219, 167, 1);\n"
"  font:75 13px \"Arial\";\n"
"/*  padding-left:20px;\n"
"  padding-top:3px;*/\n"
"  border-style: flat;\n"
"  border-image: url(:/sa/image/night/btn_w70_normal.png);\n"
"}\n"
"#SA_Dialog_QuickSave[status=\"night\"] QPushB"
                        "utton:pressed\n"
"{	\n"
"  color:rgba(251, 219, 167, 1);\n"
"  border-image: url(:/sa/image/night/btn_w70_click.png);\n"
"}"));
        pb_cancel->setFlat(true);
        pb_ok = new QPushButton(widget);
        pb_ok->setObjectName(QStringLiteral("pb_ok"));
        pb_ok->setGeometry(QRect(900, 430, 80, 30));
        pb_ok->setFont(font);
        pb_ok->setFocusPolicy(Qt::NoFocus);
        pb_ok->setLayoutDirection(Qt::LeftToRight);
        pb_ok->setStyleSheet(QLatin1String("#SA_Dialog_QuickSave[status=\"indoor\"] QPushButton\n"
"{\n"
"	border-style: flat;\n"
"	color:rgba(0,0,0,0);\n"
"	background-image: url(:/sa/image/btn_ok_w80_nor.png);\n"
"}\n"
"#SA_Dialog_QuickSave[status=\"indoor\"] QPushButton:pressed\n"
"{	\n"
"	color:rgba(0,0,0,0);\n"
"	background-image: url(:/sa/image/btn_ok_w80_click.png);\n"
"}\n"
"#SA_Dialog_QuickSave[status=\"outdoor\"] QPushButton\n"
"{\n"
"	border-style: flat;\n"
"	color:rgba(0,0,0,0);\n"
"	background-image: url(:/sa/image/btn_ok_w80_nor.png);\n"
"}\n"
"#SA_Dialog_QuickSave[status=\"outdoor\"] QPushButton:pressed\n"
"{	\n"
"	color:rgba(0,0,0,0);\n"
"	background-image: url(:/sa/image/btn_ok_w80_click.png);\n"
"}\n"
"#SA_Dialog_QuickSave[status=\"night\"] QPushButton\n"
"{\n"
"	color:rgba(251, 219, 167, 1);\n"
"  font:75 13px \"Arial\";\n"
"/*  padding-left:20px;\n"
"  padding-top:3px;*/\n"
"  border-style: flat;\n"
"  border-image: url(:/sa/image/night/btn_ok_w80_nor.png);\n"
"}\n"
"#SA_Dialog_QuickSave[status=\"night\"] QPushButton:pressed\n"
"{	\n"
""
                        "  color:rgba(251, 219, 167, 1);\n"
"  border-image: url(:/sa/image/night/btn_w70_click.png);\n"
"}"));
        pb_ok->setFlat(true);
        pb_Cancel = new QPushButton(widget);
        pb_Cancel->setObjectName(QStringLiteral("pb_Cancel"));
        pb_Cancel->setGeometry(QRect(945, 15, 35, 35));
        pb_Cancel->setStyleSheet(QLatin1String("#SA_Dialog_QuickSave[status = \"indoor\"] QPushButton\n"
"{\n"
"border-style:flat;\n"
"border-image: url(:/sa/image/KeyBoard/btn_close_r35_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_QuickSave[status = \"indoor\"] QPushButton::pressed\n"
"{\n"
"	border-image: url(:/sa/image/KeyBoard/btn_close_r35_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_QuickSave[status = \"outdoor\"] QPushButton\n"
"{\n"
"border-style:flat;\n"
"border-image: url(:/sa/image/KeyBoard/btn_close_r35_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_QuickSave[status = \"outdoor\"] QPushButton::pressed\n"
"{\n"
"	border-image: url(:/sa/image/KeyBoard/btn_close_r35_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_QuickSave[status = \"night\"] QPushButton\n"
"{\n"
"border-style:flat;\n"
"border-image: url(:/sa/image/night/btn_close_normal.png);\n"
"\n"
"}\n"
"\n"
"#SA_Dialog_QuickSave[status = \"night\"] QPushButton::pressed\n"
"{\n"
"border-image: url(:/sa/image/night/btn_close_click.png);\n"
"}\n"
""));

        retranslateUi(SA_Dialog_QuickSave);

        QMetaObject::connectSlotsByName(SA_Dialog_QuickSave);
    } // setupUi

    void retranslateUi(QDialog *SA_Dialog_QuickSave)
    {
        SA_Dialog_QuickSave->setWindowTitle(QApplication::translate("SA_Dialog_QuickSave", "Dialog", 0));
        SA_Dialog_QuickSave->setProperty("status", QVariant(QApplication::translate("SA_Dialog_QuickSave", "night", 0)));
        pb_clear->setText(QApplication::translate("SA_Dialog_QuickSave", "Clear", 0));
        inputEdit->setText(QApplication::translate("SA_Dialog_QuickSave", "Trace_0000.png", 0));
        pb_cancel->setText(QApplication::translate("SA_Dialog_QuickSave", "Cancel", 0));
        pb_ok->setText(QApplication::translate("SA_Dialog_QuickSave", "OK", 0));
        pb_Cancel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SA_Dialog_QuickSave: public Ui_SA_Dialog_QuickSave {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_QUICKSAVE_H
