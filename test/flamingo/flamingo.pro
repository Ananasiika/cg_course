QT       += core gui

QT += widgets

CONFIG += c++11
#QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage




# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    drawer.cpp \
    light.cpp \
    main.cpp \
    mainwindow.cpp \
    object.cpp \
    objects.cpp \
    polygon.cpp \
    unit_tests.cpp

HEADERS += \
    drawer.h \
    light.h \
    mainwindow.h \
    object.h \
    objects.h \
    polygon.h \
    unit_tests.h

FORMS += \
    mainwindow.ui

LIBS += -lgtest -lgtest_main #-lgcov --coverage

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
