/********************************************************************************
** Form generated from reading UI file 'dialog_asignar_jugadoro.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_ASIGNAR_JUGADORO_H
#define UI_DIALOG_ASIGNAR_JUGADORO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Dialog_asignar_jugadoro
{
public:
    QDialogButtonBox *buttonbox_asignar_jugador;
    QLabel *label_asignar_jugador;
    QSpinBox *spinbox_asignar_jugador;

    void setupUi(QDialog *Dialog_asignar_jugadoro)
    {
        if (Dialog_asignar_jugadoro->objectName().isEmpty())
            Dialog_asignar_jugadoro->setObjectName(QString::fromUtf8("Dialog_asignar_jugadoro"));
        Dialog_asignar_jugadoro->resize(400, 300);
        buttonbox_asignar_jugador = new QDialogButtonBox(Dialog_asignar_jugadoro);
        buttonbox_asignar_jugador->setObjectName(QString::fromUtf8("buttonbox_asignar_jugador"));
        buttonbox_asignar_jugador->setGeometry(QRect(30, 240, 341, 32));
        buttonbox_asignar_jugador->setOrientation(Qt::Horizontal);
        buttonbox_asignar_jugador->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label_asignar_jugador = new QLabel(Dialog_asignar_jugadoro);
        label_asignar_jugador->setObjectName(QString::fromUtf8("label_asignar_jugador"));
        label_asignar_jugador->setGeometry(QRect(60, 60, 111, 20));
        spinbox_asignar_jugador = new QSpinBox(Dialog_asignar_jugadoro);
        spinbox_asignar_jugador->setObjectName(QString::fromUtf8("spinbox_asignar_jugador"));
        spinbox_asignar_jugador->setGeometry(QRect(210, 60, 131, 26));

        retranslateUi(Dialog_asignar_jugadoro);
        QObject::connect(buttonbox_asignar_jugador, SIGNAL(accepted()), Dialog_asignar_jugadoro, SLOT(accept()));
        QObject::connect(buttonbox_asignar_jugador, SIGNAL(rejected()), Dialog_asignar_jugadoro, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog_asignar_jugadoro);
    } // setupUi

    void retranslateUi(QDialog *Dialog_asignar_jugadoro)
    {
        Dialog_asignar_jugadoro->setWindowTitle(QCoreApplication::translate("Dialog_asignar_jugadoro", "Dialog", nullptr));
        label_asignar_jugador->setText(QCoreApplication::translate("Dialog_asignar_jugadoro", "ID Jugador", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_asignar_jugadoro: public Ui_Dialog_asignar_jugadoro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_ASIGNAR_JUGADORO_H
