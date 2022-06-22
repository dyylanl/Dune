#ifndef ESCENARIO_H
#define ESCENARIO_H

#include "celda.h"
#include <QGraphicsScene>
#include <vector>
#include <QString>
#include <QVector2D>
#include "estado_last_clicked.h"
#include "yaml-cpp/yaml.h"
#include "construccion.h"
#include <QMessageBox>


class MainWindow;


class Escenario: public QGraphicsScene
{
    std::vector<std::vector<Celda*>> tablero;
    QVector<QVector<Celda*>> tableroQT;
    Estado_last_clicked* last_clicked;
    QVector<Construccion*> construcciones;
    int filas;
    int columnas;
    int cant_jugadores;
    int cant_construcciones;
    std::vector<int> jugadores;

public:
    Escenario();
    Escenario(int new_filas, int new_columnas);
    void change_last_clicked(QString tipo);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void agregar_fila();
    void agregar_columna();
    void guardar(QString file_name);
    void cargar(QString file_name);
    void eliminar_celdas_actuales();
    void colocar_estructura(int x ,int y);
    bool verificar_celdas(int x, int y);
    void cambiar_cantidad_jugadores(int cantidad);
    void ocupar_celdas(int x, int y);
    int get_cantidad_construcciones();
    int get_cantidad_jugadores();
    void eliminar_estructura(Construccion* estructura,int x, int y);
    void eliminar_todas_estructuras();
    bool verificar_jugador(int jugador);
    ~Escenario();
    void mostrar_dialog_asignar_jugador();
    void agregar_jugador(int jugador);

private:
    void desocupar_celdas(int x, int y);
};

#endif // ESCENARIO_H
