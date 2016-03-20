#include "mywidget.h"

#include <ctime>
#include <QtDebug>
#include <QPainter>
#include <qdrawutil.h>
#include <QMouseEvent>
#include <QMessageBox>
#include <QLabel>
#include <QProgressBar>

void MyWidget::init(int n)
{
    if (n != 8 && n != 20)
        return;
    _N = n;
    _NBombs = (_N == 8) ? 10 : 80;
    _visible.clear();
    _neighbours.clear();

    _visible.resize(_N);
    _neighbours.resize(_N);
    for (int i = 0; i < _N; i++)
    {
       _visible[i].resize(_N);
       _neighbours[i].resize(_N);
    }
    for (int i = 0; i < _NBombs; i++)
    {
        bool ok = false;
        while(!ok)
        {
            int x = qrand() % _N;
            int y = qrand() % _N;
            if (_N >= 10)
            {
                if (x == 0 && y == 0)
                    continue;
                if (x == _N - 1 && y == _N - 1)
                    continue;
                if (x == 0 && y == _N - 1)
                    continue;
                if (x == _N - 1 && y == 0)
                    continue;
            }

            ok = _neighbours[x][y] != eBomb;
            if (ok)
            {
                _neighbours[x][y] = eBomb;
              //  qDebug() << i << x << y;
            }
        }
    }

    for (int i = 0; i < _N; i++)
    {
        for (int j = 0; j < _N; j++)
        {
            if (_neighbours[i][j] == eBomb)
                continue;
            for (int n = -1; n <= 1; n++)
            {
                for (int m = -1; m <= 1; m++)
                {
                    int ii = i + n;
                    int jj = j + m;
                    if (ii < 0 or jj < 0 or ii >= _N or jj >= _N)
                        continue;
                    if (_neighbours[ii][jj] == eBomb)
                        _neighbours[i][j]++;

                }
            }
        }
    }
    _przelicz_geometrie(rect().width(), rect().height());
    _bombs = 0;
    setStatusTip("");
    if (_sb_progress)
    {
        _sb_progress->setMaximum(_NBombs);
        _sb_progress->setValue(0);
        QString s;
        if (_NBombs < 100)
            s = "QProgressBar {margin-right:35px; text-align: right;} QProgressBar::chunk {background-color: green; margin: 2 px;} ";
        else
            s = "QProgressBar {margin-right:45px; text-align: right;} QProgressBar::chunk {background-color: green; margin: 2 px;} ";
        _sb_progress->setStyleSheet(s);
    }
}

void MyWidget::_przelicz_geometrie(int w, int h)
{
    const int margin = 2;
    h -= margin;
    w -= margin;
    _L = qMin(h/_N, w/_N);
    _x0 = margin + (w - _N*_L)/2;
    _y0 = margin + (h - _N*_L)/2;
}

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent),
      _sb_progress(0),
      _statusBar(0)
{
    qsrand(time(0));
    init(8);
}

void MyWidget::setStatusBar(QStatusBar *sb)
{
    _statusBar = sb;
  //  _sb_label = new QLabel("00:00", this);
    _sb_progress = new QProgressBar(this);
    _sb_progress->setMaximum(_NBombs);
    _sb_progress->setFormat("%v/%m");
    _sb_progress->setTextVisible(true);
    _sb_progress->setValue(0);

    QString s;
    s = "QProgressBar {margin-right:35px; text-align: right;} QProgressBar::chunk {background-color: green; margin: 2 px;} ";

    _sb_progress->setStyleSheet(s);
  //  _statusBar->addPermanentWidget(_sb_label);
    _statusBar->addPermanentWidget(_sb_progress);

}

MyWidget::~MyWidget()
{

}

