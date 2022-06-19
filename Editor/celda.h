#ifndef CELDA_H
#define CELDA_H

#include <QGraphicsPixmapItem>
#include "estado_last_clicked.h"
#include <QString>
#include "yaml-cpp/yaml.h"

class Escenario;

class Celda: public QGraphicsPixmapItem
{
    QPixmap imagen;
    Estado_last_clicked* estado_last_clicked;
    QString estado_actual;
    Escenario* escenario;
    int pos_x;
    int pos_y;
    bool ocupada;

public:
    //Celda(Estado_last_clicked* last_clicked, int x, int y);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QString get_tipo_suelo();
    Celda(std::string tipo,Estado_last_clicked* last_clicked, int x, int y);
    Celda(Escenario* escenario,std::string tipo,Estado_last_clicked* last_clicked, int x, int y);
    void setImagen(QString tipo);
    void setEscenario(Escenario* new_escenario);
    bool get_ocupacion();
    ~Celda();
};

#endif // CELDA_H
