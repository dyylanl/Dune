#ifndef CONSTRUCCION_H
#define CONSTRUCCION_H

#include <QGraphicsPixmapItem>
#include "estado_last_clicked.h"
#include "dialog_asignar_jugadoro.h"


class Escenario;

class Construccion: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Construccion(int x, int y, Estado_last_clicked* last_estado,Escenario* escenario);
    int get_pos_x();
    int get_pos_y();
    void asignar_jugador(int jugador);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void verifcar_jugador(int jugador);

private:
    int pos_x;
    int pos_y;
    int jugador;
    QPixmap imagen;
    Estado_last_clicked* last_button_clicked;
    Escenario* escenario;
    Dialog_asignar_jugadoro dialogo_asignar_jugadores;

};

#endif // CONSTRUCCION_H
