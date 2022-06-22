#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "escenario.h"
#include <QMediaPlayer>
#include "qfiledialog.h"
#include "yaml-cpp/yaml.h"
#include "dialog_forma_tablero.h"
#include "dialog_cant_jugadores.h"
#include "dialog_asignar_jugadoro.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
     void cambiar_forma_tablero_acepted(int new_filas,int new_columnas);

     void mostrar_dialog_asignar_jugador();

private slots:
    void on_button_arena_clicked();

    void on_button_roca_clicked();

    void on_button_cimas_clicked();

    void on_button_dunas_clicked();

    void on_button_precipicio_clicked();

    void on_button_vacio_clicked();

    void on_button_agregar_fila_clicked();

    void on_button_columna_clicked();

    void on_button_mute_clicked();

    void on_actionSave_triggered();

    void on_actionLoadd_triggered();

    void on_button_tiles_clicked();

    void on_button_unidades_clicked();

    void on_button_construcciones_clicked();

    void on_button_cambiar_forma_clicked();



    void on_button_const_ordos_clicked();

    void on_button_cant_jugadores_clicked();

    void cambiar_cantidad_jugadores(int cant);

    void on_button_centro_construccion_clicked();

    void on_button_eliminar_construccion_clicked();

    void on_button_asignar_jugador_clicked();

    void on_button_especia_clicked();

private:
    Ui::MainWindow *ui;
    Escenario* escenario;
    QMediaPlayer *music_player;
    Dialog_forma_tablero dialogo_forma_tablero;
    QFileDialog* file_manager;
    Dialog_cant_jugadores dialogo_cant_jugadores;
    Dialog_asignar_jugadoro dialog_asignar_jugadores;
};
#endif // MAINWINDOW_H
