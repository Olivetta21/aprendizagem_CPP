#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Função para calcular a distância Jaro entre duas strings
double jaro(const std::string& s1, const std::string& s2) {
    size_t len1 = s1.size();
    size_t len2 = s2.size();

    if (len1 == 0 && len2 == 0) return 1.0;
    if (len1 == 0 || len2 == 0) return 0.0;

    size_t matchDistance = std::max(len1, len2) / 2 - 1;

    std::vector<bool> s1Matches(len1, false);
    std::vector<bool> s2Matches(len2, false);

    size_t matches = 0;
    size_t transpositions = 0;

    // Contando as correspondências
    for (size_t i = 0; i < len1; ++i) {
        size_t start = i >= matchDistance ? i - matchDistance : 0;
        size_t end = std::min(i + matchDistance + 1, len2);
        for (size_t j = start; j < end; ++j) {
            if (s2Matches[j]) continue;
            if (s1[i] != s2[j]) continue;
            s1Matches[i] = true;
            s2Matches[j] = true;
            ++matches;
            break;
        }
    }

    if (matches == 0) return 0.0;

    // Contando as transposições
    size_t k = 0;
    for (size_t i = 0; i < len1; ++i) {
        if (!s1Matches[i]) continue;
        while (!s2Matches[k]) ++k;
        if (s1[i] != s2[k]) ++transpositions;
        ++k;
    }

    transpositions /= 2;

    return ((matches / (double)len1) +
            (matches / (double)len2) +
            ((matches - transpositions) / (double)matches)) / 3.0;
}
// Função para converter string para minúsculas
std::string toLower(const std::string& str) {
    std::locale loc;
    std::string result;
    for (char ch : str) {
        result += std::tolower(ch, loc);
    }
    return result;
}

// Função para remover espaços extras
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
        return str;
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}
// Função para calcular a distância Jaro-Winkler entre duas strings
double jaroWinkler(const std::string& ss1, const std::string& ss2) {
    std::string s1 = toLower(ss1);
    std::string s2 = toLower(ss2);
    s1 = trim(s1);
    s2 = trim(s2);

    double jaroDist = jaro(s1, s2);

    // Prefixo de comprimento máximo para a correção de Winkler
    const double prefixScale = 0.1;
    const size_t prefixLength = 4;

    size_t commonPrefix = 0;
    for (size_t i = 0; i < std::min({s1.size(), s2.size(), prefixLength}); ++i) {
        if (s1[i] == s2[i]) {
            ++commonPrefix;
        } else {
            break;
        }
    }

    return jaroDist + (commonPrefix * prefixScale * (1 - jaroDist));
}

int main() {
    std::string name1 = "Joaozinho Da silva Pereira";
    std::string name2 = "Joao S Pereira";

    while (1){
    std::cout << "\n-------------------------------------\nNome 1: ";
    std::getline(std::cin, name1);
    std::cout << "\nNome 2: ";
    std::getline(std::cin, name2);

    double similarity = jaroWinkler(name1, name2);
    std::cout << "D: " << similarity;
    }

    return 0;
}
