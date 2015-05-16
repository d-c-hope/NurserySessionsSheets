#ifndef CHILDLISTFORM_H
#define CHILDLISTFORM_H

#include <QWidget>

namespace Ui {
class ChildListForm;
}

class ChildListForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChildListForm(QWidget *parent = 0);
    ~ChildListForm();

private:
    Ui::ChildListForm *ui;
};

#endif // CHILDLISTFORM_H
