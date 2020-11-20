/********************************************************************************
** Form generated from reading UI file 'noticmsg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTICMSG_H
#define UI_NOTICMSG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_noticmsg
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTableWidget *tableWidget;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *noticmsg)
    {
        if (noticmsg->objectName().isEmpty())
            noticmsg->setObjectName(QStringLiteral("noticmsg"));
        noticmsg->setEnabled(true);
        noticmsg->resize(550, 275);
        noticmsg->setStyleSheet(QLatin1String("#noticmsg[pltdismode=\"indoor\"] \n"
"{\n"
"background-color: rgba(243, 243, 243,1);\n"
"}\n"
"#noticmsg[pltdismode=\"night\"] \n"
"{\n"
"background-color: rgba(241, 210, 160,1);\n"
"}\n"
"\n"
"QPushButton { border-style: flat;}\n"
"QPushButton{padding-left:0px;text-align:center;\n"
"color: rgb(255, 255, 255);\n"
"}"));
        pushButton = new QPushButton(noticmsg);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(430, 225, 80, 30));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(13);
        pushButton->setFont(font);
        pushButton->setStyleSheet(QLatin1String("#noticmsg[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/btn_ok_w80_nor.png);\n"
"}\n"
"#noticmsg[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/btn_ok_w80_click.png);\n"
"}\n"
"\n"
"#noticmsg[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/oK-normal_night.png);\n"
"}\n"
"#noticmsg[pltdismode=\"night\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/oK-click_night.png);\n"
"}"));
        pushButton_2 = new QPushButton(noticmsg);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(348, 225, 80, 30));
        pushButton_2->setFont(font);
        pushButton_2->setStyleSheet(QLatin1String("#noticmsg[pltdismode=\"indoor\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/btn_cancel_w80_nor.png);\n"
"}\n"
"#noticmsg[pltdismode=\"indoor\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/btn_cancel_w80_click.png);\n"
"}\n"
"\n"
"#noticmsg[pltdismode=\"night\"] QPushButton\n"
"{\n"
"	background-image: url(:/bit/image/cancel-normal_night.png);\n"
"}\n"
"#noticmsg[pltdismode=\"night\"] QPushButton:pressed\n"
"{	\n"
"	background-image: url(:/bit/image/cancel-click_night.png);\n"
"}"));
        tableWidget = new QTableWidget(noticmsg);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget->rowCount() < 5)
            tableWidget->setRowCount(5);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem10);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEnabled(true);
        tableWidget->setGeometry(QRect(22, 30, 513, 175));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(15);
        tableWidget->setFont(font1);
        tableWidget->setFocusPolicy(Qt::NoFocus);
        tableWidget->setStyleSheet(QLatin1String("#noticmsg[pltdismode=\"indoor\"] QTableWidget\n"
"{\n"
"border:none;\n"
"alternate-background-color: rgba(243, 243, 243,1);	\n"
"background-color: rgba(255, 255, 255,1);\n"
"}\n"
"\n"
"#noticmsg[pltdismode=\"night\"] QTableWidget\n"
"{\n"
"border:none;\n"
"alternate-background-color: rgba(241, 210, 160,1);	\n"
"background-color: rgba(251, 219, 167,1);\n"
"}\n"
"\n"
"#noticmsg[pltdismode=\"indoor\"] QScrollBar:vertical {\n"
"background-color: rgba(145, 145, 145,1);\n"
"  width:12px;\n"
"  border-radius:6px; \n"
"}\n"
"\n"
"#noticmsg[pltdismode=\"night\"] QScrollBar:vertical {\n"
"background-color: rgba(142, 124, 94,1);\n"
"  width:12px;\n"
"  border-radius:6px; \n"
"}\n"
"\n"
"#noticmsg[pltdismode=\"indoor\"] QScrollBar::handle:vertical {\n"
"  border:2px solid rgba(145, 145, 145, 1);\n"
"  background-color:rgba(235, 235, 235, 1);\n"
"  width:8px;\n"
"  border-radius:6px; \n"
"}\n"
"\n"
"#noticmsg[pltdismode=\"night\"] QScrollBar::handle:vertical {\n"
"  border:2px solid rgba(145, 145, 145, 1);\n"
"  background"
                        "-color:rgba(231, 201, 153, 1);\n"
"  width:8px;\n"
"  border-radius:6px; \n"
"}\n"
"\n"
"QScrollBar::add-line:vertical {\n"
"  height:0px;\n"
"  subcontrol-position:bottom;\n"
"  subcontrol-origin:margin;\n"
"}\n"
"QScrollBar::sub-line:vertical {\n"
"  height:0px;\n"
"  subcontrol-position:top;\n"
"  subcontrol-origin:margin;\n"
"}"));
        tableWidget->setLineWidth(0);
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setAutoScroll(true);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setProperty("showDropIndicator", QVariant(true));
        tableWidget->setAlternatingRowColors(true);
        tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setShowGrid(false);
        tableWidget->setWordWrap(true);
        tableWidget->setCornerButtonEnabled(false);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(100);
        tableWidget->horizontalHeader()->setHighlightSections(false);
        tableWidget->horizontalHeader()->setStretchLastSection(false);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setHighlightSections(false);
        label = new QLabel(noticmsg);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(518, 30, 21, 175));
        label->setStyleSheet(QLatin1String("#noticmsg[pltdismode=\"indoor\"] QLabel\n"
"{\n"
"	background-color: rgba(243, 243, 243,1);\n"
"}\n"
"#noticmsg[pltdismode=\"night\"] QLabel\n"
"{\n"
"	background-color: rgba(241, 210, 160,1);\n"
"}"));
        label_2 = new QLabel(noticmsg);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 206, 451, 17));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(11);
        font2.setBold(true);
        font2.setWeight(75);
        label_2->setFont(font2);
        label_2->setStyleSheet(QLatin1String("color: rgb(239, 41, 41);\n"
"background-color: rgba(255, 255, 255,0);"));

        retranslateUi(noticmsg);

        QMetaObject::connectSlotsByName(noticmsg);
    } // setupUi

    void retranslateUi(QWidget *noticmsg)
    {
        noticmsg->setWindowTitle(QApplication::translate("noticmsg", "Form", Q_NULLPTR));
        noticmsg->setProperty("pltdismode", QVariant(QApplication::translate("noticmsg", "indoor", Q_NULLPTR)));
        pushButton->setText(QApplication::translate("noticmsg", "Close", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("noticmsg", "ClearAll", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("noticmsg", "New Column", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("noticmsg", "New Column", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("noticmsg", "New Column", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("noticmsg", "New Row", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("noticmsg", "New Row", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("noticmsg", "New Row", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem6->setText(QApplication::translate("noticmsg", "New Row", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem7->setText(QApplication::translate("noticmsg", "New Row", Q_NULLPTR));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        tableWidget->setSortingEnabled(__sortingEnabled);

        label->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class noticmsg: public Ui_noticmsg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTICMSG_H
