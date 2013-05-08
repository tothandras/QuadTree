///!  Tóth András (O8POUA)
///  NHF 2013 - QuadTree (Négy elágazású duplán láncolt generikus fa)
///  Tesztprogram

/// Input fájlt:
#define input "input.dat"

#include <iostream>
#include <fstream>
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
    for (size_t i=0; i<3; ++i) {
        doubleTree.insert(Point<double>(i, 9, 9));
    }
    /// Elemek kiírása.
    std::cout << "Double-t tartalmazó fában lévő elemek:\n" << doubleTree << std::endl;
    /// Fa mélységének kiírása.
    std::cout << "Fa mélysége: " << doubleTree.depth() << std::endl << std::endl;
    
    /// Hibakezelés vizsgálata.
    std::cout << "Kivételek kezelésének vizsgálata:\n";
    try {
        doubleTree.insert(Point<double>(100, 11, 5)); // Külső pont nem szúrható be.
    } catch (const char* c) {
        std::cout << c << std::endl;
    }
    
    /// Keresés a fában.
    try {
        doubleTree.find(Point<double>(66, 6, 6)).getData()=11; // Pont megkeresése, tárolt adat átírása.
        std::cout << doubleTree.find(11); // Sikerült átírni.
        std::cout << doubleTree.find(66); // Már nincs ilyen pont.
    } catch (const char* c) {
        std::cout << c << std::endl;
    }
    
    /// Fájlból beolvasás.
    QuadTree<char> charTree(10, 10);
    try {
        std::fstream File;
        File.open(input);
        File >> charTree;
        File.close();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << std::endl << "Fájlból beolvasott char-t tartalmazó fában lévő elemek:\n" << charTree;
    
    return 0;
}