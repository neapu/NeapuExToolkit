import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic

Rectangle {
    color: "#eeeeee"

    ScrollView {
        anchors.fill: parent
        ListView {
            id: imageListView
            anchors.fill: parent
            model: imageListModel
            clip: true
            property int selectedIndex: -1

            // Connections {
            //     target: imageListModel
            //     function onSelectedIndexChanged(index) {
            //         imageListView.selectedIndex = index
            //     }
            // }

            delegate: Rectangle {
                width: imageListView.width
                height: 60
                color: imageListModel.selectedIndex === index ? "#666666" : "transparent"

                Text {
                    text: name
                    anchors.fill: parent
                    anchors.leftMargin: 10
                    verticalAlignment: Text.AlignVCenter
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        imageListModel.selectedIndex = index
                    }
                }
            }
        }
    }
}