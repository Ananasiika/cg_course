#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include "drawer.h"

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

private:
  void text_edit_default();
  Ui::MainWindow *ui;
  drawer s;
  std::shared_ptr<QImage> _image;
  bool flag = 0;

};
#endif // MAINWINDOW_H
