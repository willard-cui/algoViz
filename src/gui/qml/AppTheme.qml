import QtQuick

QtObject {
    // Backgrounds
    property color appBackground: "#f5f5f5"
    property color chromeBackground: "#2c3e50"
    property color surfaceBackground: "white"
    property color accentPrimary: "#3498db"
    property color sideBarPaneColor: "#34495e"
    
    // Separators & Borders
    property color divider: "#bdc3c7"

    // Text
    property color textPrimary: "#333333"
    property color textSecondary: "#555555"
    property color textOnDark: "white"
    
    // Visualization Elements
    property color highlightPath: "#e74c3c"
    property color highlightCurrent: "#f1c40f"
    property color highlightVisited: "#2ecc71"
    
    // Log
    property int spacingSm: 8
    property int spacingMd: 10
    property int cornerRadiusSm: 3
    property int cornerRadiusMd: 5
    property int fontSizeTitle: 16
    property int fontSizeSm: 12
    property int windowWidth: 1200
    property int windowHeight: 800
    property int separatorThickness: 5
    property int infoPanelHeight: 150
    property int infoPanelMinHeight: 50
    property real infoPanelMaxRatio: 0.8
    property string logFontFamily: "Consolas"
    property int canvasBorderWidth: 1
    property int roadStrokeWidth: 2
    property int citySize: 20
    property int cityBorderWidth: 2
    property int cityLabelOffsetY: -15
    property int mapContainerWidth: 600
    property int mapContainerHeight: 400
    property int mapScaleRefWidth: 650
    property int mapScaleRefHeight: 450
    property real mapScale: 2.5
}
