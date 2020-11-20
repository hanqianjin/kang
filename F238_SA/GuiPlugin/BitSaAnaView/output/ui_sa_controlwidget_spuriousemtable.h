/********************************************************************************
** Form generated from reading UI file 'sa_controlwidget_spuriousemtable.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_CONTROLWIDGET_SPURIOUSEMTABLE_H
#define UI_SA_CONTROLWIDGET_SPURIOUSEMTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sa_ControlWidget_SpuriousEMTable
{
public:
    QWidget *widget;
    QSlider *verticalSlider;
    QPushButton *pushButton;

    void setupUi(QWidget *sa_ControlWidget_SpuriousEMTable)
    {
        if (sa_ControlWidget_SpuriousEMTable->objectName().isEmpty())
            sa_ControlWidget_SpuriousEMTable->setObjectName(QStringLiteral("sa_ControlWidget_SpuriousEMTable"));
        sa_ControlWidget_SpuriousEMTable->resize(95, 120);
        sa_ControlWidget_SpuriousEMTable->setStyleSheet(QLatin1String("#widget\n"
"{\n"
"	border:2px;\n"
"	border-bottom-style:solid;\n"
"	border-bottom-color: black;\n"
"   background-color:rgba(72,72,72,1);\n"
"	border-right:30px solid black;\n"
"}\n"
"QPushButton\n"
"{\n"
"border-style:flat;\n"
"background-color:rgba(0,0,0,0);\n"
"background-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"QPushButton::pressed\n"
"{\n"
"background-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"\n"
"QSlider::groove:vertical {\n"
"        width: 10px;\n"
"        background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(255, 255, 255), stop: 1.0 rgb(255, 255, 255));\n"
"        border-radius:5px;\n"
"}\n"
"QSlider::handle:vertical {\n"
"        width: 8px;\n"
"        background: rgb(72, 72, 72);\n"
"        margin: -20px 0px 10px 0px;\n"
"        border-radius: 4px;\n"
"}\n"
"QSlider:sub-page {\n"
"background-color:  rgb(253, 255, 255);\n"
"}\n"
"\n"
"/*******************indoor**********************/\n"
"#sa_ControlWidget_SpuriousEMTable[status=\"indoor\"] #widget\n"
"{\n"
""
                        "	border-bottom-color: black;\n"
"	border-right:30px solid black;\n"
"	background-color:rgba(72,72,72,1);\n"
"}\n"
"/*******************outdoor**********************/\n"
"#sa_ControlWidget_SpuriousEMTable[status=\"outdoor\"] #widget\n"
"{\n"
"	border-bottom-color: white;\n"
"	border-right:30px solid white;\n"
"	background-color:rgba(204,204,204,1);\n"
"}\n"
"/*******************night**********************/\n"
"#sa_ControlWidget_SpuriousEMTable[status=\"night\"] #widget\n"
"{\n"
"	border-bottom-color: rgb(52,8,12);\n"
"	border-right:30px solid black;\n"
"	background-color:rgba(251,219,167,1);\n"
"}"));
        widget = new QWidget(sa_ControlWidget_SpuriousEMTable);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 95, 120));
        widget->setStyleSheet(QStringLiteral(""));
        verticalSlider = new QSlider(widget);
        verticalSlider->setObjectName(QStringLiteral("verticalSlider"));
        verticalSlider->setGeometry(QRect(0, 15, 20, 90));
        verticalSlider->setOrientation(Qt::Vertical);
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(30, 50, 25, 25));

        retranslateUi(sa_ControlWidget_SpuriousEMTable);

        QMetaObject::connectSlotsByName(sa_ControlWidget_SpuriousEMTable);
    } // setupUi

    void retranslateUi(QWidget *sa_ControlWidget_SpuriousEMTable)
    {
        sa_ControlWidget_SpuriousEMTable->setWindowTitle(QApplication::translate("sa_ControlWidget_SpuriousEMTable", "Form", Q_NULLPTR));
        sa_ControlWidget_SpuriousEMTable->setProperty("status", QVariant(QString()));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class sa_ControlWidget_SpuriousEMTable: public Ui_sa_ControlWidget_SpuriousEMTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_CONTROLWIDGET_SPURIOUSEMTABLE_H
