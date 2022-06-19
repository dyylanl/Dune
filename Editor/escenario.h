#ifndef ESCENARIO_H
#define ESCENARIO_H

#include "celda.h"
#include <QGraphicsScene>
#include <vector>
#include <QString>
#include <QVector2D>
#include "estado_last_clicked.h"
#include "yaml-cpp/yaml.h"

class Escenario: public QGraphicsScene
{
    std::vector<std::vector<Celda*>> tablero;
    QVector<QVector<Celda*>> tableroQT;
    Estado_last_clicked* last_clicked;
    int filas;
    int columnas;

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
    ~Escenario();
};

#endif // ESCENARIO_H
