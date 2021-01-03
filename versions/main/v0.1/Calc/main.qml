import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5

Window {
    visible: true
    width: 640
    height: 640
    title: qsTr("Hello World")

    property var button_default_W : 60
    property var button_default_H : 60
    property var button_default_spacing_C : 20
    property var button_default_spacing_R : 20
    property var button_default_color : "grey"

    Column {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        x:0
        y:0
        width: parent.width
        height: parent.height
        id : maincol
        spacing: 20

        Canvas {
            anchors.horizontalCenter: parent.horizontalCenter
            width : parent.width
            height: 100
        }

        Text {
            id: answer
            text: "answer="
            anchors.horizontalCenter: parent.horizontalCenter
            height: 50
        }

        Text {
            id: debug
            text: "debuger!"
            anchors.horizontalCenter: parent.horizontalCenter
            height: 50
        }

        Row {
            id: maingrid
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: button_default_spacing_R

            Column {
                id: col1
                spacing :  button_default_spacing_C

                Button {
                    width: button_default_W
                    height: button_default_H
                    text: "7"
                    id : button7
                }

                Button {
                    width: button_default_W
                    height: button_default_H
                    text: "4"
                    id : button4
                }

                Button {
                    width: button_default_W
                    height: button_default_H
                    text: "1"
                    id : button1
                }
            }

            Column {
                id: col2
                spacing :  button_default_spacing_C

                Button {
                    width: button_default_W
                    height: button_default_H
                    text: "8"
                    id : button8
                }

                Button {
                    width: button_default_W
                    height: button_default_H
                    text: "5"
                    id : button5
                }

                Button {
                    width: button_default_W
                    height: button_default_H
                    text: "2"
                    id : button2
                }
            }

            Column {
                id: col3
                spacing :  button_default_spacing_C

                Button {
                    width: button_default_W
                    height: button_default_H
                    text: "9"
                    id : button9
                }

                Button {
                    width: button_default_W
                    height: button_default_H
                    text: "6"
                    id : button6
                }

                Button {
                    width: button_default_W
                    height: button_default_H
                    text: "3"
                    id : button3
                }
            }
        }
    }
}
