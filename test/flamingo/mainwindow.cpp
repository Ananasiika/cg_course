#include "mainwindow.h"
#include "objects.h"
#include "light.h"
#include "object.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFileDialog>
#include <QPainter>
#include <unistd.h>
#include <QTimer>
#include <QtCore/QTime>
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QGraphicsScene *scene = new QGraphicsScene();
  ui->graphicsView->setScene(scene);
  ui->graphicsView->scene()->clear();
  objs.set_size(ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
  const char *c_str = "/home/larisa/cg_course/flamingo.obj";
  if (!objs.load_file(c_str))
      return;
  text_edit_default();
}

MainWindow::~MainWindow() {
  delete ui->graphicsView->scene();
  delete ui;
}

int checkCoef(const QString& str) {
    bool ok;
    double number = str.toDouble(&ok);

    if (!ok || number < 0 || number > 1) {
        QMessageBox::critical(nullptr, "Ошибка", "Введено некорректное число!");
    }
    return ok;
}

int checkCoord(const QString& str) {
    bool ok;
    double number = str.toDouble(&ok);

    if (!ok) {
        QMessageBox::critical(nullptr, "Ошибка", "Введено некорректное число!");
    }
    return ok;
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

    QPalette palette_4 = ui->flam_x->palette();
    palette.setColor(QPalette::Text, Qt::gray);
    ui->flam_x->setPalette(palette);
    ui->flam_x->setText("x");

    QPalette palette_5 = ui->flam_y->palette();
    palette_2.setColor(QPalette::Text, Qt::gray);
    ui->flam_y->setPalette(palette_2);
    ui->flam_y->setText("y");

    QPalette palette_3 = ui->textEdit_3->palette();
    palette_3.setColor(QPalette::Text, Qt::gray);
    ui->textEdit_3->setPalette(palette_3);
    ui->textEdit_3->setText("z");
}

void MainWindow::on_pushButton_2_clicked()
{
    if (!run && !paint)
    {
        paint = 1;
        objs.delete_lights();
        light ls = light({150, 500, 700}, 0.5);
        objs.add_light(ls);
        objs.add_flamingo_coord(50, -220);
        objs.add_flamingo_coord(-240, -200);
        for (int j = 225; j < 226; j += 1)
        {
            objs.delete_objects();

            for (size_t fi = 0; fi < objs.get_count_flamingos(); fi++)
                objs.add_flamingo(j + objs.get_coord_flamingo(fi)[0], objs.get_coord_flamingo(fi)[1]);
            std::shared_ptr<QImage> _image = objs.draw();

            QPixmap pixmap = QPixmap::fromImage(*_image);
            ui->graphicsView->scene()->addPixmap(pixmap);
            QPixmap scenePixmap(ui->graphicsView->scene()->sceneRect().size().toSize());
            QPainter painter(&scenePixmap);
            ui->graphicsView->scene()->render(&painter);

            scenePixmap.save(QString("../photos/screenshot_%1.png").arg(j));
            paint = 1;
        }
    }
}

