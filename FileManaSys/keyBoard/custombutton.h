#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QToolButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QKeyEvent>

/**
 * @brief The CustomButton class
 *  自定义按钮1
 */
class CustomButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CustomButton(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);

signals:
    void clicked(quint32 speed);

private slots:
    void slotTimerOut();
    void slotBtnClicked();

private:
    quint32 m_speed;
    QTimer m_speedTimer;
};

/**
 * @brief The WinCustomButton class
 *  自定义按钮：按下之后可实现自动定时滑动
 */
class WinCustomButton : public QToolButton
{
    Q_OBJECT

public:
    WinCustomButton(QString name, QIcon icon, QWidget * parent = 0);
    ~WinCustomButton() {}
};

/**
 * @brief The ImageButton class
 * 自定义按钮，可以同时添加文字和图片，图片在上，文字在下
 */
class ImageButton : public QPushButton
{
    Q_OBJECT

public:
    explicit ImageButton(QWidget* parent = 0);

    void loadImage(QString url);        //!< 加载背景图片
    void setText(QString text);             //!<  设置按钮显示的文本内容
    void resizeLabel(int width, int height);        //!<  重新定义文本框的大小
    void setTextColor(QPalette &palette);         //!< 设置文本框的颜色

private:
    QLabel* p_txtLabel;     //!< 显示文本

};

/**
 * @brief The ILineEdit class
 * 重写QLineEdit鼠标和键盘事件
 */
class ILineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit ILineEdit(QWidget* parent = 0) : QLineEdit(parent){}
protected:
    void keyPressEvent(QKeyEvent* event) Q_DECL_OVERRIDE;
    //void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    //void mouseDoubleClickEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    //void mouseReleaseEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    //void mousePressEvent(QMouseEvent *) Q_DECL_OVERRIDE;

};

/**
 * @brief The ITextEdit class
 * 重写QTextEdit鼠标和键盘事件
 */
class ITextEdit : public QTextEdit
{
    Q_OBJECT

public:
    explicit ITextEdit(QWidget* parent = 0) : QTextEdit(parent){}
protected:
    void keyPressEvent(QKeyEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event) ;

};


#endif // CUSTOMBUTTON_H
