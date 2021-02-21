function testtcpclient

socat_binary = file_in_path (getenv ("PATH"), "socat");
if isempty(socat_binary)
  error ("No socat binary found")
endif

ip="127.0.0.1";
port=8000;
echostr="echotest\n";

timeout=1000; % ms
tol=0.1;                 % 10 percent tolerance

% test error
try
  fd=tcpclient(ip,port);
catch
  printf("couldnt connect to port %d - expected\n", port)
end_try_catch

% test connect, write and read
system ("killall socat 2>/dev/null; socat PIPE TCP4-LISTEN:8000 &",0);
pause(1);

fd=tcpclient(ip,port, 'Timeout', 1.0);

flush(fd);

% test read timeout1
start=tic;
result = read(fd,10000);
timeout1 = double(tic - start)/1000
testresult1 = tol > abs(1 - timeout1/timeout);

% write to socat
write(fd,echostr);

% read 4 chars, no timeout
start=tic;
result = read(fd,4);
timeout2 = double(tic - start)/1000;
testresult2 = timeout2 < timeout;

% check read result
result = char(result);
testresult3 = strcmp(echostr(1:4),result);

flush(fd);

set(fd, 'Timeout', .5);
start=tic;
result4 = read(fd,4);
timeout4 = toc(start)*1000;
testresult4 = tol > abs(1 - timeout4/500);

fd.timeout = 2;
start=tic;
result5 = read(fd,4);
timeout5 = toc(start)*1000;
testresult5 = tol > abs(1 - timeout5/2000);


% close tcp
clear fd

%system ("killall socat");


%
printf("timeout test 1:   %d (%f)\n",testresult1,timeout1);
printf("timeout test 2:   %d (%f)\n",testresult2,timeout2);
printf("timeout test 3:   %d\n",testresult3);
printf("timeout test 4:   %d (%f)\n",testresult4,timeout4);
printf("timeout test 5:   %d (%f)\n",testresult5,timeout5);

