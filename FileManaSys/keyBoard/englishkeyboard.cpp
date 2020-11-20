#include "englishkeyboard.h"
#include "wininfolistdialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QList>
#include <QWidget>
#include <QFont>
#define  Esc         0
#define  Back        14
#define  Tab         15
#define  Delete      29
#define  Caps        30
#define  Enter       42
#define  Space       58
#define  Up          54
#define  Down        61
#define  Left        60
#define  Right       62
#define  Left_Shift  43
#define  Right_Shift 55
#define  Left_Fn     56
#define  Right_Fn    63
#define  Left_Alt    57
#define  Right_Alt   59
const int fnButtons[18] = {Esc, Back, Tab, Delete, Caps, Enter, Up, Down,
                         Left, Right, Left_Shift, Right_Shift, Left_Fn, Right_Shift,
                        Left_Fn, Right_Fn, Left_Alt, Right_Alt};

#define WARNNING_MSG             qDebug() << "message";//WarningBox::instance()->showMessage(INPUT_STR_FORMAT_WRONG, QT_TRANSLATE_NOOP("WarningBox","Warning"), true);
EnglishKeyboard::EnglishKeyboard(QWidget *parent, int funcMode)
    :KeyBoard(parent)
    , m_funcMode(funcMode)
{
    initDialog();
    setDefaultStyleSheet();
    connect(&m_lettersGrp, SIGNAL(buttonClicked(int)), this, SLOT(slotLetterButtonClicked(int)));
    connect(&m_clearBtn, SIGNAL(clicked()), this, SLOT(slotClearBtnClicked()));
    //connect(WarningBox::instance(), &WarningBox::warningBoxClosed, this, &EnglishKeyboard::onWarningBoxClosed);
    //setAttribute(Qt::WA_TranslucentBackground, true);    

    if(0 == funcMode)
    {
        connect(p_buttonCancel, SIGNAL(clicked()), this, SLOT(reject()));
        connect(&m_closeBtn, SIGNAL(clicked()), this, SLOT(reject()));
        connect(p_buttonOK, SIGNAL(clicked()), this, SLOT(slotOkButtonClicked()));

    }
    else if(1 == funcMode)
    {
        connect(p_buttonCancel, SIGNAL(clicked()), this, SIGNAL(sigCancelBtnClicked()));
        connect(&m_closeBtn, SIGNAL(clicked()), this, SIGNAL(sigCancelBtnClicked()));
        connect(p_buttonOK, SIGNAL(clicked()), this, SIGNAL(sigOKBtnClicked()));
    }
}
//EnglishKeyboard *EnglishKeyboard::instance()
//{
//    static EnglishKeyboard obj(0);
//    return &obj;
//}

/**
* @brief: 输入告警框关闭槽函数
* @return: void
*/
void EnglishKeyboard::onWarningBoxClosed(int errorId)
{
    Q_UNUSED(errorId);
    if (isVisible())
    {
        m_inputLineEdit.setFocus();
        m_inputLineEdit.setSelection(m_inputLineEdit.text().size(), 0);
    }
}

/**
 * @brief EnglishKeyboard::reset
 *      重新配置键盘
 * @param num
 *      最大字符数量
 * @param str
 *      默认显示字符
 */
void EnglishKeyboard::reset(int num, QString str, int keyBoardType)
{
    this->raise();
    m_maxNum = num;
    m_keyBoardType = (ENGLISH_KEYBOARD_TYPE)keyBoardType;
    m_inputLineEdit.setText(str);
    m_inputLineEdit.setEchoMode(QLineEdit::Normal);
    m_inputLineEdit.setMaxLength(num);
    m_inputLineEdit.setFocus();
    m_lettersFrame.setVisible(true);
    slotShiftButtonClicked(false);
    changeCase(false);
    slotCapsButtonClicked(false);
    setTrText();
    if(1 == m_funcMode)
    {
        m_inputLineEdit.setSelection(0, 10);
    }
}

/**
 * @brief EnglishKeyboard::setEchoMode
 *      设置键盘回显模式（用于输入密码）
 * @param mode
 *      可参考QLineEdit::EchoMode
 */
void EnglishKeyboard::setEchoMode(QLineEdit::EchoMode mode)
{
    m_inputLineEdit.setEchoMode(mode);

}

