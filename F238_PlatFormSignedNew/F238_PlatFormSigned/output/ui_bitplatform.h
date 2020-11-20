/********************************************************************************
** Form generated from reading UI file 'bitplatform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BITPLATFORM_H
#define UI_BITPLATFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "clicklabel.h"

QT_BEGIN_NAMESPACE

class Ui_BitPlatForm
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *toplabel;
    QPushButton *chafir;
    QPushButton *chathird;
    QPushButton *chasec;
    QPushButton *chafourth;
    QLabel *statebarlabel;
    ClickLabel *batterylabel;
    ClickLabel *timelabel;
    ClickLabel *label_2;
    ClickLabel *label_3;
    ClickLabel *batpiclabel;
    ClickLabel *gpslabel;
    QPushButton *plusbtn;
    ClickLabel *label_4;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *mode3btn;
    QPushButton *mode4btn;
    QLabel *label_5;
    QPushButton *mode1btn;
    QPushButton *mode2btn;
    ClickLabel *label_10;
    ClickLabel *label_11;

    void setupUi(QMainWindow *BitPlatForm)
    {
        if (BitPlatForm->objectName().isEmpty())
            BitPlatForm->setObjectName(QStringLiteral("BitPlatForm"));
        BitPlatForm->resize(1280, 800);
        BitPlatForm->setCursor(QCursor(Qt::BlankCursor));
        BitPlatForm->setLayoutDirection(Qt::LeftToRight);
        BitPlatForm->setAutoFillBackground(false);
        BitPlatForm->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(BitPlatForm);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral(""));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 1280, 800));
        label->setFocusPolicy(Qt::StrongFocus);
        label->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"	background-image: url(:/bit/image/background.png);\n"
"}"));
        toplabel = new QLabel(centralWidget);
        toplabel->setObjectName(QStringLiteral("toplabel"));
        toplabel->setGeometry(QRect(1, 2, 1126, 50));
        QFont font;
        font.setKerning(true);
        toplabel->setFont(font);
        toplabel->setLayoutDirection(Qt::LeftToRight);
        toplabel->setPixmap(QPixmap(QString::fromUtf8(":/bit/image/4_tab1.png")));
        toplabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        chafir = new QPushButton(centralWidget);
        chafir->setObjectName(QStringLiteral("chafir"));
        chafir->setGeometry(QRect(252, 4, 35, 48));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        chafir->setFont(font1);
        chafir->setFlat(true);
        chathird = new QPushButton(centralWidget);
        chathird->setObjectName(QStringLiteral("chathird"));
        chathird->setGeometry(QRect(807, 4, 35, 48));
        chathird->setFont(font1);
        chathird->setFlat(true);
        chasec = new QPushButton(centralWidget);
        chasec->setObjectName(QStringLiteral("chasec"));
        chasec->setGeometry(QRect(529, 4, 35, 48));
        chasec->setFont(font1);
        chasec->setFlat(true);
        chafourth = new QPushButton(centralWidget);
        chafourth->setObjectName(QStringLiteral("chafourth"));
        chafourth->setGeometry(QRect(1085, 4, 35, 48));
        chafourth->setFont(font1);
        chafourth->setFlat(true);
        statebarlabel = new QLabel(centralWidget);
        statebarlabel->setObjectName(QStringLiteral("statebarlabel"));
        statebarlabel->setGeometry(QRect(0, 765, 1280, 35));
        statebarlabel->setFocusPolicy(Qt::StrongFocus);
        statebarlabel->setPixmap(QPixmap(QString::fromUtf8(":/bit/image/status_bar.png")));
        batterylabel = new ClickLabel(centralWidget);
        batterylabel->setObjectName(QStringLiteral("batterylabel"));
        batterylabel->setGeometry(QRect(1191, 772, 59, 17));
        QFont font2;
        font2.setFamily(QStringLiteral("ArialMT"));
        font2.setPointSize(13);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        batterylabel->setFont(font2);
        batterylabel->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
""));
        batterylabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        timelabel = new ClickLabel(centralWidget);
        timelabel->setObjectName(QStringLiteral("timelabel"));
        timelabel->setGeometry(QRect(901, 772, 226, 17));
        timelabel->setFont(font2);
        timelabel->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
""));
        timelabel->setAlignment(Qt::AlignCenter);
        label_2 = new ClickLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(27, 768, 69, 25));
        label_2->setStyleSheet(QStringLiteral("background-image:url(:/bit/image/logo_inno_white_s.png);"));
        label_3 = new ClickLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(150, 768, 70, 25));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/bit/image/icn_gps_disable.png")));
        batpiclabel = new ClickLabel(centralWidget);
        batpiclabel->setObjectName(QStringLiteral("batpiclabel"));
        batpiclabel->setGeometry(QRect(1147, 771, 54, 22));
        batpiclabel->setPixmap(QPixmap(QString::fromUtf8(":/bit/image/icn_battery_5.png")));
        gpslabel = new ClickLabel(centralWidget);
        gpslabel->setObjectName(QStringLiteral("gpslabel"));
        gpslabel->setGeometry(QRect(232, 772, 226, 17));
        gpslabel->setFont(font2);
        gpslabel->setStyleSheet(QLatin1String("color: rgb(136, 136, 136);\n"
""));
        gpslabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        plusbtn = new QPushButton(centralWidget);
        plusbtn->setObjectName(QStringLiteral("plusbtn"));
        plusbtn->setGeometry(QRect(1134, 0, 52, 52));
        plusbtn->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/4_icn_add_normal.png);\n"
"}\n"
"QPushButton { border-style: flat;}"));
        plusbtn->setAutoDefault(false);
        plusbtn->setFlat(true);
        label_4 = new ClickLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(605, 768, 70, 25));
        QFont font3;
        font3.setFamily(QStringLiteral("Arial"));
        font3.setPointSize(13);
        font3.setBold(false);
        font3.setWeight(50);
        label_4->setFont(font3);
        label_4->setStyleSheet(QStringLiteral("background-image: url(:/bit/image/icn_local.png);"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(294, 4, 241, 48));
        QFont font4;
        font4.setFamily(QStringLiteral("Arial"));
        font4.setPointSize(12);
        font4.setBold(true);
        font4.setWeight(75);
        label_6->setFont(font4);
        label_6->setStyleSheet(QStringLiteral("padding-left:16px"));
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(570, 4, 241, 48));
        label_7->setFont(font4);
        label_7->setStyleSheet(QStringLiteral("padding-left:16px;"));
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(850, 4, 241, 48));
        label_8->setFont(font4);
        label_8->setStyleSheet(QStringLiteral("padding-left:16px;"));
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        mode3btn = new QPushButton(centralWidget);
        mode3btn->setObjectName(QStringLiteral("mode3btn"));
        mode3btn->setGeometry(QRect(565, 4, 241, 48));
        QFont font5;
        font5.setFamily(QStringLiteral("Arial"));
        font5.setPointSize(16);
        font5.setBold(true);
        font5.setWeight(75);
        mode3btn->setFont(font5);
        mode3btn->setStyleSheet(QStringLiteral(""));
        mode3btn->setFlat(true);
        mode4btn = new QPushButton(centralWidget);
        mode4btn->setObjectName(QStringLiteral("mode4btn"));
        mode4btn->setGeometry(QRect(843, 4, 241, 48));
        QFont font6;
        font6.setFamily(QStringLiteral("Arial"));
        font6.setPointSize(14);
        font6.setBold(false);
        font6.setWeight(50);
        mode4btn->setFont(font6);
        mode4btn->setStyleSheet(QStringLiteral(""));
        mode4btn->setFlat(true);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(0, 4, 261, 48));
        label_5->setFont(font4);
        label_5->setLayoutDirection(Qt::LeftToRight);
        label_5->setStyleSheet(QStringLiteral("padding-left:16px;"));
        label_5->setText(QStringLiteral("Spectrum Analyzer<BR/><span style=\"font-weight:normal;\">Swept SA</span>"));
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        mode1btn = new QPushButton(centralWidget);
        mode1btn->setObjectName(QStringLiteral("mode1btn"));
        mode1btn->setGeometry(QRect(0, 4, 251, 48));
        mode1btn->setFont(font6);
        mode1btn->setLayoutDirection(Qt::LeftToRight);
        mode1btn->setStyleSheet(QStringLiteral(""));
        mode1btn->setCheckable(false);
        mode1btn->setFlat(true);
        mode2btn = new QPushButton(centralWidget);
        mode2btn->setObjectName(QStringLiteral("mode2btn"));
        mode2btn->setGeometry(QRect(288, 4, 241, 48));
        mode2btn->setFont(font6);
        mode2btn->setStyleSheet(QStringLiteral(""));
        mode2btn->setFlat(true);
        label_10 = new ClickLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(850, 772, 25, 25));
        label_10->setStyleSheet(QStringLiteral("border-image: url(:/bit/image/msg.png);"));
        label_11 = new ClickLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(860, 768, 20, 20));
        QFont font7;
        font7.setFamily(QStringLiteral("Arial"));
        font7.setPointSize(7);
        label_11->setFont(font7);
        label_11->setStyleSheet(QLatin1String("background-color: rgba(255, 255, 255,0);\n"
"color: rgb(255, 255, 255);"));
        label_11->setAlignment(Qt::AlignCenter);
        BitPlatForm->setCentralWidget(centralWidget);

        retranslateUi(BitPlatForm);

        QMetaObject::connectSlotsByName(BitPlatForm);
    } // setupUi

    void retranslateUi(QMainWindow *BitPlatForm)
    {
        BitPlatForm->setWindowTitle(QApplication::translate("BitPlatForm", "BitPlatForm", Q_NULLPTR));
        label->setText(QString());
#ifndef QT_NO_ACCESSIBILITY
        toplabel->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
        toplabel->setText(QString());
        chafir->setText(QString());
        chathird->setText(QString());
        chasec->setText(QString());
        chafourth->setText(QString());
        statebarlabel->setText(QString());
        batterylabel->setText(QString());
        timelabel->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        batpiclabel->setText(QString());
        gpslabel->setText(QApplication::translate("BitPlatForm", "-- -- -- --", Q_NULLPTR));
        plusbtn->setText(QString());
        label_4->setText(QString());
        label_6->setText(QApplication::translate("BitPlatForm", "Real-Time SA<BR/><span style=\"font-weight:normal;\">Persist Spectrogram</span>", Q_NULLPTR));
        label_7->setText(QApplication::translate("BitPlatForm", "LTE-A FDD<BR/><span style=\"font-weight:normal;\">Power vs Time(Slot)</span>", Q_NULLPTR));
        label_8->setText(QApplication::translate("BitPlatForm", "Power Meter<BR/><span style=\"font-weight:normal;\">Internal</span>", Q_NULLPTR));
        mode3btn->setText(QString());
        mode4btn->setText(QString());
        mode1btn->setText(QString());
        mode2btn->setText(QString());
        label_10->setText(QString());
        label_11->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BitPlatForm: public Ui_BitPlatForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BITPLATFORM_H
