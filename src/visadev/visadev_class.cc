// Copyright (C) 2025   John Donoghue   <john.donoghue@ieee.org>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.

#include <octave/oct.h>

#ifdef HAVE_CONFIG_H
#include "../config.h"
#endif

#ifdef BUILD_VISA
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

#include "visadev_class.h"
#include <octave/Matrix.h>

#include "visa_library.h"


static struct timeval
to_timeval(int ms)
{
  struct timeval tv;
  if(ms <= 0)
    {
      tv.tv_usec = 0;
      tv.tv_sec = 0;
    }
    else
    {
      tv.tv_usec = (ms % 1000) * 1000;
      tv.tv_sec = ms/1000;;
    }
  return tv;
}

static std::string visa_type_str(ViUInt16 type, const std::string &resource_name)
{
  std::string type_str;
  switch(type)
    {
      case VI_INTF_ASRL:
        type_str = "serial";
        break;
      case VI_INTF_GPIB:
        type_str = "gpib";
	break;
      case VI_INTF_VXI:
        type_str = "vxi";
	break;
      case VI_INTF_GPIB_VXI:
        type_str = "vxi";
	break;
      case VI_INTF_PXI:
        type_str = "pxi";
	break;
      case VI_INTF_TCPIP:
        type_str = "tcpip";
	if (resource_name.size() >= 8 && resource_name.substr(resource_name.size()-8, 8) == "::SOCKET")
	  {
            type_str = "socket";
          }
	break;
      case VI_INTF_USB:
        type_str = "usb";
	break;

      default:
        type_str = "unknown";
	  break;
  }
  return type_str;
}

static std::string GetStatusMessage(visa_library *lib, ViSession resource, ViStatus status)
{
  ViChar buffer[1024];
  if(lib->viStatusDesc(resource, status, buffer) == VI_SUCCESS)
    {
      return buffer;
    }
  else
    {
      sprintf((char*)buffer, "%ld", (long)status);
      return buffer;
    }
}

typedef octave_value (*CONVERT_FUNC)(const octave_value &);

struct PropertyMap
{
  const char * name;
  const char * mode;
  const char * type;
  uint32_t attr; 
  CONVERT_FUNC set; // called before calling set attribute
  CONVERT_FUNC get; // called after calling get attribute
};

static octave_value convert_nop(const octave_value &v)
{
  return v;
}

octave_value octave_visadev::get_attribute(const PropertyMap *p)
{
  octave_value retval = "x";
  ViStatus  status = VI_SUCCESS;
  std::string type = p->type ? p->type : "";
  if (type == "str")
    {
      ViChar buff[1024];
      buff[0] = 0;
      status = lib->viGetAttribute(instrument, p->attr, buff);
      retval = buff;
    }
  if (type == "u32")
    {
      ViUInt32 v = 0;
      status = lib->viGetAttribute(instrument, p->attr, &v);
      retval = octave_value(uint32_t(v));
    }
  if (type == "u16")
    {
      ViUInt16 v = 0;
      status = lib->viGetAttribute(instrument, p->attr, &v);
      retval = octave_value(uint16_t(v));
    }
  if (type == "i32")
    {
      ViInt32 v = 0;
      status = lib->viGetAttribute(instrument, p->attr, &v);
      retval = octave_value(uint32_t(v));
    }
  if (type == "i16")
    {
      ViInt16 v = 0;
      status = lib->viGetAttribute(instrument, p->attr, &v);
      retval = octave_value(uint16_t(v));
    }

  if (p->get)
    retval = p->get(retval);

  return retval;
}

bool octave_visadev::set_attribute(const PropertyMap *p, const octave_value &value)
{
  octave_value rhs = value;
  std::string type = p->type ? p->type : "";

  if (p->set)
    rhs = p->set(value);

  ViStatus  status;
  if (type == "str")
    {
      if (!rhs.is_string())
        {
          error ("Expected string for property '%s'", p->name);
          return false;
        }
      std::string value = rhs.string_value();
      status = lib->viSetAttribute(instrument, p->attr, (ViAttrState)value.c_str());
    }
  if (type == "u32")
    {
      if (!(rhs.OV_ISINTEGER () || rhs.OV_ISFLOAT ()))
        {
          error ("Expected numeric value for property '%s'", p->name);
          return false;
        }
      ViUInt32 v = rhs.ulong_value();
      status = lib->viSetAttribute(instrument, p->attr, (ViAttrState)v);
    }
  if (type == "u16")
    {
      if (!(rhs.OV_ISINTEGER () || rhs.OV_ISFLOAT ()))
        {
          error ("Expected numeric value for property '%s'", p->name);
          return false;
        }
      ViUInt16 v = rhs.ushort_value();
      status = lib->viSetAttribute(instrument, p->attr, (ViAttrState)v);
    }
  if (type == "i32")
    {
      if (!(rhs.OV_ISINTEGER () || rhs.OV_ISFLOAT ()))
        {
          error ("Expected numeric value for property '%s'", p->name);
          return false;
        }
      ViInt32 v = rhs.long_value();
      status = lib->viSetAttribute(instrument, p->attr, (ViAttrState)v);
    }
  if (type == "i16")
    {
      if (!(rhs.OV_ISINTEGER () || rhs.OV_ISFLOAT ()))
        {
          error ("Expected numeric value for property '%s'", p->name);
          return false;
        }
      ViInt16 v = rhs.ushort_value();
      status = lib->viSetAttribute(instrument, p->attr, (ViAttrState)v);
    }

  if (status != VI_SUCCESS)
    {
      std::string err = GetStatusMessage(lib, instrument, status);
      return false;
    }
  return true;
}

