OCT = serial.oct
OBJ := serial.o srl_baudrate.o srl_bytesize.o srl_flush.o srl_parity.o srl_stopbits.o srl_write.o srl_close.o srl_read.o

MKOCTFILE ?= mkoctfile

all: $(OCT)

%.oct: $(OBJ)
	$(MKOCTFILE) $^

%.o: %.cc
	$(MKOCTFILE) -c -s $<

clean:
	rm -f *.oct *.o

.PHONY: all clean
