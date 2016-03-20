#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_action_Koniec_triggered();

    void on_action8x8_triggered();

    void on_action20x20_triggered();

    void on_action_O_programie_triggered();

    void on_actionO_Qt_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