static struct PropertyMap def_field_map[] = {
  {"Type", "r", "u16", 0, convert_nop, convert_nop}, //VI_ATTR_INTF_TYPE}, // NOTE: takes other type field name ?
  {"ResourceName", "r", "str", 0, convert_nop, convert_nop}, //VI_ATTR_RSRC_NAME},
  {"Status", "r", "u16", 0, convert_nop, convert_nop},
  {"Timeout", "r", "float", 0, convert_nop, convert_nop},
  {"NumBytesAvailable", "r", "u32", 0, convert_nop, convert_nop},
  {"NumBytesWritten", "r", "u32", 0, convert_nop, convert_nop},
  {"ByteOrder", "rw", "str", 0, convert_nop, convert_nop},
  {"UserData", "rw", "obj", 0, convert_nop, convert_nop},
  {"Terminator", "r", "str", 0, convert_nop, convert_nop},
  {"Tag", "rw", "str", 0, convert_nop, convert_nop},

  // Alias
  // Vendor
  // Model
  // SerialNumber
  
  {NULL, "r", NULL, 0, convert_nop, convert_nop}
};

static octave_value oct_to_parity(const octave_value &v)
{
  // TODO: error on invalid ?
  std::string o = v.string_value();
  if (o == "odd")
    return octave_value((int)VI_ASRL_PAR_ODD);
  if (o == "even")
    return octave_value((int)VI_ASRL_PAR_EVEN);
  if (o == "mark")
    return octave_value((int)VI_ASRL_PAR_MARK);
  if (o == "space")
    return octave_value((int)VI_ASRL_PAR_SPACE);

  return octave_value((int)VI_ASRL_PAR_NONE);
}

static octave_value parity_to_oct(const octave_value &v)
{
  int o = v.int_value();
  switch(o)
    {
      case VI_ASRL_PAR_ODD:
        return "odd";
      case VI_ASRL_PAR_EVEN:
        return "event";
      case VI_ASRL_PAR_MARK:
        return "mark";
      case VI_ASRL_PAR_SPACE:
        return "space";
      default:
        break;
    }
  return "none";
}

static octave_value oct_to_flow(const octave_value &v)
{
  // TODO: error on invalid ?
  std::string o = v.string_value();
  if (o == "software")
    return octave_value((int)VI_ASRL_FLOW_XON_XOFF);
  if (o == "hardware")
    return octave_value((int)VI_ASRL_FLOW_RTS_CTS);
    //return octave_value((int)VI_ASRL_FLOW_DTR_DSR);
  if (o == "none")
    return octave_value((int)VI_ASRL_FLOW_NONE);

  return octave_value((int)VI_ASRL_FLOW_NONE);
}

static octave_value flow_to_oct(const octave_value &v)
{
  int o = v.int_value();
  switch(o)
    {
      case VI_ASRL_FLOW_XON_XOFF:
        return "software";
      case VI_ASRL_FLOW_RTS_CTS:
        return "hardware";
      case VI_ASRL_FLOW_DTR_DSR:
        return "hardware";
      default:
        break;
    }
  return "none";
}

static octave_value oct_to_stopbits(const octave_value &v)
{
  double o = v.double_value();
  // TODO: error on input of invalid ?
  // 1 = 10, 1.5 = 15, 2=20
  return octave_value((int)(o*10));
}

static octave_value stopbits_to_oct(const octave_value &v)
{
  double o = v.int_value();
  return octave_value(o/10.0);
}

static octave_value rsrc_to_port(const octave_value &v)
{
  // TODO: error on invalid ?
  std::string o = v.string_value();
  //ASRLX::.....
  size_t pos = o.find("::", 0);
  if(pos != std::string::npos)
    {
      o = o.substr(0, pos);
    }

  return octave_value(o);
}

static octave_value u16_as_hexstr(const octave_value &v)
{
  // TODO: error on invalid ?
  int u = v.ushort_value();
  char buff[32];
  sprintf(buff, "0x%04X", u);
  return octave_value(std::string(buff));
}

static struct PropertyMap serial_field_map[] = {
  // default / always there fields 
  {"Type", "r", "u16", 0, convert_nop, convert_nop}, //VI_ATTR_INTF_TYPE}, // NOTE: takes other type field name ?
  {"ResourceName", "r", "str", 0, convert_nop, convert_nop}, //VI_ATTR_RSRC_NAME},
  {"Status", "r", "u16", 0, convert_nop, convert_nop},
  {"Timeout", "rw", "float", 0, convert_nop, convert_nop},
  {"NumBytesAvailable", "r", "u32", VI_ATTR_ASRL_AVAIL_NUM, convert_nop, convert_nop},
  {"NumBytesWritten", "r", "u32", 0, convert_nop, convert_nop},
  {"ByteOrder", "rw", "str", 0, convert_nop, convert_nop},
  {"UserData", "rw", "obj", 0, convert_nop, convert_nop},
  {"Terminator", "r", "str", 0, convert_nop, convert_nop},
  {"Tag", "rw", "str", 0, convert_nop, convert_nop},

  {"Model", "r", "str", VI_ATTR_MODEL_NAME, convert_nop, convert_nop},
  {"Vendor", "r", "str", VI_ATTR_MANF_NAME, convert_nop, convert_nop},

