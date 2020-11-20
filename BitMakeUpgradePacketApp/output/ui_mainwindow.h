/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QTableWidget *tableWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit;
    QLabel *label_6;
    QLineEdit *lineEdit_2;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *lineEdit_3;
    QLabel *label_9;
    QFrame *line;
    QTextEdit *textEdit;
    QPushButton *pushButton_2;
    QLabel *label_10;
    QLabel *label_11;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1079, 800);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(549, 690, 101, 31));
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        if (tableWidget->rowCount() < 33)
            tableWidget->setRowCount(33);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setItem(1, 0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setItem(1, 1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setItem(1, 2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setItem(2, 0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setItem(2, 1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setItem(2, 2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setItem(3, 0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setItem(3, 1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setItem(3, 2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setItem(4, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setItem(4, 1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setItem(4, 2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setItem(5, 0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setItem(5, 1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setItem(5, 2, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setItem(6, 0, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setItem(6, 1, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setItem(6, 2, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setItem(7, 0, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setItem(7, 1, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget->setItem(7, 2, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget->setItem(8, 0, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget->setItem(8, 1, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget->setItem(8, 2, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget->setItem(9, 0, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget->setItem(9, 1, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget->setItem(9, 2, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget->setItem(10, 0, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget->setItem(10, 1, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget->setItem(10, 2, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget->setItem(11, 0, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget->setItem(11, 1, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidget->setItem(11, 2, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidget->setItem(12, 0, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tableWidget->setItem(12, 1, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tableWidget->setItem(12, 2, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tableWidget->setItem(13, 0, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tableWidget->setItem(13, 1, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tableWidget->setItem(13, 2, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tableWidget->setItem(14, 0, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tableWidget->setItem(14, 1, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tableWidget->setItem(14, 2, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tableWidget->setItem(15, 0, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tableWidget->setItem(15, 1, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tableWidget->setItem(15, 2, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        tableWidget->setItem(16, 0, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        tableWidget->setItem(16, 1, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        tableWidget->setItem(16, 2, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        tableWidget->setItem(17, 0, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        tableWidget->setItem(17, 1, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        tableWidget->setItem(17, 2, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        tableWidget->setItem(18, 0, __qtablewidgetitem54);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        tableWidget->setItem(18, 1, __qtablewidgetitem55);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        tableWidget->setItem(18, 2, __qtablewidgetitem56);
        QTableWidgetItem *__qtablewidgetitem57 = new QTableWidgetItem();
        tableWidget->setItem(19, 0, __qtablewidgetitem57);
        QTableWidgetItem *__qtablewidgetitem58 = new QTableWidgetItem();
        tableWidget->setItem(19, 1, __qtablewidgetitem58);
        QTableWidgetItem *__qtablewidgetitem59 = new QTableWidgetItem();
        tableWidget->setItem(19, 2, __qtablewidgetitem59);
        QTableWidgetItem *__qtablewidgetitem60 = new QTableWidgetItem();
        tableWidget->setItem(20, 0, __qtablewidgetitem60);
        QTableWidgetItem *__qtablewidgetitem61 = new QTableWidgetItem();
        tableWidget->setItem(20, 1, __qtablewidgetitem61);
        QTableWidgetItem *__qtablewidgetitem62 = new QTableWidgetItem();
        tableWidget->setItem(20, 2, __qtablewidgetitem62);
        QTableWidgetItem *__qtablewidgetitem63 = new QTableWidgetItem();
        tableWidget->setItem(21, 0, __qtablewidgetitem63);
        QTableWidgetItem *__qtablewidgetitem64 = new QTableWidgetItem();
        tableWidget->setItem(21, 1, __qtablewidgetitem64);
        QTableWidgetItem *__qtablewidgetitem65 = new QTableWidgetItem();
        tableWidget->setItem(21, 2, __qtablewidgetitem65);
        QTableWidgetItem *__qtablewidgetitem66 = new QTableWidgetItem();
        tableWidget->setItem(22, 0, __qtablewidgetitem66);
        QTableWidgetItem *__qtablewidgetitem67 = new QTableWidgetItem();
        tableWidget->setItem(22, 1, __qtablewidgetitem67);
        QTableWidgetItem *__qtablewidgetitem68 = new QTableWidgetItem();
        tableWidget->setItem(22, 2, __qtablewidgetitem68);
        QTableWidgetItem *__qtablewidgetitem69 = new QTableWidgetItem();
        tableWidget->setItem(23, 0, __qtablewidgetitem69);
        QTableWidgetItem *__qtablewidgetitem70 = new QTableWidgetItem();
        tableWidget->setItem(23, 1, __qtablewidgetitem70);
        QTableWidgetItem *__qtablewidgetitem71 = new QTableWidgetItem();
        tableWidget->setItem(23, 2, __qtablewidgetitem71);
        QTableWidgetItem *__qtablewidgetitem72 = new QTableWidgetItem();
        tableWidget->setItem(24, 0, __qtablewidgetitem72);
        QTableWidgetItem *__qtablewidgetitem73 = new QTableWidgetItem();
        tableWidget->setItem(24, 1, __qtablewidgetitem73);
        QTableWidgetItem *__qtablewidgetitem74 = new QTableWidgetItem();
        tableWidget->setItem(24, 2, __qtablewidgetitem74);
        QTableWidgetItem *__qtablewidgetitem75 = new QTableWidgetItem();
        tableWidget->setItem(25, 0, __qtablewidgetitem75);
        QTableWidgetItem *__qtablewidgetitem76 = new QTableWidgetItem();
        tableWidget->setItem(25, 1, __qtablewidgetitem76);
        QTableWidgetItem *__qtablewidgetitem77 = new QTableWidgetItem();
        tableWidget->setItem(25, 2, __qtablewidgetitem77);
        QTableWidgetItem *__qtablewidgetitem78 = new QTableWidgetItem();
        tableWidget->setItem(26, 0, __qtablewidgetitem78);
        QTableWidgetItem *__qtablewidgetitem79 = new QTableWidgetItem();
        tableWidget->setItem(26, 1, __qtablewidgetitem79);
        QTableWidgetItem *__qtablewidgetitem80 = new QTableWidgetItem();
        tableWidget->setItem(26, 2, __qtablewidgetitem80);
        QTableWidgetItem *__qtablewidgetitem81 = new QTableWidgetItem();
        tableWidget->setItem(27, 0, __qtablewidgetitem81);
        QTableWidgetItem *__qtablewidgetitem82 = new QTableWidgetItem();
        tableWidget->setItem(27, 1, __qtablewidgetitem82);
        QTableWidgetItem *__qtablewidgetitem83 = new QTableWidgetItem();
        tableWidget->setItem(27, 2, __qtablewidgetitem83);
        QTableWidgetItem *__qtablewidgetitem84 = new QTableWidgetItem();
        tableWidget->setItem(28, 0, __qtablewidgetitem84);
        QTableWidgetItem *__qtablewidgetitem85 = new QTableWidgetItem();
        tableWidget->setItem(28, 1, __qtablewidgetitem85);
        QTableWidgetItem *__qtablewidgetitem86 = new QTableWidgetItem();
        tableWidget->setItem(28, 2, __qtablewidgetitem86);
        QTableWidgetItem *__qtablewidgetitem87 = new QTableWidgetItem();
        tableWidget->setItem(29, 0, __qtablewidgetitem87);
        QTableWidgetItem *__qtablewidgetitem88 = new QTableWidgetItem();
        tableWidget->setItem(29, 1, __qtablewidgetitem88);
        QTableWidgetItem *__qtablewidgetitem89 = new QTableWidgetItem();
        tableWidget->setItem(29, 2, __qtablewidgetitem89);
        QTableWidgetItem *__qtablewidgetitem90 = new QTableWidgetItem();
        tableWidget->setItem(30, 0, __qtablewidgetitem90);
        QTableWidgetItem *__qtablewidgetitem91 = new QTableWidgetItem();
        tableWidget->setItem(30, 1, __qtablewidgetitem91);
        QTableWidgetItem *__qtablewidgetitem92 = new QTableWidgetItem();
        tableWidget->setItem(30, 2, __qtablewidgetitem92);
        QTableWidgetItem *__qtablewidgetitem93 = new QTableWidgetItem();
        tableWidget->setItem(31, 0, __qtablewidgetitem93);
        QTableWidgetItem *__qtablewidgetitem94 = new QTableWidgetItem();
        tableWidget->setItem(31, 1, __qtablewidgetitem94);
        QTableWidgetItem *__qtablewidgetitem95 = new QTableWidgetItem();
        tableWidget->setItem(31, 2, __qtablewidgetitem95);
        QTableWidgetItem *__qtablewidgetitem96 = new QTableWidgetItem();
        tableWidget->setItem(32, 0, __qtablewidgetitem96);
        QTableWidgetItem *__qtablewidgetitem97 = new QTableWidgetItem();
        tableWidget->setItem(32, 1, __qtablewidgetitem97);
        QTableWidgetItem *__qtablewidgetitem98 = new QTableWidgetItem();
        tableWidget->setItem(32, 2, __qtablewidgetitem98);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(50, 111, 431, 631));
        tableWidget->setRowCount(33);
        tableWidget->setColumnCount(3);
        tableWidget->horizontalHeader()->setVisible(false);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(170, 10, 91, 61));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QStringLiteral("color: rgb(78, 154, 6);"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 90, 67, 17));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(160, 90, 67, 17));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(290, 90, 67, 17));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(360, 20, 67, 41));
        label_5->setFont(font);
        label_5->setStyleSheet(QStringLiteral("color: rgb(78, 154, 6);"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(599, 634, 113, 31));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(549, 640, 41, 17));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(599, 594, 113, 31));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(529, 600, 61, 20));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(529, 556, 61, 20));
        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(599, 550, 113, 31));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(549, 420, 181, 111));
        label_9->setStyleSheet(QStringLiteral("color: rgb(239, 41, 41);"));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(712, 90, 41, 641));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setEnabled(true);
        textEdit->setGeometry(QRect(750, 100, 311, 611));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(750, 50, 141, 31));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(96, 30, 71, 20));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(300, 30, 67, 17));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1079, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "UpgradesTool", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Make Pakcet", Q_NULLPTR));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem = tableWidget->item(0, 0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "BitGradeApp", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->item(0, 1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->item(0, 2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->item(1, 0);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "drivers", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->item(1, 1);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->item(1, 2);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->item(2, 0);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "bitup", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->item(2, 1);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->item(2, 2);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->item(3, 0);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "info", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->item(3, 1);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->item(3, 2);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->item(4, 0);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "bit", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->item(4, 1);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->item(4, 2);
        ___qtablewidgetitem14->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->item(5, 0);
        ___qtablewidgetitem15->setText(QApplication::translate("MainWindow", "fla", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->item(5, 1);
        ___qtablewidgetitem16->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->item(5, 2);
        ___qtablewidgetitem17->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->item(6, 0);
        ___qtablewidgetitem18->setText(QApplication::translate("MainWindow", "ini", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->item(6, 1);
        ___qtablewidgetitem19->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->item(6, 2);
        ___qtablewidgetitem20->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->item(7, 0);
        ___qtablewidgetitem21->setText(QApplication::translate("MainWindow", "txt", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget->item(7, 1);
        ___qtablewidgetitem22->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget->item(7, 2);
        ___qtablewidgetitem23->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget->item(8, 0);
        ___qtablewidgetitem24->setText(QApplication::translate("MainWindow", "pres", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget->item(8, 1);
        ___qtablewidgetitem25->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget->item(8, 2);
        ___qtablewidgetitem26->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget->item(9, 0);
        ___qtablewidgetitem27->setText(QApplication::translate("MainWindow", "cond", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget->item(9, 1);
        ___qtablewidgetitem28->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget->item(9, 2);
        ___qtablewidgetitem29->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget->item(10, 0);
        ___qtablewidgetitem30->setText(QApplication::translate("MainWindow", "wav", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget->item(10, 1);
        ___qtablewidgetitem31->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget->item(10, 2);
        ___qtablewidgetitem32->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget->item(11, 0);
        ___qtablewidgetitem33->setText(QApplication::translate("MainWindow", "pm", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget->item(11, 1);
        ___qtablewidgetitem34->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget->item(11, 2);
        ___qtablewidgetitem35->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidget->item(12, 0);
        ___qtablewidgetitem36->setText(QApplication::translate("MainWindow", "so", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem37 = tableWidget->item(12, 1);
        ___qtablewidgetitem37->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem38 = tableWidget->item(12, 2);
        ___qtablewidgetitem38->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem39 = tableWidget->item(13, 0);
        ___qtablewidgetitem39->setText(QApplication::translate("MainWindow", "sh", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem40 = tableWidget->item(13, 1);
        ___qtablewidgetitem40->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem41 = tableWidget->item(13, 2);
        ___qtablewidgetitem41->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem42 = tableWidget->item(14, 0);
        ___qtablewidgetitem42->setText(QApplication::translate("MainWindow", "msg", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem43 = tableWidget->item(14, 1);
        ___qtablewidgetitem43->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem44 = tableWidget->item(14, 2);
        ___qtablewidgetitem44->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem45 = tableWidget->item(15, 0);
        ___qtablewidgetitem45->setText(QApplication::translate("MainWindow", "bmp", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem46 = tableWidget->item(15, 1);
        ___qtablewidgetitem46->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem47 = tableWidget->item(15, 2);
        ___qtablewidgetitem47->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem48 = tableWidget->item(16, 0);
        ___qtablewidgetitem48->setText(QApplication::translate("MainWindow", "BitPlatFormApp", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem49 = tableWidget->item(16, 1);
        ___qtablewidgetitem49->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem50 = tableWidget->item(16, 2);
        ___qtablewidgetitem50->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem51 = tableWidget->item(17, 0);
        ___qtablewidgetitem51->setText(QApplication::translate("MainWindow", "HomeApp", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem52 = tableWidget->item(17, 1);
        ___qtablewidgetitem52->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem53 = tableWidget->item(17, 2);
        ___qtablewidgetitem53->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem54 = tableWidget->item(18, 0);
        ___qtablewidgetitem54->setText(QApplication::translate("MainWindow", "SysCtrl", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem55 = tableWidget->item(18, 1);
        ___qtablewidgetitem55->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem56 = tableWidget->item(18, 2);
        ___qtablewidgetitem56->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem57 = tableWidget->item(19, 0);
        ___qtablewidgetitem57->setText(QApplication::translate("MainWindow", "SaCtrlApp", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem58 = tableWidget->item(19, 1);
        ___qtablewidgetitem58->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem59 = tableWidget->item(19, 2);
        ___qtablewidgetitem59->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem60 = tableWidget->item(20, 0);
        ___qtablewidgetitem60->setText(QApplication::translate("MainWindow", "RtsaCtrlApp", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem61 = tableWidget->item(20, 1);
        ___qtablewidgetitem61->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem62 = tableWidget->item(20, 2);
        ___qtablewidgetitem62->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem63 = tableWidget->item(21, 0);
        ___qtablewidgetitem63->setText(QApplication::translate("MainWindow", "LTE_FDD_CTL", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem64 = tableWidget->item(21, 1);
        ___qtablewidgetitem64->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem65 = tableWidget->item(21, 2);
        ___qtablewidgetitem65->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem66 = tableWidget->item(22, 0);
        ___qtablewidgetitem66->setText(QApplication::translate("MainWindow", "LTE_TDD_CTL", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem67 = tableWidget->item(22, 1);
        ___qtablewidgetitem67->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem68 = tableWidget->item(22, 2);
        ___qtablewidgetitem68->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem69 = tableWidget->item(23, 0);
        ___qtablewidgetitem69->setText(QApplication::translate("MainWindow", "CalcNotic", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem70 = tableWidget->item(23, 1);
        ___qtablewidgetitem70->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem71 = tableWidget->item(23, 2);
        ___qtablewidgetitem71->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem72 = tableWidget->item(24, 0);
        ___qtablewidgetitem72->setText(QApplication::translate("MainWindow", "SaCalcAnaApp", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem73 = tableWidget->item(24, 1);
        ___qtablewidgetitem73->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem74 = tableWidget->item(24, 2);
        ___qtablewidgetitem74->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem75 = tableWidget->item(25, 0);
        ___qtablewidgetitem75->setText(QApplication::translate("MainWindow", "routemap", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem76 = tableWidget->item(25, 1);
        ___qtablewidgetitem76->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem77 = tableWidget->item(25, 2);
        ___qtablewidgetitem77->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem78 = tableWidget->item(26, 0);
        ___qtablewidgetitem78->setText(QApplication::translate("MainWindow", "NR_CTL", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem79 = tableWidget->item(26, 1);
        ___qtablewidgetitem79->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem80 = tableWidget->item(26, 2);
        ___qtablewidgetitem80->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem81 = tableWidget->item(27, 0);
        ___qtablewidgetitem81->setText(QApplication::translate("MainWindow", "RtsaCalcAnaApp", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem82 = tableWidget->item(27, 1);
        ___qtablewidgetitem82->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem83 = tableWidget->item(27, 2);
        ___qtablewidgetitem83->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem84 = tableWidget->item(28, 0);
        ___qtablewidgetitem84->setText(QApplication::translate("MainWindow", "google", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem85 = tableWidget->item(28, 1);
        ___qtablewidgetitem85->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem86 = tableWidget->item(28, 2);
        ___qtablewidgetitem86->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem87 = tableWidget->item(29, 0);
        ___qtablewidgetitem87->setText(QApplication::translate("MainWindow", "dtb", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem88 = tableWidget->item(29, 1);
        ___qtablewidgetitem88->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem89 = tableWidget->item(29, 2);
        ___qtablewidgetitem89->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem90 = tableWidget->item(30, 0);
        ___qtablewidgetitem90->setText(QApplication::translate("MainWindow", "uImage", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem91 = tableWidget->item(30, 1);
        ___qtablewidgetitem91->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem92 = tableWidget->item(30, 2);
        ___qtablewidgetitem92->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem93 = tableWidget->item(31, 0);
        ___qtablewidgetitem93->setText(QApplication::translate("MainWindow", "BOOT.bin", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem94 = tableWidget->item(31, 1);
        ___qtablewidgetitem94->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem95 = tableWidget->item(31, 2);
        ___qtablewidgetitem95->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem96 = tableWidget->item(32, 0);
        ___qtablewidgetitem96->setText(QApplication::translate("MainWindow", "rtl8188eufw.bin", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem97 = tableWidget->item(32, 1);
        ___qtablewidgetitem97->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem98 = tableWidget->item(32, 2);
        ___qtablewidgetitem98->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        tableWidget->setSortingEnabled(__sortingEnabled);

        label->setText(QApplication::translate("MainWindow", "File Folder:0\n"
"File:1\n"
"Extension:2", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Items", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Property", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Update", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Yes:1\n"
"No:0", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("MainWindow", "20191204", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Date", Q_NULLPTR));
        lineEdit_2->setText(QApplication::translate("MainWindow", "V0.0.1", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Sversion", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Hversion", Q_NULLPTR));
        lineEdit_3->setText(QApplication::translate("MainWindow", "A0.1.0", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", " Sversion/Hversion\n"
" should be managed \n"
" through database", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Read Configure", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "Property:", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "Update:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
