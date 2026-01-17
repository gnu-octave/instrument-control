# Run through some quick binblock functionality using a udpport

function testbinblock
  printf("test binblock\n");
  a = udp ();
  a.remoteport = a.localport;
  a.remotehost = '127.0.0.1';
  a.timeout = 1;

  writebinblock(a, "hello", "char")
  assert(readbinblock(a), uint8("hello"));

  x = [1 2 3 4];
  writebinblock(a, x, "double")
  assert(readbinblock(a, "double"), x);

  # bigger blocks (prev was failing > 96)
  x = uint8(255*rand(1,4096));
  writebinblock(a, x, "uint8")
  y = readbinblock(a, "uint8");
  assert (y, x);

  # insert some noise before the data
  write(a, "invalidstuff");

  writebinblock(a, "hello", "char");
  assert(readbinblock(a), uint8("hello"));

  # format of a binblock
  writebinblock(a, "hello", "char");
  x = read(a);
  assert(char(x), "#15hello\n");

  writebinblock(a, "hello", "uint16");
  x = read(a);
  assert(char(x), "#210h\0e\0l\0l\0o\0\n");

  clear a
  printf("test completed\n");
endfunction
