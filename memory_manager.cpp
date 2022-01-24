#include <iostream>
#include "linked_list.cpp"
using namespace std;

class MemoryManager
{
    void *startPtr;
    void *p;
    MemoryLL *head;
    int memoryAvailable;

public:
    MemoryManager(unsigned long n)
    {

        head = nullptr;

        Init(n);
    }

    // used for assingning the one time memory pool
    void Init(unsigned long &n)
    {
        p = malloc(n);
        if (p != NULL)
        {
            memoryAvailable = n;
            printf("\nMemory pool initialized : %d(bytes)", n);
        }
        startPtr = p;
    }

    // clearning up the whole system allocated memory pool
    void cleanUp()
    {
        free(p);
        printf("\n\n[info] Memory Pool released to system ");
        memoryAvailable = 0;
        auto aux = head;
        // release the links
        while (aux != nullptr)
        {
            auto temp = aux;
            aux = aux->nextLink;
            delete temp;
        }
    }

    void *myMalloc(unsigned long n)
    {
        // this will traverse through the linked list if avilable
        // find the best place to fit in list
        // then assign the start and end ptr to list as well as next link
        // return the start pointer of the current assigned link.

        if (n > memoryAvailable)
        {
            cout << "\n\nNot enough memory for allocation" << endl;
            return nullptr;
        }

        if (head == nullptr)
        {
            head = new MemoryLL(p, p + n - 1, nullptr, n);
            memoryAvailable -= n;
            // return the starting address of memory block
            return p;
        }
        else
        {
            // first find space between start and head
            auto aux = head;
            int spaceAvailable = (char *)aux->startAddress - (char *)startPtr;
            if (spaceAvailable >= n)
            {
                // create new linke and move head back
                auto newLink = new MemoryLL(startPtr, startPtr + n - 1, nullptr, n);
                newLink->nextLink = head;
                head = newLink;
                memoryAvailable -= n;
                return startPtr;
            }
            // if there is not enough space between start and first node
            // then find space between the linked nodes
            else
            {
                auto aux2 = head;
                aux = aux->nextLink;
                // iterate till we don't find nullptr or the best fit location
                while (aux != nullptr)
                {

                    spaceAvailable = (char *)aux->startAddress - (char *)aux2->endAddress;

                    if (spaceAvailable >= n)
                    {
                        auto newLink = new MemoryLL(aux2->endAddress + 1, aux2->endAddress + n, aux, n);
                        aux2->nextLink = newLink;
                        memoryAvailable -= n;
                        return newLink->startAddress;
                    }
                    else
                    {
                        aux2 = aux;
                        aux = aux->nextLink; // move forward
                    }
                }
                if (aux == nullptr)
                {
                    auto newLink = new MemoryLL(aux2->endAddress + 1, aux2->endAddress + n, nullptr, n);
                    aux2->nextLink = newLink;
                    memoryAvailable -= n;
                    return newLink->startAddress;
                }
            }
        }
    }

    void *myFree(void *p)
    {
        // find the LL having this pointer
        // and free this LL
        auto aux = head;
        auto aux2 = aux; // follower of aux
        if (p == nullptr)
        {
            printf("\n[INFO] No such memory : %d exist in pool ", p);
            return nullptr;
        }

        while (aux != nullptr)
        {
            if (aux->startAddress == p)
            {
                auto temp = aux;
                memoryAvailable += temp->memoryAllocated;
                aux2->nextLink = aux->nextLink;
                printf("\n\n $Memory deallocated \n From : %d  to : %d \t size : %d(bytes)", temp->startAddress, temp->endAddress, temp->memoryAllocated);
                printf("\n Memory Available : %d", memoryAvailable);

                delete temp;

                return nullptr;
            }
            else
            {
                aux2 = aux;
                aux = aux->nextLink;
            }
        }
        printf("\n[INFO] No such memory : %d exist in pool ", p);
    }

    int GetMemoryAvailable()
    {
        return memoryAvailable;
    }
};
