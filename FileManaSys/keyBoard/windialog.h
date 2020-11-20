#ifndef WINDIALOG_H
#define WINDIALOG_H

#include <QDialog>
#include <QStackedLayout>
//#include "cfgGlobalDef.h"
//#include "../baseview/View.h"
//#include "../../main/application.h"
//#include "../MainWindow.h"

typedef enum WINDIALOG_TYPE
{
    NORMAL_TYPE = 0,		//点击记录按键与menu按键都需要隐藏 默认
    RECORD_NO_HIDDEN_TYPE,	//点击记录按键不需要隐藏，但点击menu按键需要隐藏
	MENU_NO_HIDDEN_TYPE		//点击记录按键和menu按键都不需要隐藏 
}WINDIALOG_TYPE;

typedef enum WIN_MSG_TYPE
{
    MENU_MSG = 0, 
    RECORD_MSG
}WIN_MSG_TYPE;

class WinDialog;
class WinStackedLayout;

class WinDialog : public QDialog
{
    Q_OBJECT
public:
    explicit WinDialog(int dialogType = NORMAL_TYPE, QWidget *parent = 0);
    virtual ~WinDialog();

	/**
	* @brief：翻译函数，每个需要翻译的界面都需要实现这个接口
	* @return: void
	*/
	virtual void        setTrText() {};

protected:
	/**
	* @brief: 获取对话框类型
    * @return:    int
    */
	int					dialogType() { return m_dialogType; }

signals:
    void				sigChangeFrame(quint32 frameId);//画面切换

protected slots:
    /**
    * @brief: 关闭对话框响应槽
	* @param[in]: msgType
    * @return:    void
    */
    virtual void		onCloseDialog(int msgType);

protected:
	int						m_dialogType;
};

class WinStackedLayout : public QStackedLayout
{
    Q_OBJECT
public:
    WinStackedLayout();
    explicit WinStackedLayout(QWidget *parent);
    explicit WinStackedLayout(QLayout *parentLayout);

    void addWidget(QWidget *w);
    void addWidget(QWidget *w, Qt::Alignment alignment);
    void setGeometry(const QRect &rect);
};

#endif // WINDIALOG_H
