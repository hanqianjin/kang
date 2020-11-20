/********************************************************************************
** Form generated from reading UI file 'sa_widget_markertable.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_WIDGET_MARKERTABLE_H
#define UI_SA_WIDGET_MARKERTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sa_widget_markerTable
{
public:
    QWidget *widget;

    void setupUi(QWidget *sa_widget_markerTable)
    {
        if (sa_widget_markerTable->objectName().isEmpty())
            sa_widget_markerTable->setObjectName(QStringLiteral("sa_widget_markerTable"));
        sa_widget_markerTable->resize(1105, 60);
        sa_widget_markerTable->setStyleSheet(QLatin1String("#widget\n"
"{\n"
"	border:2px;\n"
"	border-bottom-style:solid;\n"
"	border-bottom-color: black;\n"
"   background-color:rgba(72,72,72,0);\n"
"}	\n"
"\n"
"\n"
"/*******************indoor**********************/\n"
"#sa_widget_markerTable[status=\"indoor\"] #widget\n"
"{\n"
"	border-bottom-color: black;\n"
"}\n"
"/*******************outdoor**********************/\n"
"#sa_widget_markerTable[status=\"outdoor\"] #widget\n"
"{\n"
"	border-bottom-color: white;\n"
"}\n"
"/*******************night**********************/\n"
"#sa_widget_markerTable[status=\"night\"] #widget\n"
"{\n"
"	border-bottom-color: rgb(52,8,12);\n"
"}"));
        widget = new QWidget(sa_widget_markerTable);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 1105, 60));

        retranslateUi(sa_widget_markerTable);

        QMetaObject::connectSlotsByName(sa_widget_markerTable);
    } // setupUi

    void retranslateUi(QWidget *sa_widget_markerTable)
    {
        sa_widget_markerTable->setWindowTitle(QApplication::translate("sa_widget_markerTable", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class sa_widget_markerTable: public Ui_sa_widget_markerTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_WIDGET_MARKERTABLE_H
