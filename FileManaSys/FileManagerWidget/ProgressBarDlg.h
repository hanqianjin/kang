/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  ProgressBarDlg.h
** Latest Version:             V1.0.0
** Latest modified Date:       2019/5/21
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by:                 Zhou Yuhan
** Created date:               2019/5/21
** Descriptions:               END
**
*********************************************************************************************************/

#ifndef PROGRESSBARDLG_H
#define PROGRESSBARDLG_H

#include <QDialog>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QObject>

class ProgressBarDlg : public QDialog
{
    Q_OBJECT
public:
    ProgressBarDlg(QWidget *parent = 0);
    void set_fileNum(qint64 Num);
    void S_setFileName(QString Name);
    void S_setOperationName(QString Name);

public slots:
    void S_updateProgress(qint64 _done, qint64 _total);
    void S_setFileCount();
    void S_resetProgress();
    void S_DlgHide();

signals:
    void S_closeDlg();

private:
    QProgressBar       *progress;
    qint64              m_fileNum;
    qint64              m_fileIndex;
    QLabel             *labelCopying;
    QLabel             *labelFileName;
    QLabel             *labelProgressPercent;
    QLabel             *labelProgressNumber;
    QPushButton        *CancelButton;
};

#endif // PROGRESSBARDLG_H
