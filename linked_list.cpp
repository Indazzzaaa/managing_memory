#include <iostream>
using namespace std;

// used for memory chunks memory chunks
struct MemoryLL
{
    void *startAddress;
    void *endAddress;
    MemoryLL *nextLink;
    int memoryAllocated = 0;

    MemoryLL(void *start, void *end, MemoryLL *link, int memorySize)
    {
        startAddress = start;
        endAddress = end;
        nextLink = link;
        memoryAllocated = memorySize;

        printf("\n\n  MemoryAllocated : %d(bytes) |\tFrom : %d |\t To : %d  ", memoryAllocated, startAddress, endAddress);
    }
};