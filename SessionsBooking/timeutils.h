#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <string>
#include <chrono>

namespace TimeUtils {

    std::string timePointDateToString(std::chrono::system_clock::time_point date);
}

#endif // TIMEUTILS_H
