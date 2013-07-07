#include "sudoku.h"
#include "ui_sudoku.h"
#include <QApplication>
#include <QPushButton>
#include <qpushbuttongrid.h>
#include <QGridLayout>
#include <QDebug>
#include <QTime>
#include <QtGlobal>
#include <math.h>

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
}

void Sudoku::initGui()
{
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
    QString code[9];
    QString key[9];
    QString hint[9];
    int binaryBuffer = 0;
    int binaryBuffer2 = 0;
    int testing[9][9];

    crypt = "";
    int delta = 0;
    int decimal = 0;
    int digit = 0;
    QString sign;
    QString synt;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            crypt = crypt.append(QString("%1").arg(cell[i][j]->realNumber));

            if(!j)
            {
                delta = cell[i][j]->realNumber;
                code[i] = code[i].append(QString("%1").arg((char)(delta + 96)));

            }
            else
            {
                delta = cell[i][j]->realNumber - cell[i][j - 1]->realNumber;
                code[i] = code[i].append(QString("%1").arg((char)(abs(delta) + 96)));


            }
            if(delta > 0)
            {
                //qDebug() << pow(2, 8 - j);
                binaryBuffer += pow(2, 8 - j);

            }




            if(cell[i][j]->assignedNumber)
            {
                binaryBuffer2 += pow(2, 8 - j);
            }

        }
        key[i].setNum(binaryBuffer, 16);
        hint[i].setNum(binaryBuffer2, 16);

        qDebug() << code[i];
        qDebug() << key[i];
        qDebug() << hint[i];

        delta = 0;
        binaryBuffer = 0;
        binaryBuffer2 = 0;
        crypt = crypt.append("\n");
    }
    qDebug() << crypt;
    crypt = "";

    for (int i = 0; i < 9; i++)
    {

        QString binary;

        for (int k = 0; k < 3; k++)
        {


            if(key[i].mid(k, 1) == "a")
            {
                digit = 10;
            }
            else if(key[i].mid(k, 1) == "b")
            {
                digit = 11;
            }
            else if(key[i].mid(k, 1) == "c")
            {
                digit = 12;
            }
            else if(key[i].mid(k, 1) == "d")
            {
                digit = 13;
            }
            else if(key[i].mid(k, 1) == "e")
            {
                digit = 14;
            }
            else if(key[i].mid(k, 1) == "f")
            {
                digit = 15;
            }
            else {
                digit = key[i].mid(k, 1).toInt();
            }
            decimal += digit * pow(16, 2 - k);
        }



        binary.setNum(decimal, 2);

        for (int j = 0; j < 9; j++)
        {


            sign = binary.mid(j, 1);

            if(code[i].mid(j, 1) == "a")
            {
                synt = "1";
            }
            else if(code[i].mid(j, 1) == "b")
            {
                synt = "2";
            }
            else if(code[i].mid(j, 1) == "c")
            {
                synt = "3";
            }
            else if(code[i].mid(j, 1) == "d")
            {
                synt = "4";
            }
            else if(code[i].mid(j, 1) == "e")
            {
                synt = "5";
            }
            else if(code[i].mid(j, 1) == "f")
            {
                synt = "6";
            }
            else if(code[i].mid(j, 1) == "g")
            {
                synt = "7";
            }
            else if(code[i].mid(j, 1) == "h")
            {
                synt = "8";
            }
            else if(code[i].mid(j, 1) == "i")
            {
                synt = "9";
            }

            int deltaInverse = pow(-1, sign.toInt() + 1) * synt.toInt();

            if(!j)
            {
                testing[i][j] = deltaInverse;
            }
            else
            {
                testing[i][j] = testing[i][j - 1] + deltaInverse;
            }

            crypt = crypt.append(QString("%1").arg(testing[i][j]));
        }
        crypt = crypt.append("\n");
        decimal = 0;
    }
    qDebug() << crypt;
}
