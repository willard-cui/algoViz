cmake_minimum_required(VERSION 3.16)
project(AlgorithmVisualizationPlatform CXX)

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
find_package(Qt6 COMPONENTS Core Gui Qml Quick REQUIRED)

# --- Output directory: build/output ---
if (NOT MP_OUTPUT_DIR)
    set(MP_OUTPUT_DIR ${CMAKE_BINARY_DIR}/output)
    message(STATUS "Building to: ${MP_OUTPUT_DIR}, use -DMP_OUTPUT_DIR=xxx to override")
else()
    message(STATUS "Building to: ${MP_OUTPUT_DIR}")
endif()
set(MP_OUTPUT_BINDIR ${MP_OUTPUT_DIR}/bin)
set(MP_OUTPUT_LIBDIR ${MP_OUTPUT_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MP_OUTPUT_BINDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${MP_OUTPUT_BINDIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${MP_OUTPUT_LIBDIR})

set(QT_QML_OUTPUT_DIRECTORY ${MP_OUTPUT_DIR}/qml)
set(QML_IMPORT_PATH ${MP_OUTPUT_DIR}/qml CACHE STRING "" FORCE)

# --- GUI App (Qt Quick only) ---
qt_add_executable(AlgorithmVisualizationPlatform
    MANUAL_FINALIZATION
    src/gui/main.cpp
    src/models/SidebarModel.h
    src/models/SidebarModel.cpp
    resources/qml/qml.qrc
)

target_include_directories(AlgorithmVisualizationPlatform PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/gui
    ${CMAKE_SOURCE_DIR}/src/models
)

target_link_libraries(AlgorithmVisualizationPlatform PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

qt_finalize_executable(AlgorithmVisualizationPlatform)
