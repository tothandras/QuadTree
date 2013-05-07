///  Tóth András (O8POUA)
///  NHF 2013 - QuadTree (Négy elágazású duplán láncolt generikus fa)
///  Tesztprogram


#include <iostream>
//#include "QuadTreeIterator.hpp"
#include "QuadTree.hpp"

int main()
{
    /// QuadTree létrehozása.
    QuadTree<double> doubleTree(10, 10);
    /// Új elemek beszúrása.
    doubleTree.insert(Point<double>(23, 2, 3));
    doubleTree.insert(Point<double>(26, 2, 6));
    doubleTree.insert(Point<double>(63, 6, 3));
    doubleTree.insert(Point<double>(66, 6, 6));
    doubleTree.insert(Point<double>(99, 9, 9));
    doubleTree.insert(Point<double>(88, 8, 8));
    /// Beszúrás olyan helyre, ahol már található meglévő adat.
    for (size_t i=0; i<5; ++i) {
        doubleTree.insert(Point<double>(i, 8, 8.0));
    }
    /// Elemek kiírása.
    std::cout << "Fában lévő elemek:\n" << doubleTree << std::endl;
    /// Fa mélységének kiírása.
    std::cout << "Fa mélysége: " << doubleTree.depth() << std::endl;
    
    /// Hibakezelés vizsgálata.
    std::cout << "Hibakezelés vizsgálata:" << std::endl;
    try {
        doubleTree.insert(Point<double>(100, 11, 5));
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    /// Keresés a fában.
    try {
        doubleTree.find(Point<double>(66, 6, 6)).getData()=11;
        std::cout << doubleTree.find(11);
        std::cout << doubleTree.find(66);
    } catch (const char* c) {
        std::cout << c;
    }
    
    return 0;
}