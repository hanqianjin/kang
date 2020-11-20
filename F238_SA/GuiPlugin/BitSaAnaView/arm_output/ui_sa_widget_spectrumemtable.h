/********************************************************************************
** Form generated from reading UI file 'sa_widget_spectrumemtable.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_WIDGET_SPECTRUMEMTABLE_H
#define UI_SA_WIDGET_SPECTRUMEMTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sa_widget_SpectrumEMTable
{
public:
    QWidget *widget;

    void setupUi(QWidget *sa_widget_SpectrumEMTable)
    {
        if (sa_widget_SpectrumEMTable->objectName().isEmpty())
            sa_widget_SpectrumEMTable->setObjectName(QStringLiteral("sa_widget_SpectrumEMTable"));
        sa_widget_SpectrumEMTable->resize(1105, 180);
        sa_widget_SpectrumEMTable->setStyleSheet(QLatin1String("#widget\n"
"{\n"
"		border:2px;\n"
"	border-bottom-style:solid;\n"
"	border-bottom-color: black;\n"
"   background-color:rgba(72,72,72,0);\n"
"}\n"
"\n"
"/*******************indoor**********************/\n"
"#sa_widget_SpectrumEMTable[status=\"indoor\"] #widget\n"
"{\n"
"	border-bottom-color: black;\n"
"}\n"
"/*******************outdoor**********************/\n"
"#sa_widget_SpectrumEMTable[status=\"outdoor\"] #widget\n"
"{\n"
"	border-bottom-color: white;\n"
"}\n"
"/*******************night**********************/\n"
"#sa_widget_SpectrumEMTable[status=\"night\"] #widget\n"
"{\n"
"	border-bottom-color: rgb(52,8,12);\n"
"}"));
        widget = new QWidget(sa_widget_SpectrumEMTable);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 1105, 180));

        retranslateUi(sa_widget_SpectrumEMTable);

        QMetaObject::connectSlotsByName(sa_widget_SpectrumEMTable);
    } // setupUi

    void retranslateUi(QWidget *sa_widget_SpectrumEMTable)
    {
        sa_widget_SpectrumEMTable->setWindowTitle(QApplication::translate("sa_widget_SpectrumEMTable", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class sa_widget_SpectrumEMTable: public Ui_sa_widget_SpectrumEMTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_WIDGET_SPECTRUMEMTABLE_H
