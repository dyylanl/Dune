#include "escenario.h"
#include <iostream>
Construccion::Construccion(int x, int y, Estado_last_clicked *last_estado,Escenario* escenario):dialogo_asignar_jugadores(new Dialog_asignar_jugadoro())
{
    this->escenario = escenario;
    this->pos_x = x;
    this->pos_y = y;
    this->last_button_clicked = last_estado;
    this->imagen.load(":/resources/centro_1.png");
    this->setPixmap(this->imagen);

    connect(&this->dialogo_asignar_jugadores,SIGNAL(jugador_asignado(int)),this,SLOT(verifcar_jugador(int)));
}

int Construccion::get_pos_x()
{
    return this->pos_x;
}

int Construccion::get_pos_y()
{
    return this->pos_y;
}

void Construccion::asignar_jugador(int jugador)
{
 this->jugador = jugador;
}

void Construccion::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    QString tipo = this->last_button_clicked->get_estado();
    if(tipo == "Asignar"){

    }
    if(tipo == "Eliminar"){
        this->escenario->eliminar_estructura(this,pos_x,pos_y);
    }

    if(tipo == "Asignar Jugador"){
        int maximo_actual = this->escenario->get_cantidad_jugadores();
        this->dialogo_asignar_jugadores.cambiar_maximo(maximo_actual);
        this->dialogo_asignar_jugadores.show();
    }


}

int Construccion::get_jugador()
{
 return this->jugador;
}

void Construccion::verifcar_jugador(int jugador){
    if(jugador == 0){
        QMessageBox msgBox;
        msgBox.setText("El ID del jugador no pude ser 0. Elija otro");
        msgBox.exec();
        return;
    }
    bool jugador_asignado = this->escenario->verificar_jugador(jugador);
    if(jugador_asignado == true){
        QMessageBox msgBox;
        msgBox.setText("Ese ID ya fue asignado. Asignele uno diferente");
        msgBox.exec();
    }
    else{
        this->escenario->agregar_jugador(jugador);
        this->jugador = jugador;    }
}

Construccion::~Construccion(){
}
