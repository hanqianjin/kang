/*********************************************************************
 * Copyright(c) 2014, 大豪信息技术有限公司上海研发部
 *
 * All Rights reserved
 *
 * 文件名称：softkeypad.h
 * 概   要：在调用该类时，画面会出现一个软件盘供用户输入, sigOkPressSignal()
 *          信号表示用户输入完毕，sigCancelPressSignal() , 表示用户取消输入.
 *          setTipInfor(QString str)设置输入框的提示信息, getInputStr() 获取
 *          用户输入的内容
 *
 * 当前版本：V1.1.0
 * 作   者：葛 海 浪
 * 完成日期：2015-9-29
 *
 * 修改版本：1.0.0
 * 修改说明：替换原有的softkeypad，舍去UI设计师界面
 * 修改作者：葛 海 浪
 *
 ********************************************************************/
#include "softkeypad.h"
//#include "wininfolistdialog.h"
#include "../common/MessageBox.h"
#include "../common/Public.h"
#include <QTextCodec>
#include <QSqlError>

#define WARNNING_MSG(errId)              WarningBox::instance()->showMessage(errId, QT_TRANSLATE_NOOP("WarningBox","Warning"));
#define ENABLE_COLOR QString("color: rgb(255,255,255)")
#define DISENABLE_COLOR QString("color: rgb(210,189,170)")

SoftKeyPad *SoftKeyPad::instance()
{
    static SoftKeyPad instance(F270App->mainWindow());
    return &instance;
}

/**
 * @brief EnglishKeyboard::reset
 *      重新配置键盘
 * @param num
 *      最大字符数量
 * @param str
 *      默认显示字符
 */
void SoftKeyPad::reset(int num, QString str, int keyBoardType)
{
    Q_UNUSED(keyBoardType);
    this->raise();
    //init
    m_englishState = LatterSmall;
    m_chineseState = LatterSmall;
    m_maxNum = num;
    m_listChinese.clear();
    m_inputStr.clear();
    m_singleLetter.clear();
    m_inputLetter.clear();
    m_lineInputLetter.clear();
    p_chineseShowWidget->setHidden(true);
    m_firstInputFlag = true;

    p_textEdit->clear();
    p_textEdit->setText(tr("Up to %1 characters").arg(m_maxNum));

    p_lineEdit->clear();
    p_lineEdit->setText(str);
    p_lineEdit->setFocus();
    m_cursorPosition = p_lineEdit->cursorPosition();

    //恢复初始界面
    if (DevConfigPtr->systemConfig.environmentCfg.languageType == Language_Type_English)
    {
        slotButtonEnglishClicked();
    }
    else if (DevConfigPtr->systemConfig.environmentCfg.languageType == Language_Type_Chinese)
    {
        slotButtonChineseClicked();
    }
    
    setTrText();
}

SoftKeyPad::SoftKeyPad(QWidget *parent)
    : KeyBoard(parent)
    , m_currentWidth(0)
    , m_currentHeight(0)
    , m_englishState(LatterSmall)
    , m_chineseState(LatterSmall)
    , m_listCount(0)
    , m_listChineseID(0)
    , m_current_choice(KeyInput_English)
    , m_cursorPosition(0)
    , m_firstInputFlag(true)
    , p_centerWidget(NULL)
    , p_chineseShowWidget(NULL)
    , p_textEdit(NULL)
    , p_lineEdit(NULL)
    , p_groupEnglish(NULL)
    , p_groupChinese(NULL)
    , p_groupSymbol(NULL)
    , p_groupChineseShow(NULL)
    , p_buttonBS(NULL)
    , p_buttonDEL(NULL)
    , p_buttonLeftMove(NULL)
    , p_buttonRightMove(NULL)
    , p_buttonEnglish(NULL)
    , p_buttonSymbol(NULL)
    , p_buttonChinese(NULL)
    , m_inputStr("")
    , m_singleLetter("")
    , m_inputLetter("")
    , m_lineInputLetter("")
    , m_maxNum(2)
{
    setWindowsLayout();
    setCenterWidgetLayout();
    setDefaultStyleSheet();
    connectDatabase();
    connectFunC();
    setAttribute(Qt::WA_TranslucentBackground, true); 
	hide();
}

/**
* @brief: 关机消息槽函数
* @return: void
*/
void SoftKeyPad::onPowerOff()
{
	m_db.close();
}

/*
 * 功能：
 * 	  获取用户输入的文字
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  QString
 */
QString SoftKeyPad::getInputStr()
{

    return m_inputStr;
}

/*
* 功能：
* 	   设置窗体大小
*
* 参数：
* 	  无
*
* 返回值：
* 	  无
*/
void SoftKeyPad::setWindowsLayout()
{
    //    this->setAttribute(Qt::WA_TranslucentBackground, true);
    m_currentWidth = F270App->mainWindow()->width() - 200;
    m_currentHeight = F270App->mainWindow()->height() - 100;
    //resize(m_currentWidth, m_currentHeight);
}

/*
 * 功能：
 * 	  英文输入界面按钮单击事件
 *
 * 参数：
 * 	  int id
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::slotGroupEnglishClicked(int id)
{
    switch (id) {
    case 0: case 1: case 2: case 3:
    case 5: case 6: case 7: case 8:
    case 9: case 10: case 11: case 12:
    case 13: case 14: case 15: case 16:
    case 17: case 18: case 19: case 20:
    case 21: case 22: case 23: case 24:
    case 25: case 26: case 27: case 28:
    case 29: case 30: case 33: case 34:
    case 35: case 36: case 37: case 38:
    case 39: case 40: case 41: case 42:
    case 43:
        p_lineEdit->insert(p_groupEnglish->button(id)->text());
        break;
    case 4:
    {
        if(LatterSmall == m_englishState) {
            p_lineEdit->insert(p_groupEnglish->button(id)->text());
        } else if(LatterBig == m_englishState) {
            p_lineEdit->insert("&");
        }
        break;
    }
    case 31:    //Enter
        slotButtonOKClicked();
        break;
    case 44:
    case 46:
    {
        if(LatterSmall == m_englishState) {
            m_englishState = LatterBig;
        } else if(LatterBig == m_englishState) {
            m_englishState = LatterSmall;
        }
        setGroupEndlishText();
        break;
    }
    case 45:
        p_lineEdit->insert(" ");
        break;
    default:
        break;
    }
    m_cursorPosition = p_lineEdit->cursorPosition();
}

/*
 * 功能：
 * 	  符号输入界面按钮单击事件
 *
 * 参数：
 * 	  int id
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::slotGroupSymbolClicked(int id)
{
    switch (id) {
    case 7:
        p_lineEdit->insert("&");
        break;
    default:
        p_lineEdit->insert(p_groupSymbol->button(id)->text());
        break;
    }
    m_cursorPosition = p_lineEdit->cursorPosition();
}

/*
 * 功能：
 * 	  中文输入界面按钮单击事件
 *
 * 参数：
 * 	  int id
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::slotGroupChineseClicked(int id)
{
    switch (id) {
    case 0: case 1: case 2: case 3: case 5:
    case 6: case 7: case 8: case 9: case 10:
    case 21: case 40: case 41: case 42: case 43:
    {
        if("" == m_inputLetter) {
            p_chineseShowWidget->setHidden(true);
            p_lineEdit->insert(p_groupChinese->button(id)->text());
            m_cursorPosition = p_lineEdit->cursorPosition();
        } else {
            // do nothing
        }
        break;
    }
    case 4:
    {
        if("" == m_inputLetter) {
            if(LatterSmall == m_chineseState) {
                p_lineEdit->insert(p_groupChinese->button(id)->text());
            } else if(LatterBig == m_chineseState) {
                p_lineEdit->insert("&");
            }
            m_cursorPosition = p_lineEdit->cursorPosition();
        } else {
            // do nothing
        }
        break;
    }
    case 11: case 12: case 13: case 14: case 15:
    case 16: case 17: case 18: case 19: case 20:
    case 22: case 23: case 24: case 25: case 26:
    case 27: case 28: case 29: case 30: case 33:
    case 34: case 35: case 36: case 37: case 38:
    case 39: case 46: case 47: case 48:
    {
        p_chineseShowWidget->setHidden(false);
        m_lineInputLetter += p_groupChinese->button(id)->text();
        if(m_firstInputFlag) {
            m_singleLetter = p_groupChinese->button(id)->text().toLower();
            m_firstInputFlag = false;
        }
        m_inputLetter += p_groupChinese->button(id)->text().toLower();
		p_lineEdit->insert(m_lineInputLetter);
		p_lineEdit->setSelection(m_cursorPosition, m_lineInputLetter.size());
        break;
    }
    case 31:        // enter
    {
        p_chineseShowWidget->setHidden(true);
        if("" == m_lineInputLetter) {
            slotButtonOKClicked();
        } else {
            p_lineEdit->insert(m_lineInputLetter);
            m_cursorPosition = p_lineEdit->cursorPosition();
            m_firstInputFlag = true;
            m_inputLetter = "";
            m_lineInputLetter = "";
        }
        break;
    }
    case 44:
    case 49:    // Shift
    {
        if(LatterSmall == m_chineseState) {
            m_chineseState = LatterBig;
        } else if(LatterBig == m_chineseState) {
            m_chineseState = LatterSmall;
        }

        setGroupChineseText();
        break;
    }
    case 45:
    {
        if("" == m_inputLetter) {
            p_lineEdit->insert(" ");
            m_cursorPosition = p_lineEdit->cursorPosition();
        } else {
            // do nothing
        }
    }
    default:
        break;
    }
}

/**
* @brief：输入框内容变化槽函数
* @param: text
* @return: void
*/
void SoftKeyPad::onLineEditChange(const QString &text)
{
	Q_UNUSED(text);

	m_listChinese.clear();
	m_listChineseID = 0;
	if (selectSQL())
	{
		chineseShow();
	}
	else
	{
		// 汉字数据库失效后，中文输入法正常输入英文
		processChineseToEnglishOrSymbol();
		deselectAndClearInputLetter();
	}
}

