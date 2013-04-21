//  Tóth András
//  QuadTree.hpp
//  NHF - QuadTree
//  Tesztprogram


#include <iostream>
#include "QuadTree.hpp"

int main()
{
    // teszt: QuadTree létrehozása, elemek beszúrása, kiírása, fa mélységének kiírása
    QuadTree<double> d(1);
    d.insert(24);
    d.insert(23);
    d.insert(9234);
    d.insert(5084);
    for (size_t i=0; i<16; ++i) {
        d.insert(i);
    }
    // elemek kiírása rekurzívan
    std::cout << "Fában lévő elemek:\n" << d << std::endl;
    std::cout << "Fában lévő levelek száma: " << d.getRootNode()->countLeafs() << std::endl;
    std::cout << "Fa mélysége: " << d.depth();
    return 0;
}