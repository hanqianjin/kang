/********************************************************************************
** Form generated from reading UI file 'sa_dialog_ch_std.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_CH_STD_H
#define UI_SA_DIALOG_CH_STD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SA_Dialog_CH_Std
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_title;
    QHBoxLayout *horizontalLayout;
    QLabel *lblTitle;
    QSpacerItem *horizontalSpacer;
    QPushButton *pb_close;
    QWidget *widget_main;
    QPushButton *pb_CDMA;
    QPushButton *pb_GSM;
    QPushButton *pb_LTEFDD;
    QPushButton *pb_LTETDD;
    QPushButton *pb_TD;
    QPushButton *pb_WCDMA;
    QPushButton *pb_WIMAX;
    QLabel *label_2;
    QTableWidget *tableWidget;
    QPushButton *pb_up;
    QPushButton *pb_down;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QFrame *line_5;
    QPushButton *pb_cancel;
    QPushButton *pb_ok;

    void setupUi(QWidget *SA_Dialog_CH_Std)
    {
        if (SA_Dialog_CH_Std->objectName().isEmpty())
            SA_Dialog_CH_Std->setObjectName(QStringLiteral("SA_Dialog_CH_Std"));
        SA_Dialog_CH_Std->resize(1196, 645);
        SA_Dialog_CH_Std->setLayoutDirection(Qt::LeftToRight);
        SA_Dialog_CH_Std->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(SA_Dialog_CH_Std);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_title = new QWidget(SA_Dialog_CH_Std);
        widget_title->setObjectName(QStringLiteral("widget_title"));
        widget_title->setMinimumSize(QSize(0, 46));
        widget_title->setMaximumSize(QSize(16777215, 46));
        widget_title->setStyleSheet(QLatin1String("\n"
"/*******************indoor**********************/\n"
"#SA_Dialog_CH_Std[status=\"indoor\"] #widget_title\n"
"{\n"
"	background-color:rgba(201,201,201,1);\n"
"   border:1px;\n"
"   border-bottom-style:solid;\n"
"	border-bottom-color:rgba(76,76,76,1);\n"
"}\n"
"#SA_Dialog_CH_Std[status=\"indoor\"] #widget_title>#pb_close\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/outdoor/btn_close_45_nor.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status=\"indoor\"] #widget_title>#pb_close:pressed\n"
"{\n"
"	background-image: url(:/sa/image/outdoor/btn_close_45_click.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status=\"indoor\"] #widget_title>#lblTitle\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	font:75 20px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_CH_Std[status=\"outdoor\"] #widget_title\n"
"{\n"
"	background-color:rgba(201,201,201,1);\n"
"   border:1px;\n"
"   border-bottom-style:solid;\n"
"	border-bottom-color:rgba(76,76,76,1);\n"
"}\n"
"#SA_Dialog_CH_Std[st"
                        "atus=\"outdoor\"] #widget_title>#pb_close\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/outdoor/btn_close_45_nor.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status=\"outdoor\"] #widget_title>#pb_close:pressed\n"
"{\n"
"	background-image: url(:/sa/image/outdoor/btn_close_45_click.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status=\"outdoor\"] #widget_title>#lblTitle\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	font:75 20px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_CH_Std[status=\"night\"] #widget_title\n"
"{\n"
"	background-color:rgba(53,46,35,1);\n"
"   border:1px;\n"
"   border-bottom-style:solid;\n"
"	border-bottom-color:rgba(76,76,76,1);\n"
"}\n"
"#SA_Dialog_CH_Std[status=\"night\"] #widget_title>#pb_close\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/night/btn_close_45_normal.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status=\"night\"] #widget_title>#pb_close:pressed\n"
"{\n"
"	background-image: url(:/sa/image/night/btn_close_45_cli"
                        "ck.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status=\"night\"] #widget_title>#lblTitle\n"
