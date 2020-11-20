/********************************************************************************
** Form generated from reading UI file 'sa_dialog_virtualkeyboard.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SA_DIALOG_VIRTUALKEYBOARD_H
#define UI_SA_DIALOG_VIRTUALKEYBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SA_Dialog_VirtualKeyboard
{
public:
    QWidget *widget;
    QPushButton *key_LeftShift;
    QPushButton *key_Right_Alt;
    QPushButton *key_f;
    QPushButton *key_Slash;
    QPushButton *key_l;
    QPushButton *key_Delete;
    QPushButton *key_d;
    QPushButton *key_right_Fn;
    QPushButton *key_s;
    QPushButton *key_6;
    QPushButton *key_g;
    QPushButton *key_BracketLeft;
    QPushButton *key_k;
    QPushButton *key_4;
    QPushButton *key_RightShift;
    QPushButton *key_c;
    QPushButton *key_Up;
    QPushButton *key_u;
    QPushButton *key_v;
    QPushButton *key_Equal;
    QPushButton *key_j;
    QPushButton *key_0;
    QPushButton *key_w;
    QPushButton *key_z;
    QPushButton *key_Backslash;
    QPushButton *key_Apostrophe;
    QPushButton *key_i;
    QPushButton *key_QuoteLeft;
    QPushButton *key_Minus;
    QPushButton *key_BackSpace;
    QPushButton *key_Esc;
    QPushButton *key_b;
    QPushButton *key_Comma;
    QPushButton *key_Tab;
    QPushButton *key_r;
    QPushButton *key_t;
    QPushButton *key_Period;
    QPushButton *key_1;
    QPushButton *key_y;
    QPushButton *key_3;
    QPushButton *key_Enter;
    QPushButton *key_m;
    QPushButton *key_n;
    QPushButton *key_2;
    QPushButton *key_o;
    QPushButton *key_Semicolon;
    QPushButton *key_q;
    QPushButton *key_7;
    QPushButton *key_a;
    QPushButton *key_Down;
    QPushButton *key_Left;
    QPushButton *key_CapsLock;
    QPushButton *key_9;
    QPushButton *key_h;
    QPushButton *key_8;
    QPushButton *key_BracketRight;
    QPushButton *key_5;
    QPushButton *key_Space;
    QPushButton *key_x;
    QPushButton *key_Left_Alt;
    QPushButton *key_p;
    QPushButton *key_leftFn;
    QPushButton *key_e;
    QPushButton *key_Right;

    void setupUi(QWidget *SA_Dialog_VirtualKeyboard)
    {
        if (SA_Dialog_VirtualKeyboard->objectName().isEmpty())
            SA_Dialog_VirtualKeyboard->setObjectName(QStringLiteral("SA_Dialog_VirtualKeyboard"));
        SA_Dialog_VirtualKeyboard->resize(950, 290);
        SA_Dialog_VirtualKeyboard->setStyleSheet(QLatin1String("/************************indoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] #widget\n"
"{\n"
"	background-color:rgba(255,255,255,1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton\n"
"{\n"
"	font:75 16px \"Arial\";\n"
"	font-weight:bold;\n"
"	border-style:flat;\n"
"	\n"
"	background-image: url(:/sa/image/KeyBoard/btn_w50_nor.png);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton::pressed\n"
"{\n"
"background-image: url(:/sa/image/KeyBoard/btn_w50_click.png);\n"
"}\n"
"\n"
"/************************outdoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] #widget\n"
"{\n"
"	background-color:rgba(255,255,255,1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton\n"
"{\n"
"	font:75 16px \"Arial\";\n"
"	font-weight:bold;\n"
"	border-style:flat;\n"
"	\n"
"	background-image: url(:/sa/image/KeyBoard/btn_w50_nor.png);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton::pr"
                        "essed\n"
"{\n"
"background-image: url(:/sa/image/KeyBoard/btn_w50_click.png);\n"
"}\n"
"\n"
"\n"
"/************************night**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] #widget\n"
"{\n"
"	background-color:rgba(0,0,0,1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton\n"
"{\n"
"	font:75 16px \"Arial\";\n"
"	font-weight:bold;\n"
"	border-style:flat;\n"
"	background-color:#E4C797;\n"
"	/*background-color: rgba(228,199,151,1);	*/\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton::pressed\n"
"{\n"
"	background-color: #FB9B00;	\n"
"}\n"
""));
        widget = new QWidget(SA_Dialog_VirtualKeyboard);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 950, 290));
        key_LeftShift = new QPushButton(widget);
        key_LeftShift->setObjectName(QStringLiteral("key_LeftShift"));
        key_LeftShift->setGeometry(QRect(0, 180, 140, 50));
        key_LeftShift->setFocusPolicy(Qt::NoFocus);
        key_LeftShift->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	text-align:left;\n"
