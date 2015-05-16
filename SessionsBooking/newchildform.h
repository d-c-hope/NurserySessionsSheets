#ifndef NEWCHILD_H
#define NEWCHILD_H

#include <QWidget>

namespace Ui {
class NewChild;
}

class NewChild : public QWidget
{
    Q_OBJECT

public:
    explicit NewChild(QWidget *parent = 0);
    ~NewChild();

private:
    Ui::NewChild *ui;
};

#endif // NEWCHILD_H
