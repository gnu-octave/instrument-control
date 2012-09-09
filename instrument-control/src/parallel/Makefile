OCT := parallel.oct
OBJ := parallel.o pp_close.o pp_datadir.o pp_data.o pp_stat.o pp_ctrl.o

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
