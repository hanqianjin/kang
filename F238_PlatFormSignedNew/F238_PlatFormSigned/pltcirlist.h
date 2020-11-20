#ifndef PLTCIRLIST_H
#define PLTCIRLIST_H

#include <QObject>

typedef struct pltcirnode
{
  qint32 npflag;
  qint32 isource;
  qint32 index;
  struct pltcirnode* pnext;
  struct pltcirnode* plast;
}PLTCIRNODE,*PPLTCITNODE;

class pltcirlist
{  
public:
  pltcirlist(quint32 inum);
 ~pltcirlist();

  void InsertNodeValue(qint32 np,qint32 is,qint32 in);
  PPLTCITNODE GetNodeByStack(qint32 index);
  PPLTCITNODE GetNodeByQueue(qint32 index);
  void Clear();
  qint32 Capacity();
  qint32 Count();

private:
  qint32 count;
  qint32 capacity;
  PPLTCITNODE plastest;
  PPLTCITNODE ptemp;
};

#endif // PLTCIRLIST_H
