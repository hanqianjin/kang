#ifndef WININFOLISTDIALOG_H
#define WININFOLISTDIALOG_H

#include <QFrame>
#include <QLabel>
#include <QDialog>
#include "windialog.h"
#include <QTimer>
#include <QPushButton>
/*
 * 错误代码和信息显示对话框
 *
 */
class WinInfoListDialog : public WinDialog
{
    Q_OBJECT
public:
    static WinInfoListDialog *instance();
    void start();

    void showMsg(quint32 ErrorNum = 0, QObject *parent = 0);

    static QString getStrMsgbyNum(quint32 ErrorNum);
    static void setStrMsgbyNum();
signals:

public slots:
    void slotCloseClicked();

private:
    WinInfoListDialog();

    void initInfoDialog();  //初始化界面
    void setUserDefineStyle();  //设置风格

private:
    QFrame *p_mainFrame;
    QLabel *pictureLabel;   //标题栏图片
    QLabel *titleLabel;     //标题栏文字
    QLabel *txtLabel;       //错误信息
    quint32 m_ErrorNum;     //错误代码号

};

#endif // WININFOLISTDIALOG_H
