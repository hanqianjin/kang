/********************************************************************************
** Form generated from reading UI file 'sa_dialog_acpset.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_ACPSET_H
#define UI_SA_DIALOG_ACPSET_H

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

class Ui_sa_dialog_acpset
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
    SA_LineEdit *lineEdit_2;
    QLabel *label_3;
    QLabel *label_4;
    SA_LineEdit *lineEdit_3;
    QLabel *label_5;
    SA_LineEdit *lineEdit_4;
    QLabel *label_6;
    SA_LineEdit *lineEdit_5;
    SA_LineEdit *lineEdit_6;
    QLabel *label_7;
    SA_LineEdit *lineEdit_7;
    QLabel *label_8;

    void setupUi(QWidget *sa_dialog_acpset)
    {
        if (sa_dialog_acpset->objectName().isEmpty())
            sa_dialog_acpset->setObjectName(QStringLiteral("sa_dialog_acpset"));
        sa_dialog_acpset->resize(252, 646);
        sa_dialog_acpset->setStyleSheet(QLatin1String("#line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#widget>QPushButton\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"	font: 75 13px \"Arial\";\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"#widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"SA_LineEdit,\n"
"SA_LineEdit:disable\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"\n"
"/*******************indoor**********************/\n"
"#sa_dialog_acpset[status  =  \"indoor\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#sa_dialog_acpset[status  =  \"indoor\"] #widget>QPushButton\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"}\n"
"\n"
"#sa_dialog_acpset[status  "
                        "=  \"indoor\"] #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#sa_dialog_acpset[status  =  \"indoor\"] #widget>QLabel\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#sa_dialog_acpset[status  =  \"indoor\"] SA_LineEdit,\n"
"#sa_dialog_acpset[status  =  \"indoor\"] SA_LineEdit:disable\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"}\n"
"#sa_dialog_acpset[status  =  \"indoor\"] SA_LineEdit:focus\n"
"{\n"
"	border:2px solid rgba(162,115,0,1);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#sa_dialog_acpset[status  =  \"outdoor\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#sa_dialog_acpset[status  =  \"outdoor\"] #widget>QPushButton\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"}\n"
"\n"
"#sa_dialog_acpset[status  =  \"outdoor\"] #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#sa_dialog_acpset[status  =  \"outdoor\"] #widget>QLabel\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#sa_dialog_"
                        "acpset[status  =  \"outdoor\"] SA_LineEdit,\n"
"#sa_dialog_acpset[status  =  \"outdoor\"] SA_LineEdit:disable\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"}\n"
"#sa_dialog_acpset[status  =  \"outdoor\"] SA_LineEdit:focus\n"
"{\n"
"	border:2px solid rgba(162,115,0,1);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#sa_dialog_acpset[status  =  \"night\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#sa_dialog_acpset[status  =  \"night\"] #widget>QPushButton\n"
"{\n"
"	color:rgba(123, 123, 123,1);\n"
"}\n"
"\n"
"#sa_dialog_acpset[status  =  \"night\"] #widget\n"
"{\n"
"	background-color:rgba(208,182,139,0.9);\n"
"}\n"
"#sa_dialog_acpset[status  =  \"night\"] #widget>QLabel\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#sa_dialog_acpset[status  =  \"night\"] SA_LineEdit,\n"
"#sa_dialog_acpset[status  =  \"night\"] SA_LineEdit:disable\n"
"{\n"
" 	background-color: rgba(251,220,167,0.60);\n"
"	color:rgba(159,98,0,1);\n"
"}\n"
"#sa_dialo"
                        "g_acpset[status  =  \"night\"] SA_LineEdit:focus\n"
