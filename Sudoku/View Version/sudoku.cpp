#include "sudoku.h"
#include "ui_sudoku.h"
#include <QApplication>
#include <QPushButton>
#include <qpushbuttongrid.h>
#include <QGridLayout>
#include <QPlainTextEdit>
#include <QDebug>
#include <QTime>
#include <QtGlobal>

Sudoku::Sudoku(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sudoku)
{
    ui->setupUi(this);
    initGui();
}

Sudoku::~Sudoku()
{
    delete ui;
    for (int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            delete cell[i][j];

        }
    }
    for (int i = 0; i < 9; i++)
    {
        delete number[i];

    }
    delete grid;
}

void Sudoku::initGui()
{
    grid = new QGridLayout(this);

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            //cell[i][j] = new QPushButton(QString("(%1, %2)").arg(i + 1).arg(j + 1));
            cell[i][j] = new QPushButtonGrid();
            cell[i][j]->row = i;
            cell[i][j]->column = j;
            //cell[i][j]->setStyleSheet("QPushButtonGrid { background-color: white; }");
            connect(cell[i][j], &QPushButtonGrid::clicked, this, &Sudoku::cell_clicked);
            ui->gridLayout->addWidget(cell[i][j], i, j);

        }
    }

    for (int i = 0; i < 9; i++)
    {
        number[i] = new QPushButton(QString("%1").arg(i + 1));
        connect(number[i], &QPushButton::clicked, this, &Sudoku::number_clicked);
        ui->numberPad->addWidget(number[i], i / 3, i % 3);

    }

    ui->nullButton->setText("Null");
    ui->nullButton->setEnabled(0);
    isCellSelected = false;


    /*for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            QTime time = QTime::currentTime();
            qrand((uint)time.msec());

            int randomValue = randomNumber(1 ,9);


            qDebug() << randomValue;

            for (int k = 0; k < 9; k++)
            {
                for (int l = 0; l < 9; l++)
                {

                    if  (k == i || l == j || (k / 3 == i / 3 && l / 3 == j / 3))
                    {
                        if (cell[i][j]->text() != "")
                        {
                            int value = cell[i][j]->text().toInt();
                            number[value - 1]->setEnabled(0);
                        }
                    }

                }

            }

        }
    }*/
}


int Sudoku::randomNumber(int low, int high)
{
    return qrand() % ((high + 1) - low) + low;
}


void Sudoku::on_actionQuit_triggered()
{
   qApp->quit();
}


void Sudoku::validateCell()
{
    int centerX = coorX / 3;
    int centerY = coorY / 3;

    for (int i = 0; i < 9; i++)
    {
        number[i]->setEnabled(1);
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {

            if  (i == coorX || j == coorY || (i / 3 == centerX && j / 3 == centerY))
            {
                if (cell[i][j]->text() != "")
                {
                    int value = cell[i][j]->text().toInt();
                    number[value - 1]->setEnabled(0);
                }
            }

        }

    }
    if (cell[coorX][coorY]->text() == "")
    {
        ui->nullButton->setEnabled(0);
    }
    else
    {
        ui->nullButton->setEnabled(1);
    }
}


void Sudoku::number_clicked()
{
    if (isCellSelected) {
        number[cell[coorX][coorY]->text().toInt() - 1]->setEnabled(1);
        QPushButton *numberButton = (QPushButton *)sender();
        cell[coorX][coorY]->setText(numberButton->text());
        number[numberButton->text().toInt() - 1]->setEnabled(0);
        ui->nullButton->setEnabled(1);
    }

}

void Sudoku::cell_clicked()
{
    if (!isCellSelected)
    {
        isCellSelected = true;
    }
    QPushButtonGrid *cell = (QPushButtonGrid *)sender();
    coorX = cell->row;
    coorY = cell->column;
    validateCell();
    //cell->setStyleSheet("QPushButtonGrid { background-color: blue; }");
}

void Sudoku::on_nullButton_clicked()
{
    if (isCellSelected)
    {
        int value = cell[coorX][coorY]->text().toInt();
        number[value - 1]->setEnabled(1);
        cell[coorX][coorY]->setText("");
        ui->nullButton->setEnabled(0);
    }
}
