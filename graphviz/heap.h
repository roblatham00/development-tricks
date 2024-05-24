#include <stdlib.h>
#include <string.h>

#include <initializer_list>
#include <vector>
#include <iostream>

template <typename T>
class Heap {
    typedef T value_type;
    public:
        /* using a 0-based heap so '0' means 'element at 0 is valid' */
        Heap(): heap_size(0) {};
        Heap(std::initializer_list<T> il): A(il), heap_size(A.size()) {
            build_max_heap();
        };

        void print() {
            static int counter=0;
            std::cout<<"digraph heap_" << counter++ << " {\n";
            for (size_t i=0; i< heap_size; i++) {
                size_t l = left(i);
                size_t r = right(i);
                std::string color="\"black\"";
                /* also check for violation of heap property: shouldn't ever be invalid except in debugging situations */
                if (l < heap_size) {
                    std::cout << "   " << i << "->" << l << "\n";
                    if (A[l] > A[i]) color= "\"red\"";
                }
                if (r < heap_size) {
                    std::cout << "   " << i << "->" << r << "\n";
                    if (A[r] > A[i]) color= "\"red\"";
                }
                std::cout << "   " << i << " [label=" << A[i] << ", xlabel= " << i << " color=" << color << " ]\n";
            }
            std::cout<< "    Array [ shape = record, label = \"";
            /* the last element of the record terminates the array: we end loop early so we can treat it differently */
            for (size_t i=0; i< A.size() -1 ; i++)
                std::cout << " " << A[i] << " |";
            std::cout << " " << A.back() << "\"]\n";
            std::cout << "}" << std::endl;
        };

        T* data() { return A.data(); };

        void insert_max(T key) {
            heap_size++;
            if (heap_size > A.size())
                A.push_back(key);
            else
                A[heap_size-1] = key;
            increase_key(heap_size-1, key);
        }

        void heapsort() {
            // no need to build_max_heap: the heap is heap-y on construction or insertion
            for (ssize_t i = A.size()-1; i>=0; i--) {
                std::swap(A[0], A[i]);
                heap_size--;
                max_heapify(0);
            }
        };
    private:
        std::vector<T> A;
        size_t heap_size; // how many items in the heap: subtract one if using as index
        /* zero-based array, not 1-based as in CLR */
        inline size_t parent(size_t i) {
            return((i-1)/2);
        };
        inline size_t left(size_t i) {
            return (2*i+1);
        };
        inline size_t right(size_t i) {
            return(2*i+2);
        };
        void build_max_heap() {
            heap_size = A.size();
            /* zero-based heap requires adjustment to first not-leaf
             * calculation. Also signed size_t so we know when we finish */
            for(ssize_t i = (A.size()-1)/2; i>=0; i--) {
                max_heapify(i);
            }
        };

        void max_heapify(size_t i) {
            size_t l = left(i);
            size_t r = right(i);
            size_t largest=0;

#ifdef SHOW_TREE
            print();
#endif
            if ( (l < heap_size ) &&
                    A[l] > A[i] )
                largest = l;
            else
                largest = i;

            if ( (r < heap_size) &&
                    A[r] > A[largest])
                largest = r;

            if (largest != i) {
                std::swap(A[i], A[largest]);
                max_heapify(largest);
            }
        };

        void min_heapify(size_t i) {
            size_t l = left(i);
            size_t r = right(i);
            size_t smallest;

            if ( (l < heap_size) &&
                A[l] < A[i] )
                smallest = l;
            else
                smallest = i;

            if ( (r < heap_size) &&
                    A[r] < A[smallest])
                smallest = r;

            if (smallest != i) {
                std::swap(A[i], A[smallest]);
                min_heapify(A, smallest);
            }
        };
        /* heapsort */
        T maximum() { return A[0]; };

        void extract_max() {
            if (heap_size == 0) {
                std::cerr << "heap underflow" << std::endl;
                return;
            }
            /* it's a swap, except we also hold onto the largest value */
            auto max = A[0];
            A[0] = A[heap_size-1];
            heap_size--;
            max_heapify(0);
            return max;
        }
        void increase_key(size_t i, T key)
        {
            if (key < A[i]) {
                std::cerr << "new key smaller than current key" << std::endl;
                return;
            }
            A[i] = key;
            while (i > 0 && A[parent(i)] < A[i]) {
                std::swap(A[i], A[parent(i)]);
                i = parent(i);
            }
        }

};
