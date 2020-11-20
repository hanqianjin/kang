#ifndef BVCOLORMANA_H
#define BVCOLORMANA_H
#include <QColor>

#include "bvmacrodef.h"
//typedef struct
//{
//    QColor defaultmode;
//    QColor outdoormode;
//    QColor nightmode;
//} _COLOR_STYLE;
typedef struct
{
    QColor Trace1;
    QColor Trace2;
    QColor Trace3;
    QColor Trace4;
    QColor Trace5;
    QColor Trace6;
    QColor Trace;
} _COLOR_TRACE;


static _COLOR_TRACE traceColor[MODETOTALCNT]=
{
    // defaultmode
    {QColor("#FFED00"),QColor("#00FF2F"),QColor("#0070FF"),QColor("#D587FF"),QColor("#27FFFC"),QColor("#FB4C70"),Qt::gray},
//    {Qt::yellow,Qt::blue,Qt::red,Qt::gray},
    // outdoormode
    {QColor("#000000"),QColor("#FF9F00"),QColor("#0070FF"),QColor("#FF9090"),QColor("#B479FF"),QColor("#FB4C70"),Qt::gray},
//    {Qt::blue,Qt::yellow,Qt::red,Qt::gray},
    // nightmode
//    {QColor("#00FF2F"),QColor("#FF9F00"),QColor("#0070FF"),QColor("#FF9090"),QColor("#B479FF"),QColor("#27FFFC"),Qt::gray},
    {QColor("#FFED00"),QColor("#00FF2F"),QColor("#0070FF"),QColor("#D587FF"),QColor("#27FFFC"),QColor("#FB4C70"),Qt::gray},
//    {Qt::red,Qt::blue,Qt::yellow,Qt::gray},
};

typedef struct
{
    QColor background;
    QColor leftPart;
    QColor topPart;
    QColor bottomPart;
    QColor gridPart;
    QColor curTraceIndex;  //for display trace index in spectrogram
    QColor colBarFont;
} _COLOR_PEN;

// defaultmode outdoormode nightmode
static _COLOR_PEN penColor[]=
{
    {Qt::black,Qt::white,Qt::white,Qt::white,Qt::darkGray,Qt::white,Qt::yellow},
    {QColor("#E0E0E0"),Qt::black,Qt::black,Qt::black,Qt::black,Qt::black,Qt::black},
    {Qt::black,QColor("#715631"),QColor("#978464"),QColor("#978464"),QColor("#645842"),QColor("#978464"),QColor("#978464")},
};

typedef struct
{
    QColor edgeArea;
    QColor boardLine;
    QColor curBoardLine;
} _COLOR_BOARD;
static _COLOR_BOARD boardColor[]=
{
    {Qt::gray,Qt::black,QColor("#F0B31D")},
    {Qt::black,QColor("#E0E6E3"),Qt::green},
    {Qt::blue,QColor("#E3A6A6"),Qt::red},
};

typedef struct
{
    QColor upperlimit;
    QColor lowerlimit;
    QColor uppermargin;
    QColor lowermargin;
    QColor limitTestFont;
} _COLOR_LIMIT;

static _COLOR_LIMIT limitColor[3]=
{
    // defaultmode
    {Qt::green,Qt::blue,Qt::darkRed,Qt::cyan,Qt::color0},
    // outdoormode
    {Qt::blue,Qt::blue,Qt::red,Qt::blue,Qt::color0},
    // nightmode
    {Qt::red,Qt::red,Qt::blue,Qt::red,Qt::color0}
};

typedef struct
{
    QColor curmarker;
    QColor defaultmarker;
    QColor markerBoard;
    QColor tableBoard;
} _COLOR_MARKER;
static _COLOR_MARKER markerColor[]=
{
    {QColor("#FF900E"),QColor("#FFFFF0"),Qt::white,QColor("#FF900E")},
    {QColor("#FF900E"),Qt::black,Qt::gray,QColor("#FF101E")},
    {QColor("#4DE427"),Qt::gray,Qt::blue,QColor("#FF900E")},
};

#endif // BVCOLORMANA_H
