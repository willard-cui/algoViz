import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Rectangle {
    id: infoPanel
    
    property var theme
    property var infoPanelModel // Use the new model

    color: theme.surfaceBackground

    Rectangle { 
        id: titleBar
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: 30
        color: theme.chromeBackground
        Text {
            anchors.centerIn: parent
            text: "Execution Info"
            font.pixelSize: theme.fontSizeTitle
            font.bold: true
            color: theme.textOnDark
        }
    }

    ColumnLayout {
        anchors {
            top: titleBar.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        spacing: theme.spacingSm
        anchors.margins: theme.spacingMd

        Text {
            text: "Activity Log"
            font.bold: true
            color: theme.textSecondary
        }

        ListView {
            id: logView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: ListModel { id: logModel }
            
            delegate: Rectangle {
                width: logView.width
                height: logText.implicitHeight + 4
                color: index % 2 == 0 ? theme.appBackground : "transparent"
                Text {
                    id: logText
                    anchors.centerIn: parent
                    width: parent.width
                    text: "[" + time + "] " + message
                    font.family: theme.logFontFamily
                    font.pixelSize: theme.fontSizeSm
                    color: theme.textPrimary
                    wrapMode: Text.Wrap
                }
            }
            
            onCountChanged: {
                positionViewAtEnd()
            }
        }
    }

    Connections {
        target: infoPanelModel
        function onMessageLogged(message) {
            var now = new Date()
            var timeStr = now.toLocaleTimeString(Qt.locale(), "HH:mm:ss")
            logModel.append({"time": timeStr, "message": message})
        }
        function onLogClearRequested() {
            logModel.clear()
        }
    }
}