  // Serial only
  {"Port", "r", "str", VI_ATTR_RSRC_NAME, convert_nop, rsrc_to_port}, // need get before the XXX
  {"Baud" ,"rw", "u32", VI_ATTR_ASRL_BAUD, convert_nop, convert_nop},
  {"DataBits", "rw", "u16", VI_ATTR_ASRL_DATA_BITS, convert_nop, convert_nop},
  {"Parity", "rw", "u16", VI_ATTR_ASRL_PARITY, oct_to_parity, parity_to_oct},
  {"StopBits", "rw", "u16", VI_ATTR_ASRL_STOP_BITS, oct_to_stopbits, stopbits_to_oct},
  {"FlowControl", "rw", "u16", VI_ATTR_ASRL_FLOW_CNTRL, oct_to_flow, flow_to_oct},
  
  // null terminate
  {NULL, "r", NULL, 0, NULL, NULL}
};

static struct PropertyMap tcp_field_map[] = {
  // default / always there fields 
  {"Type", "r", "u16", 0, convert_nop, convert_nop}, //VI_ATTR_INTF_TYPE}, // NOTE: takes other type field name ?
  {"ResourceName", "r", "str", 0, convert_nop, convert_nop}, //VI_ATTR_RSRC_NAME},
  {"Status", "r", "u16", 0, convert_nop, convert_nop},
  {"Timeout", "rw", "float", 0, convert_nop, convert_nop},
  {"NumBytesAvailable", "r", "u32", 0, convert_nop, convert_nop},
  {"NumBytesWritten", "r", "u32", 0, convert_nop, convert_nop},
  {"ByteOrder", "rw", "str", 0, convert_nop, convert_nop},
  {"UserData", "rw", "obj", 0, convert_nop, convert_nop},
  {"Terminator", "r", "str", 0, convert_nop, convert_nop},
  {"Tag", "rw", "str", 0, convert_nop, convert_nop},

  {"Model", "r", "str", VI_ATTR_MODEL_NAME, convert_nop, convert_nop},
  {"Vendor", "r", "str", VI_ATTR_MANF_NAME, convert_nop, convert_nop},

  // TCP only
  {"LANName", "r", "str", VI_ATTR_TCPIP_HOSTNAME, convert_nop, convert_nop},
  {"InstrumentAddress", "r", "str", VI_ATTR_TCPIP_ADDR, convert_nop, convert_nop},
  {"BoardIndex", "r", "u16", VI_ATTR_INTF_NUM, convert_nop, convert_nop},
  
  // null terminate
  {NULL, "r", NULL, 0, convert_nop, convert_nop}
};

static struct PropertyMap socket_field_map[] = {
  // default / always there fields 
  {"Type", "r", "u16", 0, convert_nop, convert_nop}, //VI_ATTR_INTF_TYPE}, // NOTE: takes other type field name ?
  {"ResourceName", "r", "str", 0, convert_nop, convert_nop}, //VI_ATTR_RSRC_NAME},
  {"Status", "r", "u16", 0, convert_nop, convert_nop},
  {"Timeout", "rw", "float", 0, convert_nop, convert_nop},
  {"NumBytesAvailable", "r", "u32", 0, convert_nop, convert_nop}, //VI_ATTR_ASRL_AVAIL_NUM},
  {"NumBytesWritten", "r", "u32", 0, convert_nop, convert_nop},
  {"ByteOrder", "rw", "str", 0, convert_nop, convert_nop},
  {"UserData", "rw", "obj", 0, convert_nop, convert_nop},
  {"Terminator", "r", "str", 0, convert_nop, convert_nop},
  {"Tag", "rw", "str", 0, convert_nop, convert_nop},

  {"Model", "r", "str", VI_ATTR_MODEL_NAME, convert_nop, convert_nop},
  {"Vendor", "r", "str", VI_ATTR_MANF_NAME, convert_nop, convert_nop},

  // socket only
  {"Port", "r", "u16", VI_ATTR_TCPIP_PORT, convert_nop, convert_nop},
  {"IPAddress", "r", "str", VI_ATTR_TCPIP_ADDR, convert_nop, convert_nop},
  
  // null terminate
  {NULL, "r", NULL, 0, convert_nop, convert_nop}
};

static struct PropertyMap usb_field_map[] = {
  // default / always there fields 
  {"Type", "r", "u16", 0, convert_nop, convert_nop}, //VI_ATTR_INTF_TYPE}, // NOTE: takes other type field name ?
  {"ResourceName", "r", "str", 0, convert_nop, convert_nop}, //VI_ATTR_RSRC_NAME},
  {"Status", "r", "u16", 0, convert_nop, convert_nop},
  {"Timeout", "rw", "float", 0, convert_nop, convert_nop},
  {"NumBytesAvailable", "r", "u32", 0, convert_nop, convert_nop}, //VI_ATTR_ASRL_AVAIL_NUM},
  {"NumBytesWritten", "r", "u32", 0, convert_nop, convert_nop},
  {"ByteOrder", "rw", "str", 0, convert_nop, convert_nop},
  {"UserData", "rw", "obj", 0, convert_nop, convert_nop},
  {"Terminator", "r", "str", 0, convert_nop, convert_nop},
  {"Tag", "rw", "str", 0, convert_nop, convert_nop},

  {"Model", "r", "str", VI_ATTR_MODEL_NAME, convert_nop, convert_nop},
  {"Vendor", "r", "str", VI_ATTR_MANF_NAME, convert_nop, convert_nop},

