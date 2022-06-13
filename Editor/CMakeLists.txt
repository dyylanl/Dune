cmake_minimum_required(VERSION 3.16)

project(prueba_9)


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
add_executable(editor dialog_forma_tablero.cpp dialog_forma_tablero.h dialog_forma_tablero.ui  estado_last_clicked.cpp estado_last_clicked.h celda.cpp celda.h escenario.h escenario.cpp mainwindow.h mainwindow.cpp main.cpp mainwindow.ui resources/my_resources.qrc)

# el ${UIS_HEADERS} son los paths autogenerados a los .ui compilados
target_include_directories(editor PRIVATE ${UIS_HEADERS})

# Use the Widgets module from Qt 5.
target_link_libraries(editor PRIVATE Qt5::Widgets Qt5::Multimedia yaml-cpp)
