/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  ComboBox.cpp
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
#include "ComboBox.h"
#include "LineEdit.h"
#include <QLineEdit>
#include <QScrollBar>
#include <QScroller>
#include <QScrollArea>
#include <QKeyEvent>
#include <QFontMetrics>

#define     RectWidth           		(155)  //左上角的显示样式字符宽度
#define     TEXT_MAXWIDTH               (192)  //字符宽度

ComboBox::ComboBox(QWidget *parent)
    :QComboBox(parent)
	, m_pModel(new QStandardItemModel())
	, m_pListView(new ListView())
	, m_defaultIndex(0)
{      
    init();
    setContextMenuPolicy(Qt::NoContextMenu);
	setFocusPolicy(Qt::NoFocus);
}

ComboBox::ComboBox(int defaultItem, QWidget *parent)
	:QComboBox(parent)
	, m_pModel(new QStandardItemModel())
	, m_pListView(new ListView())
	, m_defaultIndex(defaultItem)
{
	init();
	setContextMenuPolicy(Qt::NoContextMenu);
	setFocusPolicy(Qt::NoFocus);
}

ComboBox::~ComboBox()
{
    if (m_pModel)
    {
        delete m_pModel;
        m_pModel = NULL;
    }
	if (m_pListView != NULL)
	{
		delete m_pListView;
		m_pListView = NULL;
	}
}

/**
* 鼠标滚轮事件
* @param[in] QWheelEvent事件内容
* @return void
*/
void ComboBox::wheelEvent(QWheelEvent* event)
{
	event->accept();
}

/**
* 初始化
*/
void ComboBox::init()
{
	LineEdit *lineEdit = new LineEdit;
	lineEdit->setReadOnly(true);
    lineEdit->setAlignment(Qt::AlignLeft);
    lineEdit->setStyleSheet("QLineEdit{border:0px solid transparent;border-left-width:14px;background-color:transparent;}");

	QFont font;
	font.setFamily("Arial");
    font.setPixelSize(18);

	lineEdit->setFont(font);
	setLineEdit(lineEdit);

	setEnabled(true);
    setStyleSheet("QComboBox{margin-bottom:3px;border-image:url(:/images/filewidgetimage/typebox.png);\
                        min-height: 35px; max-height: 35px; min-width: 380px; max-width: 380px; color:rgb(12,52,102);}\
                   QComboBox::drop-down{background-color: transparent;\
                        min-height: 25px; max-height: 40px; min-width: 40px; max-width: 40px; }\
                   QComboBox QAbstractItemView::item{ min-height:30px; max-height:40px; min-width:360px; max-width:360px; }\
                   QScrollBar:vertical{background-color: rgb(255,255,255); width:22px;margin-top:16px;margin-bottom:16px;margin-right:10px;\
                        border-image:url(:/images/filewidgetimage/scroll .png);border-radius:5px;}\
                   QScrollBar::handle:vertical{width:12px;border-image:url(:/images/filewidgetimage/scroll-handler.png);\
                        margin-left:2px;margin-right:2px;margin-top:2px;margin-bottom:2px;border-radius:4px;}\
                   QScrollBar::sub-line:vertical{background:transparent;}\
                   QScrollBar::add-line:vertical{background:transparent;}\
                   QScrollBar::sub-page:vertical{background:transparent;}\
                   QScrollBar::add-page:vertical{background:transparent;}\
				");

	m_pListView->setModel(m_pModel);
	setModel(m_pListView->model());
	setView(m_pListView);
    m_pListView->setStyleSheet("QListView{border-image:url(:/images/filewidgetimage/dropdown.png)6 6 6 6;\
                    color:rgb(255,255,255);border-radius:3px;min-width:380px; max-width:380px;}\
                    QListView::item{color:rgb(0,0,0);border: 0px solid rgb(255,255,255);background-color: rgb(255,255,255);\
                         margin-left:10px;margin-top:5px;margin-bottom:5px;margin-right:10px;}\
                    QListView::item:selected{color:rgb(243,193,68);border: 0px solid rgb(255,255,255);background-color: rgb(255,255,255);\
                         margin-left:10px;margin-top:5px;margin-bottom:5px;margin-right:10px;}\
                    QListView::item:hover{color:rgb(243,193,68);border: 0px solid rgb(255,255,255);background-color: rgb(255,255,255);\
                         margin-left:10px;margin-top:5px;margin-bottom:5px;margin-right:10px;}\
					");
	m_pListView->verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
	m_pListView->window()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
//    m_pListView->window()->setAttribute(Qt::WA_TranslucentBackground);
	m_pListView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel); //设置滚动条按像素滑动

    QFont viewFont;
    viewFont.setFamily("Arial");
    viewFont.setPixelSize(14);
    m_pListView->setFont(viewFont);

	// 设置滚动条属性
	QScroller *scroller = QScroller::scroller(m_pListView->viewport());
	QScrollerProperties prop = scroller->scrollerProperties();
	prop.setScrollMetric(QScrollerProperties::OvershootDragDistanceFactor, 0.5);
	prop.setScrollMetric(QScrollerProperties::OvershootDragResistanceFactor, 0.1);
	prop.setScrollMetric(QScrollerProperties::OvershootScrollDistanceFactor, 0.5);
	prop.setScrollMetric(QScrollerProperties::OvershootScrollTime, 0.001);
	prop.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy, QScrollerProperties::OvershootAlwaysOff);
	prop.setScrollMetric(QScrollerProperties::HorizontalOvershootPolicy, QScrollerProperties::OvershootAlwaysOff);
	scroller->setScrollerProperties(prop);
	scroller->grabGesture(m_pListView->viewport(), QScroller::TouchGesture);
	scroller->grabGesture(m_pListView->viewport(), QScroller::LeftMouseButtonGesture);

	connect(this, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::editTextChanged),
		this, &ComboBox::onCurrnetEditTextChanged);
	connect(m_pListView, &ListView::hideThePopup, this, &ComboBox::onHideThePopup);
}
/**
* 字符长度溢出时完整显示字符
*/
void ComboBox::DisconnectEnabled()
{
    disconnect(this, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::editTextChanged),
        this, &ComboBox::onCurrnetEditTextChanged);
}
/**
* 字符长度溢出时添加省略号
*/
void ComboBox::onCurrnetEditTextChanged(const QString &text)
{
	QString strText = text;
    QLineEdit *lineEdit = this->lineEdit();
 	QFontMetrics fontWidth(lineEdit->font());
	int width = fontWidth.width(text);

	if (width >= TEXT_MAXWIDTH)
	{
		strText = fontWidth.elidedText(text, Qt::ElideRight, TEXT_MAXWIDTH);
	}
	lineEdit->setText(strText);
}
/**
* 恢复Qt默认设置
*/
void ComboBox::restoreDefaultSetting()
{
    setStyleSheet("");
}