/*
 * 功能：
 * 	  中文显示界面按钮单击事件
 *
 * 参数：
 * 	  int id
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::slotGroupChineseShowClicked(int id)
{
    switch (id) {
    case 0:
        leftMove();
        p_groupChineseShow->button(8)->setEnabled(true);
		p_groupChineseShow->button(8)->setStyleSheet(ENABLE_COLOR);
        break;
    case 1: case 2: case 3: case 4:
    case 5: case 6: case 7:
        if("" == p_groupChineseShow->button(id)->text()) {
            // do nothing
        } else {
			QString str = p_groupChineseShow->button(id)->text();
			if (OK != isLetter(str))
			{
				m_lineInputLetter.clear();
           	 	m_firstInputFlag = true;
            	m_inputLetter = "";
            	m_lineInputLetter = "";
            	m_listCount = 0;
				p_chineseShowWidget->setHidden(true);
				p_lineEdit->insert(str);
				m_cursorPosition = p_lineEdit->cursorPosition();
			}
			else
			{
				m_lineInputLetter += str;
				p_chineseShowWidget->setHidden(false);
				p_lineEdit->insert(m_lineInputLetter);
				p_lineEdit->setSelection(m_cursorPosition, m_lineInputLetter.size());
			}
        }
        break;
    case 8:
        rightMove();
        p_groupChineseShow->button(0)->setEnabled(true);
		p_groupChineseShow->button(0)->setStyleSheet(ENABLE_COLOR);
        break;
    default:
        break;
    }
}

/**
* @brief：判断是否是字母
* @param: str
* @return: int
*/
int SoftKeyPad::isLetter(QString str)
{
	int pos = 0;
	QRegExp rx("[a-z]*");
	QRegExpValidator v(rx);
	int rc = v.validate(str, pos);

	if (QValidator::Acceptable == rc)
	{
		return OK;
	}
	return ERR;
}

/*
 * 功能：
 * 	  英文切换按钮下押事件，改变当前输入界面
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::slotButtonEnglishClicked()
{
    m_current_choice = KeyInput_English;
    setEnglishShow();
    processChineseToEnglishOrSymbol();
	deselectAndClearInputLetter();
    p_buttonChinese->setText(tr("C"));
    p_buttonEnglish->setText(tr("E"));
    p_buttonSymbol->setStyleSheet("QPushButton{border-image:url(../resources/controlicon/keypad/symbol_normal.png);}"\
        "font-family:'Arial Regular';font-size:20px;}"\
        "QPushButton:pressed{border-image:url(../resources/controlicon/keypad/symbol_press.png);"\
        "font-family:'Arial Regular';font-size:20px;}");
}

/*
 * 功能：
 * 	  中文切换按钮下押事件，改变当前输入界面
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::slotButtonChineseClicked()
{
    m_current_choice = KeyInput_Chinese;
    setChineseShow();
    p_buttonChinese->setText(tr("中"));
    p_buttonEnglish->setText(tr("英"));
    p_buttonSymbol->setStyleSheet("QPushButton{border-image:url(../resources/controlicon/keypad/symbol_ch.png);}"\
        "font-family:'Arial Regular';font-size:20px;}"\
        "QPushButton:pressed{border-image:url(../resources/controlicon/keypad/symbol_ch_p.png);"\
        "font-family:'Arial Regular';font-size:20px;}");
}

/*
 * 功能：
 * 	  符号切换按钮下押事件，改变当前输入界面
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::slotButtonSymbolClicked()
{
    m_current_choice = KeyInput_Symbol;
    setSymbolShow();
    processChineseToEnglishOrSymbol();
	deselectAndClearInputLetter();
    defaultStyle();
}

/**
* @brief：取消中文选中，并清空用户输入字符串
* @return: void
*/
void SoftKeyPad::deselectAndClearInputLetter()
{
	if (!m_lineInputLetter.isEmpty())
	{
		int size = p_lineEdit->text().size();
		p_lineEdit->setSelection(size, 0);
		m_cursorPosition = size;
		m_lineInputLetter.clear();
	}
}

/**
* @brief：处理中文输入下中文显示的widget未隐藏时切换到英文输入或符号输入的界面响应
* @return: void
*/
void SoftKeyPad::processChineseToEnglishOrSymbol()
{
    if (p_chineseShowWidget->isVisible())
    {
        p_chineseShowWidget->setHidden(true);
        m_cursorPosition = p_lineEdit->cursorPosition();
        m_firstInputFlag = true;
        m_inputLetter = "";
    }
}

