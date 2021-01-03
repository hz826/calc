import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import Tooska 1.0
import QtQuick.Controls.Styles 1.4

Window {
    visible: true
    width: 1000
    height: 1000
    title: qsTr("Calc")

    Mylistener{
        id: mylistener
    }

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

    property var button_default_spacing_C : 20
    property var button_default_spacing_R : 20

    Column {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        x:0
        y:0
        width: parent.width
        height: parent.height
        id : maincol
        spacing: 20

        Renderer {
            anchors.horizontalCenter: parent.horizontalCenter
            width : parent.width
            height: 100

            id: renderer
            clip: true
            anchors.fill: parent
        }

        Text {
            id: answer
            text: "answer="
            anchors.horizontalCenter: parent.horizontalCenter
            height: 50
        }

        Text {
            id: debug
            objectName: "debug"
            text: "debuger!"
            anchors.horizontalCenter: parent.horizontalCenter
            height: 50
        }

        Row {
            id: maingrid
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: button_default_spacing_R

            Column {
                spacing :  button_default_spacing_C

                IconButton {
                    btText: "7"
                    onClicked: mylistener.sendkey("7$")
                }

                IconButton {
                    btText: "4"
                    onClicked: mylistener.sendkey("4$")
                }

                IconButton {
                    btText: "1"
                    onClicked: mylistener.sendkey("1$")
                }
            }
        }
    }
}
