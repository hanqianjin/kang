/********************************************************************************
** Form generated from reading UI file 'sa_dialog_occpdset.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_OCCPDSET_H
#define UI_SA_DIALOG_OCCPDSET_H

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

class Ui_sa_dialog_occpdset
{
public:
    QWidget *widget;
    QLabel *ltitle;
    QPushButton *pb_cancel_2;
    QFrame *line;
    QLabel *label;
    SA_LineEdit *lineEdit;
    SA_LineEdit *lineEdit_1;
    QLabel *label_2;

    void setupUi(QWidget *sa_dialog_occpdset)
    {
        if (sa_dialog_occpdset->objectName().isEmpty())
            sa_dialog_occpdset->setObjectName(QStringLiteral("sa_dialog_occpdset"));
        sa_dialog_occpdset->resize(252, 646);
        sa_dialog_occpdset->setStyleSheet(QLatin1String("\n"
"/*******************indoor**********************/\n"
"#sa_dialog_occpdset[status  =  \"indoor\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#sa_dialog_occpdset[status  =  \"indoor\"] #widget>QPushButton\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#sa_dialog_occpdset[status  =  \"indoor\"] #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#sa_dialog_occpdset[status  =  \"indoor\"] #widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#sa_dialog_occpdset[status  =  \"indoor\"] SA_LineEdit,\n"
"#sa_dialog_occpdset[status  =  \"indoor\"] SA_LineEdit:disable\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_occpdset[status  =  \"indoor\"] SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,"
                        "115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"\n"
"\n"
"/*******************outdoor**********************/\n"
"#sa_dialog_occpdset[status  =  \"outdoor\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#sa_dialog_occpdset[status  =  \"outdoor\"] #widget>QPushButton\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#sa_dialog_occpdset[status  =  \"outdoor\"] #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#sa_dialog_occpdset[status  =  \"outdoor\"] #widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#sa_dialog_occpdset[status  =  \"outdoor\"] SA_LineEdit,\n"
"#sa_dialog_occpdset[status  =  \"outdoor\"] SA_LineEdit:disable\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#sa_dialog_occpdset[status  =  \"outdoor\"] SA_LineEdit"
                        ":focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"\n"
"\n"
"/*******************night**********************/\n"
"#sa_dialog_occpdset[status  =  \"night\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#sa_dialog_occpdset[status  =  \"night\"] #widget>QPushButton\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#sa_dialog_occpdset[status  =  \"night\"] #widget\n"
"{\n"
"	background-color:rgba(208,182,139,0.9);\n"
"}\n"
"#sa_dialog_occpdset[status  =  \"night\"] #widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#sa_dialog_occpdset[status  =  \"night\"] SA_LineEdit,\n"
"#sa_dialog_occpdset[status  =  \"night\"] SA_LineEdit:disable\n"
"{\n"
"	 background-color: rgba(251,220,167,0.60);\n"
"	color:rgba(159,98,0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
""
                        "#sa_dialog_occpdset[status  =  \"night\"] SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}"));
        widget = new QWidget(sa_dialog_occpdset);
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
"#sa_dialog_occpdset[status  =  \"indoor\"] QPushButton\n"
"{\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#sa_dialog_occpdset[status  =  \"indoor\"] QPushButton:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#sa_dialog_occpdset[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#sa_dialog_occpdset[status  =  \"outdoor\"] QPushButton:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#sa_dialog_occpdset[status  =  \"night\"] QPushButton\n"
"{\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/night/btn_close_normal.png);\n"
"}\n"
"#sa_dialog_occpdset[status  =  \"night\"] QPushButton:pressed\n"
"{\n"
"border-image: url"
                        "(:/sa/image/night/btn_close_click.png);\n"
"}"));
        line = new QFrame(widget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(18, 46, 212, 2));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(18, 67, 81, 30));
        lineEdit = new SA_LineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(101, 67, 140, 30));
        QFont font;
        font.setFamily(QStringLiteral("Liberation Sans"));
        font.setBold(true);
        font.setWeight(75);
        lineEdit->setFont(font);
        lineEdit->setCursorPosition(6);
        lineEdit->setReadOnly(true);
        lineEdit_1 = new SA_LineEdit(widget);
        lineEdit_1->setObjectName(QStringLiteral("lineEdit_1"));
        lineEdit_1->setGeometry(QRect(100, 130, 140, 30));
        lineEdit_1->setFont(font);
        lineEdit_1->setCursorPosition(8);
        lineEdit_1->setReadOnly(true);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(17, 130, 75, 30));

        retranslateUi(sa_dialog_occpdset);

        QMetaObject::connectSlotsByName(sa_dialog_occpdset);
    } // setupUi

    void retranslateUi(QWidget *sa_dialog_occpdset)
    {
        sa_dialog_occpdset->setWindowTitle(QApplication::translate("sa_dialog_occpdset", "Form", 0));
        ltitle->setText(QApplication::translate("sa_dialog_occpdset", "Occupied BW", 0));
        pb_cancel_2->setText(QString());
        label->setText(QApplication::translate("sa_dialog_occpdset", "OccBW%Pwr", 0));
        lineEdit->setText(QApplication::translate("sa_dialog_occpdset", "99.00%", 0));
        lineEdit_1->setText(QApplication::translate("sa_dialog_occpdset", "-26.00dB", 0));
        label_2->setText(QApplication::translate("sa_dialog_occpdset", "XdB", 0));
    } // retranslateUi

};

namespace Ui {
    class sa_dialog_occpdset: public Ui_sa_dialog_occpdset {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_OCCPDSET_H
