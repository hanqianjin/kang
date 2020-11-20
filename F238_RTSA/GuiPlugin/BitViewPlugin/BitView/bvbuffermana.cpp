#include "bvbuffermana.h"

buffermana::buffermana(QObject *parent) : QObject(parent)
{
    gtracenum = 801;
    memset(drawpointsX,0,sizeof(drawpointsX));
    memset(drawSpectroPointsSmallX,0,sizeof(drawSpectroPointsSmallX));
    memset(drawSpectroPointsBigX,0,sizeof(drawSpectroPointsBigX));
    memset(gLimitLowerMarginDrawPoint,0,sizeof(gLimitLowerMarginDrawPoint));
    memset(gLimitUpperMarginDrawPoint,0,sizeof(gLimitUpperMarginDrawPoint));
    memset(gLimitLowerDrawPoint,0,sizeof(gLimitLowerDrawPoint));
    memset(gLimitUpperDrawPoint,0,sizeof(gLimitUpperDrawPoint));
    memset(gLimitDrawPoint,0,sizeof(gLimitDrawPoint));
    memset(gLimitMarginDrawPoint,0,sizeof(gLimitMarginDrawPoint));

    memset(trace_render,0,sizeof(qreal)*SUPPORTTRACENUM*SUPPORTTRACEPOINT);
    memset(drawpointsY,0,sizeof(qreal)*SUPPORTTRACENUM*SUPPORTTRACEPOINT);
    memset(trace_ori,0,sizeof(qreal)*SUPPORTTRACEPOINT);
}
