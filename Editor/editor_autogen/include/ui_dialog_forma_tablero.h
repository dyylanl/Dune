/********************************************************************************
** Form generated from reading UI file 'dialog_forma_tablero.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_FORMA_TABLERO_H
#define UI_DIALOG_FORMA_TABLERO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog_forma_tablero
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QSpinBox *spinbox_filas;
    QSpinBox *spinbox_columnas;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *Dialog_forma_tablero)
    {
        if (Dialog_forma_tablero->objectName().isEmpty())
            Dialog_forma_tablero->setObjectName(QString::fromUtf8("Dialog_forma_tablero"));
        Dialog_forma_tablero->resize(400, 300);
        buttonBox = new QDialogButtonBox(Dialog_forma_tablero);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(Dialog_forma_tablero);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(159, 42, 171, 60));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        spinbox_filas = new QSpinBox(layoutWidget);
        spinbox_filas->setObjectName(QString::fromUtf8("spinbox_filas"));
        spinbox_filas->setMaximum(1000);

        verticalLayout->addWidget(spinbox_filas);

        spinbox_columnas = new QSpinBox(layoutWidget);
        spinbox_columnas->setObjectName(QString::fromUtf8("spinbox_columnas"));
        spinbox_columnas->setMaximum(1000);

        verticalLayout->addWidget(spinbox_columnas);

        layoutWidget1 = new QWidget(Dialog_forma_tablero);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(61, 42, 69, 61));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);


        retranslateUi(Dialog_forma_tablero);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog_forma_tablero, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog_forma_tablero, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog_forma_tablero);
    } // setupUi

    void retranslateUi(QDialog *Dialog_forma_tablero)
    {
        Dialog_forma_tablero->setWindowTitle(QCoreApplication::translate("Dialog_forma_tablero", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Dialog_forma_tablero", "FIlas", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog_forma_tablero", "Columnas", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_forma_tablero: public Ui_Dialog_forma_tablero {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_FORMA_TABLERO_H
