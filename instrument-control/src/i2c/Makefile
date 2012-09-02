OCT := i2c.oct
OBJ := i2c.o i2c_close.o i2c_addr.o i2c_write.o i2c_read.o

MKOCTFILE ?= mkoctfile

all: $(OBJ)

oct: $(OCT)

%.oct: $(OBJ)
	$(MKOCTFILE) $^

%.o: %.cc
	$(MKOCTFILE) -c -s $<


clean:
	rm -f *.oct *.o


.PHONY: all clean
