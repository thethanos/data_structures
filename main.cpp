#include "tree.h"

int main() 
{
    Tree<int> tree(10);
    tree.Insert(9);
    tree.Insert(3);
    tree.Insert(55);
    tree.Insert(12);
    tree.Insert(11);
    tree.Print();

    return 0;
}