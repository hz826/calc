import QtQuick 2.0

Item {
    focus: true
    Keys.enabled: true;
    Keys.onEscapePressed: Qt.quit();
    Keys.onPressed: {
        switch (event.key) {
            case Qt.Key_0:
            case Qt.Key_1:
            case Qt.Key_2:
            case Qt.Key_3:
            case Qt.Key_4:
            case Qt.Key_5:
            case Qt.Key_6:
            case Qt.Key_7:
            case Qt.Key_8:
            case Qt.Key_9:
                event.accepted=true;
                mylistener.sendkey(event.key-Qt.Key_0 + "$");
                break;

            case Qt.Key_BraceLeft:
                event.accepted=true;
                mylistener.sendkey("($");
                break;
            case Qt.Key_BraceRight:
                event.accepted=true;
                mylistener.sendkey(")$");
                break;

            case Qt.Key_Backspace:
                event.accepted=true;
                mylistener.backspace();
                break;
            case Qt.Key_Left:
                event.accepted=true;
                mylistener.cursorLeft();
                break;
            case Qt.Key_Right:
                event.accepted=true;
                mylistener.cursorRight();
                break;
            case Qt.Key_Home:
                event.accepted=true;
                mylistener.cursorHome();
                break;
            case Qt.Key_End:
                event.accepted=true;
                mylistener.cursorEnd();
                break;
        }
    }
}
