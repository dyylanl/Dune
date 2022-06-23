#include "dialog_asignar_especia.h"
#include "ui_dialog_asignar_especia.h"
#include <iostream>

Dialog_asignar_especia::Dialog_asignar_especia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_asignar_especia)
{
    ui->setupUi(this);
}

Dialog_asignar_especia::~Dialog_asignar_especia()
{
    delete ui;
}

void Dialog_asignar_especia::on_buttonbox_cant_especia_accepted()
{
    emit especia_asignada(this->ui->spinbox_cant_especia->text().toInt());
}

