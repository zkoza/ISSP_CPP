#include <QWebHistory>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Moja własna przeglądarka");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_webView_urlChanged(const QUrl &url)
{
    ui->lineEdit->setText(url.toString());
    QWebHistory * phistory = ui->webView->history();
    ui->toolButtonBack->setEnabled(phistory->canGoBack());
    ui->toolButtonForward->setEnabled(phistory->canGoForward());
}

void MainWindow::on_lineEdit_editingFinished()
{
    QString adres = ui->lineEdit->text();
    ui->webView->setUrl(QUrl(adres));
}

void MainWindow::on_toolButtonBack_clicked()
{
    ui->webView->back();
}

void MainWindow::on_toolButtonForward_clicked()
{
    ui->webView->forward();
}

void MainWindow::on_toolButtonReload_clicked()
{
    ui->webView->reload();
}

void MainWindow::on_action_Zako_cz_program_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionO_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_action_O_programie_triggered()
{
    QMessageBox::information(this, "Moja przeglądarka",
                             "<html><span style=\"color:red;\">Piękny</span> program</html>");
}
