#ifndef _BIT_DPXCONTROL_H
#define _BIT_DPXCONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DiIoCtrl.h" 
/*
purpose:ini the ctrl of Dpx
func:DpxEn
param:<in>devHandle:dev's ctrl handle from ini 
      <in>dpxOpenClose:open DPX or close DPX
return:>=0 is ok
*/
DiInt32 DpxEn(DiSession devHandle,DiInt32 dpxOpenClose);
/*
purpose:ini the ctrl of Dpx
func:DpxDisable
param:<in>devHandle:dev's ctrl handle from ini 
      <in>dpxOpenClose:open DPX or close DPX
return:>=0 is ok
*/
DiInt32 DpxDisable(DiSession devHandle);

/*
purpose:set the persistence of Dpx
func:DpxPersisteceMode
param:<in>devHandle:dev's ctrl handle from ini 
      <in>dpxPersisMode:dpx persistence mode
return:>=0 is ok
*/
//DiInt32 DpxPersisteceMode(DiSession devHandle,DiInt32 dpxPersisMode);

/*
purpose:set the clear contrl of Dpx
func:DpxBitmapCtrl
param:<in>devHandle:dev's ctrl handle from ini 
      <in>dpxClearCtrl:dpx clear mode
return:>=0 is ok
*/
//DiInt32 DpxBitmapCtrl(DiSession devHandle,DiInt32 dpxClearCtrl);

/*
purpose:set the extrac contrl of Dpx
func:DpxBitmapExact
param:<in>devHandle:dev's ctrl handle from ini 
      <in>dpxExtrac:dpx extrac mode
return:>=0 is ok
*/
//DiInt32 DpxBitmapExact(DiSession devHandle,DiInt32 dpxExtrac);

/*
purpose: bitmap atten step by persistence time and acquire time
func:DpxBitAttenStep
param:<in>devHandle:dev's ctrl handle from ini
      <in>persistenceTime:set the persistence time
      <in>acqTime:set the acquire time
	  user set
return:>=0 is ok
 */
//DiInt32 DpxBitAttenStep(DiSession devHandle,DiReal32 persistenceTime,DiReal32 acqTime);

/*
purpose: bitmap density step by maxDensity and minDensity
func:DpxBitDensityStep
param:<in>devHandle:dev's ctrl handle from ini
      <in>maxDensity:set the maxDensity
      <in>minDensity:set the minDensity
	  user set
return:>=0 is ok
 */
//DiInt32 DpxBitDensityStep(DiSession devHandle,DiReal32 maxDensity,DiReal32 minDensity);

/*
purpose: blue color step by maxDensity and minDensity
func:DpxBitDensityStep
param:<in>devHandle:dev's ctrl handle from ini
      <in>maxDensity:set the maxDensity
      <in>minDensity:set the minDensity
      <in>curve:set the curve
	  user set
return:>=0 is ok
 */
//DiInt32 DpxBlueColorStep(DiSession devHandle,DiReal32 maxDensity,DiReal32 minDensity,DiReal32 curve);

/*
purpose: green color step by maxDensity and minDensity
func:DpxGreenColorStep
param:<in>devHandle:dev's ctrl handle from ini
      <in>maxDensity:set the maxDensity
      <in>minDensity:set the minDensity
      <in>curve:set the curve
	  user set
return:>=0 is ok
 */
//DiInt32 DpxGreenColorStep(DiSession devHandle,DiReal32 maxDensity,DiReal32 minDensity,DiReal32 curve);

/*
purpose: red color step by maxDensity and minDensity
func:DpxRedColorStep
param:<in>devHandle:dev's ctrl handle from ini
      <in>maxDensity:set the maxDensity
      <in>minDensity:set the minDensity
      <in>curve:set the curve
	  user set
return:>=0 is ok
 */
//DiInt32 DpxRedColorStep(DiSession devHandle,DiReal32 maxDensity,DiReal32 minDensity,DiReal32 curve);

/*
purpose: reference amplitude 
func:DpxRefAmp
param:<in>devHandle:dev's ctrl handle from ini
      <in>refAmp:set the reference amplitude
      <in>refOffset:set the reference offset
	  user set
return:>=0 is ok
 */
//DiInt32 DpxRefAmp(DiSession devHandle,DiReal32 refAmp,DiReal32 refOffset);

/*
purpose: scale scope 
func:DpxScaleScope
param:<in>devHandle:dev's ctrl handle from ini
      <in>scaleScope:set the scale scope
	  scaleScope = 1/10*scale
return:>=0 is ok
 */