/*
 * 功能：
 * 	  BS输入界面按钮单击事件
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::slotButtonBSPressed()
{
    switch (m_current_choice) {
    case KeyInput_English:
    case KeyInput_Symbol:
    {
        QKeyEvent backPress(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);
        QCoreApplication::sendEvent(p_lineEdit, &backPress);
        m_cursorPosition = p_lineEdit->cursorPosition();
        break;
    }
    case KeyInput_Chinese:
    {
        if("" == m_inputLetter) {
            p_lineEdit->backspace();
            m_cursorPosition = p_lineEdit->cursorPosition();
        } else {
            
            int size = m_lineInputLetter.size();
            m_lineInputLetter = m_lineInputLetter.remove(size - 1, 1);
            p_lineEdit->insert(m_lineInputLetter);
            p_lineEdit->setSelection(m_cursorPosition, m_lineInputLetter.size());
            m_inputLetter = m_lineInputLetter.toLower();
			if (0 == m_listChinese.size()) {
                p_chineseShowWidget->setHidden(true);
                m_firstInputFlag = true;
            } else {
                p_chineseShowWidget->setHidden(false);
                m_firstInputFlag = false;
            }
        }
    }
    default:
        break;
    }
}

/*
 * 功能：
 * 	  DEL按钮单击事件
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::slotButtonDELPressed()
{
    switch (m_current_choice) {
    case KeyInput_English:
    case KeyInput_Symbol:
    {
        QKeyEvent deletePress(QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier);
        QCoreApplication::sendEvent(p_lineEdit, &deletePress);
        QKeyEvent deleteRelease(QEvent::KeyRelease, Qt::Key_Delete, Qt::NoModifier);
        QCoreApplication::sendEvent(p_lineEdit, &deleteRelease);
        break;
    }
    case KeyInput_Chinese:
    {
        if("" == m_inputLetter) {
            QKeyEvent deletePress(QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier);
            QCoreApplication::sendEvent(p_lineEdit, &deletePress);
            QKeyEvent deleteRelease(QEvent::KeyRelease, Qt::Key_Delete, Qt::NoModifier);
            QCoreApplication::sendEvent(p_lineEdit, &deleteRelease);
        } else {
            // do nothing
        }
        break;
    }
    default:
        break;
    }
}

/*
 * 功能：
 * 	  move left按钮单击事件
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::slotButtonMoveLeftPressed()
{
    switch (m_current_choice) {
    case KeyInput_English:
    case KeyInput_Symbol:
    {
        QKeyEvent leftMovePress(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
        QCoreApplication::sendEvent(p_lineEdit, &leftMovePress);
        m_cursorPosition = p_lineEdit->cursorPosition();
        break;
    }
    case KeyInput_Chinese:
    {
        if("" == m_inputLetter) {
            QKeyEvent leftMovePress(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
            QCoreApplication::sendEvent(p_lineEdit, &leftMovePress);
            m_cursorPosition = p_lineEdit->cursorPosition();
        } else {
            // do nothing
        }
        break;
    }
    default:
        break;
    }
}

/*
 * 功能：
 * 	   move right按钮单击事件
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::slotButtonMoveRightPressed()
{
    switch (m_current_choice) {
    case KeyInput_English:
    case KeyInput_Symbol:
    {
        QKeyEvent rightMovePressed(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
        QCoreApplication::sendEvent(p_lineEdit, &rightMovePressed);
        m_cursorPosition = p_lineEdit->cursorPosition();
        break;
    }
    case KeyInput_Chinese:
    {
        if("" == m_inputLetter) {
            QKeyEvent rightMovePressed(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
            QCoreApplication::sendEvent(p_lineEdit, &rightMovePressed);
            m_cursorPosition = p_lineEdit->cursorPosition();
        } else {
            // do nothing
        }
        break;
    }
    default:
        break;
    }
}

void SoftKeyPad::slotButtonBSReleased()
{
    switch (m_current_choice) {
    case KeyInput_English:
    case KeyInput_Symbol:
    {
        QKeyEvent backRelease(QEvent::KeyRelease, Qt::Key_Backspace, Qt::NoModifier);
        QCoreApplication::sendEvent(p_lineEdit, &backRelease);
        m_cursorPosition = p_lineEdit->cursorPosition();
        break;
    }
    default:
        break;
    }
}

void SoftKeyPad::slotButtonDELReleased()
{
    switch (m_current_choice) {
    case KeyInput_English:
    case KeyInput_Symbol:
    {
        QKeyEvent deleteRelease(QEvent::KeyRelease, Qt::Key_Delete, Qt::NoModifier);
        QCoreApplication::sendEvent(p_lineEdit, &deleteRelease);
        break;
    }
    case KeyInput_Chinese:
    {
        if("" == m_inputLetter) {
            QKeyEvent deleteRelease(QEvent::KeyRelease, Qt::Key_Delete, Qt::NoModifier);
            QCoreApplication::sendEvent(p_lineEdit, &deleteRelease);
        } else {
            // do nothing
        }
        break;
    }
    default:
        break;
    }
}

void SoftKeyPad::slotButtonMoveLeftReleased()
{
    switch (m_current_choice) {
    case KeyInput_English:
    case KeyInput_Symbol:
    {
        QKeyEvent leftMoveRelease(QEvent::KeyRelease, Qt::Key_Left, Qt::NoModifier);
        QCoreApplication::sendEvent(p_lineEdit, &leftMoveRelease);
        m_cursorPosition = p_lineEdit->cursorPosition();
        break;
    }
    case KeyInput_Chinese:
    {
        if("" == m_inputLetter) {
            QKeyEvent leftMoveRelease(QEvent::KeyRelease, Qt::Key_Left, Qt::NoModifier);
            QCoreApplication::sendEvent(p_lineEdit, &leftMoveRelease);
            m_cursorPosition = p_lineEdit->cursorPosition();
        } else {
            // do nothing
        }
        break;
    }
    default:
        break;
    }
}

void SoftKeyPad::slotButtonMoveRightReleased()
{
    switch (m_current_choice) {
    case KeyInput_English:
    case KeyInput_Symbol:
    {
        QKeyEvent rightMoveRelease(QEvent::KeyRelease, Qt::Key_Right, Qt::NoModifier);
        QCoreApplication::sendEvent(p_lineEdit, &rightMoveRelease);
        m_cursorPosition = p_lineEdit->cursorPosition();
        break;
    }
    case KeyInput_Chinese:
    {
        if("" == m_inputLetter) {
            QKeyEvent rightMoveRelease(QEvent::KeyRelease, Qt::Key_Right, Qt::NoModifier);
            QCoreApplication::sendEvent(p_lineEdit, &rightMoveRelease);
            m_cursorPosition = p_lineEdit->cursorPosition();
        } else {
            // do nothing
        }
        break;
    }
    default:
        break;
    }
}

/*
 * 功能：
 * 	   OK按钮单击事件
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::slotButtonOKClicked()
{
    QTextCodec *codec = QTextCodec::codecForName("GB18030");

    if (!p_lineEdit->selectedText().isEmpty())
    {
        p_chineseShowWidget->setHidden(true);
        p_lineEdit->deselect();
        m_cursorPosition = p_lineEdit->cursorPosition();
        m_firstInputFlag = true;
        m_inputLetter = "";
        m_lineInputLetter = "";
        return;
    }

    m_inputStr = p_lineEdit->text();
    QByteArray array;
    if (codec)
    {
        array = codec->fromUnicode(m_inputStr);
    }

    int strlen = array.size();  
    if (strlen <= m_maxNum) {
        accept();
    } else {
        //WinInfoListDialog::instance()->showMsg(5, this);
        WARNNING_MSG(INPUT_OUTOF_LIMIT);
    }
}

/*
 * 功能：
 * 	   主窗体设置
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::setCenterWidgetLayout()
{
    p_centerWidget = new QWidget(p_mainFrame);
    p_centerWidget->setGeometry(0, 0, this->width(), this->height());
    p_centerWidget->setAttribute(Qt::WA_TranslucentBackground);

    p_textEdit = new ILineEdit(p_centerWidget);
    p_textEdit->setObjectName("TipLineEdit");
    p_textEdit->setStyleSheet("font-size:18px; font-weight:bold;border-width:0;color:#5d97ae;padding-left:15;padding-top:15;border-color:rgb(47, 89, 103); background-color:rgb(0, 0, 0);");
    p_textEdit->setContextMenuPolicy(Qt::NoContextMenu);//禁用右键菜单
    p_textEdit->setAttribute(Qt::WA_TranslucentBackground, true);
    p_textEdit->setFrame(false);
    p_textEdit->setReadOnly(true);
    p_textEdit->setFocusPolicy(Qt::NoFocus);
    p_textEdit->setGeometry((int)(0.06 * m_currentWidth), (int)(0.07 * m_currentHeight), \
        (int)(0.712 * m_currentWidth), (int)(0.085 * m_currentHeight));
    p_textEdit->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    p_chineseShowWidget = new QWidget(p_centerWidget);
    p_chineseShowWidget->setGeometry((int)(0.06 * m_currentWidth), (int)(0.07 * m_currentHeight), (int)(0.713 * m_currentWidth), (int)(0.098 * m_currentHeight));
    p_chineseShowWidget->setHidden(true);
    p_chineseShowWidget->setStyleSheet("background-color:rgb(0, 0, 0);");
    p_chineseShowWidget->setWindowFlags(Qt::FramelessWindowHint);
    p_groupChineseShow = new QButtonGroup;
    for (int i = 0; i < 9; ++i) {
        QPushButton* chineseShowButton = new QPushButton(p_chineseShowWidget);
        chineseShowButton->setFocusPolicy(Qt::NoFocus);
        chineseShowButton->setGeometry(5 + i * (int)(0.08 * m_currentWidth), 3, \
            (int)(0.07 *m_currentWidth), (int)(0.065 * m_currentHeight));
        p_groupChineseShow->addButton(chineseShowButton, i);
    }
    p_groupChineseShow->button(0)->setText("<");
    p_groupChineseShow->button(8)->setText(">");

    p_lineEdit = new ILineEdit(p_centerWidget);
    p_lineEdit->setObjectName("InputLineEdit");
    p_lineEdit->setStyleSheet("font-size:28px; font-weight:bold;padding-left:15;padding-bottom:15;color:#5d97ae; background-color:rgb(0, 0, 0);letter-spacing:200px;");
    p_lineEdit->setContextMenuPolicy(Qt::NoContextMenu);
    p_lineEdit->setFocus();
    p_lineEdit->setAttribute(Qt::WA_TranslucentBackground, true);
    p_lineEdit->setFrame(false);
    p_lineEdit->setGeometry((int)(0.06 * m_currentWidth), (int)(0.150 * m_currentHeight), \
        (int)(0.712 * m_currentWidth), (int)(0.08 * m_currentHeight));
    p_buttonBS = new QPushButton(p_centerWidget);
    p_buttonBS->setFocusPolicy(Qt::NoFocus);
    p_buttonBS->setGeometry((int)(0.78 * m_currentWidth), (int)(0.07 * m_currentHeight),\
                            (int)(0.0714 *m_currentWidth), (int)(0.065 * m_currentHeight));
    p_lineEdit->setAttribute(Qt::WA_TranslucentBackground, true);
    p_buttonBS->setAutoRepeat(true);
    p_buttonBS->setAutoRepeatDelay(500);
    p_buttonBS->setStyleSheet("QPushButton{border-image:url(../resources/controlicon/keypad/delet_normal.png);}"\
                             "QPushButton:pressed{border-image:url(../resources/controlicon/keypad/delet_press.png);}");

    p_buttonDEL = new QPushButton(p_centerWidget);
    p_buttonDEL->setFocusPolicy(Qt::NoFocus);
    p_buttonDEL->setGeometry((int)(0.8628 * m_currentWidth), (int)(0.07 * m_currentHeight),\
                             (int)(0.0714 *m_currentWidth), (int)(0.065 * m_currentHeight));
    p_buttonDEL->setText("DEL");
    p_buttonDEL->setAutoRepeat(true);
    p_buttonDEL->setAutoRepeatDelay(500);
    p_buttonDEL->setStyleSheet("QPushButton{border-image:url(../resources/controlicon/keypad/delete_normal.png);}"\
                               "QPushButton:pressed{border-image:url(../resources/controlicon/keypad/button_press.png);}");

    p_buttonLeftMove = new QPushButton(p_centerWidget);
    p_buttonLeftMove->setFocusPolicy(Qt::NoFocus);
    p_buttonLeftMove->setGeometry((int)(0.78 * m_currentWidth), (int)(0.1508 * m_currentHeight),\
                                  (int)(0.0714 *m_currentWidth), (int)(0.065 * m_currentHeight));
    p_buttonLeftMove->setIconSize(QSize(p_buttonLeftMove->width(), p_buttonLeftMove->height()));
    p_buttonLeftMove->setAutoRepeat(true);
    p_buttonLeftMove->setAutoRepeatDelay(500);
    p_buttonLeftMove->setStyleSheet("QPushButton{border-image:url(../resources/controlicon/keypad/retreat_normal.png);}"\
                                    "QPushButton:pressed{border-image:url(../resources/controlicon/keypad/retreat_press.png);}");


    p_buttonRightMove = new QPushButton(p_centerWidget);
    p_buttonRightMove->setFocusPolicy(Qt::NoFocus);
    p_buttonRightMove->setGeometry((int)(0.8628 * m_currentWidth), (int)(0.1508 * m_currentHeight),\
                                   (int)(0.0714 *m_currentWidth), (int)(0.065 * m_currentHeight));
    p_buttonRightMove->setIconSize(QSize(p_buttonRightMove->width(), p_buttonRightMove->height()));
    p_buttonRightMove->setAutoRepeat(true);
    p_buttonRightMove->setAutoRepeatDelay(500);
    p_buttonRightMove->setStyleSheet("QPushButton{border-image:url(../resources/controlicon/keypad/advance_normal.png);}"\
                                     "QPushButton:pressed{border-image:url(../resources/controlicon/keypad/advance_press.png);}");

    p_groupEnglish = new QButtonGroup;
    p_groupChinese = new QButtonGroup;
    p_groupSymbol = new QButtonGroup;


    p_buttonCancel = new QPushButton(p_centerWidget);
    p_buttonCancel->setFocusPolicy(Qt::NoFocus);
    p_buttonCancel->setGeometry((int)(0.0578 * m_currentWidth), (int)(0.712 * m_currentHeight),\
                                (int)(0.1165 * m_currentWidth), (int)(0.065 * m_currentHeight));
    p_buttonCancel->setObjectName("ButtonCancel");
    p_buttonCancel->setText(tr("Cancel"));

    p_buttonOK = new QPushButton(p_centerWidget);
    p_buttonOK->setFocusPolicy(Qt::NoFocus);
    p_buttonOK->setGeometry((int)(0.8227 * m_currentWidth), (int)(0.712 * m_currentHeight), \
                            (int)(0.1165 * m_currentWidth), (int)(0.065 * m_currentHeight));
    p_buttonOK->setObjectName("ButtonOK");
    p_buttonOK->setText(tr("OK"));

    p_buttonEnglish = new QPushButton(p_centerWidget);
    p_buttonEnglish->setFocusPolicy(Qt::NoFocus);
    p_buttonEnglish->setGeometry((int)(0.382 * m_currentWidth), (int)(0.712 * m_currentHeight), \
                                 (int)(0.0714 * m_currentWidth), (int)(0.065 * m_currentHeight));
    p_buttonEnglish->setText(tr("EN"));

    p_buttonChinese = new QPushButton(p_centerWidget);
    p_buttonChinese->setFocusPolicy(Qt::NoFocus);
    p_buttonChinese->setGeometry((int)(0.460 * m_currentWidth), (int)(0.712 * m_currentHeight), \
                                 (int)(0.0714 * m_currentWidth), (int)(0.065 * m_currentHeight));
    p_buttonChinese->setText(tr("CH"));

    p_buttonSymbol = new QPushButton(p_centerWidget);
    p_buttonSymbol->setFocusPolicy(Qt::NoFocus);
    p_buttonSymbol->setGeometry((int)(0.546 * m_currentWidth), (int)(0.712 * m_currentHeight), \
                                (int)(0.0714 * m_currentWidth), (int)(0.065 * m_currentHeight));
    p_buttonSymbol->setText(tr("Symbol"));

    /*********  英文界面布局  *********/
    setGroupEndlishLayout();
    setGroupChineseLayout();
    setGroupSymbolLayout();
}

