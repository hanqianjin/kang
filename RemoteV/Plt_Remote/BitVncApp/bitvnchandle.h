#ifndef BITVNCHANDLE_H
#define BITVNCHANDLE_H

#include "bitplatform.h"
#include "bitvnc_internet.h"
#include "remoteinterface.h"

class sa_scpidef;
class comnution;
class BitPlatForm;
class bitvnc_internet;

class BitVncHandle
{
public:
    BitVncHandle();

    static void SetScpiHandle(sa_scpidef *Handle);
    static sa_scpidef *GetScpiHandle();

    static void SetCommuHandle(sa_scpidef *Handle);
    static sa_scpidef *GetCommuHandle();

    static void SetVncAppHandle(BitPlatForm *Handle);
    static BitPlatForm *GetVncAppHandle();

    static void SetVncInternetHandle(bitvnc_internet *Handle);
    static bitvnc_internet *GetVncInternetHandle();
private:
    static sa_scpidef *pHandleSa;
    static BitPlatForm *pBitApp;
    static bitvnc_internet *pCommuInter;
};

#endif // BITVNCHANDLE_H
