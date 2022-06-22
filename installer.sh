#!/bin/bash

# Author: dypa

greenColour="\e[0;32m\033[1m"
endColour="\033[0m\e[0m"
redColour="\e[0;31m\033[1m"
blueColour="\e[0;34m\033[1m"
yellowColour="\e[0;33m\033[1m"
purpleColour="\e[0;35m\033[1m"
turquoiseColour="\e[0;36m\033[1m"
grayColour="\e[0;37m\033[1m"

trap ctrl_c INT

function ctrl_c() {
	echo -e "\n${redColour}[*] ABORTANDO ${endColour}\n"
	exit 0
}

function waitingInputMessage() {
    printf "> Ingrese una opción: "
}

function initialMessage () {
    clear
}

function helpMessage() {
    echo "Opciones:"
    echo "  d: instalar DUNE"
    echo "  q: salir."
    echo ""
}

function unknownInput() {
    echo " >'q' para salir."
    echo " >'d' para instalar DUNE"
    echo ""
}

function build() {
    sudo mkdir /home/"$USER"/Dune
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
    cd "/home/$"USER"/Dune"
    sudo make install -j6
    echo ""
    echo -e "\n${greenColour}[*] DUNE instalado en /home/"$USER"/Dune/build ${endColour}\n"
    echo ""
    return
}

function post_installation() {
	echo "	c) Ir a la carpeta donde se instalo DUNE."
	echo " 	q) Salir."
	waitingInputMessage
	read OPTION
	case $OPTION in
		c) 
			cd "/home/"$USER"/Dune/build"
			exit 0
			;;
		q) 
			echo "Adios!"
			;;
		*)
			exit 0
	esac
}

function init_installer() {
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
            			post_installation
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
}

if [ "$(id -u)" == "0" ]; then
	echo -e "\n${greenColour}[*] Ejecutando en modo root${endColour}\n"
	init_installer
else
	echo -e "\n${redColour}[*] Ejecute el installer como root${endColour}\n"
	exit 0
fi