void EnglishKeyboard::slotLetterButtonClicked(int id)
{
    int strlen = m_inputLineEdit.text().toLocal8Bit().size();

    if (strlen > m_maxNum)
    {
       return;
    }


    if (Space == id)
    {
        m_inputLineEdit.insert(" ");
    }
    else if (8 == id && (m_letterBtns[Left_Shift].isChecked() || m_letterBtns[Right_Shift].isChecked() ))
    {
        m_inputLineEdit.insert("&");
    }
    else
    {
        m_inputLineEdit.insert(m_letterBtns[id].text());
    }
}

void EnglishKeyboard::slotOkButtonClicked()
{
    int strlen = 0;
#ifdef _WIN32
    strlen = m_inputLineEdit.text().toLocal8Bit().size();
#else __linux__
    if (m_inputLineEdit.text().contains("￥"))
    {
        QStringList list = m_inputLineEdit.text().split("￥");
        strlen = m_inputLineEdit.text().toLocal8Bit().size() - (list.size() - 1);
    }
    else
    {
        strlen = m_inputLineEdit.text().toLocal8Bit().size();
    }
#endif
    if (strlen <= m_maxNum){
        if (processKeyBoardLimit())
        {
            accept();
        }
    } else {
        //WinInfoListDialog::instance()->showMsg(5, this);
       // WarningBox::instance()->showMessage(INPUT_OUTOF_LIMIT, QT_TRANSLATE_NOOP("WarningBox","Warning"), true);
    }
}


void EnglishKeyboard::slotClearBtnClicked()
{
    m_inputLineEdit.clear();
    m_inputLineEdit.setFocus();
}


bool EnglishKeyboard::processKeyBoardLimit()
{
    QString inputStr = m_inputLineEdit.text();
    if (m_keyBoardType == FILE_NAME_KEYBOARD)
    {
        QStringList character;
        character << "?" << "," << "@" << "#" << "$" << "&" << "(" << ")" << "\\" << "|" << ";"
            << "\'" << "\"" << "<" << ">";
        for (int i = 0; i < character.size(); ++i)
        {
            if (inputStr.contains(character[i])
                || inputStr.size() == 0
                || (inputStr.size() > 0 && inputStr.left(1) == " "))
            {
                WARNNING_MSG;
                return false;
            }
        }
        return true;
    }
    else if (m_keyBoardType == COUNTRY_NAME_KEYBOARD)
    {
        for (int j = 0; j < inputStr.length(); ++j)
        {
            QChar letter = inputStr.at(j);
            if (letter > 'z' || letter < 'A' || ('Z' < letter && letter < 'a'))
            {
                WARNNING_MSG;
                return false;
            }
        }
        return true;
    }
    else
    {
        return true;
    }
}

void EnglishKeyboard::slotBSButtonClicked()
{
    m_inputLineEdit.backspace();
}

void EnglishKeyboard::slotDELButtonClicked()
{
    m_inputLineEdit.del();
}

void EnglishKeyboard::slotBKButtonClicked()
{
    m_inputLineEdit.cursorBackward(false);
}

void EnglishKeyboard::slotNTButtonClicked()
{
    m_inputLineEdit.cursorForward(false);
}

void EnglishKeyboard::slotShiftButtonClicked(bool checked)
{
    if (checked)
    {
        if (!m_letterBtns[Left_Shift].isChecked())
        {
            m_letterBtns[Left_Shift].setChecked(true);
        }
        if (!m_letterBtns[Right_Shift].isChecked())
        {
            m_letterBtns[Right_Shift].setChecked(true);
        }
    }
    else
    {
        if (m_letterBtns[Left_Shift].isChecked())
        {
            m_letterBtns[Left_Shift].setChecked(false);
        }
        if (m_letterBtns[Right_Shift].isChecked())
        {
            m_letterBtns[Right_Shift].setChecked(false);
        }
    }
    changeCase(checked);
}

