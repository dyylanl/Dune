cmake_minimum_required(VERSION 3.16)
project(dune)

# FLAGS DE COMPILACION
# Estándar a utilizar
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Flags para el manejo de errores
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors")

# Optimizaciones
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# Debugging
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -DDEBUG -fno-inline")



#QT
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        REQUIRED)


# YAML
FIND_PACKAGE(yaml-cpp REQUIRED)
INCLUDE_DIRECTORIES(${YAML_CPP_INCLUDE_DIRS})
file(GLOB CONFIG_FILE config.yaml)
#------------------------------------------------------------------------------

ADD_DEFINITIONS(-DDATA_PATH="${PROJECT_SOURCE_DIR}/Client/")

#------------------------------------------------------------------------------
#Agrego la libreria SDL2pp habilitando manejo de imagenes y de letras
SET(SDL2PP_WITH_IMAGE YES)
SET(SDL2PP_WITH_TTF YES)
ADD_SUBDIRECTORY(Client/libs/libSDL2pp)

#Agrega la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_SOURCE_DIR}Client/libs' como directorio de includes")
include_directories(${PROJECT_SOURCE_DIR}Client/libs)
include_directories(${SDL2PP_INCLUDE_DIRS})

#------------------------------------------------------------------------------
# ARCHIVOS FUENTE
FILE(GLOB_RECURSE common_src "Common/*.cpp")
FILE(GLOB_RECURSE client_src "Client/*.cpp")
FILE(GLOB_RECURSE server_src "Server/*.cpp")
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# TARGETS

# Common
add_library(dune-common SHARED ${common_src})
target_link_libraries(dune-common)

# Client
# <<<<<<< HEAD
# add_executable(dune ${client_src} Client/src/Core/UnitType.cpp Client/src/Characters/UnitType.h)
# target_link_libraries(dune dune-common SDL2 SDL2_image SDL2_ttf SDL2_mixer ${SDL2PP_LIBRARIES})
#=======
add_executable(dune ${client_src})
target_link_libraries(dune dune-common SDL2 SDL2_image SDL2_ttf SDL2_mixer ${SDL2PP_LIBRARIES} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Multimedia)
# >>>>>>> b38a09028bed847a2579ec53ab1d5ecbbd2b6dfb

# Server
add_executable(dune-server ${server_src} Server/includes/Control/ClientConnection.h Server/src/Control/ClientConnection.cpp Server/includes/Control/Commands/Command.h Server/src/Control/Command/Command.cpp Server/includes/Control/Commands/SelectUnitCommand.h Server/includes/Control/Commands/MoveUnitCommand.h Server/includes/Control/Commands/BuildBuildingCommand.h Server/includes/Control/Commands/CreateUnitCommand.h Server/src/Control/Command/SelectUnitCommand.cpp Server/src/Control/Command/BuildBuildingCommand.cpp Server/src/Control/Command/MoveUnitCommand.cpp Server/includes/Model/Player.h Server/src/Model/Player.cpp)
target_link_libraries(dune-server dune-common ${YAML_CPP_LIBRARIES})
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# INSTALACION

# Rutas
set(BINARIES_DIRPATH "/usr/bin")
set(SHAREDLIBS_DIRPATH "/usr/lib")
set(CONFIG_DIRPATH "/etc/dune")
set(ASSETS_DIRPATH "/var/dune")

# Common
install(TARGETS dune-common DESTINATION ${SHAREDLIBS_DIRPATH} PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Common/config DESTINATION ${CONFIG_DIRPATH}/common FILE_PERMISSIONS WORLD_READ WORLD_WRITE)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Common/assets DESTINATION ${ASSETS_DIRPATH}/common FILE_PERMISSIONS WORLD_READ WORLD_WRITE)

# Cliente
install(TARGETS dune DESTINATION ${BINARIES_DIRPATH} PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE WORLD_EXECUTE)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Client/config DESTINATION ${CONFIG_DIRPATH}/client FILE_PERMISSIONS WORLD_READ WORLD_WRITE)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Client/assets DESTINATION ${ASSETS_DIRPATH}/client FILE_PERMISSIONS WORLD_READ WORLD_WRITE)

# Server
install(TARGETS dune-server DESTINATION ${BINARIES_DIRPATH} PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Server/config DESTINATION ${CONFIG_DIRPATH}/server FILE_PERMISSIONS WORLD_READ WORLD_WRITE)
install(DIRECTORY DESTINATION ${ASSETS_DIRPATH}/server/assets/Database DIRECTORY_PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE)
#------------------------------------------------------------------------------
