#ifndef DIALOG_ASIGNAR_ESPECIA_H
#define DIALOG_ASIGNAR_ESPECIA_H

#include <QDialog>

namespace Ui {
class Dialog_asignar_especia;
}

class Dialog_asignar_especia : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_asignar_especia(QWidget *parent = nullptr);
    ~Dialog_asignar_especia();


signals:
    void especia_asignada(int cantidad);

private slots:
    void on_buttonbox_cant_especia_accepted();

private:
    Ui::Dialog_asignar_especia *ui;
};

#endif // DIALOG_ASIGNAR_ESPECIA_H
