import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Fusion
import AlgoViz 1.0

Rectangle {
    color: theme.chromeBackground

    property var visualizationModel
    property var theme

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: theme.spacingMd
        spacing: 15

        // Platform title
        Text {
            Layout.fillWidth: true
            text: "Parametric Settings"
            color: theme.textOnDark
            font.bold: true
            font.pixelSize: theme.fontSizeTitle
            horizontalAlignment: Text.AlignHCenter
            padding: theme.spacingMd
        }

        // Algorithm selection section
        GroupBox {
            Layout.fillWidth: true
            title: "Algorithm Selection"
            label: Label {
                color: theme.textOnDark
                text: parent.title
                font.bold: true
            }
            background: Rectangle {
                color: theme.sideBarPaneColor
                radius: theme.cornerRadiusMd
            }

            topPadding: 20

            ColumnLayout {
                anchors.fill: parent
                spacing: theme.spacingSm

                ComboBox {
                    id: algorithmCombo
                    Layout.fillWidth: true
                    implicitHeight: 25
                    model: visualizationModel && visualizationModel.algorithms ? visualizationModel.algorithms : []
                    currentIndex: 0
                    background: Rectangle {
                        color: theme.surfaceBackground
                        radius: theme.cornerRadiusSm
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
                    color: theme.divider
                    font.pixelSize: theme.fontSizeSm
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }

                Label {
                    text: "Start City"
                    color: theme.textOnDark
                    font.bold: true
                    Layout.topMargin: theme.spacingMd
                }
                
                ComboBox {
                    Layout.fillWidth: true
                    implicitHeight: 25
                    model: visualizationModel && visualizationModel.cities
                           ? visualizationModel.cities.map(function(c) { return c.name })
                           : []
                    currentIndex: 0
                    background: Rectangle {
                        color: theme.surfaceBackground
                        radius: theme.cornerRadiusSm
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
                    color: theme.textOnDark
                    font.bold: true
                }
                
                ComboBox {
                    Layout.fillWidth: true
                    implicitHeight: 25
                    model: visualizationModel && visualizationModel.cities
                           ? visualizationModel.cities.map(function(c) { return c.name })
                           : []
                    currentIndex: 1
                    background: Rectangle {
                        color: theme.surfaceBackground
                        radius: theme.cornerRadiusSm
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
                color: theme.sideBarPaneColor
                radius: theme.cornerRadiusMd
            }
            label: Label {
                color: theme.textOnDark
                text: parent.title
                font.bold: true
            }

            ColumnLayout {
                width: parent.width
                spacing: theme.spacingMd

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
                        color: theme.textOnDark
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
                        color: theme.textOnDark
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
                color: theme.sideBarPaneColor
                radius: theme.cornerRadiusMd
            }
            label: Text {
                color: theme.textOnDark
                text: parent.title
            }

            ColumnLayout {
                width: parent.width
                spacing: theme.spacingSm

                CheckBox {
                    text: "Show Grid"
                    checked: true
                    contentItem: Text {
                        text: parent.text
                        color: theme.textOnDark
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: parent.indicator.width + parent.spacing
                    }
                }

                CheckBox {
                    text: "Show Labels"
                    checked: true
                    contentItem: Text {
                        text: parent.text
                        color: theme.textOnDark
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: parent.indicator.width + parent.spacing
                    }
                }

                CheckBox {
                    text: "Animate Transitions"
                    checked: true
                    contentItem: Text {
                        text: parent.text
                        color: theme.textOnDark
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
