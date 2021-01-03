TEMPLATE = app

QT += qml quick gui
CONFIG += c++11

SOURCES += main.cpp \
    mylistener.cpp \
    output.cpp \
    renderer.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    mylistener.h \
    output.h \
    renderer.h