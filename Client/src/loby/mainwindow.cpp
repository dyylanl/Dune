#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pic_atreides(":/resources/atreides.png");
    QPixmap pic_harkonnen(":/resources/harkonnen.png");
    QPixmap pic_ordos(":/resources/ordos.png");
    QPixmap pic_titulo(":/resources/titulo.jpeg");
    ui->atreides_pic_label->setPixmap(pic_atreides.scaled(100,100,Qt::KeepAspectRatio));
    ui->harkonnen_pic_label->setPixmap(pic_harkonnen.scaled(100,100,Qt::KeepAspectRatio));
    ui->ordos_pic_label->setPixmap(pic_ordos.scaled(100,100,Qt::KeepAspectRatio));
    ui->titulo_label->setPixmap(pic_titulo.scaled(200,100,Qt::KeepAspectRatio));
    ui->stackedWidget->setCurrentIndex(0);

    
    this->ui->button_unirse_partida->setFixedSize(200,100);
    this->ui->button_crear_partida->setFixedSize(200,100);
    this->ui->button_confirmar->setFixedSize(150,75);
    this->ui->titulo_label->setFixedSize(200,100);
    this->ui->button_confirmar_unirse->setFixedSize(150,75);
    this->ui->button_cofirmar_cant_nombre->setFixedSize(150,75);
    this->ui->button_confirmar_mapa->setFixedSize(150,75);
    this->ui->button_actualizar_partidas->setFixedSize(150,50);
    this->ui->button_volver_list_partidas->setFixedSize(150,75);
    this->ui->button_volver_crear->setFixedSize(150,75);

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
    this->cliente->enviar_nombre_jugador(this->text_nombre.toStdString());
}




std::string MainWindow::get_nombre()
{
 return this->text_nombre.toStdString();
}


void MainWindow::on_button_cofirmar_cant_nombre_clicked()
{
    this->text_nombre_partida = this->ui->nombre_partida_input->text();;
    this->cliente->enviar_accion("crear");
    std::cout << this->text_nombre_partida.toStdString();
    this->cliente->enviar_nombre_partida(this->text_nombre_partida.toStdString());
    this->mostrar_mapas();
    this->ui->stackedWidget->setCurrentIndex(4);

}

void MainWindow::mostrar_mapas(){
    std::vector<std::vector<std::string>> mapas = this->cliente->listar_mapas();
   std::cout << "\n\n";
  if (mapas.size() == 0) {
    std::cout << "No hay mapas cargados en el server" << std::endl;
  } else {
  int total_maps_uploaded = (int)mapas.size();
    for (int i = 0; i < total_maps_uploaded; i++) {
        //int id = i + 1;
        std::stringstream id_stream;
        id_stream << i +1;
        std::string id_string(id_stream.str());

        std::string map_str = "\nMapa " ;
        std::string filas_str = "\nFilas: ";
        std::string columnas_str = "\nColumnas: ";
        std::string jugadores_requeridos_str = "\nJugadores Requeridos: ";
        std::string descripcion_mapa = map_str + id_string + filas_str + mapas[i][0] + columnas_str + mapas[i][1] + jugadores_requeridos_str + mapas[i][2];
        std::cout << descripcion_mapa << std::endl;
        QListWidgetItem *mapa_en_lista = new QListWidgetItem;
        mapa_en_lista->setText(QString::fromStdString(descripcion_mapa));
        this->ui->lista_mapas->insertItem(i,mapa_en_lista);
    }
  }
}

void MainWindow::on_button_crear_partida_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_button_atreides_clicked()
{
    this->text_casa = "Atreides";
    this->close();
    QApplication::exit(1);
}


void MainWindow::on_button_harkonnen_clicked()
{
    this->text_casa = "Harkonnen";
    this->close();
    QApplication::exit(1);
}


void MainWindow::on_button_ordos_clicked()
{
    this->text_casa = "Ordos";
    this->close();
    QApplication::exit(1);
}


void MainWindow::on_button_unirse_partida_clicked()
{   

    this->mostrar_partidas();
    this->ui->stackedWidget->setCurrentIndex(3);
}

Client* MainWindow::get_cliente()const{
    return this->cliente;
}

