#ifndef LOCALCOMMUNICATE_H
#define LOCALCOMMUNICATE_H

#include <QLocalSocket>
#include <QByteArray>
#include <QDataStream>

#include "type.h"

#define LOCALSERVER "IPCServer"
#define TIMEOUT 30000   //超时时间，原来10000，现在修改为15000

typedef struct ModeChange_Type {
    quint32 magicHead;
    quint32 cmdType;
    quint32 dataLen;
    quint32 remoteOnOff;
    quint32 magicEnd;
}ModeChange;

class LocalCommunicate : public QLocalSocket
{
    Q_OBJECT
public:
    static LocalCommunicate *instance();
    bool changeMode(ScpiMode mode);

private:
    explicit LocalCommunicate(QObject *parent = 0);

signals:

public slots:
};

#endif // LOCALCOMMUNICATE_H
