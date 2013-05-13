// - NHF 2013 - QuadTree (Négy elágazású duplán láncolt generikus fa) - Tesztprogram
// Feladat kiírás:
/// Készítsen GENERIKUS duplán láncolt 4 elágazású fát (quad-tree)!
/// Valósítsa meg az összes értelmes műveletet operátor átdefiniálással (overload),
/// de nem kell ragaszkodni az összes operátor átdefiniálásához!
/// Amennyiben lehetséges használjon iterátort!
/// @author Tóth András (O8POUA)

// Input fájlok:
#define input_ch "input_ch.dat"
#define input_s "input_s.dat"


#include <iostream>
#include <fstream>
#include "QuadTree.hpp"
#include "String.h" // String: saját osztály, amely dinamikus adatot tartalmaz.


int main(int argc, const char * argv[])
{
    // Egészeket tartalmazó négyfa létrehozása.
    QuadTree<int> nTree(10, 10);
    // Új elemek beszúrása.
    nTree.insert(Point<int>(66, 6, 6));
    nTree.insert(Point<int>(48, 4.5, 3.11));
    nTree.insert(Point<int>(11, 1, 1));
    nTree.insert(Point<int>(12, 1.123, 2));
    nTree.insert(Point<int>(43, 4, 3.536345));
    try {
        nTree.insert(Point<int>(99, 9, 9));
        // Beszúrás olyan helyre, ahol már található meglévő adat.
        nTree.insert(Point<int>(100, 9, 9));
    } catch (...) {
        std::cout << "Hiba beszúrásnál."; // Nem szabad, hogy hiba történjen.
    }
    
    // Elemek kiírása.
    std::cout << "Int-eket tartalmazó fában lévő elemek:\n" << nTree << std::endl;
    // Fa mélységének kiírása.
    std::cout << "Fa mélysége: " << nTree.depth() << std::endl << std::endl;
    
    // Kivételkezelés vizsgálata.
    std::cout << "Kivételkezelésének vizsgálata külső pont beszúrása esetén:\n";
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
    QuadTree<char> chTree(150, 150);
    QuadTree<String> sTree(5.1, 4.8);
    try {
        std::fstream File;
        // Char-t tartalmazó fába beolvasás.
        File.open(input_ch);
        File >> chTree;
        File.close();
        // String-et tartalmazó fába beolvasás.
        File.open(input_s);
        File >> sTree;
        File.close();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << std::endl << "Fájlból beolvasott char-t tartalmazó fában lévő elemek:\n" << chTree;
    std::cout << std::endl << "Fájlból beolvasott String-et tartalmazó fában lévő elemek:\n" << sTree;
    
    return 0;
}