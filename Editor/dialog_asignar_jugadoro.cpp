#include "dialog_asignar_jugadoro.h"
#include "ui_dialog_asignar_jugadoro.h"

Dialog_asignar_jugadoro::Dialog_asignar_jugadoro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_asignar_jugadoro)
{
    ui->setupUi(this);
}

Dialog_asignar_jugadoro::~Dialog_asignar_jugadoro()
{
    delete ui;
}

void Dialog_asignar_jugadoro::cambiar_maximo(int max)
{
    this->ui->spinbox_asignar_jugador->setMaximum(max);
}

void Dialog_asignar_jugadoro::on_buttonbox_asignar_jugador_accepted()
{
    emit jugador_asignado(this->ui->spinbox_asignar_jugador->text().toInt());
}

