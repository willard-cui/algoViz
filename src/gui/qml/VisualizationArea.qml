import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Shapes

Rectangle {
    color: theme.appBackground
    property var visualizationModel
    property var theme

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // Visualization header
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 40
            color: theme.accentPrimary

            Label {
                anchors.centerIn: parent
                text: visualizationModel && visualizationModel.currentAlgorithm && visualizationModel.currentAlgorithm !== "" 
                      ? "Visualizing: " + visualizationModel.currentAlgorithm 
                      : "Visualization Area"
                color: theme.textOnDark
                font.bold: true
                font.pixelSize: 14
            }
        }

        // Main visualization canvas
        Rectangle {
            id: canvasArea
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: theme.surfaceBackground
            border.color: theme.divider
            border.width: theme.canvasBorderWidth
            clip: true

            // Map Container
            Item {
                id: mapContainer
                width: theme.mapContainerWidth
                height: theme.mapContainerHeight
                anchors.centerIn: parent
                scale: Math.min(parent.width / theme.mapScaleRefWidth, parent.height / theme.mapScaleRefHeight)
                
                // Coordinate transformation: 
                // Map range: X[-40, 170], Y[-20, 120] -> width ~210, height ~140
                // We want to map this to our container 600x400
                // Center of map: (65, 50)
                // Center of container: (300, 200)
                // Scale factor: 2.5
                
                property real mapScale: theme.mapScale
                property real centerX: mapContainer.width / 2
                property real centerY: mapContainer.height / 2
                property real mapCenterX: 65
                property real mapCenterY: 50
                
                function toScreenX(x) { return centerX + (x - mapCenterX) * mapScale }
                function toScreenY(y) { return centerY + (y - mapCenterY) * mapScale }

                // Roads
                Repeater {
                    model: visualizationModel ? visualizationModel.roads : []
                    Shape {
                        ShapePath {
                            strokeWidth: theme.roadStrokeWidth
                            strokeColor: theme.divider
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
                        width: theme.citySize
                        height: theme.citySize
                        radius: theme.citySize / 2
                        x: mapContainer.toScreenX(modelData.x) - width/2
                        y: mapContainer.toScreenY(modelData.y) - height/2
                        
                        color: {
                            if (!visualizationModel) 
                                return theme.chromeBackground;
                            
                            // Check if in path (solution)
                            var inPath = false;
                            for(var i=0; i<visualizationModel.pathNodes.length; i++) {
                                if(visualizationModel.pathNodes[i] === modelData.name) {
                                    inPath = true;
                                    break;
                                }
                            }
                            if (inPath) 
                                return theme.highlightPath; // Red for path
                            
                            // Check if current node
                            if (visualizationModel.currentNode === modelData.name) return theme.highlightCurrent; // Yellow for current
                            
                            // Check if visited
                            var visited = false;
                            for(var i=0; i<visualizationModel.visitedNodes.length; i++) {
                                if(visualizationModel.visitedNodes[i] === modelData.name) {
                                    visited = true;
                                    break;
                                }
                            }
                            if (visited) 
                                return theme.highlightVisited; // Green for visited
                            
                            // Check if start or goal
                            if (modelData.name === visualizationModel.startNode || modelData.name === visualizationModel.goalNode) {
                                return theme.highlightPath; // Red for Start/Goal
                            }
                            
                            return theme.chromeBackground; // Default
                        }
                        
                        border.color: theme.surfaceBackground
                        border.width: theme.cityBorderWidth
                        
                        Text {
                            anchors.centerIn: parent
                            anchors.verticalCenterOffset: theme.cityLabelOffsetY
                            text: modelData.name
                            font.pixelSize: theme.fontSizeSm
                            style: Text.Outline
                            styleColor: theme.surfaceBackground
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
        
    }
}