"	padding-left:11px;\n"
"}\n"
"/************************indoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton\n"
"{\n"
"background-color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton::pressed\n"
"{\n"
"background-color:rgba(255, 181, 0, 1);\n"
"}\n"
"/************************outdoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton\n"
"{\n"
"background-color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton::pressed\n"
"{\n"
"background-color:rgba(255, 181, 0, 1);\n"
"}\n"
"\n"
"/************************night**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton\n"
"{\n"
"	background-color: rgb(119, 103, 79);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton::pressed\n"
"{\n"
"	background-color: rgb(251, 156, 0);\n"
"}\n"
""));
        key_Right_Alt = new QPushButton(widget);
        key_Right_Alt->setObjectName(QStringLiteral("key_Right_Alt"));
        key_Right_Alt->setGeometry(QRect(630, 240, 50, 50));
        key_Right_Alt->setFocusPolicy(Qt::NoFocus);
        key_Right_Alt->setStyleSheet(QLatin1String("/************************indoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton\n"
"{\n"
"background-color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton::pressed\n"
"{\n"
"background-color:rgba(255, 181, 0, 1);\n"
"}\n"
"/************************outdoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton\n"
"{\n"
"background-color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton::pressed\n"
"{\n"
"background-color:rgba(255, 181, 0, 1);\n"
"}\n"
"\n"
"/************************night**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton\n"
"{\n"
"	background-color: rgb(119, 103, 79);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton::pressed\n"
"{\n"
"	background-color: rgb(251, 156, 0);\n"
"}\n"
""));
        key_f = new QPushButton(widget);
        key_f->setObjectName(QStringLiteral("key_f"));
        key_f->setGeometry(QRect(300, 120, 50, 50));
        key_f->setFocusPolicy(Qt::NoFocus);
        key_Slash = new QPushButton(widget);
        key_Slash->setObjectName(QStringLiteral("key_Slash"));
        key_Slash->setGeometry(QRect(690, 180, 50, 50));
        key_Slash->setFocusPolicy(Qt::NoFocus);
        key_l = new QPushButton(widget);
        key_l->setObjectName(QStringLiteral("key_l"));
        key_l->setGeometry(QRect(600, 120, 50, 50));
        key_l->setFocusPolicy(Qt::NoFocus);
        key_Delete = new QPushButton(widget);
        key_Delete->setObjectName(QStringLiteral("key_Delete"));
        key_Delete->setGeometry(QRect(870, 60, 80, 50));
        key_Delete->setFocusPolicy(Qt::NoFocus);
        key_Delete->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	text-align:right;\n"
"	padding-right:15px;\n"
"}\n"
"/************************indoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton\n"
"{\n"
"background-color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton::pressed\n"
"{\n"
"background-color:rgba(255, 181, 0, 1);\n"
"}\n"
"/************************outdoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton\n"
"{\n"
"background-color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton::pressed\n"
"{\n"
"background-color:rgba(255, 181, 0, 1);\n"
"}\n"
"\n"
"/************************night**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton\n"
"{\n"
"	background-color: rgb(119, 103, 79);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton::pressed\n"
"{\n"
"	background-color: rgb(251, 156, 0);\n"
"}\n"
""));
        key_d = new QPushButton(widget);
        key_d->setObjectName(QStringLiteral("key_d"));
        key_d->setGeometry(QRect(240, 120, 50, 50));
        key_d->setFocusPolicy(Qt::NoFocus);
        key_right_Fn = new QPushButton(widget);
        key_right_Fn->setObjectName(QStringLiteral("key_right_Fn"));
        key_right_Fn->setGeometry(QRect(870, 240, 80, 50));
        key_right_Fn->setFocusPolicy(Qt::NoFocus);
        key_right_Fn->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	text-align:right;\n"