  // usb only
  {"SerialNumber", "r", "u16", VI_ATTR_USB_SERIAL_NUM, convert_nop, u16_as_hexstr},
  {"VendorID", "r", "u16", VI_ATTR_MANF_ID, convert_nop, u16_as_hexstr},
  {"ProductID", "r", "u16", VI_ATTR_MODEL_CODE, convert_nop, u16_as_hexstr},
  {"BoardIndex", "r", "u16", VI_ATTR_INTF_NUM, convert_nop, convert_nop},
  {"InterfaceIndex", "r", "u16", VI_ATTR_USB_INTFC_NUM, convert_nop, convert_nop},
  
  // null terminate
  {NULL, "r", NULL, 0, convert_nop, convert_nop}
};

static struct PropertyMap gpib_field_map[] = {
  // default / always there fields 
  {"Type", "r", "u16", 0, convert_nop, convert_nop}, //VI_ATTR_INTF_TYPE}, // NOTE: takes other type field name ?
  {"ResourceName", "r", "str", 0, convert_nop, convert_nop}, //VI_ATTR_RSRC_NAME},
  {"Status", "r", "u16", 0, convert_nop, convert_nop},
  {"Timeout", "rw", "float", 0, convert_nop, convert_nop},
  {"NumBytesAvailable", "r", "u32", 0, convert_nop, convert_nop}, //VI_ATTR_ASRL_AVAIL_NUM},
  {"NumBytesWritten", "r", "u32", 0, convert_nop, convert_nop},
  {"ByteOrder", "rw", "str", 0, convert_nop, convert_nop},
  {"UserData", "rw", "obj", 0, convert_nop, convert_nop},
  {"Terminator", "r", "str", 0, convert_nop, convert_nop},
  {"Tag", "rw", "str", 0, convert_nop, convert_nop},

  {"Model", "r", "str", VI_ATTR_MODEL_NAME, convert_nop, convert_nop},
  {"Vendor", "r", "str", VI_ATTR_MANF_NAME, convert_nop, convert_nop},

  // gpib only
  {"BoardIndex", "r", "u16", VI_ATTR_INTF_NUM, convert_nop, convert_nop},
  {"PrimaryAddress", "r", "u16", VI_ATTR_GPIB_PRIMARY_ADDR, convert_nop, convert_nop},
  {"SecondaryAddress", "r", "u16", VI_ATTR_GPIB_SECONDARY_ADDR, convert_nop, convert_nop},

  {"EOIMode", "rw", "str", 0, convert_nop, convert_nop},
  
  // null terminate
  {NULL, "r", NULL, 0, convert_nop, convert_nop}
};

static struct PropertyMap pxi_field_map[] = {
  // default / always there fields 
  {"Type", "r", "u16", 0, convert_nop, convert_nop}, //VI_ATTR_INTF_TYPE}, // NOTE: takes other type field name ?
  {"ResourceName", "r", "str", 0, convert_nop, convert_nop}, //VI_ATTR_RSRC_NAME},
  {"Status", "r", "u16", 0, convert_nop, convert_nop},
  {"Timeout", "rw", "float", 0, convert_nop, convert_nop},
  {"NumBytesAvailable", "r", "u32", 0, convert_nop, convert_nop}, //VI_ATTR_ASRL_AVAIL_NUM},
  {"NumBytesWritten", "r", "u32", 0, convert_nop, convert_nop},
  {"ByteOrder", "rw", "str", 0, convert_nop, convert_nop},
  {"UserData", "rw", "obj", 0, convert_nop, convert_nop},
  {"Terminator", "r", "str", 0, convert_nop, convert_nop},
  {"Tag", "rw", "str", 0, convert_nop, convert_nop},

  {"Model", "r", "str", VI_ATTR_MODEL_NAME, convert_nop, convert_nop},
  {"Vendor", "r", "str", VI_ATTR_MANF_NAME, convert_nop, convert_nop},

  // pxi only
  {"Bus", "r", "u16", VI_ATTR_PXI_BUS_NUM, convert_nop, convert_nop},
  {"DeviceIndex", "r", "u16", VI_ATTR_PXI_DEV_NUM, convert_nop, convert_nop},
  {"FunctionIndex", "r", "u16", VI_ATTR_PXI_FUNC_NUM, convert_nop, convert_nop},
  {"ChassisIndex", "r", "i16", VI_ATTR_PXI_CHASSIS, convert_nop, convert_nop},
  {"Slot", "r", "u16", VI_ATTR_INTF_NUM, convert_nop, convert_nop},

  {"EOIMode", "rw", "str", 0, convert_nop, convert_nop},
  
  // null terminate
  {NULL, "r", NULL, 0, convert_nop, convert_nop}
};

static struct PropertyMap vxi_field_map[] = {
  // default / always there fields 
  {"Type", "r", "u16", 0, convert_nop, convert_nop}, //VI_ATTR_INTF_TYPE}, // NOTE: takes other type field name ?
  {"ResourceName", "r", "str", 0, convert_nop, convert_nop}, //VI_ATTR_RSRC_NAME},
  {"Status", "r", "u16", 0, convert_nop, convert_nop},
  {"Timeout", "rw", "float", 0, convert_nop, convert_nop},
  {"NumBytesAvailable", "r", "u32", 0, convert_nop, convert_nop}, //VI_ATTR_ASRL_AVAIL_NUM},
  {"NumBytesWritten", "r", "u32", 0, convert_nop, convert_nop},
  {"ByteOrder", "rw", "str", 0, convert_nop, convert_nop},
  {"UserData", "rw", "obj", 0, convert_nop, convert_nop},
  {"Terminator", "r", "str", 0, convert_nop, convert_nop},
  {"Tag", "rw", "str", 0, convert_nop, convert_nop},

