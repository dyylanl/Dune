#include "estado_last_clicked.h"
#include <iostream>
#include <string.h>

Estado_last_clicked::Estado_last_clicked()
{

}

void Estado_last_clicked::cambiar_estado(QString nuevo_estado){
    this->estado = nuevo_estado;
}

QString Estado_last_clicked::get_estado()
{
    return this->estado;
}
