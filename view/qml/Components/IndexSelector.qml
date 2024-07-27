import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic

Rectangle {
    id: root
    property string labelText: ""
    property int totalIndex: 0
    property int currentIndex: 0
    signal nextButtonClicked
    signal lastButtonClicked

    Text {
        id: textLabel
        text: root.labelText
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10
        font.pixelSize: 14
    }

    IconButton {
        id: lastButton
        anchors.right: indexBox.left
        anchors.rightMargin: 10
        anchors.verticalCenter: indexBox.verticalCenter
        width: 30
        height: 30
        imgUrl: "qrc:/res/last-btn.svg"
        onClicked: {
            root.lastButtonClicked()
        }
    }

    Rectangle {
        id: indexBox
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        width: 100
        height: 30
        border.color: "#000000"

        Text {
            text: root.currentIndex + "/" + root.totalIndex
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    IconButton {
        id: nextButton
        anchors.left: indexBox.right
        anchors.leftMargin: 10
        anchors.verticalCenter: indexBox.verticalCenter
        width: 30
        height: 30
        imgUrl: "qrc:/res/next-btn.svg"
        onClicked: {
            root.nextButtonClicked()
        }
    }

}