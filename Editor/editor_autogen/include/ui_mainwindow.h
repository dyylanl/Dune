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
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave;
    QAction *actionLoadd;
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *button_tiles;
    QPushButton *button_construcciones;
    QPushButton *button_opciones;
    QGraphicsView *graphicsView;
    QVBoxLayout *verticalLayout;
    QPushButton *button_cambiar_forma;
    QPushButton *button_cant_jugadores;
    QStackedWidget *stackedWidget;
    QWidget *page_tiles;
    QHBoxLayout *horizontalLayout_4;
    QGridLayout *gridLayout;
    QPushButton *button_columna;
    QPushButton *button_agregar_fila;
    QPushButton *button_especia;
    QPushButton *button_dunas;
    QPushButton *button_arena;
    QPushButton *button_precipicio;
    QPushButton *button_cimas;
    QPushButton *button_roca;
    QPushButton *button_asignar_especia;
    QWidget *page_unidades;
    QWidget *page_construcciones;
    QGridLayout *gridLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *button_asignar_jugador;
    QPushButton *button_eliminar_construccion;
    QPushButton *button_centro_construccion;
    QSpacerItem *horizontalSpacer_4;
    QWidget *page_opciones;
    QGridLayout *gridLayout_5;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QLabel *musica_label;
    QPushButton *button_pausa;
    QPushButton *button_play;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(828, 618);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionLoadd = new QAction(MainWindow);
        actionLoadd->setObjectName(QString::fromUtf8("actionLoadd"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        button_tiles = new QPushButton(centralwidget);
        button_tiles->setObjectName(QString::fromUtf8("button_tiles"));

        horizontalLayout_3->addWidget(button_tiles);

        button_construcciones = new QPushButton(centralwidget);
        button_construcciones->setObjectName(QString::fromUtf8("button_construcciones"));

        horizontalLayout_3->addWidget(button_construcciones);

        button_opciones = new QPushButton(centralwidget);
        button_opciones->setObjectName(QString::fromUtf8("button_opciones"));

        horizontalLayout_3->addWidget(button_opciones);


        gridLayout_2->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout_2->addWidget(graphicsView, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        button_cambiar_forma = new QPushButton(centralwidget);
        button_cambiar_forma->setObjectName(QString::fromUtf8("button_cambiar_forma"));

        verticalLayout->addWidget(button_cambiar_forma);

        button_cant_jugadores = new QPushButton(centralwidget);
        button_cant_jugadores->setObjectName(QString::fromUtf8("button_cant_jugadores"));

        verticalLayout->addWidget(button_cant_jugadores);


        gridLayout_2->addLayout(verticalLayout, 0, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page_tiles = new QWidget();
        page_tiles->setObjectName(QString::fromUtf8("page_tiles"));
        horizontalLayout_4 = new QHBoxLayout(page_tiles);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        button_columna = new QPushButton(page_tiles);
        button_columna->setObjectName(QString::fromUtf8("button_columna"));

        gridLayout->addWidget(button_columna, 1, 3, 1, 1);

        button_agregar_fila = new QPushButton(page_tiles);
        button_agregar_fila->setObjectName(QString::fromUtf8("button_agregar_fila"));

        gridLayout->addWidget(button_agregar_fila, 0, 3, 1, 1);

        button_especia = new QPushButton(page_tiles);
        button_especia->setObjectName(QString::fromUtf8("button_especia"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/tile_especia.png"), QSize(), QIcon::Normal, QIcon::Off);
        button_especia->setIcon(icon);

        gridLayout->addWidget(button_especia, 1, 2, 1, 1);

        button_dunas = new QPushButton(page_tiles);
        button_dunas->setObjectName(QString::fromUtf8("button_dunas"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/tile_dunas.png"), QSize(), QIcon::Normal, QIcon::Off);
        button_dunas->setIcon(icon1);

        gridLayout->addWidget(button_dunas, 1, 0, 1, 1);

        button_arena = new QPushButton(page_tiles);
        button_arena->setObjectName(QString::fromUtf8("button_arena"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/tile_arena.png"), QSize(), QIcon::Normal, QIcon::Off);
        button_arena->setIcon(icon2);
        button_arena->setIconSize(QSize(16, 16));

        gridLayout->addWidget(button_arena, 0, 0, 1, 1);

        button_precipicio = new QPushButton(page_tiles);
        button_precipicio->setObjectName(QString::fromUtf8("button_precipicio"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resources/tile_precipicio.png"), QSize(), QIcon::Normal, QIcon::Off);
        button_precipicio->setIcon(icon3);

        gridLayout->addWidget(button_precipicio, 1, 1, 1, 1);

        button_cimas = new QPushButton(page_tiles);
        button_cimas->setObjectName(QString::fromUtf8("button_cimas"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/resources/tile_cimas.png"), QSize(), QIcon::Normal, QIcon::Off);
        button_cimas->setIcon(icon4);

        gridLayout->addWidget(button_cimas, 0, 2, 1, 1);

        button_roca = new QPushButton(page_tiles);
        button_roca->setObjectName(QString::fromUtf8("button_roca"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/resources/tile_roca.png"), QSize(), QIcon::Normal, QIcon::Off);
        button_roca->setIcon(icon5);

        gridLayout->addWidget(button_roca, 0, 1, 1, 1);

        button_asignar_especia = new QPushButton(page_tiles);
        button_asignar_especia->setObjectName(QString::fromUtf8("button_asignar_especia"));

        gridLayout->addWidget(button_asignar_especia, 2, 2, 1, 1);


        horizontalLayout_4->addLayout(gridLayout);

        stackedWidget->addWidget(page_tiles);
        page_unidades = new QWidget();
        page_unidades->setObjectName(QString::fromUtf8("page_unidades"));
        stackedWidget->addWidget(page_unidades);
        page_construcciones = new QWidget();
        page_construcciones->setObjectName(QString::fromUtf8("page_construcciones"));
        gridLayout_4 = new QGridLayout(page_construcciones);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_3, 1, 0, 1, 1);

        button_asignar_jugador = new QPushButton(page_construcciones);
        button_asignar_jugador->setObjectName(QString::fromUtf8("button_asignar_jugador"));

        gridLayout_4->addWidget(button_asignar_jugador, 1, 1, 1, 1);

        button_eliminar_construccion = new QPushButton(page_construcciones);
        button_eliminar_construccion->setObjectName(QString::fromUtf8("button_eliminar_construccion"));

        gridLayout_4->addWidget(button_eliminar_construccion, 2, 1, 1, 1);

        button_centro_construccion = new QPushButton(page_construcciones);
        button_centro_construccion->setObjectName(QString::fromUtf8("button_centro_construccion"));

        gridLayout_4->addWidget(button_centro_construccion, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_4, 1, 2, 1, 1);

        stackedWidget->addWidget(page_construcciones);
        page_opciones = new QWidget();
        page_opciones->setObjectName(QString::fromUtf8("page_opciones"));
        gridLayout_5 = new QGridLayout(page_opciones);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalSpacer = new QSpacerItem(160, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(160, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        musica_label = new QLabel(page_opciones);
        musica_label->setObjectName(QString::fromUtf8("musica_label"));
        musica_label->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(musica_label, 0, 1, 1, 1);

        button_pausa = new QPushButton(page_opciones);
        button_pausa->setObjectName(QString::fromUtf8("button_pausa"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/resources/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        button_pausa->setIcon(icon6);

        gridLayout_5->addWidget(button_pausa, 3, 1, 1, 1);

        button_play = new QPushButton(page_opciones);
        button_play->setObjectName(QString::fromUtf8("button_play"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/resources/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        button_play->setIcon(icon7);

        gridLayout_5->addWidget(button_play, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_5->addItem(verticalSpacer, 2, 1, 1, 1);

        stackedWidget->addWidget(page_opciones);

        gridLayout_3->addWidget(stackedWidget, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 828, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionSave);
        menuFile->addAction(actionLoadd);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionLoadd->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
        button_tiles->setText(QCoreApplication::translate("MainWindow", "TIles", nullptr));
        button_construcciones->setText(QCoreApplication::translate("MainWindow", "Construcciones", nullptr));
        button_opciones->setText(QCoreApplication::translate("MainWindow", "Opciones", nullptr));
        button_cambiar_forma->setText(QCoreApplication::translate("MainWindow", "Cambiar filas y columnas", nullptr));
        button_cant_jugadores->setText(QCoreApplication::translate("MainWindow", "Cantidad de Jugadores", nullptr));
        button_columna->setText(QCoreApplication::translate("MainWindow", "Agregar Columna", nullptr));
        button_agregar_fila->setText(QCoreApplication::translate("MainWindow", "Agregar Fila", nullptr));
        button_especia->setText(QCoreApplication::translate("MainWindow", "Especia", nullptr));
        button_dunas->setText(QCoreApplication::translate("MainWindow", "Dunas", nullptr));
        button_arena->setText(QCoreApplication::translate("MainWindow", "Arena", nullptr));
        button_precipicio->setText(QCoreApplication::translate("MainWindow", "Precipicio", nullptr));
        button_cimas->setText(QCoreApplication::translate("MainWindow", "Cimas", nullptr));
        button_roca->setText(QCoreApplication::translate("MainWindow", "Roca", nullptr));
        button_asignar_especia->setText(QCoreApplication::translate("MainWindow", "Asignar Especia", nullptr));
        button_asignar_jugador->setText(QCoreApplication::translate("MainWindow", "Asignar jugador", nullptr));
        button_eliminar_construccion->setText(QCoreApplication::translate("MainWindow", "Eliminar Construcci\303\263n", nullptr));
        button_centro_construccion->setText(QCoreApplication::translate("MainWindow", "Centro de Construcci\303\263n", nullptr));
        musica_label->setText(QCoreApplication::translate("MainWindow", "M\303\272sica", nullptr));
        button_pausa->setText(QCoreApplication::translate("MainWindow", "Pausar", nullptr));
        button_play->setText(QCoreApplication::translate("MainWindow", "Play", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
