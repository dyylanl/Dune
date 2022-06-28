#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , reloj(new QTimer())
{
    ui->setupUi(this);
    QPixmap pic_atreides(":/resources/atreides.png");
    QPixmap pic_harkonnen(":/resources/harkonnen.png");
    QPixmap pic_ordos(":/resources/ordos.png");
    ui->atreides_pic_label->setPixmap(pic_atreides.scaled(100,100,Qt::KeepAspectRatio));
    ui->harkonnen_pic_label->setPixmap(pic_harkonnen.scaled(100,100,Qt::KeepAspectRatio));
    ui->ordos_pic_label->setPixmap(pic_ordos.scaled(100,100,Qt::KeepAspectRatio));
    std::cout << "rompo en Index" << std::endl;
    ui->stackedWidget->setCurrentIndex(0);
    std::cout << "ROMPI" << std::endl;
    connect(this->reloj,SIGNAL(timeout()),this,SLOT(actualizar_lista_partidas()));
    std::cout << "ROMPE EL RELOJ" << std::endl;

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
    //Socket skt(this->text_IP.toStdString(),this->text_puerto.toStdString());
    
    QString mensaje_bienvenida = "Bienvenido a Dune " + this->text_nombre;
    //this->vector_socket.push_back(skt);
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
    //this->text_cantidad_jugadores = this->ui->cantidad_jugadores_input->text();
    //this->cliente->crear_partida(this->text_nombre.toStdString(),this->text_nombre_partida.toStdString());
    this->cliente->enviar_nombre_jugador(this->text_nombre.toStdString());
    this->cliente->enviar_accion("crear");
    std::cout << this->text_nombre_partida.toStdString();
    this->cliente->enviar_nombre_partida(this->text_nombre_partida.toStdString());
    //this->protocolo.crear_partida(this->skt,this->text_nombre.toStdString(),this->text_nombre_partida.toStdString())
    this->mostrar_mapas();
    this->ui->stackedWidget->setCurrentIndex(4);

}

