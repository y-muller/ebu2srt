CXX=g++
CXXFLAGS= -std=c++11
#CXXFLAGS= -std=c++11 -g -DDEBUGMODE

MAKE=make
INCLUDES=-I../tclap-code/include -I../tinyxml2
LIBTINYXML=../tinyxml2/libtinyxml2.a

DEBINCLUDES=-I../tclap-code/include

ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

SRCS:=$(wildcard *.cpp)
INCS:=$(wildcard *.h)

ebu2srt: $(SRCS) $(INCS) $(LIBTINYXML)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o ebu2srt $(SRCS) $(LIBTINYXML)

debian: $(SRCS) $(INCS)
	$(CXX) $(CXXFLAGS) $(DEBINCLUDES) -o ebu2srt $(SRCS) -ltinyxml2

$(LIBTINYXML):
	$(MAKE) -C ../tinyxml2

clean:
	rm -f ebu2srt

distclean: clean

install:
	install -d $(DESTDIR)$(PREFIX)/bin/
	install -m 755 ebu2srt $(DESTDIR)$(PREFIX)/bin/

uninstall:
	rm $(DESTDIR)$(PREFIX)/bin/ebu2srt

.PHONY: install clean distclean uninstall

