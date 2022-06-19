#include "escenario.h"
#include <iostream>
#include <fstream>
#include <iostream>

Escenario::Escenario():tableroQT(10)
{
    this->filas = 10;
    this->columnas = 10;
    for(int outer = 0; outer < tableroQT.size(); ++outer)
        tableroQT[outer].resize(10);
    this->last_clicked = new Estado_last_clicked();
for (int i = 0; i < this->filas; i++){
    for(int j = 0;j < this->columnas ;j ++){
        //this->tableroQT.resize(100);
        Celda *celda = new Celda(this,"Arena",this->last_clicked,i,j);
        //celda->setEscenario(this);
        celda->setPos(j*32,i*32);
        this->addItem(celda);
        this->tableroQT [i][j] = celda;

    }

}
this->agregar_columna();
}


Escenario::Escenario(int new_filas, int new_columnas):tableroQT(new_filas)
{
    this->filas = new_filas;
    this->columnas = new_columnas;
    for(int outer = 0; outer < tableroQT.size(); ++outer)
        tableroQT[outer].resize(this->columnas);
    this->last_clicked = new Estado_last_clicked();
for (int i = 0; i < this->filas; i++){
    for(int j = 0;j < this->columnas ;j ++){
        //this->tableroQT.resize(100);
        Celda *celda = new Celda(this,"Arena",this->last_clicked,i,j);
        //celda->setEscenario(this);
        celda->setPos(j*32,i*32);
        this->addItem(celda);
        this->tableroQT [i][j] = celda;

    }
}
}


void Escenario::change_last_clicked(QString tipo){
    this->last_clicked->cambiar_estado(tipo);

}

void Escenario::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);

}

void Escenario::agregar_fila()
{
    this->filas = this->filas + 1;
    this->tableroQT.resize(this->filas);
    this->tableroQT[this->filas - 1].resize(this->columnas);
    for(int j = 0; j < this->columnas; j++){
        Celda *celda = new Celda(this,"Arena",this->last_clicked,this->filas -1,j);
        //celda->setEscenario(this);
        celda->setPos(j*32,(this->filas -1)*32);
        this->addItem(celda);
        this->tableroQT[this->filas - 1][j]   = celda;


    }
}

void Escenario::agregar_columna()
{
    this->columnas = this->columnas + 1;
    this->tableroQT[this->filas - 1].resize(this->columnas);
    for(int i = 0; i < this->filas; i++){
        this->tableroQT[i].resize(this->columnas);
        Celda *celda = new Celda(this,"Arena",this->last_clicked,i,this->columnas -1);
        //celda->setEscenario(this);
        celda->setPos((this->columnas -1) *32, i *32);
        this->addItem(celda);
        this->tableroQT[i][this->columnas - 1]   = celda;
    }
}

void Escenario::guardar(QString file_name){
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "Tablero";
    out << YAML::BeginMap;
    out << YAML::Key << "Filas";
    out << YAML::Value << this->filas;
    out << YAML::Key << "Columnas";
    out << YAML::Value << this->columnas;

    for(int i = 0; i < this->filas; i++){
        for(int j = 0; j < this->columnas;j++){
             std::stringstream key_i_j;
             key_i_j << i << "," << j;
             out << YAML::Key << key_i_j.str();
             out << YAML::BeginMap;
             out << YAML::Key << "Tipo";
             std::string tipo = this->tableroQT[i][j]->get_tipo_suelo().toStdString();
             out << YAML::Value << tipo;
             out << YAML::EndMap;


        }
    }
    out << YAML::EndMap;
    //const char *path="/home/fede/Desktop/Taller_1/qt/prueba_9/test.yaml";
    std::ofstream fout(file_name.toStdString());
    fout << out.c_str() << std::endl;
}

void Escenario::cargar(QString file_name)
{
    YAML::Node node = YAML::LoadFile(file_name.toStdString());
    int filas = node["Tablero"]["Filas"].as<int>();
    int columnas= node["Tablero"]["Columnas"].as<int>();
    std::cout << filas << std::endl;
    std::cout << columnas << std::endl;
    this->eliminar_celdas_actuales();

    this->tableroQT.resize(filas);
    for(int i = 0; i < filas; i++){
        this->tableroQT[i].resize(columnas);
            for(int j = 0; j < columnas;j++){
                 std::stringstream key_i_j;
                 key_i_j << i << "," << j;
                 std::string tipo = node["Tablero"][key_i_j.str()]["Tipo"].as<std::string>();
                 Celda *celda_cargada = new Celda(this,tipo,this->last_clicked,i,j);
                 celda_cargada->setPos(j*32,i*32);
                 this->addItem(celda_cargada);
                 this->tableroQT [i][j] = celda_cargada;
                 std::cout <<tipo << std::endl;
                }
    }
}

void Escenario::eliminar_celdas_actuales(){
    for (int i = 0; i < this->filas; i++){
        for(int j = 0;j < this->columnas ;j ++){
            Celda* celda_a_borrar = this->tableroQT [i][j];
            this->removeItem(celda_a_borrar);
            delete(celda_a_borrar);
        }
    }
}

void Escenario::colocar_estructura(int x, int y){
    bool colocar = this->verificar_celdas(x,y);
    if(colocar == false){
        return;
    }
    std::cout << "llego a colocar en x:"<<x<<"en y:"<<y << std::endl;
    QGraphicsPixmapItem* cc_ordos = new QGraphicsPixmapItem();
    std::cout << "Rompo 1" << std::endl;
    QPixmap imagen;
    imagen.load(":/resources/centro_1.png");
    cc_ordos->setPixmap(imagen);
    cc_ordos ->setPos(y*32,x*32);
    cc_ordos->setOffset(-32,-32);
    cc_ordos->setZValue(1);
    this->addItem(cc_ordos);
}

bool Escenario::verificar_celdas(int x, int y)
{
 std::cout << "llego a verificar" <<std::endl;
    for(int i = x - 1; i < x + 2; i++){
        for(int j = y -1; j < y+ 2;j++){
            if((i > this->filas) ||( j > this->columnas)){
                return false;

            }
            std::cout << "i:" << i << " j:"<<j << std::endl;
            Celda* celda = this->tableroQT[i][j];
            QString suelo = celda->get_tipo_suelo();
            std::cout << suelo.toStdString() << std::endl;
            if(suelo != "Roca"){
                return false;
            }
            bool ocupada = celda->get_ocupacion();
            std::cout<< ocupada <<std::endl;
            if(ocupada == true){
                return false;
            }
        }
    }
    return true;
}

Escenario::~Escenario(){
    this->eliminar_celdas_actuales();
    delete(this->last_clicked);
}
