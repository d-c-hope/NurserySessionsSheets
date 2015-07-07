#include "childWeeklySessions.h"
#include "timeutils.h"


ChildWeeklySessions::ChildWeeklySessions()
{
    sessionsList = {};
    endDate = TimeUtils::dateToTimePoint(1, 1, 2100);
}
