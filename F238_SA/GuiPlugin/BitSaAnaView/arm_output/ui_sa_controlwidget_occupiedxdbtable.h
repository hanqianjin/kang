/********************************************************************************
** Form generated from reading UI file 'sa_controlwidget_occupiedxdbtable.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_CONTROLWIDGET_OCCUPIEDXDBTABLE_H
#define UI_SA_CONTROLWIDGET_OCCUPIEDXDBTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sa_controlWidget_OccupiedXdBTable
{
public:
    QWidget *widget;
    QSlider *verticalSlider;
    QPushButton *pushButton;

    void setupUi(QWidget *sa_controlWidget_OccupiedXdBTable)
    {
        if (sa_controlWidget_OccupiedXdBTable->objectName().isEmpty())
            sa_controlWidget_OccupiedXdBTable->setObjectName(QStringLiteral("sa_controlWidget_OccupiedXdBTable"));
        sa_controlWidget_OccupiedXdBTable->resize(93, 130);
        sa_controlWidget_OccupiedXdBTable->setStyleSheet(QLatin1String("#widget\n"
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
"/*******************indoor**********************/\n"
"#sa_controlWidget_OccupiedXdBTable[status=\"indoor\"] #widget\n"
"{\n"
"	"
                        "border-bottom-color: black;\n"
"	border-right:30px solid black;\n"
"	background-color:rgba(72,72,72,1);\n"
"}\n"
"/*******************outdoor**********************/\n"
"#sa_controlWidget_OccupiedXdBTable[status=\"outdoor\"] #widget\n"
"{\n"
"	border-bottom-color: white;\n"
"	border-right:30px solid white;\n"
"	background-color:rgba(204,204,204,1);\n"
"}\n"
"/*******************night**********************/\n"
"#sa_controlWidget_OccupiedXdBTable[status=\"night\"] #widget\n"
"{\n"
"	border-bottom-color: rgb(52,8,12);\n"
"	border-right:30px solid black;\n"
"	background-color:rgba(251,219,167,1);\n"
"}"));
        widget = new QWidget(sa_controlWidget_OccupiedXdBTable);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 95, 130));
        verticalSlider = new QSlider(widget);
        verticalSlider->setObjectName(QStringLiteral("verticalSlider"));
        verticalSlider->setGeometry(QRect(0, 25, 20, 80));
        verticalSlider->setOrientation(Qt::Vertical);
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(30, 55, 25, 25));

        retranslateUi(sa_controlWidget_OccupiedXdBTable);

        QMetaObject::connectSlotsByName(sa_controlWidget_OccupiedXdBTable);
    } // setupUi

    void retranslateUi(QWidget *sa_controlWidget_OccupiedXdBTable)
    {
        sa_controlWidget_OccupiedXdBTable->setWindowTitle(QApplication::translate("sa_controlWidget_OccupiedXdBTable", "Form", 0));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class sa_controlWidget_OccupiedXdBTable: public Ui_sa_controlWidget_OccupiedXdBTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_CONTROLWIDGET_OCCUPIEDXDBTABLE_H
