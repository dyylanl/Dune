#include "dialog_forma_tablero.h"
#include "ui_dialog_forma_tablero.h"

Dialog_forma_tablero::Dialog_forma_tablero(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_forma_tablero)
{
    ui->setupUi(this);
}

Dialog_forma_tablero::~Dialog_forma_tablero()
{
    delete ui;
}

void Dialog_forma_tablero::on_buttonBox_accepted()
{
    emit nuevos_valores (this->ui->spinbox_filas->value(),this->ui->spinbox_columnas->value());
}

