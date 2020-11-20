/****************************************Copyright (c)****************************************************
**
**                                       D.H. InfoTech
**
**--------------File Info---------------------------------------------------------------------------------
** File name:                  CopyFileThread.cpp
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

#include "CopyFileThread.h"

CopyFileThread::CopyFileThread() :m_isfile(true)
{
    m_start = false;
    set_run(true);
}

/*获得当前线程状态，return false线程空闲*/
bool CopyFileThread::get_start()
{
    return m_start;
}

/*线程开始复制或移动文件*/
void CopyFileThread::set_start()
{
    m_start = true;
}

/*设置源文件绝对路径*/
void CopyFileThread::set_srcpath(QString path)
{
    m_srcpath = path;
}

/*设置目标目录绝对路径*/
void CopyFileThread::set_targetpath(QString path)
{
    m_targetpath = path;
}

/*设置文件属性*/
void CopyFileThread::set_file()
{
    m_isfile = true;
}

void CopyFileThread::set_dir()
{
    m_isfile = false;
}

/*设置线程运行标志*/
void CopyFileThread::set_run(bool value)
{
    m_run = value;
}

bool CopyFileThread::get_run()
{
    return m_run;
}

bool CopyFileThread::pasteDir(QString & srcPath, QString & targetPath)
{
    QDir dir(srcPath);
    /*获得子目录*/
    QStringList files = dir.entryList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
    /*使用迭代器访问项*/
    QList<QString>::iterator f = files.begin();

    bool error = true;

    /*目标目录*/
    QString targetabsolutepath = targetPath + '/' + dir.dirName();
    QDir targetdir(targetabsolutepath);
    /*判断目录是否存在，不存在则创建目录*/
    if (!targetdir.exists())
    {
        if (!targetdir.mkpath(targetabsolutepath))
        {
            return false;
        }
    }

    /*遍历复制或移动文件*/
    for (; f != files.end(); f++)
    {
        if (!m_run)
        {
            break;
        }
        QString filePath = QDir::toNativeSeparators(dir.path() + '/' + (*f));
        QFileInfo fi(filePath);
        if (fi.isFile() || fi.isSymLink())
        {
            if(!isCorrectSuffix(filePath))
            {
                continue;
            }
            QString targetFile = targetabsolutepath + '/' + (*f);
            /*文件存在则先删除*/
            if (QFile::exists(targetFile))
            {
                QFile::remove(targetFile);
            }

            if (!copyProgress(filePath, targetFile))
            {
                qDebug() << "copy " << filePath << " fail";
                error = false;
                break;
            }
            emit G_sndFileCount();
        }
        else if (fi.isDir())
        {
            if (!pasteDir(filePath, targetabsolutepath))
            {
                error = false;
                break;
            }
        }

    }
    emit G_sndFileCount();

    return error;
}

/*复制文件*/
bool CopyFileThread::copyProgress(QString fileName, QString newName)
{
    bool error = true;
    QFile srcfile;
    QFile dstfile;
    qint64 count = 0;
    qint64 filesize = QFileInfo(fileName).size();

    srcfile.setFileName(fileName);
    dstfile.setFileName(newName);

    //qDebug() << srcfile.fileName();
    //qDebug() << dstfile.fileName();
    m_fileCopying = dstfile.fileName();
    if (srcfile.open(QIODevice::ReadOnly) && dstfile.open(QIODevice::WriteOnly))
    {
        qDebug() << "start";

        while (!srcfile.atEnd() && m_run)
        {
            static char strBuf[64 * 1024] = { 0 };
            qint64 res = srcfile.read(strBuf, 64 * 1024);
            if (-1 == res)
            {
                error = false;
                break;
            }
            count += res;
            int writeSize = dstfile.write(strBuf, res);
            //qDebug() << "copy file write size:" << res << "return:" << writeSize;
            if (writeSize == -1 || writeSize != res) //文件写入失败
            {
                error = false;
                break;
            }
            dstfile.flush();
            emit G_sndProgressValue(count, filesize);   
        }
        qDebug() << "success";
        srcfile.close();
        dstfile.close();

        //transCount++;
    }
    else
    {
        qDebug() << tr("Failed to open file");
    }

    emit G_ProgressReset();

    return error;
}

void CopyFileThread::run()
{
    while (m_run)
    {
        if (!get_start())
        {
            msleep(10);
            continue;
        }

        if (!QFile::exists(m_srcpath))
        {
            m_start = false;
            continue;
        }

        if (m_isfile)
        {
            if (!copyProgress(m_srcpath, m_targetpath))
            {
                m_run = false;
                emit G_DialogHide();
            }
            emit G_sndFileCount();
        }
        else
        {
            if (!pasteDir(m_srcpath, m_targetpath))
            {
                m_run = false;
                emit G_DialogHide();
            }
        }

        emit G_DialogHide();    //隐藏进度对话框，防止阻塞主线程
        msleep(10);

        m_start = false;
    }
}

void CopyFileThread::G_quitThread()
{
    QFile file(m_fileCopying);
    set_run(false);
    QThread::msleep(50);
    if (file.exists())
    {
        file.remove();
    }
}

//文件夹删除 递归删除
bool CopyFileThread::removeDir(QString & dirPath)
{
    QDir dir(dirPath);
    //获得子目录
    QStringList files = dir.entryList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
    //使用迭代器访问项
    QList<QString>::iterator f = files.begin();

    bool error = true;
    //递归删除
    for (; f != files.end(); f++)
    {
        QString filePath = QDir::toNativeSeparators(dir.path() + '/' + (*f));
        QFileInfo fi(filePath);
        if (fi.isFile() || fi.isSymLink())
        {
            QFile::setPermissions(filePath, QFile::WriteOwner);
            if (!QFile::remove(filePath))
            {
                qDebug() << "Global::deleteDir 1" << filePath << "faild";
                error = false;
            }
        }
        else if (fi.isDir())
        {
            if (!removeDir(filePath))
            {
                qDebug() << "Global::deleteDir 2" << filePath << "faild";
                error = false;
            }
        }
    }

    if (!dir.rmdir(QDir::toNativeSeparators(dir.path())))
    {
        qDebug() << dir.path();
        qDebug() << "Global::deleteDir 3" << dir.path() << "faild";
        error = false;
    }

    return error;
}

bool CopyFileThread::isCorrectSuffix(QString fileName)
{
    bool state = false;
    if ( fileName.endsWith("state") ||  fileName.endsWith("STATE"))
    {
        state = true;
    }
    else if ( fileName.endsWith("trace") ||  fileName.endsWith("TRACE"))
    {
        state = true;
    }
    else if ( fileName.endsWith("csv") ||  fileName.endsWith("CSV"))
    {
        state = true;
    }
    else if ( fileName.endsWith("png") ||  fileName.endsWith("PNG"))
    {
        state = true;
    }
    else if ( fileName.endsWith("jpg") ||  fileName.endsWith("JPG"))
    {
        state = true;
    }
    else if ( fileName.endsWith("dat") ||  fileName.endsWith("DAT"))
    {
        state = true;
    }
    else if ( fileName.endsWith("meas") ||  fileName.endsWith("MEAS"))
    {
        state = true;
    }

    return state;
}
