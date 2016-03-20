#include "figura.h"


void Kolo::draw(QPainter & painter)
{
    double r = this->scale;
    QPointF center (this->xc, this->yc);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor("red")));
    painter.drawEllipse(center, r, r);
}

void Litera::draw(QPainter & painter)
{
    double scale = this->scale;

    QFont font = painter.font();
    font.setPixelSize(2*scale);
    painter.setFont(font);

    double x = this->xc - scale;
    double y = this->yc - scale;
    double width = scale * 2.0;
    double height = scale * 2.0;
    QRectF rect(x, y, width, height);

    painter.setPen(QColor("blue"));
    painter.drawText(rect, Qt::AlignCenter, QString(this->litera));
}