  {"Model", "r", "str", VI_ATTR_MODEL_NAME, convert_nop, convert_nop},
  {"Vendor", "r", "str", VI_ATTR_MANF_NAME, convert_nop, convert_nop},

  // vxi only
  {"Slot", "r", "u16", VI_ATTR_INTF_NUM, convert_nop, convert_nop},
  {"LogicalAddress", "r", "u16", VI_ATTR_VXI_LA, convert_nop, convert_nop},

  {"EOIMode", "rw", "str", 0, convert_nop, convert_nop},
  
  // null terminate
  {NULL, "r", NULL, 0, convert_nop, convert_nop}
};


DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_visadev, "octave_visadev", "octave_visadev");

std::vector <visa_devinfo> octave_visadev::list_devices()
{
  std::vector <visa_devinfo> devices;

  visa_library * lib = get_visa_library();
  if (!lib || !lib->is_valid())
    {
      error("visadev: Could not open VISA library.");
      return devices;
    }

  ViAccessMode access_mode = VI_NULL;
  ViUInt32 timeout_ms      = 5000;

  // Communication buffer
  ViChar buffer[1000];
  //ViRsrc description[1024];
  ViChar description[1024];
  ViUInt32 io_bytes;

  // Get VISA resource manager
  ViSession resource_manager;
  ViStatus  status;
  status = lib->viOpenDefaultRM(&resource_manager);
  if (status < VI_SUCCESS) 
    {
      error("visadev: Could not open VISA resource manager.");
      return devices;
    }
  else
    {
      // if passed in true ?
      //viSetAttribute(resource_manager, VI_KTATTR_RETURN_ALL, VI_TRUE );
      //
      //strcpy((char*)buffer, "?*INSTR");
      strcpy((char*)buffer, "?*");

      ViFindList find_list;
      ViUInt32 ret_cnt;

      status = lib->viFindRsrc(resource_manager, buffer, &find_list, &ret_cnt, description); 
      if (status < VI_SUCCESS)
        {
          lib->viClose(resource_manager);
          return devices;
        }

      while (status >= VI_SUCCESS)
        {
          ViUInt16 intf_type, intf_num;
          ViChar class_name[100];
          ViChar alias_name[1024];
          ViChar unalias_name[2046];
          visa_devinfo d;

          d.name = description;
          d.alias = description;

          status = lib->viParseRsrcEx(resource_manager, description, &intf_type, &intf_num, class_name, unalias_name, alias_name);
          if (status >= VI_SUCCESS)
            {
              if (alias_name[0])
                d.alias = alias_name;

	      d.type = visa_type_str(intf_type, description);
            }
          devices.push_back(d);

          status = lib->viFindNext(find_list, description)  ;
        }

      lib->viClose(find_list);
      lib->viClose(resource_manager);
    }

  free_visa_library(lib);

  return devices;
}

octave_visadev::octave_visadev (void)
: buffer_len(0), instrument(VI_NULL), timeout(-1), name("")
{
  static bool type_registered = false;

  if (! type_registered)
    {
      type_registered = true;
      register_type ();
    }

  lib = 0; //get_visa_library();

  userData = Matrix ();
  byteswritten = 0;
  byteOrder = "little-endian";
  interminator = octave_value("lf");
  outterminator = octave_value("lf");
  eoimode = true;

  properties = def_field_map;
}

string_vector octave_visadev::map_keys(void) const
{
  int i = 0;
  string_vector keys;

  PropertyMap *p = &properties[i];
  do
    {
      keys.append(std::string(p->name));
      i++;
      p = &properties[i];
    }
  while(p != NULL && p->name != NULL);

  return keys;
}


const PropertyMap * octave_visadev::get_property(const std::string &name) const
{
  int i = 0;

  PropertyMap *p = &properties[i];
  do
    {
      if (name == p->name)
        return p;
      i++;
      p = &properties[i];
    }
  while(p != NULL && p->name != NULL);

  return NULL;
}

