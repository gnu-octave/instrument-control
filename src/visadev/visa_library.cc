
#include <octave/oct.h>
#ifdef HAVE_CONFIG_H
#include "../config.h"
#endif

#include "visa_library.h"

#include <octave/oct-shlib.h>
#include "octave/file-ops.h"
#include "octave/file-stat.h"
#include "octave/oct-env.h"
//#include "octave/oct-sysdep.h"

static octave::dynamic_library visa_lib("");

visa_library::visa_library()
{
  tx = 0x0c;
  lib_viOpenDefaultRM = 0;

  // see if librrary is loaded
  octave::dynamic_library lib("");
  void * s = reinterpret_cast<void*>
                                 (lib.search ("viOpenDefaultRM"));
  if (!s)
    {
      std::string visa_library_path = octave::sys::env::getenv ("VISA_LIBRARY");
      if (visa_library_path.empty())
        {
          std::string paths = "";
          std::string sep = ":";
          string_vector lib_list;
#ifdef _WIN32
          paths = octave::sys::env::getenv ("PATH");
          sep = ";";
#ifdef _WIN64
          lib_list.append(std::string("visa64.dll"));
#endif
          lib_list.append(std::string("visa32.dll"));
          lib_list.append(std::string("visa.dll"));
          lib_list.append(std::string("libvisa.dll"));
#else
# ifdef __APPLE__
          paths = octave::sys::env::getenv ("DYLD_LIBRARY_PATH");
          lib_list.append(std::string("libvisa.dylib"));
# else
          paths = octave::sys::env::getenv ("LD_LIBRARY_PATH");
          lib_list.append(std::string("libvisa.so"));
# endif
#endif
          string_vector path_list;
          std::string path;
          std::istringstream pathStream(paths); // Using stringstream for convenience
          while (std::getline(pathStream, path, sep[0]))
            path_list.append(path);

#ifndef _WIN32
          path_list.append(std::string("/usr"));
          path_list.append(std::string("/usr/lib"));
          path_list.append(std::string("/usr/local/lib"));
#endif

          for (octave_idx_type p=0; p<path_list.numel(); p++) 
            {
              // can we find the vis lib
              for (octave_idx_type l=0;l<lib_list.numel();l++)
                {
                  path = path_list(p) + octave::sys::file_ops::dir_sep_str () + lib_list(l);

                  if (octave::sys::file_stat (path))
                    {
                      visa_library_path = path;
                      break;
                    }
                }

              if (!visa_library_path.empty()) break;
            }
        }

      lib = octave::dynamic_library (visa_library_path);

      void * s = reinterpret_cast<void*>
                                 (lib.search ("viOpenDefaultRM"));
      if(!s) 
        {
          // still not found
          return;
        }
      else
        {
          visa_lib = lib;
        }
    }
  // else - already loaded
  //
  // get each func pointer if can
  lib_viOpenDefaultRM = reinterpret_cast<ViStatus (*)(ViPSession)>(lib.search ("viOpenDefaultRM"));
  lib_viOpen = reinterpret_cast<ViStatus (*)(ViSession,ViRsrc,ViAccessMode,ViUInt32,ViPSession)>(lib.search ("viOpen"));
  lib_viClose = reinterpret_cast<ViStatus (*)(ViObject)>(lib.search ("viClose"));
  lib_viStatusDesc = reinterpret_cast<ViStatus (*)(ViObject,ViStatus,ViChar _VI_FAR [])>(lib.search ("viStatusDesc"));
  lib_viGetAttribute = reinterpret_cast<ViStatus (*)(ViObject,ViAttr,void _VI_PTR)>(lib.search ("viGetAttribute"));
  lib_viSetAttribute = reinterpret_cast<ViStatus (*)(ViObject,ViAttr,ViAttrState)>(lib.search ("viSetAttribute"));
  lib_viFindRsrc = reinterpret_cast<ViStatus (*)(ViSession,ViString,ViPFindList,ViPUInt32,ViChar _VI_FAR [])>(lib.search ("viFindRsrc"));
  lib_viFindNext = reinterpret_cast<ViStatus (*)(ViFindList,ViChar _VI_FAR [])>(lib.search ("viFindNext"));
  lib_viParseRsrc = reinterpret_cast<ViStatus (*)(ViSession,ViRsrc,ViPUInt16,ViPUInt16)>(lib.search ("viParseRsrc"));
  lib_viParseRsrcEx = reinterpret_cast<ViStatus (*)(ViSession,ViRsrc,ViPUInt16,ViPUInt16,ViChar _VI_FAR [], ViChar _VI_FAR [], ViChar _VI_FAR [])>(lib.search ("viParseRsrcEx"));
  lib_viRead = reinterpret_cast<ViStatus (*)(ViSession,ViPBuf,ViUInt32,ViPUInt32)>(lib.search ("viRead"));
  lib_viWrite = reinterpret_cast<ViStatus (*)(ViSession,ViPBuf,ViUInt32,ViPUInt32)>(lib.search ("viWrite"));
  lib_viClear = reinterpret_cast<ViStatus (*)(ViSession)>(lib.search ("viClear"));
  lib_viReadSTB = reinterpret_cast<ViStatus (*)(ViSession, ViPUInt16)>(lib.search ("viReadSTB"));
  lib_viFlush = reinterpret_cast<ViStatus (*)(ViSession, ViUInt16)>(lib.search ("viFlush"));
  lib_viAssertTrigger = reinterpret_cast<ViStatus (*)(ViSession, ViUInt16)>(lib.search ("viAssertTrigger"));
}

