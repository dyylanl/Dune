/********************************************************************************
** Form generated from reading UI file 'dialog_cant_jugadores.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_CANT_JUGADORES_H
#define UI_DIALOG_CANT_JUGADORES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Dialog_cant_jugadores
{
public:
    QDialogButtonBox *buttonBox_cant_jugadores;
    QLabel *cant_jugadores_label;
    QSpinBox *cant_jugadores_spinbox;

    void setupUi(QDialog *Dialog_cant_jugadores)
    {
        if (Dialog_cant_jugadores->objectName().isEmpty())
            Dialog_cant_jugadores->setObjectName(QString::fromUtf8("Dialog_cant_jugadores"));
        Dialog_cant_jugadores->resize(400, 300);
        buttonBox_cant_jugadores = new QDialogButtonBox(Dialog_cant_jugadores);
        buttonBox_cant_jugadores->setObjectName(QString::fromUtf8("buttonBox_cant_jugadores"));
        buttonBox_cant_jugadores->setGeometry(QRect(30, 240, 341, 32));
        buttonBox_cant_jugadores->setOrientation(Qt::Horizontal);
        buttonBox_cant_jugadores->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        cant_jugadores_label = new QLabel(Dialog_cant_jugadores);
        cant_jugadores_label->setObjectName(QString::fromUtf8("cant_jugadores_label"));
        cant_jugadores_label->setGeometry(QRect(20, 60, 171, 20));
        cant_jugadores_label->setAlignment(Qt::AlignCenter);
        cant_jugadores_spinbox = new QSpinBox(Dialog_cant_jugadores);
        cant_jugadores_spinbox->setObjectName(QString::fromUtf8("cant_jugadores_spinbox"));
        cant_jugadores_spinbox->setGeometry(QRect(220, 60, 141, 26));

        retranslateUi(Dialog_cant_jugadores);
        QObject::connect(buttonBox_cant_jugadores, SIGNAL(accepted()), Dialog_cant_jugadores, SLOT(accept()));
        QObject::connect(buttonBox_cant_jugadores, SIGNAL(rejected()), Dialog_cant_jugadores, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog_cant_jugadores);
    } // setupUi

    void retranslateUi(QDialog *Dialog_cant_jugadores)
    {
        Dialog_cant_jugadores->setWindowTitle(QCoreApplication::translate("Dialog_cant_jugadores", "Dialog", nullptr));
        cant_jugadores_label->setText(QCoreApplication::translate("Dialog_cant_jugadores", "Cantidad de Jugadores", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_cant_jugadores: public Ui_Dialog_cant_jugadores {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_CANT_JUGADORES_H
