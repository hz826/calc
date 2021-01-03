import QtQuick 2.0
import TeamWuhanAlice 1.0

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
                listener.sendkey(event.key-Qt.Key_0 + "$");
                break;

            case Qt.Key_BraceLeft:
                event.accepted=true;
                listener.sendkey("($");
                break;
            case Qt.Key_BraceRight:
                event.accepted=true;
                listener.sendkey(")$");
                break;

            case Qt.Key_Backspace:
                event.accepted=true;
                listener.backspace();
                break;
            case Qt.Key_Left:
                event.accepted=true;
                listener.left();
                break;
            case Qt.Key_Right:
                event.accepted=true;
                listener.right();
                break;
            case Qt.Key_Home:
                event.accepted=true;
                listener.home();
                break;
            case Qt.Key_End:
                event.accepted=true;
                listener.end();
                break;
        }
    }
}
