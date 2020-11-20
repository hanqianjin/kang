#ifndef BITVNC_INTERNET_H
#define BITVNC_INTERNET_H

#include <QThread>
#include <QObject>
#include <QMutex>
#include <QTcpSocket>
#include <QLocalServer>
#include <QLocalSocket>
#include "bitvnc_datahandling.h"
#include <QFile>

class bitvnc_internet:public QObject
{
    Q_OBJECT

public:
    ~bitvnc_internet();
    static bitvnc_internet* GetInstance();
    QTcpSocket* GetTcpSocket();
    QLocalServer* GetLocalServer();
    qint32 SetInternetConnect(QString pIP,qint32 pPort);
    qint32 SetInternetDisconnect();
    qint32 GetInternetStatus();

    //QByteArray   gOriginalMeasureVal[10];
    //qreal  gOriginalMeasureVal[10][801];
    qreal  gOriginalMeasureVal[6*801];
    QString state;//for scpi like "***?"
    qint32 dataComplete;
    qreal* getOriData();
    QByteArray tmpData;
protected slots:
    void tcp_socket_Read_Data();
    void tcp_socket_Disconnected();
    void slotAcceptConnection();
signals:
    void readData(QByteArray buffer);
    void ConnectStatus(qint32 pStatus);
    void fileReceive();
private:
    void TransFile(QByteArray buffer);
    bool isTransFile(QByteArray buffer);

    explicit bitvnc_internet(QObject *parent = 0);

    bitvnc_DataHandling *pDataHandle;
    qint32 pConnectStatus;
    static bitvnc_internet* m_pInstance;
    static QMutex m_Mutex;

    QTcpSocket *socket;
    QLocalServer *server;
    QLocalSocket *m_LocalSocketConnected;
    qint32 pStart,pEnd;
    qint32 transFileFlag; //0 -- no  1 -- transfer
    QString strFile;
    QString strFileSize;
    void saveOriData(QByteArray* buffer);
    void ProcessingData(QByteArray* buffer);
};

#endif // BITVNC_INTERNET_H
