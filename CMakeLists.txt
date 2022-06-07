cmake_minimum_required(VERSION 3.21)
project(dune)

# FLAGS DE COMPILACION
# Estándar a utilizar
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Flags para el manejo de errores
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors")

# Optimizaciones
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# Debugging
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -DDEBUG -fno-inline")

# YAML
FIND_PACKAGE( yaml-cpp REQUIRED)
INCLUDE_DIRECTORIES(${YAML_CPP_INCLUDE_DIRS})
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

FILE(GLOB_RECURSE common_src "Common/src/*.cpp")
FILE(GLOB_RECURSE client_src "Client/src/*.cpp")
FILE(GLOB_RECURSE server_src "Server/*.cpp")
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# TARGETS

# Common
add_library(dune-common SHARED ${common_src} Common/includes/Thread.h Common/src/Thread.cpp Common/includes/Socket/Socket.h Common/includes/Exceptions/Exception.h Common/includes/Exceptions/ClosedSocketException.h Common/includes/Exceptions/LoginException.h Common/src/Exceptions/Exception.cpp Common/src/Socket/Socket.cpp)

# Client
add_executable(dune ${client_src} Common/includes/Exceptions/ClosedSocketException.h Client/src/main.cpp Client/src/Characters/Player.cpp Client/src/Characters/Player.h Client/src/Animation/Animation.cpp Client/src/Animation/Animation.h Client/src/Core/Engine.cpp Client/src/Core/Engine.h Client/src/Events/EventManager.cpp Client/src/Events/EventManager.h Client/includes/Client.h Client/src/Client.cpp)
target_link_libraries(dune dune-common SDL2 SDL2_image SDL2_ttf SDL2_mixer)
target_link_libraries(dune ${SDL2PP_LIBRARIES})

# Server
add_executable(dune-server ${server_src} Common/src/Exceptions/Exception.cpp Server/src/main.cpp Server/includes/Control/Server.h Server/src/Control/Server.cpp Server/includes/Model/Position.h Server/src/Model/Position.cpp Server/src/Model/Units/Unit.cpp Server/includes/Model/Units/Unit.h Server/includes/Model/Map.h Server/src/Model/Map.cpp Server/includes/Model/AStarNode.h Server/src/Model/AStarNode.cpp Server/includes/Model/AStar.h Server/src/Model/AStar.cpp Server/includes/Model/Terrains/Terrain.h Server/src/Model/Terrains/Terrain.cpp Server/includes/Model/Terrains/Rock.h Server/src/Model/Terrains/Rock.cpp Server/includes/Model/Terrains/Dunes.h Server/src/Model/Terrains/Dunes.cpp Server/includes/Model/Terrains/Precipice.h Server/src/Model/Terrains/Precipice.cpp Server/includes/Model/Units/States/UnitState.h Server/src/Model/Units/States/UnitState.cpp Server/includes/Model/Weapons/Weapon.h Server/src/Model/Weapons/Weapon.cpp Server/includes/Model/Attackable.h Server/src/Model/Attackable.cpp Server/includes/Model/Attacker.h Server/src/Model/Attacker.cpp Server/includes/Model/Buildings/Building.h Server/src/Model/Buildings/Building.cpp Server/includes/Model/Terrains/Sand.h Server/src/Model/Terrains/Sand.cpp Server/includes/Model/defs.h)
# include_directories(${PROJECT_SOURCE_DIR}/Server/includes/Control)
target_link_libraries(dune-server dune-common)
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
