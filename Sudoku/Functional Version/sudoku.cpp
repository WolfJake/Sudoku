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
    srand((unsigned)time(NULL));
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
            cell[i][j]->realNumber = 0;
            cell[i][j]->assignedNumber = 0;
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
    while(!sudokuBlankChecker())
    {
        sudokuErrorWiper();
        sudokuGenerator(0);
    }
}

void Sudoku::sudokuErrorWiper()
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            cell[i][j]->realNumber = 0;
            cell[i][j]->setText("");
        }
    }
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


bool Sudoku::validateCellAtPointWithNumber(int row, int column, int value, int counter)
{
    int centerX = row / 3;
    int centerY = column / 3;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {

            if  ((i == row || j == column || (i / 3 == centerX && j / 3 == centerY)))
            {
                if (cell[i][j]->text() != "")
                {
                    if (value == cell[i][j]->realNumber && !(i == row && j == column - counter))
                    {
                        return false;
                    }
                }
            }

        }

    }
    return true;
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

void Sudoku::sudokuGenerator(int row)
{
    if (row > 8)
    {
        return;
    }

    int range = 9;
    int digitArray[9];
    for (int i = 0; i < 9; i++)
    {
        digitArray[i] = i;
    }
    while (range > 0)
    {
        int random = rand() % range;
        range--;

        int temp = digitArray[range];
        digitArray[range] = digitArray[random];
        digitArray[random] = temp;

    }
    bool flag = false;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            flag = false;
            if (digitArray[j] >= 0)
            {
                qDebug() << "Index: (" << row << ", " << i << ")\nValue: " << (digitArray[j] + 1) << "\n";
                if (numberAssigner(0, row, i, digitArray[j] + 1))
                {
                    digitArray[j] = -1;
                    flag = true;
                }

            }
            if (flag)
            {
                break;
            }
        }
    }

    sudokuGenerator(row + 1);
}

bool Sudoku::sudokuBlankChecker()
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if (!cell[i][j]->realNumber)
            {
                return false;
            }
        }
    }
    return true;
}

bool Sudoku::numberAssigner(int counter, int row, int column, int value)
{
    if (counter > column)
    {
        return false;
    }
    else {
        if ((!counter && validateCellAtPointWithNumber(row, column, value, 0)) || (counter && validateCellAtPointWithNumber(row, column, cell[row][column - counter]->realNumber, counter) && validateCellAtPointWithNumber(row, column - counter, value, 0)))
        {
            if (!counter)
            {
                cell[row][column]->realNumber = value;
                cell[row][column]->setText(QString("%1").arg(value));
            }
            else
            {
                cell[row][column]->realNumber = cell[row][column - counter]->realNumber;
                cell[row][column]->setText(QString("%1").arg(cell[row][column - counter]->realNumber));
                cell[row][column - counter]->realNumber = value;
                cell[row][column - counter]->setText(QString("%1").arg(value));

            }
            return true;
        }
        else
        {
            counter++;
            return numberAssigner(counter, row, column, value);
        }
    }
}
