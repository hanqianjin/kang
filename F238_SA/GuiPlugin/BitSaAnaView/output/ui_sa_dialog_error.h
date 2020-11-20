/********************************************************************************
** Form generated from reading UI file 'sa_dialog_error.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_ERROR_H
#define UI_SA_DIALOG_ERROR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SA_Dialog_Error
{
public:
    QWidget *widget;
    QLabel *Title;
    QLabel *Warning;
    QLabel *label;
    QPushButton *pb_ok;

    void setupUi(QDialog *SA_Dialog_Error)
    {
        if (SA_Dialog_Error->objectName().isEmpty())
            SA_Dialog_Error->setObjectName(QStringLiteral("SA_Dialog_Error"));
        SA_Dialog_Error->resize(550, 170);
        SA_Dialog_Error->setStyleSheet(QLatin1String("/*****************indoor****************/\n"
"#BitSA[status=\"indoor\"] #widget\n"
"{\n"
"	background-color:rgb(245,245,245);\n"
"	border:1px solid rgb(151,151,151);\n"
"}\n"
"\n"
"#BitSA[status=\"indoor\"] #label\n"
"{\n"
"	background-image: url(:/sa/image/error.png);\n"
"}\n"
"#BitSA[status=\"indoor\"] QPushButton\n"
"{\n"
"	color:rgba(0,0,0,0);\n"
"	border-style: flat;\n"
"	background-image: url(:/sa/image/btn_ok_w80_nor.png);\n"
"}\n"
"#BitSA[status=\"indoor\"] QPushButton:pressed\n"
"{	\n"
"	color:rgba(0,0,0,0);\n"
"	background-image: url(:/sa/image/btn_ok_w80_click.png);\n"
"}\n"
"/*****************outdoor****************/\n"
"#BitSA[status=\"outdoor\"] #widget\n"
"{\n"
"	color:rgba(0,0,0,0);\n"
"	background-color:rgb(245,245,245);\n"
"	border:1px solid rgb(151,151,151);\n"
"}\n"
"\n"
"#BitSA[status=\"outdoor\"] #label\n"
"{\n"
"	background-image: url(:/sa/image/error.png);\n"
"}\n"
"#BitSA[status=\"outdoor\"] QPushButton\n"
"{\n"
"	color:rgba(0,0,0,0);\n"
"	border-style: flat;\n"
"	background-image: url"
                        "(:/sa/image/btn_ok_w80_nor.png);\n"
"}\n"
"#BitSA[status=\"outdoor\"] QPushButton:pressed\n"
"{	\n"
"	color:rgba(0,0,0,0);\n"
"	background-image: url(:/sa/image/btn_ok_w80_click.png);\n"
"}\n"
"/*****************night****************/\n"
"#BitSA[status=\"night\"] #widget\n"
"{\n"
"	background-color:rgb(241,210,160);\n"
"	border:1px solid rgb(151,151,151);\n"
"}\n"
"\n"
"#BitSA[status=\"night\"] #label\n"
"{\n"
"	background-image: url(:/sa/image/night/error.png);\n"
"}\n"
"#BitSA[status=\"night\"] QPushButton\n"
"{\n"
"	font:\"Arial\";\n"
"	color:rgba(241, 210, 160, 1);\n"
"	border-style: flat;\n"
"	border-image:  url(:/sa/image/night/btn_ok_w80_nor.png);\n"
"}\n"
"#BitSA[status=\"night\"] QPushButton:pressed\n"
"{	\n"
"	color:rgba(241, 210, 160, 1);\n"
"	border-image: url(:/sa/image/night/btn_w70_click.png);\n"
"}"));
        widget = new QWidget(SA_Dialog_Error);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 550, 170));
        Title = new QLabel(widget);
        Title->setObjectName(QStringLiteral("Title"));
        Title->setGeometry(QRect(110, 32, 85, 22));
        Title->setStyleSheet(QLatin1String("font:75 20px \"Arial\";\n"
"font-weight:bold;"));
        Warning = new QLabel(widget);
        Warning->setObjectName(QStringLiteral("Warning"));
        Warning->setGeometry(QRect(110, 65, 360, 44));
        Warning->setStyleSheet(QStringLiteral("font:75 18px \"Arial\";"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(34, 29, 60, 60));
        label->setStyleSheet(QStringLiteral(""));
        pb_ok = new QPushButton(widget);
        pb_ok->setObjectName(QStringLiteral("pb_ok"));
        pb_ok->setGeometry(QRect(430, 110, 80, 30));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(13);
        pb_ok->setFont(font);
        pb_ok->setLayoutDirection(Qt::LeftToRight);
        pb_ok->setStyleSheet(QStringLiteral(""));
        pb_ok->setFlat(true);

        retranslateUi(SA_Dialog_Error);

        QMetaObject::connectSlotsByName(SA_Dialog_Error);
    } // setupUi

    void retranslateUi(QDialog *SA_Dialog_Error)
    {
        SA_Dialog_Error->setWindowTitle(QApplication::translate("SA_Dialog_Error", "Dialog", Q_NULLPTR));
        Title->setText(QApplication::translate("SA_Dialog_Error", "Notice", Q_NULLPTR));
        Warning->setText(QApplication::translate("SA_Dialog_Error", "Are you sure to clean all?\n"
"okok", Q_NULLPTR));
        label->setText(QString());
        pb_ok->setText(QApplication::translate("SA_Dialog_Error", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SA_Dialog_Error: public Ui_SA_Dialog_Error {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_ERROR_H
