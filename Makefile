FILES=html.cpp modernkit.cpp machine.cpp file.cpp
OBJ=html.o modernkit.o machine.o file.o
INC=-I.
CXXFLAGS=-std=c++11

all: out

obj: $(FILES)
	g++ -c $(FILES) $(INC) $(CXXFLAGS)

out: obj
	g++ $(OBJ) -L/usr/local/lib -lxerces-c-3.1 -o modernkit

.PHONY: clean
clean:
	rm -rf *.o