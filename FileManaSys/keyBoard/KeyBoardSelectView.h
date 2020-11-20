/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  KeyBoardSelectView.h
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
#ifndef KEYBOARDSELECTVIEW_H__
#define KEYBOARDSELECTVIEW_H__

#include "KeyBoard.h" 
#include "englishkeyboard.h"

enum KEYBOARD_SELECT_ENUM
{
    AUTO_SELECT_KEYBOARD = 0,
    SELECT_ENGLISH_KEYBOARD,
    SELECT_CHINESE_KEYBOARD,
};

class KeyBoardSelectView : public View
{
    Q_OBJECT
public:
    static KeyBoardSelectView*    instance();
    virtual QString               name()    { return "KeyBoardSelectView"; };
    virtual int                   init();
    virtual int                   makeTopWidget() { return OK; };
    /**
    * @brief:配置数据变更通知处理函数
    * @param[in]: int cfgType
    * @return:    int
    */
    virtual int                   cfgChanged(int changeType, int cfgType, const QVariant changedConent = QVariant());
    /**
    * @brief: 根据当前的语言类型获取键盘实例
    * @param[in]: KEYBOARD_SELECT_ENUM type
    * @return: KeyBoard*
    */
    KeyBoard*                     getKeyBoardInstance(KEYBOARD_SELECT_ENUM type = AUTO_SELECT_KEYBOARD);
private:
    explicit KeyBoardSelectView(int key = -1);
    virtual ~KeyBoardSelectView() { };
    /**
    * @brief: 根据当前的语言类型获取键盘实例
    * @return: void
    */
    KeyBoard*                     getKeyBoardInstanceForCurrentLanguage();
private:
    static KeyBoardSelectView     *m_instance;
    Language_Type                  m_currentLanguage;
};

#endif // KEYBOARDSELECTVIEW_H__