"{\n"
"	color:rgba(250,218,166,1);\n"
"	font:75 20px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"\n"
"\n"
"\n"
"/*******************indoor**********************/ \n"
"/*\n"
"#SA_Dialog_CH_Std[status = \"indoor\"] #widget_title\n"
"{\n"
"	background-color:rgba(201,201,201,1);\n"
"	border-bottom:1px solid rgba(0,0,0,1);\n"
"}\n"
"#SA_Dialog_CH_Std[status=\"indoor\"] #widget_title>#pb_close\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/btn_close_w30_normal.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status=\"indoor\"] #widget_title>#pb_close:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_close_w30_click.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status=\"indoor\"] #widget_title>#lblTitle\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	font:75 20px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"*/\n"
"/*******************outdoor**********************/\n"
"/*\n"
"#SA_Dialog_CH_Std[status=\"outdoor\"] #widget_title\n"
"{\n"
"	background-col"
                        "or:rgba(201,201,201,1);\n"
"	border-bottom:1px solid rgba(0,0,0,1);\n"
"}\n"
"#SA_Dialog_CH_Std[status=\"outdoor\"] #widget_title>#pb_close\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/btn_close_w30_normal.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status=\"outdoor\"] #widget_title>#pb_close:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_close_w30_click.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status=\"outdoor\"] #widget_title>#lblTitle\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	font:75 20px \"Arial\";\n"
"	font-weight:bold;\n"
"}*/\n"
"/*******************night**********************/\n"
"/*\n"
"#SA_Dialog_CH_Std[status=\"night\"] #widget_title\n"
"{\n"
"	background-color: rgb(197,172,131);\n"
"	border-bottom:1px solid rgba(0,0,0,1);\n"
"}\n"
"#SA_Dialog_CH_Std[status=\"night\"] #widget_title>#pb_close\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/night/btn_close_normal.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status=\"night\"] #widget_title>#pb_close:pressed\n"
"{\n"
"	background-image: "
                        "url(:/sa/image/night/btn_close_click.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status=\"night\"] #widget_title>#lblTitle\n"
