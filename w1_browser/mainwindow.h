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
    void on_webView_urlChanged(const QUrl &url);

    void on_lineEdit_editingFinished();

    void on_toolButtonBack_clicked();

    void on_toolButtonForward_clicked();

    void on_toolButtonReload_clicked();

    void on_action_Zako_cz_program_triggered();

    void on_actionO_Qt_triggered();

    void on_action_O_programie_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
