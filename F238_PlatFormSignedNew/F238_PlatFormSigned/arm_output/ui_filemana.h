/********************************************************************************
** Form generated from reading UI file 'filemana.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEMANA_H
#define UI_FILEMANA_H

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

class Ui_filemana
{
public:
    QWidget *widget_2;
    QFrame *line_4;
    QLabel *label_4;
    QPushButton *pushButton_19;
    QPushButton *pushButton_21;
    QFrame *line_5;
    QLabel *label_5;

    void setupUi(QWidget *filemana)
    {
        if (filemana->objectName().isEmpty())
            filemana->setObjectName(QStringLiteral("filemana"));
        filemana->resize(996, 598);
        filemana->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255,1);"));
        widget_2 = new QWidget(filemana);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(0, 0, 996, 720));
        widget_2->setStyleSheet(QLatin1String("QPushButton{\n"
"padding-left:10px;text-align:left;\n"
"color: rgb(105, 105, 105);\n"
"background-color: rgb(211, 211, 211);\n"
"font: 10pt \"Arial\";\n"
"font-weight:Bold;\n"
"border: none;\n"
"}\n"
"QPushButton:checked\n"
"{\n"
"background-color: rgb(255, 181, 0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"QLabel{background-color:rgba(0,0,0,0);\n"
"font: 11pt \"Arial\";font-weight:Bold;}\n"
"\n"
"#filemana[pltdismode=\"night\"] #widget_2\n"
"{	\n"
"background-color: rgb(0, 0, 0);\n"
"}\n"
"#filemana[pltdismode=\"indoor\"] #widget_2\n"
"{	\n"
"background-color:white;\n"
"}"));
        line_4 = new QFrame(widget_2);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(22, 47, 250, 2));
        line_4->setStyleSheet(QLatin1String("#filemana[pltdismode=\"indoor\"] #line_4\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#filemana[pltdismode=\"night\"] #line_4\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(22, 26, 221, 17));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        label_4->setFont(font);
        label_4->setStyleSheet(QStringLiteral("#filemana[pltdismode=\"indoor\"] QLabel  {color:rgba(6,62,97,1);	background-color: white;}#filemana[pltdismode=\"night\"] QLabel  {color:rgba(7,97,116,1);	background-color: black;}"));
        pushButton_19 = new QPushButton(widget_2);
        pushButton_19->setObjectName(QStringLiteral("pushButton_19"));
        pushButton_19->setGeometry(QRect(30, 68, 160, 34));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        pushButton_19->setFont(font1);
        pushButton_19->setStyleSheet(QLatin1String("#filemana[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(85, 87, 83);\n"
"text-align:center;\n"
"}\n"
"#filemana[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"text-align:center;\n"
"border-image: url(:/bit/image/click_night.png);\n"
"}"));
        pushButton_21 = new QPushButton(widget_2);
        pushButton_21->setObjectName(QStringLiteral("pushButton_21"));
        pushButton_21->setGeometry(QRect(330, 68, 160, 34));
        pushButton_21->setFont(font1);
        pushButton_21->setStyleSheet(QLatin1String("#filemana[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(85, 87, 83);\n"
"text-align:center;\n"
"}\n"
"#filemana[pltdismode=\"night\"] QPushButton\n"
"{\n"
"color: rgb(250,218,166);\n"
"text-align:center;\n"
"border-image: url(:/bit/image/click_night.png);\n"
"}"));
        line_5 = new QFrame(widget_2);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(322, 47, 250, 2));
        line_5->setStyleSheet(QLatin1String("#filemana[pltdismode=\"indoor\"] #line_5\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#filemana[pltdismode=\"night\"] #line_5\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        label_5 = new QLabel(widget_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(322, 26, 251, 17));
        label_5->setFont(font);
        label_5->setStyleSheet(QStringLiteral("#filemana[pltdismode=\"indoor\"] QLabel  {color:rgba(6,62,97,1);	background-color: white;}#filemana[pltdismode=\"night\"] QLabel  {color:rgba(7,97,116,1);	background-color: black;}"));

        retranslateUi(filemana);

        QMetaObject::connectSlotsByName(filemana);
    } // setupUi

    void retranslateUi(QWidget *filemana)
    {
        filemana->setWindowTitle(QApplication::translate("filemana", "Form", 0));
        filemana->setProperty("pltdismode", QVariant(QApplication::translate("filemana", "indoor", 0)));
        label_4->setText(QApplication::translate("filemana", "Zero Frequency Adjust", 0));
        pushButton_19->setText(QApplication::translate("filemana", "Zero Freq Auto Adjust", 0));
        pushButton_21->setText(QApplication::translate("filemana", "Factory Debug", 0));
        label_5->setText(QApplication::translate("filemana", "Factory Funtions Debug", 0));
    } // retranslateUi

};

namespace Ui {
    class filemana: public Ui_filemana {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEMANA_H
