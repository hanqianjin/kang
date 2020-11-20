#ifndef LOADCTRLRUNPARAM_H
#define LOADCTRLRUNPARAM_H

#include <QObject>
#include <QVector>

class loadctrlrunparam : QObject
{
  Q_OBJECT

public:
  loadctrlrunparam();

private:
  QString sactrlpath;
  QString rtsactrlpath;
  QString ltefddctrlpath;
  QString ltetddctrlpath;
  QString fgnrctrlpath;

public:
  QVector<QString> pctrlpathvec;//!<must in enum RUNMODE order to add element

private:
  qint32 iniallmodectrlpath();
};

#endif // LOADCTRLRUNPARAM_H
