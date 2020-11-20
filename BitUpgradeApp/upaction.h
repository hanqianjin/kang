#ifndef UPACTION_H
#define UPACTION_H
#include <QThread>

typedef struct updatep
{
  qint32 itype;//File Folder:0\nFile:1\nExtension:2
  char name[64];
}UPDATEPRO,*PUPDATEPRO;
typedef struct uppro
{
  qint32 isum;
  char swver[64];
  char hwver[64];
  char update[64];
}UPPRO,*PUPPRO;

typedef struct Devel
{
  qint32 qsoci;
  qint32 secifatten;
  char swver[64];
  char hwver[64];
  char update[64];
}DEVEMSG,*PDEVEMSG;

class upaction : public QThread
{
  Q_OBJECT
public:
  upaction();
  ~upaction();
  qint32 mflag;
  qint32 sendflag;//1means send sig

  qint32 sumitem;
  PUPDATEPRO puplist;
  DEVEMSG pltdevelopmsg;
  UPPRO upproperty;
  qint32 SaveDevelopMsg();
  void Ganba(PUPDATEPRO pmsg);
private:
  void run();
  qint32 loaddata();
signals:
  void Upgradesig();
  void UpGradeStage(qint32 istage);
};

#endif // UPACTION_H
