#include<QPainter>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralWidget->setStatusBar(statusBar());
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_action_Koniec_triggered()
{
    QMessageBox::StandardButton butt = QMessageBox::question(this, tr("Koniec programu?"), tr("Czy zakończyć program?"), QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    if (butt == QMessageBox::Yes)
        qApp->quit();
}

void MainWindow::on_action8x8_triggered()
{
    ui->centralWidget->init(8);
    repaint();
}

void MainWindow::on_action20x20_triggered()
{
    ui->centralWidget->init(20);
    repaint();
}

void MainWindow::on_action_O_programie_triggered()
{
    QMessageBox::about(this,"saper","Program demonstracyjny");
}

void MainWindow::on_actionO_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}
