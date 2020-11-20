/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  KeyBoardSelectView.cpp
** Latest Version:             V1.0.0
** Latest modified Date:       2018/07/13
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by:                 Wang FeiLong
** Created date:               2018/07/13
** Descriptions:
**
*********************************************************************************************************/
#include "KeyBoardSelectView.h"
//#include "../../src/common/DataType.h"

KeyBoardSelectView *KeyBoardSelectView::m_instance = NULL;

KeyBoardSelectView* KeyBoardSelectView::instance()
{
    if (!m_instance)
    {
        m_instance = new KeyBoardSelectView;
    }
    return m_instance;
}

KeyBoardSelectView::KeyBoardSelectView(int key)
    : View(key)
    , m_currentLanguage(Language_Type_English)
{
    enableCfgNotifier();
    registerMsgFun(SYS_SETTING_ENVIRONMENT_SETTINGS, VIEW_FUN(KeyBoardSelectView, processLanguageTypeChangedMsg));
}

/**
* @brief:初始化操作
* @return:    int
*/
int KeyBoardSelectView::init()
{
    requestConfig(SYS_SETTING_ENVIRONMENT_SETTINGS);
    return OK;
}

/**
* @brief:配置数据变更通知处理函数
* @param[in]: int cfgType
* @return:    int
*/
int KeyBoardSelectView::cfgChanged(int changeType, int cfgType, const QVariant changedConent)
{
    Q_UNUSED(changedConent);

    if (changeType != ICfgNotifier::ConfigValided)
    {
        return MSG_MODE_IS_ERROR;
    }

    if (cfgType == LOAD_CONFIG_END || cfgType == SYS_SETTING_ENVIRONMENT_SETTINGS)
    {
        requestConfig(SYS_SETTING_ENVIRONMENT_SETTINGS);
    }
   
    return OK;
}

/**
* @brief: 获取最新配置
* @return: void
*/
void KeyBoardSelectView::requestConfig(int dataType)
{
    MsgHelp msgHelp;
    MSG_S *msg = msgHelp.mallocMsg(this, dataType, 0, READ_SAVED_CFG_MSG);
    if (NULL == msg)
    {
        return;
    }

    int ret = msgHelp.postMsgEvent(CFG_DATA_PROCESSER, msg);
    if (ret != OK)
    {
        free(msg);
    }
}

/**
* @brief:处理从配置表中读取的语言类型改变消息
* @param[in]: MSG_S * msg
* @return:    int
*/
int KeyBoardSelectView::processLanguageTypeChangedMsg(MSG_S *msg)
{
    if (NULL == msg)
    {
        return MSG_IS_NULL_PTR;
    }

    int result = 0;
    char *pText = msg->text;
    getValue(pText, QMetaType::Int, &result);
    if (OK != result)
    {
        return REQUEST_RECORD_FAIL;
    }

    ENVIRONMENT_CONFIG config = *((ENVIRONMENT_CONFIG*)pText);
    if (m_currentLanguage != config.languageType)
    {
        m_currentLanguage = config.languageType;
    }

    return OK;
}

/**
* @brief: 根据当前的语言类型获取键盘实例
* @return: void
*/
KeyBoard* KeyBoardSelectView::getKeyBoardInstance(KEYBOARD_SELECT_ENUM type)
{
    switch(type)
    {
    case AUTO_SELECT_KEYBOARD:
        return getKeyBoardInstanceForCurrentLanguage();
        break;
    case SELECT_ENGLISH_KEYBOARD:
        return EnglishKeyboard::instance();
        break;
    case SELECT_CHINESE_KEYBOARD:
        return EnglishKeyboard::instance();
        //return SoftKeyPad::instance();
        break;
    default:
        break;
    }

    return NULL;
}

/**
* @brief: 根据当前的语言类型获取键盘实例
* @return: void
*/
KeyBoard* KeyBoardSelectView::getKeyBoardInstanceForCurrentLanguage()
{
    if (m_currentLanguage == Language_Type_English)
    {
        return EnglishKeyboard::instance();
    }
    else if (m_currentLanguage == Language_Type_Chinese)
    {
        return EnglishKeyboard::instance();
        //return SoftKeyPad::instance();
    }
    else
    {
        return EnglishKeyboard::instance();
    }
}
