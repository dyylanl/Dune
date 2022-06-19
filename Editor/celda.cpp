#include "celda.h"
#include "qpainter.h"
#include <iostream>
#include <string>
#include "escenario.h"

/*Celda::Celda(Estado_last_clicked* last_clicked,int x, int y):imagen(":/resources/tile_vacio.jpg")
{
    this->estado_actual = "Vacio";
    this->estado_last_clicked = last_clicked;
    this->imagen = this->imagen.scaled(32, 32);
    this->setPixmap(imagen);
    this->pos_x = x;
    this->pos_y = y;
}*/

Celda::Celda(std::string tipo,Estado_last_clicked* last_clicked, int x, int y)
{
    this->estado_actual = QString::fromStdString(tipo);
    this->setImagen(QString::fromStdString(tipo));
    this->estado_last_clicked = last_clicked;
    this->pos_x = x;
    this->pos_y = y;
}


Celda::Celda(Escenario* escenario, std::string tipo,Estado_last_clicked* last_clicked, int x, int y)
{
    this->escenario = escenario;
    this->estado_actual = QString::fromStdString(tipo);
    this->setImagen(QString::fromStdString(tipo));
    this->estado_last_clicked = last_clicked;
    this->pos_x = x;
    this->pos_y = y;
    this->ocupada = false;
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
    if(tipo == "CC_Ordos"){
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

Celda::~Celda()
{

}

QString Celda::get_tipo_suelo()
{
 return this->estado_actual;
}
