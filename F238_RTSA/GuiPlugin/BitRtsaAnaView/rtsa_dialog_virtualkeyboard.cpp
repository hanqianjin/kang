#include "rtsa_dialog_virtualkeyboard.h"
#include "ui_rtsa_dialog_virtualkeyboard.h"

RtSa_dialog_virtualkeyboard::RtSa_dialog_virtualkeyboard(QWidget *parent) :
    QWidget(parent),
    mParent(parent),
    ui(new Ui::RtSa_dialog_virtualkeyboard)
{
    ui->setupUi(this);
    mCapLockOn = 0;
//    mCtrlFlag = 0;
    mShiftFlag = 0;
    initKeyBoard();
}

RtSa_dialog_virtualkeyboard::~RtSa_dialog_virtualkeyboard()
{
    delete ui;
}
void RtSa_dialog_virtualkeyboard::initKeyBoard()
{
    qint32 btnCnt;

    key_btn.insert(ui->key_Esc,Qt::Key_Escape);
    key_btn.insert(ui->key_QuoteLeft,Qt::Key_QuoteLeft);
    key_btn.insert(ui->key_0,Qt::Key_0);
    key_btn.insert(ui->key_1,Qt::Key_1);
    key_btn.insert(ui->key_2,Qt::Key_2);
    key_btn.insert(ui->key_3,Qt::Key_3);
    key_btn.insert(ui->key_4,Qt::Key_4);
    key_btn.insert(ui->key_5,Qt::Key_5);
    key_btn.insert(ui->key_6,Qt::Key_6);
    key_btn.insert(ui->key_7,Qt::Key_7);
    key_btn.insert(ui->key_8,Qt::Key_8);
    key_btn.insert(ui->key_9,Qt::Key_9);
    key_btn.insert(ui->key_Minus,Qt::Key_Minus);
    key_btn.insert(ui->key_Equal,Qt::Key_Equal);
    key_btn.insert(ui->key_BackSpace,Qt::Key_Backspace);

    key_btn.insert(ui->key_Tab,Qt::Key_Tab);
    key_btn.insert(ui->key_BracketLeft,Qt::Key_BracketLeft);
    key_btn.insert(ui->key_BracketRight,Qt::Key_BracketRight);
    key_btn.insert(ui->key_Backslash,Qt::Key_Backslash);
    key_btn.insert(ui->key_Delete,Qt::Key_Delete);

    key_btn.insert(ui->key_CapsLock,Qt::Key_CapsLock);
    key_btn.insert(ui->key_Semicolon,Qt::Key_Semicolon);
    key_btn.insert(ui->key_Apostrophe,Qt::Key_Apostrophe);
    key_btn.insert(ui->key_Enter,Qt::Key_Enter);

    key_btn.insert(ui->key_LeftShift,Qt::Key_Shift);
    key_btn.insert(ui->key_Comma,Qt::Key_Comma);
    key_btn.insert(ui->key_Period,Qt::Key_Period);
    key_btn.insert(ui->key_Slash,Qt::Key_Slash);
    key_btn.insert(ui->key_Up,Qt::Key_Up);
    key_btn.insert(ui->key_RightShift,Qt::Key_Shift);

    key_btn.insert(ui->key_Left_Alt,Qt::Key_Alt);
    key_btn.insert(ui->key_Space,Qt::Key_Space);
    key_btn.insert(ui->key_Right_Alt,Qt::Key_Alt);
    key_btn.insert(ui->key_Left,Qt::Key_Left);
    key_btn.insert(ui->key_Down,Qt::Key_Down);
    key_btn.insert(ui->key_Right,Qt::Key_Right);

    key_btn.insert(ui->key_a,Qt::Key_A);
    key_btn.insert(ui->key_b,Qt::Key_B);
    key_btn.insert(ui->key_c,Qt::Key_C);
    key_btn.insert(ui->key_d,Qt::Key_D);
    key_btn.insert(ui->key_e,Qt::Key_E);
    key_btn.insert(ui->key_f,Qt::Key_F);
    key_btn.insert(ui->key_g,Qt::Key_G);
    key_btn.insert(ui->key_h,Qt::Key_H);
    key_btn.insert(ui->key_i,Qt::Key_I);
    key_btn.insert(ui->key_j,Qt::Key_J);
    key_btn.insert(ui->key_k,Qt::Key_K);
    key_btn.insert(ui->key_l,Qt::Key_L);
    key_btn.insert(ui->key_m,Qt::Key_M);
    key_btn.insert(ui->key_n,Qt::Key_N);
    key_btn.insert(ui->key_o,Qt::Key_O);
    key_btn.insert(ui->key_p,Qt::Key_P);
    key_btn.insert(ui->key_q,Qt::Key_Q);
    key_btn.insert(ui->key_r,Qt::Key_R);
    key_btn.insert(ui->key_s,Qt::Key_S);
    key_btn.insert(ui->key_t,Qt::Key_T);
    key_btn.insert(ui->key_u,Qt::Key_U);
    key_btn.insert(ui->key_v,Qt::Key_V);
    key_btn.insert(ui->key_w,Qt::Key_W);
    key_btn.insert(ui->key_x,Qt::Key_X);
    key_btn.insert(ui->key_y,Qt::Key_Y);
    key_btn.insert(ui->key_z,Qt::Key_Z);

    btnCnt = key_btn.size();
    for(qint32 i=0;i<btnCnt;i++)
    {
        connect(key_btn.keys().at(i),SIGNAL(clicked()),this,SLOT(btn_clicked()));
    }
}

