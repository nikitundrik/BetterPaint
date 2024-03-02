#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Magick++.h>
#include <iostream>
#include <vector>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QFileDialog>
#include <QDir>

using namespace std;
using namespace Magick;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void drawSquare(QPainter *qp);
    void saveDialog();
    void loadDialog();
    void saveImage(string filename);
    void loadImage(string filename);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    vector<QPoint> points;
    vector<QColor> colors;
    bool painted;
    QPoint currentPos;
};
#endif // MAINWINDOW_H
