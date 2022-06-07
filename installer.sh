#!/bin/bash

#------------------------------------------------------------------------------
# Mensajes

function waitingInputMessage() {
    printf "> Ingrese una opción: "
}

function initialMessage () {
    clear
}

function helpMessage() {
    echo "Opciones:"
    echo "  d: instala dependencias necesarias."
    echo "  u: desinstalador."
    echo "  q: cerrar."
    echo ""
}

function unknownInput() {
    echo "Opción desconocida (ingrese 'h' para ayuda, 'q' para salir)."
    echo ""
}

#------------------------------------------------------------------------------
# Compilación e instalación

function build() {
    sudo rm -rf build
    mkdir build
    cd build
    cmake ..
}

function installDependencies() {
    echo "=== INSTALACIÓN DE DEPENDENCIAS ==="
    echo ""
    echo ">> Instalando 'cmake'..."
    sudo apt-get install cmake
    echo ""
    echo ">> Instalando 'libsdl2-dev'..."
    sudo apt-get install libsdl2-dev
    echo ""
    echo ">> Instalando 'libsdl2-image-dev'..."
    sudo apt-get install libsdl2-image-dev
    echo ""
    echo ">> Instalando 'libsdl2-ttf-dev'..."
    sudo apt-get install libsdl2-ttf-dev
    echo ""
    echo ">> Instalando 'libsdl2-mixer-dev'..."
    sudo apt-get install libsdl2-mixer-dev
    echo ""
    echo ">> Instalando 'libyaml-cpp-dev'..."
    sudo apt-get install libyaml-cpp-dev
    echo ""
    echo ">> Instalando 'nlohmann-json-dev'..."
    sudo apt-get install nlohmann-json-dev
    echo ""
        echo "Instalación de dependencias finalizada."
    echo ""
}

function installGame() {
    echo "=== INSTALACIÓN DEL JUEGO ==="
    build
    sudo make install -j4
    echo ""
    echo "Instalación del juego finalizada."
    echo ""
}

function all() {
    installDependencies
    installGame
}

function uninstall() {
    echo "=== DESINSTALADOR ==="
    sudo rm -rf build
    sudo rm -rf /etc/dune
    sudo rm -rf /var/dune
    sudo rm -rf /usr/bin/dune-server
    sudo rm -rf /usr/bin/dune
    sudo rm -rf /usr/lib/libdune-common.so
    echo ""
    echo "Se ha desinstalado el juego con éxito."
    echo ""
}

#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# Loop ppal

# exit when any command fails
set -e

initialMessage
helpMessage
waitingInputMessage

while :
do
    read OPTION
    case $OPTION in
        d)
            echo ""
            installDependencies
            waitingInputMessage
        ;;
        i)
            echo ""
            installGame
            waitingInputMessage
        ;;
        a)
            echo ""
            installDependencies
            installGame
            waitingInputMessage
        ;;
        u)
            echo ""
            uninstall
            waitingInputMessage
        ;;
        h)
            echo ""
            helpMessage
            waitingInputMessage
        ;;
        m)
            echo ""
            waitingInputMessage
        ;;
        q)
            exit 0
        ;;
        *)
            echo ""
            unknownInput
            waitingInputMessage
        ;;
    esac
done

#------------------------------------------------------------------------------