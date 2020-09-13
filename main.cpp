#include "heap.h"

int main() 
{
    Heap<int> heap;
    heap.Insert(555);
    heap.Insert(9);
    heap.Insert(3);
    heap.Insert(122);
    heap.Insert(55);
    heap.Insert(12);
    heap.Insert(0);
    heap.Insert(11);
    
    for (int i(0); i < 8; ++i)
        std::cout << heap.ExtractMax() << std::endl; 


    return 0;
}
