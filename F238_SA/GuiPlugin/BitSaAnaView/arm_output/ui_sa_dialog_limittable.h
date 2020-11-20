/********************************************************************************
** Form generated from reading UI file 'sa_dialog_limittable.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_LIMITTABLE_H
#define UI_SA_DIALOG_LIMITTABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <sa_customedTablewidget.h>
#include <sa_lineedit.h>

QT_BEGIN_NAMESPACE

class Ui_SA_Dialog_LimitTable
{
public:
    QWidget *widget;
    QLabel *lblTitle;
    QFrame *line;
    QPushButton *pb_cancel;
    QPushButton *pb_InsertRow;
    QPushButton *pb_DeleteRow;
    QPushButton *pb_DeleteLimit;
    ClickableTableWidget *tableWidget;
    QLabel *lblFreq;
    QLabel *lblAmpt;
    QLabel *lblCurRowIndex;
    SA_LineEdit *LED_CurPtIndex;

    void setupUi(QWidget *SA_Dialog_LimitTable)
    {
        if (SA_Dialog_LimitTable->objectName().isEmpty())
            SA_Dialog_LimitTable->setObjectName(QStringLiteral("SA_Dialog_LimitTable"));
        SA_Dialog_LimitTable->resize(252, 646);
        SA_Dialog_LimitTable->setStyleSheet(QLatin1String("#widget\n"
"{\n"
"background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#widget>#lblTitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}\n"
"SA_LineEdit,\n"
"SA_LineEdit:disable\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"	padding:8px 8px 7px 10px ;\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"SA_LineEdit:focus\n"
"{\n"
"	outline: none;\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"#pb_cancel\n"
"{\n"
"border-style:flat;\n"
"background-color:rgba(0,0,0,0);\n"
"border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"#line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"QPushButton\n"
"{\n"
"	color:rgba(255, 255, 255, 1);\n"
"	border-style:flat;\n"
"	font: 75 13px \"Arial\";\n"
"}\n"
"\n"
"#widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"}\n"
"\n"
"/**"
                        "*****************indoor**********************/\n"
"#SA_Dialog_LimitTable[status  =  \"indoor\"] #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#SA_Dialog_LimitTable[status  =  \"indoor\"] #widget>#lblTitle\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"indoor\"] SA_LineEdit,\n"
"#SA_Dialog_LimitTable[status  =  \"indoor\"] SA_LineEdit:disable\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"indoor\"] SA_LineEdit:focus\n"
"{\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"#SA_Dialog_LimitTable[status  =  \"indoor\"] #pb_cancel\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_LimitTable[status  =  \"indoor\"] #pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"#SA_Dialog_LimitTable[status  =  \"indoor\"] #line\n"
"{\n"
"	background-color"
                        ":rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_LimitTable[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	color:rgba(255, 255, 255, 1);\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"indoor\"] #widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"}\n"
"\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_LimitTable[status  =  \"outdoor\"] #widget\n"
"{\n"
"	background-color:rgba(211,211,211,0.9);\n"
"}\n"
"#SA_Dialog_LimitTable[status  =  \"outdoor\"] #widget>#lblTitle\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"outdoor\"] SA_LineEdit,\n"
"#SA_Dialog_LimitTable[status  =  \"outdoor\"] SA_LineEdit:disable\n"
"{\n"
"	background:rgba(255,255,255,1);\n"
"	color:rgba(162, 115, 0,1);\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"outdoor\"] SA_LineEdit:focus\n"
"{\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"#SA_Dialog_LimitTable[status  =  \"outdoor\"] #pb_cancel\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-"
                        "image: url(:/sa/image/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_LimitTable[status  =  \"outdoor\"] #pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/btn_close_click.png);\n"
"}\n"
"#SA_Dialog_LimitTable[status  =  \"outdoor\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_LimitTable[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	color:rgba(255, 255, 255, 1);\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"outdoor\"] #widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"}\n"
"\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_LimitTable[status  =  \"night\"] #widget\n"
"{\n"
"		background-color:rgba(208,182,139,0.9);\n"
"}\n"
"#SA_Dialog_LimitTable[status  =  \"night\"] #widget>#lblTitle\n"
"{\n"
"	color:rgba(46,46,46,1);\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"night\"] SA_LineEdit,\n"
"#SA_Dialog_LimitTable[status  =  \"night\"] SA_LineEdit:disable\n"
"{\n"
"	background:rgba(251,219,167,0.6);\n"
"	color:rgba(162, 115, 0,1);\n"
"}\n"
"\n"
""
                        "#SA_Dialog_LimitTable[status  =  \"night\"] SA_LineEdit:focus\n"
