#include "celda.h"
#include "qpainter.h"
#include <iostream>
#include <string>
#include "escenario.h"



Celda::Celda(Escenario* escenario, std::string tipo,Estado_last_clicked* last_clicked, int x, int y): dialogo_asignar_especia(new Dialog_asignar_especia)
{
    this->escenario = escenario;
    this->setImagen(QString::fromStdString(tipo));
    this->estado_last_clicked = last_clicked;
    this->pos_x = x;
    this->pos_y = y;
    this->ocupada = false;
    connect(&this->dialogo_asignar_especia,SIGNAL(especia_asignada(int)),this,SLOT(cambiar_cantidad_especia(int)));
}

void Celda::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    QString tipo = this->estado_last_clicked->get_estado();
    this->setImagen(tipo);


}

void Celda::setImagen(QString tipo){

    QString arena = "Arena";
    QString roca = "Roca";
    QString dunas = "Dunas";
    QString cimas = "Cimas";
    QString precipicio = "Precipicio";
    QString vacio = "Vacio";
    QString especia = "Especia";
    QString asignar_especia = "Asignar Especia";

    if(this->ocupada == true){
        return;
    }

    if(tipo == asignar_especia && this->estado_actual == especia){
        this->dialogo_asignar_especia.show();
    }

    if(tipo == especia && this->estado_actual == arena){
        this->estado_actual = tipo;
        this->imagen.load(":/resources/tile_especia.png");
        this->imagen = this->imagen.scaled(32, 32);
        this->setPixmap(imagen);
    }

    if (tipo == arena){
        this->estado_actual = tipo;
        this->imagen.load(":/resources/tile_arena.png");
        this->imagen = this->imagen.scaled(32, 32);
        this->setPixmap(imagen);
    }
    if(tipo == roca){
        this->estado_actual = tipo;
        this->imagen.load(":/resources/tile_roca.png");
        this->imagen = this->imagen.scaled(32, 32);
        this->setPixmap(imagen);
    }
    if(tipo == dunas){
        this->estado_actual = tipo;
        this->imagen.load(":/resources/tile_dunas.png");
        this->imagen = this->imagen.scaled(32, 32);
        this->setPixmap(imagen);
    }
    if(tipo == cimas){
        this->estado_actual = tipo;
        this->imagen.load(":/resources/tile_cimas.png");
        this->imagen = this->imagen.scaled(32, 32);
        this->setPixmap(imagen);
    }
    if(tipo == precipicio){
        this->estado_actual = tipo;
        this->imagen.load(":/resources/tile_precipicio.png");
        this->imagen = this->imagen.scaled(32, 32);
        this->setPixmap(imagen);
    }
    if(tipo == vacio){
        this->estado_actual = tipo;
        this->imagen.load(":/resources/tile_vacio.jpg");
        this->imagen = this->imagen.scaled(32, 32);
        this->setPixmap(imagen);
    }
    if(tipo == "Construccion"){
        this->escenario->colocar_estructura(this->pos_x, this->pos_y);

    }
}
void Celda::setEscenario(Escenario* new_escenario){
    this->escenario = new_escenario;
}

bool Celda::get_ocupacion()
{
    return this->ocupada;
}

void Celda::ocupar(){
    this->ocupada = true;
}

void Celda::desocupar()
{
    this->ocupada = false;
}

int Celda::get_cant_especia()
{
    return this->cant_especia;
}

void Celda::set_cant_especia(int cantidad)
{
    this->cant_especia = cantidad;
}

Celda::~Celda()
{

}

void Celda::cambiar_cantidad_especia(int cantidad)
{
    this->cant_especia = cantidad;
}

QString Celda::get_tipo_suelo()
{
 return this->estado_actual;
}
