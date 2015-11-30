#compiler
CC=g++
#compiler options
OPTS=-c -Wall
#source files
SOURCES=$(wildcard src/*.cpp )
#object files
OBJECTS=$(SOURCES:.cc=.o)
#sdl-config or any other library here. 
#''- ensures that the command between them is executed, and the result is put into LIBS
LIBS=
#executable filename
EXECUTABLE=ok
#Special symbols used:
#$^ - is all the dependencies (in this case =$(OBJECTS) )
#$@ - is the result name (in this case =$(EXECUTABLE) )

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(LINK.o) $^ -o $@ $(LIBS)

clean:
	rm $(EXECUTABLE) $(OBJECTS)
