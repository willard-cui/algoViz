import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Shapes

Rectangle {
    color: "#ecf0f1"
    property var visualizationModel

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
                text: visualizationModel && visualizationModel.currentAlgorithm && visualizationModel.currentAlgorithm !== "" 
                      ? "Visualizing: " + visualizationModel.currentAlgorithm 
                      : "Visualization Area"
                color: "white"
                font.bold: true
                font.pixelSize: 14
            }
        }

        // Main visualization canvas
        Rectangle {
            id: canvasArea
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "white"
            border.color: "#bdc3c7"
            border.width: 1
            clip: true

            // Map Container
            Item {
                id: mapContainer
                width: 600
                height: 400
                anchors.centerIn: parent
                scale: Math.min(parent.width / 650, parent.height / 450)
                
                // Coordinate transformation: 
                // Map range: X[-40, 170], Y[-20, 120] -> width ~210, height ~140
                // We want to map this to our container 600x400
                // Center of map: (65, 50)
                // Center of container: (300, 200)
                // Scale factor: 2.5
                
                property real mapScale: 2.5
                property real centerX: 300
                property real centerY: 200
                property real mapCenterX: 65
                property real mapCenterY: 50
                
                function toScreenX(x) { return centerX + (x - mapCenterX) * mapScale }
                function toScreenY(y) { return centerY + (y - mapCenterY) * mapScale }

                // Roads
                Repeater {
                    model: visualizationModel ? visualizationModel.roads : []
                    Shape {
                        ShapePath {
                            strokeWidth: 2
                            strokeColor: "#bdc3c7"
                            startX: mapContainer.toScreenX(modelData.fromX !== undefined ? modelData.fromX : canvasArea.getCityX(modelData.from))
                            startY: mapContainer.toScreenY(modelData.fromY !== undefined ? modelData.fromY : canvasArea.getCityY(modelData.from))
                            PathLine {
                                x: mapContainer.toScreenX(modelData.toX !== undefined ? modelData.toX : canvasArea.getCityX(modelData.to))
                                y: mapContainer.toScreenY(modelData.toY !== undefined ? modelData.toY : canvasArea.getCityY(modelData.to))
                            }
                        }
                    }
                }

                // Cities
                Repeater {
                    model: visualizationModel ? visualizationModel.cities : []
                    Rectangle {
                        width: 20
                        height: 20
                        radius: 10
                        x: mapContainer.toScreenX(modelData.x) - width/2
                        y: mapContainer.toScreenY(modelData.y) - height/2
                        
                        color: {
                            if (!visualizationModel) 
                                return "#34495e";
                            
                            // Check if in path (solution)
                            var inPath = false;
                            for(var i=0; i<visualizationModel.pathNodes.length; i++) {
                                if(visualizationModel.pathNodes[i] === modelData.name) {
                                    inPath = true;
                                    break;
                                }
                            }
                            if (inPath) 
                                return "#e74c3c"; // Red for path
                            
                            // Check if current node
                            if (visualizationModel.currentNode === modelData.name) return "#f1c40f"; // Yellow for current
                            
                            // Check if visited
                            var visited = false;
                            for(var i=0; i<visualizationModel.visitedNodes.length; i++) {
                                if(visualizationModel.visitedNodes[i] === modelData.name) {
                                    visited = true;
                                    break;
                                }
                            }
                            if (visited) 
                                return "#2ecc71"; // Green for visited
                            
                            // Check if start or goal
                            if (modelData.name === visualizationModel.startNode || modelData.name === visualizationModel.goalNode) {
                                return "#e74c3c"; // Red for Start/Goal
                            }
                            
                            return "#34495e"; // Default
                        }
                        
                        border.color: "white"
                        border.width: 2
                        
                        Text {
                            anchors.centerIn: parent
                            anchors.verticalCenterOffset: -15
                            text: modelData.name
                            font.pixelSize: 12
                            style: Text.Outline
                            styleColor: "white"
                        }
                    }
                }
            }
            
            // Helper function to get city coordinates by name (naive implementation, O(N))
            function getCityX(name) {
                if (!visualizationModel) return 0;
                var cities = visualizationModel.cities;
                for(var i=0; i<cities.length; i++) {
                    if (cities[i].name === name) return cities[i].x;
                }
                return 0;
            }
            
            function getCityY(name) {
                if (!visualizationModel) return 0;
                var cities = visualizationModel.cities;
                for(var i=0; i<cities.length; i++) {
                    if (cities[i].name === name) return cities[i].y;
                }
                return 0;
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
                    text: visualizationModel ? "Nodes Visited: " + visualizationModel.visitedNodes.length : "Not ready"
                    color: "white"
                    font.pixelSize: 11
                }

                Item { Layout.fillWidth: true }
                
                Label {
                    text: visualizationModel && visualizationModel.pathNodes.length > 0 ? "Path Found! Length: " + visualizationModel.pathNodes.length : ""
                    color: "#2ecc71"
                    font.pixelSize: 11
                    font.bold: true
                }

                Item { Layout.fillWidth: true }

                Label {
                    text: visualizationModel ? (visualizationModel.isRunning ? "Running..." : "Ready") : "Initializing..."
                    color: "#bdc3c7"
                    font.pixelSize: 11
                }
            }
        }
    }
}