/**
* 重写setCurrentText函数
场景：使用此函数到值下拉列表高亮项与显示项不对应
* @param[in] text 内容
* @return void
*/
void ComboBox::setCurrentText(const QString &text)
{
	int index = this->findText(text);
	if (-1 == index)
	{
		index = 0;
	}
	setCurrentIndex(index);
}

/**
* 添加Item
* @param[in] list 内容
* @return void
*/
void ComboBox::addItems(QStringList list)
{
	for (int i = 0; i < list.size(); i++)
	{
		addItem(list.at(i));
	}
}

/**
* 添加Item
* @param[in] list 内容
* @return void
*/
void ComboBox::insertItems(int index, const QStringList &texts)
{
	Q_UNUSED(index);
    addItems(texts);
}

/**
* 添加Item
* @param[in] text 内容
* @param[int] parent 父节点，默认为顶级节点
* @return void
*/
void ComboBox::addItem(const QString &text, const QVariant &userData)
{
	QStandardItem *pItem = new QStandardItem();
	pItem->setTextAlignment(Qt::AlignCenter);
	pItem->setText(text);
    pItem->setData(userData, Qt::UserRole);
	m_pModel->appendRow(pItem);
}

/**
* Reset按键处理
*/
void ComboBox::operateResetKey()
{
	setCurrentIndex(m_defaultIndex);
}

