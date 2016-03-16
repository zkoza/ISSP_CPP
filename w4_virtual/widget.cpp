#include <QMouseEvent>
#include <QMessageBox>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
    for (auto x : this->figury)
        delete x;
}

void Widget::paintEvent(QPaintEvent * )
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    auto rect = this->rect();
    painter.translate(rect.width()/2.0, rect.height()/2.0);
    double scale = std::min(rect.width(), rect.height());
    scale /= this->my_effective_widget_size;
    painter.scale(scale, scale);

    for (auto x : this->figury)
        x->draw(painter);
}


void Widget::mousePressEvent(QMouseEvent * event)
{
   auto button = event->button();
   double x = event->x();
   double y = event->y();

   QRect rect = this->rect();
   double width = rect.width();
   double height = rect.height();

   double scale = std::min(width, height);
   scale /= this->my_effective_widget_size;

   x -= width/2.0;
   y -= height/2.0;
   x /= scale;
   y /= scale;

   switch (button)
   {
   case Qt::LeftButton:
       {
           Kolo * kolo = new Kolo(x, y, 10);
           this->figury.push_back(kolo);
           break;
       }
   case Qt::RightButton:
       {
           Litera * kwadrat = new Litera(x, y, 10, this->jaki_znak());
           this->figury.push_back(kwadrat);
           break;
       }
   case Qt::MiddleButton:
       QMessageBox::information(this, "Uwaga!", "Środkowego klawisza jeszcze nie obsługujemy!");
       break;
   case Qt::BackButton:
       QMessageBox::information(this, "Uwaga!", "Gratuluję! Masz mysz z (nieobsługiwanym) klawiszem \"back\"!");
       break;
   default:
       QMessageBox::information(this, "Uwaga!", "Przyciśnięto nieznany przycisk myszy!");

   }
   this->repaint();
}

void Widget::keyPressEvent(QKeyEvent * event)
{
    auto key = event->key();
    if (key == Qt::Key_Backspace)
    {
        if (this->figury.empty())
        {
            QMessageBox::warning(this, "Ostrzeżenie", "Bufor figur jest pusty!");
            return;
        }
        Figura * fig = this->figury.back();
        delete fig;
        figury.pop_back();
        this->repaint();
        return;
    }

    if (not (key >= Qt::Key_A and key <= Qt::Key_Z))
        return;

    this->setKey(key);
}