"	padding-right:15px;\n"
"}\n"
"/************************indoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton\n"
"{\n"
"background-color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton::pressed\n"
"{\n"
"background-color:rgba(255, 181, 0, 1);\n"
"}\n"
"/************************outdoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton\n"
"{\n"
"background-color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton::pressed\n"
"{\n"
"background-color:rgba(255, 181, 0, 1);\n"
"}\n"
"\n"
"/************************night**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton\n"
"{\n"
"	background-color: rgb(119, 103, 79);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton::pressed\n"
"{\n"
"	background-color: rgb(251, 156, 0);\n"
"}\n"
""));
        key_s = new QPushButton(widget);
        key_s->setObjectName(QStringLiteral("key_s"));
        key_s->setGeometry(QRect(180, 120, 50, 50));
        key_s->setFocusPolicy(Qt::NoFocus);
        key_6 = new QPushButton(widget);
        key_6->setObjectName(QStringLiteral("key_6"));
        key_6->setGeometry(QRect(420, 0, 50, 50));
        key_6->setFocusPolicy(Qt::NoFocus);
        key_g = new QPushButton(widget);
        key_g->setObjectName(QStringLiteral("key_g"));
        key_g->setGeometry(QRect(360, 120, 50, 50));
        key_g->setFocusPolicy(Qt::NoFocus);
        key_BracketLeft = new QPushButton(widget);
        key_BracketLeft->setObjectName(QStringLiteral("key_BracketLeft"));
        key_BracketLeft->setGeometry(QRect(690, 60, 50, 50));
        key_BracketLeft->setFocusPolicy(Qt::NoFocus);
        key_k = new QPushButton(widget);
        key_k->setObjectName(QStringLiteral("key_k"));
        key_k->setGeometry(QRect(540, 120, 50, 50));
        key_k->setFocusPolicy(Qt::NoFocus);
        key_4 = new QPushButton(widget);
        key_4->setObjectName(QStringLiteral("key_4"));
        key_4->setGeometry(QRect(300, 0, 50, 50));
        key_4->setFocusPolicy(Qt::NoFocus);
        key_RightShift = new QPushButton(widget);
        key_RightShift->setObjectName(QStringLiteral("key_RightShift"));
        key_RightShift->setGeometry(QRect(810, 180, 140, 50));
        key_RightShift->setFocusPolicy(Qt::NoFocus);
        key_RightShift->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	text-align:right;\n"
"	padding-right:15px;\n"
"}\n"
"/************************indoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton\n"
"{\n"
"background-color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton::pressed\n"
"{\n"
"background-color:rgba(255, 181, 0, 1);\n"
"}\n"
"/************************outdoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton\n"
"{\n"
"background-color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton::pressed\n"
"{\n"
"background-color:rgba(255, 181, 0, 1);\n"
"}\n"
"\n"
"/************************night**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton\n"
"{\n"
"	background-color: rgb(119, 103, 79);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton::pressed\n"
"{\n"
"	background-color: rgb(251, 156, 0);\n"
"}\n"
""));
        key_c = new QPushButton(widget);
        key_c->setObjectName(QStringLiteral("key_c"));
        key_c->setGeometry(QRect(270, 180, 50, 50));
        key_c->setFocusPolicy(Qt::NoFocus);
        key_Up = new QPushButton(widget);
        key_Up->setObjectName(QStringLiteral("key_Up"));
        key_Up->setGeometry(QRect(750, 180, 50, 50));
        key_Up->setFocusPolicy(Qt::NoFocus);
        key_Up->setStyleSheet(QLatin1String("/************************indoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton\n"
"{\n"
"color:rgba(0,0,0,0);\n"
"background-image: url(:/sa/image/KeyBoard/btn_up_w50_nor.png);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton::pressed\n"
"{\n"
"color:rgba(0,0,0,0);\n"
"background-image: url(:/sa/image/KeyBoard/btn_up_w50_click.png);\n"
"}\n"
"/************************outdoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton\n"
"{\n"
"color:rgba(0,0,0,0);\n"
"background-image: url(:/sa/image/KeyBoard/btn_up_w50_nor.png);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton::pressed\n"
"{\n"
"color:rgba(0,0,0,0);\n"
"background-image: url(:/sa/image/KeyBoard/btn_up_w50_click.png);\n"
"}\n"
"\n"
"/************************night**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton\n"
"{\n"
"	padding-left:109px;\n"
"	color: #FBDBA7;\n"
"	border-image: url(:"
                        "/sa/image/night/btn_up_w50_nor.png);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton::pressed\n"
"{\n"
"	border-image: url(:/sa/image/night/btn_up_w50_click.png);\n"
"}\n"
""));
        key_u = new QPushButton(widget);
        key_u->setObjectName(QStringLiteral("key_u"));
        key_u->setGeometry(QRect(450, 60, 50, 50));
        key_u->setFocusPolicy(Qt::NoFocus);
        key_v = new QPushButton(widget);
        key_v->setObjectName(QStringLiteral("key_v"));
        key_v->setGeometry(QRect(330, 180, 50, 50));
        key_v->setFocusPolicy(Qt::NoFocus);
        key_Equal = new QPushButton(widget);
        key_Equal->setObjectName(QStringLiteral("key_Equal"));
        key_Equal->setGeometry(QRect(780, 0, 50, 50));
        key_Equal->setFocusPolicy(Qt::NoFocus);
        key_j = new QPushButton(widget);
        key_j->setObjectName(QStringLiteral("key_j"));
        key_j->setGeometry(QRect(480, 120, 50, 50));
        key_j->setFocusPolicy(Qt::NoFocus);
        key_0 = new QPushButton(widget);
        key_0->setObjectName(QStringLiteral("key_0"));
        key_0->setGeometry(QRect(660, 0, 50, 50));
        key_0->setFocusPolicy(Qt::NoFocus);
        key_w = new QPushButton(widget);
        key_w->setObjectName(QStringLiteral("key_w"));
        key_w->setGeometry(QRect(150, 60, 50, 50));
        key_w->setFocusPolicy(Qt::NoFocus);
        key_z = new QPushButton(widget);
        key_z->setObjectName(QStringLiteral("key_z"));
        key_z->setGeometry(QRect(150, 180, 50, 50));
        key_z->setFocusPolicy(Qt::NoFocus);
        key_Backslash = new QPushButton(widget);
        key_Backslash->setObjectName(QStringLiteral("key_Backslash"));
        key_Backslash->setGeometry(QRect(810, 60, 50, 50));
        key_Backslash->setFocusPolicy(Qt::NoFocus);
        key_Apostrophe = new QPushButton(widget);
        key_Apostrophe->setObjectName(QStringLiteral("key_Apostrophe"));
        key_Apostrophe->setGeometry(QRect(720, 120, 50, 50));
        key_Apostrophe->setFocusPolicy(Qt::NoFocus);
        key_i = new QPushButton(widget);
        key_i->setObjectName(QStringLiteral("key_i"));
        key_i->setGeometry(QRect(510, 60, 50, 50));
        key_i->setFocusPolicy(Qt::NoFocus);
        key_QuoteLeft = new QPushButton(widget);
        key_QuoteLeft->setObjectName(QStringLiteral("key_QuoteLeft"));
        key_QuoteLeft->setGeometry(QRect(60, 0, 50, 50));
        key_QuoteLeft->setFocusPolicy(Qt::NoFocus);
        key_Minus = new QPushButton(widget);
        key_Minus->setObjectName(QStringLiteral("key_Minus"));
        key_Minus->setGeometry(QRect(720, 0, 50, 50));
        key_Minus->setFocusPolicy(Qt::NoFocus);
        key_BackSpace = new QPushButton(widget);
        key_BackSpace->setObjectName(QStringLiteral("key_BackSpace"));
        key_BackSpace->setGeometry(QRect(840, 0, 110, 50));
        key_BackSpace->setFocusPolicy(Qt::NoFocus);
        key_BackSpace->setStyleSheet(QLatin1String("/************************indoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton\n"
"{\n"
"background-color:rgba(197, 197, 197, 1);\n"
"background-image: url(:/sa/image/KeyBoard/btn_del_w110_nor.png);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton::pressed\n"
"{\n"
"background-image: url(:/sa/image/KeyBoard/btn_del_w110_click.png);\n"
"}\n"
"/************************outdoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton\n"
"{\n"
"background-color:rgba(197, 197, 197, 1);\n"
"background-image: url(:/sa/image/KeyBoard/btn_del_w110_nor.png);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton::pressed\n"
"{\n"
"background-image: url(:/sa/image/KeyBoard/btn_del_w110_click.png);\n"
"}\n"
"\n"
"/************************night**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton\n"
"{\n"
"background-image: url(:/sa/image/night/btn_del_w110_nor.png);\n"
"}\n"
""
                        "#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton::pressed\n"
"{\n"
"background-image: url(:/sa/image/night/btn_del_w110_click.png);\n"
"}\n"
""));
        key_BackSpace->setAutoDefault(false);
        key_BackSpace->setDefault(false);
        key_BackSpace->setFlat(true);
        key_Esc = new QPushButton(widget);
        key_Esc->setObjectName(QStringLiteral("key_Esc"));
        key_Esc->setGeometry(QRect(0, 0, 50, 50));
        key_Esc->setFocusPolicy(Qt::NoFocus);
        key_Esc->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	text-align:left;\n"