void EnglishKeyboard::slotCapsButtonClicked(bool checked)
{
    if (checked)
    {
        m_letterBtns[16].setText("Q");
        m_letterBtns[17].setText("W");
        m_letterBtns[18].setText("E");
        m_letterBtns[19].setText("R");
        m_letterBtns[20].setText("T");
        m_letterBtns[21].setText("Y");
        m_letterBtns[22].setText("U");
        m_letterBtns[23].setText("I");
        m_letterBtns[24].setText("O");
        m_letterBtns[25].setText("P");
        m_letterBtns[31].setText("A");
        m_letterBtns[32].setText("S");
        m_letterBtns[33].setText("D");
        m_letterBtns[34].setText("F");
        m_letterBtns[35].setText("G");
        m_letterBtns[36].setText("H");
        m_letterBtns[37].setText("J");
        m_letterBtns[38].setText("K");
        m_letterBtns[39].setText("L");
        m_letterBtns[44].setText("Z");
        m_letterBtns[45].setText("X");
        m_letterBtns[46].setText("C");
        m_letterBtns[47].setText("V");
        m_letterBtns[48].setText("B");
        m_letterBtns[49].setText("N");
        m_letterBtns[50].setText("M");
    }
    else
    {
        m_letterBtns[16].setText("q");
        m_letterBtns[17].setText("w");
        m_letterBtns[18].setText("e");
        m_letterBtns[19].setText("r");
        m_letterBtns[20].setText("t");
        m_letterBtns[21].setText("y");
        m_letterBtns[22].setText("u");
        m_letterBtns[23].setText("i");
        m_letterBtns[24].setText("o");
        m_letterBtns[25].setText("p");
        m_letterBtns[31].setText("a");
        m_letterBtns[32].setText("s");
        m_letterBtns[33].setText("d");
        m_letterBtns[34].setText("f");
        m_letterBtns[35].setText("g");
        m_letterBtns[36].setText("h");
        m_letterBtns[37].setText("j");
        m_letterBtns[38].setText("k");
        m_letterBtns[39].setText("l");
        m_letterBtns[44].setText("z");
        m_letterBtns[45].setText("x");
        m_letterBtns[46].setText("c");
        m_letterBtns[47].setText("v");
        m_letterBtns[48].setText("b");
        m_letterBtns[49].setText("n");
        m_letterBtns[50].setText("m");
    }
}

/**
 * @brief EnglishKeyboard::initDialog
 *          初始化界面
 */
void EnglishKeyboard::initDialog()
{
    m_padFrame.setParent(p_mainFrame);
    m_padFrame.setGeometry(30,20,950,370);
    m_InputFrame.setParent(&m_padFrame);
    m_InputFrame.setGeometry(230, 0, 490, 50);
    m_InputFrame.setStyleSheet("background-color: rgb(0, 0, 0);");

    m_inputLineEdit.setParent(&m_InputFrame);
    m_inputLineEdit.setGeometry(0,0,380,50);
    m_clearBtn.setParent(&m_InputFrame);
    m_clearBtn.setGeometry(387,3,100,44);
    m_clearBtn.setText("Clear");
    m_clearBtn.setStyleSheet("QPushButton{background-color: rgb(233, 233, 233);}\
                                    QPushButton:pressed {background-color: rgb(245, 193, 65);}");

    m_closeBtn.setParent(&m_padFrame);
    m_closeBtn.setGeometry(950 - 35, 0, 35, 35);
    m_closeBtn.setStyleSheet(
                "QPushButton{border-image:url(:/images/keyboardimage/btn_close_r35_nor.png);background-color:rgb(245,245,245);}"\
                "QPushButton:pressed {border-image:url(:/images/keyboardimage/btn_close_r35_click.png);background-color:rgb(245,245,245);}");

    p_buttonOK->setParent(p_mainFrame);
    p_buttonOK->setGeometry(p_mainFrame->geometry().width() - 80 - 30, p_mainFrame->geometry().height() - 30 - 30, 80, 30);
    p_buttonOK->setStyleSheet("");
    p_buttonOK->setStyleSheet("background-color: rgb(13, 94, 144);font-size:18px;color: rgb(250, 250, 250);");

    p_buttonCancel->setParent(p_mainFrame);
    p_buttonCancel->setGeometry(p_mainFrame->geometry().width() - 80*2 - 5 - 30, p_mainFrame->geometry().height() - 30 - 30, 80, 30);
    p_buttonCancel->setStyleSheet("");
    p_buttonCancel->setStyleSheet("QPushButton{background-color: rgb(7, 7, 7);font-size:18px;color: rgb(250, 250, 250);}\
                                    QPushButton:pressed {background-color: rgb(245, 193, 65);}");
    m_inputLineEdit.setObjectName("InputLineEdit");
    m_inputLineEdit.setContextMenuPolicy(Qt::NoContextMenu);
    m_inputLineEdit.setFocus();
    m_inputLineEdit.setFrame(false);
    m_inputLineEdit.setAlignment(Qt::AlignBottom);
    //m_inputLineEdit.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    m_inputLineEdit.setStyleSheet("font-size:30px; font-weight:bold; color: rgb(240, 179, 29); background-color: rgb(0, 0, 0);");

    m_lettersFrame.setParent(&m_padFrame);
    m_lettersFrame.setGeometry(0,80, 950, 290);

    initFnBtns();

    QList<int>indexCount;
    indexCount.append(14);
    indexCount.append(29);
    indexCount.append(42);
    indexCount.append(55);
    indexCount.append(63);
    int x = 0;
    int y = 0;
    int row = 0;
    m_lettersGrp.setParent(&m_lettersFrame);
    for (int index = 0; index < 64; ++index)
    {
        if (index > indexCount[row])
        {
            row++;
            x = 0;
            y += 60;
        }
        m_letterBtns[index].setParent(&m_lettersFrame);
        m_letterBtns[index].setFocusPolicy(Qt::NoFocus);
        m_letterBtns[index].setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        m_letterBtns[index].setGeometry(x, y, getButtonWidth(index), 50);
        x += (10 + m_letterBtns[index].width());
        insertLetterBtns(index);
    }


    p_buttonCancel->setObjectName("ButtonCancel");
    p_buttonCancel->setFocusPolicy(Qt::NoFocus);
    p_buttonCancel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    p_buttonCancel->setMinimumHeight(30);

    p_buttonOK->setObjectName("ButtonOK");
    p_buttonOK->setFocusPolicy(Qt::NoFocus);
    p_buttonOK->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    p_buttonCancel->setMinimumHeight(30);
    p_buttonCancel->setMinimumHeight(30);
}

