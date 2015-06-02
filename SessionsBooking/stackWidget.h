#ifndef STACKWIDGET_H
#define STACKWIDGET_H

#include <QWidget>
#include <string>

namespace Ui {
class StackWidget;
}

class StackWidget : public QWidget
{
    Q_OBJECT

public:
    StackWidget(QWidget *parent);
    std::string name;

};

#endif // STACKWIDGET_H