void RtSa_dialog_virtualkeyboard::btn_clicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    qint32 keyValue;
    Qt::KeyboardModifier keyMod;
    QString keyText;
    //get key value and key text
    keyValue = key_btn.value(btn);
    if(keyValue>=0x21 && keyValue<=0x7E)
    {
        if(keyValue == Qt::Key_7 && mShiftFlag)
        {
            keyText = "&";
        }
        else
        {
            keyText = btn->text();
        }
    }else if(keyValue == Qt::Key_Space){
        keyText = " ";
    }else
    {
        keyText = "";
    }

    if(Qt::Key_Alt == keyValue)
    {
        keyMod = Qt::AltModifier;
    }else if(Qt::Key_Control == keyValue)
    {
        keyMod = Qt::ControlModifier;
    }else if(Qt::Key_Shift == keyValue)
    {
        keyMod = Qt::ShiftModifier;
    }else
    {
        keyMod = Qt::NoModifier;
    }
    //send key event
    QKeyEvent event(QKeyEvent::KeyPress,keyValue, keyMod,keyText);

    keyPressEvent(&event);
    return;
}

void RtSa_dialog_virtualkeyboard::keyPressEvent(QKeyEvent *event)
{
    qint32 keyValue = event->key();
    if(event->key() == Qt::Key_PowerOff)
    {
        if(!event->isAutoRepeat())
        {
            QApplication::sendEvent(this->parent(),event);
        }
        return;
    }
    if(keyValue == Qt::Key_CapsLock)
    {
        CapslockChange();
        return;
    }
    else if(keyValue == Qt::Key_Shift)
    {
        ShiftChange();
        return;
    }
    QApplication::sendEvent(mParent,event);
}

void RtSa_dialog_virtualkeyboard::CapslockChange()
{
    mCapLockOn = !mCapLockOn;
    QPushButton *btn;
    if(mCapLockOn)
    {
        for(qint32 i = Qt::Key_A;i<=Qt::Key_Z;i++)
        {
            btn = key_btn.key(i);
            btn->setText(btn->text().toUpper());
        }
    }
    else
    {
        for(qint32 i = Qt::Key_A;i<=Qt::Key_Z;i++)
        {
            btn = key_btn.key(i);
            btn->setText(btn->text().toLower());
        }
    }
    return;
}

