#ifndef PAGENAVIGATOR_H
#define PAGENAVIGATOR_H

#include <string>

class PageNavigator
{
public:
//    PageNavigator();
    virtual void goToPage(std::string name) = 0;
    virtual void goBack() = 0;
};

#endif // PAGENAVIGATOR_H
