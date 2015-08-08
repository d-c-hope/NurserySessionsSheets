#ifndef MONTHRANGE_H
#define MONTHRANGE_H

class MonthRange
{
public:
    MonthRange();
    MonthRange(int startMonth, int endMonth, int startYear, int endYear);

    int startMonth;
    int endMonth;
    int startYear;
    int endYear;
};

#endif // MONTHRANGE_H
