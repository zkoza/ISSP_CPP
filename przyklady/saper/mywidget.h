#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QStatusBar>
#include <QProgressBar>
#include <QLabel>

class MyWidget : public QWidget
{
    Q_OBJECT

    enum {eBomb = 10};

    int _L;
    int _N;
    int _NBombs;
    int _x0;
    int _y0;
    int _bombs;
    QLabel * _sb_label;
    QProgressBar * _sb_progress;
    QStatusBar * _statusBar;
    QVector<QVector<bool> > _visible;
    QVector<QVector<int> > _neighbours;

    void _przelicz_geometrie(int w, int h);


public:
    explicit MyWidget(QWidget *parent = 0);
    void setStatusBar(QStatusBar* sb);
    void init(int n);

    ~MyWidget();

signals:

public slots:

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *ev);
    virtual void resizeEvent(QResizeEvent *ev);
};

#endif // MYWIDGET_H