void MainWindow::mostrar_partidas(){
    this->ui->lista_partidas->clear();
    this->cliente->enviar_accion("listar");
    std::vector<std::vector<std::string>> list = this->cliente->listar_partidas();
    if (!list.empty()) {
       int n = (int)list.size();
       for (int i = 0; i < n;  i++) {
           std::string nombre_partida = list[i][2];
            std::string nombre_partida_completo = nombre_partida + " " + list[i][0] + "/" + list[i][1];
            std::cout << nombre_partida_completo << std::endl;
            QListWidgetItem *partida_en_lista = new QListWidgetItem;
            partida_en_lista->setText(QString::fromStdString(nombre_partida_completo));
            this->ui->lista_partidas->insertItem(i,partida_en_lista);
            std::cout << "PASO MOSTRAR PARTIDAS" << std::endl;
        }
    }
}

void MainWindow::on_button_confirmar_unirse_clicked()
{
    QListWidgetItem *partida_elegida =  this->ui->lista_partidas->currentItem();
    if(partida_elegida == nullptr){
        QMessageBox msgBox;
        msgBox.setText("Elija una partida");
        msgBox.exec();
        return;
    }
    std::string buf;                 // Have a buffer string
    std::stringstream ss(partida_elegida->text().toStdString());       // Insert the string into a stream

    std::vector<std::string> tokens; // Create vector to hold our words

    while (ss >> buf){
        tokens.push_back(buf);
    }
    std::cout << tokens[0] << std::endl;
    this->cliente->enviar_accion("unirse");
    this->cliente->enviar_nombre_partida(tokens[0]);


    if(this->cliente->conexion_exitosa()) { 
      std::cout << "Union exitosa" << std::endl;
        QMessageBox msgBox;
        msgBox.setText("Se unio con éxito");
        msgBox.exec();
      if(this->cliente->partida_iniciada()) { // ACA TIENE QUE ESTAR BLOQUEADO HASTA QUE SE CREE LA PARTIDA
        std::cout << "Se completo la partida..." << std::endl;
        QMessageBox msgBox;
        msgBox.setText("La partida va a empezar");
        msgBox.exec();
        this->ui->stackedWidget->setCurrentIndex(5);
      }  
  } else {
    QMessageBox msgBox;
        msgBox.setText("La partida esta llena. Elija otra");
        msgBox.exec();
        
        std::cout << "ERROR UNIENDOME A LA PARTIDA "<< std::endl;
        return;
    }


}

void MainWindow::on_button_confirmar_mapa_clicked()
{
    QListWidgetItem *mapa_elegido =  this->ui->lista_mapas->currentItem();
    if(mapa_elegido == nullptr){
        QMessageBox msgBox;
        msgBox.setText("Elija un mapa");
        msgBox.exec();
        return;
    }
    std::cout << mapa_elegido->text().toStdString() << std::endl;
    char map_id = mapa_elegido->text().toStdString().at(6);
    std::cout << map_id << std::endl;
    int map_id_cast =(int)map_id - 48;
    std::cout << map_id_cast << std::endl;
    this->cliente->enviar_map_id(map_id_cast);


    if(this->cliente->conexion_exitosa()) {
      std::cout << "Creacion exitosa" << std::endl;
        QMessageBox msgBox;
        msgBox.setText("Partida creada con exito");
        msgBox.exec();
        this->ui->stackedWidget->setCurrentIndex(6);
      if(this->cliente->partida_iniciada()) { // ACA TIENE QUE ESTAR BLOQUEADO HASTA QUE SE CREE LA PARTIDA
        std::cout << "Se completo la partida..." << std::endl;
        QMessageBox msgBox;
        msgBox.setText("La partida va a empezar");
        msgBox.exec();
        this->ui->stackedWidget->setCurrentIndex(5);
      }  
  } else {
        QMessageBox msgBox;
        msgBox.setText("Esa partida ya existe. Cambie el nombre");
        msgBox.exec();
        this->ui->stackedWidget->setCurrentIndex(2);
        return;
        std::cout << "ERROR UNIENDOME A LA PARTIDA "<< std::endl;
       
    }

}

void MainWindow::actualizar_lista_partidas(){
    std::cout << "ACTUALIZO" << std::endl;
    this->mostrar_partidas();
    return;
}

void MainWindow::on_button_volver_list_partidas_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(1);
}





void MainWindow::on_button_actualizar_partidas_clicked()
{
    //ACTUALIZAR
    std::cout << "ACTUALIZO" << std::endl;
    this->mostrar_partidas();
    return;
}


void MainWindow::on_button_volver_crear_clicked()
{
    this->ui->stackedWidget->setCurrentIndex(1);
}