"	padding-left:11px;\n"
"}\n"
"/************************indoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton\n"
"{\n"
"background-color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton::pressed\n"
"{\n"
"background-color:rgba(255, 181, 0, 1);\n"
"}\n"
"/************************outdoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton\n"
"{\n"
"background-color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton::pressed\n"
"{\n"
"background-color:rgba(255, 181, 0, 1);\n"
"}\n"
"\n"
"/************************night**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton\n"
"{\n"
"	background-color: rgb(119, 103, 79);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton::pressed\n"
"{\n"
"	background-color: rgb(251, 156, 0);\n"
"}\n"
""));
        key_b = new QPushButton(widget);
        key_b->setObjectName(QStringLiteral("key_b"));
        key_b->setGeometry(QRect(390, 180, 50, 50));
        key_b->setFocusPolicy(Qt::NoFocus);
        key_Comma = new QPushButton(widget);
        key_Comma->setObjectName(QStringLiteral("key_Comma"));
        key_Comma->setGeometry(QRect(570, 180, 50, 50));
        key_Comma->setFocusPolicy(Qt::NoFocus);
        key_Tab = new QPushButton(widget);
        key_Tab->setObjectName(QStringLiteral("key_Tab"));
        key_Tab->setGeometry(QRect(0, 60, 80, 50));
        key_Tab->setFocusPolicy(Qt::NoFocus);
        key_Tab->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	text-align:left;\n"
