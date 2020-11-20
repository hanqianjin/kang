#ifndef BITVNC_DATAHANDLING_H
#define BITVNC_DATAHANDLING_H

#include <QObject>

class bitvnc_DataHandling : public QObject
{
    Q_OBJECT
public:
    explicit bitvnc_DataHandling(QObject *parent = 0);
    QByteArray pReadDate;
    qint32     pReadPos;
    void readOneInfo(QByteArray *pData);
    void readData(QByteArray pData);
signals:

public slots:
};

#endif // BITVNC_DATAHANDLING_H
