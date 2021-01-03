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
    property var button_size1_w : 80
    property var button_size1_h : 70

    Column {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        x:0
        y:0
        width: parent.width
        height: parent.height
        id : maincol
        spacing: 20

        MCanvas {
            width : parent.width
            height: 300

            id: m_painter
            objectName: "m_canvas"
            clip: true
        }

        Text {
            id: answer
            objectName: "answer"
            text: "answer="
            anchors.horizontalCenter: parent.horizontalCenter
            height: 20
        }

        Text {
            id: status
            objectName: "status"
            text: ""
            anchors.horizontalCenter: parent.horizontalCenter
            height: 20
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: button_default_spacing_R
            Column {
                spacing :  button_default_spacing_C

                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "("
                    onClicked: listener.sendkey("$(|")
                }

                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "x^n"
                    onClicked: listener.sendkey("$^{|}$")
                }

                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "x²"
                    onClicked: listener.sendkey("$^{2}|")
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "frac"
                    onClicked: listener.sendkey("$\\frac{|}{$}$")
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "sin"
                    onClicked: listener.sendkey("$\\sin(|")
                }
            }
            Column {
                spacing :  button_default_spacing_C

                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: ")"
                    onClicked: listener.sendkey("$)|")
                }

                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "n√x"
                    onClicked: listener.sendkey("$\\sqrtn{|}{$}$")
                }

                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "√x"
                    onClicked: listener.sendkey("$\\sqrt{|}$")
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "abs"
                    onClicked: listener.sendkey("$\\abs{|}$")
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "cos"
                    onClicked: listener.sendkey("$\\cos(|")
                }
            }
            Column {
                spacing :  button_default_spacing_C

                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "x!"
                    onClicked: listener.sendkey("$!|")
                }

                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "log"
                    onClicked: listener.sendkey("$\\log{|}{$}")
                }

                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "ln"
                    onClicked: listener.sendkey("$\\ln(|")
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "lg"
                    onClicked: listener.sendkey("$\\lg(|")
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "tan"
                    onClicked: listener.sendkey("$\\tan(|")
                }
            }

            Column {
                spacing :  button_default_spacing_C

                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "7"
                    onClicked: listener.sendkey("$7|")
                }

                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "4"
                    onClicked: listener.sendkey("$4|")
                }

                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "1"
                    onClicked: listener.sendkey("$1|")
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "0"
                    onClicked: listener.sendkey("$0|")
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "e"
                    onClicked: listener.sendkey("$\\E|")
                }
            }
            Column {
                spacing :  button_default_spacing_C

                IconButton{
                    width: button_size1_w
                    height: button_size1_h
                    btText: "8"
                    onClicked: listener.sendkey("$8|")
                }
                IconButton{
                    width: button_size1_w
                    height: button_size1_h
                    btText: "5"
                    onClicked: listener.sendkey("$5|")
                }
                IconButton{
                    width: button_size1_w
                    height: button_size1_h
                    btText: "2"
                    onClicked: listener.sendkey("$2|")
                }
                IconButton{
                    width: button_size1_w
                    height: button_size1_h
                    btText: "."
                    onClicked: listener.sendkey("$.|")
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "PI"
                    onClicked: listener.sendkey("$\\PI|")
                }
            }

            Column {
                spacing :  button_default_spacing_C

                IconButton{
                    width: button_size1_w
                    height: button_size1_h
                    btText: "9"
                    onClicked: listener.sendkey("$9|")
                }
                IconButton{
                    width: button_size1_w
                    height: button_size1_h
                    btText: "6"
                    onClicked: listener.sendkey("$6|")
                }
                IconButton{
                    width: button_size1_w
                    height: button_size1_h
                    btText: "3"
                    onClicked: listener.sendkey("$3|")
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "*10^"
                    onClicked: listener.sendkey("$*$1$0$^{|}$")
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "°"
                    onClicked: listener.sendkey("$\\deg|")
                }
            }
            Column {
                spacing :  button_default_spacing_C
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "MODE"
                    //onClicked: listener.test()
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "DEL"
                    onClicked: listener.backspace()
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "*"
                    onClicked: listener.sendkey("$*|")
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "+"
                    onClicked: listener.sendkey("$+|")
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "Ans"
                    onClicked: listener.sendkey("$\\Ans|")
                }
            }
            Column {
                spacing :  button_default_spacing_C
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "test!"
                    onClicked: listener.test()
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "AC"
                    onClicked: listener.clear()
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "/"
                    onClicked: listener.sendkey("$/|")
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "-"
                    onClicked: listener.sendkey("$-|")
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "="
                    onClicked: listener.calc()
                }
            }
        }
    }
}
