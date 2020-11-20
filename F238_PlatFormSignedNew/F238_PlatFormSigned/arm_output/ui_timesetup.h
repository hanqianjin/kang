/********************************************************************************
** Form generated from reading UI file 'timesetup.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMESETUP_H
#define UI_TIMESETUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_timeSetup
{
public:
    QWidget *widget;
    QPushButton *up_hour;
    QPushButton *up_minu;
    QPushButton *up_sec;
    QPushButton *down_hour;
    QPushButton *down_minu;
    QPushButton *down_sec;
    QLineEdit *Edit_hour;
    QLineEdit *Edit_minu;
    QLineEdit *edit_sec;
    QPushButton *pb_cancel;
    QPushButton *pb_ok;

    void setupUi(QDialog *timeSetup)
    {
        if (timeSetup->objectName().isEmpty())
            timeSetup->setObjectName(QStringLiteral("timeSetup"));
        timeSetup->resize(370, 190);
        timeSetup->setStyleSheet(QLatin1String("#timeSetup[pltdismode=\"indoor\"] #widget\n"
"{\n"
"	background-color:rgba(247, 247, 247, 1);\n"
"}\n"
"\n"
"#timeSetup[pltdismode=\"outdoor\"] #widget\n"
"{\n"
"	background-color:rgba(247, 247, 247, 1);\n"
"}\n"
"\n"
"#timeSetup[pltdismode=\"night\"] #widget\n"
"{\n"
"	background-image: url(:/bit/image/popup/bk-night.png);\n"
"}\n"
"QLineEdit\n"
"{\n"
"	font:75 18px \"Arial\";\n"
"	padding-left:10px;\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"	border-style:flat;\n"
"}\n"
"\n"
"\n"
"\n"
""));
        widget = new QWidget(timeSetup);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 370, 190));
        widget->setStyleSheet(QStringLiteral(""));
        up_hour = new QPushButton(widget);
        up_hour->setObjectName(QStringLiteral("up_hour"));
        up_hour->setGeometry(QRect(20, 15, 100, 34));
        up_hour->setFocusPolicy(Qt::NoFocus);
        up_hour->setStyleSheet(QLatin1String("#timeSetup[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/popup/up.png);\n"
"}\n"
"#timeSetup[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/popup/up.png);\n"
"}\n"
"\n"
"#timeSetup[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/popup/up.png);\n"
"}\n"
"#timeSetup[pltdismode=\"outdoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/popup/up.png);\n"
"}\n"
"\n"
"#timeSetup[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/popup/up-night.png);\n"
"}\n"
"#timeSetup[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/popup/up-night.png);\n"
"}\n"
"\n"
""));
        up_minu = new QPushButton(widget);
        up_minu->setObjectName(QStringLiteral("up_minu"));
        up_minu->setGeometry(QRect(135, 15, 100, 34));
        up_minu->setFocusPolicy(Qt::NoFocus);
        up_minu->setStyleSheet(QLatin1String("#timeSetup[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/popup/up.png);\n"
"}\n"
"#timeSetup[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/popup/up.png);\n"
"}\n"
"\n"
"#timeSetup[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/popup/up.png);\n"
"}\n"
"#timeSetup[pltdismode=\"outdoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/popup/up.png);\n"
"}\n"
"\n"
"#timeSetup[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/popup/up-night.png);\n"
"}\n"
"#timeSetup[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/popup/up-night.png);\n"
"}\n"
"\n"
""));
        up_sec = new QPushButton(widget);
        up_sec->setObjectName(QStringLiteral("up_sec"));
        up_sec->setGeometry(QRect(250, 15, 100, 34));
        up_sec->setFocusPolicy(Qt::NoFocus);
        up_sec->setStyleSheet(QLatin1String("#timeSetup[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/popup/up.png);\n"
"}\n"
"#timeSetup[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/popup/up.png);\n"
"}\n"
"\n"
"#timeSetup[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/popup/up.png);\n"
"}\n"
"#timeSetup[pltdismode=\"outdoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/popup/up.png);\n"
"}\n"
"\n"
"#timeSetup[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/popup/up-night.png);\n"
"}\n"
"#timeSetup[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/popup/up-night.png);\n"
"}\n"
"\n"
""));
        down_hour = new QPushButton(widget);
        down_hour->setObjectName(QStringLiteral("down_hour"));
        down_hour->setGeometry(QRect(20, 91, 100, 34));
        down_hour->setFocusPolicy(Qt::NoFocus);
        down_hour->setStyleSheet(QLatin1String("#timeSetup[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/popup/down.png);\n"
"}\n"
"#timeSetup[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/popup/down.png);\n"
"}\n"
"\n"
"#timeSetup[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/popup/down.png);\n"
"}\n"
"#timeSetup[pltdismode=\"outdoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/popup/down.png);\n"
"}\n"
"\n"
"#timeSetup[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/popup/down-night.png);\n"
"}\n"
"#timeSetup[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/popup/down-night.png);\n"
"}\n"
"\n"
""));
        down_minu = new QPushButton(widget);
        down_minu->setObjectName(QStringLiteral("down_minu"));
        down_minu->setGeometry(QRect(135, 91, 100, 34));
        down_minu->setFocusPolicy(Qt::NoFocus);
        down_minu->setStyleSheet(QLatin1String("#timeSetup[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/popup/down.png);\n"
"}\n"
"#timeSetup[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/popup/down.png);\n"
"}\n"
"\n"
"#timeSetup[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/popup/down.png);\n"
"}\n"
"#timeSetup[pltdismode=\"outdoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/popup/down.png);\n"
"}\n"
"\n"
"#timeSetup[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/popup/down-night.png);\n"
"}\n"
"#timeSetup[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/popup/down-night.png);\n"
"}\n"
"\n"
""));
        down_sec = new QPushButton(widget);
        down_sec->setObjectName(QStringLiteral("down_sec"));
        down_sec->setGeometry(QRect(250, 91, 100, 34));
        down_sec->setFocusPolicy(Qt::NoFocus);
        down_sec->setStyleSheet(QLatin1String("#timeSetup[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/popup/down.png);\n"
"}\n"
"#timeSetup[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/popup/down.png);\n"
"}\n"
"\n"
"#timeSetup[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/popup/down.png);\n"
"}\n"
"#timeSetup[pltdismode=\"outdoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/popup/down.png);\n"
"}\n"
"\n"
"#timeSetup[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/popup/down-night.png);\n"
"}\n"
"#timeSetup[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/popup/down-night.png);\n"
"}\n"
"\n"
""));
        Edit_hour = new QLineEdit(widget);
        Edit_hour->setObjectName(QStringLiteral("Edit_hour"));
        Edit_hour->setGeometry(QRect(20, 53, 100, 34));
        Edit_hour->setStyleSheet(QLatin1String("#timeSetup[pltdismode=\"indoor\"] QLineEdit\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/bit/image/popup/input-box.png);\n"
"}\n"
"#timeSetup[pltdismode=\"outdoor\"] QLineEdit\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/bit/image/popup/input-box.png);\n"
"}\n"
"#timeSetup[pltdismode=\"night\"] QLineEdit\n"
"{\n"
"	color:rgba(3, 39, 62, 1);\n"
"	border-style:flat;\n"
"	background-image: url(:/bit/image/popup/input-box-night.png);\n"
"}\n"
"\n"
"\n"
""));
        Edit_minu = new QLineEdit(widget);
        Edit_minu->setObjectName(QStringLiteral("Edit_minu"));
        Edit_minu->setGeometry(QRect(135, 53, 100, 34));
        Edit_minu->setStyleSheet(QLatin1String("#timeSetup[pltdismode=\"indoor\"] QLineEdit\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/bit/image/popup/input-box.png);\n"
"}\n"
"#timeSetup[pltdismode=\"outdoor\"] QLineEdit\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/bit/image/popup/input-box.png);\n"
"}\n"
"#timeSetup[pltdismode=\"night\"] QLineEdit\n"
"{\n"
"	color:rgba(3, 39, 62, 1);\n"
"	border-style:flat;\n"
"	background-image: url(:/bit/image/popup/input-box-night.png);\n"
"}\n"
"\n"
"\n"
""));
        edit_sec = new QLineEdit(widget);
        edit_sec->setObjectName(QStringLiteral("edit_sec"));
        edit_sec->setGeometry(QRect(250, 53, 100, 34));
        edit_sec->setStyleSheet(QLatin1String("#timeSetup[pltdismode=\"indoor\"] QLineEdit\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/bit/image/popup/input-box.png);\n"
"}\n"
"#timeSetup[pltdismode=\"outdoor\"] QLineEdit\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/bit/image/popup/input-box.png);\n"
"}\n"
"#timeSetup[pltdismode=\"night\"] QLineEdit\n"
"{\n"
"	color:rgba(3, 39, 62, 1);\n"
"	border-style:flat;\n"
"	background-image: url(:/bit/image/popup/input-box-night.png);\n"
"}\n"
"\n"
"\n"
""));
        pb_cancel = new QPushButton(widget);
        pb_cancel->setObjectName(QStringLiteral("pb_cancel"));
        pb_cancel->setGeometry(QRect(193, 140, 80, 30));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(13);
        pb_cancel->setFont(font);
        pb_cancel->setFocusPolicy(Qt::NoFocus);
        pb_cancel->setStyleSheet(QLatin1String("#timeSetup[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/btn_cancel_w80_nor.png);\n"
"}\n"
"#timeSetup[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/btn_cancel_w80_click.png);\n"
"}\n"
"\n"
"#timeSetup[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/btn_cancel_w80_nor.png);\n"
"}\n"
"#timeSetup[pltdismode=\"outdoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/btn_cancel_w80_click.png);\n"
"}\n"
"\n"
"#timeSetup[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/cancel-normal_night.png);\n"
"}\n"
"#timeSetup[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/cancel-click_night.png);\n"
"}\n"
"QPushButton{padding-left:0px;text-align:center;\n"
"color: rgb(255, 255, 255);\n"
"}"));
        pb_ok = new QPushButton(widget);
        pb_ok->setObjectName(QStringLiteral("pb_ok"));
        pb_ok->setGeometry(QRect(275, 140, 80, 30));
        pb_ok->setFont(font);
        pb_ok->setFocusPolicy(Qt::NoFocus);
        pb_ok->setStyleSheet(QLatin1String("#timeSetup[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-image:url(:/bit/image/btn_ok_w80_nor.png);\n"
"}\n"
"#timeSetup[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/btn_ok_w80_click.png);\n"
"}\n"
"\n"
"#timeSetup[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	background-image:url(:/bit/image/btn_ok_w80_nor.png);\n"
"}\n"
"#timeSetup[pltdismode=\"outdoor\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/btn_ok_w80_click.png);\n"
"}\n"
"\n"
"#timeSetup[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/oK-normal_night.png);\n"
"}\n"
"#timeSetup[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"	background-image: url(:/bit/image/oK-click_night.png);\n"
"}\n"
"\n"
"QPushButton{padding-left:0px;text-align:center;\n"
"color: rgb(255, 255, 255);\n"
"}"));

        retranslateUi(timeSetup);

        QMetaObject::connectSlotsByName(timeSetup);
    } // setupUi

    void retranslateUi(QDialog *timeSetup)
    {
        timeSetup->setWindowTitle(QApplication::translate("timeSetup", "Dialog", 0));
        timeSetup->setProperty("pltdismode", QVariant(QApplication::translate("timeSetup", "indoor", 0)));
        up_hour->setText(QString());
        up_minu->setText(QString());
        up_sec->setText(QString());
        down_hour->setText(QString());
        down_minu->setText(QString());
        down_sec->setText(QString());
        pb_cancel->setText(QApplication::translate("timeSetup", "Cancel", 0));
        pb_ok->setText(QApplication::translate("timeSetup", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class timeSetup: public Ui_timeSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMESETUP_H
