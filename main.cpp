#include "heap.h"

int main() 
{
    Heap<int> heap;
    heap.Insert(9);
    heap.Insert(3);
    heap.Insert(55);
    heap.Insert(12);
    heap.Insert(11);
    heap.Print();


    return 0;
}
