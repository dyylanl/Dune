
#include <iostream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "escenario.h"


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
this->cant_jugadores = 1;
this->cant_construcciones = 0;
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
            Celda* celda = this->tableroQT[i][j];
             std::stringstream key_i_j;
             key_i_j << i << "," << j;
             out << YAML::Key << key_i_j.str();
             out << YAML::BeginMap;
             out << YAML::Key << "Tipo";
             std::string tipo = celda->get_tipo_suelo().toStdString();
             out << YAML::Value << tipo;
             out << YAML::Key << "Ocupada";
             out << YAML::Value << celda->get_ocupacion();
             out << YAML::Key << "Cantidad Especia";
             out << YAML::Value << celda->get_cant_especia();
             out << YAML::EndMap;


        }
    }
    out << YAML::EndMap;
    out<< YAML::Key << "Cantidad Jugadores";
    out<< YAML::Value << this->get_cantidad_jugadores();
    out<< YAML::Key << "Estructuras";
    out << YAML::BeginMap;
    out << YAML::Key << "Cantidad";
    out << YAML::Value << this->cant_construcciones;
    std::cout << this->cant_construcciones << std::endl;
    for(int i = 0; i < this->cant_construcciones;i++){
        std::cout << i << std::endl;
        Construccion* constr = this->construcciones[i];
        std::stringstream key_constr;
        key_constr << i;
        out << YAML::Key << key_constr.str();
        out << YAML::BeginMap;
        out << YAML::Key << "Pos_x";
        int pos_x = constr->get_pos_x();
        out << YAML::Value << pos_x;
        out << YAML::Key << "Pos_y";
        int pos_y = constr->get_pos_y();
        out << YAML::Value << pos_y;
        out << YAML::Key << "ID_jugador";
        int id_jugador = constr->get_jugador();
        out << YAML::Value << id_jugador;
        out << YAML::EndMap;
    }
    out << YAML::EndMap;
    //const char *path="/home/fede/Desktop/Taller_1/qt/prueba_9/test.yaml";
    std::ofstream fout(file_name.toStdString());
    fout << out.c_str() << std::endl;
}

void Escenario::cargar(QString file_name)
{
    //this->eliminar_celdas_actuales();
    this->eliminar_todas_estructuras();
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
                 int cant_especia = node["Tablero"][key_i_j.str()]["Cantidad Especia"].as<int>();
                 Celda *celda_cargada = new Celda(this,tipo,this->last_clicked,i,j);
                 celda_cargada->set_cant_especia(cant_especia);
                 celda_cargada->setPos(j*32,i*32);
                 this->addItem(celda_cargada);
                 this->tableroQT [i][j] = celda_cargada;
                 std::cout <<tipo << std::endl;
                }
    }
    this->jugadores.erase(this->jugadores.begin(),this->jugadores.end());
    int cantidad_jugadores = node["Cantidad Jugadores"].as<int>();
    this->cant_jugadores = cantidad_jugadores;
    int cant_estructuras = node["Estructuras"]["Cantidad"].as<int>();
    for(int i = 0; i< cant_estructuras; i ++){
        std::stringstream key_constr;
        key_constr << i;
        int pos_x = node["Estructuras"][key_constr.str()]["Pos_x"].as<int>();
        int pos_y = node["Estructuras"][key_constr.str()]["Pos_y"].as<int>();
        int id_jugador = node["Estructuras"][key_constr.str()]["ID_jugador"].as<int>();
        this->jugadores.push_back(id_jugador);
        Construccion* construccion = new Construccion(pos_x,pos_y,this->last_clicked,this);
        construccion->asignar_jugador(id_jugador);
        construccion ->setPos(pos_y*32,pos_x*32);
        construccion->setOffset(-32,-32);
        this->addItem(construccion);
        this->construcciones.push_back(construccion);
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
    this->ocupar_celdas(x,y);

    std::cout << "llego a colocar en x:"<<x<<"en y:"<<y << std::endl;
    //QGraphicsPixmapItem* cc_ordos = new QGraphicsPixmapItem();
    Construccion* estructura = new Construccion(x,y,this->last_clicked,this);
    std::cout << "Rompo 1" << std::endl;
    this->construcciones.append(estructura);
    //->setPixmap(imagen);
    estructura ->setPos(y*32,x*32);
    estructura->setOffset(-32,-32);
    estructura->setZValue(1);
    this->addItem(estructura);
    this->cant_construcciones += 1;
}

bool Escenario::verificar_celdas(int x, int y)
{
 std::cout << "llego a verificar" <<std::endl;
    for(int i = x - 1; i < x + 2; i++){
        for(int j = y -1; j < y+ 2;j++){
            if((i > this->filas) ||( j > this->columnas)){
                return false;

            }
            if((i < 0) ||( j < 0)){
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


void Escenario::ocupar_celdas(int x, int y){
    for(int i = x - 1; i < x + 2; i++){
        for(int j = y -1; j < y+ 2;j++){
            this->tableroQT[i][j]->ocupar();
        }
    }
}

int Escenario::get_cantidad_construcciones()
{
    return this->cant_construcciones;
}

int Escenario::get_cantidad_jugadores()
{
    return this->cant_jugadores;
}

void Escenario::eliminar_estructura(Construccion *estructura,int x, int y)
{
    this->removeItem(estructura);
    this->desocupar_celdas(x,y);
    this->cant_construcciones -= 1;

}

void Escenario::desocupar_celdas(int x, int y){
    for(int i = x - 1; i < x + 2; i++){
        for(int j = y -1; j < y+ 2;j++){
            Celda* celda = this->tableroQT[i][j];
            celda->desocupar();
        }
       }
}

void Escenario::eliminar_todas_estructuras()
{
 for(int i = 0; i < this->cant_construcciones; i++){
     delete(this->construcciones[i]);
 }
}

bool Escenario::verificar_jugadores_asignados(){
    for(int i = 0; i < this->cant_construcciones; i++){
        int id_jugador = this->construcciones[i]->get_jugador();
        if(id_jugador == 0){
            return false;
        }
    }
    return true;
}

bool Escenario::verificar_jugador(int jugador)
{
    if ( std::find(this->jugadores.begin(), this->jugadores.end(), jugador) != this->jugadores.end()){
        return true;
    }else{

        return false;
    }

}

void Escenario::agregar_jugador(int jugador){
    this->jugadores.push_back(jugador);
}

void Escenario::cambiar_cantidad_jugadores(int cantidad)
{
    this->cant_jugadores = cantidad;
    std::cout << this->cant_jugadores << std::endl;
}

void Escenario::mostrar_dialog_asignar_jugador(){

}

Escenario::~Escenario(){
    this->eliminar_celdas_actuales();
    delete(this->last_clicked);
    this->eliminar_todas_estructuras();
}
