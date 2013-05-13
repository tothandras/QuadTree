/// String osztály deklarációja.
/// @author Tóth András (O8POUA)

#ifndef STRING_H
#define STRING_H

#include <iostream>

/// @brief String osztály.
/// A 'pData'-ban vannak a karakterek (a lezáró nullával együtt), 'len' a hossza.
/// A hosszba nem számít bele a lezáró nulla.
class String {
    char *pData;
    unsigned int len;
public:
    /// @brief Konstruktor: egy karakterből.
    /// @param Ch egy karakter.
    String(char ch);
    
    /// @brief Konstruktor: egy egy nullával lezárt char sorozatból, ez a default konstruktor is.
    /// @param p Pointer a C stringre.
    String(const char* p = "");
    
    /// @brief C stringet ad vissza.
    /// @return Nullával lezárt karaktersorozatra mutató pointer.
    const char* c_str() const {
        return pData;
    }
    
    /// @brief Másoló konstruktor.
    /// @param s1 String, amiből létrehozzuk az új String-et.
    String(const String& s1);
    
    /// @brief Destruktor.
    ~String();
    
    /// @param rhs_s jobboldali String.
    /// @return Baoldali string.
    String& operator=(const String& rhs_s);
    
    /// @brief Két Stringet összefűz.
    /// @param rhs_s jobboldali String.
    /// @return Új String, ami tartalmazza a két stringet egymás után.
    String operator+(const String& rhs_s) const ;
    
    /// @brief A string egy megadott indexű elemének referenciájával tér vissza.
    /// @param idx Karakter indexe.
    /// @return Karakter referenciája.
    ///         Indexelési hiba esetén const char* kivételt dob.
    char& operator[](unsigned int idx);
    
    /// @brief A string egy megadott indexű elemének referenciájával tér vissza.
    /// @param idx Karakter indexe.
    /// @return Karakter referenciája.
    ///         Indexelési hiba esetén const char* kivételt dob.
    const char& operator[](unsigned int idx) const;
    
    /// @brief Kiíró operátor.
    /// @param os Ostream típusú objektum.
    /// @param s0 String, amit kiírunk.
    /// @return os
    friend std::ostream& operator<<(std::ostream& os, const String& s0);
    
    /// @brief Beolvas az istream-ről egy szót egy String-be.
    /// @param is Istream típusú objektum.
    /// @param s0 String, amibe beolvas.
    /// @return is
    friend std::istream& operator>>(std::istream& is, String& s0);
};
#endif