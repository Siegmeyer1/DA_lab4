#include "letter.h"

TLetter::TLetter(std::istream &is) {
    is >> Value;
    for (char & i : Value) {
        i = (char)std::tolower(i);
    }
}

TLetter::TLetter(std::string& s) {
    Value = s;
    for (char & i : Value) {
        i = (char)std::tolower(i);
    }
}

std::istream& TLetter::operator>>(std::istream &is) {
    is >> this->Value;
    for (char & i : Value) {
        i = (char)std::tolower(i);
    }
    return is;
}

bool TLetter::operator==(const TLetter &other) {
    return this->Value == other.Value;
}
