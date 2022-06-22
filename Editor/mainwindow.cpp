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


void MainWindow::on_button_vacio_clicked()
{
    this->escenario->change_last_clicked("Vacio");
}


void MainWindow::on_button_agregar_fila_clicked()
{
    this->escenario->agregar_fila();
}


void MainWindow::on_button_columna_clicked()
{
    this->escenario->agregar_columna();
}


void MainWindow::on_button_mute_clicked()
{
    this->music_player->pause();



}


void MainWindow::on_actionSave_triggered()
{
    int cant_construcciones = this->escenario->get_cantidad_construcciones();
    int cant_jugadores = this->escenario->get_cantidad_jugadores();
    if(cant_construcciones < cant_jugadores){
        QMessageBox msgBox;
        msgBox.setText("La cantidad de construcciones es Menor a la cantidad de jugadores");
        msgBox.exec();
        return;
    }
    if(cant_construcciones > cant_jugadores){
        QMessageBox msgBox;
        msgBox.setText("La cantidad de construcciones es Mayor a la cantidad de jugadores");
        msgBox.exec();
        return;
    }
    QString extension = ".yaml";
    QString save_name = file_manager->getSaveFileName(this,"Sava a File",QDir::homePath());
    QString full_path = save_name + extension;
    std::cout << full_path.toStdString() << std::endl;
    this->escenario->guardar(full_path);
}


void MainWindow::on_actionLoadd_triggered()
{
    QString filter = "yaml (*.yaml)";
    QString file_name = this->file_manager->getOpenFileName(this,"Open a file",QDir::homePath(),filter);

    this->escenario->cargar(file_name);
}


void MainWindow::on_button_tiles_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_button_unidades_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(1);
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
    //std::cout << new_filas <<std::endl;
    //std::cout << new_columnas<< std::endl;
    //checquear que sea removido de la escena
    delete(this->escenario);
    this->escenario = new Escenario(new_filas,new_columnas);
    this->ui->graphicsView->setScene(this->escenario);
}

void MainWindow::mostrar_dialog_asignar_jugador()
{
 this->dialog_asignar_jugadores.show();
}


void MainWindow::on_button_const_ordos_clicked()
{
    this->escenario->change_last_clicked("CC_Ordos");


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

