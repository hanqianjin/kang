cross=arm-linux-gnueabihf-
cc=$(cross)gcc
midobj=SaCalcMain.o DiIoCtrl.o MainBoardVirtualDriver.o RfVirtualDriver.o DigSigDealVirtualDriver.o CalcPointAlog.o
SaCalcAnaApp:$(midobj) $(secobj)
	$(cc) -o SaCalcAnaApp $(midobj) -lm -lpthread -lrt
$(midobj):DiIoCtrl.h BitVisaType.h
mainh=SaDataStruct.h MainBoardVirtualDriver.h RfVirtualDriver.h DigSigDealVirtualDriver.h
SaCalcMain.o:SaCalcMain.c $(mainh)
	$(cc) -c SaCalcMain.c
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
clean:
	rm SaCalcAnaApp $(midobj) 
