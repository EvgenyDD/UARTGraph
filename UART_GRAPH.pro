
QT += widgets
QT += svg
QTPLUGIN += windowsprintersupport

greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets serialport
} else {
    include($$QTSERIALPORT_PROJECT_ROOT/src/serialport/qt4support/serialport.prf)
}

TARGET       = UART_Graph

include(C:/Qt/QWT/qwt.pri)

HEADERS += curvedata.h \
    mainwindow.h \
    plot.h

SOURCES += \
    main.cpp \
    plot.cpp \
    mainwindow.cpp

FORMS +=
