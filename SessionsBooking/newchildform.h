#ifndef NEWCHILDFORM_H
#define NEWCHILDFORM_H

#include <QWidget>
#include <pagenavigator.h>

namespace Ui {
class NewChildForm;
}

class NewChildForm : public QWidget
{
    Q_OBJECT

public:
    explicit NewChildForm(QWidget *parent = 0, PageNavigator* _nav = nullptr);
    ~NewChildForm();
    std::vector<int> getYears();
    void createChild();

public slots:
    void onGoBackClicked();

private:
    Ui::NewChildForm *ui;
    PageNavigator* navigator;
};

#endif // NEWCHILDFORM_H