/**
* 设置主窗口菜单栏左上角的显示样式-单个Item
* @return void
*/
void ComboBox::setMainMenuStatusOneItem()
{
	setDisabled(true);
	setStyleSheet("QComboBox#statusComboBox{margin-bottom:3px;border-image:url(../resources/controlicon/combo/main menu disable.png);\
                  color:rgb(255,255,255); min-height: 45px; max-height: 45px; min-width: 190px; max-width: 190px;}\
				  QComboBox#statusComboBox::drop-down{background-color: rgb(0,0,0,0);\
						min-height: 45px; max-height: 45px; min-width: 25px; max-width: 25px;}\
				");
}

/**
* 设置主窗口菜单栏左上角的显示样式-多个Item
* @return void
*/
void ComboBox::setMainMenuStatusMultiItem()
{
	setEnabled(true);
	setStyleSheet("QComboBox#statusComboBox{margin-bottom:3px;border-image:url(../resources/controlicon/combo/combo.png);\
						color:rgb(255,255,255); min-height: 45px; max-height: 45px; min-width: 190px; max-width: 190px;}\
					QComboBox#statusComboBox::drop-down{background-color: rgb(0,0,0,0);\
						min-height: 45px; max-height: 45px; min-width: 25px; max-width: 25px;}\
					QComboBox#statusComboBox QAbstractItemView::item{ min-height:40px; max-height:40px; min-width:130px; max-width:130px; color:rgb(255, 255, 255);}\
                    QScrollBar:vertical{background-color: rgb(0,0,0,0); width:15;margin-top:16px;margin-bottom:16px;margin-right:5px;\
                        border-image:url(../resources/controlicon/combo/scrollBG.png)}\
					QScrollBar::handle:vertical{width:19px;border-image:url(../resources/controlicon/combo/scroll.png);}\
					QScrollBar::add-line:vertical,QScrollBar::sub-line:vertical{height:0px}\
					QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background:transparent}\
				");

	m_pListView->setStyleSheet("QListView{ background-color: rgb(0,0,0,0);border-image:url(../resources/controlicon/combo/dropdownwidget.png)10 10 0 10;\
						min-width: 190px; max-width: 190px;;border-radius:8px;}\
					QListView::item:selected{border-image:url(../resources/controlicon/combo/slectitem.png);\
						margin-left:15px;margin-right:15px; min-height:40px; max-height:40px; min-width:130px; max-width:130px;}\
                    QListView::item:hover{border-image:url(../resources/controlicon/combo/hover.png);\
						margin-left:15px;margin-right:15px; min-height:40px; max-height:40px; min-width:130px; max-width:130px;}\
					");
	m_pListView->setSpacing(2);

    QFont font;
    font.setFamily("Arial");
    font.setPixelSize(12);
    m_pListView->setFont(font);
}

/**
* @brief : 设置ComboBox单个Item
* @param[in] : height
* @param[in] : width
* @param[in] : name
* @return : void
*/
void ComboBox::setComboBoxOneItemStyle(int height, int width, QString name)
{
    QString styleStr = QString("QComboBox#%1{margin-bottom:3px;border-image:url(../resources/controlicon/combo/combo.png);\
                                color:rgb(255,255,255); min-height: %2px; max-height: %3px; min-width: %4px; max-width: %5px;}"\
				                ).arg(name).arg(height).arg(height).arg(width).arg(width);
	setStyleSheet(styleStr);
}

/**
* 设置主界面状态字体大小
* @param[int] text 需要显示的字符串
* @return void
*/
void ComboBox::setMenuStatusFontSize(QString text)
{
    int ArialSize = 15;

    QFont font;
    font.setFamily("Arial");
    font.setPixelSize(ArialSize);

    QFontMetrics fm(font);

    QRect rec = fm.boundingRect(text);
    int textSize = rec.width();

    while (textSize > RectWidth)
    {
        --ArialSize;
        font.setPixelSize(ArialSize);
        QFontMetrics fm(font);
        rec = fm.boundingRect(text);
        textSize = rec.width();
    }

    lineEdit()->setFont(font);
}
/**
* 设置主窗口菜单栏左上角的显示样式
* @return void
*/
void ComboBox::setMainMenuStatusItem(int currentIndex, QStringList list)
{
	if (currentIndex < 0 || (currentIndex + 1) > list.count())
	{
		return;
	}

    clear();
    addItems(list);

	QString currentItem = list.at(currentIndex);
	setMenuStatusFontSize(currentItem);

	setCurrentIndex(currentIndex);

	if (list.count() > 1)
	{
		setMainMenuStatusMultiItem();
	}
	else
	{
		setMainMenuStatusOneItem();
	}
}

