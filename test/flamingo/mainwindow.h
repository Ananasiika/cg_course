#pragma once

#include <QMainWindow>
#include <QMouseEvent>
#include "objects.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();


private slots:
  void on_pushButton_2_clicked();

  void on_pushButton_clicked();

  void on_textEdit_selectionChanged();

  void on_textEdit_2_selectionChanged();

  void on_textEdit_3_selectionChanged();

  void mousePressEvent(QMouseEvent *event);

  void on_video_clicked();

  void on_add_flam_clicked();

  void on_flam_x_selectionChanged();

  void on_flam_y_selectionChanged();

  void on_pushButton_3_clicked();

  void on_pushButton_4_clicked();

  void on_pushButton_5_clicked();

  void time_measure();
private:
  void text_edit_default();
  Ui::MainWindow *ui;
  objects objs;
  bool run = 0, paint = 0;
  QTimer* timer;

};
