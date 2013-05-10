// - NHF 2013 - QuadTree (Négy elágazású duplán láncolt generikus fa) - Tesztprogram
// Feladat kiírás:
// Készítsen GENERIKUS duplán láncolt 4 elágazású fát (quad-tree)!
// Valósítsa meg az összes értelmes műveletet operátor átdefiniálással (overload),
// de nem kell ragaszkodni az összes operátor átdefiniálásához!
// Amennyiben lehetséges használjon iterátort!
// - Tóth András (O8POUA)

// Input fájlt:
#define input "/Users/tothandras/Dropbox/Mernokinformatika/Szoftlab2/Szoftlab2NHFquadtree/NHFQuadTree/input.dat"

#include <iostream>
#include <fstream>
#include "QuadTree.hpp"

int main()
{
    // QuadTree létrehozása.
    QuadTree<int> nTree(10, 10);
    // Új elemek beszúrása.
    nTree.insert(Point<int>(23, 2, 3));
    nTree.insert(Point<int>(26, 2, 6));
    nTree.insert(Point<int>(63, 6, 3));
    nTree.insert(Point<int>(66, 6, 6));
    nTree.insert(Point<int>(99, 9, 9));
    // Beszúrás olyan helyre, ahol már található meglévő adat.
    for (int i=0; i<3; ++i) {
        nTree.insert(Point<int>(i, 9, 9));
    }
    // Elemek kiírása.
    std::cout << "Double-t tartalmazó fában lévő elemek:\n" << nTree << std::endl;
    // Fa mélységének kiírása.
    std::cout << "Fa mélysége: " << nTree.depth() << std::endl << std::endl;
    
    // Hibakezelés vizsgálata.
    std::cout << "Kivételek kezelésének vizsgálata:\n";
    try {
        nTree.insert(Point<int>(100, 11, 5)); // Külső pont nem szúrható be.
    } catch (const char* c) {
        std::cout << c << std::endl;
    }
    
    // Keresés a fában.
    try {
        nTree.find(Point<int>(66, 6, 6)).getData()=11; // Pont megkeresése, tárolt adat átírása.
        std::cout << nTree.find(11); // Sikerült átírni.
        std::cout << nTree.find(66); // Már nincs ilyen pont.
    } catch (const char* c) {
        std::cout << c << std::endl;
    }
    
    // Fájlból beolvasás.
    QuadTree<char> chTree(10, 10);
    try {
        std::fstream File;
        File.open(input);
        File >> chTree;
        File.close();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << std::endl << "Fájlból beolvasott char-t tartalmazó fában lévő elemek:\n" << chTree;
    
    return 0;
}