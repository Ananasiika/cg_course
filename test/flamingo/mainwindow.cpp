#include "mainwindow.h"
#include "drawer.h"
#include "light.h"
#include "flamingo.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFileDialog>
#include <QPainter>
#include <unistd.h>
#include <QTimer>
#include <QtCore/QTime>
#include <QGraphicsScene>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QGraphicsScene *scene = new QGraphicsScene();
  ui->graphicsView->setScene(scene);
  ui->graphicsView->scene()->clear();

  text_edit_default();
}

MainWindow::~MainWindow() {
  delete ui->graphicsView->scene();
  delete ui;
}

void MainWindow::text_edit_default() {
    QPalette palette = ui->textEdit->palette();
    palette.setColor(QPalette::Text, Qt::gray);
    ui->textEdit->setPalette(palette);
    ui->textEdit->setText("x");

    QPalette palette_2 = ui->textEdit_2->palette();
    palette_2.setColor(QPalette::Text, Qt::gray);
    ui->textEdit_2->setPalette(palette_2);
    ui->textEdit_2->setText("y");

    QPalette palette_3 = ui->textEdit_3->palette();
    palette_3.setColor(QPalette::Text, Qt::gray);
    ui->textEdit_3->setPalette(palette_3);
    ui->textEdit_3->setText("z");
}

void MainWindow::on_pushButton_2_clicked()
{
    s.set_size(ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
    flag = 1;
    const char *c_str = "/home/larisa/cg_course/flamingo.obj";
    for (int j = 0; j < 1; j += 1)
    {
        s.delete_flamingos();
        s.delete_lights();

        if (!s.load_file(c_str, j, j * 3 / 4 - 290, 1 - double(j) / 2 / ui->graphicsView->width()))
            return;

        if (!s.load_file(c_str, j - 60, j * 3 / 4, 1 - double(j) / 2 / ui->graphicsView->width()))
            return;

        light ls = light({800, 500, 800}, 0.7);
        s.add_light(ls);
        _image = s.draw();
        QPixmap pixmap = QPixmap::fromImage(*_image);
        ui->graphicsView->scene()->addPixmap(pixmap);
        QPixmap scenePixmap(ui->graphicsView->scene()->sceneRect().size().toSize());
        QPainter painter(&scenePixmap);
        ui->graphicsView->scene()->render(&painter);

        scenePixmap.save(QString("../photos/screenshot_%1.png").arg(j));

    }
}


void MainWindow::on_pushButton_clicked()
{
    QString qx = ui->textEdit->toPlainText();
    QString qy = ui->textEdit_2->toPlainText();
    QString qz = ui->textEdit_3->toPlainText();
    if (qx == "x" || qy == "y" || qz == "z" || !flag)
        return;
    light l = light({qx.toFloat(), qy.toFloat(), qz.toFloat()}, 0.6);
    s.add_light(l);
    _image = s.draw();
    QPixmap pixmap = QPixmap::fromImage(*_image);
    ui->graphicsView->scene()->clear();
    ui->graphicsView->scene()->addPixmap(pixmap);
}


void MainWindow::on_textEdit_selectionChanged()
{
    if (ui->textEdit->toPlainText() == "x")
    {
        QPalette palette = ui->textEdit->palette();
        palette.setColor(QPalette::Text, Qt::black);
        ui->textEdit->setPalette(palette);
        ui->textEdit->clear();
    }

}

void MainWindow::on_textEdit_2_selectionChanged()
{
    if (ui->textEdit_2->toPlainText() == "y")
    {
        QPalette palette = ui->textEdit_2->palette();
        palette.setColor(QPalette::Text, Qt::black);
        ui->textEdit_2->setPalette(palette);
        ui->textEdit_2->clear();
    }
}

void MainWindow::on_textEdit_3_selectionChanged()
{
    if (ui->textEdit_3->toPlainText() == "z")
    {
        QPalette palette = ui->textEdit_3->palette();
        palette.setColor(QPalette::Text, Qt::black);
        ui->textEdit_3->setPalette(palette);
        ui->textEdit_3->clear();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint viewPos = event->pos();
    std::cout << viewPos.x() - 140 << " " << viewPos.y() - 10 << std::endl;
}

