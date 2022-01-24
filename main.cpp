#include <iostream>
#include "memory_manager.cpp"
using namespace std;

int main(int argc, char const *argv[])
{
    MemoryManager m(1000);

    void *p1 = m.myMalloc(100);
    void *p2 = m.myMalloc(200);
    void *p3 = m.myMalloc(200);
    void *p4 = m.myMalloc(200);
    void *p5 = m.myMalloc(200);
    void *p6 = m.myMalloc(200);
    p2 = m.myFree(p2);
    p2 = m.myMalloc(100);
    m.cleanUp();

    return 0;
}
