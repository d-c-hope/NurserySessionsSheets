#ifndef APPUTILS_H
#define APPUTILS_H

#include <sstream>
#include <vector>

namespace AppUtils
{
template<class T>
    std::string  join(std::vector<T> array, std::string separator=" ") {

        std::stringstream joinedValues;

        for (auto value: array) {
            joinedValues << value << separator;
        }
        //Strip off the trailing comma
        std::string result = joinedValues.str().substr(0,joinedValues.str().size()-separator.size());
        return result;

    }

}

#endif // APPUTILS_H
