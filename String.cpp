#include <iostream>
#include <cstring>
#include "String.h"

using namespace std;

String::String(char ch) {
    len = 1;
    pData = new char[len+1];
    pData[0] = ch;
    pData[1] = '\0';
}

String::~String() { delete[] pData; }

String::String(const char *p) {
    len = (unsigned)strlen(p);
    pData = new char[len+1];
    strcpy(pData, p);
}

String::String(const String& s1) {
    len = s1.len;
    pData = new char[len+1];
    strcpy(pData, s1.pData);
}

String& String::operator=(const String& rhs_s) {
    if (this != &rhs_s) {
        delete[] pData;
        len = rhs_s.len;
        pData = new char[len+1];
        strcpy(pData, rhs_s.pData);
    }
    return *this;
}

char& String::operator[](unsigned int idx) {
    if (idx >= len) throw "String: failure";
    return pData[idx];
}

const char& String::operator[](unsigned int idx) const {
    if (idx >= len) throw "String: faliure";
    return pData[idx];
}

String String::operator+(const String& rhs_s) const {
    String temp;           
    temp.len = len + rhs_s.len;
    delete []temp.pData;
    temp.pData = new char[temp.len+1];
    strcpy(temp.pData, pData);
    strcat(temp.pData, rhs_s.pData);
    
    return temp;                
    
}

std::ostream& operator<<(std::ostream& os, const String& s0) {
    os << s0.pData;
    return os;
}

std::istream& operator>>(std::istream& is, String& s0) {
    unsigned char ch;
    s0 = String("");            
    std::ios_base::fmtflags fl = is.flags();
    is.setf(ios_base::skipws);                      
    while (is >> ch) {
        is.unsetf(ios_base::skipws);        
        if (isspace(ch)) {
            is.putback(ch);             
            break;
        } else {
            s0 = s0 + ch;               
        }
    }
    is.setf(fl);                                            
    return is;
}