octave_value_list
octave_visadev::subsref (const std::string& type, const std::list<octave_value_list>& idx, int nargout)
{
  octave_value_list retval;
  int skip = 1;

  switch (type[0])
    {
    default:
      error ("octave_visadev object cannot be indexed with %c", type[0]);
      return retval;
    case '.':
      std::string property = (idx.front ()) (0).string_value ();
      const PropertyMap *p = get_property(property);
      if (!p && type.length () > 1 && type[1] == '(')
        {
          // calling a function as visadef.function_name ?
	  octave_value_list ovl (1);
          OV_COUNT++; 
          ovl(0) = octave_value (this);
          std::list<octave_value_list>::const_iterator it = idx.begin();
          ovl.append (*++it);

          retval = OCTAVE__FEVAL (property, ovl);

	  skip ++;
        }
      else if (!p)
        {
          error ("Unknown property '%s'", property.c_str());
          return retval;
        }
      else
        {
          if (p->attr > 0)
            {
              retval(0) = get_attribute(p);
            }
          // handle some properties we handle specifically
          else if (property == "ResourceName")
            {
              retval(0) = get_name();
            }
          else if (property == "Type")
            {
              retval(0) = get_type();
            }
          else if (property == "Timeout")
            {
              retval(0) = get_timeout();
            }
          else if (property == "Tag")
            {
              retval(0) = get_tag();
            }
          else if (property == "UserData")
            {
              retval(0) = get_userdata();
            }
          else if (property == "Terminator")
            {
              octave_value_list ovl;
              // inc ref count as assign this to octave_value
              OV_COUNT++; 
              ovl (0) = octave_value (this);
              ovl (1) = "terminator";
              retval = OCTAVE__FEVAL (std::string ("__visadev_dispatch__"), ovl, 1);
            }
          else if (property == "NumBytesWritten")
            {
              retval(0) = get_byteswritten();
            }
          else if (property == "NumBytesAvailable")
            {
              // note we only use this is we didnt have a visa dev attribute prior
              retval(0) = (int)0;
            }
          else if (property == "Status")
            {
              // NOTE: sshould this be a visa status or ours ?
              retval(0) = get_status();
            }
          else if (property == "EIOMode")
            {
              retval(0) = get_eoimode();
            }
          else if (property == "ByteOrder")
            {
              retval(0) = get_byteorder();
            }
          else
            {
              error ("Unhandled property '%s'", property.c_str());
              return retval;
            }
        }
        break;
    }

  if (idx.size () > 1 && type.length () > 1)
    retval = retval (0).next_subsref (nargout, type, idx, skip);

  return retval;
}

octave_value
octave_visadev::subsasgn (const std::string& type, const std::list<octave_value_list>& idx, const octave_value& rhs)
{
  octave_value retval;

  switch (type[0])
    {
    default:
      error ("octave_visadev object cannot be indexed with %c", type[0]);
      break;
    case '.':
      if (type.length () == 1)
        {
          std::string property = (idx.front ()) (0).string_value ();
          const PropertyMap* p = get_property(property);
          if (!p)
            {
              error ("Unknown property '%s'", property.c_str());
              return retval;
            }
          else
            {
              bool writable = false;
              const char *mode = p->mode;
              while (*mode != '\0')
                {
                  if (*mode == 'w') writable = true;
                  mode ++;
                }

              if (!writable)
                {
                  error ("Readonly property '%s'", property.c_str());
                  return retval;
                }
            }

          if (p->attr > 0)
            {
              set_attribute(p, rhs);

              OV_COUNT++;
              retval = octave_value (this);
            }
          else if (property == "Timeout")
            {
              if ( !(rhs.OV_ISINTEGER () || rhs.OV_ISFLOAT ()) )
                {
                  error ("Expected numeric value for property '%s'", property.c_str());
                }
              else 
	        {
                  set_timeout(rhs.double_value());
                  OV_COUNT++;
                  retval = octave_value (this);
                }
	    }
          else if (property == "UserData")
            {
              set_userdata (rhs);
              OV_COUNT++;
              retval = octave_value (this);
	    }
          else if (property == "ByteOrder")
            {
              if (!rhs.is_string())
	        {
                  error ("Expected string value for property '%s'", property.c_str());
                }
              else
	        {
                  set_byteorder(rhs.string_value());
                  OV_COUNT++;
                  retval = octave_value (this);
                }
            }
          else if (property == "Tag")
            {
              if (!rhs.is_string())
	        {
                  error ("Expected string value for property '%s'", property.c_str());
                }
              else
	        {
                  set_tag(rhs.string_value());
                  OV_COUNT++;
                  retval = octave_value (this);
                }
            }
	  else
	    {
              error ("Unhandled property '%s'", property.c_str());
	    }
        }
      else if (type.length () > 1 && type[1] == '.')
        {
          // pass along any further assignments
          octave_value_list u = subsref (type.substr (0, 1), idx, 1);
          if (u.length () > 0)
            {
              std::list<octave_value_list> next_idx (idx);
              next_idx.erase (next_idx.begin ());
              u (0).subsasgn(type.substr (1), next_idx, rhs);
              OV_COUNT++;
              retval = octave_value (this);
            } 
        }
      else
        {
          error ("octave_visadev invalid index");
        }

    }
  return retval;
}

