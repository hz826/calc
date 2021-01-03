TEMPLATE = app

QT += qml quick gui
CONFIG += c++11

SOURCES += main.cpp \
    listener.cpp \
    mcanvas/box.cpp \
    mcanvas/mcanvas.cpp \
    mcanvas/mpainter.cpp \
    mcanvas/renderer.cpp \
    calc/reader.cpp \
    calc/number.cpp \

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
    mcanvas/mcanvas.h \
    mcanvas/mpainter.h \
    mcanvas/renderer.h \
    calc/calc.h \
    calc/reader.h \
    calc/number.h \
