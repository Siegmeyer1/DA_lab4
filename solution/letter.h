#ifndef DA_LAB4_PREPROCESSOR_H
#define DA_LAB4_PREPROCESSOR_H

#include <iostream>
#include <string>

struct TLetter {
    std::string Value;
    TLetter() = default;
    explicit TLetter(std::istream& is);
    explicit TLetter(std::string&);
    std::istream& operator>>(std::istream& is);
    bool operator==(const TLetter &other);
    ~TLetter() = default;
};



#endif //DA_LAB4_PREPROCESSOR_H