void EnglishKeyboard::initFnBtns()
{
    //esc
    m_letterBtns[Esc].setObjectName("EscBtn");
    //back
    m_letterBtns[Back].setObjectName("BackBtn");
    connect(&m_letterBtns[Back], SIGNAL(clicked()), this, SLOT(slotBSButtonClicked()));
    //tab
    m_letterBtns[Tab].setObjectName("TabBtn");
    //del
    m_letterBtns[Delete].setObjectName("DeleteBtn");
    connect(&m_letterBtns[Delete], SIGNAL(clicked()), this, SLOT(slotDELButtonClicked()));
    //caps
    m_letterBtns[Caps].setObjectName("CapsBtn");
    m_letterBtns[Caps].setCheckable(true);
    m_letterBtns[Caps].setChecked(false);
    connect(&m_letterBtns[Caps],SIGNAL(clicked(bool)),this,SLOT(slotCapsButtonClicked(bool)));
    //enter
    m_letterBtns[Enter].setObjectName("EnterBtn");
    if(0 == m_funcMode)
    {
        connect(&m_letterBtns[Enter],SIGNAL(clicked()),this,SLOT(slotOkButtonClicked()));
    }
    else if(1 == m_funcMode)
    {
        connect(&m_letterBtns[Enter],SIGNAL(clicked()),this,SIGNAL(sigOKBtnClicked()));
    }
    //space
    m_letterBtns[Space].setObjectName("SpaceBtn");
    //up
    m_letterBtns[Up].setObjectName("UpBtn");
    connect(&m_letterBtns[Up], SIGNAL(clicked()), this, SLOT(slotBKButtonClicked()));
    //down
    m_letterBtns[Down].setObjectName("DownBtn");
    connect(&m_letterBtns[Down], SIGNAL(clicked()), this, SLOT(slotNTButtonClicked()));
    //left
    m_letterBtns[Left].setObjectName("LeftBtn");
    connect(&m_letterBtns[Left], SIGNAL(clicked()), this, SLOT(slotBKButtonClicked()));
    //right
    m_letterBtns[Right].setObjectName("RightBtn");
    connect(&m_letterBtns[Right], SIGNAL(clicked()), this, SLOT(slotNTButtonClicked()));
    //shift
    m_letterBtns[Left_Shift].setObjectName("LeftShiftBtn");
    m_letterBtns[Left_Shift].setCheckable(true);
    m_letterBtns[Left_Shift].setChecked(false);
    connect(&m_letterBtns[Left_Shift],SIGNAL(clicked(bool)),this,SLOT(slotShiftButtonClicked(bool)));
    m_letterBtns[Right_Shift].setObjectName("RightShiftBtn");
    m_letterBtns[Right_Shift].setCheckable(true);
    m_letterBtns[Right_Shift].setChecked(false);
    connect(&m_letterBtns[Right_Shift],SIGNAL(clicked(bool)),this,SLOT(slotShiftButtonClicked(bool)));
    //fn
    m_letterBtns[Left_Fn].setObjectName("LeftFntBtn");
    m_letterBtns[Right_Fn].setObjectName("RightFnBtn");
    //alt
    m_letterBtns[Left_Alt].setObjectName("LeftAltBtn");
    m_letterBtns[Right_Alt].setObjectName("RightAltBtn");

    m_letterBtns[0].setText("Esc");
    m_letterBtns[14].setText("");
    m_letterBtns[15].setText("Tab");
    m_letterBtns[29].setText("Delete");
    m_letterBtns[30].setText("Caps");
    //m_letterBtns[42].setText("Enter");
    m_letterBtns[43].setText("Shift");
    m_letterBtns[54].setText("");
    m_letterBtns[55].setText("Shift");
    m_letterBtns[56].setText("Fn");
    m_letterBtns[57].setText("Alt");
    m_letterBtns[58].setText("");
    m_letterBtns[59].setText("Alt");
    m_letterBtns[60].setText("");
    m_letterBtns[61].setText("");
    m_letterBtns[62].setText("");
    m_letterBtns[63].setText("Fn");

}

