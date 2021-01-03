import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import TeamWuhanAlice 1.0
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

        MPainter {
            width : parent.width
            height: 300

            id: m_painter
            objectName: "m_painter"
            clip: true
        }

        Text {
            id: answer
            objectName: "answer"
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
                    btText: "Test!"
                    onClicked: listener.test()
                }
            }
        }
    }
}
