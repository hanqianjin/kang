#include "peakfunc.h"

/**
 * @brief search the max Amplitude
 * @return Max Amplitude
 */
qreal searchMaxAmplitude(user_variable *globalUserVariable)
{
    qreal AMax = globalUserVariable->gOriginalMeasureVal[0];
    for (int k = 1; k < globalUserVariable->gSweepTracePoint; k++) {
        if (AMax < globalUserVariable->gOriginalMeasureVal[k]) {
            AMax = globalUserVariable->gOriginalMeasureVal[k];
          }
      }
    return AMax;
}
/**
 * @brief search the Min Amplitude
 * @return Min Amplitude
 */
qreal searchMinAmplitude(user_variable *globalUserVariable)
{
    qreal AMin = globalUserVariable->gOriginalMeasureVal[0];
    for (int k = 1; k < globalUserVariable->gSweepTracePoint; k++) {
        if (AMin > globalUserVariable->gOriginalMeasureVal[k]) {
            AMin = globalUserVariable->gOriginalMeasureVal[k];
          }
      }
    return AMin;
}