"	padding-left:11px;\n"
"}\n"
"/************************indoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton\n"
"{\n"
"/*background-image:url(:/sa/image/KeyBoard/btn_tab_w80_nor.png);*/\n"
"    background-color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton::pressed\n"
"{\n"
"background-color:rgba(255, 181, 0, 1);\n"
"}\n"
"/************************outdoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton\n"
"{\n"
"    background-color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton::pressed\n"
"{\n"
"background-color:rgba(255, 181, 0, 1);\n"
"}\n"
"\n"
"/************************night**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton\n"
"{\n"
"	background-color: rgb(119, 103, 79);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton::p"
                        "ressed\n"
"{\n"
"	background-color: rgb(251, 156, 0);\n"
"}\n"
""));
        key_r = new QPushButton(widget);
        key_r->setObjectName(QStringLiteral("key_r"));
        key_r->setGeometry(QRect(270, 60, 50, 50));
        key_r->setFocusPolicy(Qt::NoFocus);
        key_t = new QPushButton(widget);
        key_t->setObjectName(QStringLiteral("key_t"));
        key_t->setGeometry(QRect(330, 60, 50, 50));
        key_t->setFocusPolicy(Qt::NoFocus);
        key_Period = new QPushButton(widget);
        key_Period->setObjectName(QStringLiteral("key_Period"));
        key_Period->setGeometry(QRect(630, 180, 50, 50));
        key_Period->setFocusPolicy(Qt::NoFocus);
        key_1 = new QPushButton(widget);
        key_1->setObjectName(QStringLiteral("key_1"));
        key_1->setGeometry(QRect(120, 0, 50, 50));
        key_1->setFocusPolicy(Qt::NoFocus);
        key_y = new QPushButton(widget);
        key_y->setObjectName(QStringLiteral("key_y"));
        key_y->setGeometry(QRect(390, 60, 50, 50));
        key_y->setFocusPolicy(Qt::NoFocus);
        key_3 = new QPushButton(widget);
        key_3->setObjectName(QStringLiteral("key_3"));
        key_3->setGeometry(QRect(240, 0, 50, 50));
        key_3->setFocusPolicy(Qt::NoFocus);
        key_Enter = new QPushButton(widget);
        key_Enter->setObjectName(QStringLiteral("key_Enter"));
        key_Enter->setGeometry(QRect(780, 120, 170, 50));
        key_Enter->setFocusPolicy(Qt::NoFocus);
        key_Enter->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	text-align:right;\n"
"	padding-right:15px;\n"
"}\n"
"/************************indoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton\n"
"{\n"
"color:rgba(0,0,0,0);\n"
"background-image: url(:/sa/image/KeyBoard/btn_enter_170_nor.png);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton::pressed\n"
"{\n"
"color:rgba(0,0,0,0);\n"
"background-image: url(:/sa/image/KeyBoard/btn_enter_170_click.png);\n"
"}\n"
"/************************outdoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton\n"
"{\n"
"color:rgba(0,0,0,0);\n"
"background-image: url(:/sa/image/KeyBoard/btn_enter_170_nor.png);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton::pressed\n"
"{\n"
"color:rgba(0,0,0,0);\n"
"background-image: url(:/sa/image/KeyBoard/btn_enter_170_click.png);\n"
"}\n"
"\n"
"/************************night**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] "
                        "QPushButton\n"
