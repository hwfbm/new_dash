/********************************************************************************
** Form generated from reading UI file 'imu.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMU_H
#define UI_IMU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Imu
{
public:

    void setupUi(QWidget *Imu)
    {
        if (Imu->objectName().isEmpty())
            Imu->setObjectName("Imu");
        Imu->resize(400, 300);

        retranslateUi(Imu);

        QMetaObject::connectSlotsByName(Imu);
    } // setupUi

    void retranslateUi(QWidget *Imu)
    {
        Imu->setWindowTitle(QCoreApplication::translate("Imu", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Imu: public Ui_Imu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMU_H
