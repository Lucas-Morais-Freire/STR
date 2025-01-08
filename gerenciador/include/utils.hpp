#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

namespace utils {

bool is_uint(const std::string& str) {
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }

    return true;
}

};

#endif