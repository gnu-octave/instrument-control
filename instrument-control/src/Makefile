OCT = instrument-control
SUBDIRS = i2c serial

MKOCTFILE ?= mkoctfile

all:
	@for dir in $(SUBDIRS); do $(MAKE) -C $$dir; done
	$(MKOCTFILE) i2c/*.o serial/*.o -o $(OCT)
	
clean:
	 @for dir in $(SUBDIRS); do $(MAKE) -C $$dir clean; done
	 rm -f *.oct