void EnglishKeyboard::insertLetterBtns(int index)
{
    bool isFnBtn = false;
    for(int i = 0; i < 18; ++i)
    {
        if(index == fnButtons[i])
        {
            isFnBtn = true;
            break;
        }

    }
    if(!isFnBtn)
    {
        m_lettersGrp.addButton(&(m_letterBtns[index]), index);
    }
}

int EnglishKeyboard::getButtonWidth(int index)
{
    switch (index)
    {
    case 15:
    case 29:
    case 56:
    case 63:
        return 80;
    case 30:
    case 14:
        return 110;
    case 43:
    case 55:
        return 140;
    case 42:
        return 170;
    case 58:
        return 470;
    default:
        return 50;
    }
}

/**
 * @brief EnglishKeyboard::setDefaultStyleSheet
 *          设置默认样式
 */
void EnglishKeyboard::setDefaultStyleSheet()
{
    /*
    m_padFrame.setStyleSheet(
                  "QLineEdit#TipLineEdit{background-color: rgb(0, 0, 0);font-size:18px;"\
                  "border-top-left-radius: 3px; border-top-right-radius: 3px; }"\
                  "QLineEdit#InputLineEdit{background-color: rgb(0, 0, 0);font-size:30px;"\
                  "border-bottom-left-radius: 3px;border-bottom-right-radius: 3px; }"\

                  "QPushButton{border-image:url(:/images/keyboardimage/btn_w50_nor.png);"\
                  "font-size:16px; font-weight:bold;color: rgb(0, 0, 0);}"\
                  "QPushButton:pressed{border-image:url(:/images/keyboardimage/btn_w50_click.png);"\
                  "font-size:16px; font-weight:bold;color: rgb(0, 0, 0);}"\

                  "#EscBtn{border-image:url(:/images/keyboardimage/btn_esc_w50_nor.png);}"\
                  "#EscBtn:pressed {border-image:url(:/images/keyboardimage/btn_esc_w50_click.png);}"\

                  "#BackBtn{border-image:url(:/images/keyboardimage/btn_del_w110_nor.png);}"\
                  "#BackBtn:pressed {border-image:url(:/images/keyboardimage/btn_del_w110_click.png);}"\

                  "#TabBtn{border-image:url(:/images/keyboardimage/btn_tab_w80_nor.png);}"\
                  "#TabBtn:pressed {border-image:url(:/images/keyboardimage/btn_tab_w80_click.png);}"\

                  "#DeleteBtn{border-image:url(:/images/keyboardimage/btn_del_w80_nor.png);}"\
                  "#DeleteBtn:pressed {border-image:url(:/images/keyboardimage/btn_del_w80_click.png);}"\

                  "#CapsBtn{border-image:url(:/images/keyboardimage/btn_caps_w110_nor.png);}"\
                  "#CapsBtn:pressed {border-image:url(:/images/keyboardimage/btn_caps_w110_click.png);}"\

                  "#EnterBtn{border-image:url(:/images/keyboardimage/btn_enter_170_nor.png);}"\
                  "#EnterBtn:pressed {border-image:url(:/images/keyboardimage/btn_enter_170_click.png);}"\

                  "#SpaceBtn{border-image:url(:/images/keyboardimage/btn_spacebar_w470_nor.png);}"\
                  "#SpaceBtn:pressed {border-image:url(:/images/keyboardimage/btn_spacebar_w470_click.png);}"\

                  "#UpBtn{border-image:url(:/images/keyboardimage/btn_up_w50_nor.png);}"\
                  "#UpBtn:pressed {border-image:url(:/images/keyboardimage/btn_up_w50_click.png);}"\

                  "#DownBtn{border-image:url(:/images/keyboardimage/btn_down_w50_nor.png);}"\
                  "#DownBtn:pressed {border-image:url(:/images/keyboardimage/btn_down_w50_click.png);}"\

                  "#LeftBtn{border-image:url(:/images/keyboardimage/btn_left_w50_nor.png);}"\
                  "#LeftBtn:pressed {border-image:url(:/images/keyboardimage/btn_left_w50_click.png);}"\

                  "#RightBtn{border-image:url(:/images/keyboardimage/btn_right_w50_nor.png);}"\
                  "#RightBtn:pressed {border-image:url(:/images/keyboardimage/btn_right_w50_click.png);}"\

                  "#LeftShiftBtn{border-image:url(:/images/keyboardimage/btn_shift_w140_nor.png);}"\
                  "#LeftShiftBtn:pressed {border-image:url(:/images/keyboardimage/btn_shift_w140_click.png);}"\

                  "#RightShiftBtn{border-image:url(:/images/keyboardimage/btn_esc_w50_nor.png);}"\
                  "#RightShiftBtn:pressed {border-image:url(:/images/keyboardimage/btn_esc_w50_click.png);}"\

                  "#LeftFntBtn{border-image:url(:/images/keyboardimage/btn_fn_w80_nor.png);}"\
                  "#LeftFntBtn:pressed {border-image:url(:/images/keyboardimage/btn_fn_w80_click.png);}"\

                  "#RightFnBtn{border-image:url(:/images/keyboardimage/btn_esc_w50_nor.png);}"\
                  "#RightFnBtn:pressed {border-image:url(:/images/keyboardimage/btn_esc_w50_click.png);}"\

                  "#LeftAltBtn{border-image:url(:/images/keyboardimage/btn_alt_w50_nor.png);}"\
                  "#LeftAltBtn:pressed {border-image:url(:/images/keyboardimage/btn_alt_w50_click.png);}"\

                  "#RightAltBtn{border-image:url(:/images/keyboardimage/btn_esc_w50_nor.png);}"\
                  "#RightAltBtn:pressed {border-image:url(:/images/keyboardimage/btn_esc_w50_click.png);}");
    */
    m_padFrame.setStyleSheet(
                  "QLineEdit#TipLineEdit{background-color: rgb(0, 0, 0);font-size:18px;"\
                  "border-top-left-radius: 3px; border-top-right-radius: 3px; }"\
                  "QLineEdit#InputLineEdit{background-color: rgb(0, 0, 0);font-size:30px;"\
                  "border-bottom-left-radius: 3px;border-bottom-right-radius: 3px; }"\

                  "QPushButton{background-color: rgb(233, 233, 233);border: 10px solid transparent;"\
                  "font-size:16px; font-weight:bold;color: rgb(0, 0, 0);}"\
                  "QPushButton:pressed{background-color: rgb(255, 181, 0);"\
                  "font-size:16px; font-weight:bold;color: rgb(0, 0, 0);}"\

                  "#EscBtn{background-color: rgb(197, 197, 197);}"\
                  "#EscBtn:pressed {background-color: rgb(255, 181, 0);}"\

                  "#BackBtn{border-image:url(:/images/keyboardimage/btn_del_w110_nor.png);}"\
                  "#BackBtn:pressed {border-image:url(:/images/keyboardimage/btn_del_w110_click.png);}"\

                  "#TabBtn{background-color: rgb(197, 197, 197);text-align:left;}"\
                  "#TabBtn:pressed {background-color: rgb(255, 181, 0);}"\

                  "#DeleteBtn{background-color: rgb(197, 197, 197);text-align:right;}"\
                  "#DeleteBtn:pressed {background-color: rgb(255, 181, 0);}"\

                  "#CapsBtn{background-color: rgb(197, 197, 197);text-align:left;}"\
                  "#CapsBtn:pressed {background-color: rgb(255, 181, 0);}"\
                    "#CapsBtn:checked {background-color: rgb(255, 181, 0);}"\

                  "#EnterBtn{border-image:url(:/images/keyboardimage/btn_enter_170_nor.png);}"\
                  "#EnterBtn:pressed {border-image:url(:/images/keyboardimage/btn_enter_170_click.png);}"\

                  "#UpBtn{border-image:url(:/images/keyboardimage/btn_up_w50_nor.png);}"\
                  "#UpBtn:pressed {border-image:url(:/images/keyboardimage/btn_up_w50_click.png);}"\

                  "#DownBtn{border-image:url(:/images/keyboardimage/btn_down_w50_nor.png);}"\
                  "#DownBtn:pressed {border-image:url(:/images/keyboardimage/btn_down_w50_click.png);}"\

                  "#LeftBtn{border-image:url(:/images/keyboardimage/btn_left_w50_nor.png);text-align:left;}"\
                  "#LeftBtn:pressed {border-image:url(:/images/keyboardimage/btn_left_w50_click.png);}"\

                  "#RightBtn{border-image:url(:/images/keyboardimage/btn_right_w50_nor.png);text-align:right;}"\
                  "#RightBtn:pressed {border-image:url(:/images/keyboardimage/btn_right_w50_click.png);}"\

                  "#LeftShiftBtn{background-color: rgb(197, 197, 197);text-align:left;}"\
                  "#LeftShiftBtn:pressed {background-color: rgb(255, 181, 0);}"\
                  "#LeftShiftBtn:checked {background-color: rgb(255, 181, 0);}"\

                  "#RightShiftBtn{background-color: rgb(197, 197, 197);text-align:right;}"\
                  "#RightShiftBtn:pressed {background-color: rgb(255, 181, 0);}"\
                    "#RightShiftBtn:checked {background-color: rgb(255, 181, 0);}"\

                  "#LeftFntBtn{background-color: rgb(197, 197, 197);text-align:left;}"\
                  "#LeftFntBtn:pressed {background-color: rgb(255, 181, 0);}"\

                  "#RightFnBtn{background-color: rgb(197, 197, 197);text-align:right;}"\
                  "#RightFnBtn:pressed {background-color: rgb(255, 181, 0);}"\

                  "#LeftAltBtn{background-color: rgb(197, 197, 197);}"\
                  "#LeftAltBtn:pressed {background-color: rgb(255, 181, 0);}"\

                  "#RightAltBtn{background-color: rgb(197, 197, 197);}"\
                  "#RightAltBtn:pressed {background-color: rgb(255, 181, 0);}");
}

