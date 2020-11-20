#ifndef PLTDISTHREAD_H
#define PLTDISTHREAD_H

#include <QObject>
#include <QThread>

class pltdisthread : public QThread
{
  Q_OBJECT
public:
  pltdisthread();
  qint32 pltdism;
  qint32 grunflag;
private:
    void run();
signals:
    qint32 sigpltdis(qint32 imod);
};

#endif // PLTDISTHREAD_H
