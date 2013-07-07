/********************************************************************************
** Form generated from reading UI file 'sudoku.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUDOKU_H
#define UI_SUDOKU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Sudoku
{
public:
    QWidget *centralWidget;
    QPushButton *nullButton;
    QWidget *gridLayoutWidget_2;
    QGridLayout *numberPad;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QRadioButton *radioButton;
    QPushButton *printButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Sudoku)
    {
        if (Sudoku->objectName().isEmpty())
            Sudoku->setObjectName(QStringLiteral("Sudoku"));
        Sudoku->resize(1094, 725);
        centralWidget = new QWidget(Sudoku);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        nullButton = new QPushButton(centralWidget);
        nullButton->setObjectName(QStringLiteral("nullButton"));
        nullButton->setGeometry(QRect(800, 300, 114, 32));
        gridLayoutWidget_2 = new QWidget(centralWidget);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(780, 120, 160, 151));
        numberPad = new QGridLayout(gridLayoutWidget_2);
        numberPad->setSpacing(6);
        numberPad->setContentsMargins(11, 11, 11, 11);
        numberPad->setObjectName(QStringLiteral("numberPad"));
        numberPad->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(180, 50, 571, 521));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        radioButton = new QRadioButton(centralWidget);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setEnabled(false);
        radioButton->setGeometry(QRect(820, 360, 21, 20));
        printButton = new QPushButton(centralWidget);
        printButton->setObjectName(QStringLiteral("printButton"));
        printButton->setGeometry(QRect(800, 440, 114, 32));
        Sudoku->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Sudoku);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1094, 22));
        Sudoku->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Sudoku);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Sudoku->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Sudoku);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Sudoku->setStatusBar(statusBar);

        retranslateUi(Sudoku);

        QMetaObject::connectSlotsByName(Sudoku);
    } // setupUi

    void retranslateUi(QMainWindow *Sudoku)
    {
        Sudoku->setWindowTitle(QApplication::translate("Sudoku", "Sudoku", 0));
        nullButton->setText(QApplication::translate("Sudoku", "PushButton", 0));
        radioButton->setText(QString());
        printButton->setText(QApplication::translate("Sudoku", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class Sudoku: public Ui_Sudoku {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUDOKU_H