"{\n"
"	color:rgb(0,0,0);\n"
"	font:75 20px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"*/\n"
""));
        horizontalLayout = new QHBoxLayout(widget_title);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(28, 0, 13, 0);
        lblTitle = new QLabel(widget_title);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));
        lblTitle->setMinimumSize(QSize(228, 46));
        lblTitle->setMaximumSize(QSize(228, 46));

        horizontalLayout->addWidget(lblTitle);

        horizontalSpacer = new QSpacerItem(875, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pb_close = new QPushButton(widget_title);
        pb_close->setObjectName(QStringLiteral("pb_close"));
        pb_close->setMinimumSize(QSize(45, 45));
        pb_close->setMaximumSize(QSize(45, 45));

        horizontalLayout->addWidget(pb_close);


        verticalLayout->addWidget(widget_title);

        widget_main = new QWidget(SA_Dialog_CH_Std);
        widget_main->setObjectName(QStringLiteral("widget_main"));
        widget_main->setLayoutDirection(Qt::LeftToRight);
        widget_main->setStyleSheet(QLatin1String("/*******************indoor**********************/ \n"
"#SA_Dialog_CH_Std[status = \"indoor\"] #widget_main\n"
"{\n"
"	background-color:rgba(255,255,255,1);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"indoor\"] #widget_main>QLabel\n"
"{\n"
"	color:rgba(6, 62, 97, 1);\n"
"	font:75 15px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"indoor\"] #widget_main>#pb_up\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/btn_up_normal.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"indoor\"] #widget_main>#pb_up:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_up_click.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"indoor\"] #widget_main>#pb_down\n"
"{\n"
"border-style:flat;\n"
"	background-image: url(:/sa/image/btn_down_normal.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"indoor\"] #widget_main>#pb_down:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_down_click.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"indoor\"] #widget_main>#line,\n"
"#SA_Dialog_CH_Std[status = \"indoor\""
                        "] #widget_main>#line_2,\n"
"#SA_Dialog_CH_Std[status = \"indoor\"] #widget_main>#line_3,\n"
"#SA_Dialog_CH_Std[status = \"indoor\"] #widget_main>#line_4\n"
"{\n"
"	background-color:rgba(6,62,97,1);\n"
"}\n"
"\n"
"#SA_Dialog_CH_Std[status = \"indoor\"] #widget_main>#line_5\n"
"{\n"
"	background-color:rgba(181, 181, 181, 1);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"indoor\"] #widget_main>#tableWidget\n"
"{\n"
"	border-style:flat;\n"
"	outline:0px;\n"
"	font:75 15px \"Arial\";\n"
"	\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"indoor\"] #widget_main>#tableWidget::item\n"
"{\n"
"	padding-left:10px;\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"indoor\"] #widget_main>#tableWidget::item:selected\n"
"{\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	background-image: url(:/sa/image/box_click.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"indoor\"] #widget_main>QPushButton:checked\n"
"{\n"
"	background-color:rgba(255, 181, 0, 1)\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"indoor\"] #widget_main>QPushButton\n"
"{\n"
"	border-style:flat;"
                        "\n"
"	text-align:left;\n"
"	padding-left:10px;\n"
"}\n"
"\n"
"#SA_Dialog_CH_Std[status = \"indoor\"] #widget_main>#pb_ok\n"
"{\n"
"	color:rgba(0,0,0,0);\n"
"	background-image: url(:/sa/image/btn_ok_w80_nor.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"indoor\"] #widget_main>#pb_ok:pressed\n"
"{	\n"
"	color:rgba(0,0,0,0);\n"
"	background-image: url(:/sa/image/btn_ok_w80_click.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"indoor\"] #widget_main>#pb_cancel\n"
"{\n"
"	color:rgba(0,0,0,0);\n"
"	background-image: url(:/sa/image/btn_cancel_w80_nor.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"indoor\"] #widget_main>#pb_cancel:pressed\n"
"{	\n"
"	color:rgba(0,0,0,0);\n"
"	background-image: url(:/sa/image/btn_cancel_w80_click.png);\n"
"}\n"
"/*******************outdoor**********************/\n"
"#SA_Dialog_CH_Std[status = \"outdoor\"] #widget_main\n"
"{\n"
"	background-color:rgba(255,255,255,1);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"outdoor\"] #widget_main>QLabel\n"
"{\n"
"	color:rgba(6, 62, 97, 1);\n"
"	font:75 15px \"A"
                        "rial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"outdoor\"] #widget_main>#pb_up\n"
"{\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/btn_up_normal.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"outdoor\"] #widget_main>#pb_up:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_up_click.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"outdoor\"] #widget_main>#pb_down\n"
"{\n"
"border-style:flat;\n"
"	background-image: url(:/sa/image/btn_down_normal.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"outdoor\"] #widget_main>#pb_down:pressed\n"
"{\n"
"	background-image: url(:/sa/image/btn_down_click.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"outdoor\"] #widget_main>#line,\n"
"#SA_Dialog_CH_Std[status = \"outdoor\"] #widget_main>#line_2,\n"
"#SA_Dialog_CH_Std[status = \"outdoor\"] #widget_main>#line_3,\n"
"#SA_Dialog_CH_Std[status = \"outdoor\"] #widget_main>#line_4\n"
"{\n"
"	background-color:rgba(6,62,97,1);\n"
"}\n"
"\n"
"#SA_Dialog_CH_Std[status = \"outdoor\"] #widget_main>#line_5\n"
""
                        "{\n"
"	background-color:rgba(181, 181, 181, 1);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"outdoor\"] #widget_main>#tableWidget\n"
"{\n"
"	border-style:flat;\n"
"	outline:0px;\n"
"	font:75 15px \"Arial\";\n"
"	\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"outdoor\"] #widget_main>#tableWidget::item\n"
"{\n"
"	padding-left:10px;\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"outdoor\"] #widget_main>#tableWidget::item:selected\n"
"{\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	background-image: url(:/sa/image/box_click.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"outdoor\"] #widget_main>QPushButton:checked\n"
"{\n"
"	background-color:rgba(255, 181, 0, 1)\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"outdoor\"] #widget_main>QPushButton\n"
"{\n"
"	border-style:flat;\n"
"	text-align:left;\n"
"	padding-left:10px;\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"outdoor\"] #widget_main>#pb_ok\n"
"{\n"
"	color:rgba(0,0,0,0);\n"
"	background-image: url(:/sa/image/btn_ok_w80_nor.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"outdoor\"] #widget_main>#"
                        "pb_ok:pressed\n"
"{	\n"
"	color:rgba(0,0,0,0);\n"
"	background-image: url(:/sa/image/btn_ok_w80_click.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"outdoor\"] #widget_main>#pb_cancel\n"
"{\n"
"	color:rgba(0,0,0,0);\n"
"	background-image: url(:/sa/image/btn_cancel_w80_nor.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"outdoor\"] #widget_main>#pb_cancel:pressed\n"
"{	\n"
"	color:rgba(0,0,0,0);\n"
"	background-image: url(:/sa/image/btn_cancel_w80_click.png);\n"
"}\n"
"\n"
"/*******************night**********************/\n"
"#SA_Dialog_CH_Std[status = \"night\"] #widget_main\n"
"{\n"
"	background-color:rgba(0,0,0,1);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"night\"] #widget_main>QLabel\n"
"{\n"
"	color:rgba(7,97,116,1);\n"
"	font:75 15px \"Arial\";\n"
"	font-weight:bold;\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"night\"] #widget_main>#pb_up\n"
"{\n"
"	border-style:flat;\n"
"	background-color:rgb(0,0,0);\n"
"	background-image: url(:/sa/image/night/btn_up_normal.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"night\"] #widget"
                        "_main>#pb_up:pressed\n"
"{\n"
"	background-color:rgb(0,0,0);\n"
"	background-image: url(:/sa/image/night/btn_up_click.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"night\"] #widget_main>#pb_down\n"
"{\n"
"	background-color:rgb(0,0,0);\n"
"	border-style:flat;\n"
"	background-image: url(:/sa/image/night/btn_down_normal.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"night\"] #widget_main>#pb_down:pressed\n"
"{\n"
"	background-color:rgb(0,0,0);\n"
"	background-image: url(:/sa/image/night/btn_down_click.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"night\"] #widget_main>#line,\n"
"#SA_Dialog_CH_Std[status = \"night\"] #widget_main>#line_2,\n"
"#SA_Dialog_CH_Std[status = \"night\"] #widget_main>#line_3,\n"
"#SA_Dialog_CH_Std[status = \"night\"] #widget_main>#line_4\n"
"{\n"
"	background-color:rgba(6,62,97,1);\n"
"}\n"
"\n"
"#SA_Dialog_CH_Std[status = \"night\"] #widget_main>#line_5\n"
"{\n"
"	background-color:rgba(7,97,116,1);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"night\"] #widget_main>#tableWidget\n"
"{\n"
"	backgroun"
                        "d-color: rgb(0, 0, 0);\n"
"	alternate-background-color: rgba(24,23,20,1);\n"
"	color: rgba(176,153,117,1);\n"
"	border-style:flat;\n"
"	outline:0px;\n"
"	font:75 15px \"Arial\";\n"
"	\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"night\"] #widget_main>#tableWidget::item\n"
"{\n"
"	padding-left:10px;\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"night\"] #widget_main>#tableWidget::item:selected\n"
"{\n"
"	color: rgba(0,0,0,1);\n"
"	border-style:flat;\n"
"	font-weight:bold;\n"
"	background-image: url(:/sa/image/night/box_click.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"night\"] #widget_main>QPushButton:checked\n"
"{\n"
"	color:rgba(0,0,0,1);\n"
"	background-color:rgba(255, 156, 0, 1)\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"night\"] #widget_main>QPushButton\n"
"{\n"
"	color:rgba(251, 219, 167, 1);\n"
"	background-color:rgba(24,23,20,1);\n"
"	border-style:flat;\n"
"	text-align:left;\n"
"	padding-left:10px;\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"night\"] #widget_main>#pb_ok\n"
"{\n"
"	padding-left:30px;\n"
"	font:75 13px \"Aria"
                        "l\";\n"
"	border-style: flat;\n"
"	border-image: url(:/sa/image/night/btn_ok_w80_nor.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"night\"] #widget_main>#pb_ok:pressed\n"
"{	\n"
"	border-image: url(:/sa/image/night/btn_w70_click.png);\n"
"}\n"
"\n"
"#SA_Dialog_CH_Std[status = \"night\"] #widget_main>#pb_cancel\n"
"{\n"
"	font:75 13px \"Arial\";\n"
"	padding-left:20px;\n"
"	padding-top:3px;\n"
"	border-style: flat;\n"
"	border-image: url(:/sa/image/night/btn_w70_normal.png);\n"
"}\n"
"#SA_Dialog_CH_Std[status = \"night\"] #widget_main>#pb_cancel:pressed\n"
"{	\n"
"	border-image: url(:/sa/image/night/btn_w70_click.png);\n"
"}"));
        pb_CDMA = new QPushButton(widget_main);
        pb_CDMA->setObjectName(QStringLiteral("pb_CDMA"));
        pb_CDMA->setGeometry(QRect(19, 68, 240, 30));
        pb_CDMA->setCheckable(true);
        pb_CDMA->setChecked(true);
        pb_GSM = new QPushButton(widget_main);
        pb_GSM->setObjectName(QStringLiteral("pb_GSM"));
        pb_GSM->setGeometry(QRect(19, 113, 240, 30));
        pb_GSM->setCheckable(true);
        pb_LTEFDD = new QPushButton(widget_main);
        pb_LTEFDD->setObjectName(QStringLiteral("pb_LTEFDD"));
        pb_LTEFDD->setGeometry(QRect(19, 158, 240, 30));
        pb_LTEFDD->setCheckable(true);
        pb_LTETDD = new QPushButton(widget_main);
        pb_LTETDD->setObjectName(QStringLiteral("pb_LTETDD"));
        pb_LTETDD->setGeometry(QRect(19, 203, 240, 30));
        pb_LTETDD->setCheckable(true);
        pb_TD = new QPushButton(widget_main);
        pb_TD->setObjectName(QStringLiteral("pb_TD"));
        pb_TD->setGeometry(QRect(19, 248, 240, 30));
        pb_TD->setCheckable(true);
        pb_WCDMA = new QPushButton(widget_main);
        pb_WCDMA->setObjectName(QStringLiteral("pb_WCDMA"));
        pb_WCDMA->setGeometry(QRect(19, 293, 240, 30));
        pb_WCDMA->setCheckable(true);
        pb_WIMAX = new QPushButton(widget_main);
        pb_WIMAX->setObjectName(QStringLiteral("pb_WIMAX"));
        pb_WIMAX->setGeometry(QRect(19, 338, 240, 30));
        pb_WIMAX->setCheckable(true);
        label_2 = new QLabel(widget_main);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(21, 28, 90, 17));
        tableWidget = new QTableWidget(widget_main);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidget->rowCount() < 9)
            tableWidget->setRowCount(9);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setItem(1, 0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setItem(1, 1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setItem(1, 2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setItem(2, 0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setItem(2, 1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setItem(2, 2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setItem(3, 0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setItem(3, 1, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setItem(3, 2, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setItem(4, 0, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setItem(4, 1, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setItem(4, 2, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setItem(5, 0, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setItem(5, 1, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setItem(5, 2, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setItem(6, 0, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setItem(6, 1, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setItem(6, 2, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget->setItem(7, 0, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget->setItem(7, 1, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget->setItem(7, 2, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget->setItem(8, 0, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget->setItem(8, 1, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget->setItem(8, 2, __qtablewidgetitem28);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(320, 70, 758, 440));
        tableWidget->setLayoutDirection(Qt::LeftToRight);
        tableWidget->setStyleSheet(QStringLiteral(""));
        tableWidget->setFrameShape(QFrame::StyledPanel);
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setProperty("showDropIndicator", QVariant(true));
        tableWidget->setAlternatingRowColors(true);
        tableWidget->setTextElideMode(Qt::ElideRight);
        tableWidget->setShowGrid(false);
        tableWidget->setWordWrap(true);
        tableWidget->setRowCount(9);
        tableWidget->setColumnCount(3);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(259);
        tableWidget->horizontalHeader()->setHighlightSections(false);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(55);
        tableWidget->verticalHeader()->setHighlightSections(false);
        tableWidget->verticalHeader()->setStretchLastSection(false);
        pb_up = new QPushButton(widget_main);
        pb_up->setObjectName(QStringLiteral("pb_up"));
        pb_up->setGeometry(QRect(1116, 230, 52, 52));
        pb_down = new QPushButton(widget_main);
        pb_down->setObjectName(QStringLiteral("pb_down"));
        pb_down->setGeometry(QRect(1116, 315, 52, 52));
        label_3 = new QLabel(widget_main);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(322, 28, 88, 17));
        label_4 = new QLabel(widget_main);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(581, 28, 118, 17));
        label_5 = new QLabel(widget_main);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(840, 28, 179, 17));
        line = new QFrame(widget_main);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(21, 48, 237, 2));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(widget_main);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(322, 48, 237, 2));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(widget_main);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(581, 48, 237, 2));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(widget_main);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(840, 48, 237, 2));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(widget_main);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(280, 1, 1, 597));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);
        pb_cancel = new QPushButton(widget_main);
        pb_cancel->setObjectName(QStringLiteral("pb_cancel"));
        pb_cancel->setGeometry(QRect(994, 539, 80, 30));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        pb_cancel->setFont(font);
        pb_cancel->setStyleSheet(QStringLiteral(""));
        pb_cancel->setFlat(true);
        pb_ok = new QPushButton(widget_main);
        pb_ok->setObjectName(QStringLiteral("pb_ok"));
        pb_ok->setGeometry(QRect(1076, 539, 80, 30));
        pb_ok->setFont(font);
        pb_ok->setLayoutDirection(Qt::LeftToRight);
        pb_ok->setStyleSheet(QStringLiteral(""));
        pb_ok->setFlat(true);

        verticalLayout->addWidget(widget_main);

        verticalLayout->setStretch(0, 46);
        verticalLayout->setStretch(1, 599);

        retranslateUi(SA_Dialog_CH_Std);

        QMetaObject::connectSlotsByName(SA_Dialog_CH_Std);
    } // setupUi

    void retranslateUi(QWidget *SA_Dialog_CH_Std)
    {
        SA_Dialog_CH_Std->setWindowTitle(QApplication::translate("SA_Dialog_CH_Std", "Form", Q_NULLPTR));
        SA_Dialog_CH_Std->setProperty("status", QVariant(QApplication::translate("SA_Dialog_CH_Std", "night", Q_NULLPTR)));
        lblTitle->setText(QApplication::translate("SA_Dialog_CH_Std", "Channel Standard", Q_NULLPTR));
        pb_close->setText(QString());
        pb_CDMA->setText(QApplication::translate("SA_Dialog_CH_Std", "CDMA", Q_NULLPTR));
        pb_GSM->setText(QApplication::translate("SA_Dialog_CH_Std", "GSM", Q_NULLPTR));
        pb_LTEFDD->setText(QApplication::translate("SA_Dialog_CH_Std", "LTE-A FDD", Q_NULLPTR));
        pb_LTETDD->setText(QApplication::translate("SA_Dialog_CH_Std", "LTE-A TDD", Q_NULLPTR));
        pb_TD->setText(QApplication::translate("SA_Dialog_CH_Std", "TD-SCDMA", Q_NULLPTR));
        pb_WCDMA->setText(QApplication::translate("SA_Dialog_CH_Std", "WCDMA", Q_NULLPTR));
        pb_WIMAX->setText(QApplication::translate("SA_Dialog_CH_Std", "WIMAX", Q_NULLPTR));
        label_2->setText(QApplication::translate("SA_Dialog_CH_Std", "Technology", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SA_Dialog_CH_Std", "\346\226\260\345\273\272\345\210\227", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("SA_Dialog_CH_Std", "\346\226\260\345\273\272\350\241\214", Q_NULLPTR));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->item(0, 0);
        ___qtablewidgetitem2->setText(QApplication::translate("SA_Dialog_CH_Std", "Band 0(800)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->item(0, 1);
        ___qtablewidgetitem3->setText(QApplication::translate("SA_Dialog_CH_Std", "(1 - 799)\n"
"(991-1023)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->item(0, 2);
        ___qtablewidgetitem4->setText(QApplication::translate("SA_Dialog_CH_Std", "(825.03-848.97)\n"
"(824.04-825.00)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->item(1, 0);
        ___qtablewidgetitem5->setText(QApplication::translate("SA_Dialog_CH_Std", "Band 0(800)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->item(1, 1);
        ___qtablewidgetitem6->setText(QApplication::translate("SA_Dialog_CH_Std", "(1 - 799)\n"
"(991-1023)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->item(1, 2);
        ___qtablewidgetitem7->setText(QApplication::translate("SA_Dialog_CH_Std", "(825.03-848.97)\n"
"(824.04-825.00)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->item(2, 0);
        ___qtablewidgetitem8->setText(QApplication::translate("SA_Dialog_CH_Std", "Band 0(800)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->item(2, 1);
        ___qtablewidgetitem9->setText(QApplication::translate("SA_Dialog_CH_Std", "(1 - 799)\n"
"(991-1023)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->item(2, 2);
        ___qtablewidgetitem10->setText(QApplication::translate("SA_Dialog_CH_Std", "(825.03-848.97)\n"
"(824.04-825.00)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->item(3, 0);
        ___qtablewidgetitem11->setText(QApplication::translate("SA_Dialog_CH_Std", "Band 0(800)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->item(3, 1);
        ___qtablewidgetitem12->setText(QApplication::translate("SA_Dialog_CH_Std", "(1 - 799)\n"
"(991-1023)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->item(3, 2);
        ___qtablewidgetitem13->setText(QApplication::translate("SA_Dialog_CH_Std", "(825.03-848.97)\n"
"(824.04-825.00)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->item(4, 0);
        ___qtablewidgetitem14->setText(QApplication::translate("SA_Dialog_CH_Std", "Band 0(800)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->item(4, 1);
        ___qtablewidgetitem15->setText(QApplication::translate("SA_Dialog_CH_Std", "(1 - 799)\n"
"(991-1023)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->item(4, 2);
        ___qtablewidgetitem16->setText(QApplication::translate("SA_Dialog_CH_Std", "(825.03-848.97)\n"
"(824.04-825.00)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->item(5, 0);
        ___qtablewidgetitem17->setText(QApplication::translate("SA_Dialog_CH_Std", "Band 0(800)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->item(5, 1);
        ___qtablewidgetitem18->setText(QApplication::translate("SA_Dialog_CH_Std", "(1 - 799)\n"
"(991-1023)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->item(5, 2);
        ___qtablewidgetitem19->setText(QApplication::translate("SA_Dialog_CH_Std", "(825.03-848.97)\n"
"(824.04-825.00)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->item(6, 0);
        ___qtablewidgetitem20->setText(QApplication::translate("SA_Dialog_CH_Std", "Band 0(800)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->item(6, 1);
        ___qtablewidgetitem21->setText(QApplication::translate("SA_Dialog_CH_Std", "(1 - 799)\n"
"(991-1023)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget->item(6, 2);
        ___qtablewidgetitem22->setText(QApplication::translate("SA_Dialog_CH_Std", "(825.03-848.97)\n"
"(824.04-825.00)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget->item(7, 0);
        ___qtablewidgetitem23->setText(QApplication::translate("SA_Dialog_CH_Std", "Band 0(800)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget->item(7, 1);
        ___qtablewidgetitem24->setText(QApplication::translate("SA_Dialog_CH_Std", "(1 - 799)\n"
"(991-1023)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget->item(7, 2);
        ___qtablewidgetitem25->setText(QApplication::translate("SA_Dialog_CH_Std", "(825.03-848.97)\n"
"(824.04-825.00)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget->item(8, 0);
        ___qtablewidgetitem26->setText(QApplication::translate("SA_Dialog_CH_Std", "Band 0(800)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget->item(8, 1);
        ___qtablewidgetitem27->setText(QApplication::translate("SA_Dialog_CH_Std", "(1 - 799)\n"
"(991-1023)", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget->item(8, 2);
        ___qtablewidgetitem28->setText(QApplication::translate("SA_Dialog_CH_Std", "(825.03-848.97)\n"
"(824.04-825.00)", Q_NULLPTR));
        tableWidget->setSortingEnabled(__sortingEnabled);

        pb_up->setText(QString());
        pb_down->setText(QString());
        label_3->setText(QApplication::translate("SA_Dialog_CH_Std", "Band Class", Q_NULLPTR));
        label_4->setText(QApplication::translate("SA_Dialog_CH_Std", "Channel Range", Q_NULLPTR));
        label_5->setText(QApplication::translate("SA_Dialog_CH_Std", "Frequency Range (MHz)", Q_NULLPTR));
        pb_cancel->setText(QApplication::translate("SA_Dialog_CH_Std", "Cancel", Q_NULLPTR));
        pb_ok->setText(QApplication::translate("SA_Dialog_CH_Std", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SA_Dialog_CH_Std: public Ui_SA_Dialog_CH_Std {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_CH_STD_H
