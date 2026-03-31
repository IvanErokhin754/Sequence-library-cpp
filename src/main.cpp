#include <iostream>
#include "MutableArraySequence.hpp"

int main()
{
    MutableArraySequence<int> array;
    array.AppendInternal(10);
    std::cout << array[0];
    return 0;
}