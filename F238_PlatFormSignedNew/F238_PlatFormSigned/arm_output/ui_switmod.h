/********************************************************************************
** Form generated from reading UI file 'switmod.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SWITMOD_H
#define UI_SWITMOD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_switmod
{
public:
    QWidget *widget;
    QLabel *label_4;

    void setupUi(QWidget *switmod)
    {
        if (switmod->objectName().isEmpty())
            switmod->setObjectName(QStringLiteral("switmod"));
        switmod->setWindowModality(Qt::NonModal);
        switmod->resize(264, 100);
        switmod->setStyleSheet(QStringLiteral("#switmod{background-color: rgba(193,193,193,0.5);}"));
        widget = new QWidget(switmod);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 264, 100));
        widget->setStyleSheet(QStringLiteral("#widget{background-image: url(:/bit/image/temp_box_d.png);}"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(49, 39, 167, 22));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(15);
        label_4->setFont(font);
        label_4->setStyleSheet(QStringLiteral("color: rgba(0, 255, 0,1);"));

        retranslateUi(switmod);

        QMetaObject::connectSlotsByName(switmod);
    } // setupUi

    void retranslateUi(QWidget *switmod)
    {
        switmod->setWindowTitle(QApplication::translate("switmod", "Form", 0));
        label_4->setText(QApplication::translate("switmod", "Changing Mode \342\200\246", 0));
    } // retranslateUi

};

namespace Ui {
    class switmod: public Ui_switmod {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SWITMOD_H
