/********************************************************************************
** Form generated from reading UI file 'sa_widget_spuriousemtable.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_WIDGET_SPURIOUSEMTABLE_H
#define UI_SA_WIDGET_SPURIOUSEMTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sa_widget_SpuriousEMTable
{
public:
    QWidget *widget;

    void setupUi(QWidget *sa_widget_SpuriousEMTable)
    {
        if (sa_widget_SpuriousEMTable->objectName().isEmpty())
            sa_widget_SpuriousEMTable->setObjectName(QStringLiteral("sa_widget_SpuriousEMTable"));
        sa_widget_SpuriousEMTable->resize(1105, 120);
        sa_widget_SpuriousEMTable->setStyleSheet(QLatin1String("#widget\n"
"{\n"
"		border:2px;\n"
"	border-bottom-style:solid;\n"
"	border-bottom-color: black;\n"
"   background-color:rgba(72,72,72,0);\n"
"}\n"
"\n"
"/*******************indoor**********************/\n"
"#sa_widget_SpuriousEMTable[status=\"indoor\"] #widget\n"
"{\n"
"	border-bottom-color: black;\n"
"}\n"
"/*******************outdoor**********************/\n"
"#sa_widget_SpuriousEMTable[status=\"outdoor\"] #widget\n"
"{\n"
"	border-bottom-color: white;\n"
"}\n"
"/*******************night**********************/\n"
"#sa_widget_SpuriousEMTable[status=\"night\"] #widget\n"
"{\n"
"	border-bottom-color:black;\n"
"}"));
        widget = new QWidget(sa_widget_SpuriousEMTable);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 1105, 120));

        retranslateUi(sa_widget_SpuriousEMTable);

        QMetaObject::connectSlotsByName(sa_widget_SpuriousEMTable);
    } // setupUi

    void retranslateUi(QWidget *sa_widget_SpuriousEMTable)
    {
        sa_widget_SpuriousEMTable->setWindowTitle(QApplication::translate("sa_widget_SpuriousEMTable", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class sa_widget_SpuriousEMTable: public Ui_sa_widget_SpuriousEMTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_WIDGET_SPURIOUSEMTABLE_H
