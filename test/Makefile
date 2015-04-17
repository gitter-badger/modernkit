CXX=`$CXX`
FILE1=../html.cpp modernkit_test1.cpp ../machine.cpp ../file.cpp
OBJ1=html.o modernkit_test1.o machine.o file.o
INC=../include

all: modernkit_test

obj1: $(FILE1)
	$(CXX) -c $(FILE1) $(INC)

modernkit_test: obj1
	$(CXX) $(OBJ1) -L.. -lxerces-c-3.1 -o modernkit_test1

.PHONY: clean
clean:
	rm -rf *.o
.PHONY: test
test:
	./modernkit_test1
