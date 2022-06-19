#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pic_atreides(":/resources/atreides.png");
    QPixmap pic_harkonnen(":/resources/harkonnen.png");
    QPixmap pic_ordos(":/resources/ordos.png");
    ui->atreides_pic_label->setPixmap(pic_atreides.scaled(100,100,Qt::KeepAspectRatio));
    ui->harkonnen_pic_label->setPixmap(pic_harkonnen.scaled(100,100,Qt::KeepAspectRatio));
    ui->ordos_pic_label->setPixmap(pic_ordos.scaled(100,100,Qt::KeepAspectRatio));
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button_confirmar_clicked()
{
    this->text_IP = this->ui->IP_text_input ->text();
    this->text_puerto = this->ui->puerto_text_input->text();
    this->text_nombre = this->ui->nombre_text_input->text();

    this->cliente = new Client(this->text_IP.toStdString(),this->text_puerto.toStdString());    
// TODO: LANZAR EXCEPCION SI NO SE CONECTA
    this->ui->stackedWidget->setCurrentIndex(1);
    QString mensaje_bienvenida = "Bienvenido a Dune " + this->text_nombre;
    this->ui->bienvenida_label->setText(mensaje_bienvenida);

}


void MainWindow::on_button_volver_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}

std::string MainWindow::get_nombre()
{
 return this->text_nombre.toStdString();
}


void MainWindow::on_button_cofirmar_cant_nombre_clicked()
{
    this->text_nombre_partida = this->ui->nombre_partida_input->text();
    this->text_cantidad_jugadores = this->ui->cantidad_jugadores_input->text();
    this->ui->stackedWidget->setCurrentIndex(3);

}


void MainWindow::on_button_crear_partida_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_button_atreides_clicked()
{
    this->text_casa = "Atreides";
    this->cliente->crear_partida(this->text_casa.toStdString(),this->text_nombre_partida.toStdString(),this->text_cantidad_jugadores.toStdString());
    QApplication::quit();
}


void MainWindow::on_button_harkonnen_clicked()
{
    this->text_casa = "Harkonnen";
    this->cliente->crear_partida(this->text_casa.toStdString(),this->text_nombre_partida.toStdString(),this->text_cantidad_jugadores.toStdString());
    QApplication::quit();
}


void MainWindow::on_button_ordos_clicked()
{
    this->text_casa = "Ordos";
    this->cliente->crear_partida(this->text_casa.toStdString(),this->text_nombre_partida.toStdString(),this->text_cantidad_jugadores.toStdString());
    QApplication::quit();
}

Client* MainWindow::get_cliente(){
    return this->cliente;
}