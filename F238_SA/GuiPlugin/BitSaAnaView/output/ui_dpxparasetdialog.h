/********************************************************************************
** Form generated from reading UI file 'dpxparasetdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DPXPARASETDIALOG_H
#define UI_DPXPARASETDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DPXParaSetDialog
{
public:
    QLabel *label;
    QComboBox *dpxEnablecomboBox;
    QComboBox *persistenceModecomboBox;
    QLabel *label_2;
    QComboBox *bitmapExtraccomboBox;
    QLabel *label_3;
    QComboBox *bitmapCtrlcomboBox;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *persistenceTimelineEdit;
    QLineEdit *acquireTimelineEdit;
    QLineEdit *highestDensitylineEdit;
    QLineEdit *lowestDensitylineEdit;
    QLabel *label_9;
    QLabel *label_10;
    QPushButton *OKbutton;
    QPushButton *Cancelbutton;
    QLabel *label_11;
    QLabel *label_12;

    void setupUi(QDialog *DPXParaSetDialog)
    {
        if (DPXParaSetDialog->objectName().isEmpty())
            DPXParaSetDialog->setObjectName(QStringLiteral("DPXParaSetDialog"));
        DPXParaSetDialog->resize(702, 297);
        label = new QLabel(DPXParaSetDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 20, 91, 17));
        dpxEnablecomboBox = new QComboBox(DPXParaSetDialog);
        dpxEnablecomboBox->setObjectName(QStringLiteral("dpxEnablecomboBox"));
        dpxEnablecomboBox->setGeometry(QRect(200, 20, 121, 25));
        persistenceModecomboBox = new QComboBox(DPXParaSetDialog);
        persistenceModecomboBox->setObjectName(QStringLiteral("persistenceModecomboBox"));
        persistenceModecomboBox->setGeometry(QRect(200, 70, 121, 25));
        label_2 = new QLabel(DPXParaSetDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 70, 141, 21));
        bitmapExtraccomboBox = new QComboBox(DPXParaSetDialog);
        bitmapExtraccomboBox->setObjectName(QStringLiteral("bitmapExtraccomboBox"));
        bitmapExtraccomboBox->setGeometry(QRect(200, 170, 121, 25));
        label_3 = new QLabel(DPXParaSetDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(50, 120, 101, 17));
        bitmapCtrlcomboBox = new QComboBox(DPXParaSetDialog);
        bitmapCtrlcomboBox->setObjectName(QStringLiteral("bitmapCtrlcomboBox"));
        bitmapCtrlcomboBox->setGeometry(QRect(200, 120, 121, 25));
        label_4 = new QLabel(DPXParaSetDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(50, 170, 141, 21));
        label_5 = new QLabel(DPXParaSetDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(360, 120, 131, 17));
        label_6 = new QLabel(DPXParaSetDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(360, 170, 141, 21));
        label_7 = new QLabel(DPXParaSetDialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(360, 20, 131, 17));
        label_8 = new QLabel(DPXParaSetDialog);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(360, 70, 141, 21));
        persistenceTimelineEdit = new QLineEdit(DPXParaSetDialog);
        persistenceTimelineEdit->setObjectName(QStringLiteral("persistenceTimelineEdit"));
        persistenceTimelineEdit->setGeometry(QRect(510, 20, 113, 25));
        acquireTimelineEdit = new QLineEdit(DPXParaSetDialog);
        acquireTimelineEdit->setObjectName(QStringLiteral("acquireTimelineEdit"));
        acquireTimelineEdit->setGeometry(QRect(510, 70, 113, 25));
        highestDensitylineEdit = new QLineEdit(DPXParaSetDialog);
        highestDensitylineEdit->setObjectName(QStringLiteral("highestDensitylineEdit"));
        highestDensitylineEdit->setGeometry(QRect(510, 120, 113, 25));
        lowestDensitylineEdit = new QLineEdit(DPXParaSetDialog);
        lowestDensitylineEdit->setObjectName(QStringLiteral("lowestDensitylineEdit"));
        lowestDensitylineEdit->setGeometry(QRect(510, 170, 113, 25));
        label_9 = new QLabel(DPXParaSetDialog);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(640, 20, 41, 17));
        label_10 = new QLabel(DPXParaSetDialog);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(640, 70, 41, 17));
        OKbutton = new QPushButton(DPXParaSetDialog);
        OKbutton->setObjectName(QStringLiteral("OKbutton"));
        OKbutton->setGeometry(QRect(160, 240, 89, 25));
        Cancelbutton = new QPushButton(DPXParaSetDialog);
        Cancelbutton->setObjectName(QStringLiteral("Cancelbutton"));
        Cancelbutton->setGeometry(QRect(400, 240, 89, 25));
        label_11 = new QLabel(DPXParaSetDialog);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(640, 120, 41, 17));
        label_12 = new QLabel(DPXParaSetDialog);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(640, 170, 41, 17));

        retranslateUi(DPXParaSetDialog);

        QMetaObject::connectSlotsByName(DPXParaSetDialog);
    } // setupUi

    void retranslateUi(QDialog *DPXParaSetDialog)
    {
        DPXParaSetDialog->setWindowTitle(QApplication::translate("DPXParaSetDialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("DPXParaSetDialog", "DPX Enable:", Q_NULLPTR));
        dpxEnablecomboBox->setCurrentText(QString());
        persistenceModecomboBox->setCurrentText(QString());
        label_2->setText(QApplication::translate("DPXParaSetDialog", "Persistence Mode:", Q_NULLPTR));
        bitmapExtraccomboBox->setCurrentText(QString());
        label_3->setText(QApplication::translate("DPXParaSetDialog", "Bitmap Clear:", Q_NULLPTR));
        bitmapCtrlcomboBox->setCurrentText(QString());
        label_4->setText(QApplication::translate("DPXParaSetDialog", "Bitmap Extrac:", Q_NULLPTR));
        label_5->setText(QApplication::translate("DPXParaSetDialog", "Highest Density:", Q_NULLPTR));
        label_6->setText(QApplication::translate("DPXParaSetDialog", "Lowest Density:", Q_NULLPTR));
        label_7->setText(QApplication::translate("DPXParaSetDialog", "Persistence Time:", Q_NULLPTR));
        label_8->setText(QApplication::translate("DPXParaSetDialog", "Acquire Time:", Q_NULLPTR));
        label_9->setText(QApplication::translate("DPXParaSetDialog", "s", Q_NULLPTR));
        label_10->setText(QApplication::translate("DPXParaSetDialog", "s", Q_NULLPTR));
        OKbutton->setText(QApplication::translate("DPXParaSetDialog", "OK", Q_NULLPTR));
        Cancelbutton->setText(QApplication::translate("DPXParaSetDialog", "Cancel", Q_NULLPTR));
        label_11->setText(QApplication::translate("DPXParaSetDialog", "%", Q_NULLPTR));
        label_12->setText(QApplication::translate("DPXParaSetDialog", "%", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DPXParaSetDialog: public Ui_DPXParaSetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DPXPARASETDIALOG_H
