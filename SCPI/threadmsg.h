#ifndef THREADMSG_H
#define THREADMSG_H

#include <QThread>
#include <sys/msg.h>

#define MSG_CONFIG_SCPI_UART    1
#define MSG_CONFIG_SCPI_USB       2
#define MSG_CONFIG_SCPI_GPIB     3

#define MAX_SIZE    4

typedef struct  process_msg_type{
    long int msg_type;
    int      data[2];
}process_msg;


class ThreadMsg : public QThread
{
    Q_OBJECT
public:
    explicit ThreadMsg(QObject *parent = 0);

signals:
    void sigRestartUart();
    void sigRestartGPIB();
    void sigRestartUSB();

protected:
    void run();

public slots:

private:
    process_msg m_recvMsg;
};


#endif // THREADMSG_H
