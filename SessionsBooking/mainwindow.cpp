#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "childlistform.h"
#include "newchildform.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stackedWidget = ui->stackedWidget;
    QWidget* w1 = stackedWidget->currentWidget();
    stackedWidget->removeWidget(w1);
    QWidget* w2 = stackedWidget->currentWidget();
    stackedWidget->removeWidget(w2);
    std::cout << "Count" << stackedWidget->count() << std::endl;
    QWidget* clForm = new ChildListForm(this, this);
    stackedWidget->addWidget(clForm);
//    setCentralWidget(clForm);
//    windows.push_back(clForm);
    auto lastWidget = windows.back();
    int i = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::goToPage(std::string name) {
    if (name == "new_child") {
//        auto lastWidget = windows.back();
//        lastWidget->deleteLater();
        QWidget* ncForm = new NewChildForm(this, this);


        stackedWidget->addWidget(ncForm);
        stackedWidget->setCurrentIndex(stackedWidget->count()-1);
//        setCentralWidget(ncForm);

//        windows.push_back(ncForm);
//        auto lastWidget2 = windows.front();
//        auto lastWidget3 = windows.back();
//        int i = windows.size();
//        int g = 8;
    }
}


void MainWindow::goBack() {
    int i = windows.size();
    if (stackedWidget->count() > 1) {
        stackedWidget->removeWidget(stackedWidget->currentWidget());
//        stackedWidget->setCurrentIndex(stackedWidget->count()-1);



//        auto lastWidget = windows.back();
//        auto widget2 = windows.front();
////        auto lastWidget2 = windows.back()-1;
//        windows.pop_back();
//        auto secondLastWidget = windows.back();
//        setCentralWidget(secondLastWidget);

//        delete lastWidget;
    }
}






