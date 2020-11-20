#include "windialog.h"
#include <QKeyEvent>
#include <QDebug>

WinDialog::WinDialog(int dialogType, QWidget *parent)
    :QDialog(parent)
	, m_dialogType(dialogType)
{
    this->setFocus();
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setGeometry(0, 0, 1024/*F270App->mainWindow()->width()*/, 768/*F270App->mainWindow()->height()*/);

}

WinDialog::~WinDialog()
{

}

/**
* @brief: 关闭对话框响应槽
* @param[in]: msgType
* @return:    void
*/
void WinDialog::onCloseDialog(int msgType)
{
	if (RECORD_MSG == msgType) //记录按键消息
	{
		if (this->dialogType() != NORMAL_TYPE)
		{
			return;
		}
	}
	else //物理按键消息
	{
		if (this->dialogType() == MENU_NO_HIDDEN_TYPE)
		{
			return;
		}
	}

	this->close();
}


WinStackedLayout::WinStackedLayout()
{
}

WinStackedLayout::WinStackedLayout(QWidget *parent) :
    QStackedLayout(parent)
{
}

WinStackedLayout::WinStackedLayout(QLayout *parentLayout):
    QStackedLayout(parentLayout)
{
}


void WinStackedLayout::addWidget(QWidget *w)
{
    QStackedLayout::addWidget(w);
}

void WinStackedLayout::addWidget(QWidget *w, Qt::Alignment alignment)
{
    QStackedLayout::addWidget(w);
    setAlignment(w,alignment);
}

void WinStackedLayout::setGeometry(const QRect &rect)
{
    switch (stackingMode()) {
    case StackOne:
    {
        if(QLayoutItem  *item = itemAt(currentIndex())){
            item->setGeometry(rect);
        }
        break;
    }

    case StackAll:
    {
        int i = 0;
        QLayoutItem  *item = NULL;
        while((item = itemAt(i++)) != NULL)
            item->setGeometry(rect);
        break;
    }
    }
}