"{\n"
"	padding-left:109px;\n"
"	color: #FBDBA7;\n"
"	border-image: url(:/sa/image/night/btn_w70_normal.png);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton::pressed\n"
"{\n"
"	border-image: url(:/sa/image/night/btn_w70_click.png);\n"
"}\n"
""));
        key_m = new QPushButton(widget);
        key_m->setObjectName(QStringLiteral("key_m"));
        key_m->setGeometry(QRect(510, 180, 50, 50));
        key_m->setFocusPolicy(Qt::NoFocus);
        key_n = new QPushButton(widget);
        key_n->setObjectName(QStringLiteral("key_n"));
        key_n->setGeometry(QRect(450, 180, 50, 50));
        key_n->setFocusPolicy(Qt::NoFocus);
        key_2 = new QPushButton(widget);
        key_2->setObjectName(QStringLiteral("key_2"));
        key_2->setGeometry(QRect(180, 0, 50, 50));
        key_2->setFocusPolicy(Qt::NoFocus);
        key_o = new QPushButton(widget);
        key_o->setObjectName(QStringLiteral("key_o"));
        key_o->setGeometry(QRect(570, 60, 50, 50));
        key_o->setFocusPolicy(Qt::NoFocus);
        key_Semicolon = new QPushButton(widget);
        key_Semicolon->setObjectName(QStringLiteral("key_Semicolon"));
        key_Semicolon->setGeometry(QRect(660, 120, 50, 50));
        key_Semicolon->setFocusPolicy(Qt::NoFocus);
        key_q = new QPushButton(widget);
        key_q->setObjectName(QStringLiteral("key_q"));
        key_q->setGeometry(QRect(90, 60, 50, 50));
        key_q->setFocusPolicy(Qt::NoFocus);
        key_7 = new QPushButton(widget);
        key_7->setObjectName(QStringLiteral("key_7"));
        key_7->setGeometry(QRect(480, 0, 50, 50));
        key_7->setFocusPolicy(Qt::NoFocus);
        key_a = new QPushButton(widget);
        key_a->setObjectName(QStringLiteral("key_a"));
        key_a->setGeometry(QRect(120, 120, 50, 50));
        key_a->setFocusPolicy(Qt::NoFocus);
        key_Down = new QPushButton(widget);
        key_Down->setObjectName(QStringLiteral("key_Down"));
        key_Down->setGeometry(QRect(750, 240, 50, 50));
        key_Down->setFocusPolicy(Qt::NoFocus);
        key_Down->setStyleSheet(QLatin1String("/************************indoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton\n"
"{\n"
"color:rgba(0,0,0,0);\n"
"background-image: url(:/sa/image/KeyBoard/btn_down_w50_nor.png);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton::pressed\n"
"{\n"
"color:rgba(0,0,0,0);\n"
"background-image: url(:/sa/image/KeyBoard/btn_down_w50_click.png);\n"
"}\n"
"/************************outdoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton\n"
"{\n"
"color:rgba(0,0,0,0);\n"
"background-image: url(:/sa/image/KeyBoard/btn_down_w50_nor.png);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton::pressed\n"
"{\n"
"color:rgba(0,0,0,0);\n"
"background-image: url(:/sa/image/KeyBoard/btn_down_w50_click.png);\n"
"}\n"
"\n"
"/************************night**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton\n"
"{\n"
"	padding-left:109px;\n"
"	color: #FBDBA7;\n"
"	border-imag"
                        "e: url(:/sa/image/night/btn_down_w50_nor.png);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton::pressed\n"
"{\n"
"	border-image: url(:/sa/image/night/btn_down_w50_click.png);\n"
"}\n"
""));
        key_Left = new QPushButton(widget);
        key_Left->setObjectName(QStringLiteral("key_Left"));
        key_Left->setGeometry(QRect(690, 240, 50, 50));
        key_Left->setFocusPolicy(Qt::NoFocus);
        key_Left->setStyleSheet(QLatin1String("/************************indoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton\n"
"{\n"
"\n"
"color:rgba(0,0,0,0);\n"
"background-image: url(:/sa/image/KeyBoard/btn_up_w50_nor.png);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton::pressed\n"
"{\n"
"color:rgba(0,0,0,0);\n"
"background-image: url(:/sa/image/KeyBoard/btn_up_w50_click.png);\n"
"}\n"
"/************************outdoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton\n"
"{\n"
"color:rgba(0,0,0,0);\n"
"background-image: url(:/sa/image/KeyBoard/btn_up_w50_nor.png);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton::pressed\n"
"{\n"
"color:rgba(0,0,0,0);\n"
"background-image: url(:/sa/image/KeyBoard/btn_up_w50_click.png);\n"
"}\n"
"\n"
"/************************night**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton\n"
"{\n"
"\n"
"	padding-left:109px;\n"
"	color: #FBDBA7;\n"
"	border-im"
                        "age: url(:/sa/image/night/btn_left_w50_nor.png);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton::pressed\n"
"{\n"
"	border-image: url(:/sa/image/night/btn_left_w50_click.png);\n"
"}\n"
""));
        key_CapsLock = new QPushButton(widget);
        key_CapsLock->setObjectName(QStringLiteral("key_CapsLock"));
        key_CapsLock->setGeometry(QRect(0, 120, 110, 50));
        key_CapsLock->setFocusPolicy(Qt::NoFocus);
        key_CapsLock->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	text-align:left;\n"
