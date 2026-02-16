import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import AlgoViz 1.0

Rectangle {
    color: "#2c3e50"

    property var visualizationModel

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 15

        // Platform title
        Label {
            Layout.fillWidth: true
            text: "Parametric Settings"
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
            label: Label {
                color: "white"
                text: parent.title
                font.bold: true
            }
            background: Rectangle {
                color: "#34495e"
                radius: 5
            }

            topPadding: 20

            ColumnLayout {
                anchors.fill: parent
                spacing: 8

                ComboBox {
                    id: algorithmCombo
                    Layout.fillWidth: true
                    model: visualizationModel && visualizationModel.algorithms ? visualizationModel.algorithms : []
                    currentIndex: 0
                    background: Rectangle {
                        color: "white"
                        radius: 3
                    }
                    onActivated: visualizationModel.currentAlgorithm = currentText
                    Component.onCompleted: {
                        if (visualizationModel) algorithmCombo.currentIndex = algorithmCombo.find(visualizationModel.currentAlgorithm)
                    }
                    Connections {
                        target: visualizationModel
                        function onCurrentAlgorithmChanged() {
                            algorithmCombo.currentIndex = algorithmCombo.find(visualizationModel.currentAlgorithm)
                        }
                    }
                }

                Label {
                    text: "Select an algorithm to visualize."
                    color: "#bdc3c7"
                    font.pixelSize: 11
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }

                Label {
                    text: "Start City"
                    color: "white"
                    font.bold: true
                    Layout.topMargin: 10
                }
                
                ComboBox {
                    Layout.fillWidth: true
                    model: visualizationModel && visualizationModel.cities
                           ? visualizationModel.cities.map(function(c) { return c.name })
                           : []
                    currentIndex: 0
                    background: Rectangle {
                        color: "white"
                        radius: 3
                    }
                    onActivated: visualizationModel.startNode = currentText
                    Component.onCompleted: {
                        if (visualizationModel)
                            currentIndex = find(visualizationModel.startNode)
                    }
                    Connections {
                        target: visualizationModel
                        function onStartNodeChanged() {
                             parent.currentIndex = parent.find(visualizationModel.startNode)
                        }
                    }
                }

                Label {
                    text: "Goal City"
                    color: "white"
                    font.bold: true
                }
                
                ComboBox {
                    Layout.fillWidth: true
                    model: visualizationModel && visualizationModel.cities
                           ? visualizationModel.cities.map(function(c) { return c.name })
                           : []
                    currentIndex: 1
                    background: Rectangle {
                        color: "white"
                        radius: 3
                    }
                    onActivated: visualizationModel.goalNode = currentText
                    Component.onCompleted: {
                        if (visualizationModel)
                            currentIndex = find(visualizationModel.goalNode)
                    }
                    Connections {
                        target: visualizationModel
                        function onGoalNodeChanged() {
                             parent.currentIndex = parent.find(visualizationModel.goalNode)
                        }
                    }
                }
            }
        }

        // Control panel section
        GroupBox {
            Layout.fillWidth: true
            title: "Control Panel"

            topPadding: 20
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
                    text: "Step Forward"
                    onClicked: visualizationModel.stepForward()
                }

                Button {
                    Layout.fillWidth: true
                    text: visualizationModel && visualizationModel.isRunning ? "Pause" : "Run"
                    onClicked: {
                        if (visualizationModel.isRunning) {
                            visualizationModel.pause()
                        } else {
                            visualizationModel.startAlgorithm(visualizationModel.currentAlgorithm)
                        }
                    }
                }

                Button {
                    Layout.fillWidth: true
                    text: "Reset"
                    onClicked: visualizationModel.reset()
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
                        value: visualizationModel ? visualizationModel.speed : 5
                        id: speedSlider
                        onMoved: if (visualizationModel) visualizationModel.speed = value
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
            topPadding: 20
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

        Item {
            Layout.fillHeight: true
        }
    }
}
