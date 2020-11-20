cross=arm-linux-gnueabihf-
cc=$(cross)gcc
midobj=RtsaCalcMain.o DiIoCtrl.o MainBoardVirtualDriver.o RfVirtualDriver.o DigSigDealVirtualDriver.o CalcPointAlog.o dpxMem.o DpxContrl.o sweepinterupt.o msgNoticeCode.o
SaCalcAnaApp:$(midobj) $(secobj)
	$(cc) -o RtsaCalcAnaApp $(midobj) -lm -lpthread -lrt
$(midobj):DiIoCtrl.h BitVisaType.h
mainh=SaDataStruct.h MainBoardVirtualDriver.h RfVirtualDriver.h DigSigDealVirtualDriver.h dpxMem.h DpxContrl.h msgNoticeCode.h
RtsaCalcMain.o:RtsaCalcMain.c $(mainh)
	$(cc) -c RtsaCalcMain.c
DiIoCtrl.o:DiIoCtrl.c 
	$(cc) -c DiIoCtrl.c
MainBoardVirtualDriver.o:MainBoardVirtualDriver.c MainBoardVirtualDriver.h 
	$(cc) -c MainBoardVirtualDriver.c
RfVirtualDriver.o:RfVirtualDriver.c RfVirtualDriver.h 
	$(cc) -c RfVirtualDriver.c
DigSigDealVirtualDriver.o:DigSigDealVirtualDriver.c DigSigDealVirtualDriver.h 
	$(cc) -c DigSigDealVirtualDriver.c
CalcPointAlog.o:CalcPointAlog.c CalcPointAlog.h
	$(cc) -c CalcPointAlog.c
dpxMem.o:dpxMem.c dpxMem.h
	$(cc) -c dpxMem.c
DpxContrl.o:DpxContrl.c DpxContrl.h
	$(cc) -c DpxContrl.c
sweepinterupt.o:sweepinterupt.c sweepinterupt.h
	$(cc) -c sweepinterupt.c
msgNoticeCode.o:msgNoticeCode.c msgNoticeCode.h
	$(cc) -c msgNoticeCode.c
clean:
	rm RtsaCalcAnaApp $(midobj) 