visa_library::~visa_library()
{
}

ViStatus visa_library::viOpenDefaultRM(ViPSession vi)
{
  if (!lib_viOpenDefaultRM)
    return VI_ERROR_LIBRARY_NFOUND;

  return lib_viOpenDefaultRM(vi);
}

ViStatus visa_library::viOpen(ViSession sesn, ViRsrc name, ViAccessMode mode, ViUInt32 timeout, ViPSession vi)
{
  if (!lib_viOpen)
    return VI_ERROR_LIBRARY_NFOUND;

  return lib_viOpen(sesn, name, mode, timeout, vi);
}

ViStatus visa_library::viClose(ViObject  vi)
{
  if (!lib_viClose)
    return VI_ERROR_LIBRARY_NFOUND;

  return lib_viClose(vi);
}

ViStatus visa_library::viStatusDesc(ViObject  vi, ViStatus status, ViChar _VI_FAR desc[])
{
  if (!lib_viStatusDesc)
  {
    sprintf((char*)desc, "%ld", (long)status);
    return VI_SUCCESS;
  }
  return visa_library::lib_viStatusDesc(vi, status, desc);
}

ViStatus visa_library::viGetAttribute(ViObject  vi, ViAttr attrName, void _VI_PTR attrValue)
{
  if (!lib_viGetAttribute)
    return VI_ERROR_LIBRARY_NFOUND;

  return lib_viGetAttribute(vi, attrName, attrValue);
}
ViStatus visa_library::viSetAttribute(ViObject  vi, ViAttr attrName, ViAttrState attrValue)
{
  if (!lib_viSetAttribute)
    return VI_ERROR_LIBRARY_NFOUND;

  return lib_viSetAttribute(vi, attrName, attrValue);
}
ViStatus visa_library::viFindRsrc(ViSession sesn, ViString expr, ViPFindList vi,
                                  ViPUInt32 retCnt, ViChar _VI_FAR desc[])
{
  if (!lib_viFindRsrc)
    return VI_ERROR_LIBRARY_NFOUND;

  return lib_viFindRsrc(sesn, expr, vi, retCnt, desc);
}
ViStatus visa_library::viFindNext(ViFindList vi, ViChar _VI_FAR desc[])
{
  if (!lib_viFindNext)
    return VI_ERROR_LIBRARY_NFOUND;

  return lib_viFindNext(vi, desc);
}
ViStatus  visa_library::viParseRsrc(ViSession rmSesn, ViRsrc rsrcName,
                      ViPUInt16 intfType, ViPUInt16 intfNum)
{
  if (!lib_viParseRsrc)
    return VI_ERROR_LIBRARY_NFOUND;

  return lib_viParseRsrc(rmSesn, rsrcName, intfType, intfNum);
}

ViStatus visa_library::viParseRsrcEx(ViSession rmSesn, ViRsrc rsrcName, ViPUInt16 intfType,
                       ViPUInt16 intfNum, ViChar _VI_FAR rsrcClass[],
                       ViChar _VI_FAR expandedUnaliasedName[],
                       ViChar _VI_FAR aliasIfExists[])
{
  if (!lib_viParseRsrcEx)
    {
      // fallback to viParseRsrc
      rsrcClass[0] = 0;
      expandedUnaliasedName[0] = 0;
      aliasIfExists[0] = 0;

      return this->viParseRsrc(rmSesn, rsrcName, intfType, intfNum);
    }
  return lib_viParseRsrcEx(rmSesn, rsrcName, intfType, intfNum, rsrcClass, expandedUnaliasedName, aliasIfExists);
}
ViStatus visa_library::viRead(ViSession  vi, ViPBuf buf, ViUInt32 cnt, ViPUInt32 retCnt)
{
  if (!lib_viRead)
    return VI_ERROR_LIBRARY_NFOUND;

  return lib_viRead(vi, buf, cnt, retCnt);
}
ViStatus visa_library::viWrite(ViSession  vi, ViBuf buf, ViUInt32 cnt, ViPUInt32 retCnt)
{
  if (!lib_viWrite)
    return VI_ERROR_LIBRARY_NFOUND;

  return lib_viWrite(vi, buf, cnt, retCnt);
}
ViStatus visa_library::viClear(ViSession  vi)
{
  if (!lib_viClear)
    return VI_ERROR_LIBRARY_NFOUND;

  return lib_viClear(vi);
}
ViStatus visa_library::viReadSTB(ViSession  vi, ViPUInt16 status)
{
  if (!lib_viReadSTB)
    return VI_ERROR_LIBRARY_NFOUND;

  return lib_viReadSTB(vi, status);
}
ViStatus visa_library::viFlush(ViSession vi, ViUInt16 mask)
{
  if (!lib_viFlush)
    return VI_ERROR_LIBRARY_NFOUND;

  return lib_viFlush(vi, mask);
}

ViStatus visa_library::viAssertTrigger(ViSession vi, ViUInt16 protocol)
{
  if (!lib_viAssertTrigger)
    return VI_ERROR_LIBRARY_NFOUND;

  return lib_viAssertTrigger(vi, protocol);
}

visa_library * get_visa_library()
{
  return new visa_library();
}

void free_visa_library(visa_library *l)
{
  if(l)
    {
      delete l;
    }
}
