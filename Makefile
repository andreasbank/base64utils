BASE_DIR  = $(shell pwd)
prefix   ?= /usr/local
LIBDIR    = $(prefix)/lib
INCLDIR    = $(prefix)/include
INSTALL  ?= /usr/bin/install
CXXFLAGS += -O3 -Wall -g -I$(BASE_DIR)

all: base64_utils.o

base64_utils.o: base64_utils.cpp
	$(CXX) -c $(CXXFLAGS) $^ $(LDFLAGS) -o $@

install: all
	$(INSTALL) -d $(LIBDIR)
	$(INSTALL) -m 0644 base64_utils.o $(LIBDIR)
	$(INSTALL) -d $(INCLDIR)
	$(INSTALL) -m 0644 base64_utils.hpp $(INCLDIR)

test: test.cpp base64_utils.o
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@
	$(BASE_DIR)/$@

clean:
	$(RM) -rf test base64_utils.o *~
