#ifndef DIALOG_ASIGNAR_JUGADORO_H
#define DIALOG_ASIGNAR_JUGADORO_H

#include <QDialog>

namespace Ui {
class Dialog_asignar_jugadoro;
}

class Dialog_asignar_jugadoro : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_asignar_jugadoro(QWidget *parent = nullptr);
    ~Dialog_asignar_jugadoro();

signals:
    void jugador_asignado(int jugador);

public slots:
    void cambiar_maximo(int max);
private slots:
    void on_buttonbox_asignar_jugador_accepted();

private:
    Ui::Dialog_asignar_jugadoro *ui;
};

#endif // DIALOG_ASIGNAR_JUGADORO_H
