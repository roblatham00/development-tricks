CXX=g++
CXXFLAGS=-Wall -g -fsanitize=address -fsanitize=undefined

all: fib fib-demo
fib: fib.cc
fib-demo: fib.cc
	$(CXX) -DSTOP_DEMO $(CXXFLAGS) $< -o $@
clean:
	rm -f fib fib-demo *.o
