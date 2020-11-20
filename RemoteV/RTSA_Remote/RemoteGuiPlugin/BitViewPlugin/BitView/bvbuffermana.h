#ifndef BVBUFFERMANA_H
#define BVBUFFERMANA_H

#include <QObject>
#include "bvmacrodef.h"
#include "bvcolormana.h"
#include <QPoint>
class buffermana : public QObject
{
  Q_OBJECT
public:
  explicit buffermana(QObject *parent = 0);

signals:

public slots:

public:
  qreal trace_ori[SUPPORTTRACEPOINT];
  qreal trace_render[SUPPORTTRACENUM][SUPPORTTRACEPOINT];
  qreal drawpointsY[SUPPORTTRACENUM][SUPPORTTRACEPOINT];
  qreal drawpointsX[SUPPORTTRACEPOINT];
  uint   gtracenum;

//! Albert 1024
qreal drawSpectroPointsSmallX[SUPPORTTRACEPOINT];
qreal drawSpectroPointsBigX[SUPPORTTRACEPOINT];

//Tony 1112
qreal gLimitLowerMarginDrawPoint[NOWTRACENUM];
qreal gLimitUpperMarginDrawPoint[NOWTRACENUM];

qreal gLimitLowerDrawPoint[NOWTRACENUM];
qreal gLimitUpperDrawPoint[NOWTRACENUM];

qreal gLimitDrawPoint[BIT_LIMIT_TOTAL_CNT][NOWTRACENUM];
qreal gLimitMarginDrawPoint[BIT_LIMIT_TOTAL_CNT][NOWTRACENUM];
};

#endif // BVBUFFERMANA_H
