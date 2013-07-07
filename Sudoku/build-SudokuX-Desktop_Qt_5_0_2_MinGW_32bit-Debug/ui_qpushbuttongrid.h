/********************************************************************************
** Form generated from reading UI file 'qpushbuttongrid.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QPUSHBUTTONGRID_H
#define UI_QPUSHBUTTONGRID_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QPushButtonGrid
{
public:

    void setupUi(QWidget *QPushButtonGrid)
    {
        if (QPushButtonGrid->objectName().isEmpty())
            QPushButtonGrid->setObjectName(QStringLiteral("QPushButtonGrid"));
        QPushButtonGrid->resize(400, 300);

        retranslateUi(QPushButtonGrid);

        QMetaObject::connectSlotsByName(QPushButtonGrid);
    } // setupUi

    void retranslateUi(QWidget *QPushButtonGrid)
    {
        QPushButtonGrid->setWindowTitle(QApplication::translate("QPushButtonGrid", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class QPushButtonGrid: public Ui_QPushButtonGrid {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QPUSHBUTTONGRID_H
