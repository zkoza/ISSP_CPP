#ifndef FIGURA_H
#define FIGURA_H

#include <string>
#include <QPainter>
#include <QDebug>

class Figura
{
public:
    Figura(double x, double y, double s)
        : xc(x), yc(y), scale(s)
    { }


    virtual void draw(QPainter & )
    {
        qDebug() << "w funkcji" << __func__;
    }

    virtual ~Figura() { qDebug() << "deleting a Figure"; }

protected:
    double xc;
    double yc;
    double scale;
};


class Kolo : public Figura
{
public:
    Kolo (double x, double y, double s = 10)
        : Figura(x, y, s)
    {  }

    void draw(QPainter & painter);
};



class Litera : public Figura
{
public:
    Litera (double x, double y, double s = 10, char c = 'X')
        : Figura(x, y, s), litera(c)
    {  }

    void draw(QPainter & painter);

private:
    char litera;
};



#endif // FIGURA_H
