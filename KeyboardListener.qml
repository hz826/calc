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
                listener.sendkey("$" + (event.key-Qt.Key_0) + "|");
                break;

            case Qt.Key_ParenLeft:
                event.accepted=true;
                listener.sendkey("$(|");
                break;
            case Qt.Key_ParenRight:
                event.accepted=true;
                listener.sendkey("$)|");
                break;

            case Qt.Key_Plus:
                event.accepted=true;
                listener.sendkey("$+|");
                break;
            case Qt.Key_Minus:
                event.accepted=true;
                listener.sendkey("$-|");
                break;
            case Qt.Key_Asterisk:
                event.accepted=true;
                listener.sendkey("$*|");
                break;
            case Qt.Key_Slash:
                event.accepted=true;
                listener.sendkey("$/|");
                break;
            case Qt.Key_AsciiCircum:
                event.accepted=true;
                listener.sendkey("$^{|}$");
                break;
            case Qt.Key_Period:
                event.accepted=true;
                listener.sendkey("$.|");
                break;


            case Qt.Key_Equal:
                event.accepted=true;
                listener.calc();
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
            case Qt.Key_Left:
                event.accepted=true;
                listener.left();
                break;
            case Qt.Key_Down:
                event.accepted=true;
                listener.down();
                break;
            case Qt.Key_Up:
                event.accepted=true;
                listener.up();
                break;
            case Qt.Key_Home:
                event.accepted=true;
                listener.home();
                break;
            case Qt.Key_End:
                event.accepted=true;
                listener.end();
                break;

            case Qt.Key_S:
                listener.sendkey("$\\sin(|")
                break;
            case Qt.Key_C:
                listener.sendkey("$\\cos(|")
                break;
            case Qt.Key_T:
                listener.sendkey("$\\tan(|")
                break;
            case Qt.Key_E:
                listener.sendkey("$\\E|")
                break;
            case Qt.Key_P:
                listener.sendkey("$\\PI|")
                break;
            case Qt.Key_D:
                listener.sendkey("$\\deg|")
                break;
            case Qt.Key_F:
                listener.sendkey("$\\frac{|}{$}$")
                break;
        }
    }
}
