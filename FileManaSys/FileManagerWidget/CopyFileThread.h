/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  CopyFileThread.h
** Latest Version:             V1.0.0
** Latest modified Date:       2019/5/20
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by:                 Zhou Yuhan
** Created date:               2019/5/20
** Descriptions:               END
**
*********************************************************************************************************/

#ifndef COPYFILETHREAD_H
#define COPYFILETHREAD_H

#include <QObject>
#include <QThread>
#include <QDir>
#include <QDebug>

class CopyFileThread : public QThread
{
    Q_OBJECT
public:
    CopyFileThread();

    ~CopyFileThread(){}

    bool get_start();
    void set_start();
    void set_srcpath(QString path);
    void set_targetpath(QString path);
    void set_file();
    void set_dir();
    void set_run(bool value);
    bool get_run();

signals:
    void G_sndProgressValue(qint64 _done, qint64 _total);
    void G_sndFileCount();
    void G_DialogHide();
    void G_ProgressReset();

protected:
    void run();

private:
    bool pasteDir(QString & srcPath, QString & targetPath);

    /*复制文件*/
    bool copyProgress(QString fileName, QString newName);

    bool removeDir(QString & dirPath);

    bool isCorrectSuffix(QString fileName);

private slots:
    void G_quitThread();

private:
    QString             m_srcpath;      //源路径->为需要复制或移动的文件或目录的绝对路径
    QString             m_targetpath;   //目标路径->为目标目录的绝对路径
    QString             m_fileCopying;  //正在复制的文件
    bool                m_start;        //开始标志
    bool                m_isfile;       //文件或目录标志
    bool                m_run;
};

#endif // COPYFILETHREAD_H
