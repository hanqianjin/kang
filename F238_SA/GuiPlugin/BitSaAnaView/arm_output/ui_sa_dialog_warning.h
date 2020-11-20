/********************************************************************************
** Form generated from reading UI file 'sa_dialog_warning.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_WARNING_H
#define UI_SA_DIALOG_WARNING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SA_Dialog_Warning
{
public:
    QWidget *widget;
    QDialogButtonBox *buttonBox;
    QLabel *Title;
    QLabel *Warning;
    QLabel *label;

    void setupUi(QWidget *SA_Dialog_Warning)
    {
        if (SA_Dialog_Warning->objectName().isEmpty())
            SA_Dialog_Warning->setObjectName(QStringLiteral("SA_Dialog_Warning"));
        SA_Dialog_Warning->resize(550, 170);
        SA_Dialog_Warning->setStyleSheet(QLatin1String("/******************indoor********************/\n"
"#BitSA[status=\"indoor\"] #widget\n"
"{\n"
"	background-color:rgba(245,245,245,1);\n"
"	border:1px solid rgba(151,151,151,1);\n"
"}\n"
"\n"
"#BitSA[status=\"indoor\"] #label\n"
"{\n"
"	background-image: url(:/sa/image/notice.png);\n"
"}\n"
"#BitSA[status=\"indoor\"] #pb_ok\n"
"{\n"
"	color:rgba(0,0,0,0);\n"
"	height:30px;\n"
"	width:80px;\n"
"	border-style: flat;\n"
"	background-image: url(:/sa/image/btn_ok_w80_nor.png);\n"
"}\n"
"#BitSA[status=\"indoor\"] #pb_ok:pressed\n"
"{\n"
"	color:rgba(0,0,0,0);\n"
"	background-image: url(:/sa/image/btn_ok_w80_click.png);\n"
"}\n"
"\n"
"#BitSA[status=\"indoor\"] #pb_cancel\n"
"{\n"
"	color:rgba(0,0,0,0);\n"
"	height:30px;\n"
"	width:80px;\n"
"	border-style: flat;\n"
"	border-image: url(:/sa/image/btn_cancel_w80_nor.png);\n"
"}\n"
"#BitSA[status=\"indoor\"] #pb_cancel:pressed\n"
"{\n"
"	color:rgba(0,0,0,0);\n"
"	border-image: url(:/sa/image/btn_cancel_w80_click.png);\n"
"}\n"
"\n"
"/******************outdoor*************"
                        "******/\n"
"#BitSA[status=\"outdoor\"] #widget\n"
"{\n"
"	background-color:rgba(245,245,245,1);\n"
"	border:1px solid rgba(151,151,151,1);\n"
"}\n"
"\n"
"#BitSA[status=\"outdoor\"] #label\n"
"{\n"
"	background-image: url(:/sa/image/notice.png);\n"
"}\n"
"#BitSA[status=\"outdoor\"] #pb_ok\n"
"{\n"
"	color:rgba(0,0,0,0);\n"
"	height:30px;\n"
"	width:80px;\n"
"	border-style: flat;\n"
"	background-image: url(:/sa/image/btn_ok_w80_nor.png);\n"
"}\n"
"#BitSA[status=\"outdoor\"] #pb_ok:pressed\n"
"{\n"
"	color:rgba(0,0,0,0);\n"
"	background-image: url(:/sa/image/btn_ok_w80_click.png);\n"
"}\n"
"\n"
"#BitSA[status=\"outdoor\"] #pb_cancel\n"
"{\n"
"	color:rgba(0,0,0,0);\n"
"	height:30px;\n"
"	width:80px;\n"
"	border-style: flat;\n"
"	border-image: url(:/sa/image/btn_cancel_w80_nor.png);\n"
"}\n"
"#BitSA[status=\"outdoor\"] #pb_cancel:pressed\n"
"{\n"
"	color:rgba(0,0,0,0);\n"
"	border-image: url(:/sa/image/btn_cancel_w80_click.png);\n"
"}\n"
"/*****************night*********************/\n"
"#BitSA[status=\"night\"] #w"
                        "idget\n"
"{\n"
"	background-color:rgba(241,210,160,1);\n"
"	border:1px solid rgba(151,151,151,1);\n"
"}\n"
"\n"
"#BitSA[status=\"night\"] #label\n"
"{\n"
"	border-image: url(:/sa/image/night/notice.png);\n"
"}\n"
"#BitSA[status=\"night\"] #pb_ok\n"
"{\n"
"	font:\"Arial\";\n"
"	color:rgba(241, 210, 160, 1);\n"
"	height:30px;\n"
"	width:80px;\n"
"	border-style: flat;\n"
"	border-image: url(:/sa/image/night/btn_ok_w80_nor.png);\n"
"}\n"
"#BitSA[status=\"night\"] #pb_ok:pressed\n"
"{\n"
"	color:rgba(241, 210, 160, 1);\n"
"	border-image: url(:/sa/image/night/btn_w70_click.png);\n"
"}\n"
"\n"
"#BitSA[status=\"night\"] #pb_cancel\n"
"{\n"
"	font:\"Arial\";\n"
"	color:rgba(241, 210, 160, 1);\n"
"	height:30px;\n"
"	width:80px;\n"
"	border-style: flat;\n"
"\n"
"	border-image: url(:/sa/image/night/btn_w70_normal.png);;\n"
"}\n"
"#BitSA[status=\"night\"] #pb_cancel:pressed\n"
"{\n"
"	color:rgba(241, 210, 160, 1);\n"
"	border-image: url(:/sa/image/night/btn_w70_click.png);\n"
"}"));
        widget = new QWidget(SA_Dialog_Warning);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 550, 170));
        buttonBox = new QDialogButtonBox(widget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(349, 110, 164, 32));
        buttonBox->setStyleSheet(QStringLiteral(""));
        Title = new QLabel(widget);
        Title->setObjectName(QStringLiteral("Title"));
        Title->setGeometry(QRect(110, 32, 85, 22));
        Title->setStyleSheet(QLatin1String("font:75 20px \"Arial\";\n"
"font-weight:bold;"));
        Warning = new QLabel(widget);
        Warning->setObjectName(QStringLiteral("Warning"));
        Warning->setGeometry(QRect(110, 65, 420, 22));
        Warning->setStyleSheet(QStringLiteral("font:75 18px \"Arial\";"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(34, 29, 60, 60));
        label->setStyleSheet(QStringLiteral(""));

        retranslateUi(SA_Dialog_Warning);

        QMetaObject::connectSlotsByName(SA_Dialog_Warning);
    } // setupUi

    void retranslateUi(QWidget *SA_Dialog_Warning)
    {
        SA_Dialog_Warning->setWindowTitle(QApplication::translate("SA_Dialog_Warning", "Form", 0));
        Title->setText(QApplication::translate("SA_Dialog_Warning", "Notice", 0));
        Warning->setText(QApplication::translate("SA_Dialog_Warning", "Are you sure to clean all?", 0));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SA_Dialog_Warning: public Ui_SA_Dialog_Warning {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_WARNING_H