int
octave_visadev::open (const std::string &resource)
{
  int sockerr;

  name = resource;

  if(!lib)
    {
      lib = get_visa_library();
      if (!lib || !lib->is_valid())
        {
          error("visadev: Could not open VISA library.");
          return -1;
        }
    }

  ViAccessMode access_mode = VI_NULL;
  ViUInt32 timeout_ms      = 5000;

  // Communication buffer
  const ViUInt32 buffer_size_B = 1000;
  ViChar buffer[1000];
  ViUInt32 io_bytes;

  // Get VISA resource manager
  ViSession resource_manager;
  ViStatus  status;
  status = lib->viOpenDefaultRM(&resource_manager);
  if (status < VI_SUCCESS) 
    {
      error("visadev: Could not open VISA resource manager.");
      return -1;
    }

  // Connect to instrument
  strcpy((char*)buffer, resource.c_str());
  status = lib->viOpen(resource_manager, buffer, access_mode, timeout_ms, &instrument);
  if (status < VI_SUCCESS || instrument == VI_NULL) 
    {
      std::string err = GetStatusMessage(lib, resource_manager, status);
      lib->viClose(resource_manager);
      error("visadev: Could not open VISA resource - '%s'", err.c_str());
      return -1;
    }
  buffer[0] = 0;
  status = lib->viGetAttribute(instrument, VI_ATTR_RSRC_NAME, buffer);
  if (status == VI_SUCCESS and buffer[0] != 0)
    name = buffer;

  buffer[0] = 0;
  status = lib->viGetAttribute(instrument, VI_ATTR_RSRC_CLASS, buffer);

  ViUInt16 type;
  status = lib->viGetAttribute(instrument, VI_ATTR_INTF_TYPE, &type);
  if (status < VI_SUCCESS)
    {
      std::string err = GetStatusMessage(lib, resource_manager, status);
      lib->viClose(instrument);
      lib->viClose(resource_manager);
      instrument =  VI_NULL;
      error("visadev: Could not open VISA resouce - '%s'", err.c_str());
      return -1;
    }

  switch(type)
    {
      case VI_INTF_ASRL:
        type_str = "serial";
        properties = serial_field_map;
        break;
      case VI_INTF_GPIB:
        type_str = "gpib";
        properties = gpib_field_map;
	break;
      case VI_INTF_VXI:
        type_str = "vxi";
        properties = vxi_field_map;
	break;
      case VI_INTF_GPIB_VXI:
        type_str = "vxi";
        properties = vxi_field_map;
	break;
      case VI_INTF_PXI:
        type_str = "pxi";
        properties = pxi_field_map;
	break;
      case VI_INTF_TCPIP:
        type_str = "tcpip";
        properties = tcp_field_map;
	if (name.size() >= 8 && name.substr(name.size()-8, 8) == "::SOCKET")
	  {
            type_str = "socket";
            properties = socket_field_map;
          }
	break;
      case VI_INTF_USB:
        type_str = "usb";
        properties = usb_field_map;
	break;

      default:
        type_str = "unknown";
	  break;
  }

  // Set timeout on instrument io
  lib->viSetAttribute(instrument, VI_ATTR_TMO_VALUE, timeout_ms);
  timeout = ((double)timeout_ms)/1000.0;

  return 1;
}

octave_visadev::~octave_visadev (void)
{
  close();

  if(lib)
    free_visa_library(lib);
}

void
octave_visadev::print (std::ostream& os, bool pr_as_read_syntax)
{
  print_raw (os, pr_as_read_syntax);
  newline (os);
}

void
octave_visadev::print (std::ostream& os, bool pr_as_read_syntax) const
{
  print_raw (os, pr_as_read_syntax);
  newline (os);
}

void
octave_visadev::print_raw (std::ostream& os, bool pr_as_read_syntax) const
{
  os << "  Visadev Object:";
  newline(os);
  os << " Resource Name: " << get_name (); 
  newline(os);
  os << "          Type: " << get_type (); 
  newline(os);
  os << "        Status: " << get_status ();
  newline(os);
}

int
octave_visadev::get_bytesavailable () const
{
  return 0;
}

int
octave_visadev::read (uint8_t *buf, unsigned int len)
{
  size_t bytes_read = 0;

  if (! is_open())
    {
      error ("visadev_read: Interface must be opened first...");
      return 0;
    }

  ViStatus  status;
  const ViUInt32 buffer_size_B = len;
  ViByte buffer[buffer_size_B+1];
  ViUInt32 io_bytes;

  status = lib->viRead(instrument, buffer, buffer_size_B, &io_bytes);
  if (status < VI_SUCCESS)
    {
      std::string err = GetStatusMessage(lib, instrument, status);
      error("visadev: Could not read - '%s'", err.c_str());
      return -1;
    }

  if (io_bytes > 0)
    {
      bytes_read = io_bytes;
      memcpy(&buf[0], buffer, bytes_read);
    }

  return bytes_read;
}

int
octave_visadev::write (const std::string &str)
{
  int len = str.length();
  return write((uint8_t*)str.c_str(), len);
}

int
octave_visadev::write (const uint8_t *buf, unsigned int len)
{
  if (! is_open())
    {
      error ("visadev_write: Interface must be opened first...");
      return 0;
    }

  ViStatus  status;
  ViUInt32 io_bytes;

  status = lib->viWrite(instrument, (ViBuf)buf, len, &io_bytes);
  if (status < VI_SUCCESS)
    {
      std::string err = GetStatusMessage(lib, instrument, status);
      error("visadev: Could not read - '%s'", err.c_str());
      return -1;
    }

  return io_bytes;
}

int
octave_visadev::set_timeout (double newtimeout)
{
  if (newtimeout < -1 )
    {
      error ("visadev_timeout: timeout value must be -1 or positive");
      return -1;
    }

  // convert seconds to ms

  ViUInt32 v;
  if(newtimeout < 0)
    v = VI_TMO_INFINITE;
  else if(newtimeout == 0)
    v = VI_TMO_IMMEDIATE;
  else
    v = ViUInt32(newtimeout * 1000UL);

  ViStatus  status;
  status = lib->viSetAttribute(instrument, VI_ATTR_TMO_VALUE, v);

  if (status == VI_SUCCESS)
    {
      timeout = newtimeout;

      return 1;
    }
  return 0;
}

bool
octave_visadev::is_open (void) const
{
  return instrument != VI_NULL;
}

std::string
octave_visadev::get_status (void) const
{
  if (! is_open ()) 
    {
      return "closed";
    }
  else
    {
      return "open";
    }
}

