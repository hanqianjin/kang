#include "KeyBoard.h"

#define INITIAL_POS_VALUE                   0
#define KEYBOARD_X_POS                      110
#define KEYBOARD_Y_POS                      80
#define KEYBOARD_WIDTH_DIFFERENCE_VALUE     224
#define KEYBOARD_HEIGHT_DIFFERENCE_VALUE    150
KeyBoard::KeyBoard(QWidget *parent, int dialogType)
    :WinDialog(dialogType, parent)
    , p_buttonCancel(new QPushButton)
    , p_buttonOK(new QPushButton)
    , p_mainFrame(new QFrame(this))
{
    this->setFocus();
    //setAttribute(Qt::WA_TranslucentBackground, true);
    //setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    //this->setGeometry(INITIAL_POS_VALUE, 60, 1278, 715);
    this->setObjectName("keypadFrame");
    //p_mainFrame->setGeometry(155, 135, 1010, 490);
    p_mainFrame->setObjectName("keypad_mainFrame");
    setDefaultStyle();

    this->setGeometry(155, 195, 1010, 490);
    p_mainFrame->setGeometry(0, 0, 1010, 490);
}

KeyBoard::~KeyBoard()
{

}

void KeyBoard::setDefaultStyle()
{
    this->setStyleSheet("#keypad_mainFrame{background-color: rgb(250, 250, 250);}");
}
