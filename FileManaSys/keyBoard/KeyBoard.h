#ifndef KEYBOARD_H__
#define KEYBOARD_H__

#include <QDialog>
#include <QLineEdit>
#include <QFrame>
#include <QPushButton>
//#include "../dialog/windialog.h"
#include "windialog.h"
//#include "../../main/application.h"
class KeyBoard :public WinDialog
{
    Q_OBJECT
public:
    explicit KeyBoard(QWidget *parent = 0, int dialogType = RECORD_NO_HIDDEN_TYPE);
    ~KeyBoard();

	virtual void reset(int num, QString str = "", int keyBoardType = 0) {
		Q_UNUSED(num); Q_UNUSED(str); Q_UNUSED(keyBoardType);
	};
	virtual void setEchoMode(QLineEdit::EchoMode mode) { Q_UNUSED(mode); };
    virtual QString getInputStr(){ return "";}

private:
    void setDefaultStyle();
protected:
    QPushButton* p_buttonCancel;
    QPushButton* p_buttonOK;
    QFrame *     p_mainFrame;
    QVBoxLayout  m_layout;
};

#endif
