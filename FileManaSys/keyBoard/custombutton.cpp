#include "custombutton.h"

CustomButton::CustomButton(QWidget *parent) :
    QPushButton(parent),
    m_speed(1)
{
    this->setAutoRepeat(true);
    connect(&m_speedTimer, SIGNAL(timeout()), this, SLOT(slotTimerOut()));
    connect(this, SIGNAL(clicked()), this, SLOT(slotBtnClicked()));
}

void CustomButton::mousePressEvent(QMouseEvent * e)
{
    m_speedTimer.start(100);
    m_speed = 1;

    QPushButton::mousePressEvent(e);
}

void CustomButton::mouseReleaseEvent(QMouseEvent * e)
{
    m_speedTimer.stop();

    QPushButton::mouseReleaseEvent(e);
}

void CustomButton::slotTimerOut()
{
    if (m_speed < 50) {
        m_speed += 5;
    }
}

void CustomButton::slotBtnClicked()
{
    emit clicked(m_speed);
}

/********************************************************************/
WinCustomButton::WinCustomButton(QString name, QIcon icon, QWidget *parent)
    : QToolButton(parent)
{
    this->setFocusPolicy(Qt::NoFocus);
    this->setText(name);
    this->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->setIcon(icon);
    this->setIconSize(QSize(40,20));
    this->setAutoRepeat(true);
    this->setAutoRepeatDelay(100);
    this->resize(50, 50);
    this->setStyleSheet("QToolButton {border: none;font-size:14px;color:#000000}");
}

/********************************************************************/
ImageButton::ImageButton(QWidget *parent):
    QPushButton(parent)
{
    p_txtLabel = new QLabel(this);
//    p_txtLabel->setAttribute(Qt::WA_TranslucentBackground);
    p_txtLabel->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
	this->setStyleSheet("QPushButton{border:none;padding-bottom: 12px;}");
}

void ImageButton::loadImage(QString url)
{
    this->setIcon(QIcon(url));
    this->setIconSize(QSize(this->width(), this->height()));
}

void ImageButton::setText(QString text)
{
    p_txtLabel->setText(text);
}

void ImageButton::resizeLabel(int width, int height)
{
    p_txtLabel->setGeometry(0, 0, width, height - 8);
}

void ImageButton::setTextColor(QPalette &palette)
{
    p_txtLabel->setPalette(palette);
}


/********************************************************************/
void ILineEdit::keyPressEvent(QKeyEvent *event)
{
    if(event->matches(QKeySequence::SelectAll)
            || event->matches(QKeySequence::Copy)
            || event->matches(QKeySequence::Cut)
            || event->matches(QKeySequence::Paste))
    {
        return;
    }

    QLineEdit::keyPressEvent(event);
}

//void ILineEdit::mouseMoveEvent(QMouseEvent *event)
//{
//    Q_UNUSED(event);
//    return;
//}

//void ILineEdit::mouseDoubleClickEvent(QMouseEvent *event)
//{
//    Q_UNUSED(event);
//    return;
//}

//void ILineEdit::mouseReleaseEvent(QMouseEvent *)
//{
//    return;
//}

//void ILineEdit::mousePressEvent(QMouseEvent *)
//{
//    return;
//}

/********************************************************************/
void ITextEdit::keyPressEvent(QKeyEvent *event)
{
    if(event->matches(QKeySequence::SelectAll)
            || event->matches(QKeySequence::Copy)
            || event->matches(QKeySequence::Cut)
            || event->matches(QKeySequence::Paste))
    {
        return;
    }

    QTextEdit::keyPressEvent(event);
}

void ITextEdit::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    return;
}

void ITextEdit::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    return;
}
