#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "childlistform.h"
#include "newchildform.h"
#include "editchildform.h"
#include "sessionsform.h"
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
    QWidget* clForm = new ChildListForm(this, this);
    stackedWidget->addWidget(clForm);
    auto lastWidget = windows.back();
    int i = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::goToPage(std::string name) {
    if (name == "new_child") {
        QWidget* ncForm = new NewChildForm(this, this);

        stackedWidget->addWidget(ncForm);
        stackedWidget->setCurrentIndex(stackedWidget->count()-1);
    }
    if (name == "edit_child") {
        ChildListForm* current = dynamic_cast<ChildListForm*>(stackedWidget->currentWidget());
        Child child = current->selectedChild;
        QWidget* ecForm = new EditChildForm(child, this, this);
        stackedWidget->addWidget(ecForm);
        stackedWidget->setCurrentIndex(stackedWidget->count()-1);
    }
    if (name == "sessions") {
        ChildListForm* current = dynamic_cast<ChildListForm*>(stackedWidget->currentWidget());
        Child child = current->selectedChild;
        QWidget* sForm = new SessionsForm(child, this, this);
        stackedWidget->addWidget(sForm);
        stackedWidget->setCurrentIndex(stackedWidget->count()-1);
    }
}


void MainWindow::goBack() {
    int i = windows.size();
    if (stackedWidget->count() > 1) {
        StackWidget * prev = dynamic_cast<StackWidget*>(stackedWidget->widget(stackedWidget->count()-2));
        StackWidget * current = dynamic_cast<StackWidget*>(stackedWidget->currentWidget());
        if (current->name == "new_child"){
            NewChildForm* currentNCF = dynamic_cast<NewChildForm*>(current);
            Child c = currentNCF->getChild();
            ChildListForm* prevConcrete = dynamic_cast<ChildListForm*>(prev);
            if (! currentNCF->isCancelled) prevConcrete->addChild(c);
        }
        else if (current->name == "edit_child"){
            EditChildForm* currentNCF = dynamic_cast<EditChildForm*>(current);
            Child c = currentNCF->getChild();
            Child original = currentNCF->getOriginal();
            bool isDeleted = currentNCF->childIsDeleted;
            ChildListForm* prevConcrete = dynamic_cast<ChildListForm*>(prev);
            prevConcrete->updateChild(original, c, isDeleted);
        }
        else if (current->name == "sessions"){

        }

        stackedWidget->removeWidget(stackedWidget->currentWidget());

    }
}






