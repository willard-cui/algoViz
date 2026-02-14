import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    color: "#ecf0f1"

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // Visualization header
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 40
            color: "#3498db"

            Label {
                anchors.centerIn: parent
                text: "Algorithm Visualization Area"
                color: "white"
                font.bold: true
                font.pixelSize: 14
            }
        }

        // Main visualization canvas
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "white"
            border.color: "#bdc3c7"
            border.width: 1

            Column {
                anchors.centerIn: parent
                spacing: 20
                width: parent.width * 0.8

                // Visualization placeholder
                Rectangle {
                    width: 400
                    height: 300
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "#f8f9fa"
                    border.color: "#3498db"
                    border.width: 2
                    radius: 5

                    Label {
                        anchors.centerIn: parent
                        text: "Visualization Canvas"
                        font.bold: true
                        font.pixelSize: 18
                        color: "#2c3e50"
                    }

                    Label {
                        anchors.top: parent.top
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.topMargin: 20
                        text: "Algorithm steps will be visualized here"
                        font.pixelSize: 12
                        color: "#7f8c8d"
                    }
                }

                // Status indicators
                Row {
                    spacing: 20
                    anchors.horizontalCenter: parent.horizontalCenter

                    Rectangle {
                        width: 100
                        height: 60
                        color: "#2ecc71"
                        radius: 5

                        Column {
                            anchors.centerIn: parent
                            spacing: 5

                            Label {
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: "Ready"
                                color: "white"
                                font.bold: true
                            }

                            Label {
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: "Status"
                                font.pixelSize: 10
                                color: "white"
                            }
                        }
                    }

                    Rectangle {
                        width: 100
                        height: 60
                        color: "#e74c3c"
                        radius: 5

                        Column {
                            anchors.centerIn: parent
                            spacing: 5

                            Label {
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: "0"
                                color: "white"
                                font.bold: true
                                font.pixelSize: 18
                            }

                            Label {
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: "Steps"
                                font.pixelSize: 10
                                color: "white"
                            }
                        }
                    }

                    Rectangle {
                        width: 100
                        height: 60
                        color: "#f39c12"
                        radius: 5

                        Column {
                            anchors.centerIn: parent
                            spacing: 5

                            Label {
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: "5"
                                color: "white"
                                font.bold: true
                                font.pixelSize: 18
                            }

                            Label {
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: "Speed"
                                font.pixelSize: 10
                                color: "white"
                            }
                        }
                    }
                }
            }
        }

        // Bottom status bar
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 30
            color: "#2c3e50"

            RowLayout {
                anchors.fill: parent
                anchors.margins: 5

                Label {
                    text: "Platform Framework Active"
                    color: "white"
                    font.pixelSize: 11
                }

                Item {
                    Layout.fillWidth: true
                }

                Label {
                    text: "No algorithm loaded"
                    color: "#bdc3c7"
                    font.pixelSize: 11
                }
            }
        }
    }
}
