cmake_minimum_required(VERSION 3.16)
project(AlgoViz CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# --- Dependencies ---
# Qt setup (configurable)
set(QT_ROOT "${CMAKE_SOURCE_DIR}/../qt6101" CACHE PATH "Qt root")
set(QT_HOST_PREFIX "${QT_ROOT}/msvc2022_64" CACHE PATH "Qt host prefix")
set(QT_BIN_DIR "${QT_HOST_PREFIX}/bin" CACHE PATH "Qt bin dir")
set(CMAKE_PREFIX_PATH ${QT_HOST_PREFIX})

# Qt6
find_package(Qt6 COMPONENTS Core Gui Qml Quick REQUIRED QuickControls2)

# --- Output directory: build/output ---
if (NOT AV_OUTPUT_DIR)
    set(AV_OUTPUT_DIR ${CMAKE_BINARY_DIR}/output)
endif()
set(AV_OUTPUT_BINDIR ${AV_OUTPUT_DIR}/bin)
set(AV_OUTPUT_LIBDIR ${AV_OUTPUT_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${AV_OUTPUT_BINDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${AV_OUTPUT_BINDIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${AV_OUTPUT_LIBDIR})

set(QT_QML_OUTPUT_DIRECTORY ${AV_OUTPUT_DIR}/qml)
set(QML_IMPORT_PATH ${AV_OUTPUT_DIR}/qml CACHE STRING "" FORCE)

# --- GUI App (Qt Quick only) ---
qt_add_executable(AlgoViz
    MANUAL_FINALIZATION
    src/gui/main.cpp    
    src/algorithms/SearchAlgorithm.cpp
    src/algorithms/BreadthFirstSearch.cpp
    src/algorithms/DepthFirstSearch.cpp
    src/algorithms/DepthLimitedSearch.cpp
    src/algorithms/IterativeDeepeningDFS.cpp
    src/algorithms/UniformCostSearch.cpp
    src/algorithms/GreedyBestFirstSearch.cpp
    src/algorithms/AStarSearch.cpp
    src/algorithms/WeightedAStarSearch.cpp
    src/algorithms/IterativeDeepeningAStar.cpp
)

qt_add_qml_module(AlgoViz
    URI AlgoViz
    VERSION 1.0
    RESOURCE_PREFIX "/"
    SOURCES
        src/gui/models/InfoPanelModel.h
        src/gui/models/InfoPanelModel.cpp
        src/gui/models/VisualizationModel.h
        src/gui/models/VisualizationModel.cpp

    QML_FILES
        src/gui/qml/AppTheme.qml
        src/gui/qml/InfoPanel.qml
        src/gui/qml/Main.qml
        src/gui/qml/Sidebar.qml
        src/gui/qml/VisualizationArea.qml
)

target_include_directories(AlgoViz PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/gui
    ${CMAKE_SOURCE_DIR}/src/gui/models
)

target_link_libraries(AlgoViz PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
)
qt_finalize_executable(AlgoViz)
