cmake_minimum_required(VERSION 3.16)

project(GestionDeVoyages VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

option(BUILD_TESTING "Build the QtTest suite" ON)
option(ENABLE_COVERAGE "Enable gcov/lcov coverage instrumentation" OFF)

# Supports both Qt 5.15 (current, via qmake too) and Qt 6 (forward-looking).
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    REQUIRED COMPONENTS
        Core Gui Widgets Sql PrintSupport Charts SerialPort Network)

if(ENABLE_COVERAGE)
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

# --- Reusable library so the app and tests share the same code ----------
add_library(voyager_core STATIC
    gestionVoyages/voyage.cpp
    gestionVoyages/voyage.h
    config/connection.cpp
    config/connection.h
    config/arduino.cpp
    config/arduino.h
    ai/flightinsights.cpp
    ai/flightinsights.h
)
target_include_directories(voyager_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(voyager_core PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::SerialPort
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::PrintSupport
)

# --- Application --------------------------------------------------------
if(QT_VERSION_MAJOR GREATER_EQUAL 6)
    qt_standard_project_setup()
endif()

add_executable(GestionDeVoyages
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    assets/files/mybutton.cpp
    assets/files/mybutton.h
    assets/images/images.qrc
)
target_link_libraries(GestionDeVoyages PRIVATE
    voyager_core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Charts
)

include(GNUInstallDirs)
install(TARGETS GestionDeVoyages
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