/**
* 设置总览图菜单栏显示组的显示样式
* @return void
*/
void ComboBox::setOVComboBoxText(int currentStrIndex, QStringList groupListStr)
{
    clear();
    addItems(groupListStr);
    setCurrentIndex(currentStrIndex);

    setEnabled(true);
    QFont font;
    font.setFamily("Arial Rounded MT Bold");
    font.setPixelSize(15);
    setFont(font);
    if (1 == groupListStr.count())
    {      
        setStyleSheet("QComboBox#groupIndexBox{border-image:url(../resources/controlicon/combo/overviewcombo_un.png);color:rgb(0, 64, 127);}\
                       QComboBox#groupIndexBox::drop-down{border-style: none;}");
        setEnabled(false);
        return;
    }

    setStyleSheet("QComboBox#groupIndexBox{margin-bottom:3px;border-image:url(../resources/controlicon/combo/OverviewComb.png);\
                    color:rgb(255,255,255); min-height: 30px; max-height: 30px; min-width: 230px; max-width: 230px;}\
					QComboBox#groupIndexBox::drop-down{border-style: none;}\
                    QComboBox#groupBox QAbstractItemView{border-radius:5px;\
                        min-height: 45px; max-height: 429px; min-width: 230px; max-width: 230px;}\
					QComboBox#groupIndexBox QAbstractItemView::item{ min-height:30px; max-height:30px; min-width:130px; max-width:130px; }\
                    QScrollBar:vertical{background-color: rgb(0,0,0,0); width:20;margin-top:16px;margin-bottom:16px;margin-right:10px;\
                        border-image:url(../resources/controlicon/combo/scrollBG.png)}\
					QScrollBar::handle:vertical{width:24px;border-image:url(../resources/controlicon/combo/scroll.png);}\
					QScrollBar::add-line:vertical,QScrollBar::sub-line:vertical{height:0px}\
					QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background:transparent}\
                ");

    m_pListView->setStyleSheet("QListView{ background-color: rgb(0,0,0,0);border-image:url(../resources/controlicon/combo/overviewwidget.png)0 10 10 10;\
						        min-height:45px; max-height: 429px; min-width: 230px; max-width: 230px;}\
								QListView::item{border-radius:5px; color:#ffffff; \
								margin-left:15px; margin-right:15px; margin-top:5px; margin-bottom:5px;}\
					            QListView::item:selected{border-image:url(../resources/controlicon/combo/slectitem.png);\
								border-radius:5px;color:#ffffff;\
						        margin-left:15px;margin-right:15px; min-height:30px; max-height:30px; min-width:130px; max-width:130px;}\
                                QListView::item:hover{border-image:url(../resources/controlicon/combo/hover.png);\
								border-radius:5px;color:#ffffff;\
						        margin-left:15px;margin-right:15px; min-height:30px; max-height:30px; min-width:130px; max-width:130px;}\
					            ");

    font.setPixelSize(12);
    m_pListView->setFont(font);
}

