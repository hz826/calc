import QtQuick 2.7//不同Qt版本使用的QtQuick版本可能不同，需修改

Rectangle {
    //自定义属性
    property string btMesg: ""//按钮按下时发出的字符串
    property string btText: ""//按钮文字

    property color  textColor: "#ff000000"
    property string pressedTextColor: textColor
    property string releaseTextColor: textColor

    property real   fontSize: 24

    //前两位表示透明色，ff000000纯黑，ffffffff纯白
    property string buttonColor: "#00000000"
    property string pressedColor: "#ffeeeeee" //"#fff5f5f5" //按下和松开的背景颜色
    property string releaseColor: "#fffafafa"

    property string btIcon: ""
    property string pressedIcon: btIcon
    property string releaseIcon: btIcon

    property string borderColor: textColor
    property string pressdBorderColor: pressedTextColor

    property alias wrapMode: textId.wrapMode
    property alias elide: textId.elide

    width: 80; height: 80 //默认大小
    color: mouseArea.pressed?pressedColor:releaseColor
    border.width: 0
    border.color: mouseArea.pressed?pressdBorderColor:borderColor
    focus : true
    signal clicked()
    signal clickedWithMesg(string mesg)
    signal pressed()
    signal release()

    Image {
        id: image
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter:  parent.verticalCenter
        width: (btIcon != "") ? parent.width * 0.7 : 0
        height: (btIcon != "") ? parent.height * 0.7 : 0
        source: mouseArea.pressed? pressedIcon : releaseIcon
    }
    Text {
        id: textId
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter:  parent.verticalCenter
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
        width: parent.width
        text: btText
        color: mouseArea.pressed?pressedTextColor:releaseTextColor
        font.pixelSize: fontSize
    }

    MouseArea{
        id : mouseArea
        hoverEnabled: true
        anchors.fill: parent
        onClicked: {
            parent.clicked()
            parent.clickedWithMesg(btMesg)
        }
        onPressed: {
            parent.pressed(btMesg)
        }
        onReleased: {
            parent.release()
        }
    }
}