/**
 * @brief EnglishKeyboard::changeCase
 *          大小写切换
 * @param upper
 *          大小写标记 true=大写，false=小写
 */
void EnglishKeyboard::changeCase(bool upper)
{
    /*
    if (upper) {
        m_letterBtns[0].setText("Esc");
        m_letterBtns[1].setText("~");
        m_letterBtns[2].setText("!");
        m_letterBtns[3].setText("@");
        m_letterBtns[4].setText("#");
        m_letterBtns[5].setText("$");
        m_letterBtns[6].setText("%");
        m_letterBtns[7].setText("^");
        m_letterBtns[8].setText("&");
        m_letterBtns[9].setText("*");
        m_letterBtns[10].setText("(");
        m_letterBtns[11].setText(")");
        m_letterBtns[12].setText("_");
        m_letterBtns[13].setText("+");
        m_letterBtns[14].setText("");
        m_letterBtns[15].setText("Tab");
        m_letterBtns[16].setText("q");
        m_letterBtns[17].setText("w");
        m_letterBtns[18].setText("e");
        m_letterBtns[19].setText("r");
        m_letterBtns[20].setText("t");
        m_letterBtns[21].setText("y");
        m_letterBtns[22].setText("u");
        m_letterBtns[23].setText("i");
        m_letterBtns[24].setText("o");
        m_letterBtns[25].setText("p");
        m_letterBtns[26].setText("[");
        m_letterBtns[27].setText("]");
        m_letterBtns[28].setText("\\");
        m_letterBtns[29].setText("Delete");
        m_letterBtns[30].setText("Caps");
        m_letterBtns[31].setText("a");
        m_letterBtns[32].setText("s");
        m_letterBtns[33].setText("d");
        m_letterBtns[34].setText("f");
        m_letterBtns[35].setText("g");
        m_letterBtns[36].setText("h");
        m_letterBtns[37].setText("j");
        m_letterBtns[38].setText("k");
        m_letterBtns[39].setText("l");
        m_letterBtns[40].setText(":");
        m_letterBtns[41].setText("\"");
        m_letterBtns[42].setText("Enter");
        m_letterBtns[43].setText("Shift");
        m_letterBtns[44].setText("z");
        m_letterBtns[45].setText("x");
        m_letterBtns[46].setText("c");
        m_letterBtns[47].setText("v");
        m_letterBtns[48].setText("b");
        m_letterBtns[49].setText("n");
        m_letterBtns[50].setText("m");
        m_letterBtns[51].setText("<");
        m_letterBtns[52].setText(">");
        m_letterBtns[53].setText("?");
        m_letterBtns[54].setText("");
        m_letterBtns[55].setText("Shift");
        m_letterBtns[56].setText("Fn");
        m_letterBtns[57].setText("Alt");
        m_letterBtns[58].setText("");
        m_letterBtns[59].setText("Alt");
        m_letterBtns[60].setText("");
        m_letterBtns[61].setText("");
        m_letterBtns[62].setText("");
        m_letterBtns[63].setText("Fn");
    } else {
        m_letterBtns[0].setText("Esc");
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
        m_letterBtns[14].setText("");
        m_letterBtns[15].setText("Tab");
        m_letterBtns[16].setText("q");
        m_letterBtns[17].setText("w");
        m_letterBtns[18].setText("e");
        m_letterBtns[19].setText("r");
        m_letterBtns[20].setText("t");
        m_letterBtns[21].setText("y");
        m_letterBtns[22].setText("u");
        m_letterBtns[23].setText("i");
        m_letterBtns[24].setText("o");
        m_letterBtns[25].setText("p");
        m_letterBtns[26].setText("[");
        m_letterBtns[27].setText("]");
        m_letterBtns[28].setText("\\");
        m_letterBtns[29].setText("Delete");
        m_letterBtns[30].setText("Caps");
        m_letterBtns[31].setText("a");
        m_letterBtns[32].setText("s");
        m_letterBtns[33].setText("d");
        m_letterBtns[34].setText("f");
        m_letterBtns[35].setText("g");
        m_letterBtns[36].setText("h");
        m_letterBtns[37].setText("j");
        m_letterBtns[38].setText("k");
        m_letterBtns[39].setText("l");
        m_letterBtns[40].setText(";");
        m_letterBtns[41].setText("'");
        m_letterBtns[42].setText("Enter");
        m_letterBtns[43].setText("Shift");
        m_letterBtns[44].setText("z");
        m_letterBtns[45].setText("x");
        m_letterBtns[46].setText("c");
        m_letterBtns[47].setText("v");
        m_letterBtns[48].setText("b");
        m_letterBtns[49].setText("n");
        m_letterBtns[50].setText("m");
        m_letterBtns[51].setText(",");
        m_letterBtns[52].setText(".");
        m_letterBtns[53].setText("/");
        m_letterBtns[54].setText("");
        m_letterBtns[55].setText("Shift");
        m_letterBtns[56].setText("Fn");
        m_letterBtns[57].setText("Alt");
        m_letterBtns[58].setText("");
        m_letterBtns[59].setText("Alt");
        m_letterBtns[60].setText("");
        m_letterBtns[61].setText("");
        m_letterBtns[62].setText("");
        m_letterBtns[63].setText("Fn");
    }
    */
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
}

void EnglishKeyboard::setTrText()
{
    p_buttonCancel->setText(tr("Cancel"));
    p_buttonOK->setText(tr("OK"));
}
