#include "dialog_cant_jugadores.h"
#include "ui_dialog_cant_jugadores.h"

Dialog_cant_jugadores::Dialog_cant_jugadores(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_cant_jugadores)
{
    ui->setupUi(this);
}

Dialog_cant_jugadores::~Dialog_cant_jugadores()
{
    delete ui;
}

void Dialog_cant_jugadores::on_buttonBox_cant_jugadores_accepted()
{
    emit nueva_cantidad_jugadores(this->ui->cant_jugadores_spinbox->value());

}

