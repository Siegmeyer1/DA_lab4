#ifndef DA_LAB4_PREPROC_H
#define DA_LAB4_PREPROC_H

#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include "letter.h"

class TPreprocessor {
public:
    TPreprocessor() = default;
    explicit TPreprocessor(std::istream& is);
    TPreprocessor(std::vector<TLetter>& patt);
    void CalcBadSymb();
    void CalcN();
    void CalcGoodSuff();
    void CalcPrefSuff();
    unsigned long Size();
    ~TPreprocessor() = default;

    std::vector<TLetter> Pattern;
    std::unordered_map<std::string, std::vector<unsigned long>> BadSymb;
    std::vector<unsigned long> GoodSuff;
    std::vector<unsigned long> N;
    std::vector<unsigned long> PrefSuff;
};

#endif //DA_LAB4_PREPROC_H
