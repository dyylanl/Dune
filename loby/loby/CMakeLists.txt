cmake_minimum_required(VERSION 3.16)

project(loby)


# Find the QtWidgets library

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        REQUIRED)

find_package(yaml-cpp REQUIRED)

# autocompila los archivos de QT
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# completar con la ruta de los archivos
add_executable(loby mainwindow.h mainwindow.cpp main.cpp mainwindow.ui resources/resources.qrc)

# el ${UIS_HEADERS} son los paths autogenerados a los .ui compilados
target_include_directories(loby PRIVATE ${UIS_HEADERS})

# Use the Widgets module from Qt 5.
target_link_libraries(loby PRIVATE Qt5::Widgets Qt5::Multimedia yaml-cpp)
