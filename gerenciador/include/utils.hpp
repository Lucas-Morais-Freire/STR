#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

namespace utils {

inline bool is_uint(const std::string& str) {
    if (str.size() == 0) {
        return false;
    }

    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }

    return true;
}

};

#endif