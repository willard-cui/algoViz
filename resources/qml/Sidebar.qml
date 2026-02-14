import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import AlgoViz 1.0

Rectangle {
    color: "#2c3e50"

    SidebarModel {
        id: sidebarModel
        onCurrentAlgorithmChanged: console.log("Current algorithm:", currentAlgorithm)
        onSpeedChanged: console.log("Speed:", speed)
        onIsRunningChanged: console.log("Is running:", isRunning)
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 15

        // Platform title
        Label {
            Layout.fillWidth: true
            text: "Algorithm Visualization Platform"
            color: "white"
            font.bold: true
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            padding: 10
        }

        // Algorithm selection section
        GroupBox {
            Layout.fillWidth: true
            title: "Algorithm Selection"
            background: Rectangle {
                color: "#34495e"
                radius: 5
            }
            label: Label {
                color: "white"
                text: parent.title
                font.bold: true
            }

            ColumnLayout {
                width: parent.width
                spacing: 8

                ComboBox {
                    Layout.fillWidth: true
                    model: ["Select Algorithm", "BFS", "DFS", "A*", "Dijkstra", "Sorting", "Pathfinding"]
                    currentIndex: 0
                    background: Rectangle {
                        color: "white"
                        radius: 3
                    }
                    onActivated: sidebarModel.currentAlgorithm = currentText
                }

                Label {
                    text: "No specific algorithms implemented.\nThis is a platform framework."
                    color: "#bdc3c7"
                    font.pixelSize: 11
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }
            }
        }

        // Control panel section
        GroupBox {
            Layout.fillWidth: true
            title: "Control Panel"
            background: Rectangle {
                color: "#34495e"
                radius: 5
            }
            label: Label {
                color: "white"
                text: parent.title
                font.bold: true
            }

            ColumnLayout {
                width: parent.width
                spacing: 10

                Button {
                    Layout.fillWidth: true
                    text: "Initialize"
                    highlighted: true
                    onClicked: sidebarModel.initialize()
                }

                Button {
                    Layout.fillWidth: true
                    text: "Step Forward"
                    onClicked: sidebarModel.stepForward()
                }

                Button {
                    Layout.fillWidth: true
                    text: sidebarModel.isRunning ? "Pause" : "Run"
                    onClicked: {
                        if (sidebarModel.isRunning) {
                            sidebarModel.pause()
                        } else {
                            sidebarModel.run()
                        }
                    }
                }

                Button {
                    Layout.fillWidth: true
                    text: "Reset"
                    onClicked: sidebarModel.reset()
                }

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 10

                    Label {
                        text: "Speed:"
                        color: "white"
                    }

                    Slider {
                        Layout.fillWidth: true
                        from: 1
                        to: 10
                        value: 5
                        id: speedSlider
                        onMoved: sidebarModel.speed = value
                    }

                    Label {
                        text: speedSlider.value.toFixed(0)
                        color: "white"
                        Layout.preferredWidth: 30
                    }
                }
            }
        }

        // Visualization settings
        GroupBox {
            Layout.fillWidth: true
            title: "Visualization Settings"
            background: Rectangle {
                color: "#34495e"
                radius: 5
            }
            label: Label {
                color: "white"
                text: parent.title
                font.bold: true
            }

            ColumnLayout {
                width: parent.width
                spacing: 8

                CheckBox {
                    text: "Show Grid"
                    checked: true
                    contentItem: Text {
                        text: parent.text
                        color: "white"
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: parent.indicator.width + parent.spacing
                    }
                }

                CheckBox {
                    text: "Show Labels"
                    checked: true
                    contentItem: Text {
                        text: parent.text
                        color: "white"
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: parent.indicator.width + parent.spacing
                    }
                }

                CheckBox {
                    text: "Animate Transitions"
                    checked: true
                    contentItem: Text {
                        text: parent.text
                        color: "white"
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: parent.indicator.width + parent.spacing
                    }
                }
            }
        }

        // Spacer to push info to bottom
        Item {
            Layout.fillHeight: true
        }
    }
}
