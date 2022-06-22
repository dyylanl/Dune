#ifndef DIALOG_CANT_JUGADORES_H
#define DIALOG_CANT_JUGADORES_H

#include <QDialog>

namespace Ui {
class Dialog_cant_jugadores;
}

class Dialog_cant_jugadores : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_cant_jugadores(QWidget *parent = nullptr);
    ~Dialog_cant_jugadores();
signals:
    void nueva_cantidad_jugadores(int cantidad);

private slots:
    void on_buttonBox_cant_jugadores_accepted();

private:
    Ui::Dialog_cant_jugadores *ui;
};

#endif // DIALOG_CANT_JUGADORES_H
