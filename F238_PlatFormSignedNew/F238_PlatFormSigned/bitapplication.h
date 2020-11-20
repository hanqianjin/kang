#ifndef BITAPPLICATION_H
#define BITAPPLICATION_H
#include "QApplication"
#include "bitplatform.h"

class bitapplication:public QApplication
{
public:
  bitapplication(int &argc, char **argv);

  ~bitapplication();

  bool notify(QObject *receiver, QEvent *e);
  BitPlatForm *gplt;
};

#endif // BITAPPLICATION_H
