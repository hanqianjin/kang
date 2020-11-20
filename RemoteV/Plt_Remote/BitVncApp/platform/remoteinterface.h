#ifndef REMOTEINTERFACE_H
#define REMOTEINTERFACE_H

#include "rtsaremote.h"
#include "bitsa.h"
#include "bitplatform.h"
#include "bitltefdd.h"
#include "bitltetdd.h"
#include "bitnr.h"

class remoteinterface
{
public:
  remoteinterface();

private:
  static BitSA *premotesa;
  static RtSaRemote *premotertsa;
  static quint32 *nowanamode;
  static BitPlatForm *premoteplatform;
  static BitLteFdd *premotefdd;
  static BitLteTdd *premotetdd;
  static BitNr *premotefgnr;

public:
  static void SetRemoteSaHandle(BitSA *phandle);
  static void SetRemoteRtsaHandle(RtSaRemote *phandle);
  static void SetAnaModeHandle(quint32 *panamode);
  static void SetPlatFormHandle(BitPlatForm *phandle);
  static void SetRemoteFddHandle(BitLteFdd *phandle);
  static void SetRemoteTddHandle(BitLteTdd *phandle);
  static void SetRemoteFgnrHandle(BitNr *phandle);

  static BitSA *getsaremotehandle();
  static RtSaRemote *getrtsaremotehandle();
  static quint32 getanamodehandle();
  static BitPlatForm *getplatformremotehandle();
  static BitLteFdd *getfddremotehandle();
  static BitLteTdd *gettddremotehandle();
  static BitNr *getfgnrremotehandle();
};

#endif // REMOTEINTERFACE_H
