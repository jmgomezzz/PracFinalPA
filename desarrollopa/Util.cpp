#include "Util.h"
namespace Util{
std::string trim(const std::string& s) {
    auto start = std::find_if_not(s.begin(), s.end(), ::isspace);
    auto end = std::find_if_not(s.rbegin(), s.rend(), ::isspace).base();
    return (start < end ? std::string(start, end) : std::string());
}

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;

    for (char c : s) {
        if (c == delimiter) {
            tokens.push_back(token);
            token.clear();
        }
        else {
            token += c;
        }
    }

    tokens.push_back(token);
    return tokens;
}
}

