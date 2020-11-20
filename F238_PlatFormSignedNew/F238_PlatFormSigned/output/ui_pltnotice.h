/********************************************************************************
** Form generated from reading UI file 'pltnotice.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLTNOTICE_H
#define UI_PLTNOTICE_H

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

class Ui_pltnotice
{
public:
    QWidget *widget_2;
    QPushButton *pushButtoncancel;
    QLabel *Warning;
    QLabel *Title;
    QLabel *label;
    QPushButton *pushButtonok;
    QLabel *label_2;
    focuslinedit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QDialog *pltnotice)
    {
        if (pltnotice->objectName().isEmpty())
            pltnotice->setObjectName(QStringLiteral("pltnotice"));
        pltnotice->resize(550, 170);
        pltnotice->setWindowOpacity(1);
        pltnotice->setStyleSheet(QLatin1String("#widget\n"
"{\n"
"	background-image: url(:/bit/image/popup_box_w550.png);\n"
"	background-color: rgba(245, 245, 245,0);\n"
"}"));
        widget_2 = new QWidget(pltnotice);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(0, 0, 550, 170));
        widget_2->setCursor(QCursor(Qt::BlankCursor));
        widget_2->setStyleSheet(QLatin1String("QLabel\n"
"{\n"
"background-color:transparent;\n"
"}\n"
"#pltnotice[pltdismode=\"night\"] #widget_2\n"
"{	\n"
"background-color: rgb(243, 212, 161);\n"
"border-radius:5px;\n"
"}\n"
"#pltnotice[pltdismode=\"indoor\"] #widget_2\n"
"{	\n"
"background-color: rgb(245, 245, 245);\n"
"border-radius:5px;\n"
"}\n"
""));
        pushButtoncancel = new QPushButton(widget_2);
        pushButtoncancel->setObjectName(QStringLiteral("pushButtoncancel"));
        pushButtoncancel->setGeometry(QRect(358, 118, 80, 30));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(13);
        pushButtoncancel->setFont(font);
        pushButtoncancel->setLayoutDirection(Qt::LeftToRight);
        pushButtoncancel->setStyleSheet(QLatin1String("#pltnotice[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/btn_cancel_w80_nor.png);\n"
"}\n"
"#pltnotice[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/btn_cancel_w80_click.png);\n"
"}\n"
"\n"
"#pltnotice[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/cancel-normal_night.png);\n"
"}\n"
"#pltnotice[pltdismode=\"night\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/cancel-click_night.png);\n"
"}\n"
"\n"
"QPushButton { border-style: flat;\n"
"color: rgb(255, 255, 255);\n"
"}\n"
""));
        pushButtoncancel->setFlat(true);
        Warning = new QLabel(widget_2);
        Warning->setObjectName(QStringLiteral("Warning"));
        Warning->setGeometry(QRect(120, 73, 411, 22));
        Warning->setStyleSheet(QStringLiteral("font:75 18px \"Arial\";"));
        Title = new QLabel(widget_2);
        Title->setObjectName(QStringLiteral("Title"));
        Title->setGeometry(QRect(120, 38, 311, 22));
        Title->setStyleSheet(QLatin1String("font:75 20px \"Arial\";\n"
"font-weight:bold;"));
        label = new QLabel(widget_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(44, 37, 60, 60));
        label->setStyleSheet(QLatin1String("#pltnotice[pltdismode=\"indoor\"] QLabel\n"
"{\n"
"	border-image: url(:/bit/image/notice.png);\n"
"}\n"
"#pltnotice[pltdismode=\"night\"] QLabel\n"
"{	\n"
"	border-image: url(:/bit/image/icn_notice_night.png);\n"
"}"));
        pushButtonok = new QPushButton(widget_2);
        pushButtonok->setObjectName(QStringLiteral("pushButtonok"));
        pushButtonok->setGeometry(QRect(440, 118, 80, 30));
        pushButtonok->setFont(font);
        pushButtonok->setStyleSheet(QLatin1String("#pltnotice[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/btn_ok_w80_nor.png);\n"
"}\n"
"#pltnotice[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/btn_ok_w80_click.png);\n"
"}\n"
"\n"
"#pltnotice[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/oK-normal_night.png);\n"
"}\n"
"#pltnotice[pltdismode=\"night\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/oK-click_night.png);\n"
"}\n"
"QPushButton { border-style: flat;\n"
"\n"
"color: rgb(255, 255, 255);\n"
"}"));
        pushButtonok->setFlat(true);
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(210, 102, 151, 17));
        label_2->setStyleSheet(QStringLiteral("color: rgb(239, 41, 41);"));
        lineEdit = new focuslinedit(widget_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(210, 67, 311, 34));
        lineEdit->setCursor(QCursor(Qt::BlankCursor));
        lineEdit->setStyleSheet(QLatin1String("#pltnotice[pltdismode=\"indoor\"] #lineEdit\n"
"{	\n"
"background-color: white;\n"
"color:black;\n"
"}\n"
"#pltnotice[pltdismode=\"night\"] #lineEdit\n"
"{	\n"
"background-color: rgb(243, 212, 161);\n"
"color:rgba(0, 42, 93, 1)\n"
"}\n"
"QLineEdit\n"
"{\n"
"padding-left:10px;text-align:left;\n"
"}"));
        lineEdit->setMaxLength(51);
        lineEdit->setEchoMode(QLineEdit::Password);
        lineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(480, 73, 33, 22));
        pushButton->setStyleSheet(QLatin1String("#pltnotice[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	border-image: url(:/bit/image/eyeclose_night.png);\n"
"}\n"
"QPushButton{border: none;}"));
        pushButton->setFlat(true);

        retranslateUi(pltnotice);

        QMetaObject::connectSlotsByName(pltnotice);
    } // setupUi

    void retranslateUi(QDialog *pltnotice)
    {
        pltnotice->setWindowTitle(QApplication::translate("pltnotice", "Dialog", Q_NULLPTR));
        pltnotice->setProperty("pltdismode", QVariant(QApplication::translate("pltnotice", "indoor", Q_NULLPTR)));
        pushButtoncancel->setText(QApplication::translate("pltnotice", "Cancel", Q_NULLPTR));
        Warning->setText(QApplication::translate("pltnotice", "Are you sure to save current state to \342\200\234User\342\200\235?", Q_NULLPTR));
        Title->setText(QApplication::translate("pltnotice", "Notice", Q_NULLPTR));
        label->setText(QString());
        pushButtonok->setText(QApplication::translate("pltnotice", "OK", Q_NULLPTR));
        label_2->setText(QApplication::translate("pltnotice", "Password failed!", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("pltnotice", "123456", Q_NULLPTR));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class pltnotice: public Ui_pltnotice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLTNOTICE_H
