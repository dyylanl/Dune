#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <fstream>
#include <iostream>
#include <QFileDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), escenario(new Escenario(10,10)), music_player(new QMediaPlayer()),
      dialogo_forma_tablero(new Dialog_forma_tablero()), file_manager(new QFileDialog()),
      dialogo_cant_jugadores(new Dialog_cant_jugadores())

{
    ui->setupUi(this);
    this->ui->graphicsView->setScene(this->escenario);
    this->music_player->setMedia(QUrl("qrc:/resources/music.ogg"));
    this->music_player->setVolume(50);
    this->music_player->play();
    ui->stackedWidget->setCurrentIndex(0);

    connect(&this->dialogo_forma_tablero,SIGNAL(nuevos_valores(int,int)),this,SLOT(cambiar_forma_tablero_acepted(int,int)));

    connect(&this->dialogo_cant_jugadores,SIGNAL(nueva_cantidad_jugadores(int)),this,SLOT(cambiar_cantidad_jugadores(int)));


   }

MainWindow::~MainWindow()
{
    delete ui;
    delete(this->music_player);
    delete(this->escenario);
    delete(this->file_manager);
}



void MainWindow::on_button_arena_clicked()
{
    this->escenario->change_last_clicked("Arena");

}


void MainWindow::on_button_roca_clicked()
{
    this->escenario->change_last_clicked("Roca");
}


void MainWindow::on_button_cimas_clicked()
{
    this->escenario->change_last_clicked("Cimas");
}


void MainWindow::on_button_dunas_clicked()
{
    this->escenario->change_last_clicked("Dunas");
}


void MainWindow::on_button_precipicio_clicked()
{
 this->escenario->change_last_clicked("Precipicio");
}



void MainWindow::on_button_agregar_fila_clicked()
{
    this->escenario->agregar_fila();
}


void MainWindow::on_button_columna_clicked()
{
    this->escenario->agregar_columna();
}



void MainWindow::on_actionSave_triggered()
{
    int cant_construcciones = this->escenario->get_cantidad_construcciones();
    int cant_jugadores = this->escenario->get_cantidad_jugadores();
    std::string str_cant_construcciones = std::to_string(cant_construcciones);
    std::string str_cant_jugaadores = std::to_string(cant_jugadores);
    if(cant_construcciones < cant_jugadores){
        std::string mensaje = "La cantidad de construcciones(" + str_cant_construcciones + ")" + " es Menor a la cantidad de jugadores(" + str_cant_jugaadores + ")";
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString(mensaje));
        msgBox.exec();
        return;
    }
    if(cant_construcciones > cant_jugadores){
        QMessageBox msgBox;
        std::string mensaje = "La cantidad de construcciones(" + str_cant_construcciones + ")" + "es Mayor a la cantidad de jugadores(" + str_cant_jugaadores + ")";
        msgBox.setText("La cantidad de construcciones es Mayor a la cantidad de jugadores");
        msgBox.exec();
        return;
    }
    bool todos_jugadores_asignados = this->escenario->verificar_jugadores_asignados();
    if(todos_jugadores_asignados == false){
        QMessageBox msgBox;
        msgBox.setText("Asignele un jugador válido a cada construccion");
        msgBox.exec();
        return;
    }
    QString extension = ".yaml";
    QString save_name = file_manager->getSaveFileName(this,"Sava a File",QDir::homePath());
    if(save_name == ""){
        return;
    }
    QString full_path = save_name + extension;
    this->escenario->guardar(full_path);
}


void MainWindow::on_actionLoadd_triggered()
{
    QString filter = "yaml (*.yaml)";
    QString file_name = this->file_manager->getOpenFileName(this,"Open a file",QDir::homePath(),filter);
    if(file_name == ""){
        return;
    }
    this->escenario->cargar(file_name);
}


void MainWindow::on_button_tiles_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}



void MainWindow::on_button_construcciones_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_button_cambiar_forma_clicked()
{
    dialogo_forma_tablero.show();
}

void MainWindow::cambiar_forma_tablero_acepted(int new_filas,int new_columnas){
    delete(this->escenario);
    this->escenario = new Escenario(new_filas,new_columnas);
    this->ui->graphicsView->setScene(this->escenario);
}

void MainWindow::mostrar_dialog_asignar_jugador()
{
 this->dialog_asignar_jugadores.show();
}



void MainWindow::on_button_cant_jugadores_clicked()
{
 this->dialogo_cant_jugadores.show();
}


void MainWindow::cambiar_cantidad_jugadores(int cant){
 this->escenario->cambiar_cantidad_jugadores(cant);
}

void MainWindow::on_button_centro_construccion_clicked()
{
    this->escenario->change_last_clicked("Construccion");
}


void MainWindow::on_button_eliminar_construccion_clicked()
{
    this->escenario->change_last_clicked("Eliminar");
}


void MainWindow::on_button_asignar_jugador_clicked()
{
    this->escenario->change_last_clicked("Asignar Jugador");
}


void MainWindow::on_button_especia_clicked()
{
    this->escenario->change_last_clicked("Especia");
}


void MainWindow::on_button_asignar_especia_clicked()
{
    this->escenario->change_last_clicked("Asignar Especia");
}


void MainWindow::on_button_play_clicked()
{
    this->music_player->play();
}


void MainWindow::on_button_pausa_clicked()
{
    this->music_player->pause();
}


void MainWindow::on_button_opciones_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(3);
}

