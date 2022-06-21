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
    this->ui->stackedWidget->setCurrentIndex(1);
    
    this->cliente = new Client(this->text_IP.toStdString(),this->text_puerto.toStdString());
    
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
    this->cliente->crear_partida(this->text_nombre.toStdString(),this->text_nombre_partida.toStdString(),this->text_cantidad_jugadores.toInt());
   
    
    this->ui->stackedWidget->setCurrentIndex(4);

}


void MainWindow::on_button_crear_partida_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_button_atreides_clicked()
{
    this->text_casa = "Atreides";
}


void MainWindow::on_button_harkonnen_clicked()
{
    this->text_casa = "Harkonnen";
}


void MainWindow::on_button_ordos_clicked()
{
    this->text_casa = "Ordos";
}


void MainWindow::on_button_unirse_partida_clicked()
{   std::cout << "LLEGO A UNIRME"<< std::endl;
    //this->cliente->enviar_nombre_jugador(this->text_nombre.toStdString());
    std::cout << "LLEGO A UNIRME 2"<< std::endl;
    //this->cliente->crear_partida(this->text_nombre.toStdString(),"duelo",2);
    /*std::vector<std::string> partidas = this->cliente->listar_partidas();
    for(size_t i = 0; i< partidas.size(); i ++){
      std::string nombre_partida = partidas[i]; 
      std::cout << nombre_partida << std::endl;
      
    }*/
    std::vector<std::string> list = this->cliente->listar_partidas();
        if (!list.empty()) {
        int n = (int)list.size();
        for (int i = 0; i <= (n-2); i = i+3) {
            std::string nombre_partida = list[i+2];
            std::cout << nombre_partida;
            std::cout << " " << list[i] << "/" << list[i+1] << std::endl;
            QListWidgetItem *partida_en_lista = new QListWidgetItem;
            partida_en_lista->setText(QString::fromStdString(nombre_partida));
            this->ui->lista_partidas->insertItem(i,partida_en_lista);
            
            }
        }
    this->ui->stackedWidget->setCurrentIndex(3);
    //AGREGAR CURRENITEM DE LA LISTA PARA SELECIONAR
}

Client* MainWindow::get_cliente()const{
    return this->cliente;
}

