/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  ComboBox.h
** Latest Version:             V1.0.0
** Latest modified Date:       2017/09/18
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by:                 niu honglin
** Created date:               2017/09/18
** Descriptions:               END
**
*********************************************************************************************************/
#ifndef COMBOBOX_H_
#define COMBOBOX_H_

#include "ListView.h"
#include <QComboBox>
#include <QFont>
#include <QStandardItemModel>
#include <QString>
#include <QLineEdit>
#include <QEvent>
#include <QListView>

class ComboBox :public QComboBox
{
    Q_OBJECT

public:
    explicit ComboBox(QWidget *parent = Q_NULLPTR);
	ComboBox(int defaultItem, QWidget *parent = Q_NULLPTR);
    ~ComboBox();
signals:
    void popupShow();
    void popupHide();
public:
    /**
    * 字符长度溢出时完整显示字符
    */
    void DisconnectEnabled();
    /**
    * 恢复Qt默认设置
    */
    void restoreDefaultSetting();

	/**
	* 设置主窗口菜单栏左上角的显示样式
	* @return void
	*/
	void setMainMenuStatusItem(int currentIndex, QStringList list);

	/**
	* 鼠标滚轮事件
	* @param[in] QWheelEvent事件内容
	* @return void
	*/
	void wheelEvent(QWheelEvent*);

	/**
	* 添加Item
	* @param[in] list 内容
	* @return void
	*/
	virtual void addItems(QStringList list);

    /**
    * 添加Item
    * @param[in] list 内容
    * @return void
    */
    void insertItems(int index, const QStringList &texts);

	/**
	* 重写setCurrentText函数
			场景：使用此函数到值下拉列表高亮项与显示项不对应
	* @param[in] text 内容
	* @return void
	*/
	void setCurrentText(const QString &text);

	/**
	* 添加Item
	* @param[in] text 内容
	* @param[int] parent 父节点，默认为顶级节点
	* @return void
	*/
    void addItem(const QString &text, const QVariant &userData = QVariant());
    /**
    * 设置总览图菜单栏显示组的显示样式
    * @return void
    */
    void setOVComboBoxText(int currentStrIndex, QStringList groupListStr);
    /**
    * 设置多画面对话框下拉菜单的显示样式-多个Item
    * @return void
    */
    void setMultiPanelDialogStyle(bool enable);

    void setReportSummaryStyle(int height, int width, QString name);

	/**
	* 设置主界面状态字体大小
	* @param[int] text 需要显示的字符串
	* @return void
	*/
	void setMenuStatusFontSize(QString text);
    virtual void showPopup();
	virtual void hidePopup();
private:
    /**
    * 初始化
    */
    void init();

	/**
	* Reset按键处理
	*/
	void operateResetKey();

	/**
	* 设置主窗口菜单栏左上角的显示样式-单个Item
	* @return void
	*/
	void setMainMenuStatusOneItem();
	/**
	* 设置主窗口菜单栏左上角的显示样式-多个Item
	* @return void
	*/
	void setMainMenuStatusMultiItem();
    /**
    * @brief : 设置ComboBox单个Item
    * @param[in] : height
    * @param[in] : width
    * @param[in] : name
    * @return : void
    */
    void setComboBoxOneItemStyle(int height, int width, QString name);

private slots:
	/**
	* @brief : 字符长度溢出时添加省略号
	* @param[in] : text
	* @return : void
	*/
	void onCurrnetEditTextChanged(const QString &text);

	/**
	* @brief : 告警框弹出时，将popup隐藏
	* @return :
	*/
	void onHideThePopup();


private:
	ListView				*m_pListView;
    QStandardItemModel      *m_pModel;
	int					     m_defaultIndex;
};
#endif // !COMBOBOX_H_
