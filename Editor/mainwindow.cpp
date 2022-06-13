#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <fstream>
#include <iostream>
#include <QFileDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), escenario(new Escenario()), music_player(new QMediaPlayer()), dialogo_forma_tablero(new Dialog_forma_tablero())
{
    ui->setupUi(this);
    this->ui->graphicsView->setScene(this->escenario);
    this->music_player->setMedia(QUrl("qrc:/resources/music.ogg"));
    this->music_player->setVolume(50);
    this->music_player->play();
    ui->stackedWidget->setCurrentIndex(0);

    connect(&this->dialogo_forma_tablero,SIGNAL(nuevos_valores(int,int)),this,SLOT(cambiar_forma_tablero_acepted(int,int)));


   }

MainWindow::~MainWindow()
{
    delete ui;
    delete(this->music_player);
    delete(this->escenario);
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
    this->escenario->guardar();
}


void MainWindow::on_actionLoadd_triggered()
{
    QString filter = "All files (*.*) ;; yaml (*.yaml)";
    QString file_name = QFileDialog::getOpenFileName(this,"Open a file",QDir::homePath(),filter);

    this->escenario->cargar();
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
    std::cout << new_filas <<std::endl;
    std::cout << new_columnas<< std::endl;
    //checquear que sea removido de la escena
    delete(this->escenario);
    this->escenario = new Escenario(new_filas,new_columnas);
    this->ui->graphicsView->setScene(this->escenario);
}

