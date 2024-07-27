import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic
import QtQuick.Dialogs
import "./Components"
import NeapuExView 1.0

ApplicationWindow {
    visible: true
    width: 1280
    height: 720
    title: qsTr("Hello World")
    color: "#ffffff"

    FileDialog {
        id: fileDialog
        title: "选择NPK文件"
        nameFilters: ["NPK文件 (*.npk)"]
        fileMode: FileDialog.OpenFile
        onAccepted: {
            console.log("You chose: " + selectedFile)
            exWardrobe.openNpk(selectedFile)
        }
    }

    Button {
        id: selectNpkButton
        text: "选择NPK文件"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 10
        width: 300
        height: 50
        onClicked: {
            fileDialog.open()
        }
    }

    Rectangle {
        id: titleBar
        anchors.left: selectNpkButton.right
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 10
        color: "#eeeeee"
        height: 50

        Text {
            id: titleText
            text: exWardrobe.title
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 10
        }
    }

    ImgList {
        id: imgList
        anchors.top: selectNpkButton.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 10
        width: 300
    }

    Rectangle {
        id: infoView
        anchors.top: titleBar.bottom
        anchors.bottom: parent.bottom
        anchors.left: imgList.right
        anchors.margins: 10
        width: 300
        color: "#eeeeee"

        Column {
            padding: 10
            spacing: 10
            property int childWidth: infoView.width - 20
            property int childHeight: 50

            Rectangle {
                id: itemVersion
                width: parent.childWidth
                height: parent.childHeight

                Text {
                    text: "IMG版本: " + exWardrobe.imgVersion
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    font.pixelSize: 14
                }
            }

            IndexSelector {
                id: paletteSelector
                width: parent.childWidth
                height: 80
                visible: exWardrobe.imgVersion === 4 || exWardrobe.imgVersion === 6

                labelText: "调色板"
                totalIndex: exWardrobe.paletteCount
                currentIndex: exWardrobe.currentPaletteIndex

                onLastButtonClicked: exWardrobe.lastPalette()
                onNextButtonClicked: exWardrobe.nextPalette()
            }

            Rectangle {
                id: itemLinkInfo
                width: parent.childWidth
                height: parent.childHeight
                visible: exWardrobe.frameProperty.is_link

                Text {
                    text: "链接帧: " + exWardrobe.frameProperty.link_info
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    font.pixelSize: 14
                }
            }

            Rectangle {
                id: itemDDSInfo
                width: parent.childWidth
                height: parent.childHeight
                visible: exWardrobe.frameProperty.is_dds

                Text {
                    text: "DDS索引: " + exWardrobe.frameProperty.dds_index + "(" + exWardrobe.frameProperty.dds_info + ")"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    font.pixelSize: 14
                }
            }

            Rectangle {
                id: itemColorType
                width: parent.childWidth
                height: parent.childHeight
                visible: exWardrobe.imgVersion === 2

                Text {
                    text: "颜色类型: " + exWardrobe.frameProperty.colorType
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    font.pixelSize: 14
                }
            }

            Rectangle {
                id: itemSize
                width: parent.childWidth
                height: parent.childHeight

                Rectangle {
                    id: itemWidth
                    width: parent.width / 2
                    height: 50

                    Text {
                        text: "宽度: " + exWardrobe.frameProperty.width
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        font.pixelSize: 14
                    }
                }

                Rectangle {
                    id: itemHeight
                    width: parent.width / 2
                    height: 50
                    anchors.right: parent.right

                    Text {
                        text: "高度: " + exWardrobe.frameProperty.height
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.rightMargin: 10
                        font.pixelSize: 14
                    }
                }
            }

            IndexSelector {
                id: frameSelector
                width: parent.childWidth
                height: 80

                labelText: "帧序号"
                totalIndex: exWardrobe.totalFrames
                currentIndex: exWardrobe.currentFrame

                onLastButtonClicked: exWardrobe.lastFrame()
                onNextButtonClicked: exWardrobe.nextFrame()
            }
        }
    }

    Connections {
        target: exWardrobe
        onFrameChanged: matrixRenderer.updateImage(imgID)
    }

    MatrixRenderer {
        id: matrixRenderer
        anchors.top: titleBar.bottom
        anchors.bottom: parent.bottom
        anchors.left: infoView.right
        anchors.right: parent.right
        anchors.margins: 10
    }
}
