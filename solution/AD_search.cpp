#include "letter.h"
#include "preproc.h"

void entry (std::vector<unsigned long>& newLines, unsigned long &k, unsigned long &n, int &line) {
    unsigned long position = k - n + 1;
    while(newLines[line-1] <= position) {
        line++;
    }
    if (line > 1) {
        position -= newLines[line - 2] - 1;
    }
    std::cout << line << ", " << position << "\n";
}

void boyer_move(TPreprocessor& Pat, std::vector<TLetter>& text, unsigned long &n, unsigned long &k, unsigned long &h, unsigned long &i, bool found) {
    if (found) {
        if (n > 2) {
            k += n - Pat.PrefSuff[1];
        } else {
            k++;
        }
    } else {
        unsigned long bad = 0;
        auto iter = Pat.BadSymb.find(text[h].Value);
        if (iter != Pat.BadSymb.end()) {
            for (int d : iter->second) {
                if (d < i) {
                    bad = d + 1;
                    break;
                }
            }
        }
        if (bad == 0) {
            bad++;
        } else {
            bad = i - bad + 1;
        }
        unsigned long suff;
        if (i == n - 1) {
            suff = 1;
        } else {
            if (Pat.GoodSuff[i + 1] > 0) {
                suff = n - (Pat.GoodSuff[i + 1] + 1);
            } else {
                suff = n - Pat.PrefSuff[i + 1];
            }
        }
        k += std::max(suff, bad);
    }
}

void AD_search(TPreprocessor& Pat, std::vector<TLetter>& text, std::vector<unsigned long>& newLines) {
    if (Pat.Pattern.empty()) {
        return;
    }
    std::vector<unsigned long> M(text.size());
    unsigned long k = 0, n = Pat.Size(), i = 0, h = 0;
    int line = 1;
    k = n;
    while (k < text.size()) {
        i = n-1;
        h = k-1;
        while (true) {
            if (M[h] == 0) {
                if (Pat.Pattern[i] == text[h]) {
                    if (i == 0) {
                        entry(newLines, k, n, line);
                        M[k-1] = n;
                        boyer_move(Pat, text, n, k, h, i, true);
                        break;
                    } else {
                        i--;
                        h--;
                    }
                } else {
                    M[k-1] = k - h -1;
                    boyer_move(Pat, text, n, k, h, i, false);
                    break;
                }
            } else if (M[h] < Pat.N[i]) {
                i -= M[h];
                h -= M[h];
            } else if (M[h] >= Pat.N[i] && Pat.N[i] >= i) {
                entry(newLines, k, n, line);
                M[k-1] = k-1 - h;
                boyer_move(Pat, text, n, k, h, i, true);
                break;
            } else if (M[h] > Pat.N[i] && Pat.N[i] < i) {
                M[k-1] = k - h -1;
                h -= Pat.N[i];
                i -= Pat.N[i];
                boyer_move(Pat, text, n, k, h, i, false);
                break;
            } else if (M[h] == Pat.N[i] && Pat.N[i] < i) {
                i -= M[h];
                h -= M[h];
            }
        }
    }
}