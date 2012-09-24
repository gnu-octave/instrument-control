OCT := parallel.oct pp_close.oct pp_datadir.oct pp_data.oct pp_stat.oct pp_ctrl.oct
OBJ := parallel_class.o

MKOCTFILE ?= mkoctfile

all: $(OBJ) $(OCT)

%.o: %.cc
	$(MKOCTFILE) -c $^

%.oct: %.o
	$(MKOCTFILE) $^ $(OBJ) -o ../$@

clean:
	rm -f *.oct *.o

.PHONY: all clean