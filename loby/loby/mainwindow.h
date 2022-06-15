#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <string>

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

private slots:
    void on_button_confirmar_clicked();

    void on_button_volver_clicked();



private:
    Ui::MainWindow *ui;
    QString text_IP;
    QString text_puerto;
    QString text_nombre;
    QString text_casa;
};
#endif // MAINWINDOW_H