"	padding-left:11px;\n"
"}\n"
"/************************indoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton\n"
"{\n"
"background-color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton::pressed\n"
"{\n"
"background-color:rgba(255, 181, 0, 1);\n"
"}\n"
"/************************outdoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton\n"
"{\n"
"background-color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton::pressed\n"
"{\n"
"background-color:rgba(255, 181, 0, 1);\n"
"}\n"
"\n"
"/************************night**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton\n"
"{\n"
"	background-color: rgb(119, 103, 79);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton::pressed\n"
"{\n"
"	background-color: rgb(251, 156, 0);\n"
"}\n"
""));
        key_9 = new QPushButton(widget);
        key_9->setObjectName(QStringLiteral("key_9"));
        key_9->setGeometry(QRect(600, 0, 50, 50));
        key_9->setFocusPolicy(Qt::NoFocus);
        key_h = new QPushButton(widget);
        key_h->setObjectName(QStringLiteral("key_h"));
        key_h->setGeometry(QRect(420, 120, 50, 50));
        key_h->setFocusPolicy(Qt::NoFocus);
        key_8 = new QPushButton(widget);
        key_8->setObjectName(QStringLiteral("key_8"));
        key_8->setGeometry(QRect(540, 0, 50, 50));
        key_8->setFocusPolicy(Qt::NoFocus);
        key_BracketRight = new QPushButton(widget);
        key_BracketRight->setObjectName(QStringLiteral("key_BracketRight"));
        key_BracketRight->setGeometry(QRect(750, 60, 50, 50));
        key_BracketRight->setFocusPolicy(Qt::NoFocus);
        key_5 = new QPushButton(widget);
        key_5->setObjectName(QStringLiteral("key_5"));
        key_5->setGeometry(QRect(360, 0, 50, 50));
        key_5->setFocusPolicy(Qt::NoFocus);
        key_Space = new QPushButton(widget);
        key_Space->setObjectName(QStringLiteral("key_Space"));
        key_Space->setGeometry(QRect(149, 240, 471, 50));
        key_Space->setFocusPolicy(Qt::NoFocus);
        key_Space->setStyleSheet(QLatin1String("/************************indoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton\n"
"{\n"
"background-image: url(:/sa/image/KeyBoard/btn_spacebar_w470_nor.png);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton::pressed\n"
"{\n"
"background-image: url(:/sa/image/KeyBoard/btn_spacebar_w470_click.png);\n"
"}\n"
"/************************outdoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton\n"
"{\n"
"background-image: url(:/sa/image/KeyBoard/btn_spacebar_w470_nor.png);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton::pressed\n"
"{\n"
"background-image: url(:/sa/image/KeyBoard/btn_spacebar_w470_click.png);\n"
"}\n"
"\n"
"/************************night**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton\n"
"{\n"
"	background-color: #9A8666;\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton::pressed\n"
"{\n"
"	background-color: #FB"
                        "9B00;\n"
"}\n"
"\n"
"\n"
""));
        key_x = new QPushButton(widget);
        key_x->setObjectName(QStringLiteral("key_x"));
        key_x->setGeometry(QRect(210, 180, 50, 50));
        key_x->setFocusPolicy(Qt::NoFocus);
        key_Left_Alt = new QPushButton(widget);
        key_Left_Alt->setObjectName(QStringLiteral("key_Left_Alt"));
        key_Left_Alt->setGeometry(QRect(90, 240, 50, 50));
        key_Left_Alt->setFocusPolicy(Qt::NoFocus);
        key_Left_Alt->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	text-align:left;\n"
"	padding-left:11px;\n"
"}\n"
"/************************indoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton\n"
"{\n"
"background-color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton::pressed\n"
"{\n"
"background-color:rgba(255, 181, 0, 1);\n"
"}\n"
"/************************outdoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton\n"
"{\n"
"background-color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton::pressed\n"
"{\n"
"background-color:rgba(255, 181, 0, 1);\n"
"}\n"
"\n"
"/************************night**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton\n"
"{\n"
"	background-color: rgb(119, 103, 79);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton::pressed\n"
"{\n"
"	background-color: rgb(251, 156, 0);\n"
"}\n"
""));
        key_p = new QPushButton(widget);
        key_p->setObjectName(QStringLiteral("key_p"));
        key_p->setGeometry(QRect(630, 60, 50, 50));
        key_p->setFocusPolicy(Qt::NoFocus);
        key_leftFn = new QPushButton(widget);
        key_leftFn->setObjectName(QStringLiteral("key_leftFn"));
        key_leftFn->setGeometry(QRect(0, 240, 80, 50));
        key_leftFn->setFocusPolicy(Qt::NoFocus);
        key_leftFn->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	text-align:left;\n"
