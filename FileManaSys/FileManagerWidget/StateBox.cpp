#include "StateBox.h"
#include "ui_StateBox.h"
#include <QDebug>

StateBox::StateBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StateBox)
  , m_timer(NULL)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    move(QPoint(0,0));
}

StateBox::~StateBox()
{
    delete ui;
    if (m_timer)
    {
        delete m_timer;
        m_timer = NULL;
    }
}

void StateBox::showMessage(QString info, bool autoClose, int time)
{
    if (info.trimmed().length() > 0)
    {
        ui->m_stateLabel->setText(tr(info.toUtf8()));
    }
    show();
    delayClose(autoClose, time);
}

void StateBox::delayClose(bool autoClose, int time)
{
    if (m_timer)
    {
        m_timer->deleteLater();
        m_timer = NULL;
    }

    if (autoClose)
    {
        m_timer = new QTimer(this);
        m_timer->singleShot(time, this, SLOT(close()));
    }
}

void StateBox::closeEvent(QCloseEvent *e)
{
    QWidget::closeEvent(e);
    emit stateboxClosed();
}
