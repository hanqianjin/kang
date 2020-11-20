/********************************************************************************
** Form generated from reading UI file 'debugdia.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBUGDIA_H
#define UI_DEBUGDIA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_debugdia
{
public:
    QLabel *label_2;
    QPushButton *pushButton_15;
    QLabel *label_8;
    QPushButton *pushButton;
    QLabel *label;
    QSpinBox *spinBox;
    QPushButton *pushButton_2;
    QLabel *label_3;
    QPushButton *pushButton_3;
    QSpinBox *spinBox_2;
    QLabel *label_4;
    QPushButton *pushButton_4;
    QFrame *line;

    void setupUi(QDialog *debugdia)
    {
        if (debugdia->objectName().isEmpty())
            debugdia->setObjectName(QStringLiteral("debugdia"));
        debugdia->resize(1280, 800);
        debugdia->setCursor(QCursor(Qt::ArrowCursor));
        debugdia->setStyleSheet(QStringLiteral("background-color: rgba(238, 238, 236,1);"));
        label_2 = new QLabel(debugdia);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 1, 1278, 45));
        label_2->setStyleSheet(QStringLiteral("background-color: rgba(201, 201, 201,1);"));
        pushButton_15 = new QPushButton(debugdia);
        pushButton_15->setObjectName(QStringLiteral("pushButton_15"));
        pushButton_15->setGeometry(QRect(1211, 1, 45, 45));
        pushButton_15->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/btn_close_30_nor.png);\n"
"}\n"
"QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/btn_close_30_click.png);\n"
"}\n"
"QPushButton { border-style: flat;}\n"
""));
        pushButton_15->setFlat(true);
        label_8 = new QLabel(debugdia);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(30, 13, 261, 22));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        label_8->setFont(font);
        label_8->setStyleSheet(QStringLiteral("background-color: rgba(0, 0, 0,0);"));
        pushButton = new QPushButton(debugdia);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(290, 70, 89, 31));
        label = new QLabel(debugdia);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 80, 101, 20));
        spinBox = new QSpinBox(debugdia);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(130, 68, 111, 41));
        spinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox->setMinimum(1);
        spinBox->setMaximum(16383);
        spinBox->setValue(4758);
        pushButton_2 = new QPushButton(debugdia);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(420, 70, 91, 41));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        pushButton_2->setFont(font1);
        label_3 = new QLabel(debugdia);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 126, 101, 20));
        pushButton_3 = new QPushButton(debugdia);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(290, 120, 89, 31));
        spinBox_2 = new QSpinBox(debugdia);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(130, 114, 111, 41));
        spinBox_2->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox_2->setMinimum(0);
        spinBox_2->setMaximum(31);
        spinBox_2->setValue(0);
        label_4 = new QLabel(debugdia);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(250, 124, 31, 21));
        pushButton_4 = new QPushButton(debugdia);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(420, 120, 91, 41));
        line = new QFrame(debugdia);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(390, 50, 16, 751));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        retranslateUi(debugdia);

        QMetaObject::connectSlotsByName(debugdia);
    } // setupUi

    void retranslateUi(QDialog *debugdia)
    {
        debugdia->setWindowTitle(QApplication::translate("debugdia", "Dialog", Q_NULLPTR));
        label_2->setText(QString());
        pushButton_15->setText(QString());
        label_8->setText(QApplication::translate("debugdia", "Debug Dialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("debugdia", "Setting", Q_NULLPTR));
        label->setText(QApplication::translate("debugdia", "FerqCtrlWord", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("debugdia", "Flat Calc", Q_NULLPTR));
        label_3->setText(QApplication::translate("debugdia", "SecIfAtten", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("debugdia", "Setting", Q_NULLPTR));
        label_4->setText(QApplication::translate("debugdia", "dB", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("debugdia", "Delete Log", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class debugdia: public Ui_debugdia {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBUGDIA_H
