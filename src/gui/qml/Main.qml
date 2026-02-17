import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import AlgoViz 1.0

Window {
    width: appTheme.windowWidth
    height: appTheme.windowHeight
    visible: true
    title: qsTr("Algorithm Visualization Platform")
    color: appTheme.appBackground

    AppTheme {
        id: appTheme
    }

    VisualizationModel {
        id: vizModel
    }

    // Main application layout
    Rectangle {
        id: mainContainer
        anchors.fill: parent
        

        // Left sidebar - Algorithm selection and controls
        Sidebar {
            id: leftSidebar
            visualizationModel: vizModel
            theme: appTheme
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
            width: appTheme.separatorThickness
            color: appTheme.chromeBackground
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
            theme: appTheme
            anchors {
                top: parent.top
                bottom: hSeparator.top
                left: separator.right
                right: parent.right
            }
        }

        Rectangle {
            id: hSeparator
            anchors {
                left: separator.right
                right: parent.right
                bottom: infoPanel.top
            }
            height: appTheme.separatorThickness
            color: appTheme.chromeBackground
            
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.SplitVCursor
                property real initialLocalY
                onPressed: initialLocalY = mouse.y
                onPositionChanged: {
                    if (pressed) {
                        var globalMouseY = mapToItem(mainContainer, mouse.x, mouse.y).y
                        var newHeight = mainContainer.height - globalMouseY + initialLocalY - appTheme.separatorThickness
                        if (newHeight < appTheme.infoPanelMinHeight) newHeight = appTheme.infoPanelMinHeight
                        if (newHeight > mainContainer.height * appTheme.infoPanelMaxRatio) newHeight = mainContainer.height * appTheme.infoPanelMaxRatio
                        infoPanel.height = newHeight
                    }
                }
            }
        }

        // Bottom status bar
        InfoPanel {
            id: infoPanel
            height: appTheme.infoPanelHeight
            theme: appTheme
            infoPanelModel: vizModel.infoPanelModel
            
            anchors {
                bottom: parent.bottom
                left: separator.right
                right: parent.right
            }
        }
    }
}
