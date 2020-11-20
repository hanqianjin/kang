/********************************************************************************
** Form generated from reading UI file 'setwid.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETWID_H
#define UI_SETWID_H

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

class Ui_setwid
{
public:
    QLabel *label;
    QPushButton *clobtn;
    QLabel *label_2;
    QWidget *backwid;
    QPushButton *pushButton_4;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QLabel *label_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_5;
    QFrame *line_2;
    QFrame *line_3;
    QPushButton *pushButton_6;

    void setupUi(QWidget *setwid)
    {
        if (setwid->objectName().isEmpty())
            setwid->setObjectName(QStringLiteral("setwid"));
        setwid->resize(1280, 800);
        setwid->setStyleSheet(QLatin1String("#setwid[pltdismode=\"indoor\"] \n"
"{\n"
"background-color: rgba(255, 255, 255,1);\n"
"}\n"
"#setwid[pltdismode=\"night\"]\n"
"{\n"
"background-color: rgba(0, 0, 0,1);\n"
"}\n"
""));
        label = new QLabel(setwid);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(1, 1, 1278, 45));
        label->setStyleSheet(QLatin1String("#setwid[pltdismode=\"indoor\"] QLabel\n"
"{\n"
"background-color: rgba(201, 201, 201,1);\n"
"}\n"
"#setwid[pltdismode=\"night\"] QLabel\n"
"{\n"
"background-color: rgba(53, 46, 35,1);\n"
"}"));
        clobtn = new QPushButton(setwid);
        clobtn->setObjectName(QStringLiteral("clobtn"));
        clobtn->setGeometry(QRect(1211, 1, 45, 45));
        clobtn->setStyleSheet(QLatin1String("#setwid[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/btn_close_30_nor.png);\n"
"}\n"
"#setwid[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/btn_close_30_click.png);\n"
"}\n"
"\n"
"#setwid[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/night_close_nor.png);\n"
"}\n"
"#setwid[pltdismode=\"night\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/night_close_click.png);\n"
"}\n"
"QPushButton { border-style: flat;}"));
        clobtn->setFlat(true);
        label_2 = new QLabel(setwid);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 12, 347, 22));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        label_2->setStyleSheet(QLatin1String("#setwid[pltdismode=\"indoor\"] QLabel\n"
"{\n"
"color: rgba(0, 0, 0,1);\n"
"}\n"
"#setwid[pltdismode=\"night\"] QLabel\n"
"{\n"
"background-color: rgba(53,46,35,1);\n"
"color: rgba(250,218,166,1);\n"
"}"));
        backwid = new QWidget(setwid);
        backwid->setObjectName(QStringLiteral("backwid"));
        backwid->setGeometry(QRect(0, 46, 282, 720));
        backwid->setStyleSheet(QLatin1String("#setwid[pltdismode=\"indoor\"] #backwid\n"
"{\n"
"background-color: rgba(255, 255, 255,1);\n"
"}\n"
"#setwid[pltdismode=\"night\"] #backwid\n"
"{\n"
"background-color: rgba(0, 0, 0,1);\n"
"}\n"
"QPushButton{border-style:flat;text-align:left;}\n"
"QLabel{background-color:rgba(0,0,0,0);}\n"
"QPushButton{padding-left:10px}\n"
"\n"
"#setwid[pltdismode=\"indoor\"] QPushButton:!checked\n"
"{\n"
"font: 11pt \"Arial\";\n"
"font-weight:normal;\n"
"background-color: rgba(237, 212, 0,0);\n"
"color: rgb(105, 105, 105);\n"
"}\n"
"#setwid[pltdismode=\"night\"] QPushButton:!checked\n"
"{\n"
"font: 11pt \"Arial\";\n"
"font-weight:normal;\n"
"color: rgb(250,218,166);\n"
"background-color: rgb(24,23,20);\n"
"}\n"
"#setwid[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"font: 75 11pt \"Arial\";\n"
"font-weight:bold;\n"
"background-color: rgb(255,181,0);\n"
"color: rgb(57, 57, 57);\n"
"}\n"
"#setwid[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"font: 75 11pt \"Arial\";\n"
"font-weight:bold;\n"
"background-color: rgb(25"
                        "5, 156, 0);\n"
"color: rgb(0, 0, 0);\n"
"}\n"
""));
        pushButton_4 = new QPushButton(backwid);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setEnabled(true);
        pushButton_4->setGeometry(QRect(20, 190, 237, 30));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        pushButton_4->setFont(font1);
        pushButton_4->setStyleSheet(QStringLiteral(""));
        pushButton_4->setCheckable(true);
        pushButton_4->setAutoExclusive(true);
        pushButton_4->setFlat(false);
        pushButton = new QPushButton(backwid);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(20, 55, 237, 30));
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QStringLiteral(""));
        pushButton->setCheckable(true);
        pushButton->setChecked(true);
        pushButton->setAutoExclusive(true);
        pushButton->setFlat(false);
        pushButton_3 = new QPushButton(backwid);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(20, 145, 237, 30));
        pushButton_3->setFont(font1);
        pushButton_3->setStyleSheet(QStringLiteral(""));
        pushButton_3->setCheckable(true);
        pushButton_3->setChecked(false);
        pushButton_3->setAutoExclusive(true);
        pushButton_3->setFlat(false);
        label_3 = new QLabel(backwid);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(22, 28, 60, 17));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(11);
        font2.setBold(true);
        font2.setWeight(75);
        label_3->setFont(font2);
        label_3->setStyleSheet(QLatin1String("#setwid[pltdismode=\"indoor\"] QLabel \n"
" {\n"
"color:rgba(6,62,97,1);\n"
"	background-color: white;\n"
"}\n"
"#setwid[pltdismode=\"night\"] QLabel \n"
" {\n"
"color:rgba(7,97,116,1);\n"
"	background-color: black;\n"
"}"));
        pushButton_2 = new QPushButton(backwid);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(20, 100, 237, 30));
        pushButton_2->setFont(font1);
        pushButton_2->setStyleSheet(QStringLiteral(""));
        pushButton_2->setCheckable(true);
        pushButton_2->setAutoExclusive(true);
        pushButton_2->setFlat(false);
        pushButton_5 = new QPushButton(backwid);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(20, 235, 237, 30));
        pushButton_5->setFont(font1);
        pushButton_5->setStyleSheet(QStringLiteral(""));
        pushButton_5->setCheckable(true);
        pushButton_5->setAutoExclusive(true);
        pushButton_5->setFlat(false);
        line_2 = new QFrame(backwid);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(280, -10, 2, 800));
        line_2->setSizeIncrement(QSize(0, 0));
        line_2->setBaseSize(QSize(0, 0));
        line_2->setStyleSheet(QLatin1String("#setwid[pltdismode=\"indoor\"] #line_2\n"
"{\n"
"background-color: rgba(181, 181, 181,1);\n"
"}\n"
"#setwid[pltdismode=\"night\"] #line_2\n"
"{\n"
"background-color: rgba(64, 64, 64,1);\n"
"}"));
        line_2->setLineWidth(0);
        line_2->setMidLineWidth(0);
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(backwid);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(22, 47, 237, 2));
        line_3->setStyleSheet(QLatin1String("#setwid[pltdismode=\"indoor\"] #line_3\n"
" {\n"
"background-color:rgba(6,62,97,1);	\n"
"}\n"
"#setwid[pltdismode=\"night\"] #line_3\n"
" {\n"
"background-color:rgba(7,97,116,1);\n"
"}"));
        line_3->setLineWidth(0);
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        pushButton_6 = new QPushButton(backwid);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(20, 280, 237, 30));
        pushButton_6->setFont(font1);
        pushButton_6->setStyleSheet(QStringLiteral(""));
        pushButton_6->setCheckable(true);
        pushButton_6->setAutoExclusive(true);
        pushButton_6->setFlat(false);

        retranslateUi(setwid);

        QMetaObject::connectSlotsByName(setwid);
    } // setupUi

    void retranslateUi(QWidget *setwid)
    {
        setwid->setWindowTitle(QApplication::translate("setwid", "Form", Q_NULLPTR));
        setwid->setProperty("pltdismode", QVariant(QApplication::translate("setwid", "indoor", Q_NULLPTR)));
        label->setText(QString());
        clobtn->setText(QString());
        label_2->setText(QApplication::translate("setwid", "Settings", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("setwid", "Self Test", Q_NULLPTR));
        pushButton->setText(QApplication::translate("setwid", "General Setting", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("setwid", "Network Setting", Q_NULLPTR));
        label_3->setText(QApplication::translate("setwid", "Items", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("setwid", "Display / Sound / Date / Time", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("setwid", "Calibration", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("setwid", "System Information", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class setwid: public Ui_setwid {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETWID_H
