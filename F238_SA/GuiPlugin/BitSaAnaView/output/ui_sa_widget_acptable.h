/********************************************************************************
** Form generated from reading UI file 'sa_widget_acptable.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_WIDGET_ACPTABLE_H
#define UI_SA_WIDGET_ACPTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sa_widget_ACPTable
{
public:
    QWidget *widget;

    void setupUi(QWidget *sa_widget_ACPTable)
    {
        if (sa_widget_ACPTable->objectName().isEmpty())
            sa_widget_ACPTable->setObjectName(QStringLiteral("sa_widget_ACPTable"));
        sa_widget_ACPTable->resize(1105, 125);
        sa_widget_ACPTable->setWindowOpacity(1);
        sa_widget_ACPTable->setStyleSheet(QLatin1String("#widget\n"
"{\n"
"	border:2px;\n"
"	border-bottom-style:solid;\n"
"	border-bottom-color: black;\n"
"   background-color:rgba(72,72,72,0);\n"
"}	\n"
"\n"
"/*******************indoor**********************/\n"
"#sa_widget_ACPTable[status=\"indoor\"] #widget\n"
"{\n"
"	border-bottom-color: black;\n"
"}\n"
"/*******************outdoor**********************/\n"
"#sa_widget_ACPTable[status=\"outdoor\"] #widget\n"
"{\n"
"	border-bottom-color: white;\n"
"}\n"
"/*******************night**********************/\n"
"#sa_widget_ACPTable[status=\"night\"] #widget\n"
"{\n"
"	border-bottom-color: rgb(52,8,12);\n"
"}"));
        widget = new QWidget(sa_widget_ACPTable);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 1105, 125));

        retranslateUi(sa_widget_ACPTable);

        QMetaObject::connectSlotsByName(sa_widget_ACPTable);
    } // setupUi

    void retranslateUi(QWidget *sa_widget_ACPTable)
    {
        sa_widget_ACPTable->setWindowTitle(QApplication::translate("sa_widget_ACPTable", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class sa_widget_ACPTable: public Ui_sa_widget_ACPTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_WIDGET_ACPTABLE_H