"{\n"
"	border:2px solid rgba(162,115,0,1);\n"
"	padding:6px 6px 5px 8px ;\n"
"}\n"
"#SA_Dialog_LimitTable[status  =  \"night\"] #pb_cancel\n"
"{\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-image: url(:/sa/image/night/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_LimitTable[status  =  \"night\"] #pb_cancel:pressed\n"
"{\n"
"border-image: url(:/sa/image/night/btn_close_click.png);\n"
"}\n"
"#SA_Dialog_LimitTable[status  =  \"night\"] #line\n"
"{\n"
"	background-color:rgba(46,46,46,1);\n"
"}\n"
"#SA_Dialog_LimitTable[status  =  \"night\"] QPushButton\n"
"{\n"
"	color:rgba(255, 255, 255, 1);\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"night\"] #widget>QLabel\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"}\n"
""));
        widget = new QWidget(SA_Dialog_LimitTable);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 252, 646));
        lblTitle = new QLabel(widget);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));
        lblTitle->setGeometry(QRect(17, 19, 102, 22));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        lblTitle->setFont(font);
        lblTitle->setStyleSheet(QLatin1String("#lblTitle\n"
"{\n"
"	font: 75 20px \"Arial\";\n"
"	color:rgba(46,46,46,1);\n"
"	line-height:23px;\n"
"	font-weight:bold;\n"
"}"));
        line = new QFrame(widget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(18, 46, 212, 2));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        pb_cancel = new QPushButton(widget);
        pb_cancel->setObjectName(QStringLiteral("pb_cancel"));
        pb_cancel->setGeometry(QRect(212, 6, 35, 35));
        pb_cancel->setStyleSheet(QStringLiteral(""));
        pb_InsertRow = new QPushButton(widget);
        pb_InsertRow->setObjectName(QStringLiteral("pb_InsertRow"));
        pb_InsertRow->setGeometry(QRect(18, 67, 106, 50));
        pb_InsertRow->setFocusPolicy(Qt::NoFocus);
        pb_InsertRow->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_LimitTable[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(255, 255, 255, 1);\n"
"	text-align:center;\n"
"	background-image: url(:/sa/image/btn_w106_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"indoor\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_w106_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_LimitTable[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	text-align:center;\n"
"	color:rgba(0, 0, 0, 1);\n"
"	border-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/sa/image/btn_w106_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_LimitTable[status  =  \"night\"] QPushButton\n"
"{\n"
"	font: 75 13px "
                        "\"Arial\";\n"
"	font-weight:bold;\n"
"	color: #FBDBA7;\n"
"	text-align:center;\n"
"	border-image: url(:/sa/image/btn_w106_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"night\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/sa/image/night/btn_w216_click.png);\n"
"}"));
        pb_DeleteRow = new QPushButton(widget);
        pb_DeleteRow->setObjectName(QStringLiteral("pb_DeleteRow"));
        pb_DeleteRow->setGeometry(QRect(128, 67, 106, 50));
        pb_DeleteRow->setFocusPolicy(Qt::NoFocus);
        pb_DeleteRow->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_LimitTable[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(255, 255, 255, 1);\n"
"	text-align:center;\n"
"	background-image: url(:/sa/image/btn_w106_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"indoor\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_w106_click.png);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_LimitTable[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	text-align:center;\n"
"	color:rgba(0, 0, 0, 1);\n"
"	border-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"outdoor\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/sa/image/btn_w106_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_LimitTable[status  =  \"night\"] QPushButton\n"
"{\n"
"	font: 75 13px "
                        "\"Arial\";\n"
"	font-weight:bold;\n"
"	color: #FBDBA7;\n"
"	text-align:center;\n"
"	border-image: url(:/sa/image/btn_w106_nor.png);\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"night\"] QPushButton:pressed\n"
"{\n"
"	border-image: url(:/sa/image/night/btn_w216_click.png);\n"
"}"));
        pb_DeleteLimit = new QPushButton(widget);
        pb_DeleteLimit->setObjectName(QStringLiteral("pb_DeleteLimit"));
        pb_DeleteLimit->setGeometry(QRect(18, 595, 216, 30));
        pb_DeleteLimit->setStyleSheet(QLatin1String("/*******************indoor**********************/\n"
"#SA_Dialog_LimitTable[status  =  \"indoor\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(255, 255, 255, 1);\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"	text-align:center;\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"indoor\"] QPushButton:pressed\n"
"{\n"
"	\n"
"	background-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_LimitTable[status  =  \"outdoor\"] QPushButton\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color:rgba(0, 0, 0, 1);\n"
"	border-image: url(:/sa/image/outdoor/btn_w70_normal.png);\n"
"	text-align:center;\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"outdoor\"] QPushButton:pressed\n"
"{\n"
"	\n"
"	border-image: url(:/sa/image/btn_w216_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_LimitTable[status  =  \"night\"] QPushButton\n"
"{\n"
""
                        "	font: 75 13px \"Arial\";\n"
"	font-weight:bold;\n"
"	color: #FBDBA7;\n"
"	background-image: url(:/sa/image/btn_w216_nor.png);\n"
"	text-align:center;\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"night\"] QPushButton:pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/btn_w216_click.png);\n"
"}"));
        tableWidget = new ClickableTableWidget(widget);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidget->rowCount() < 3)
            tableWidget->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem4);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(8, 208, 224, 370));
        tableWidget->setFocusPolicy(Qt::StrongFocus);
        tableWidget->setStyleSheet(QLatin1String("\n"
"QTableWidget QHeaderView { \n"
"	font:75 13px  \"Arial\";\n"
"    text-align:left;\n"
"	border-style:flat;\n"
"	background-color:rgba(255,0,0,0);\n"
"}	\n"
"QTableWidget QHeaderView::section::item { \n"
"	text-align:left;\n"
"	border-style:flat;\n"
"	background-color:rgba(211,211,211,0.1);\n"
"}	\n"
"QTableWidget\n"
"{\n"
"	font: 75 13px \"Arial\";\n"
"	font-weight:bold;		\n"
"	background-color:rgba(211,211,211,0.1);\n"
"	border-style:flat;\n"
"	outline:0px;\n"
"}\n"
"\n"
"QTableWidget::item\n"
"{\n"
"	border-style:flat;\n"
"	color:rgba(162, 115, 0, 1);\n"
"	padding-left:10px;\n"
"	margin:2px 2px 2px 2px;\n"
"	background-color:rgba(255,255,255,0.6);\n"
"}\n"
"\n"
"QScrollBar:vertical {\n"
"	background-color:rgba(145, 145, 145, 1);\n"
"	width:14px;\n"
"	border-radius:6px; \n"
"}\n"
"QScrollBar::handle:vertical {\n"
"	border:2px solid rgba(145, 145, 145, 1);\n"
"	background-color:rgba(235, 235, 235, 1);\n"
"	width:8px;\n"
"	border-radius:6px; \n"
"}\n"
"QScrollBar::add-line:vertical {\n"
"	height:0px;\n"
"	"
                        "subcontrol-position:bottom;\n"
"	subcontrol-origin:margin;\n"
"}\n"
"QScrollBar::sub-line:vertical {\n"
"	height:0px;\n"
"	subcontrol-position:top;\n"
"	subcontrol-origin:margin;\n"
"}\n"
"\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_LimitTable[status  =  \"indoor\"] QTableWidget QHeaderView \n"
"{ \n"
"	background-color:rgba(255,0,0,0);\n"
"}	\n"
"#SA_Dialog_LimitTable[status  =  \"indoor\"] QTableWidget QHeaderView::section::item \n"
"{ \n"
"	background-color:rgba(211,211,211,0.1);\n"
"}	\n"
"#SA_Dialog_LimitTable[status  =  \"indoor\"] QTableWidget\n"
"{\n"
"	background-color:rgba(211,211,211,0.1);\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"indoor\"] QTableWidget::item\n"
"{\n"
"	color:rgba(162, 115, 0, 1);\n"
"	background-color:rgba(255,255,255,0.6);\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"indoor\"] QScrollBar:vertical\n"
"{\n"
"	background-color:rgba(145, 145, 145, 1);\n"
"}\n"
"#SA_Dialog_LimitTable[status  =  \"indoor\"] QScrollBar::handle:vertical\n"
" {\n"
"	b"
                        "order:2px solid rgba(145, 145, 145, 1);\n"
"	background-color:rgba(235, 235, 235, 1);\n"
"}\n"
"\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_LimitTable[status  =  \"outdoor\"] QTableWidget QHeaderView \n"
"{ \n"
"	background-color:rgba(255,0,0,0);\n"
"}	\n"
"#SA_Dialog_LimitTable[status  =  \"outdoor\"] QTableWidget QHeaderView::section::item \n"
"{ \n"
"	background-color:rgba(211,211,211,0.1);\n"
"}	\n"
"#SA_Dialog_LimitTable[status  =  \"outdoor\"] QTableWidget\n"
"{\n"
"	background-color:rgba(211,211,211,0.1);\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"outdoor\"] QTableWidget::item\n"
"{\n"
"	color:rgba(162, 115, 0, 1);\n"
"	background-color:rgba(255,255,255,0.6);\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"outdoor\"] QScrollBar:vertical\n"
"{\n"
"	background-color:rgba(145, 145, 145, 1);\n"
"}\n"
"#SA_Dialog_LimitTable[status  =  \"outdoor\"] QScrollBar::handle:vertical\n"
" {\n"
"	border:2px solid rgba(145, 145, 145, 1);\n"
"	background-color:rgba(235, 235, 235, 1);\n"
""
                        "}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_LimitTable[status  =  \"night\"] QTableWidget QHeaderView \n"
"{ \n"
"	background-color:rgba(255,0,0,0);\n"
"}	\n"
"#SA_Dialog_LimitTable[status  =  \"night\"] QTableWidget QHeaderView::section::item \n"
"{ \n"
"	background-color:rgba(211,211,211,0.1);\n"
"}	\n"
"#SA_Dialog_LimitTable[status  =  \"night\"] QTableWidget\n"
"{\n"
"	background-color:rgba(211,211,211,0.1);\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"night\"] QTableWidget::item\n"
"{\n"
"	color:rgba(162, 115, 0, 1);\n"
"	background-color:rgba(255,255,255,0.6);\n"
"}\n"
"\n"
"#SA_Dialog_LimitTable[status  =  \"night\"] QScrollBar:vertical\n"
"{\n"
"	background-color:rgba(145, 145, 145, 1);\n"
"}\n"
"#SA_Dialog_LimitTable[status  =  \"night\"] QScrollBar::handle:vertical\n"
" {\n"
"	border:2px solid rgba(145, 145, 145, 1);\n"
"	background-color:rgba(235, 235, 235, 1);\n"
"}\n"
""));
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setShowGrid(false);
        tableWidget->setColumnCount(2);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(84);
        tableWidget->horizontalHeader()->setHighlightSections(false);
        tableWidget->horizontalHeader()->setMinimumSectionSize(34);
        tableWidget->horizontalHeader()->setStretchLastSection(false);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setHighlightSections(true);
        lblFreq = new QLabel(widget);
        lblFreq->setObjectName(QStringLiteral("lblFreq"));
        lblFreq->setGeometry(QRect(16, 174, 91, 30));
        lblFreq->setStyleSheet(QStringLiteral("padding-left:5px;"));
        lblAmpt = new QLabel(widget);
        lblAmpt->setObjectName(QStringLiteral("lblAmpt"));
        lblAmpt->setGeometry(QRect(108, 174, 121, 30));
        lblAmpt->setStyleSheet(QStringLiteral("padding-left:5px;"));
        lblCurRowIndex = new QLabel(widget);
        lblCurRowIndex->setObjectName(QStringLiteral("lblCurRowIndex"));
        lblCurRowIndex->setGeometry(QRect(18, 133, 81, 30));
        LED_CurPtIndex = new SA_LineEdit(widget);
        LED_CurPtIndex->setObjectName(QStringLiteral("LED_CurPtIndex"));
        LED_CurPtIndex->setGeometry(QRect(128, 133, 106, 30));
        LED_CurPtIndex->setFocusPolicy(Qt::StrongFocus);
        LED_CurPtIndex->setReadOnly(true);

        retranslateUi(SA_Dialog_LimitTable);

        QMetaObject::connectSlotsByName(SA_Dialog_LimitTable);
    } // setupUi

    void retranslateUi(QWidget *SA_Dialog_LimitTable)
    {
        SA_Dialog_LimitTable->setWindowTitle(QApplication::translate("SA_Dialog_LimitTable", "Form", 0));
        SA_Dialog_LimitTable->setProperty("status", QVariant(QApplication::translate("SA_Dialog_LimitTable", "night", 0)));
        lblTitle->setText(QApplication::translate("SA_Dialog_LimitTable", "Edit Limit", 0));
        pb_cancel->setText(QString());
        pb_InsertRow->setText(QApplication::translate("SA_Dialog_LimitTable", "Insert\n"
"Row Below", 0));
        pb_DeleteRow->setText(QApplication::translate("SA_Dialog_LimitTable", "Delete\n"
"Row", 0));
        pb_DeleteLimit->setText(QApplication::translate("SA_Dialog_LimitTable", "Delete Limit", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SA_Dialog_LimitTable", "1", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("SA_Dialog_LimitTable", "1", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QApplication::translate("SA_Dialog_LimitTable", "2", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem3->setText(QApplication::translate("SA_Dialog_LimitTable", "3", 0));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->item(0, 0);
        ___qtablewidgetitem4->setText(QApplication::translate("SA_Dialog_LimitTable", "123", 0));
        tableWidget->setSortingEnabled(__sortingEnabled);

        lblFreq->setText(QApplication::translate("SA_Dialog_LimitTable", "Frequency\n"
"(MHz)", 0));
        lblAmpt->setText(QApplication::translate("SA_Dialog_LimitTable", "Amplitude \n"
"(dBm)", 0));
        lblCurRowIndex->setText(QApplication::translate("SA_Dialog_LimitTable", "Current\n"
"Row Index", 0));
    } // retranslateUi

};

namespace Ui {
    class SA_Dialog_LimitTable: public Ui_SA_Dialog_LimitTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_LIMITTABLE_H
