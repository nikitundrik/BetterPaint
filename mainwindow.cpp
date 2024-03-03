#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    InitializeMagick("~/");
    painted = false;
    ui->setupUi(this);
    connect(ui->actionSave, &QAction::triggered, [=]() {
        saveDialog();
    });
    connect(ui->actionLoad, &QAction::triggered, [=]() {
        loadDialog();
    });
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        painted = true;
        currentPos = event->pos();
        points.push_back(currentPos);
        colors.push_back(QColor("red"));
        repaint();
    }
}

void MainWindow::paintEvent(QPaintEvent *event) {
    if (painted) {
        Q_UNUSED(event);

        QPainter qp(this);
        drawSquare(&qp);
    }
}

void MainWindow::drawSquare(QPainter *qp) {
    qp->setBrush(QColor("#ed0602"));
    qp->setPen(QColor("#ed0602"));
    int position = 0;
    for (QPoint i : points) {
        qp->setPen(colors.at(position));
        qp->setBrush(colors.at(position));
        qp->drawRect(i.x(), i.y(), 1, 1);
        position++;
    }
}

void MainWindow::saveDialog() {
    QString filename = QFileDialog::getSaveFileName(this, tr("Save file"),
                                                    "", tr("Image (*.png)"));
    if (!filename.isEmpty()) {
        saveImage(filename.toStdString());
    }
}

void MainWindow::saveImage(string filename) {
    Image savedImg("513x513", "white");
    int colorsPos = 0;
    for (QPoint i : points) {
        QColor currentColor = colors.at(colorsPos);
        savedImg.pixelColor(i.x(), i.y(), ColorRGB(currentColor.red() / 255, currentColor.green() / 255, currentColor.blue() / 255));
        colorsPos++;
    }
    savedImg.write(filename);
}

void MainWindow::loadDialog() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open file"),
                                                    "", tr("Images (*.png)"));
    if (!filename.isEmpty()) {
        loadImage(filename.toStdString());
    }
}

void MainWindow::loadImage(string filename) {
    Image loadedImg = Image();
    loadedImg.read(filename);
    for (int y = 0; y <= 512; y++) {
        for (int x = 0; x <= 512; x++) {
            ColorRGB currentPix = loadedImg.pixelColor(x, y);
            colors.push_back(QColor(currentPix.red() * 255, currentPix.green() * 255, currentPix.blue() * 255));
            points.push_back(QPoint(x, y));
        }
    }
    painted = true;
    repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}
