#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <unit_tests.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    if (argc > 1 && strcmp(argv[1], "unit") == 0)
        unit_tests(argc, argv);
    w.show();
    return app.exec();
}