"	padding-left:11px;\n"
"}\n"
"/************************indoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton\n"
"{\n"
"background-color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton::pressed\n"
"{\n"
"background-color:rgba(255, 181, 0, 1);\n"
"}\n"
"/************************outdoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton\n"
"{\n"
"background-color:rgba(123, 123, 123, 1);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton::pressed\n"
"{\n"
"background-color:rgba(255, 181, 0, 1);\n"
"}\n"
"\n"
"/************************night**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton\n"
"{\n"
"	background-color: rgb(119, 103, 79);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton::pressed\n"
"{\n"
"	background-color: rgb(251, 156, 0);\n"
"}\n"
""));
        key_e = new QPushButton(widget);
        key_e->setObjectName(QStringLiteral("key_e"));
        key_e->setGeometry(QRect(210, 60, 50, 50));
        key_e->setFocusPolicy(Qt::NoFocus);
        key_Right = new QPushButton(widget);
        key_Right->setObjectName(QStringLiteral("key_Right"));
        key_Right->setGeometry(QRect(810, 240, 50, 50));
        key_Right->setFocusPolicy(Qt::NoFocus);
        key_Right->setStyleSheet(QLatin1String("/************************indoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton\n"
"{\n"
"color:rgba(0,0,0,0);\n"
"background-image: url(:/sa/image/KeyBoard/btn_right_w50_nor.png);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"indoor\"] QPushButton::pressed\n"
"{\n"
"color:rgba(0,0,0,0);\n"
"background-image: url(:/sa/image/KeyBoard/btn_right_w50_click.png);\n"
"}\n"
"/************************outdoor**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton\n"
"{\n"
"color:rgba(0,0,0,0);\n"
"background-image: url(:/sa/image/KeyBoard/btn_right_w50_nor.png);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"outdoor\"] QPushButton::pressed\n"
"{\n"
"color:rgba(0,0,0,0);\n"
"background-image: url(:/sa/image/KeyBoard/btn_right_w50_click.png);\n"
"}\n"
"\n"
"/************************night**************************/\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton\n"
"{\n"
"	padding-left:109px;\n"
"	color: #FBDBA7;\n"
"	border-"
                        "image: url(:/sa/image/night/btn_right_w50_nor.png);\n"
"}\n"
"#SA_Dialog_VirtualKeyboard[status = \"night\"] QPushButton::pressed\n"
"{\n"
"	border-image: url(:/sa/image/night/btn_right_w50_click.png);\n"
"}\n"
""));

        retranslateUi(SA_Dialog_VirtualKeyboard);

        QMetaObject::connectSlotsByName(SA_Dialog_VirtualKeyboard);
    } // setupUi

    void retranslateUi(QWidget *SA_Dialog_VirtualKeyboard)
    {
        SA_Dialog_VirtualKeyboard->setWindowTitle(QApplication::translate("SA_Dialog_VirtualKeyboard", "Form", 0));
        SA_Dialog_VirtualKeyboard->setProperty("status", QVariant(QApplication::translate("SA_Dialog_VirtualKeyboard", "night", 0)));
        SA_Dialog_VirtualKeyboard->setProperty("pp", QVariant(QApplication::translate("SA_Dialog_VirtualKeyboard", "night", 0)));
        key_LeftShift->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "Shift", 0));
        key_Right_Alt->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "Alt", 0));
        key_f->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "f", 0));
        key_Slash->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "/", 0));
        key_l->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "l", 0));
        key_Delete->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "Delete", 0));
        key_d->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "d", 0));
        key_right_Fn->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "Fn", 0));
        key_s->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "s", 0));
        key_6->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "6", 0));
        key_g->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "g", 0));
        key_BracketLeft->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "[", 0));
        key_k->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "k", 0));
        key_4->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "4", 0));
        key_RightShift->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "Shift", 0));
        key_c->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "c", 0));
        key_Up->setText(QString());
        key_u->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "u", 0));
        key_v->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "v", 0));
        key_Equal->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "=", 0));
        key_j->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "j", 0));
        key_0->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "0", 0));
        key_w->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "w", 0));
        key_z->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "z", 0));
        key_Backslash->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "\\", 0));
        key_Apostrophe->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "'", 0));
        key_i->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "i", 0));
        key_QuoteLeft->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "`", 0));
        key_Minus->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "-", 0));
        key_BackSpace->setText(QString());
        key_Esc->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "Esc", 0));
        key_b->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "b", 0));
        key_Comma->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", ",", 0));
        key_Tab->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "Tab", 0));
        key_r->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "r", 0));
        key_t->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "t", 0));
        key_Period->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", ".", 0));
        key_1->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "1", 0));
        key_y->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "y", 0));
        key_3->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "3", 0));
        key_Enter->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "Enter", 0));
        key_m->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "m", 0));
        key_n->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "n", 0));
        key_2->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "2", 0));
        key_o->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "o", 0));
        key_Semicolon->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", ";", 0));
        key_q->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "q", 0));
        key_7->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "7", 0));
        key_a->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "a", 0));
        key_Down->setText(QString());
        key_Left->setText(QString());
        key_CapsLock->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "Caps", 0));
        key_9->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "9", 0));
        key_h->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "h", 0));
        key_8->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "8", 0));
        key_BracketRight->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "]", 0));
        key_5->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "5", 0));
        key_Space->setText(QString());
        key_x->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "x", 0));
        key_Left_Alt->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "Alt", 0));
        key_p->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "p", 0));
        key_leftFn->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "Fn", 0));
        key_e->setText(QApplication::translate("SA_Dialog_VirtualKeyboard", "e", 0));
        key_Right->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SA_Dialog_VirtualKeyboard: public Ui_SA_Dialog_VirtualKeyboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SA_DIALOG_VIRTUALKEYBOARD_H
