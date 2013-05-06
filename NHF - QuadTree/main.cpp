//  Tóth András
//  QuadTree.hpp
//  NHF - QuadTree
//  Tesztprogram


#include <iostream>
#include "QuadTree.hpp"

int main()
{
    // teszt: QuadTree létrehozása, elemek beszúrása, kiírása, fa mélységének kiírása
    QuadTree<double> d(1000, 1000);
    d.insert(Point<double>(32, 4.0, 3.0));
    d.insert(Point<double>(35, 4.0, 3.1));
    d.insert(Point<double>(33, 9.8, 8.0));
    for (size_t i=0; i<20; ++i) {
    }
    // elemek kiírása
    std::cout << "Fában lévő elemek:\n" << d << std::endl;
    /*std::cout << "Fában lévő elemek száma: " << d.getRootNode()->countNodes() << std::endl;
    std::cout << "Fában lévő levelek száma: " << d.getRootNode()->countLeafs() << std::endl;
    */
    std::cout << "Fa mélysége: " << d.depth() << std::endl;
    
    return 0;
}