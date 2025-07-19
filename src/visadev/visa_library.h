#ifndef VISADEV_LIBRARY_H
#define VIDADEV_LIBRARY_H

#ifdef HAVE_VISA_H
# include <visa.h>
#else
# ifdef HAVE_VISA_VISA_H
#  include <visa/visa.h>
# endif
#endif



class visa_library
{
  int tx;
  // the functions we currently use - TODO: add all ?
  ViStatus _VI_FUNC (*lib_viOpenDefaultRM)(ViPSession vi); 
  ViStatus _VI_FUNC (*lib_viOpen)(ViSession sesn, ViRsrc name, ViAccessMode mode, ViUInt32 timeout, ViPSession vi);
  ViStatus _VI_FUNC (*lib_viClose)(ViObject  vi);
  ViStatus _VI_FUNC (*lib_viStatusDesc)(ViObject  vi, ViStatus status, ViChar _VI_FAR desc[]);
  ViStatus _VI_FUNC (*lib_viGetAttribute)(ViObject  vi, ViAttr attrName, void _VI_PTR attrValue);
  ViStatus _VI_FUNC (*lib_viSetAttribute)(ViObject  vi, ViAttr attrName, ViAttrState attrValue);
  ViStatus _VI_FUNC (*lib_viFindRsrc)(ViSession sesn, ViString expr, ViPFindList vi,
                                    ViPUInt32 retCnt, ViChar _VI_FAR desc[]);
  ViStatus _VI_FUNC (*lib_viFindNext)(ViFindList vi, ViChar _VI_FAR desc[]);
  ViStatus _VI_FUNC (*lib_viParseRsrc)(ViSession rmSesn, ViRsrc rsrcName,
                                    ViPUInt16 intfType, ViPUInt16 intfNum);
  ViStatus _VI_FUNC (*lib_viParseRsrcEx)(ViSession rmSesn, ViRsrc rsrcName, ViPUInt16 intfType,
                                    ViPUInt16 intfNum, ViChar _VI_FAR rsrcClass[],
                                    ViChar _VI_FAR expandedUnaliasedName[],
                                    ViChar _VI_FAR aliasIfExists[]);
  ViStatus _VI_FUNC (*lib_viRead)(ViSession  vi, ViPBuf buf, ViUInt32 cnt, ViPUInt32 retCnt);
  ViStatus _VI_FUNC (*lib_viWrite)(ViSession  vi, ViBuf buf, ViUInt32 cnt, ViPUInt32 retCnt); 
  ViStatus _VI_FUNC (*lib_viClear)(ViSession  vi);
  ViStatus _VI_FUNC (*lib_viReadSTB)(ViSession  vi, ViPUInt16 status);
  ViStatus _VI_FUNC (*lib_viFlush)(ViSession vi, ViUInt16 mask);
  ViStatus _VI_FUNC (*lib_viAssertTrigger)(ViSession vi, ViUInt16 protocol);

public:
  visa_library();
  virtual ~visa_library();

  bool is_valid() const
  {
      return lib_viOpenDefaultRM != 0;
  }

  ViStatus viOpenDefaultRM(ViPSession vi);
  ViStatus viOpen(ViSession sesn, ViRsrc name, ViAccessMode mode, ViUInt32 timeout, ViPSession vi);
  ViStatus viClose(ViObject  vi);
  ViStatus viStatusDesc(ViObject  vi, ViStatus status, ViChar _VI_FAR desc[]);
  ViStatus viGetAttribute(ViObject  vi, ViAttr attrName, void _VI_PTR attrValue);
  ViStatus viSetAttribute(ViObject  vi, ViAttr attrName, ViAttrState attrValue);
  ViStatus viFindRsrc(ViSession sesn, ViString expr, ViPFindList vi,
                                    ViPUInt32 retCnt, ViChar _VI_FAR desc[]);
  ViStatus viFindNext(ViFindList vi, ViChar _VI_FAR desc[]);
  ViStatus  viParseRsrc(ViSession rmSesn, ViRsrc rsrcName,
                        ViPUInt16 intfType, ViPUInt16 intfNum);
  ViStatus viParseRsrcEx(ViSession rmSesn, ViRsrc rsrcName, ViPUInt16 intfType,
                         ViPUInt16 intfNum, ViChar _VI_FAR rsrcClass[],
                         ViChar _VI_FAR expandedUnaliasedName[],
                         ViChar _VI_FAR aliasIfExists[]);
  ViStatus viRead(ViSession  vi, ViPBuf buf, ViUInt32 cnt, ViPUInt32 retCnt);
  ViStatus viWrite(ViSession  vi, ViBuf buf, ViUInt32 cnt, ViPUInt32 retCnt);
  ViStatus viClear(ViSession  vi);
  ViStatus viReadSTB(ViSession  vi, ViPUInt16 status);
  ViStatus viFlush(ViSession vi, ViUInt16 mask);
  ViStatus viAssertTrigger(ViSession vi, ViUInt16 protocol);
};


visa_library * get_visa_library();
void free_visa_library(visa_library *l);

#endif // VISADEV_LIBRARY_H
