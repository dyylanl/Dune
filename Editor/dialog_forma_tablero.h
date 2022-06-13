#ifndef DIALOG_FORMA_TABLERO_H
#define DIALOG_FORMA_TABLERO_H

#include <QDialog>

namespace Ui {
class Dialog_forma_tablero;
}

class Dialog_forma_tablero : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_forma_tablero(QWidget *parent = nullptr);
    ~Dialog_forma_tablero();

signals:
    void nuevos_valores(int new_filas,int new_columnas);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog_forma_tablero *ui;
};

#endif // DIALOG_FORMA_TABLERO_H
