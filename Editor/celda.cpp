#include "celda.h"
#include <iostream>
#include <string>

Celda::Celda(Estado_last_clicked* last_clicked):imagen(":/resources/tile_vacio.jpg")
{
    this->estado_actual = "Vacio";
    this->estado_last_clicked = last_clicked;
    this->imagen = this->imagen.scaled(32, 32);
    this->setPixmap(imagen);
}

Celda::Celda(std::string tipo,Estado_last_clicked* last_clicked)
{
    this->estado_actual = QString::fromStdString(tipo);
    this->setImagen(QString::fromStdString(tipo));
    this->estado_last_clicked = last_clicked;
}

void Celda::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    QString tipo = this->estado_last_clicked->get_estado();
    this->estado_actual = tipo;
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
        this->imagen.load(":/resources/tile_arena.png");
        this->imagen = this->imagen.scaled(32, 32);
        this->setPixmap(imagen);
    }
    if(tipo == roca){
        this->imagen.load(":/resources/tile_roca.png");
        this->imagen = this->imagen.scaled(32, 32);
        this->setPixmap(imagen);
    }
    if(tipo == dunas){
        this->imagen.load(":/resources/tile_dunas.png");
        this->imagen = this->imagen.scaled(32, 32);
        this->setPixmap(imagen);
    }
    if(tipo == cimas){
        this->imagen.load(":/resources/tile_cimas.png");
        this->imagen = this->imagen.scaled(32, 32);
        this->setPixmap(imagen);
    }
    if(tipo == precipicio){
        this->imagen.load(":/resources/tile_precipicio.png");
        this->imagen = this->imagen.scaled(32, 32);
        this->setPixmap(imagen);
    }
    if(tipo == vacio){
        this->imagen.load(":/resources/tile_vacio.jpg");
        this->imagen = this->imagen.scaled(32, 32);
        this->setPixmap(imagen);
    }
}

Celda::~Celda()
{

}

QString Celda::get_tipo_suelo()
{
return this->estado_actual;
}
