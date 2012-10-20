SUBDIRS = serial parallel i2c

MKOCTFILE ?= mkoctfile

all:
	@for dir in $(SUBDIRS); do $(MAKE) -i -C $$dir; done # -i - ignore errors
	
clean:
	 @for dir in $(SUBDIRS); do $(MAKE) -C $$dir clean; done
	 rm -f *.oct
