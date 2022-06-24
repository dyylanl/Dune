/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page_inicio;
    QLabel *titulo_label;
    QPushButton *button_confirmar;
    QWidget *layoutWidget;
    QGridLayout *layout_grid;
    QLabel *IP_label;
    QLineEdit *IP_text_input;
    QLabel *puerto_label;
    QLineEdit *puerto_text_input;
    QLabel *nombre_label;
    QLineEdit *nombre_text_input;
    QWidget *page_crear_unirse;
    QPushButton *button_crear_partida;
    QPushButton *button_unirse_partida;
    QWidget *page_crear;
    QPushButton *button_cofirmar_cant_nombre;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_2;
    QLabel *nombre_partida_label;
    QLineEdit *nombre_partida_input;
    QLabel *cantidad_jugadores_label;
    QLineEdit *cantidad_jugadores_input;
    QWidget *page_lista_patidas;
    QListWidget *lista_partidas;
    QWidget *page_casas;
    QLabel *bienvenida_label;
    QLabel *label_3;
    QPushButton *button_volver;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout;
    QLabel *atreides_pic_label;
    QLabel *ordos_pic_label;
    QLabel *harkonnen_pic_label;
    QPushButton *button_atreides;
    QSpacerItem *horizontalSpacer;
    QPushButton *button_harkonnen;
    QPushButton *button_ordos;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, 10, 781, 551));
        page_inicio = new QWidget();
        page_inicio->setObjectName(QString::fromUtf8("page_inicio"));
        titulo_label = new QLabel(page_inicio);
        titulo_label->setObjectName(QString::fromUtf8("titulo_label"));
        titulo_label->setGeometry(QRect(170, 30, 221, 61));
        QFont font;
        font.setPointSize(20);
        titulo_label->setFont(font);
        titulo_label->setAlignment(Qt::AlignCenter);
        button_confirmar = new QPushButton(page_inicio);
        button_confirmar->setObjectName(QString::fromUtf8("button_confirmar"));
        button_confirmar->setGeometry(QRect(488, 414, 121, 41));
        layoutWidget = new QWidget(page_inicio);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(130, 140, 351, 171));
        layout_grid = new QGridLayout(layoutWidget);
        layout_grid->setObjectName(QString::fromUtf8("layout_grid"));
        layout_grid->setContentsMargins(0, 0, 0, 0);
        IP_label = new QLabel(layoutWidget);
        IP_label->setObjectName(QString::fromUtf8("IP_label"));
        IP_label->setAlignment(Qt::AlignCenter);

        layout_grid->addWidget(IP_label, 0, 0, 1, 1);

        IP_text_input = new QLineEdit(layoutWidget);
        IP_text_input->setObjectName(QString::fromUtf8("IP_text_input"));

        layout_grid->addWidget(IP_text_input, 0, 1, 1, 1);

        puerto_label = new QLabel(layoutWidget);
        puerto_label->setObjectName(QString::fromUtf8("puerto_label"));
        puerto_label->setAlignment(Qt::AlignCenter);

        layout_grid->addWidget(puerto_label, 1, 0, 1, 1);

        puerto_text_input = new QLineEdit(layoutWidget);
        puerto_text_input->setObjectName(QString::fromUtf8("puerto_text_input"));

        layout_grid->addWidget(puerto_text_input, 1, 1, 1, 1);

        nombre_label = new QLabel(layoutWidget);
        nombre_label->setObjectName(QString::fromUtf8("nombre_label"));
        nombre_label->setAlignment(Qt::AlignCenter);

        layout_grid->addWidget(nombre_label, 2, 0, 1, 1);

        nombre_text_input = new QLineEdit(layoutWidget);
        nombre_text_input->setObjectName(QString::fromUtf8("nombre_text_input"));

        layout_grid->addWidget(nombre_text_input, 2, 1, 1, 1);

        stackedWidget->addWidget(page_inicio);
        page_crear_unirse = new QWidget();
        page_crear_unirse->setObjectName(QString::fromUtf8("page_crear_unirse"));
        button_crear_partida = new QPushButton(page_crear_unirse);
        button_crear_partida->setObjectName(QString::fromUtf8("button_crear_partida"));
        button_crear_partida->setGeometry(QRect(270, 100, 181, 71));
        button_unirse_partida = new QPushButton(page_crear_unirse);
        button_unirse_partida->setObjectName(QString::fromUtf8("button_unirse_partida"));
        button_unirse_partida->setGeometry(QRect(270, 220, 181, 71));
        stackedWidget->addWidget(page_crear_unirse);
        page_crear = new QWidget();
        page_crear->setObjectName(QString::fromUtf8("page_crear"));
        button_cofirmar_cant_nombre = new QPushButton(page_crear);
        button_cofirmar_cant_nombre->setObjectName(QString::fromUtf8("button_cofirmar_cant_nombre"));
        button_cofirmar_cant_nombre->setGeometry(QRect(538, 300, 121, 71));
        layoutWidget1 = new QWidget(page_crear);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(200, 60, 471, 111));
        gridLayout_2 = new QGridLayout(layoutWidget1);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        nombre_partida_label = new QLabel(layoutWidget1);
        nombre_partida_label->setObjectName(QString::fromUtf8("nombre_partida_label"));
        nombre_partida_label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(nombre_partida_label, 0, 0, 1, 1);

        nombre_partida_input = new QLineEdit(layoutWidget1);
        nombre_partida_input->setObjectName(QString::fromUtf8("nombre_partida_input"));

        gridLayout_2->addWidget(nombre_partida_input, 0, 1, 1, 1);

        cantidad_jugadores_label = new QLabel(layoutWidget1);
        cantidad_jugadores_label->setObjectName(QString::fromUtf8("cantidad_jugadores_label"));
        cantidad_jugadores_label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(cantidad_jugadores_label, 1, 0, 1, 1);

        cantidad_jugadores_input = new QLineEdit(layoutWidget1);
        cantidad_jugadores_input->setObjectName(QString::fromUtf8("cantidad_jugadores_input"));

        gridLayout_2->addWidget(cantidad_jugadores_input, 1, 1, 1, 1);

        stackedWidget->addWidget(page_crear);
        page_lista_patidas = new QWidget();
        page_lista_patidas->setObjectName(QString::fromUtf8("page_lista_patidas"));
        lista_partidas = new QListWidget(page_lista_patidas);
        lista_partidas->setObjectName(QString::fromUtf8("lista_partidas"));
        lista_partidas->setGeometry(QRect(260, 60, 291, 221));
        stackedWidget->addWidget(page_lista_patidas);
        page_casas = new QWidget();
        page_casas->setObjectName(QString::fromUtf8("page_casas"));
        bienvenida_label = new QLabel(page_casas);
        bienvenida_label->setObjectName(QString::fromUtf8("bienvenida_label"));
        bienvenida_label->setGeometry(QRect(270, 30, 211, 17));
        bienvenida_label->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(page_casas);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(260, 110, 211, 17));
        label_3->setAlignment(Qt::AlignCenter);
        button_volver = new QPushButton(page_casas);
        button_volver->setObjectName(QString::fromUtf8("button_volver"));
        button_volver->setGeometry(QRect(38, 414, 101, 51));
        layoutWidget2 = new QWidget(page_casas);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(130, 190, 461, 161));
        gridLayout = new QGridLayout(layoutWidget2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        atreides_pic_label = new QLabel(layoutWidget2);
        atreides_pic_label->setObjectName(QString::fromUtf8("atreides_pic_label"));
        atreides_pic_label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(atreides_pic_label, 0, 0, 1, 1);

        ordos_pic_label = new QLabel(layoutWidget2);
        ordos_pic_label->setObjectName(QString::fromUtf8("ordos_pic_label"));
        ordos_pic_label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(ordos_pic_label, 0, 4, 1, 1);

        harkonnen_pic_label = new QLabel(layoutWidget2);
        harkonnen_pic_label->setObjectName(QString::fromUtf8("harkonnen_pic_label"));
        harkonnen_pic_label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(harkonnen_pic_label, 0, 2, 1, 1);

        button_atreides = new QPushButton(layoutWidget2);
        button_atreides->setObjectName(QString::fromUtf8("button_atreides"));

        gridLayout->addWidget(button_atreides, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 1, 1, 1);

        button_harkonnen = new QPushButton(layoutWidget2);
        button_harkonnen->setObjectName(QString::fromUtf8("button_harkonnen"));

        gridLayout->addWidget(button_harkonnen, 1, 2, 1, 1);

        button_ordos = new QPushButton(layoutWidget2);
        button_ordos->setObjectName(QString::fromUtf8("button_ordos"));

        gridLayout->addWidget(button_ordos, 1, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 3, 1, 1);

        stackedWidget->addWidget(page_casas);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        titulo_label->setText(QCoreApplication::translate("MainWindow", "DUNE", nullptr));
        button_confirmar->setText(QCoreApplication::translate("MainWindow", "Confirmar", nullptr));
        IP_label->setText(QCoreApplication::translate("MainWindow", "IP", nullptr));
        puerto_label->setText(QCoreApplication::translate("MainWindow", "Puerto a conectar", nullptr));
        nombre_label->setText(QCoreApplication::translate("MainWindow", "Nombre", nullptr));
        button_crear_partida->setText(QCoreApplication::translate("MainWindow", "Crear Partida", nullptr));
        button_unirse_partida->setText(QCoreApplication::translate("MainWindow", "Unirse a Partida", nullptr));
        button_cofirmar_cant_nombre->setText(QCoreApplication::translate("MainWindow", "Confirmar", nullptr));
        nombre_partida_label->setText(QCoreApplication::translate("MainWindow", "Ingresar nombre de la partida", nullptr));
        cantidad_jugadores_label->setText(QCoreApplication::translate("MainWindow", "Ingresar cantidad de jugadores", nullptr));
        bienvenida_label->setText(QCoreApplication::translate("MainWindow", "BIenvenido a Dune nombre", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Select your house", nullptr));
        button_volver->setText(QCoreApplication::translate("MainWindow", "Volver", nullptr));
        atreides_pic_label->setText(QCoreApplication::translate("MainWindow", "Pic_Atreides", nullptr));
        ordos_pic_label->setText(QCoreApplication::translate("MainWindow", "Pic_Ordos", nullptr));
        harkonnen_pic_label->setText(QCoreApplication::translate("MainWindow", "Pic_Harkonnen", nullptr));
        button_atreides->setText(QCoreApplication::translate("MainWindow", "Atreides", nullptr));
        button_harkonnen->setText(QCoreApplication::translate("MainWindow", "Harkonnen", nullptr));
        button_ordos->setText(QCoreApplication::translate("MainWindow", "Ordos", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
