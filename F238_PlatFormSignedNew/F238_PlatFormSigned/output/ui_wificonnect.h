/********************************************************************************
** Form generated from reading UI file 'wificonnect.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIFICONNECT_H
#define UI_WIFICONNECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <focuslinedit.h>

QT_BEGIN_NAMESPACE

class Ui_WifiConnect
{
public:
    QWidget *widget;
    QLabel *lblTitle;
    QLabel *lblnotice;
    QLabel *label;
    QLabel *lblPassWord;
    focuslinedit *passWordEdit;
    QPushButton *pb_pair;
    QPushButton *pb_cancel;
    QLabel *lblWarning;
    QPushButton *pb_pwView;

    void setupUi(QDialog *WifiConnect)
    {
        if (WifiConnect->objectName().isEmpty())
            WifiConnect->setObjectName(QStringLiteral("WifiConnect"));
        WifiConnect->resize(550, 245);
        WifiConnect->setStyleSheet(QLatin1String("/*\n"
"#WifiConnect[pltdismode=\"indoor\"] #widget\n"
"{\n"
"	background-color:rgba(245, 245, 245, 1);\n"
"}\n"
"#WifiConnect[pltdismode=\"outdoor\"] #widget\n"
"{\n"
"	background-color:rgba(245, 245, 245, 1);\n"
"}\n"
"#WifiConnect[pltdismode=\"night\"] #widget\n"
"{\n"
"	background-color:rgba(241, 210, 160, 1);\n"
"}*/\n"
"#networkset[pltdismode=\"indoor\"] #widget\n"
"{\n"
"	background-color:rgba(245, 245, 245, 1);\n"
"}\n"
"#networkset[pltdismode=\"outdoor\"] #widget\n"
"{\n"
"	background-color:rgba(245, 245, 245, 1);\n"
"}\n"
"#networkset[pltdismode=\"night\"] #widget\n"
"{\n"
"	background-color:rgba(241, 210, 160, 1);\n"
"}\n"
""));
        widget = new QWidget(WifiConnect);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 550, 245));
        lblTitle = new QLabel(widget);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));
        lblTitle->setGeometry(QRect(110, 32, 341, 25));
        lblTitle->setStyleSheet(QLatin1String("	font: 75 22px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(0,0,0,1);\n"
"	background-color:rgba(0,0,0,0);\n"
"\n"
""));
        lblnotice = new QLabel(widget);
        lblnotice->setObjectName(QStringLiteral("lblnotice"));
        lblnotice->setGeometry(QRect(110, 55, 400, 41));
        lblnotice->setStyleSheet(QLatin1String("font:75 17px \"Arial\";\n"
"background-color:rgba(0,0,0,0);"));
        lblnotice->setScaledContents(true);
        lblnotice->setWordWrap(true);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(37, 33, 49, 49));
        label->setStyleSheet(QLatin1String("/*\n"
"#WifiConnect[pltdismode=\"indoor\"] QLabel\n"
"{\n"
"	background-image: url(:/bit/image/Wife.png);\n"
"}\n"
"#WifiConnect[pltdismode=\"outdoor\"] QLabel\n"
"{\n"
"	background-image: url(:/bit/image/Wife.png);\n"
"}\n"
"#WifiConnect[pltdismode=\"night\"] QLabel\n"
"{\n"
"	background-image: url(:/bit/image/Wife_night.png);\n"
"}\n"
"*/\n"
"#networkset[pltdismode=\"indoor\"] QLabel\n"
"{\n"
"	background-image: url(:/bit/image/Wife.png);\n"
"}\n"
"#networkset[pltdismode=\"outdoor\"] QLabel\n"
"{\n"
"	background-image: url(:/bit/image/Wife.png);\n"
"}\n"
"#networkset[pltdismode=\"night\"] QLabel\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	background-image: url(:/bit/image/Wife_night.png);\n"
"}\n"
""));
        lblPassWord = new QLabel(widget);
        lblPassWord->setObjectName(QStringLiteral("lblPassWord"));
        lblPassWord->setGeometry(QRect(110, 115, 81, 17));
        lblPassWord->setStyleSheet(QLatin1String("font:75 13px \"Arial\";\n"
"background-color:rgba(0,0,0,0);"));
        passWordEdit = new focuslinedit(widget);
        passWordEdit->setObjectName(QStringLiteral("passWordEdit"));
        passWordEdit->setGeometry(QRect(174, 106, 336, 34));
        passWordEdit->setStyleSheet(QLatin1String("/*\n"
"#WifiConnect[pltdismode=\"indoor\"] QLineEdit\n"
"{\n"
"	font:75 18px \"Arial\";\n"
"	padding-left:19px;\n"
"	border-image: url(:/bit/image/input_box_w180.png);\n"
"}\n"
"\n"
"#WifiConnect[pltdismode=\"outdoor\"] QLineEdit\n"
"{\n"
"	font:75 18px \"Arial\";\n"
"	padding-left:19px;		\n"
"	border-image: url(:/bit/image/input_box_w180.png);\n"
"}\n"
"\n"
"#WifiConnect[pltdismode=\"night\"] QLineEdit\n"
"{\n"
"	font:75 18px \"Arial\";\n"
"	padding-left:19px;\n"
"	border-image: url(:/bit/image/inputbox_night.png);\n"
"}*/\n"
"\n"
"#networkset[pltdismode=\"indoor\"] QLineEdit\n"
"{\n"
"	font:75 18px \"Arial\";\n"
"	padding-left:19px;\n"
"	border-image: url(:/bit/image/input_box_w180.png);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QLineEdit\n"
"{\n"
"	font:75 18px \"Arial\";\n"
"	padding-left:19px;		\n"
"	border-image: url(:/bit/image/input_box_w180.png);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QLineEdit\n"
"{\n"
"	font:75 18px \"Arial\";\n"
"	padding-left:19px;\n"
"	border-image: url(:/bit/i"
                        "mage/inputbox_night.png);\n"
"}\n"
""));
        passWordEdit->setEchoMode(QLineEdit::Password);
        pb_pair = new QPushButton(widget);
        pb_pair->setObjectName(QStringLiteral("pb_pair"));
        pb_pair->setGeometry(QRect(430, 185, 80, 30));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(11);
        pb_pair->setFont(font);
        pb_pair->setFocusPolicy(Qt::NoFocus);
        pb_pair->setStyleSheet(QLatin1String("/*#WifiConnect[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	border-style: flat;\n"
"	background-image: url(:/bit/image/btn_ok_w80_nor.png);\n"
"}\n"
"#WifiConnect[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/btn_ok_w80_click.png);\n"
"}\n"
"\n"
"#WifiConnect[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	border-style: flat;\n"
"	background-image: url(:/bit/image/btn_ok_w80_nor.png);\n"
"}\n"
"#WifiConnect[pltdismode=\"outdoor\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/btn_ok_w80_click.png);\n"
"}\n"
"\n"
"#WifiConnect[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	border-style: flat;\n"
"	background-image:url(:/bit/image/oK-normal_night.png);\n"
"}\n"
"#WifiConnect[pltdismode=\"night\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/oK-click_night.png);\n"
"}*/\n"
"\n"
"#networkset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	border-style: flat;\n"
"	background-image: url(:/bit/image/btn_ok_w80_nor.png);\n"
"	color:rgba(25"
                        "5,255,255);\n"
"}\n"
"#networkset[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/btn_ok_w80_click.png);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	border-style: flat;\n"
"	background-image: url(:/bit/image/btn_ok_w80_nor.png);\n"
"	color:rgba(255,255,255);\n"
"}\n"
"#networkset[pltdismode=\"outdoor\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/btn_ok_w80_click.png);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	border-style: flat;\n"
"	background-image:url(:/bit/image/oK-normal_night.png);\n"
"	color:rgba(255,255,255);\n"
"}\n"
"#networkset[pltdismode=\"night\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/oK-click_night.png);\n"
"}\n"
""));
        pb_pair->setFlat(true);
        pb_cancel = new QPushButton(widget);
        pb_cancel->setObjectName(QStringLiteral("pb_cancel"));
        pb_cancel->setGeometry(QRect(348, 185, 80, 30));
        pb_cancel->setFont(font);
        pb_cancel->setFocusPolicy(Qt::NoFocus);
        pb_cancel->setLayoutDirection(Qt::LeftToRight);
        pb_cancel->setStyleSheet(QLatin1String("/*\n"
"#WifiConnect[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	border-style: flat;\n"
"	background-image: url(:/bit/image/btn_cancel_w80_nor.png);\n"
"}\n"
"#WifiConnect[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/btn_cancel_w80_click.png);\n"
"}\n"
"\n"
"#WifiConnect[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	border-style: flat;\n"
"	background-image: url(:/bit/image/btn_cancel_w80_nor.png);\n"
"}\n"
"#WifiConnect[pltdismode=\"outdoor\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/btn_cancel_w80_click.png);\n"
"}\n"
"\n"
"#WifiConnect[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	border-style: flat;\n"
"	background-image: url(:/bit/image/cancel-normal_night.png);\n"
"}\n"
"#WifiConnect[pltdismode=\"night\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/cancel-click_night.png);\n"
"}*/\n"
"\n"
"#networkset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	border-style: flat;\n"
"	background-image: url(:/bit/image/btn_cance"
                        "l_w80_nor.png);\n"
"	color:rgba(255,255,255);\n"
"}\n"
"#networkset[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/btn_cancel_w80_click.png);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	border-style: flat;\n"
"	background-image: url(:/bit/image/btn_cancel_w80_nor.png);\n"
"	color:rgba(255,255,255);\n"
"}\n"
"#networkset[pltdismode=\"outdoor\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/btn_cancel_w80_click.png);\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	border-style: flat;\n"
"	background-image: url(:/bit/image/cancel-normal_night.png);\n"
"	color:rgba(255,255,255);\n"
"}\n"
"#networkset[pltdismode=\"night\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/cancel-click_night.png);\n"
"\n"
"}\n"
"\n"
""));
        pb_cancel->setFlat(true);
        lblWarning = new QLabel(widget);
        lblWarning->setObjectName(QStringLiteral("lblWarning"));
        lblWarning->setGeometry(QRect(173, 145, 336, 20));
        lblWarning->setStyleSheet(QLatin1String("color:rgba(250, 15, 30, 1);\n"
"font:75 15px \"Arial\";\n"
"background-color:rgba(0,0,0,0);"));
        pb_pwView = new QPushButton(widget);
        pb_pwView->setObjectName(QStringLiteral("pb_pwView"));
        pb_pwView->setGeometry(QRect(472, 115, 28, 15));
        pb_pwView->setFocusPolicy(Qt::NoFocus);
        pb_pwView->setStyleSheet(QLatin1String("/*#WifiConnect[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	border-image:url(:/bit/image/eyeclose.png);\n"
"	border:flat;\n"
"}\n"
"\n"
"#WifiConnect[pltdismode=\"indoor\"] QPushButton:checked\n"
"{\n"
"	border-image:url(:/bit/image/eyeopen.png);\n"
"	border:flat;\n"
"}\n"
"\n"
"#WifiConnect[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	border-image:url(:/bit/image/eyeclose.png);\n"
"	border:flat;\n"
"}\n"
"\n"
"#WifiConnect[pltdismode=\"outdoor\"] QPushButton:checked\n"
"{\n"
"	border-image:url(:/bit/image/eyeopen.png);\n"
"	border:flat;\n"
"}\n"
"\n"
"#WifiConnect[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	border-image:url(:/bit/image/eyeclose_night.png);\n"
"	border:flat;\n"
"}\n"
"\n"
"#WifiConnect[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"	border-image:url(:/bit/image/eyeopen_night.png);\n"
"	border:flat;\n"
"}*/\n"
"\n"
"#networkset[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	border-image:url(:/bit/image/eyeclose.png);\n"
"	border:flat;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"indoor\"] QP"
                        "ushButton:checked\n"
"{\n"
"	border-image:url(:/bit/image/eyeopen.png);\n"
"	border:flat;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QPushButton\n"
"{\n"
"	border-image:url(:/bit/image/eyeclose.png);\n"
"	border:flat;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"outdoor\"] QPushButton:checked\n"
"{\n"
"	border-image:url(:/bit/image/eyeopen.png);\n"
"	border:flat;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image:url(:/bit/image/eyeclose_night.png);\n"
"	border:flat;\n"
"}\n"
"\n"
"#networkset[pltdismode=\"night\"] QPushButton:checked\n"
"{\n"
"	border-image:url(:/bit/image/eyeopen_night.png);\n"
"	border:flat;\n"
"}\n"
""));
        pb_pwView->setCheckable(true);

        retranslateUi(WifiConnect);

        QMetaObject::connectSlotsByName(WifiConnect);
    } // setupUi

    void retranslateUi(QDialog *WifiConnect)
    {
        WifiConnect->setWindowTitle(QApplication::translate("WifiConnect", "Dialog", Q_NULLPTR));
        WifiConnect->setProperty("pltdismode", QVariant(QApplication::translate("WifiConnect", "indoor", Q_NULLPTR)));
        lblTitle->setText(QApplication::translate("WifiConnect", "Please enter password", Q_NULLPTR));
        lblnotice->setText(QApplication::translate("WifiConnect", "Wi-fi network \342\200\234 ******* \342\200\235 need to enter password.", Q_NULLPTR));
        label->setText(QString());
        lblPassWord->setText(QApplication::translate("WifiConnect", "Password", Q_NULLPTR));
        passWordEdit->setInputMask(QString());
        passWordEdit->setText(QString());
        pb_pair->setText(QApplication::translate("WifiConnect", "OK", Q_NULLPTR));
        pb_cancel->setText(QApplication::translate("WifiConnect", "Cancel", Q_NULLPTR));
        lblWarning->setText(QApplication::translate("WifiConnect", "Connection error, please reconnect.", Q_NULLPTR));
        pb_pwView->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class WifiConnect: public Ui_WifiConnect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIFICONNECT_H
