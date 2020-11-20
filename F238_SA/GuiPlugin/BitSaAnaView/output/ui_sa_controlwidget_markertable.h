/********************************************************************************
** Form generated from reading UI file 'sa_controlwidget_markertable.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_CONTROLWIDGET_MARKERTABLE_H
#define UI_SA_CONTROLWIDGET_MARKERTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sa_controlWidget_MarkerTable
{
public:
    QWidget *widget;
    QPushButton *pushButton;

    void setupUi(QWidget *sa_controlWidget_MarkerTable)
    {
        if (sa_controlWidget_MarkerTable->objectName().isEmpty())
            sa_controlWidget_MarkerTable->setObjectName(QStringLiteral("sa_controlWidget_MarkerTable"));
        sa_controlWidget_MarkerTable->resize(93, 60);
        sa_controlWidget_MarkerTable->setStyleSheet(QLatin1String("#widget\n"
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
"/*******************indoor**********************/\n"
"#sa_controlWidget_MarkerTable[status=\"indoor\"] #widget\n"
"{\n"
"	border-bottom-color: black;\n"
"	border-right:30px solid black;\n"
"	background-color:rgba(72,72,72,1);\n"
"}\n"
"/*******************outdoor**********************/\n"
"#sa_controlWidget_MarkerTable[status=\"outdoor\"] #widget\n"
"{\n"
"	border-bottom-color: white;\n"
"	border-right:30px solid white;\n"
"	background-color:rgba(204,204,204,1);\n"
"}\n"
"/*******************night**********************/\n"
"#sa_controlWidget_MarkerTable[status=\"night\"] #widget\n"
"{\n"
""
                        "	border-bottom-color: rgb(52,8,12);\n"
"	border-right:30px solid black;\n"
"	background-color:rgba(251,219,167,1);\n"
"}"));
        widget = new QWidget(sa_controlWidget_MarkerTable);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 95, 60));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(30, 20, 25, 25));

        retranslateUi(sa_controlWidget_MarkerTable);

        QMetaObject::connectSlotsByName(sa_controlWidget_MarkerTable);
    } // setupUi

    void retranslateUi(QWidget *sa_controlWidget_MarkerTable)
    {
        sa_controlWidget_MarkerTable->setWindowTitle(QApplication::translate("sa_controlWidget_MarkerTable", "Form", Q_NULLPTR));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class sa_controlWidget_MarkerTable: public Ui_sa_controlWidget_MarkerTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_CONTROLWIDGET_MARKERTABLE_H
