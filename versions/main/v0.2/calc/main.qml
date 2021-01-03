import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import Tooska 1.0

Window {
    visible: true
    width: 1000
    height: 1000
    title: qsTr("Calc")

    Mylistener{
        id: mylistener
    }

    Button{
        text: "7"
        onClicked: mylistener.sendkey("7$")
    }
}
