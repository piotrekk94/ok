
CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -c -Wall -std=c++11
LDFLAGS=-g -std=c++11
LDLIBS=

SRCS=$(wildcard src/*.cpp )
OBJS=$(subst .cc,.o,$(SRCS))

all: tool

tool: $(OBJS)
	$(CXX) $(LDFLAGS) -o ok $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend
