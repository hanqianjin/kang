#ifndef REMOTEINTERFACE_H
#define REMOTEINTERFACE_H

#include "bitrtsa.h"
#include "bitsa.h"

class remoteinterface
{
public:
  remoteinterface();

private:
  static BitSA *premotesa;
  static BitRtSa *premotertsa;

public:
  static void SetRemoteSaHandle(BitSA *phandle);
  static void SetRemoteRtsaHandle(BitRtSa *phandle);

  static BitSA *getsaremotehandle();
  static BitRtSa *getrtsaremotehandle();
};

#endif // REMOTEINTERFACE_H
