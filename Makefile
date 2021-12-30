CXX= g++
CXX_FLAGS= -g -Wall


SOURCES= $(wildcard *.cpp)
OBJS= $(patsubst %.cpp, %.o, $(SOURCES))
DEP_FILES=$(patsubst %.cpp, %_deps.mk, $(SOURCES))


all: main

include deps.mk

main: $(OBJS)
	$(CXX) -o $@ $^

%.o : %.cpp
	$(CXX) $(CXX_FLAGS) -c $<

%_deps.mk: %.cpp
	$(CXX) -MM -MF $@ $<

deps.mk: $(DEP_FILES)
	rm -f deps.mk
	cat $(DEP_FILES) > deps.mk

tests:
	./main tests/1
	./main tests/2
	./main tests/3
	./main tests/4
	./main tests/5
	./main tests/6

clean: 
	clear
	rm -f $(OBJS)
	rm -f $(DEP_FILES)