//DiInt32 DpxScaleScope(DiSession devHandle,DiReal32 scaleScope);

/*
purpose: the max counter 
func:DpxMaxCounter
param:<in>devHandle:dev's ctrl handle from ini
      <in>persistenceTime:set the persistence time
	  outPutToFpga = persistenceTime/clock
return:>=0 is ok
 */
//DiInt32 DpxMaxCounter(DiSession devHandle,DiReal32 persistenceTime,DiReal32 acqTime);

/*
purpose: the max density index
func:DpxMaxDensityIndex
param:<in>devHandle:dev's ctrl handle from ini
      <in>maxDensity:set the max density
      <in>minDensity:set the min density
return:>=0 is ok
 */
//DiInt32 DpxMaxDensityIndex(DiSession devHandle,DiReal32 maxDensity,DiReal32 minDensity);

/*
purpose: the min density index
func:DpxMinDensityIndex
param:<in>devHandle:dev's ctrl handle from ini
	  <in>maxDensity:set the max density
      <in>minDensity:set the min density
return:>=0 is ok
 */
//DiInt32 DpxMinDensityIndex(DiSession devHandle,DiReal32 maxDensity,DiReal32 minDensity);

/*
purpose: dpx persistence time 50ms/bits
func:DpxPersistenceTime
param:<in>devHandle:dev's ctrl handle from ini
	  <in>persistenceTime:set persistence time
return:>=0 is ok
 */
DiInt32 DpxPersistenceTime(DiSession devHandle,DiInt32 persistenceTime);
/*
purpose: dpx ampt axis min value
func:DpxAmptAxisMin
param:<in>devHandle:dev's ctrl handle from ini
	  <in>amptMin:set ampt min value
return:>=0 is ok
 */
DiInt32 DpxAmptAxisMin(DiSession devHandle,DiInt32 amptMin);
/*
purpose: dpx ampt axis zoom value
func:DpxAmptAxisZoom
param:<in>devHandle:dev's ctrl handle from ini
	  <in>amptZoom:set ampt zoom value
return:>=0 is ok
 */
DiInt32 DpxAmptAxisZoom(DiSession devHandle,DiInt32 amptZoom);
/*
purpose: dpx Probability Color Table
func:setHighestDpxColorTable
param:<in>devHandle:dev's ctrl handle from ini
	  <in>amptZoom:set ampt zoom value
return:>=0 is ok
 */
DiInt32 setHighestDpxColorTable(DiSession devHandle,DiInt32 colorFactor);
/*
purpose: dpx Probability Color Table
func:setLowestDpxColorTable
param:<in>devHandle:dev's ctrl handle from ini
	  <in>amptZoom:set ampt zoom value
return:>=0 is ok
 */
DiInt32 setLowestDpxColorTable(DiSession devHandle,DiInt32 colorFactor);
/*
purpose: dpx Probability Color Table
func:setLowestDpxColorTable
param:<in>devHandle:dev's ctrl handle from ini
	  <in>amptZoom:set ampt zoom value
return:>=0 is ok
 */
DiInt32 setDpxCurveColor(DiSession devHandle,DiReal32 colorFactor,DiInt32 lowest, DiInt32 Highest);
/*
purpose:get dpx color table
func:getDpxColorTable
param:<in>devHandle:dev's ctrl handle from ini 
return:>=0 is ok
*/
DiInt32 getDpxColorTable(DiSession devHandle);
/*
purpose:cal dpx curve color
func:CalCurveColor
param:
return:
*/
DiInt32 CalCurveColor(DiReal32 SrcColor, DiReal32 colorFactor, DiInt32 lowest, DiInt32 Highest);
/*
purpose:set dpx fmt table
func:setFmtData
param:<in>devHandle:dev's ctrl handle from ini 
return:>=0 is ok
*/
DiInt32 setFmtData(DiSession devHandle, DiPInt32 data);
/*
purpose:set dpx fmt table
func:setFmtData
param:<in>devHandle:dev's ctrl handle from ini 
return:>=0 is ok
*/
DiInt32 ConfigFmtReg(DiSession devHandle, DiInt32 type);
/*
purpose:set dpx fmt trigger criterion
func:setFmtData
param:<in>devHandle:dev's ctrl handle from ini 
return:>=0 is ok
*/
DiInt32 ConfigFmtTriggerCriterion(DiSession devHandle, DiInt32 type);


DiInt32 DpxTest(DiSession devHandle);

#ifdef __cplusplus
}
#endif

#endif
