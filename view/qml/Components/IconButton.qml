import QtQuick

Rectangle {
    id: root
    width: 30
    height: 30
    color: "#00000000"
    radius: 2
    signal clicked
    property url imgUrl: ""

    // 因为是Rectangle而不是Button，需要一个MouseArea组件来监听鼠标事件
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true // 默认不监听hover，因为会降低性能，要显式置为true
        onEntered: {
            root.color = "#eeeeee"
        }

        onExited: root.color = "#00000000"
        onPressed: root.color = "#666666"
        onReleased: root.color = "#eeeeee"

        onClicked: {
            root.clicked()
        }
    }

    Image {
        source: root.imgUrl
        width: root.width - 8
        height: root.height - 8
        anchors.centerIn: parent
    }
}
