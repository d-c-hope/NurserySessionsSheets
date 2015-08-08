#include "monthrange.h"

MonthRange::MonthRange()
{
}


MonthRange::MonthRange(int startMonth, int endMonth, int startYear, int endYear) {
    this->startMonth = startMonth;
    this->endMonth = endMonth;
    this->startYear = startYear;
    this->endYear = endYear;
}
