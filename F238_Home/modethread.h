#ifndef MODETHREAD_H
#define MODETHREAD_H

#include <QThread>
#include "runstateshm.h"

class modethread : public QThread
{
  Q_OBJECT
public:
  explicit modethread(QObject *parent = NULL); 

signals:
    void ShowSig();

public slots:
    void ExitThread();

private:
  void run();

private:
  int overflg;
  int runflg;//!<only once in structor
};

#endif // MODETHREAD_H
