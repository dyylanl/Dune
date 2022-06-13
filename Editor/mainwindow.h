#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "escenario.h"
#include <QMediaPlayer>
#include "yaml-cpp/yaml.h"
#include "dialog_forma_tablero.h"

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



private:
    Ui::MainWindow *ui;
    Escenario* escenario;
    QMediaPlayer *music_player;
    Dialog_forma_tablero dialogo_forma_tablero;
};
#endif // MAINWINDOW_H
