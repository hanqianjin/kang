/********************************************************************************
** Form generated from reading UI file 'sa_widget_occupiedxdbtable.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_WIDGET_OCCUPIEDXDBTABLE_H
#define UI_SA_WIDGET_OCCUPIEDXDBTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sa_widget_OccupiedXdBTable
{
public:
    QWidget *widget;

    void setupUi(QWidget *sa_widget_OccupiedXdBTable)
    {
        if (sa_widget_OccupiedXdBTable->objectName().isEmpty())
            sa_widget_OccupiedXdBTable->setObjectName(QStringLiteral("sa_widget_OccupiedXdBTable"));
        sa_widget_OccupiedXdBTable->resize(1105, 130);
        sa_widget_OccupiedXdBTable->setStyleSheet(QLatin1String("#widget\n"
"{\n"
"	border:2px;\n"
"	border-bottom-style:solid;\n"
"	border-bottom-color: black;\n"
"   background-color:rgba(72,72,72,0);\n"
"}	\n"
"\n"
"/*******************indoor**********************/\n"
"#sa_widget_OccupiedXdBTable[status=\"indoor\"] #widget\n"
"{\n"
"	border-bottom-color: black;\n"
"}\n"
"/*******************outdoor**********************/\n"
"#sa_widget_OccupiedXdBTable[status=\"outdoor\"] #widget\n"
"{\n"
"	border-bottom-color: white;\n"
"}\n"
"/*******************night**********************/\n"
"#sa_widget_OccupiedXdBTable[status=\"night\"] #widget\n"
"{\n"
"	border-bottom-color: rgb(52,8,12);\n"
"}"));
        widget = new QWidget(sa_widget_OccupiedXdBTable);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 1105, 130));

        retranslateUi(sa_widget_OccupiedXdBTable);

        QMetaObject::connectSlotsByName(sa_widget_OccupiedXdBTable);
    } // setupUi

    void retranslateUi(QWidget *sa_widget_OccupiedXdBTable)
    {
        sa_widget_OccupiedXdBTable->setWindowTitle(QApplication::translate("sa_widget_OccupiedXdBTable", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class sa_widget_OccupiedXdBTable: public Ui_sa_widget_OccupiedXdBTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_WIDGET_OCCUPIEDXDBTABLE_H