"{\n"
"	border:2px solid rgba(162,115,0,1);\n"
"}"));
        widget = new QWidget(sa_dialog_acpset);
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
"#sa_dialog_acpset[status  =  \"indoor\"] QPushButton\n"
"{\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#sa_dialog_acpset[status  =  \"indoor\"] QPushButton:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#sa_dialog_acpset[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#sa_dialog_acpset[status  =  \"outdoor\"] QPushButton:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#sa_dialog_acpset[status  =  \"night\"] QPushButton\n"
"{\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/night/btn_close_normal.png);\n"
"}\n"
"#sa_dialog_acpset[status  =  \"night\"] QPushButton:pressed\n"
"{\n"
"border-image: url(:/sa/image/"
                        "night/btn_close_click.png);\n"
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
        lineEdit_1 = new SA_LineEdit(widget);
        lineEdit_1->setObjectName(QStringLiteral("lineEdit_1"));
        lineEdit_1->setGeometry(QRect(100, 140, 140, 30));
        lineEdit_1->setFont(font);
        lineEdit_1->setCursorPosition(9);
        lineEdit_1->setReadOnly(true);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(18, 140, 75, 30));
        lineEdit_2 = new SA_LineEdit(widget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(100, 280, 140, 30));
        lineEdit_2->setFont(font);
        lineEdit_2->setCursorPosition(9);
        lineEdit_2->setReadOnly(true);
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(18, 280, 75, 30));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(18, 210, 75, 30));
        lineEdit_3 = new SA_LineEdit(widget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(100, 210, 140, 30));
        lineEdit_3->setFont(font);
        lineEdit_3->setCursorPosition(9);
        lineEdit_3->setReadOnly(true);
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(18, 350, 75, 30));
        lineEdit_4 = new SA_LineEdit(widget);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(100, 420, 140, 30));
        lineEdit_4->setFont(font);
        lineEdit_4->setCursorPosition(9);
        lineEdit_4->setReadOnly(true);
        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(18, 420, 75, 30));
        lineEdit_5 = new SA_LineEdit(widget);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(100, 350, 140, 30));
        lineEdit_5->setFont(font);
        lineEdit_5->setCursorPosition(9);
        lineEdit_5->setReadOnly(true);
        lineEdit_6 = new SA_LineEdit(widget);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(100, 560, 140, 30));
        lineEdit_6->setFont(font);
        lineEdit_6->setCursorPosition(9);
        lineEdit_6->setReadOnly(true);
        label_7 = new QLabel(widget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(18, 490, 75, 30));
        lineEdit_7 = new SA_LineEdit(widget);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(100, 490, 140, 30));
        lineEdit_7->setFont(font);
        lineEdit_7->setCursorPosition(9);
        lineEdit_7->setReadOnly(true);
        label_8 = new QLabel(widget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(18, 560, 75, 30));

        retranslateUi(sa_dialog_acpset);

        QMetaObject::connectSlotsByName(sa_dialog_acpset);
    } // setupUi

    void retranslateUi(QWidget *sa_dialog_acpset)
    {
        sa_dialog_acpset->setWindowTitle(QApplication::translate("sa_dialog_acpset", "Form", Q_NULLPTR));
        sa_dialog_acpset->setProperty("status", QVariant(QApplication::translate("sa_dialog_acpset", "indoor", Q_NULLPTR)));
        ltitle->setText(QApplication::translate("sa_dialog_acpset", "ACP", Q_NULLPTR));
        pb_cancel_2->setText(QString());
        label->setText(QApplication::translate("sa_dialog_acpset", "Channel\n"
"Bandwidth", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("sa_dialog_acpset", "3.000 MHz", Q_NULLPTR));
        lineEdit_1->setText(QApplication::translate("sa_dialog_acpset", "5.000 MHz", Q_NULLPTR));
        label_2->setText(QApplication::translate("sa_dialog_acpset", "Channel\n"
"Space", Q_NULLPTR));
        lineEdit_2->setText(QApplication::translate("sa_dialog_acpset", "5.000 MHz", Q_NULLPTR));
        label_3->setText(QApplication::translate("sa_dialog_acpset", "Lowest\n"
"CH FREQ", Q_NULLPTR));
        label_4->setText(QApplication::translate("sa_dialog_acpset", "Highest\n"
"CH FREQ", Q_NULLPTR));
        lineEdit_3->setText(QApplication::translate("sa_dialog_acpset", "3.000 MHz", Q_NULLPTR));
        label_5->setText(QApplication::translate("sa_dialog_acpset", "CHANNEL\n"
"SPACING", Q_NULLPTR));
        lineEdit_4->setText(QApplication::translate("sa_dialog_acpset", "5.000 MHz", Q_NULLPTR));
        label_6->setText(QApplication::translate("sa_dialog_acpset", "MAIN\n"
"INTEG BW", Q_NULLPTR));
        lineEdit_5->setText(QApplication::translate("sa_dialog_acpset", "3.000 MHz", Q_NULLPTR));
        lineEdit_6->setText(QApplication::translate("sa_dialog_acpset", "5.000 MHz", Q_NULLPTR));
        label_7->setText(QApplication::translate("sa_dialog_acpset", "ADJ\n"
"INTEG BW", Q_NULLPTR));
        lineEdit_7->setText(QApplication::translate("sa_dialog_acpset", "3.000 MHz", Q_NULLPTR));
        label_8->setText(QApplication::translate("sa_dialog_acpset", "ALT\n"
"INTEG BW", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class sa_dialog_acpset: public Ui_sa_dialog_acpset {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_ACPSET_H
