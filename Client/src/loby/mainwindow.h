#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QString>
#include <string>
#include <vector>
#include <QListWidget>
#include "../../includes/Client.h"
//#include "../../../Common/includes/Socket/Socket.h"
//#include "../../../Common/includes/Protocol.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    std::string get_nombre();
    ~MainWindow();
    Client* get_cliente()const;

private slots:
    void on_button_confirmar_clicked();

    void on_button_volver_clicked();



    void on_button_cofirmar_cant_nombre_clicked();

    void on_button_crear_partida_clicked();

    void on_button_atreides_clicked();

    void on_button_harkonnen_clicked();

    void on_button_ordos_clicked();

    void on_button_unirse_partida_clicked();

    void on_button_confirmar_unirse_clicked();

    void on_button_confirmar_mapa_clicked();

    void actualizar_lista_partidas();

    void mostrar_partidas();
    
    void mostrar_mapas();

private:
    Ui::MainWindow *ui;
    QString text_IP;
    QString text_puerto;
    QString text_nombre;
    QString text_casa;
    QString text_nombre_partida;
    QString text_cantidad_jugadores;
    QString casa;
    Client* cliente;
    //std::vector<Socket> vector_socket;
    //Socket* skt;
    //Protocol protocolo;
    QTimer* reloj;
};
#endif // MAINWINDOW_H
