/********************************************************************************
** Form generated from reading UI file 'dialog_asignar_especia.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_ASIGNAR_ESPECIA_H
#define UI_DIALOG_ASIGNAR_ESPECIA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Dialog_asignar_especia
{
public:
    QDialogButtonBox *buttonbox_cant_especia;
    QLabel *label_cant_especia;
    QSpinBox *spinbox_cant_especia;

    void setupUi(QDialog *Dialog_asignar_especia)
    {
        if (Dialog_asignar_especia->objectName().isEmpty())
            Dialog_asignar_especia->setObjectName(QString::fromUtf8("Dialog_asignar_especia"));
        Dialog_asignar_especia->resize(400, 300);
        buttonbox_cant_especia = new QDialogButtonBox(Dialog_asignar_especia);
        buttonbox_cant_especia->setObjectName(QString::fromUtf8("buttonbox_cant_especia"));
        buttonbox_cant_especia->setGeometry(QRect(30, 240, 341, 32));
        buttonbox_cant_especia->setOrientation(Qt::Horizontal);
        buttonbox_cant_especia->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label_cant_especia = new QLabel(Dialog_asignar_especia);
        label_cant_especia->setObjectName(QString::fromUtf8("label_cant_especia"));
        label_cant_especia->setGeometry(QRect(40, 40, 141, 20));
        spinbox_cant_especia = new QSpinBox(Dialog_asignar_especia);
        spinbox_cant_especia->setObjectName(QString::fromUtf8("spinbox_cant_especia"));
        spinbox_cant_especia->setGeometry(QRect(200, 40, 141, 26));

        retranslateUi(Dialog_asignar_especia);
        QObject::connect(buttonbox_cant_especia, SIGNAL(accepted()), Dialog_asignar_especia, SLOT(accept()));
        QObject::connect(buttonbox_cant_especia, SIGNAL(rejected()), Dialog_asignar_especia, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog_asignar_especia);
    } // setupUi

    void retranslateUi(QDialog *Dialog_asignar_especia)
    {
        Dialog_asignar_especia->setWindowTitle(QCoreApplication::translate("Dialog_asignar_especia", "Dialog", nullptr));
        label_cant_especia->setText(QCoreApplication::translate("Dialog_asignar_especia", "Cantidad de Especia", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_asignar_especia: public Ui_Dialog_asignar_especia {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_ASIGNAR_ESPECIA_H
