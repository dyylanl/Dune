#ifndef CELDA_H
#define CELDA_H

#include <QGraphicsPixmapItem>
#include "estado_last_clicked.h"
#include <QString>
#include "yaml-cpp/yaml.h"

class Celda: public QGraphicsPixmapItem
{
    QPixmap imagen;
    Estado_last_clicked* estado_last_clicked;
    QString estado_actual;

public:
    Celda(Estado_last_clicked* last_clicked);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QString get_tipo_suelo();
    Celda(std::string tipo,Estado_last_clicked* last_clicked);
    void setImagen(QString tipo);
    ~Celda();
};

#endif // CELDA_H
