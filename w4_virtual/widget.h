#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <figura.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent * event);
    void keyPressEvent(QKeyEvent * event);

    const double my_effective_widget_size = 200.0;

    char jaki_znak() const { return znak; }
private:
    Ui::Widget *ui;
    std::vector<Figura*> figury;
    char znak = 'X';

    void setKey(int k) { znak = 'A' + k - Qt::Key_A; }
};

#endif // WIDGET_H
