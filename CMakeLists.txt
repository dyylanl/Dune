cmake_minimum_required(VERSION 2.8.12)
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
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# ARCHIVOS FUENTE

FILE(GLOB_RECURSE common_src "Common/src/*.cpp")
FILE(GLOB_RECURSE client_src "Client/src/*.cpp")
FILE(GLOB_RECURSE server_src "Server/*.cpp")
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# TARGETS

# Common
add_library(dune-common SHARED ${common_src} Common/includes/Thread.h Common/src/Thread.cpp Common/includes/Socket/Socket.h Common/includes/Exceptions/Exception.h Common/includes/Exceptions/ClosedSocketException.h Common/includes/Exceptions/LoginException.h Common/includes/Socket/SocketWrapper.h Common/src/Socket/SocketWrapper.cpp Common/src/Exceptions/Exception.cpp Common/src/Socket/Socket.cpp)

# Client
add_executable(dune ${client_src} Common/includes/Exceptions/ClosedSocketException.h Client/src/main.cpp)
target_link_libraries(dune dune-common SDL2 SDL2_image SDL2_ttf SDL2_mixer)

# Server
add_executable(dune-server ${server_src} Common/src/Exceptions/Exception.cpp Server/src/main.cpp)
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
