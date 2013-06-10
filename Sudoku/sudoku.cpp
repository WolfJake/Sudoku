#include "sudoku.h"
#include "ui_sudoku.h"
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QPlainTextEdit>
#include <QDebug>

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
            cell[i][j] = new QPushButton();
            connect(cell[i][j], &QPushButton::clicked, this, &Sudoku::cell_clicked);
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
}



void Sudoku::on_actionQuit_triggered()
{
   qApp->quit();
}



void Sudoku::on_rowBox_valueChanged(int arg1)
{
    int centerX = (arg1 - 1) / 3;
    int centerY = (ui->columnBox->value() - 1) / 3;

    for (int i = 0; i < 9; i++)
    {
        number[i]->setEnabled(1);
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {

            if  (i == arg1 - 1 || j == ui->columnBox->value() - 1 || (i / 3 == centerX && j / 3 == centerY))
            {
                if (cell[i][j]->text() != "")
                {
                    qDebug() << cell[i][j]->text();
                    int value = cell[i][j]->text().toInt();

                    number[value - 1]->setEnabled(0);
                }
            }

        }

    }
    if (cell[arg1 - 1][ui->columnBox->value() - 1]->text() == "")
    {
        ui->nullButton->setEnabled(0);
    }
    else
    {
        ui->nullButton->setEnabled(1);
    }
}

void Sudoku::on_columnBox_valueChanged(int arg1)
{
    int centerX = (ui->rowBox->value() - 1) / 3;
    int centerY = (arg1 - 1) / 3;

    for (int i = 0; i < 9; i++)
    {
        number[i]->setEnabled(1);
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {

            if  (i == ui->rowBox->value() - 1 || j == arg1 - 1 || (i / 3 == centerX && j / 3 == centerY))
            {
                if (cell[i][j]->text() != "")
                {
                    qDebug() << cell[i][j]->text();
                    int value = cell[i][j]->text().toInt();

                    number[value - 1]->setEnabled(0);
                }
            }

        }
    }
    if (cell[ui->rowBox->value() - 1][arg1 - 1]->text() == "")
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
    QPushButton *numberButton = (QPushButton *)sender();
    cell[ui->rowBox->value() - 1][ui->columnBox->value() - 1]->setText(numberButton->text());
    number[numberButton->text().toInt() - 1]->setEnabled(0);
    ui->nullButton->setEnabled(1);
}

void Sudoku::cell_clicked()
{

}

void Sudoku::on_nullButton_clicked()
{
    int value = cell[ui->rowBox->value() - 1][ui->columnBox->value() - 1]->text().toInt();
    number[value - 1]->setEnabled(1);
    cell[ui->rowBox->value() - 1][ui->columnBox->value() - 1]->setText("");
    ui->nullButton->setEnabled(0);
}
