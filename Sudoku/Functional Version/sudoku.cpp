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
    bool paintFlag = false;
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
            if(paintFlag)
            {
                cell[i][j]->color = 0;
                cell[i][j]->setStyleSheet("QPushButtonGrid { background-color: white; }");
            }
            else
            {
                cell[i][j]->color = 1;
                cell[i][j]->setStyleSheet("QPushButtonGrid { background-color: red; }");
            }

            connect(cell[i][j], &QPushButtonGrid::clicked, this, &Sudoku::cell_clicked);
            ui->gridLayout->addWidget(cell[i][j], i, j);
            if (j % 3 == 2)
            {
                paintFlag = !paintFlag;
            }
        }
        if(i % 3 != 2)
        {
            paintFlag = !paintFlag;
        }
    }

    for (int i = 0; i < 9; i++)
    {
        number[i] = new QPushButton(QString("%1").arg(i + 1));
        connect(number[i], &QPushButton::clicked, this, &Sudoku::number_clicked);
        ui->numberPad->addWidget(number[i], i / 3, i % 3);

    }

    ui->nullButton->setText("Erase");
    ui->nullButton->setEnabled(false);
    isCellSelected = false;
    while(!sudokuBlankChecker())
    {
        sudokuErrorWiper();
        sudokuGenerator(0);
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
                //cell[row][column]->setText(QString("%1").arg(value));
            }
            else
            {

                cell[row][column]->realNumber = cell[row][column - counter]->realNumber;
                //cell[row][column]->setText(QString("%1").arg(cell[row][column - counter]->realNumber));
                cell[row][column - counter]->realNumber = value;
                //cell[row][column - counter]->setText(QString("%1").arg(value));

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
                if (cell[i][j]->realNumber)
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


void Sudoku::number_clicked()
{
    if (isCellSelected) {
        QPushButton *numberButton = (QPushButton *)sender();
        number[cell[coorX][coorY]->assignedNumber - 1]->setEnabled(1);
        cell[coorX][coorY]->setText(numberButton->text());
        cell[coorX][coorY]->assignedNumber = numberButton->text().toInt();

        if (cell[coorX][coorY]->realNumber == cell[coorX][coorY]->assignedNumber)
        {
            ui->radioButton->setChecked(true);
        }
        else
        {
            ui->radioButton->setChecked(false);
        }
        number[cell[coorX][coorY]->assignedNumber - 1]->setEnabled(false);
        ui->nullButton->setEnabled(1);

    }

}


void Sudoku::cell_clicked()
{
    if (!isCellSelected)
    {
        isCellSelected = true;
    }
    else
    {
        if(cell[coorX][coorY]->color == 0)
        {
            cell[coorX][coorY]->setStyleSheet("QPushButtonGrid { background-color: white; }");
        }
        else
        {
            cell[coorX][coorY]->setStyleSheet("QPushButtonGrid { background-color: red; }");
        }
    }
    QPushButtonGrid *cell = (QPushButtonGrid *)sender();
    coorX = cell->row;
    coorY = cell->column;

    if (cell->realNumber == cell->assignedNumber)
    {
        ui->radioButton->setChecked(true);
    }
    else
    {
        ui->radioButton->setChecked(false);
    }

    validateCell();
    cell->setStyleSheet("QPushButtonGrid { background-color: blue; }");
}


void Sudoku::on_nullButton_clicked()
{
    if (isCellSelected)
    {
        int value = cell[coorX][coorY]->assignedNumber;
        number[value - 1]->setEnabled(true);
        cell[coorX][coorY]->setText("");
        cell[coorX][coorY]->assignedNumber = 0;
        ui->nullButton->setEnabled(false);
        ui->radioButton->setChecked(false);
    }
}


void Sudoku::validateCell()
{
    int centerX = coorX / 3;
    int centerY = coorY / 3;

    for (int i = 0; i < 9; i++)
    {
        number[i]->setEnabled(true);
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {

            if  (i == coorX || j == coorY || (i / 3 == centerX && j / 3 == centerY))
            {
                if (cell[i][j]->assignedNumber)
                {
                    int value = cell[i][j]->assignedNumber;
                    number[value - 1]->setEnabled(false);
                }
            }

        }

    }
    if (!cell[coorX][coorY]->assignedNumber)
    {
        ui->nullButton->setEnabled(false);
    }
    else
    {
        ui->nullButton->setEnabled(true);
    }
}

void Sudoku::on_printButton_clicked()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {

            qDebug() << cell[i][j]->realNumber;

        }
        qDebug() <<"\n";
    }
}
