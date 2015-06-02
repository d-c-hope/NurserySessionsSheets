#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <list>
#include <pagenavigator.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, PageNavigator
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStackedWidget* stackedWidget;
    std::list<QWidget*> windows;
    void goToPage(std::string name);
    void goBack();
};

#endif // MAINWINDOW_H
