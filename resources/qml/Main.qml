import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import AlgoViz 1.0

Window {
    width: 1200
    height: 800
    visible: true
    title: qsTr("Algorithm Visualization Platform")
    color: "#f5f5f5"

    VisualizationModel {
        id: vizModel
        onIsRunningChanged: console.log("Viz Running:", isRunning)
    }

    // Main application layout
    Rectangle {
        id: mainContainer
        anchors.fill: parent
        

        // Left sidebar - Algorithm selection and controls
        Sidebar {
            id: leftSidebar
            visualizationModel: vizModel
            anchors {
                top: parent.top
                bottom: parent.bottom
                left: parent.left
            }
            width: parent.width * 0.2
        }

        Rectangle {
            id: separator
            anchors {
                top: parent.top
                bottom: parent.bottom
                left: leftSidebar.right
            }
            width: 5
            color: "#34495e"
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.SplitHCursor
                onPositionChanged: function(mouse) {
                    let pos = mouse.x + parent.x
                    if (pos < mainContainer.width * 0.1)
                        pos = mainContainer.width * 0.1
                    if (pos > mainContainer.width * 0.9)
                        pos = mainContainer.width * 0.9
                    leftSidebar.width = pos;
                }
            }
        }

        // Main visualization area
        VisualizationArea {
            id: visualizationArea
            visualizationModel: vizModel
            anchors {
                top: parent.top
                bottom: parent.bottom
                left: separator.right
                right: parent.right
            }
        }
    }
}