/*
 * 功能：
 * 	   英文界面布局
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::setGroupEndlishLayout()
{
    int groupEnglishID = 0;
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 11; ++j) {
            QPushButton* englishButton = new QPushButton(p_centerWidget);
            englishButton->setGeometry((int)(0.0600 * m_currentWidth) + j * (int)(0.0807 * m_currentWidth), \
                                        (int)(0.265 * m_currentHeight) + i * (int)(0.0828 * m_currentHeight), \
                                       (int)(0.0714 *m_currentWidth), (int)(0.065 * m_currentHeight));

            englishButton->setFocusPolicy(Qt::NoFocus);
            p_groupEnglish->addButton(englishButton, groupEnglishID);
            ++groupEnglishID;
        }
    p_groupEnglish->button(31)->setGeometry((int)(0.780 * m_currentWidth), (int)(0.431 * m_currentHeight),\
                                            (int)(0.1532 *m_currentWidth), (int)(0.065 * m_currentHeight));

    QPushButton* leftShiftButton = new QPushButton(p_centerWidget);
    leftShiftButton->setGeometry((int)(0.0587 * m_currentWidth), (int)(0.5966 * m_currentHeight),\
                                 (int)(0.1532 *m_currentWidth), (int)(0.065 * m_currentHeight));
    p_groupEnglish->addButton(leftShiftButton, 44);

    QPushButton* spaceButton = new QPushButton(p_centerWidget);
    spaceButton->setGeometry((int)(0.2211 * m_currentWidth), (int)(0.5966 * m_currentHeight),\
                             (int)(0.5529 *m_currentWidth), (int)(0.065 * m_currentHeight));
    spaceButton->setObjectName("SpaceButton");
    p_groupEnglish->addButton(spaceButton, 45);

    QPushButton* rightShiftButton = new QPushButton(p_centerWidget);
    rightShiftButton->setGeometry((int)(0.780 * m_currentWidth), (int)(0.5966 * m_currentHeight),\
                                  (int)(0.1532 *m_currentWidth), (int)(0.065 * m_currentHeight));
    p_groupEnglish->addButton(rightShiftButton, 46);

    for(int i = 44; i < 47; ++i) {
        p_groupEnglish->button(i)->setFocusPolicy(Qt::NoFocus);
    }

    setGroupEndlishText();
}

/*
 * 功能：
 * 	   英文界面显示
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::setGroupEndlishText()
{
    p_groupEnglish->button(32)->setHidden(true);
    if(LatterSmall == m_englishState)  {  // 小写状态下布局
        for(int i = 0; i < 9; ++i) {
            p_groupEnglish->button(i)->setText(QString("%1").arg(i + 1));
        }
        p_groupEnglish->button(9)->setText("0");
        p_groupEnglish->button(10)->setText("-");
        p_groupEnglish->button(11)->setText("q");
        p_groupEnglish->button(12)->setText("w");
        p_groupEnglish->button(13)->setText("e");
        p_groupEnglish->button(14)->setText("r");
        p_groupEnglish->button(15)->setText("t");
        p_groupEnglish->button(16)->setText("y");
        p_groupEnglish->button(17)->setText("u");
        p_groupEnglish->button(18)->setText("i");
        p_groupEnglish->button(19)->setText("o");
        p_groupEnglish->button(20)->setText("p");
        p_groupEnglish->button(21)->setText("+");
        p_groupEnglish->button(22)->setText("a");
        p_groupEnglish->button(23)->setText("s");
        p_groupEnglish->button(24)->setText("d");
        p_groupEnglish->button(25)->setText("f");
        p_groupEnglish->button(26)->setText("g");
        p_groupEnglish->button(27)->setText("h");
        p_groupEnglish->button(28)->setText("j");
        p_groupEnglish->button(29)->setText("k");
        p_groupEnglish->button(30)->setText("l");
        p_groupEnglish->button(31)->setText("Enter");
        p_groupEnglish->button(31)->setStyleSheet("QPushButton{border-image:url(../resources/controlicon/keypad/bigBtn_normal.png);}"\
                                                "font-family:'Microsoft YaHei';font-size:24px;}"\
                                                 "QPushButton:pressed{border-image:url(../resources/controlicon/keypad/bigBtn_press.png);"\
                                                "font-family:'Microsoft YaHei';font-size:24px;}");
        p_groupEnglish->button(33)->setText("z");
        p_groupEnglish->button(34)->setText("x");
        p_groupEnglish->button(35)->setText("c");
        p_groupEnglish->button(36)->setText("v");
        p_groupEnglish->button(37)->setText("b");
        p_groupEnglish->button(38)->setText("n");
        p_groupEnglish->button(39)->setText("m");
        p_groupEnglish->button(40)->setText(",");
        p_groupEnglish->button(41)->setText(".");
        p_groupEnglish->button(42)->setText("/");
        p_groupEnglish->button(43)->setText("?");
        p_groupEnglish->button(44)->setStyleSheet("QPushButton{border-image:url(../resources/controlicon/keypad/bigBtn_normal.png);}"\
            "font-family:'Arial Regular';font-size:24px;}"\
            "QPushButton:pressed{border-image:url(../resources/controlicon/keypad/bigBtn_press.png);"\
            "font-family:'Arial Regular';font-size:24px;}");
        p_groupEnglish->button(46)->setStyleSheet("QPushButton{border-image:url(../resources/controlicon/keypad/bigBtn_normal.png);}"\
            "font-family:'Microsoft YaHei';font-size:24px;}"\
            "QPushButton:pressed{border-image:url(../resources/controlicon/keypad/bigBtn_press.png);"\
            "font-family:'Arial Regular';font-size:24px;}");
    } else {
        p_groupEnglish->button(0)->setText("!");
        p_groupEnglish->button(1)->setText("@");
        p_groupEnglish->button(2)->setText("#");
        p_groupEnglish->button(3)->setText("%");
        p_groupEnglish->button(4)->setText("&&");
        p_groupEnglish->button(5)->setText("*");
        p_groupEnglish->button(6)->setText("`");
        p_groupEnglish->button(7)->setText("\"");
        p_groupEnglish->button(8)->setText("(");
        p_groupEnglish->button(9)->setText(")");
        p_groupEnglish->button(10)->setText("_");
        p_groupEnglish->button(11)->setText("Q");
        p_groupEnglish->button(12)->setText("W");
        p_groupEnglish->button(13)->setText("E");
        p_groupEnglish->button(14)->setText("R");
        p_groupEnglish->button(15)->setText("T");
        p_groupEnglish->button(16)->setText("Y");
        p_groupEnglish->button(17)->setText("U");
        p_groupEnglish->button(18)->setText("I");
        p_groupEnglish->button(19)->setText("O");
        p_groupEnglish->button(20)->setText("P");
        p_groupEnglish->button(21)->setText("=");
        p_groupEnglish->button(22)->setText("A");
        p_groupEnglish->button(23)->setText("S");
        p_groupEnglish->button(24)->setText("D");
        p_groupEnglish->button(25)->setText("F");
        p_groupEnglish->button(26)->setText("G");
        p_groupEnglish->button(27)->setText("H");
        p_groupEnglish->button(28)->setText("J");
        p_groupEnglish->button(29)->setText("K");
        p_groupEnglish->button(30)->setText("L");
        p_groupEnglish->button(31)->setText("Enter");
        p_groupEnglish->button(31)->setStyleSheet("QPushButton{border-image:url(../resources/controlicon/keypad/bigBtn_normal.png);}"\
            "font-family:'Arial Regular';font-size:24px;}"\
            "QPushButton:pressed{border-image:url(../resources/controlicon/keypad/bigBtn_press.png);"\
            "font-family:'Arial Regular';font-size:24px;}");
        p_groupEnglish->button(33)->setText("Z");
        p_groupEnglish->button(34)->setText("X");
        p_groupEnglish->button(35)->setText("C");
        p_groupEnglish->button(36)->setText("V");
        p_groupEnglish->button(37)->setText("B");
        p_groupEnglish->button(38)->setText("N");
        p_groupEnglish->button(39)->setText("M");
        p_groupEnglish->button(40)->setText(",");
        p_groupEnglish->button(41)->setText(".");
        p_groupEnglish->button(42)->setText("/");
        p_groupEnglish->button(43)->setText(":");
        p_groupEnglish->button(44)->setStyleSheet("QPushButton{border-image:url(../resources/controlicon/keypad/bigBtn_normal.png);}"\
            "font-family:'Arial Regular';font-size:24px;}"\
            "QPushButton:pressed{border-image:url(../resources/controlicon/keypad/bigBtn_press.png);"\
            "font-family:'Arial Regular';font-size:26px;}");
        p_groupEnglish->button(46)->setStyleSheet("QPushButton{border-image:url(../resources/controlicon/keypad/bigBtn_normal.png);}"\
            "font-family:'Arial Regular';font-size:24px;}"\
            "QPushButton:pressed{border-image:url(../resources/controlicon/keypad/bigBtn_press.png);"\
            "font-family:'Arial Regular';font-size:24px;}");
    }

    p_groupEnglish->button(45)->setText("");
    p_groupEnglish->button(44)->setText("Shift");
    p_groupEnglish->button(46)->setText("Shift");
}

/*
 * 功能：
 * 	   中文界面布局
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::setGroupChineseLayout()
{
    int groupChineseID = 0;
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 11; ++j) {
            QPushButton* chineseButton = new QPushButton(p_centerWidget);
            chineseButton->setGeometry((int)(0.0600 * m_currentWidth) + j * (int)(0.0807 * m_currentWidth), \
                                       (int)(0.265 * m_currentHeight) + i * (int)(0.0828 * m_currentHeight), \
                                       (int)(0.0714 *m_currentWidth), (int)(0.065 * m_currentHeight));
            chineseButton->setFocusPolicy(Qt::NoFocus);
            p_groupChinese->addButton(chineseButton, groupChineseID);
            ++groupChineseID;
        }
    p_groupChinese->button(31)->setGeometry((int)(0.780 * m_currentWidth), (int)(0.431 * m_currentHeight),\
                                            (int)(0.1532 *m_currentWidth), (int)(0.065 * m_currentHeight));

    QPushButton* leftShiftButton = new QPushButton(p_centerWidget);
    leftShiftButton->setGeometry((int)(0.06 * m_currentWidth), (int)(0.5966 * m_currentHeight),\
                                 (int)(0.1532 *m_currentWidth), (int)(0.065 * m_currentHeight));
    p_groupChinese->addButton(leftShiftButton, 44);
    leftShiftButton->setFocusPolicy(Qt::NoFocus);

    QPushButton* spaceButton = new QPushButton(p_centerWidget);
    spaceButton->setGeometry((int)(0.2224 * m_currentWidth), (int)(0.5966 * m_currentHeight), \
                             (int)(0.3095 *m_currentWidth), (int)(0.065 * m_currentHeight));
    spaceButton->setFocusPolicy(Qt::NoFocus);
    spaceButton->setObjectName("SpaceButton");
    p_groupChinese->addButton(spaceButton, 45);

    QPushButton* chButton = new QPushButton(p_centerWidget);
    chButton->setGeometry((int)(0.539 * m_currentWidth), (int)(0.5966 * m_currentHeight), \
                          (int)(0.0704 *m_currentWidth), (int)(0.065 * m_currentHeight));
    chButton->setText("ch");
    p_groupChinese->addButton(chButton, 46);

    QPushButton* shButton = new QPushButton(p_centerWidget);
    shButton->setGeometry((int)(0.6210 * m_currentWidth), (int)(0.5966 * m_currentHeight), \
                          (int)(0.0714 *m_currentWidth), (int)(0.065 * m_currentHeight));
    shButton->setText("sh");
    p_groupChinese->addButton(shButton, 47);

    QPushButton* zhButton = new QPushButton(p_centerWidget);
    zhButton->setGeometry((int)(0.7024 * m_currentWidth), (int)(0.5966 * m_currentHeight), \
                          (int)(0.0714 *m_currentWidth), (int)(0.065 * m_currentHeight));
    zhButton->setText("zh");
    p_groupChinese->addButton(zhButton, 48);

    for(int i = 46; i < 49; ++i) {
        p_groupChinese->button(i)->setFocusPolicy(Qt::NoFocus);
    }

    QPushButton* rightShiftButton = new QPushButton(p_centerWidget);
    rightShiftButton->setFocusPolicy(Qt::NoFocus);
    rightShiftButton->setGeometry((int)(0.7823 * m_currentWidth), (int)(0.5966 * m_currentHeight),\
                                  (int)(0.1532 *m_currentWidth), (int)(0.065 * m_currentHeight));
    p_groupChinese->addButton(rightShiftButton, 49);
    setGroupChineseText();
}

/*
 * 功能：
 * 	   中文界面显示
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::setGroupChineseText()
{
    p_groupChinese->button(32)->setHidden(true);
    if(LatterSmall == m_chineseState)  {  // 小写状态下布局
        for(int i = 0; i < 9; ++i) {
            p_groupChinese->button(i)->setText(QString("%1").arg(i + 1));
        }
        p_groupChinese->button(9)->setText("0");
        p_groupChinese->button(10)->setText("－");
        p_groupChinese->button(11)->setText("q");
        p_groupChinese->button(12)->setText("w");
        p_groupChinese->button(13)->setText("e");
        p_groupChinese->button(14)->setText("r");
        p_groupChinese->button(15)->setText("t");
        p_groupChinese->button(16)->setText("y");
        p_groupChinese->button(17)->setText("u");
        p_groupChinese->button(18)->setText("i");
        p_groupChinese->button(19)->setText("o");
        p_groupChinese->button(20)->setText("p");
        p_groupChinese->button(21)->setText("＋");
        p_groupChinese->button(22)->setText("a");
        p_groupChinese->button(23)->setText("s");
        p_groupChinese->button(24)->setText("d");
        p_groupChinese->button(25)->setText("f");
        p_groupChinese->button(26)->setText("g");
        p_groupChinese->button(27)->setText("h");
        p_groupChinese->button(28)->setText("j");
        p_groupChinese->button(29)->setText("k");
        p_groupChinese->button(30)->setText("l");
        p_groupChinese->button(31)->setText("Enter");
        p_groupChinese->button(31)->setStyleSheet("QPushButton{border-image:url(../resources/controlicon/keypad/bigBtn_normal.png);}"\
            "font-family:'Arial Regular';font-size:24px;}"\
            "QPushButton:pressed{border-image:url(../resources/controlicon/keypad/bigBtn_press.png);"\
            "font-family:'Arial Regular';font-size:24px;}");
        p_groupChinese->button(33)->setText("z");
        p_groupChinese->button(34)->setText("x");
        p_groupChinese->button(35)->setText("c");
        p_groupChinese->button(36)->setText("v");
        p_groupChinese->button(37)->setText("b");
        p_groupChinese->button(38)->setText("n");
        p_groupChinese->button(39)->setText("m");
        p_groupChinese->button(40)->setText("，");
        p_groupChinese->button(41)->setText("。");
        p_groupChinese->button(42)->setText("；");
        p_groupChinese->button(43)->setText("：");
        p_groupChinese->button(46)->setText("ch");
        p_groupChinese->button(47)->setText("sh");
        p_groupChinese->button(48)->setText("zh");
        p_groupChinese->button(44)->setStyleSheet("QPushButton{border-image:url(../resources/controlicon/keypad/bigBtn_normal.png);}"\
            "font-family:'Arial Regular';font-size:24px;}"\
            "QPushButton:pressed{border-image:url(../resources/controlicon/keypad/bigBtn_press.png);"\
            "font-family:'Arial Regular';font-size:24px;}");
        for (int i = 46; i <= 49; i++)
        {
            p_groupChinese->button(i)->setStyleSheet("QPushButton{border-image:url(../resources/controlicon/keypad/bigBtn_normal.png);}"\
                "font-family:'Arial Regular';font-size:24px;}"\
                "QPushButton:pressed{border-image:url(../resources/controlicon/keypad/bigBtn_press.png);"\
                "font-family:'Arial Regular';font-size:24px;}");
        }        
    } else {
        p_groupChinese->button(0)->setText("!");
        p_groupChinese->button(1)->setText("@");
        p_groupChinese->button(2)->setText("#");
        p_groupChinese->button(3)->setText("%");
        p_groupChinese->button(4)->setText("&&");
        p_groupChinese->button(5)->setText("*");
        p_groupChinese->button(6)->setText("“");
        p_groupChinese->button(7)->setText("”");
        p_groupChinese->button(8)->setText("(");
        p_groupChinese->button(9)->setText(")");
        p_groupChinese->button(10)->setText("－");
        p_groupChinese->button(11)->setText("Q");
        p_groupChinese->button(12)->setText("W");
        p_groupChinese->button(13)->setText("E");
        p_groupChinese->button(14)->setText("R");
        p_groupChinese->button(15)->setText("T");
        p_groupChinese->button(16)->setText("Y");
        p_groupChinese->button(17)->setText("U");
        p_groupChinese->button(18)->setText("I");
        p_groupChinese->button(19)->setText("O");
        p_groupChinese->button(20)->setText("P");
        p_groupChinese->button(21)->setText("=");
        p_groupChinese->button(22)->setText("A");
        p_groupChinese->button(23)->setText("S");
        p_groupChinese->button(24)->setText("D");
        p_groupChinese->button(25)->setText("F");
        p_groupChinese->button(26)->setText("G");
        p_groupChinese->button(27)->setText("H");
        p_groupChinese->button(28)->setText("J");
        p_groupChinese->button(29)->setText("K");
        p_groupChinese->button(30)->setText("L");
        p_groupChinese->button(31)->setText("Enter");
        p_groupChinese->button(31)->setStyleSheet("QPushButton{border-image:url(../resources/controlicon/keypad/bigBtn_normal.png);}"\
            "font-family:'Arial Regular';font-size:24px;}"\
            "QPushButton:pressed{border-image:url(../resources/controlicon/keypad/bigBtn_press.png);"\
            "font-family:'Arial Regular';font-size:24px;}");
        p_groupChinese->button(33)->setText("Z");
        p_groupChinese->button(34)->setText("X");
        p_groupChinese->button(35)->setText("C");
        p_groupChinese->button(36)->setText("V");
        p_groupChinese->button(37)->setText("B");
        p_groupChinese->button(38)->setText("N");
        p_groupChinese->button(39)->setText("M");
        p_groupChinese->button(40)->setText("，");
        p_groupChinese->button(41)->setText("。");
        p_groupChinese->button(42)->setText("；");
        p_groupChinese->button(43)->setText("：");
        p_groupChinese->button(46)->setText("CH");
        p_groupChinese->button(47)->setText("SH");
        p_groupChinese->button(48)->setText("ZH");
        p_groupChinese->button(44)->setStyleSheet("QPushButton{border-image:url(../resources/controlicon/keypad/bigBtn_normal.png);}"\
            "font-family:'Arial Regular';font-size:26px;}"\
            "QPushButton:pressed{border-image:url(../resources/controlicon/keypad/bigBtn_press.png);"\
            "font-family:'Arial Regular';font-size:26px;}");
        for (int i = 46; i <= 49; i++)
        {
            p_groupChinese->button(i)->setStyleSheet("QPushButton{border-image:url(../resources/controlicon/keypad/bigBtn_normal.png);}"\
                "font-family:'Arial Regular';font-size:26px;}"\
                "QPushButton:pressed{border-image:url(../resources/controlicon/keypad/bigBtn_press.png);"\
                "font-family:'Arial Regular';font-size:26px;}");
        }
    }

    p_groupChinese->button(45)->setText("");
    p_groupChinese->button(44)->setText("Shift");
    p_groupChinese->button(49)->setText("Shift");
}

/*
 * 功能：
 * 	   符号界面布局
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::setGroupSymbolLayout()
{
    int groupSymbolID = 0;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 11; ++j) 
        {
            QPushButton* symbolButton = new QPushButton(p_centerWidget);
            symbolButton->setGeometry((int)(0.0600 * m_currentWidth) + j * (int)(0.0807 * m_currentWidth), \
                (int)(0.265 * m_currentHeight) + i * (int)(0.0828 * m_currentHeight), \
                (int)(0.0714 *m_currentWidth), (int)(0.065 * m_currentHeight));
            symbolButton->setFocusPolicy(Qt::NoFocus);
            p_groupSymbol->addButton(symbolButton, groupSymbolID);
            ++groupSymbolID;
        }
    }

    setGroupSymbolText();
}

/*
 * 功能：
 * 	   符号界面显示
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::setGroupSymbolText()
{
    p_groupSymbol->button(0)->setText("~");
    p_groupSymbol->button(1)->setText("!");
    p_groupSymbol->button(2)->setText("@");
    p_groupSymbol->button(3)->setText("#");
    p_groupSymbol->button(4)->setText("$");
    p_groupSymbol->button(5)->setText("%");
    p_groupSymbol->button(6)->setText("^");
    p_groupSymbol->button(7)->setText("&&");
    p_groupSymbol->button(8)->setText("*");
    p_groupSymbol->button(9)->setText("(");
    p_groupSymbol->button(10)->setText(")");
    p_groupSymbol->button(11)->setText("\"");
    p_groupSymbol->button(12)->setText(",");
    p_groupSymbol->button(13)->setText(".");
    p_groupSymbol->button(14)->setText(":");
    p_groupSymbol->button(15)->setText("?");
    p_groupSymbol->button(16)->setText("_");
    p_groupSymbol->button(17)->setText("=");
    p_groupSymbol->button(18)->setText("+");
    p_groupSymbol->button(19)->setText("-");
    p_groupSymbol->button(20)->setText("/");
    p_groupSymbol->button(21)->setText("\\");
    p_groupSymbol->button(22)->setText("|");
    p_groupSymbol->button(23)->setText("<");
    p_groupSymbol->button(24)->setText(">");
    p_groupSymbol->button(25)->setText("{");
    p_groupSymbol->button(26)->setText("}");
    p_groupSymbol->button(27)->setText("[");
    p_groupSymbol->button(28)->setText("]");
    p_groupSymbol->button(29)->setText("·");
    p_groupSymbol->button(30)->setText("°");
    p_groupSymbol->button(31)->setText("×");
    p_groupSymbol->button(32)->setText("÷");
    p_groupSymbol->button(33)->setText("￥");
    p_groupSymbol->button(34)->setText("±");
//    QFont font;
//    font.setStyle(QFont::Style::StyleOblique);
//    p_groupSymbol->button(35)->setFont(font);
    p_groupSymbol->button(35)->setText("μ");
	p_groupSymbol->button(36)->setText("℃");
	p_groupSymbol->button(37)->setText("Ω");
    for (int id = 38; id < 44; ++id) {
        p_groupSymbol->button(id)->setHidden(true);
    }
}

/*
 * 功能：
 * 	   显示英文界面
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::setEnglishShow()
{
    for(int i = 0; i < p_groupChinese->buttons().size(); ++i) {
        p_groupChinese->button(i)->setHidden(true);
    }

    for(int i = 0; i < p_groupSymbol->buttons().size(); ++i) {
        p_groupSymbol->button(i)->setHidden(true);
    }

    for(int i = 0; i < p_groupEnglish->buttons().size(); ++i) {
        p_groupEnglish->button(i)->setHidden(false);
    }

    setGroupEndlishText();
}

/*
 * 功能：
 * 	   显示中文界面
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::setChineseShow()
{
    for(int i = 0; i < p_groupChinese->buttons().size(); ++i) {
        p_groupChinese->button(i)->setHidden(false);
    }

    for(int i = 0; i < p_groupSymbol->buttons().size(); ++i) {
        p_groupSymbol->button(i)->setHidden(true);
    }

    for(int i = 0; i < p_groupEnglish->buttons().size(); ++i) {
        p_groupEnglish->button(i)->setHidden(true);
    }
    setGroupChineseText();
}

/*
 * 功能：
 * 	   显示符号界面
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::setSymbolShow()
{
    for(int i = 0; i < p_groupChinese->buttons().size(); ++i) {
        p_groupChinese->button(i)->setHidden(true);
    }

    for(int i = 0; i < p_groupSymbol->buttons().size(); ++i) {
        p_groupSymbol->button(i)->setHidden(false);
    }

    for(int i = 0; i < p_groupEnglish->buttons().size(); ++i) {
        p_groupEnglish->button(i)->setHidden(true);
    }
    setGroupSymbolText();
}

/*
 * 功能：
 * 	   数据库连接
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::connectDatabase()
{
    if (QSqlDatabase::contains("../resources/china.db")) {
        m_db = QSqlDatabase::database("../resources/china.db");
    } else {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "../resources/china.db");
        m_db.setDatabaseName("../resources/china.db");
    }
    if(m_db.open()) {
        qDebug() << "m_db open successful!";
    } else {
        qDebug() << "m_db open failure!";
    }

    m_query = QSqlQuery(m_db);
}

/*
 * 功能：
 * 	   显示中文
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::chineseShow()
{
    if(0 == m_listCount) {
        p_chineseShowWidget->setHidden(true);
    } else {
        if(m_listChineseID < 7) {
            p_groupChineseShow->button(0)->setEnabled(false);
			p_groupChineseShow->button(0)->setStyleSheet(DISENABLE_COLOR);
        } else {
            p_groupChineseShow->button(0)->setEnabled(true);
			p_groupChineseShow->button(0)->setStyleSheet(ENABLE_COLOR);
        }
        while (m_listChineseID < m_listCount) {

            p_groupChineseShow->button(m_listChineseID % 7 + 1)->setText(m_listChinese.value(m_listChineseID));

            if(++m_listChineseID == m_listCount)
            {
                if (0 == (m_listChineseID % 7)) {
                    // do nothing
                } else if (1 == (m_listChineseID % 7)) {
                    for(int i = 2; i < 8; ++i) {
                        p_groupChineseShow->button(i)->setText("");
                    }
                } else if (2 == (m_listChineseID % 7)) {
                    for(int i = 3; i < 8; ++i) {
                        p_groupChineseShow->button(i)->setText("");
                    }
                } else if (3 == (m_listChineseID % 7)) {
                    for(int i = 4; i < 8; ++i) {
                        p_groupChineseShow->button(i)->setText("");
                    }
                } else if (4 == (m_listChineseID % 7)) {
                    for(int i = 5; i < 8; ++i) {
                        p_groupChineseShow->button(i)->setText("");
                    }
                } else if (5 == (m_listChineseID % 7)) {
                    for(int i = 6; i < 8; ++i) {
                        p_groupChineseShow->button(i)->setText("");
                    }
                } else if (6 == (m_listChineseID % 7)) {
                    for(int i = 7; i < 8; ++i) {
                        p_groupChineseShow->button(i)->setText("");
                    }
                }
                p_groupChineseShow->button(8)->setEnabled(false);
				p_groupChineseShow->button(8)->setStyleSheet(DISENABLE_COLOR);
            } else {
                p_groupChineseShow->button(8)->setEnabled(true);
				p_groupChineseShow->button(8)->setStyleSheet(ENABLE_COLOR);
            }

            if (0 == (m_listChineseID % 7))
                break;
        }
    }
}

/*
 * 功能：
 * 	   光标左移
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::leftMove()
{
    int chineseNum = m_listChineseID % 7;
    switch (chineseNum) {
    case 0:
        m_listChineseID -= 14;
        break;
    case 1:
        m_listChineseID -= 8;
        break;
    case 2:
        m_listChineseID -= 9;
        break;
    case 3:
        m_listChineseID -= 10;
        break;
    case 4:
        m_listChineseID -= 11;
        break;
    case 5:
        m_listChineseID -= 12;
        break;
    case 6:
        m_listChineseID -= 13;
        break;
//     case 7:
//         m_listChineseID -= 14;
//         break;
    default:
        break;
    }
    chineseShow();
}

/*
 * 功能：
 * 	   光标右移
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::rightMove()
{
    chineseShow();
}

/*
 * 功能：
 * 	   SQL语句
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
bool SoftKeyPad::selectSQL()
{
    /**************** 根据输入拼音查询对应的表 ************/
	bool flag = m_query.exec(QString("select chinese from chinesecharactertable where pinyin = '" + m_lineInputLetter + "'"));
	if (!flag)
	{
		qDebug() << QString("m_query from chinesecharactertable fail! The error is %1.").arg(m_query.lastError().text());
		return false;
    }

    /**************** 将查询到的汉字插入到list链表中 ************/
    while(m_query.next())
	{
		QStringList list = m_query.value(0).toString().split(',');
		m_listChinese.append(list);
    }

    /**************** 统计list中string的数量 ************/
    m_listCount = m_listChinese.count();
	
	return true;
}

