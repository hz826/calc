TEMPLATE = app

QT += qml quick gui
CONFIG += c++11

SOURCES += main.cpp \
    listener.cpp \
    mcanvas/box.cpp \
    mcanvas/mcanvas.cpp \
    mcanvas/mpainter.cpp \
    mcanvas/renderer.cpp \
    calc/biginteger.cpp \
    calc/rational.cpp \
    calc/reader.cpp \
    calc/factor.cpp \
    calc/radicalextension.cpp \
    calc/poly.cpp \
    calc/trig.cpp \
    calc/expr.cpp \


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
    calc/algo.h \
    calc/mainheader.h \
    calc/hash.h \
    calc/biginteger.h \
    calc/rational.h \
    calc/reader.h \
    calc/number.h \
    calc/factor.h \
    calc/radicalextension.h \
    calc/poly.h \
    calc/trig.h \
    calc/expr.h \
    calc/calcmain.h \
