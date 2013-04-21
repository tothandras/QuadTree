#include <iostream>
#include "QuadTree.hpp"

int main(int argc, const char * argv[])
{
    //teszt: QuadTree létrehozása, elemek beszúrása, kiírása, fa mélységének kiírása
    QuadTree<double> d(1);
    d.insert(24);
    d.insert(23);
    d.insert(9234);
    d.insert(5084);
    for (size_t i=0; i<16; ++i) {
        d.insert(i);
    }
    std::cout << d << "\ndepth: " << d.depth();
    return 0;
}