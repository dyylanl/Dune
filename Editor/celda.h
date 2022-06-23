#ifndef CELDA_H
#define CELDA_H

#include <QGraphicsPixmapItem>
#include "estado_last_clicked.h"
#include <QString>
#include "yaml-cpp/yaml.h"
#include "dialog_asignar_especia.h"

class Escenario;

class Celda: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT


public:
    //Celda(Estado_last_clicked* last_clicked, int x, int y);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QString get_tipo_suelo();
    Celda(std::string tipo,Estado_last_clicked* last_clicked, int x, int y);
    Celda(Escenario* escenario,std::string tipo,Estado_last_clicked* last_clicked, int x, int y);
    void setImagen(QString tipo);
    void setEscenario(Escenario* new_escenario);
    bool get_ocupacion();
    void ocupar();
    void desocupar();
    int get_cant_especia();
    void set_cant_especia(int cantidad);

    ~Celda();

public slots:
    void cambiar_cantidad_especia(int cantidad);

private:
    QPixmap imagen;
    Estado_last_clicked* estado_last_clicked;
    QString estado_actual = "Vacio";
    Escenario* escenario;
    int pos_x;
    int pos_y;
    bool ocupada;
    Dialog_asignar_especia dialogo_asignar_especia;
    int cant_especia = 0;

};

#endif // CELDA_H
