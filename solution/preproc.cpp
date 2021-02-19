#include "preproc.h"

TPreprocessor::TPreprocessor(std::istream &is) {
    std::string inp, letter;
    std::getline(std::cin, inp);
    if (inp.back() == '\n') {
        inp.pop_back();
    }
    std::stringstream inpStr(inp);
    while (inpStr >> letter) {
        Pattern.emplace_back(letter);
    }
    CalcBadSymb();
    CalcN();
    CalcGoodSuff();
    CalcPrefSuff();
}

TPreprocessor::TPreprocessor(std::vector<TLetter>& patt) {
    Pattern = patt;
    CalcBadSymb();
    CalcN();
    CalcGoodSuff();
    CalcPrefSuff();
}


void TPreprocessor::CalcBadSymb() {
    if (Pattern.empty()) return;
    for (unsigned long i = Pattern.size() - 1; i >= 0; --i) {
        auto iter = BadSymb.find(Pattern[i].Value);
        if (iter == BadSymb.end()) {
            BadSymb.emplace(Pattern[i].Value, std::vector<unsigned long>{i});
        } else {
            iter->second.push_back(i);
        }
        if (i == 0) break;
    }
}

void TPreprocessor::CalcN() {
    if (Pattern.empty()) return;
    unsigned long l = 0, r = 0, size = Pattern.size();
    unsigned long RevN[size];
    N.resize(size);
    for (unsigned long i = 0; i < size; ++i) {
        RevN[i] = 0;
    }
    std::vector<TLetter> RPattern;
    for (unsigned long i = 0; i < size; ++i) {
        RPattern.push_back(Pattern[size - 1 - i]);
    }
    for (unsigned long i = 1; i < RPattern.size(); ++i) {
        if (i <= r) {
            RevN[i] = std::min(r - i + (unsigned long)1, RevN[i - l]);
        }
        while (i+RevN[i] < size && RPattern[RevN[i]] == RPattern[i+RevN[i]]) {
            RevN[i]++;
        }
        if (i + RevN[i] - (unsigned long)1 > r) {
            l = i;
            r = i + RevN[i] - (unsigned long)1;
        }
    }
    for (unsigned long i = 0; i < size; ++i) {
        N[i] = RevN[size - i - 1];
    }
}

    void TPreprocessor::CalcGoodSuff() {
    if (Pattern.empty()) return;
    unsigned long size = Pattern.size();
    GoodSuff.resize(size);
    for (unsigned long i = 0; i < size - 1; ++i) {
        if (N[i] != 0) {
            GoodSuff[size - N[i]] = i;
        }
    }
}

void TPreprocessor::CalcPrefSuff() {
    if (Pattern.empty()) return;
    unsigned long size = Pattern.size();
    PrefSuff.resize(size);
    for (int i = size - 1; i >= 0; i--) {
        int j = size - i - 1;
        if (N[j] == j + 1) {
            PrefSuff[i] = j + 1;
        } else {
            if (i == size - 1) {
                PrefSuff[i] = 0;
            } else {
                PrefSuff[i] = PrefSuff[i + 1];
            }
        }
    }
}

unsigned long TPreprocessor::Size() {
    return Pattern.size();
}
