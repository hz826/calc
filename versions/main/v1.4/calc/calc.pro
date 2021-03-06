TEMPLATE = app

QT += qml quick gui
CONFIG += c++11

SOURCES += main.cpp \
    box.cpp \
    listener.cpp \
    mpainter.cpp \
    renderer.cpp \
    textview.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    box.h \
    listener.h \
    mpainter.h \
    renderer.h \
    textview.h