void MainWindow::mostrar_mapas(){
    std::vector<std::vector<std::string>> mapas = this->cliente->listar_mapas();
   std::cout << "\n\n";
   //std::stringstream descripcion_mapa;
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
    this->ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_button_harkonnen_clicked()
{
    this->text_casa = "Harkonnen";
    this->ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_button_ordos_clicked()
{
    this->text_casa = "Ordos";
    this->ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_button_unirse_partida_clicked()
{   
    
    this->reloj->start(5000);
    std::cout << "paso el reloj" << std::endl;
    //this->cliente->enviar_nombre_y_comando(this->text_nombre.toStdString(),"listar");
    //this->cliente->enviar_nombre_jugador(this->text_nombre.toStdString());
    std::cout << "LLEGO A LA PARTIDA" << std::endl;
    this->cliente->enviar_accion("listar");
    std::cout << "TRATO DE RECIBIR" << std::endl;
    std::vector<std::vector<std::string>> list_1 = this->cliente->listar_partidas();
    std::cout << "LLEGO A LA PARTIDA" << std::endl;
    this->cliente->enviar_accion("listar");
    std::cout << "TRATO DE RECIBIR" << std::endl;
    std::vector<std::vector<std::string>> list_2 = this->cliente->listar_partidas();
    this->mostrar_partidas();
    //this->mostrar_partidas();

    this->ui->stackedWidget->setCurrentIndex(3);
    std::cout << "PASO MOSTRAR NO ERROR" << std::endl;
    //AGREGAR CURRENITEM DE LA LISTA PARA SELECIONAR
}
/*
Client* MainWindow::get_cliente()const{
    return this->cliente;
}*/

void MainWindow::mostrar_partidas(){
    this->ui->lista_partidas->clear();
    std::cout << "LLEGO A LA PARTIDA" << std::endl;
    this->cliente->enviar_accion("listar");
    std::cout << "TRATO DE RECIBIR" << std::endl;
    std::vector<std::vector<std::string>> list = this->cliente->listar_partidas();
    std::cout << "recibo las partidas" << std::endl;
    if (!list.empty()) {
       int n = (int)list.size();
       for (int i = 0; i < n;  i++) {
           std::string nombre_partida = list[i][2];
            //std::cout << nombre_partida;
            //std::cout << " " << list[i][0] << "/" << list[i][1] << std::endl;
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
    this->reloj->stop();
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
        msgBox.setText("Partida creada con exito");
        msgBox.exec();
      if(this->cliente->partida_iniciada()) { // ACA TIENE QUE ESTAR BLOQUEADO HASTA QUE SE CREE LA PARTIDA
        std::cout << "Se completo la partida..." << std::endl;
        QMessageBox msgBox;
        msgBox.setText("La partida va a empezar");
        msgBox.exec();
        this->ui->stackedWidget->setCurrentIndex(5);
        //QApplication::quit();
        /*map = protocol.recvMap(socket);
        std::cout << "Mapa recibido..." << std::endl;*/
      }  
  } else {
    QMessageBox msgBox;
        msgBox.setText("La partida esta llena. Elija otra");
        msgBox.exec();
        
        std::cout << "ERROR UNIENDOME A LA PARTIDA "<< std::endl;
        return;
  }

    /*int respuesta_unirse_partida = this->cliente->recibir_respuesta();
    if(respuesta_unirse_partida == 9){
        QMessageBox msgBox;
        msgBox.setText("Se unio con exito");
        msgBox.exec();
    }

    //this->ui->stackedWidget->setCurrentIndex(5);
    if(this->cliente->partida_iniciada()){
        QMessageBox msgBox;
        msgBox.setText("La partida va a empezar");
        msgBox.exec();
        QApplication::quit();
    }*/

}

void MainWindow::on_button_confirmar_mapa_clicked()
{
    QListWidgetItem *mapa_elegido =  this->ui->lista_mapas->currentItem();
    std::cout << mapa_elegido->text().toStdString() << std::endl;
    char map_id = mapa_elegido->text().toStdString().at(6);
    /*int prueba_int = std::stoi(prueba);
    int map_id = std::stoi(prueba);
    std::cout << map_id  << std::endl;*/
    std::cout << map_id << std::endl;
    int map_id_cast =(int)map_id - 48;
    std::cout << map_id_cast << std::endl;
    this->cliente->enviar_map_id(map_id_cast);


    if(this->cliente->conexion_exitosa()) { 
      std::cout << "Creacion exitosa" << std::endl;
        QMessageBox msgBox;
        msgBox.setText("Partida creada con exito");
        msgBox.exec();
      if(this->cliente->partida_iniciada()) { // ACA TIENE QUE ESTAR BLOQUEADO HASTA QUE SE CREE LA PARTIDA
        std::cout << "Se completo la partida..." << std::endl;
        QMessageBox msgBox;
        msgBox.setText("La partida va a empezar");
        msgBox.exec();
        this->close();
        //QApplication::quit();
        /*map = protocol.recvMap(socket);
        std::cout << "Mapa recibido..." << std::endl;*/
      }  
  } else {
        QMessageBox msgBox;
        msgBox.setText("Esa partida ya existe. Cambie el nombre");
        msgBox.exec();
        this->ui->stackedWidget->setCurrentIndex(2);
        return;
        std::cout << "ERROR UNIENDOME A LA PARTIDA "<< std::endl;
  }

/*
    int respuesta_crear_partida = this->cliente->recibir_respuesta();
    if(respuesta_crear_partida == 9){
        QMessageBox msgBox;
        msgBox.setText("Partida creada con exito");
        msgBox.exec();
    }
    
    this->ui->stackedWidget->setCurrentIndex(5);
    std::cout << "PASO EL" << std::endl;
    if(this->cliente->partida_iniciada()){
        std::cout << "EMPIEZA LA PARTIDA" << std::endl;
        QMessageBox msgBox;
        msgBox.setText("La partida va a empezar");
        msgBox.exec();
        QApplication::quit();
    }
*/
}

void MainWindow::actualizar_lista_partidas(){
    std::cout << "ACTUALIZO" << std::endl;
    this->mostrar_partidas();
    return;
}