/**
* 设置多画面对话框下拉菜单的显示样式-多个Item
* @return void
*/
void ComboBox::setMultiPanelDialogStyle(bool enable)
{
    clear();
    setEnabled(enable);

    QString fontColor = enable ? "rgb(255,255,255)" : "#00407f";
    QString boxImage = enable ? "../resources/32icon/multipanel/dialog/groupBox_normal.png"
                              : "../resources/32icon/multipanel/dialog/groupBox_disable.png";
    //border-image:url(../resources/32icon/multipanel/dialog/boxArrow.png);min-height: 25px; max-height: 25px; min-width: 25px; max-width: 25px;";
    //QComboBox#groupBox QAbstractItemView{border-radius:5px; min-height: 429px; max-height: 429px; min-width: 230px; max-width: 230px;}
	QString pStyleSheet = QString("QComboBox#groupBox{border-radius:5px; background-color:rgb(255,255,255,0); margin-bottom:3px;\
                         border-image:url(%1); color:%2; min-height: 25px; max-height: 25px; min-width: 230px; max-width: 230px; }\
					QComboBox#groupBox::drop-down{border-image:url(../resources/controlicon/combo/enabledown.png); min-height: 25px; max-height: 25px; min-width: 25px; max-width: 25px;}\
					QComboBox#groupBox QAbstractItemView{border-radius:5px; min-height: 0px; max-height: 429px; min-width: 230px; max-width: 230px;}\
                    QComboBox#groupBox QAbstractItemView::item{border-radius:5px; min-height: 30px; max-height: 30px; min-width: 200px; max-width: 200px;}\
                    QComboBox#groupBox QAbstractItemView::item:selected:active{border-image:url(../resources/32icon/multipanel/dialog/groupBox3.png);\
                        min-height: 30px; max-height: 30px; min-width: 200px; max-width: 200px;}\
					 QScrollBar:vertical{background-color:rgb(0,0,0,0); width:20;margin-top:16px; margin-bottom:16px; margin-right:10px;\
                        border-image:url(../resources/controlicon/combo/scrollBG.png)}\
					QScrollBar::handle:vertical{width:24px;border-image:url(../resources/controlicon/combo/scroll.png);}\
					QScrollBar::add-line:vertical,QScrollBar::sub-line:vertical{height:0px}\
                    QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background:transparent};").arg(boxImage).arg(fontColor);
    setStyleSheet(pStyleSheet);

    QFont font;
    font.setFamily("Arial");
    font.setPixelSize(13);
    setFont(font);
	//min-height: 429px; max-height: 429px; min-width: 230px; max-width: 230px;
    m_pListView->setStyleSheet("QListView{background-color:rgb(0,0,0,0); border-radius:5px;\
                        border-image:url(../resources/32icon/multipanel/dialog/groupBox2.png)0 10 10 10;\
                        min-height: 0px; max-height: 429px; min-width: 230px; max-width: 230px;}\
                    QListView::item{border-radius:5px; color:#ffffff; \
                        margin-left:15px; margin-right:15px; margin-top:5px; margin-bottom:5px;}\
                    QListView::item:selected:active{border-radius:5px; color:#ffffff;\
                    	margin-left:15px; margin-right:15px; margin-top:5px; margin-bottom:5px}\
					QListView::item:hover{border-image:url(../resources/controlicon/combo/hover.png);\
						border-radius:5px; color:#ffffff; margin-left:15px; margin-right:15px; \
						min-height:30px; max-height:30px; min-width:200px; max-width:200px;}");
}

void ComboBox::setReportSummaryStyle(int height, int width, QString name)
{
	Q_UNUSED(height); Q_UNUSED(width);

    setStyleSheet("QComboBox{margin-bottom:3px;border-image:url(../resources/controlicon/combo/report_combo_un.png);\
						min-height: 25px; max-height: 25px; min-width: 225px; max-width: 225px; color:rgb(255,255,255);}\
					QComboBox::drop-down{border-image:url(../resources/controlicon/combo/universe down.png);\
                        min-height: 25px; max-height: 25px; min-width: 25px; max-width: 25px; }\
                        QComboBox::drop-down:on{border-image:url(../resources/controlicon/combo/report_combo_on.png);\
                        min-height: 25px; max-height: 25px; min-width: 25px; max-width: 25px; }\
                    QComboBox QAbstractItemView::item{min-height:30px; max-height:30px; min-width:140px; max-width:140px;}\
					QScrollBar:vertical{margin-top:16px;margin-bottom:16px;margin-right:10px;width:15;\
						border-image:url(../resources/controlicon/combo/scrollBG.png)}\
					QScrollBar::handle:vertical{border-image:url(../resources/controlicon/combo/scroll.png);\
						border-radius:4px; min-height:50px;}\
					QScrollBar::add-line:vertical,QScrollBar::sub-line:vertical{height: 0px}\
					QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background:transparent}\
				");
}

void ComboBox::showPopup()
{
    emit popupShow();
    QComboBox::showPopup();
}
void ComboBox::hidePopup()
{
    emit popupHide();
	QComboBox::hidePopup();
}

/**
* @brief : 告警框弹出时，将popup隐藏
* @return :
*/
void ComboBox::onHideThePopup()
{
	hidePopup();
}
