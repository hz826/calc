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

    property var button_default_spacing_C : 5
    property var button_default_spacing_R : 5
    property var button_size1_w : 80
    property var button_size1_h : 70
    property var button_size1_h1 : 145

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

            MouseArea {
                id:mous
                anchors.fill: parent //鼠标的作用区域，也可以用宽与高属性来设置
                enabled: true //是否接受鼠标事件，默认true
                preventStealing: true //是否防止鼠标时间被窃取，默认为false，false的时候可以被窃取。
                onPressed: { //按下就能触发
                    // console.log("onPressed" + mouseX + "  "  + mouseY)
                    listener.onclick(mouseX,mouseY)
                }
                onPositionChanged: { //鼠标位置变化（hoverEnabled得为true），不然得点击才变化
                    // console.log("onPositionChanged" + mouseX + "  "  + mouseY)
                    listener.onclick(mouseX,mouseY)
                }
            }
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
                    btIcon: "icon/x^n.png"
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
                    btText: "x³"
                    onClicked: listener.sendkey("$^{3}|")
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
                    //btText: "n√x"
                    btIcon:"icon/sqrtn.png"
                    onClicked: listener.sendkey("$\\sqrtn{|}{$}$")
                }

                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    //btText: "√x"
                    btIcon:"icon/sqrt.png"
                    onClicked: listener.sendkey("$\\sqrt{|}$")
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    //btText: "abs"
                    btIcon:"icon/abs.png"
                    onClicked: listener.sendkey("$\\abs{|}$")
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
                    //btText: "frac"
                    btIcon:"icon/frac.png"
                    onClicked: listener.sendkey("$\\frac{|}{$}$")
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    //btText: "log"
                    btIcon:"icon/log.png"
                    onClicked: listener.sendkey("$\\log{|}{$}$")
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
                    btText: "cos"
                    onClicked: listener.sendkey("$\\cos(|")
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
                    btText: "tan"
                    onClicked: listener.sendkey("$\\tan(|")
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
                    btText: "e"
                    onClicked: listener.sendkey("$\\E|")
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
                    btIcon:"icon/10^.png"
                    onClicked: listener.sendkey("$*$1$0$^{|}$")
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "𝜋"
                    onClicked: listener.sendkey("$\\PI|")
                }
            }
            Column {
                spacing :  button_default_spacing_C
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btText: "DEL"
                    onClicked: listener.backspace()
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btIcon:"icon/multiple.png"
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
                    btIcon:"icon/e^.png"
                    onClicked: listener.sendkey("$\\E^{|}$")
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
                    btText: "AC"
                    onClicked: listener.clear()
                }
                IconButton {
                    width: button_size1_w
                    height: button_size1_h
                    btIcon:"icon/division.png"
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
                    height: button_size1_h1
                    btText: "="
                    onClicked: listener.calc()
                }
            }
        }
    }
}
