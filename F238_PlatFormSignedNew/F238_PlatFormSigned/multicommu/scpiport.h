#ifndef SCPIPORT_H
#define SCPIPORT_H

#define MAX_FILE_SZIE 1024 * 1024

#include <QObject>
#include <QByteArray>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QSettings>
#include <QDebug>
#include "libscpi/inc/scpi/scpi.h"
#include "localcommunicate.h"

class ScpiPort_common :public QObject
{
    Q_OBJECT
public:
    explicit ScpiPort_common(QObject *parent = 0);
    void initTransFile(QString filename,int filelen);
    void transFile();
    qint32 transFileToRemote(QString srcFile, QString destFile);
    //从GUI端断开与SCPI连接,eg:用户按下LOCAL键
    virtual void lostConn()=0;
    //从SCPI端断开与GUI连接
    virtual void closeConn()=0;
signals:
    void sigLostConn();
protected:
    void clear();

public slots:
    void slotLostConn();
protected:
    QIODevice   *m_IoDevice;
    QByteArray  m_cmdBuffer;
    //真为SCPI模式,假为文件传输
    bool        m_modeScpi;
    QString     m_fileName;
    int         m_fileLen;
    int         m_byte_readed;
};

#endif // SCPIPORT_H
