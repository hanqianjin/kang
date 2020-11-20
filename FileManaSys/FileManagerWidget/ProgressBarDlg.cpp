/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  ProgressBarDlg.cpp
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

#include "ProgressBarDlg.h"

ProgressBarDlg::ProgressBarDlg(QWidget *parent) :QDialog(parent)
{
    m_fileNum = 0;
    m_fileIndex = 1;

    progress = new QProgressBar;
    progress->setRange(0, 100);

    labelCopying = new QLabel();
    labelFileName = new QLabel();
    labelProgressNumber = new QLabel();

    CancelButton = new QPushButton(tr("Cancel"));

    connect(CancelButton, SIGNAL(clicked()), this, SIGNAL(S_closeDlg()));

    //使得进度弹窗不显示但能阻塞进程,所以去掉控件且大小设为0
//    QGridLayout *layout = new QGridLayout;
//    layout->addWidget(labelCopying, 0, 0, 1, 2);
//    layout->addWidget(labelFileName, 1, 0, 1, 2);
//    layout->addWidget(progress, 2, 0, 1, 2);
//    layout->addWidget(labelProgressNumber, 3, 0);
//    layout->addWidget(CancelButton, 4, 1);
//    setLayout(layout);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAutoFillBackground(true);
    setFixedSize(0, 0);
}

void ProgressBarDlg::set_fileNum(qint64 Num)
{
    qDebug() << "m_fileNum" << Num;
    m_fileNum = Num;
    QString proNum = QString("1/%1").arg(m_fileNum);
    labelProgressNumber->setText(proNum);
}

void ProgressBarDlg::S_updateProgress(qint64 _done, qint64 _total)
{
    int i_Progress = _done * 100 / _total;
    progress->setValue(i_Progress);
}

void ProgressBarDlg::S_setFileCount()
{
    m_fileIndex++;
    if (m_fileIndex <= m_fileNum)
    {
        QString c_Count = QString("%1/%2").arg(m_fileIndex).arg(m_fileNum);
        labelProgressNumber->setText(c_Count);
    }
}

void ProgressBarDlg::S_setFileName(QString Name)
{
    labelFileName->setText(Name);
}

void ProgressBarDlg::S_setOperationName(QString Name)
{
    labelCopying->setText(Name);
}

void ProgressBarDlg::S_resetProgress()
{
    progress->reset();
}

void ProgressBarDlg::S_DlgHide()
{
    this->hide();
}
