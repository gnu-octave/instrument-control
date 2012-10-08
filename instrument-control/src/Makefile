SUBDIRS = i2c serial parallel

MKOCTFILE ?= mkoctfile

all:
	# -i - ignore errors
	@for dir in $(SUBDIRS); do $(MAKE) -i -C $$dir; done
	
clean:
	 @for dir in $(SUBDIRS); do $(MAKE) -C $$dir clean; done
	 rm -f *.oct
