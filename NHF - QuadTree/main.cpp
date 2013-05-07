//  Tóth András
//  QuadTree.hpp
//  NHF - QuadTree
//  Tesztprogram


#include <iostream>
#include "QuadTree.hpp"

int main(int argc, char* argv[])
{
    // teszt: QuadTree létrehozása, elemek beszúrása, kiírása, fa mélységének kiírása
    QuadTree<double> doubleTree(10, 10);
    doubleTree.insert(Point<double>(23, 2, 3));
    doubleTree.insert(Point<double>(26, 2, 6));
    doubleTree.insert(Point<double>(63, 6, 3));
    doubleTree.insert(Point<double>(66, 6, 6));
    doubleTree.insert(Point<double>(99, 9, 9));
    doubleTree.insert(Point<double>(88, 8, 8));
    for (size_t i=0; i<20; ++i) {
        doubleTree.insert(Point<double>(i, 8, 8.0));
    }
    // elemek kiírása
    std::cout << "Fában lévő elemek:\n" << doubleTree << std::endl;
    std::cout << "Fa mélysége: " << doubleTree.depth() << std::endl;
    
    return 0;
}