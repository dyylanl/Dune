#ifndef ESTADO_LAST_CLICKED_H
#define ESTADO_LAST_CLICKED_H
#include <QString>
#include <string>

class Estado_last_clicked
{
    QString estado;
public:
    Estado_last_clicked();
    void cambiar_estado(QString nuevo_estado);
    QString get_estado();
};

#endif // ESTADO_LAST_CLICKED_H
