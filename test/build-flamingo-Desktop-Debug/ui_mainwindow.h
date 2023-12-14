/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QPushButton *pushButton_2;
    QPushButton *video;
    QPushButton *pushButton_3;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QTextEdit *textEdit_3;
    QPushButton *pushButton;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *flam_x;
    QTextEdit *flam_y;
    QPushButton *add_flam;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *plant;
    QPushButton *pushButton_4;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QTextEdit *scattered;
    QLabel *label_2;
    QTextEdit *diffuse;
    QLabel *label_3;
    QTextEdit *specular;
    QLabel *label_4;
    QTextEdit *transmission;
    QLabel *label_5;
    QTextEdit *refractive;
    QPushButton *pushButton_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1271, 958);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(230, 10, 1031, 911));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(30, 20, 171, 41));
        video = new QPushButton(centralwidget);
        video->setObjectName(QString::fromUtf8("video"));
        video->setGeometry(QRect(30, 70, 171, 41));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(30, 120, 171, 41));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(30, 180, 171, 131));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        textEdit = new QTextEdit(verticalLayoutWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout->addWidget(textEdit);

        textEdit_2 = new QTextEdit(verticalLayoutWidget);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));

        verticalLayout->addWidget(textEdit_2);

        textEdit_3 = new QTextEdit(verticalLayoutWidget);
        textEdit_3->setObjectName(QString::fromUtf8("textEdit_3"));

        verticalLayout->addWidget(textEdit_3);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(30, 330, 173, 111));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        flam_x = new QTextEdit(verticalLayoutWidget_2);
        flam_x->setObjectName(QString::fromUtf8("flam_x"));

        verticalLayout_2->addWidget(flam_x);

        flam_y = new QTextEdit(verticalLayoutWidget_2);
        flam_y->setObjectName(QString::fromUtf8("flam_y"));

        verticalLayout_2->addWidget(flam_y);

        add_flam = new QPushButton(verticalLayoutWidget_2);
        add_flam->setObjectName(QString::fromUtf8("add_flam"));

        verticalLayout_2->addWidget(add_flam);

        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(30, 460, 171, 81));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        plant = new QTextEdit(verticalLayoutWidget_3);
        plant->setObjectName(QString::fromUtf8("plant"));

        verticalLayout_3->addWidget(plant);

        pushButton_4 = new QPushButton(verticalLayoutWidget_3);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        verticalLayout_3->addWidget(pushButton_4);

        verticalLayoutWidget_4 = new QWidget(centralwidget);
        verticalLayoutWidget_4->setObjectName(QString::fromUtf8("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(30, 560, 171, 361));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget_4);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_4->addWidget(label);

        scattered = new QTextEdit(verticalLayoutWidget_4);
        scattered->setObjectName(QString::fromUtf8("scattered"));

        verticalLayout_4->addWidget(scattered);

        label_2 = new QLabel(verticalLayoutWidget_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_4->addWidget(label_2);

        diffuse = new QTextEdit(verticalLayoutWidget_4);
        diffuse->setObjectName(QString::fromUtf8("diffuse"));

        verticalLayout_4->addWidget(diffuse);

        label_3 = new QLabel(verticalLayoutWidget_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_4->addWidget(label_3);

        specular = new QTextEdit(verticalLayoutWidget_4);
        specular->setObjectName(QString::fromUtf8("specular"));

        verticalLayout_4->addWidget(specular);

        label_4 = new QLabel(verticalLayoutWidget_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_4->addWidget(label_4);

        transmission = new QTextEdit(verticalLayoutWidget_4);
        transmission->setObjectName(QString::fromUtf8("transmission"));

        verticalLayout_4->addWidget(transmission);

        label_5 = new QLabel(verticalLayoutWidget_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_4->addWidget(label_5);

        refractive = new QTextEdit(verticalLayoutWidget_4);
        refractive->setObjectName(QString::fromUtf8("refractive"));

        verticalLayout_4->addWidget(refractive);

        pushButton_5 = new QPushButton(verticalLayoutWidget_4);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        verticalLayout_4->addWidget(pushButton_5);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1271, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\200\320\270\321\201\320\276\320\262\320\260\321\202\321\214", nullptr));
        video->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214 \320\262\320\270\320\264\320\265\320\276", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\320\236\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \320\262\320\270\320\264\320\265\320\276", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\201\320\262\320\265\321\202", nullptr));
        add_flam->setText(QCoreApplication::translate("MainWindow", "\320\264\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \n"
"\321\204\320\273\320\260\320\274\320\270\320\275\320\263\320\276", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \320\277\320\273\320\276\321\202\320\275\320\276\321\201\321\202\321\214 \n"
"\321\200\320\260\321\201\321\202\320\270\321\202\320\265\320\273\321\214\320\275\320\276\321\201\321\202\320\270", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\321\200\320\260\321\201\321\201\320\265\321\217\320\275\320\276\320\265 \320\276\321\202\321\200\320\260\320\266\320\265\320\275\320\270\320\265:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\264\320\270\321\204\321\204\321\203\320\267\320\275\320\276\320\265 \320\276\321\202\321\200\320\260\320\266\320\265\320\275\320\270\320\265:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\267\320\265\321\200\320\272\320\260\320\273\321\214\320\275\320\276\320\265 \320\276\321\202\321\200\320\260\320\266\320\265\320\275\320\270\321\217:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\277\321\200\320\276\320\277\321\203\321\201\320\272\320\260\320\275\320\270\320\265:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\277\321\200\320\265\320\273\320\276\320\274\320\273\320\265\320\275\320\270\320\265:", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\321\203\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214\n"
" \320\272\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202\321\213 ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
