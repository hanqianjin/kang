#ifndef ENGLISHKEYBOARD_H
#define ENGLISHKEYBOARD_H

#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QButtonGroup>
#include "windialog.h"
#include "custombutton.h"
#include "KeyBoard.h"

typedef enum ENGLISH_KEYBOARD_TYPE
{
    COMMON_KEYBOARD = 0,
    FILE_NAME_KEYBOARD,
    COUNTRY_NAME_KEYBOARD,
}ENGLISH_KEYBOARD_TYPE;

//英语输入键盘
class EnglishKeyboard : public KeyBoard
{
    Q_OBJECT
public:
     explicit EnglishKeyboard(QWidget *parent = 0, int funcMode = 0);
    //重置键盘
    void                    reset(int num,QString str = "", int keyBoardType = COMMON_KEYBOARD) Q_DECL_OVERRIDE;
    //设置回显
    virtual void            setEchoMode(QLineEdit::EchoMode mode);
    //获取输入字符
    QString                 getInputStr(){return m_inputLineEdit.text();}

signals:
    //屏幕截图调用键盘时使用此信号发送确认状态
    void                    sigOKBtnClicked();
    //屏幕截图调用键盘时使用此信号发送取消或关闭状态
    void                    sigCancelBtnClicked();
private slots:
    //字母键被点击
    void                    slotLetterButtonClicked(int id);
    //输入完成
    void                    slotOkButtonClicked();

    void                    slotClearBtnClicked();
    //删除光标前面一个字符
    void                    slotBSButtonClicked();
    //删除光标后面一个字符
    void                    slotDELButtonClicked();
    //光标向后移动一个字符
    void                    slotBKButtonClicked();
    //光标向前移动一个字符
    void                    slotNTButtonClicked();
    //Shift键被点击
    void                    slotShiftButtonClicked(bool);

    void                    slotCapsButtonClicked(bool);
    /**
    * @brief: 输入告警框关闭槽函数
    * @return: void
    */
    void                    onWarningBoxClosed(int errorId);
private:
    //初始化设置
    void                    initDialog();

    void                    initFnBtns();
    //设置样式
    void                    setDefaultStyleSheet();
    //设置大小写
    void                    changeCase(bool upper);

    void                    setTrText();

    bool                    processKeyBoardLimit();

    int                     getButtonWidth(int index);

    void                    insertLetterBtns(int index);
private:
    QFrame                  m_padFrame;
    QFrame                  m_lettersFrame;
    QFrame                  m_InputFrame;

    ILineEdit               m_inputLineEdit;//输入字符

    QPushButton             m_clearBtn;
    QPushButton             m_closeBtn;

    QButtonGroup            m_lettersGrp;//字符按钮组

    QPushButton             m_letterBtns[64];//字符键集合

    int                     m_maxNum;//最大字符数
    ENGLISH_KEYBOARD_TYPE   m_keyBoardType;
    int                     m_funcMode;
};

#endif // ENGLISHKEYBOARD_H
