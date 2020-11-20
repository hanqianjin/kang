/********************************************************************************
** Form generated from reading UI file 'sa_dialog_chnlpowerset.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_CHNLPOWERSET_H
#define UI_SA_DIALOG_CHNLPOWERSET_H

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

class Ui_sa_dialog_chnlpowerset
{
public:
    QWidget *widget;
    QLabel *ltitle;
    QPushButton *pb_cancel_2;
    QFrame *line;
    QLabel *label;
    SA_LineEdit *lineEdit;
    SA_LineEdit *lineEdit_2;
    QLabel *label_2;

    void setupUi(QWidget *sa_dialog_chnlpowerset)
    {
        if (sa_dialog_chnlpowerset->objectName().isEmpty())
            sa_dialog_chnlpowerset->setObjectName(QStringLiteral("sa_dialog_chnlpowerset"));
        sa_dialog_chnlpowerset->resize(252, 646);
        sa_dialog_chnlpowerset->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#sa_dialog_chnlpowerset[status  =  \"indoor\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#sa_dialog_chnlpowerset[status  =  \"indoor\"] #widget>QPushButton\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#sa_dialog_chnlpowerset[status  =  \"indoor\"] #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"\n"
"#sa_dialog_chnlpowerset[status  =  \"indoor\"] #widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"\n"
"#sa_dialog_chnlpowerset[status  =  \"indoor\"] SA_LineEdit,\n"
"#sa_dialog_chnlpowerset[status  =  \"indoor\"] SA_LineEdit:disable\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_chnlpowerset[status  =  \"indoor\"] SA_LineEdit:focus\n"
"{\n"
"	outline: none"
                        ";\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"\n"
"/*******************indoor**********************/\n"
"#sa_dialog_chnlpowerset[status  =  \"outdoor\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#sa_dialog_chnlpowerset[status  =  \"outdoor\"] #widget>QPushButton\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#sa_dialog_chnlpowerset[status  =  \"outdoor\"] #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"\n"
"#sa_dialog_chnlpowerset[status  =  \"outdoor\"] #widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"\n"
"#sa_dialog_chnlpowerset[status  =  \"outdoor\"] SA_LineEdit,\n"
"#sa_dialog_chnlpowerset[status  =  \"outdoor\"] SA_LineEdit:disable\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
""
                        "}\n"
"#sa_dialog_chnlpowerset[status  =  \"outdoor\"] SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#sa_dialog_chnlpowerset[status  =  \"night\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#sa_dialog_chnlpowerset[status  =  \"night\"] #widget>QPushButton\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#sa_dialog_chnlpowerset[status  =  \"night\"] #widget\n"
"{\n"
"	background-color:rgba(208,182,139,0.9);\n"
"}\n"
"\n"
"#sa_dialog_chnlpowerset[status  =  \"night\"] #widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"\n"
"#sa_dialog_chnlpowerset[status  =  \"night\"] SA_LineEdit,\n"
"#sa_dialog_chnlpowerset[status  =  \"night\"] SA_LineEdit:disable\n"
"{\n"
"   background-color: rgba(251,220,167,0.60);\n"
"   color:rgba(159,98,0"
                        ",1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_chnlpowerset[status  =  \"night\"] SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}"));
        widget = new QWidget(sa_dialog_chnlpowerset);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 252, 646));
        ltitle = new QLabel(widget);
        ltitle->setObjectName(QStringLiteral("ltitle"));
        ltitle->setGeometry(QRect(17, 19, 151, 22));
        ltitle->setStyleSheet(QLatin1String("#ltitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}"));
        pb_cancel_2 = new QPushButton(widget);
        pb_cancel_2->setObjectName(QStringLiteral("pb_cancel_2"));
        pb_cancel_2->setGeometry(QRect(212, 6, 35, 35));
        pb_cancel_2->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#sa_dialog_chnlpowerset[status  =  \"indoor\"] QPushButton\n"
"{\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#sa_dialog_chnlpowerset[status  =  \"indoor\"] QPushButton:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#sa_dialog_chnlpowerset[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#sa_dialog_chnlpowerset[status  =  \"outdoor\"] QPushButton:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#sa_dialog_chnlpowerset[status  =  \"night\"] QPushButton\n"
"{\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/night/btn_close_normal.png);\n"
"}\n"
"#sa_dialog_chnlpowerset[status  =  \"night\"] QPushButton:pressed\n"
""
                        "{\n"
"border-image: url(:/sa/image/night/btn_close_click.png);\n"
"}"));
        line = new QFrame(widget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(18, 46, 212, 2));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(18, 70, 75, 30));
        lineEdit = new SA_LineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(100, 70, 140, 30));
        QFont font;
        font.setFamily(QStringLiteral("Liberation Sans"));
        font.setBold(true);
        font.setWeight(75);
        lineEdit->setFont(font);
        lineEdit->setCursorPosition(9);
        lineEdit->setReadOnly(true);
        lineEdit_2 = new SA_LineEdit(widget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(100, 140, 140, 30));
        lineEdit_2->setFont(font);
        lineEdit_2->setCursorPosition(9);
        lineEdit_2->setReadOnly(true);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(18, 140, 75, 30));

        retranslateUi(sa_dialog_chnlpowerset);

        QMetaObject::connectSlotsByName(sa_dialog_chnlpowerset);
    } // setupUi

    void retranslateUi(QWidget *sa_dialog_chnlpowerset)
    {
        sa_dialog_chnlpowerset->setWindowTitle(QApplication::translate("sa_dialog_chnlpowerset", "Form", 0));
        ltitle->setText(QApplication::translate("sa_dialog_chnlpowerset", "Channel Power", 0));
        pb_cancel_2->setText(QString());
        label->setText(QApplication::translate("sa_dialog_chnlpowerset", "Integrated\n"
"Bandwidth", 0));
        lineEdit->setText(QApplication::translate("sa_dialog_chnlpowerset", "3.000 MHz", 0));
        lineEdit_2->setText(QApplication::translate("sa_dialog_chnlpowerset", "3.000 MHz", 0));
        label_2->setText(QApplication::translate("sa_dialog_chnlpowerset", "Channel\n"
"Bandwidth", 0));
    } // retranslateUi

};

namespace Ui {
    class sa_dialog_chnlpowerset: public Ui_sa_dialog_chnlpowerset {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_CHNLPOWERSET_H
