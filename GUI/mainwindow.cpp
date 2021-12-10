#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGridLayout>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGridLayout* layout = new QGridLayout(); //stack overflow
    ui->centralwidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
