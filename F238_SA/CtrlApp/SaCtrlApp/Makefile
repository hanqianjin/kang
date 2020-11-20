cross=arm-linux-gnueabihf-
cc=$(cross)gcc
midobj=main.o DiIoCtrl.o RfVirtualDriver.o SaAnalysis.o DigSigDealVirtualDriver.o CalcPointAlog.o sweepinterupt.o msgNoticeCode.o
secobj=ShmEngine.o MidMsg.o
SaAnaAppArm:$(midobj) $(secobj)
	$(cc) -o SaCtrlApp $(midobj) $(secobj) -lm -lpthread -lrt
$(midobj):DiIoCtrl.h BitVisaType.h
mainh=SaDataStruct.h RfVirtualDriver.h SaAnalysis.h ShmEngine.h MidMsg.h DigSigDealVirtualDriver.h
main.o:main.c $(mainh)
	$(cc) -c main.c
DiIoCtrl.o:DiIoCtrl.c 
	$(cc) -c DiIoCtrl.c
RfVirtualDriver.o:RfVirtualDriver.c RfVirtualDriver.h 
	$(cc) -c RfVirtualDriver.c 
SaAnalysis.o:SaAnalysis.c SaAnalysis.h SaDataStruct.h 
	$(cc) -c SaAnalysis.c 
ShmEngine.o:ShmEngine.c ShmEngine.h SaDataStruct.h BitVisaType.h
	$(cc) -c ShmEngine.c
MidMsg.o:MidMsg.c MidMsg.h SaDataStruct.h BitVisaType.h
	$(cc) -c MidMsg.c
DigSigDealVirtualDriver.o:DigSigDealVirtualDriver.c DigSigDealVirtualDriver.h 
	$(cc) -c DigSigDealVirtualDriver.c
CalcPointAlog.o:CalcPointAlog.c CalcPointAlog.h
	$(cc) -c CalcPointAlog.c
sweepinterupt.o:sweepinterupt.c sweepinterupt.h
	$(cc) -c sweepinterupt.c
msgNoticeCode.o:msgNoticeCode.c msgNoticeCode.h
	$(cc) -c msgNoticeCode.c
clean:
	rm SaCtrlApp $(midobj) $(secobj)