void MainWindow::time_measure() {
    int iterations = 25;
    std::cout << "Количество фламинго    Время" << std::endl;
    objs.delete_lights();
    light ls = light({800, 500, 800}, 0.5);
    objs.add_light(ls);

    std::chrono::time_point<std::chrono::system_clock> time_start, time_end;
    double res_time = 0;
    for (int o = 0; o < 15; o++)
        objs.add_flamingo_coord(o * 20 - 120, o * 20 - 490);
    for (int i = 1; i < 15; i++)
    {
        objs.delete_objects();
        for (int j = 0; j <= i; j++)
            objs.add_flamingo(150 + objs.get_coord_flamingo(j)[0], objs.get_coord_flamingo(j)[1]);

        for (int j = 0; j < iterations; j++)
        {
            time_start = std::chrono::system_clock::now();

            std::shared_ptr<QImage> _image = objs.draw();
            QPixmap pixmap = QPixmap::fromImage(*_image);
            ui->graphicsView->scene()->clear();
            ui->graphicsView->scene()->addPixmap(pixmap);


            time_end = std::chrono::system_clock::now();

            res_time += (std::chrono::duration_cast<std::chrono::milliseconds>
            (time_end - time_start).count());
        }

        res_time /= iterations;
        // std::cout << i << "   " << res_time << std::endl;
        std::cout  << res_time << ", " << std::endl;
    }

    std::cout << "Количество источников    Время" << std::endl;
    objs.delete_lights();
    objs.delete_objects();

    for (int i = 1; i <= 2; i++)
    {
        objs.add_flamingo(150 + objs.get_coord_flamingo(i)[0], objs.get_coord_flamingo(i)[1]);
    }
    for (int i = 1; i <= 10; i ++)
    {
        light ls1 = light(QVector3D(float(300 + i * 10), float(300 + i * 20), 500), 0.1 * i - 0.05);
        objs.add_light(ls1);
        for (int j = 0; j < iterations; j++)
        {
            time_start = std::chrono::system_clock::now();

            std::shared_ptr<QImage> _image = objs.draw();
            QPixmap pixmap = QPixmap::fromImage(*_image);
            ui->graphicsView->scene()->clear();
            ui->graphicsView->scene()->addPixmap(pixmap);

            time_end = std::chrono::system_clock::now();

            res_time += (std::chrono::duration_cast<std::chrono::milliseconds>
            (time_end - time_start).count());
        }

        res_time /= iterations;
        // std::cout << i << "   " << res_time << std::endl;
        std::cout  << res_time << ", " << std::endl;
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString qx = ui->textEdit->toPlainText();
    QString qy = ui->textEdit_2->toPlainText();
    QString qz = ui->textEdit_3->toPlainText();
    if (qx == "x" || qy == "y" || qz == "z")
    {
        QMessageBox::critical(nullptr, "Ошибка", "Координата не введена!");
        return;
    }
    if (checkCoord(qx) || checkCoord(qy) || checkCoord(qz))
        return;
    light l = light({qx.toFloat(), qy.toFloat(), qz.toFloat()}, 0.3);
    objs.add_light(l);
    std::shared_ptr<QImage> _image = objs.draw();
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

void MainWindow::on_flam_x_selectionChanged()
{
    if (ui->flam_x->toPlainText() == "x")
    {
        QPalette palette = ui->flam_x->palette();
        palette.setColor(QPalette::Text, Qt::black);
        ui->flam_x->setPalette(palette);
        ui->flam_x->clear();
    }

}

void MainWindow::on_flam_y_selectionChanged()
{
    if (ui->flam_y->toPlainText() == "y")
    {
        QPalette palette = ui->flam_y->palette();
        palette.setColor(QPalette::Text, Qt::black);
        ui->flam_y->setPalette(palette);
        ui->flam_y->clear();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint viewPos = event->pos();
    std::cout << viewPos.x() - 140 << " " << viewPos.y() - 10 << std::endl;
}

void MainWindow::on_video_clicked()
{
    objs.delete_lights();
    light ls = light({150, 500, 600}, 0.5);
    objs.add_light(ls);
    //light ls1 = light({350, 800, 600}, 0.1);
    //objs.add_light(ls1);

    if (!paint && !run)
    {
        objs.add_flamingo_coord(0, -490);
        objs.add_flamingo_coord(-120, -200);
    }
    run = 1;

    int frameIndex = 150;

    if (timer != nullptr) {
        timer->start();
    } else {

        timer = new QTimer(this);

        connect(timer, &QTimer::timeout, [this, frameIndex]() mutable {
            objs.delete_objects();

            for (size_t fi = 0; fi < objs.get_count_flamingos(); fi++)
                objs.add_flamingo(frameIndex + objs.get_coord_flamingo(fi)[0], objs.get_coord_flamingo(fi)[1]);
            std::shared_ptr<QImage> _image = objs.draw();
            QPixmap pixmap = QPixmap::fromImage(*_image);
            ui->graphicsView->scene()->clear();
            ui->graphicsView->scene()->addPixmap(pixmap);

            if (frameIndex < 800) {
                frameIndex += 1;
            } else {
                frameIndex = 800;
                disconnect(timer, &QTimer::timeout, nullptr, nullptr);
            }
        });

        timer->start(10);
    }
    run = 1;
}


void MainWindow::on_add_flam_clicked()
{
    QString qx = ui->flam_x->toPlainText();
    QString qy = ui->flam_y->toPlainText();
    if (qx == "x" || qy == "y")
    {
        QMessageBox::critical(nullptr, "Ошибка", "Одна из координат не введена!");
        return;
    }
    if (!checkCoord(qx) || !checkCoord(qy))
    {
        QMessageBox::critical(nullptr, "Ошибка", "Одна из координат введена неверно!");
        return;
    }
    objs.add_flamingo_coord(-300 + qx.toFloat(), -qy.toFloat());
    qDebug() << "Фламинго добавлено!";
}

// остановка видео
void MainWindow::on_pushButton_3_clicked()
{
    if (timer != nullptr) {
        timer->stop();
    }
}

// установка плотности растительности
void MainWindow::on_pushButton_4_clicked()
{
    objs.delete_plant();
    QString p = ui->plant->toPlainText();
    if (!checkCoef(p))
        return;
    objs.set_density_plant(p.toDouble());
    objs.generate_plant();
}

// установка коэффициентов
void MainWindow::on_pushButton_5_clicked()
{
    QString scat = ui->scattered->toPlainText();
    QString dif = ui->diffuse->toPlainText();
    QString spec = ui->specular->toPlainText();
    QString tran = ui->transmission->toPlainText();
    QString ref = ui->refractive->toPlainText();
    if ((scat != "" && !checkCoef(scat)) || (dif != "" && !checkCoef(dif)) || \
            (spec != "" && !checkCoef(spec)) || (tran != "" && !checkCoef(tran)) || \
            (ref != "" && !checkCoef(ref)))
        return;
    objs.set_factors(scat, dif, spec, tran, ref);
}

