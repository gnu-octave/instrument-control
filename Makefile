## Copyright 2018 John Donoghue
## Copyright 2015-2016 Carnë Draug
## Copyright 2015-2016 Oliver Heimlich
##
## Copying and distribution of this file, with or without modification,
## are permitted in any medium without royalty provided the copyright
## notice and this notice are preserved.  This file is offered as-is,
## without any warranty.

## Some basic tools (can be overriden using environment variables)
SED ?= sed
TAR ?= tar
GREP ?= grep
CUT ?= cut
TR ?= tr

PACKAGE = $(shell $(GREP) "^Name: " DESCRIPTION | $(CUT) -f2 -d" ")
VERSION = $(shell $(GREP) "^Version: " DESCRIPTION | $(CUT) -f2 -d" ")

TARGET_DIR      = target/
RELEASE_DIR     = $(TARGET_DIR)$(PACKAGE)-$(VERSION)
RELEASE_TARBALL = $(TARGET_DIR)$(PACKAGE)-$(VERSION).tar.gz
HTML_DIR        = $(TARGET_DIR)$(PACKAGE)-html
HTML_TARBALL    = $(TARGET_DIR)$(PACKAGE)-html.tar.gz

M_SOURCES   = $(wildcard inst/*.m) $(patsubst %.in,%,$(wildcard src/*.m.in))
#CC_SOURCES  = $(wildcard src/*.cc)
CC_SOURCES  = 
OCT_FILES   = $(patsubst %.cc,%.oct,$(CC_SOURCES))
## This has the issue that it won't include PKG_ADD from src/*.m since
## they may not exist yet to be grepped.
PKG_ADD     = $(shell $(GREP) -Pho '(?<=// PKG_ADD: ).*' $(CC_SOURCES) $(M_SOURCES) src/make-pkg-add-file.cc)

# other octave packages we depend on in testing
DEPENDS     =

OCTAVE ?= octave --no-window-system --silent

.PHONY: help dist html release install all check run clean

help:
	@echo "Targets:"
	@echo "   dist    - Create $(RELEASE_TARBALL) for release"
	@echo "   html    - Create $(HTML_TARBALL) for release"
	@echo "   release - Create both of the above and show md5sums"
	@echo
	@echo "   install - Install the package in GNU Octave"
	@echo "   all     - Build all oct files"
	@echo "   check   - Execute package tests (w/o install)"
	@echo "   doctest - Tests only the help text via the doctest package"
	@echo "   run     - Run Octave with development in PATH (no install)"
	@echo
	@echo "   clean   - Remove releases, html documentation, and oct files"

%.tar.gz: %
	$(TAR) -c -f - --posix -C "$(TARGET_DIR)" "$(notdir $<)" | gzip -9n > "$@"

$(RELEASE_DIR): .hg/dirstate
	@echo "Creating package version $(VERSION) release ..."
	-rm -rf "$@"
	hg archive --exclude ".hg*" --exclude "Makefile" --exclude "HACKING" \
	  --exclude "devel" --type files "$@"
	cd "$@" && cd "src/" && ./bootstrap && rm -rf "autom4te.cache"
	chmod -R a+rX,u+w,go-w "$@"

$(HTML_DIR): install
	@echo "Generating HTML documentation. This may take a while ..."
	-rm -rf "$@"
	$(OCTAVE) --no-window-system --silent \
	  --eval "pkg load generate_html; " \
	  --eval "pkg load $(PACKAGE);" \
	  --eval 'generate_package_html ("${PACKAGE}", "$@", "octave-forge");'
	chmod -R a+rX,u+w,go-w $@

dist: $(RELEASE_TARBALL)
html: $(HTML_TARBALL)

release: dist html
	md5sum $(RELEASE_TARBALL) $(HTML_TARBALL)
	@echo "Upload @ https://sourceforge.net/p/octave/package-releases/new/"

## Note that in development versions this target may fail if we are dependent
## on unreleased versions.  This is by design, to force possible developers
## to set this up by hand (either using the "-nodeps" option" or changing the
## dependencies on DESCRIPTION.
install: $(RELEASE_TARBALL)
	@echo "Installing package locally ..."
	$(OCTAVE) --eval 'pkg ("install", "-verbose", "${RELEASE_TARBALL}")'

all: $(CC_SOURCES)
	test -e src/configure || (cd "src/" && ./bootstrap && rm -rf "autom4te.cache")
	cd src/ && ./configure
	$(MAKE) -C src/

check: all
	$(OCTAVE) --silent --path "inst/" --path "src/" \
          --eval 'if(!isempty("$(DEPENDS)")); pkg load $(DEPENDS); endif;' \
          --eval '${PKG_ADD}' \
          --eval "__run_test_suite__ ({'inst'}, {})"

doctest: all
	$(OCTAVE) --path "inst/" --path "src/" \
	  --eval '${PKG_ADD}' \
	  --eval 'pkg load doctest;' \
	  --eval "targets = '$(shell (ls inst; ls src | $(GREP) .oct) | $(CUT) -f2 -d@ | $(CUT) -f1 -d.)';" \
	  --eval "targets = strsplit (targets, ' ');" \
	  --eval "doctest (targets);"

run: all
	$(OCTAVE) --persist --path "inst/" --path "src/" \
	  --eval '${PKG_ADD}'

clean:
	rm -rf $(TARGET_DIR)
	test -e inst/test && rm -rf inst/test || true
	test -e src/Makefile && $(MAKE) -C src distclean || true
