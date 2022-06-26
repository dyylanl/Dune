#!/bin/bash

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
	tput cnorm
	exit 0
}

function helpPanel() {
    echo -e "${purpleColour} Opciones:"
    echo "  d: instalar DUNE"
    echo -e "  q: salir. ${endColour}"
     echo -e "\n${yellowColour} Ingrese una opcion: ${endColour}"
}

function installDependencies() {
	tput civis
	clear
    echo -e "${yellowColour} [*] Instalando librerias necesarias.... ${endColour}"
    echo ""
    echo -e "${grayColour}>> Instalando 'cmake'..."
    sudo apt-get install cmake > /dev/null 2>&1
    echo ""
    echo ">> Instalando 'libsdl2-dev'..."
    sudo apt-get install libsdl2-dev > /dev/null 2>&1
    echo ""
    echo ">> Instalando 'libsdl2-image-dev'..."
    sudo apt-get install libsdl2-image-dev  > /dev/null 2>&1
    echo ""
    echo ">> Instalando 'libsdl2-ttf-dev'..."
    sudo apt-get install libsdl2-ttf-dev  > /dev/null 2>&1
    echo ""
    echo ">> Instalando 'libsdl2-mixer-dev'..."
    sudo apt-get install libsdl2-mixer-dev > /dev/null 2>&1
    echo ""
    echo ">> Instalando 'libyaml-cpp-dev'..."
    sudo apt-get install libyaml-cpp-dev > /dev/null 2>&1
    echo ""
    echo ">> Instalando 'qtbase5-dev'..."
    sudo apt-get install qtbase5-dev > /dev/null 2>&1
    echo ""
    echo ">> Instalando 'qtmultimedia5-dev'..."
    sudo apt-get install qtmultimedia5-dev > /dev/null 2>&1
    echo ""
    echo -e ">> Instalando 'qtdeclarative5-dev' ${endColour}"
    sudo apt-get install qtdeclarative5-dev -y > /dev/null 2>&1
    echo ""
    echo -e "${greenColour}Instalación de librerias finalizada. ${endColour}"
    echo ""
    sleep 2
}

function installGame() {
	tput civis
	clear
    echo -e "${blueColour} Comenzando la instalacion de DUNE ${endColour}"
    sleep 2
    sudo rm -r build 2>&1
    mkdir build
    cd build
    sudo cmake .. > /dev/null 2>&1
    sudo make install -j6 > /dev/null 2>&1
    echo ""
    echo -e "\n${greenColour}[*] DUNE instalado en "$(pwd)"${endColour}\n"
    path=$pwd
    echo ""
    return
}

function post_installation() {
	echo "c) Ir a la carpeta donde se instalo DUNE."
	echo "q) Salir."
	echo "Ingrese una opcion: "
	read OPTION
	tput cnorm
	case $OPTION in
		c) 
			cd "$path"
			echo "Directorio DUNE"
			exit 0
			;;
		q) 
			echo "Adios!"
			exit 0
			;;
		*)
			helpPanel
            getInput
	esac
}

function init_installer() {
	helpPanel
	while :
	do
		read OPTION
		case $OPTION in
			d)
				echo ""
				installDependencies
            	installGame
            	post_installation
        			;;
        	q)
            	exit 0
        		;;
        	*)
            	echo ""
            	helpPanel
        		;;
		esac
	done
}

if [ "$(id -u)" == "0" ]; then
	echo -e "\n${greenColour}[*] Ejecutando en modo root${endColour}\n"
	init_installer
else
	echo -e "\n${redColour}[*] No soy root${endColour}\n"
fi
