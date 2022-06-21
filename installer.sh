#!/bin/bash

function waitingInputMessage() {
    printf "> Ingrese una opción: "
}

function initialMessage () {
    clear
}

function helpMessage() {
    echo "Opciones:"
    echo "  d: instalador."
    echo "  q: salir."
    echo ""
}

function unknownInput() {
    echo " >'q' para salir."
    echo " >'d' para instalar librerias"
    echo ""
}

function build() {
    sudo rm -rf build
    mkdir build
    cd build
    cmake ..
}

function installDependencies() {
    echo "=== INSTALANDO LIBRERIAS ==="
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
    echo ">> Instalando 'qtbase5-dev'..."
    sudo apt-get install qtbase5-dev
    echo ">> Instalando 'qtmultimedia5-dev'..."
    sudo apt-get install qtmultimedia5-dev
    echo ">> Instalando 'qtdeclarative5-dev'"
    sudo apt-get install qtdeclarative5-dev
    echo ""
        echo "Instalación de librerias finalizada."
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
            build
            installGame
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
