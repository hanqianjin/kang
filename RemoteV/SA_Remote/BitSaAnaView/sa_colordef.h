#ifndef SA_COLORDEF_H
#define SA_COLORDEF_H
#include <QColor>
#include "define.h"
#define SA_COLORMODE_CNT  3
#define SA_INDOOR_COLOR   0
#define SA_OUTDOOR_COLOR  1
#define SA_NIGHT_COLOR    2
#define SA_DEFAULT_COLOR  SA_INDOOR_COLOR

static QColor TraceColor[SA_COLORMODE_CNT][TRACE_CNT_TOTAL] =
{
    // SA_INDOOR_COLOR
    {QColor(255, 237, 0),QColor(0,255,47),QColor(0,112,255),QColor(213, 135, 255),QColor(39, 255, 252),QColor(255, 89, 172)},
    // SA_OUTDOOR_COLOR
    {QColor(255, 237, 0),QColor(0,255,47),QColor(0,112,255),QColor(213, 135, 255),QColor(39, 255, 252),QColor(255, 89, 172)},
    // SA_NIGHT_COLOR
    {QColor(255, 237, 0),QColor(0,255,47),QColor(0,112,255),QColor(213, 135, 255),QColor(39, 255, 252),QColor(255, 89, 172)},
};

static QColor TrOutLimitColor[SA_COLORMODE_CNT] =
{
    // SA_INDOOR_COLOR
    {Qt::gray,},
    // SA_OUTDOOR_COLOR
    {Qt::blue,},
    // SA_NIGHT_COLOR
    {Qt::white,},
};

static QColor EdgeColor[SA_COLORMODE_CNT][2] =
{
    /// SA_INDOOR_COLOR
    {QColor(250,174,2),Qt::cyan},
    /// SA_OUTDOOR_COLOR
    {QColor(210,214,2),QColor(120,124,2)},
    /// SA_NIGHT_COLOR
    {QColor(250,214,21),QColor(250,124,12)},
};

static QColor LimitColor[SA_COLORMODE_CNT][2] =   //UPPER = 1  LOWER = 2
{
    /// SA_INDOOR_COLOR
    {Qt::green,Qt::blue},
    /// SA_OUTDOOR_COLOR
    {QColor(250,214,21),QColor(250,124,12)},
    /// SA_NIGHT_COLOR
    {QColor(210,214,2),QColor(120,124,2)},
};

static QColor MarkerColor[SA_COLORMODE_CNT][2] =
{
    /// SA_INDOOR_COLOR
    {QColor("#FF900E"),QColor("#FFFFF0")},
    /// SA_OUTDOOR_COLOR
    {QColor(250,214,21),QColor(250,124,12)},
    /// SA_NIGHT_COLOR
    {QColor(210,214,2),QColor(120,124,2)},
};

static QColor infoFontColor[SA_COLORMODE_CNT] =
{
    // SA_INDOOR_COLOR
    {Qt::white,},
    // SA_OUTDOOR_COLOR
    {"#000000",},
    // SA_NIGHT_COLOR
    {"#978464",},
};

static QColor GridColor[SA_COLORMODE_CNT][2] =   //Outer frame and inner grid
{
    // SA_INDOOR_COLOR
    {Qt::white,Qt::darkGray},
    // SA_OUTDOOR_COLOR
    {"#000000","#666666",},
    // SA_NIGHT_COLOR
    {"#645842","#645842"},
};

static QColor ScaleColor[SA_COLORMODE_CNT] =
{
    // SA_INDOOR_COLOR
    {Qt::white,},
    // SA_OUTDOOR_COLOR
    {"#000000",},
    // SA_NIGHT_COLOR
    {"#715631",},
};

static QColor BackgroundColor[SA_COLORMODE_CNT] =
{
    // SA_INDOOR_COLOR
    {Qt::black,},
    // SA_OUTDOOR_COLOR
    {Qt::white,},
    // SA_NIGHT_COLOR
    {Qt::black,},
};

static QColor TableBackgroundColor[SA_COLORMODE_CNT] =
{
    // SA_INDOOR_COLOR
    {QColor(72,72,72),},
    // SA_OUTDOOR_COLOR
    {QColor(112,112,112),},
    // SA_NIGHT_COLOR
    {QColor(251,219,167),},
};

static QColor TableFontColor[SA_COLORMODE_CNT] =
{
    // SA_INDOOR_COLOR
    {Qt::white,},
    // SA_OUTDOOR_COLOR
    {Qt::white,},
    // SA_NIGHT_COLOR
    {Qt::black,},
};

static QColor TableCurFontColor[SA_COLORMODE_CNT] =
{
    // SA_INDOOR_COLOR
    {QColor(250,210,120),},
    // SA_OUTDOOR_COLOR
    {QColor(250,210,120),},
    // SA_NIGHT_COLOR
    {QColor(30,30,30),},
};

#endif // SA_COLORDEF_H
