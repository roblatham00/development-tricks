CXX=g++
CXXFLAGS=-Wall -g -O2 -fsanitize=address -fsanitize=undefined

all: test_heap_show test_heap

test_heap_show: test_heap.cc heap.h
	$(CXX) -DSHOW_TREE $(CXXFLAGS) $< -o $@

test_heap: test_heap.cc heap.h

clean:
	rm -f *.o test_heap test_heap_show