void MyWidget::paintEvent(QPaintEvent *)
{
    const QColor kolor[11] = {"white", "black", "blue", "green", "magenta", "orange", "cyan", "", "", "", "red"};

    QPainter painter(this);

    QFont font("Arial", _L*3/5, 75);
    painter.setFont(font);


    for (int i = 0; i < _N; i++)
    {
        for (int j = 0; j < _N; j++)
        {
            const int n = _neighbours[i][j];
            QString s("0");

            if (n == eBomb)
                s[0] = 'B';
            else
                s[0] = char('0' + n);

            qDrawShadePanel(&painter, _x0+ i*_L, _y0 +  j*_L, _L, _L, palette(),_visible[i][j], 2);
            if (_visible[i][j]  && n > 0)
            {
                painter.setPen(kolor[n]);
                if (n == eBomb)
                {
                    painter.setBrush(QColor("lightgreen"));
                    painter.drawRect(_x0 + i*_L, _y0 + j*_L, _L, _L);
                }
                painter.drawText(_x0 + i*_L, _y0 + j*_L, _L, _L, Qt::AlignCenter, s);
            }
          //  painter.drawRect(i*_L, j*_L, _L, _L);
        }
    }
}

void MyWidget::mousePressEvent(QMouseEvent * ev)
{
    Qt::MouseButton button = ev->button();
    bool left_button = button == Qt::LeftButton;
    bool right_button = button == Qt::RightButton;
    if (!left_button && !right_button)
        return;

    QPoint point = ev->pos();
    int i = (point.x() - _x0)/_L;
    int j = (point.y() - _y0)/_L;

    if (_N > 10 && _bombs == 0 && _neighbours[i][j] == eBomb)
    {
      right_button = true;
      left_button = false;
      _statusBar->showMessage("Pierwsza mina - atrapa!", 2000);
    }
//    qDebug() << point << i << j << _bombs << _N;
    if (i < _N && j < _N && i >= 0 && j >= 0)
    {
        if (_visible[i][j])
            return;
        _visible[i][j] = true;
        if (right_button)
        {
            _bombs++;
            if (_neighbours[i][j] == eBomb)
            {
                _sb_progress->setValue(_bombs);
                if (_bombs == _NBombs)
                {
                    for (int i = 0; i < _N; i++)
                    {
                        for (int j = 0; j < _N; j++)
                            _visible[i][j] = true;
                    }
                    QMessageBox::information(this, "Koniec gry", "Zwycięstwo!", QMessageBox::Ok);
                    setStatusTip("Zwycięstwo!");
                    return;
                }
            }
        }
    }
    else
        return;



    if ((_neighbours[i][j] == eBomb && left_button) or (right_button && _neighbours[i][j] != eBomb))
    {
        for (int i = 0; i < _N; i++)
        {
            for (int j = 0; j < _N; j++)
                _visible[i][j] = true;
        }
        // koniec pieśni
        QString s = left_button ? "Bomba!" : "Tu nie ma bomby";
        QMessageBox::information(this, "koniec gry", s, QMessageBox::Ok);
        setStatusTip(s);
    }
    if (_neighbours[i][j] == 0)
    {
        QVector <QPair<int, int> > v;
        v.push_back(QPair<int, int>(i, j));
        while(!v.empty())
        {
            QPair<int, int> para = v.back();
            int i = para.first;
            int j = para.second;
            v.pop_back();
            _visible[i][j] = true;
            if (_neighbours[i][j] != 0)
                continue;
            for (int n = -1; n <= 1; n++)
            {
                for (int m = -1; m <= 1; m++)
                {
                    int ii = i + n;
                    int jj = j + m;
                    if (ii < 0 or jj < 0 or ii >= _N or jj >= _N)
                        continue;
                    if (!_visible[ii][jj])
                    {
                        _visible[ii][jj] = true;
                        v.push_back(QPair<int, int>(ii, jj));
                    }
                }
            }
        }
    }

    repaint();

}



void MyWidget::resizeEvent(QResizeEvent * ev)
{

    _przelicz_geometrie(ev->size().width(), ev->size().height());
}
