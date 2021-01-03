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

    Listener{
        id: listener
        objectName: "m_listener"
    }

    KeyboardListener {
        id:keyboardlistener
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
            width : parent.width
            height: 300

            id: m_renderer
            objectName: "m_renderer"
            clip: true
        }

        Text {
            id: answer
            text: "answer="
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
                    onClicked: listener.sendkey("7$")
                }

                IconButton {
                    btText: "4"
                    onClicked: listener.sendkey("4$")
                }

                IconButton {
                    btText: "1"
                    onClicked: listener.sendkey("1$")
                }
            }
        }
    }
}