/*
 * 功能：
 * 	   默认状态
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::defaultStyle()
{
    p_buttonChinese->setStyleSheet("QPushButton{border-image:url(../resources/controlicon/keypad/delete_normal.png);}"\
                                   "font-family:'Arial Regular';font-size:20px;}"\
                                   "QPushButton:pressed{border-image:url(../resources/controlicon/keypad/button_press.png);"\
                                   "font-family:'Arial Regular';font-size:20px;}");
    p_buttonSymbol->setStyleSheet("QPushButton{border-image:url(../resources/controlicon/keypad/symbol_normal.png);}"\
                                   "font-family:'Arial Regular';font-size:20px;}"\
                                   "QPushButton:pressed{border-image:url(../resources/controlicon/keypad/symbol_press.png);"\
                                   "font-family:'Arial Regular';font-size:20px;}");
    p_buttonEnglish->setStyleSheet("QPushButton{border-image:url(../resources/controlicon/keypad/delete_normal.png);}"\
                                   "font-family:'Arial Regular';font-size:20px;}"\
                                   "QPushButton:pressed{border-image:url(../resources/controlicon/keypad/button_press.png);"\
                                   "font-family:'Arial Regular';font-size:20px;}");
}

/*
 * 功能：
 * 	   信号槽连接
 *
 * 参数：
 * 	  无
 *
 * 返回值：
 * 	  无
 */
