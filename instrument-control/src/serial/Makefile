OCT := serial.oct srl_baudrate.oct srl_timeout.oct srl_bytesize.oct srl_flush.oct \
	srl_parity.oct srl_stopbits.oct srl_write.oct srl_close.oct srl_read.oct
OBJ := serial_class.o

MKOCTFILE ?= mkoctfile

all: $(OBJ) $(OCT)

%.o: %.cc
	$(MKOCTFILE) -c $^

%.oct: %.o
	$(MKOCTFILE) $^ $(OBJ) -o ../$@

clean:
	rm -f *.oct *.o

distclean: clean

.PHONY: all clean
