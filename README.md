# Algorithm Visualization Platform

A Qt Quick based platform for visualizing and validating algorithms. This is a framework that provides the UI infrastructure for algorithm visualization without implementing specific algorithms.

## Features

- **Modern Qt Quick UI**: Clean, responsive interface built with Qt 6
- **Modular Design**: Sidebar for algorithm selection and controls, main visualization area, status panel
- **Platform Framework**: Ready-to-extend structure for adding algorithm visualizations
- **Cross-platform**: Built with Qt for Windows, macOS, and Linux support

## Project Structure

```
AlgorithmVisualizationPlatform/
├── CMakeLists.txt          # CMake build configuration
├── README.md               # This file
├── resources/
│   └── qml/
│       ├── Main.qml        # Main QML interface
│       └── qml.qrc         # Qt resource file
└── src/
    └── gui/
        └── main.cpp        # Application entry point
```

## Building

### Prerequisites
- Qt 6.10 or compatible version
- CMake 3.16 or higher
- C++17 compatible compiler

### Build Steps
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

The executable will be placed in `build/output/bin/`.

## Usage

1. **Run the application**: Launch `AlgorithmVisualizationPlatform` executable
2. **Interface**:
   - Left sidebar: Algorithm selection and control panel
   - Main area: Visualization canvas
   - Bottom: Status information
3. **Extending**: Add algorithm implementations by:
   - Extending the QML interface for visualization
   - Adding C++ algorithm classes
   - Connecting algorithm logic to visualization

## Platform Design

### UI Components
- **Algorithm Selection**: Dropdown for selecting algorithms (placeholder)
- **Control Panel**: Standard controls (Initialize, Step, Run, Reset, Speed)
- **Visualization Settings**: Toggle for grid, labels, animations
- **Visualization Canvas**: Main area for algorithm visualization
- **Status Indicators**: Visual feedback on algorithm state

### Extension Points
1. **Add new algorithms**: Extend the ComboBox model in `Main.qml`
2. **Implement visualization**: Replace the visualization canvas with custom QML
3. **Add algorithm logic**: Create C++ classes and expose them to QML
4. **Connect controls**: Wire up buttons to algorithm functions

## Dependencies

- Qt6 Core, Gui, Qml, Quick
- CMake build system

## License

This is a framework project for educational and development purposes.

## Notes

This platform does not include specific algorithm implementations. It is designed as a starting point for building algorithm visualizations. The UI is fully functional but serves as a template for actual algorithm visualization projects.