void RtSa_dialog_virtualkeyboard::ShiftChange()
{
    mShiftFlag = !mShiftFlag;
    if(mShiftFlag)
    {
        key_btn.key('`')->setText("~");
        key_btn.key('1')->setText("!");
        key_btn.key('2')->setText("@");
        key_btn.key('3')->setText("#");
        key_btn.key('4')->setText("$");
        key_btn.key('5')->setText("%");
        key_btn.key('6')->setText("^");
        key_btn.key('7')->setText("&&");
        key_btn.key('8')->setText("*");
        key_btn.key('9')->setText("(");
        key_btn.key('0')->setText(")");
        key_btn.key('-')->setText("_");
        key_btn.key('=')->setText("+");
        key_btn.key('[')->setText("[");
        key_btn.key(']')->setText("]");
        key_btn.key('\\')->setText("\\");
        key_btn.key(';')->setText(":");
        key_btn.key('\'')->setText("\"");
        key_btn.key(',')->setText("<");
        key_btn.key('.')->setText(">");
        key_btn.key('/')->setText("?");


    }
    else
    {
        key_btn.key('`')->setText("`");
        key_btn.key('1')->setText("1");
        key_btn.key('2')->setText("2");
        key_btn.key('3')->setText("3");
        key_btn.key('4')->setText("4");
        key_btn.key('5')->setText("5");
        key_btn.key('6')->setText("6");
        key_btn.key('7')->setText("7");
        key_btn.key('8')->setText("8");
        key_btn.key('9')->setText("9");
        key_btn.key('0')->setText("0");
        key_btn.key('-')->setText("-");
        key_btn.key('=')->setText("=");
        key_btn.key('[')->setText("[");
        key_btn.key(']')->setText("]");
        key_btn.key('\\')->setText("\\");
        key_btn.key(';')->setText(";");
        key_btn.key('\'')->setText("\'");
        key_btn.key(',')->setText(",");
        key_btn.key('.')->setText(".");
        key_btn.key('/')->setText("/");
    }

/*
    if (upper)
    {
    m_letterBtns[1].setText("~");
    m_letterBtns[2].setText("!");
    m_letterBtns[3].setText("@");
    m_letterBtns[4].setText("#");
    m_letterBtns[5].setText("$");
    m_letterBtns[6].setText("%");
    m_letterBtns[7].setText("^");
    m_letterBtns[8].setText("&&");
    m_letterBtns[9].setText("*");
    m_letterBtns[10].setText("(");
    m_letterBtns[11].setText(")");
    m_letterBtns[12].setText("_");
    m_letterBtns[13].setText("+");
    m_letterBtns[26].setText("[");
    m_letterBtns[27].setText("]");
    m_letterBtns[28].setText("\\");
    m_letterBtns[40].setText(":");
    m_letterBtns[41].setText("\"");
    m_letterBtns[51].setText("<");
    m_letterBtns[52].setText(">");
    m_letterBtns[53].setText("?");
    }
    else
    {
    m_letterBtns[1].setText("`");
    m_letterBtns[2].setText("1");
    m_letterBtns[3].setText("2");
    m_letterBtns[4].setText("3");
    m_letterBtns[5].setText("4");
    m_letterBtns[6].setText("5");
    m_letterBtns[7].setText("6");
    m_letterBtns[8].setText("7");
    m_letterBtns[9].setText("8");
    m_letterBtns[10].setText("9");
    m_letterBtns[11].setText("0");
    m_letterBtns[12].setText("-");
    m_letterBtns[13].setText("=");
    m_letterBtns[26].setText("[");
    m_letterBtns[27].setText("]");
    m_letterBtns[28].setText("\\");
    m_letterBtns[40].setText(";");
    m_letterBtns[41].setText("'");
    m_letterBtns[51].setText(",");
    m_letterBtns[52].setText(".");
    m_letterBtns[53].setText("/");
    m_letterBtns[54].setText("");
    }
*/
}
