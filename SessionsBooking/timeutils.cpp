#include "timeutils.h"
#include <sstream>
#include <chrono>
#include <iomanip>



namespace TimeUtils {

    std::string  timePointDateToString(std::chrono::system_clock::time_point date) {
        std::stringstream s;
        std::time_t dateT = std::chrono::system_clock::to_time_t(date);
        s << std::put_time(std::localtime(&dateT), "%d/%m/%Y");
        return s.str();
    }


}
