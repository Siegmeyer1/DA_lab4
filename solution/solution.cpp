#include "letter.h"
#include "preproc.h"
#include "AD_search.h"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    bool word = false;
    std::vector<TLetter> text, pattern;
    std::string inp, letter;

    pattern.emplace_back();
    std::getline(std::cin, inp);
    for (auto symb : inp) {
        if (symb != ' ') {
            word = true;
            pattern.back().Value.push_back(std::tolower(symb));
        }
        else {
            if (word) {
                word = false;
                pattern.emplace_back();
            }
        }
    }
    if (pattern.back().Value.empty()) {
        pattern.pop_back();
    }
    TPreprocessor A(pattern);
    unsigned long wordNo = 1;
    std::vector<unsigned long> newLines;
    text.emplace_back();
    while (std::getline(std::cin, inp)) {
        for (int i = 0; i < inp.size(); i++) {
            if (inp[i] != ' ') {
                word = true;
                text.back().Value.push_back(std::tolower(inp[i]));
            }
            else {
                if (word) {
                    wordNo++;
                    word = false;
                    text.emplace_back();
                }
            }
        }
        if (word) {
            wordNo++;
            word = false;
            text.emplace_back();
        }
        newLines.emplace_back(wordNo);
    }
    AD_search(A, text, newLines);
    return 0;
}