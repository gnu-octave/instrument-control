## Copyright (C) 2019 John D <john.donoghue@ieee.org>
##
## This program is free software; you can redistribute it and/or modify it under
## the terms of the GNU General Public License as published by the Free Software
## Foundation; either version 3 of the License, or (at your option) any later
## version.
##
## This program is distributed in the hope that it will be useful, but WITHOUT
## ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
## FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
## details.
##
## You should have received a copy of the GNU General Public License along with
## this program; if not, see <http://www.gnu.org/licenses/>.

## -*- texinfo -*-
## @deftypefn {Function File} {@var{struct} = } get (@var{serial})
## @deftypefnx {Function File} {@var{field} = } get (@var{serial}, @var{property})
## Get the properties of serialport object.
##
## @subsubheading Inputs
## @var{serial} - instance of @var{octave_serialport} class.@*
## @var{property} - name of property.@*
##
## @subsubheading Outputs
## When @var{property} was specified, return the value of that property.@*
## otherwise return the values of all properties as a structure.@*
##
## @seealso{@@octave_serial/set}
## @end deftypefn

function retval = get (serial, property)

%{
s = 

Serialport with properties

                 Port: "COM4"
             BaudRate: 9600
    NumBytesAvailable: 0
      NumBytesWritten: 0

Show all properties

                      Port: "COM4"
                  BaudRate: 9600
         NumBytesAvailable: 0
           NumBytesWritten: 0

                 ByteOrder: "little-endian"
                  DataBits: 8
                  StopBits: 1
                    Parity: "none"
               FlowControl: "none"
                   Timeout: 10
                Terminator: "LF"

     BytesAvailableFcnMode: "off"
    BytesAvailableFcnCount: 64
         BytesAvailableFcn: []

          ErrorOccurredFcn: []
                  UserData: []

###
as.NumBytesAvailable
no status any more ?

currently we have:
  scalar structure containing the fields:

    name = Serial-/dev/ttyS0
    type = serial
    status = open
    baudrate =  600
    datasize =  8
    parity = None
    stopbits =  1
    timeout = -1
    requesttosend = on
    dataterminalready = on
    pinstatus =

      scalar structure containing the fields:

        CarrierDetect = off
        ClearToSend = off
        DataSetReady = off
        RingIndicator = off

    bytesavailable = 0
    port = /dev/ttyS0
%}

  properties = {'port', 'baudrate', 'numbytesavailable', 'numbyteswritten', ...
		'byteorder', 'databits', 'stopbits', 'parity', 'flowcontrol', ...
		'timeout', 'terminator', 'userdata'};

  if (nargin == 1)
    property = properties;
  elseif (nargin > 2)
    # TODO: multi properties ?
    error ("Too many arguments.\n");
  end

  if !iscell (property)
    property = {property};
  end
  property = tolower(property);

  valid     = ismember (property, properties);
  not_found = {property{!valid}};

  if !isempty (not_found)
    msg = @(x) error("serialport:get:InvalidArgument", ...
                     "Unknown property '%s'.\n",x);
    cellfun (msg, not_found);
  end

  property = {property{valid}};
  func     = @(x) __srlp_properties__ (serial, x);
  retval   = cellfun (func, property, 'UniformOutput', false);

  if numel(property) == 1
    retval = retval{1};
  elseif (nargin == 1)
    retval = cell2struct (retval',properties);
  end

end