void SoftKeyPad::connectFunC()
{
    connect(p_buttonCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(p_groupEnglish, SIGNAL(buttonClicked(int)), this, SLOT(slotGroupEnglishClicked(int)));
    connect(p_buttonEnglish, SIGNAL(clicked()), this, SLOT(slotButtonEnglishClicked()));
    connect(p_buttonChinese, SIGNAL(clicked()), this, SLOT(slotButtonChineseClicked()));
    connect(p_buttonSymbol, SIGNAL(clicked()), this, SLOT(slotButtonSymbolClicked()));
    connect(p_groupSymbol, SIGNAL(buttonClicked(int)), this, SLOT(slotGroupSymbolClicked(int)));
    connect(p_buttonBS, SIGNAL(pressed()), this, SLOT(slotButtonBSPressed()));
    connect(p_buttonBS, SIGNAL(released()), this, SLOT(slotButtonBSReleased()));
    connect(p_buttonDEL, SIGNAL(pressed()), this, SLOT(slotButtonDELPressed()));
    connect(p_buttonDEL, SIGNAL(released()), this, SLOT(slotButtonDELReleased()));
    connect(p_buttonLeftMove, SIGNAL(pressed()), this, SLOT(slotButtonMoveLeftPressed()));
    connect(p_buttonLeftMove, SIGNAL(released()), this, SLOT(slotButtonMoveLeftReleased()));
    connect(p_buttonRightMove, SIGNAL(pressed()), this, SLOT(slotButtonMoveRightPressed()));
    connect(p_buttonRightMove, SIGNAL(released()), this, SLOT(slotButtonMoveRightReleased()));
    connect(p_groupChinese, SIGNAL(buttonClicked(int)), this, SLOT(slotGroupChineseClicked(int)));
    connect(p_groupChineseShow, SIGNAL(buttonClicked(int)), this, SLOT(slotGroupChineseShowClicked(int)));
    connect(p_buttonOK, SIGNAL(clicked()), this, SLOT(slotButtonOKClicked()));
    connect(WarningBox::instance(), &WarningBox::warningBoxClosed, this, &SoftKeyPad::onWarningBoxClosed);
	connect(p_lineEdit, &QLineEdit::textChanged, this, &SoftKeyPad::onLineEditChange);
}

/**
* @brief: 输入告警框关闭槽函数
* @return: void
*/
void SoftKeyPad::onWarningBoxClosed(int errorId)
{
    Q_UNUSED(errorId);
    if (isVisible())
    {
        p_lineEdit->setFocus();
        p_lineEdit->setSelection(p_lineEdit->text().size(), 0);
    }
}

void SoftKeyPad::setDefaultStyleSheet()
{
    p_mainFrame->setStyleSheet("QPushButton{border-image:url(../resources/controlicon/keypad/button_normal.png);"\
        "font-family:'Arial Regular';font-size:24px;font-weight:bold;color: rgb(255, 255, 255);}"\
        "QPushButton:pressed {border-image:url(../resources/controlicon/keypad/button_press.png);"\
        "font-family:'Arial Regular';font-size:24px;font-weight:bold;color: rgb(255, 255, 255);}"\
        "#ButtonCancel{border-image:url(../resources/controlicon/keypad/bigBtn_normal.png); color: rgb(255, 255, 255);"\
        "font-family:'Arial Regular';font-size:24px;font-weight:bold;color: rgb(255, 255, 255);}"\
        "#ButtonCancel:pressed {bborder-image:url(../resources/controlicon/keypad/bigBtn_press.png);color: rgb(255, 255, 255);"\
        "font-family:'Arial Regular';font-size:24px;font-weight:bold;color: rgb(255, 255, 255);}"\
        "#ButtonOK{border-image:url(../resources/controlicon/keypad/bigBtn_normal.png);color: rgb(255, 255, 255);"\
        "font-family:'Arial Regular';font-size:24px;font-weight:bold;color: rgb(255, 255, 255);}"\
        "#ButtonOK:pressed {border-image:url(../resources/controlicon/keypad/bigBtn_press.png);color: rgb(255, 255, 255);"\
        "font-family:'Arial Regular';font-size:24px;font-weight:bold;color: rgb(255, 255, 255);}" \
        "#SpaceButton{border-image:url(../resources/controlicon/keypad/space_en.png);}"\
        "#SpaceButton:pressed{border-image:url(../resources/controlicon/keypad/space_en_press.png);}");
}

void SoftKeyPad::setTrText()
{
    p_textEdit->setText(tr("Up to %1 characters").arg(m_maxNum));
    p_buttonCancel->setText(tr("Cancel"));
    p_buttonOK->setText(tr("OK"));
    p_buttonSymbol->setText(tr(""));
}

