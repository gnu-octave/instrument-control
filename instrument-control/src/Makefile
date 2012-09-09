OCT = instrument-control.oct
SUBDIRS = i2c serial parallel

MKOCTFILE ?= mkoctfile

all:
	@for dir in $(SUBDIRS); do $(MAKE) -C $$dir; done
	$(MKOCTFILE) i2c/*.o serial/*.o parallel/*.o -o $(OCT)
	
clean:
	 @for dir in $(SUBDIRS); do $(MAKE) -C $$dir clean; done
	 rm -f *.oct
