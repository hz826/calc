TEMPLATE = app

QT += qml quick gui
CONFIG += c++11

SOURCES += main.cpp \
    listener.cpp \
    mcanvas/box.cpp \
    mcanvas/reader.cpp \
    mcanvas/number.cpp \
    mcanvas/mcanvas.cpp \
    mcanvas/mpainter.cpp \
    mcanvas/renderer.cpp \
    mcanvas/textview.cpp \
    calc/calc.cpp \

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    listener.h \
    mcanvas/box.h \
    mcanvas/reader.h \
    mcanvas/number.h \
    mcanvas/mcanvas.h \
    mcanvas/mpainter.h \
    mcanvas/renderer.h \
    mcanvas/textview.h \
    calc/calc.h