int
octave_visadev::close (void)
{
  int retval = -1;
  if (instrument != VI_NULL)
    {
      ViSession session_manager;
      lib->viGetAttribute(instrument, VI_ATTR_RM_SESSION, &session_manager);
      lib->viClose(instrument);
      lib->viClose(session_manager);
      instrument = VI_NULL;
    }

  if (buffer_len)
    {
      delete [] input_buffer;
      buffer_len = 0;
    }

  return retval;
}

int
octave_visadev::get_visa_status ()
{
  ViStatus  status;
  ViStatus v = 0;

  status = lib->viGetAttribute(instrument, VI_ATTR_STATUS, &v);

  return (int)v;
}

int
octave_visadev::trigger ()
{
  ViStatus  status = 0;
  ViUInt16 protocol = VI_TRIG_PROT_DEFAULT;

  status = lib->viAssertTrigger(instrument, protocol);

  if (status < VI_SUCCESS)
    {
      std::string err = GetStatusMessage(lib, instrument, status);
      error("visadev: Could not trigger - '%s'", err.c_str());
      return -1;
    }

  return 0;
}


int
octave_visadev::flush (int mode)
{
  int retval = 0;

  if (! is_open())
    {
      error ("visadev_flush: Interface must be opened first...");
      return 0;
    }

  ViStatus  status = 0;
  ViUInt16 mask = 0;

  if (mode & 1)
    {
      mask = mask | VI_WRITE_BUF_DISCARD;
      //status = lib->viFlush(instrument, mask);
    }

  if (mode & 2)
    {
      mask = mask | VI_READ_BUF_DISCARD;
      //status = lib->viFlush(instrument, mask);
    }

  status = lib->viFlush(instrument, mask);

  if (status < VI_SUCCESS)
    {
      std::string err = GetStatusMessage(lib, instrument, status);
      error("visadev: Could not flush - '%s'", err.c_str());
      return -1;
    }

  return retval;
}

int
octave_visadev::set_control_line(const std::string &line, bool on_off)
{
  ViStatus  status;
  ViUInt16 v = 0;
  uint32_t attr = 0;

  if (line == "CTS")
    attr = VI_ATTR_ASRL_CTS_STATE;
  else if (line == "RI")
    attr = VI_ATTR_ASRL_RI_STATE;
  else if (line == "DSR")
    attr = VI_ATTR_ASRL_DSR_STATE;
  else if (line == "DTR")
    attr = VI_ATTR_ASRL_DTR_STATE;
  else if (line == "RTS")
    attr = VI_ATTR_ASRL_RTS_STATE;
  else if (line == "CD")
    attr = VI_ATTR_ASRL_DCD_STATE;
  else
    {
      error ("octave_visadev invalid control line name");
      return -1;
    }

  if (on_off)
    v = VI_STATE_ASSERTED;
  else
    v = VI_STATE_UNASSERTED;

  status = lib->viSetAttribute(instrument, attr, v);

  return (int)v;
}

int
octave_visadev::get_control_line(const std::string &line)
{
  ViStatus  status;
  ViUInt16 v = 0;
  uint32_t attr = 0;

  if (line == "CTS")
    attr = VI_ATTR_ASRL_CTS_STATE;
  else if (line == "RI")
    attr = VI_ATTR_ASRL_RI_STATE;
  else if (line == "DSR")
    attr = VI_ATTR_ASRL_DSR_STATE;
  else if (line == "DTR")
    attr = VI_ATTR_ASRL_DTR_STATE;
  else if (line == "RTS")
    attr = VI_ATTR_ASRL_RTS_STATE;
  else if (line == "CD")
    attr = VI_ATTR_ASRL_DCD_STATE;
  else
    {
      error ("octave_visadev invalid control line name");
      return -1;
    }

  status = lib->viGetAttribute(instrument, attr, &v);

  return (int)v;
}

int
octave_visadev::set_byteorder(const std::string& neworder)
{
  std::string order = neworder;
  std::transform (order.begin (), order.end (), order.begin (), ::tolower);
  if (order == "big" || order == "big-endian")
    byteOrder = "big-endian";
  else if (order == "little" || order == "little-endian")
    byteOrder = "little-endian";
  else
    error ("octave_visadev invalid byteorder");

 return 1;
}

int
octave_visadev::set_input_terminator(const octave_value& t)
{
  if(t.is_string())
    {
      std::string term = t.string_value();
      std::transform (term.begin (), term.end (), term.begin (), ::tolower);
      if (term != "lf" && term != "cr" && term != "cr/lf")
        error ("octave_visadev invalid input terminator");
      else
        interminator = term;
    }
  else if(t.is_scalar_type())
    {
      int x = t.int_value();
      if(x < 0 || x > 255)
        {
          error ("octave_visadev invalid input terminator");
        }
      else
        {
          interminator = octave_value(x);
        }
    }
  else
    error ("octave_visadev invalid input terminator");

  return 1;
}

int
octave_visadev::set_output_terminator(const octave_value& t)
{
  if(t.is_string())
    {
      std::string term = t.string_value();
      std::transform (term.begin (), term.end (), term.begin (), ::tolower);
      if (term != "lf" && term != "cr" && term != "cr/lf")
        error ("octave_visadev invalid output terminator");
      else
        outterminator = term;
    }
  else if(t.is_scalar_type())
    {
      int x = t.int_value();
      if(x < 0 || x > 255)
        {
          error ("octave_visadev invalid output terminator");
        }
      else
        {
          outterminator = octave_value(x);
        }
    }
  else
    error ("octave_visadev invalid output terminator");

 return 1;
}

#endif
