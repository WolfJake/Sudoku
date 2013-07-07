#include "sudoku.h"
#include "ui_sudoku.h"
#include "ui_start.h"
#include <QApplication>
#include <QPushButton>
#include <qpushbuttongrid.h>
#include <QGridLayout>
#include <QDebug>
#include <QTime>
#include <QtGlobal>
#include <math.h>
#include <QFile>
#include <QDialog>
#include <clock.h>

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
    delete clock;
}

void Sudoku::initGui()
{
    coorX = -1;
    coorY = -1;
    bool paintFlag = false;

    //ui->gridLayout->setStyleSheet("background-color: white;");

    this->setStyleSheet("background-color: white;");


    /*//QImage image(":/images/sketchBackground.jpg");

    setStyleSheet("background-image: url(/Users/Jake/Desktop/images/sketchBackground.jpg);");*/

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

                cell[i][j]->setStyleSheet("QPushButtonGrid { background-color: darkBlue; }");
            }
            else
            {
                cell[i][j]->color = 1;
                cell[i][j]->setStyleSheet("QPushButtonGrid { background-color: magenta; }");
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
        number[i]->setStyleSheet("QPushButton { background-color: darkCyan; }");
    }

    ui->nullButton->setText("Erase");
    ui->nullButton->setEnabled(false);
    ui->nullButton->setStyleSheet("QPushButton { background-color: darkCyan; }");
    isCellSelected = false;

    invalidateWindow();


    clock = new Clock();
    ui->verticalLayout->addWidget(clock);
    clock->setHidden(true);

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
            cell[i][j]->assignedNumber = 0;
            cell[i][j]->setText("");
        }
    }
}



void Sudoku::number_clicked()
{
    if (isCellSelected) {
        QPushButton *numberButton = (QPushButton *)sender();
        number[cell[coorX][coorY]->assignedNumber - 1]->setEnabled(true);
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
        if(ui->hintButton->isChecked())
        {
            number[cell[coorX][coorY]->assignedNumber - 1]->setEnabled(false);
        }

        ui->nullButton->setEnabled(true);

        if(isSudokuComplete())
        {
            invalidateWindow();
            clock->stopTimer();
        }
    }
    else if (ui->clueButton->isChecked())
    {
        invalidateWindow();
        validateWindow();
        QPushButton *numberButton = (QPushButton *)sender();
        for (int k = 0; k < 9; k++)
        {
            for (int l = 0; l < 9; l++)
            {
                cell[k][l]->setStyleSheet("background-color: yellow");
            }

        }
        for (int k = 0; k < 9; k++)
        {
            for (int l = 0; l < 9; l++)
            {
                if(cell[k][l]->assignedNumber)
                {
                    if(cell[k][l]->assignedNumber == numberButton->text().toInt())
                    {
                        int centerX = k / 3;
                        int centerY = l / 3;

                        for (int i = 0; i < 9; i++)
                        {
                            for (int j = 0; j < 9; j++)
                            {

                                if  ((i == k || j == l || (i / 3 == centerX && j / 3 == centerY)))
                                {

                                        if (!cell[i][j]->assignedNumber)
                                        {
                                            if(cell[i][j]->color == 0)
                                            {
                                                cell[i][j]->setStyleSheet("QPushButtonGrid { background-color: darkBlue; }");
                                            }
                                            else
                                            {
                                                cell[i][j]->setStyleSheet("QPushButtonGrid { background-color: magenta; }");
                                            }
                                        }
                                    }

                            }

                        }
                    }
                    if(cell[k][l]->color == 0)
                    {
                        cell[k][l]->setStyleSheet("QPushButtonGrid { background-color: darkBlue; }");
                    }
                    else
                    {
                        cell[k][l]->setStyleSheet("QPushButtonGrid { background-color: magenta; }");
                    }
                }



            }

        }
        for (int i = 0; i < 9; i++)
        {
            number[i]->setEnabled(true);
        }
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
            cell[coorX][coorY]->setStyleSheet("QPushButtonGrid { background-color: darkBlue; }");
        }
        else
        {
            cell[coorX][coorY]->setStyleSheet("QPushButtonGrid { background-color: magenta; }");
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

    for (int i = 0; i < 9; i++)
    {
        number[i]->setEnabled(true);
    }

    if(ui->hintButton->isChecked())
    {
        validateCell();
    }


    cell->setStyleSheet("QPushButtonGrid { background-color: darkRed; }");
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


void Sudoku::on_actionNew_triggered()
{
    sudokuErrorWiper();
    while(!sudokuBlankChecker())
    {
        sudokuErrorWiper();
        sudokuGenerator(0);
    }
    invalidateWindow();
    validateWindow();
    clock->startTimer();
    clock->setHidden(false);
}


void Sudoku::on_actionOpen_triggered()
{
    QString code[9];
    QString key[9];
    QString hint[9];

    crypt = "";
    int decimal = 0;
    int digit = 0;
    QString sign;
    QString synt;

    sudokuErrorWiper();

    QFile inFile("/Users/Jake/Desktop/savedGame.txt");
    inFile.open(QIODevice::Text | QIODevice::ReadOnly);
    QTextStream in(&inFile);

    int tracker = 0;

    while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.length())
            {
                line.replace(QString("\n"), QString(""));
                if(tracker % 3 == 0)
                {
                    code[tracker / 3] = line;
                }
                else if(tracker % 3 == 1)
                {
                    key[tracker / 3] = line;
                }
                else if(tracker % 3 == 2)
                {
                    hint[tracker / 3] = line;
                }
                tracker++;
            }

        }

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
                cell[i][j]->realNumber = deltaInverse;
            }
            else
            {
                cell[i][j]->realNumber = cell[i][j - 1]->realNumber + deltaInverse;
            }

            //crypt = crypt.append(QString("%1").arg(testing[i][j]));
        }
        //crypt = crypt.append("\n");
        decimal = 0;
    }
    invalidateWindow();
    validateWindow();

    for (int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if (hint[i].mid(j, 1).toInt())
            {
                cell[8 - i][8 - j]->setText(hint[i].mid(j, 1));
            }
            else
            {
                cell[8 -i][8 - j]->setText("");
            }
            cell[8 -i][8 - j]->assignedNumber = hint[i].mid(j, 1).toInt();
        }
    }
    clock->setHidden(true);
}


void Sudoku::on_actionSave_triggered()
{
    QString code[9];
    QString key[9];
    QString hint[9];
    int binaryBuffer = 0;

    crypt = "";
    int delta = 0;

    if (!sudokuBlankChecker())
    {
        return;
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {

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

            hint[i] = hint[i].append(QString("%1").arg(cell[8 - i][8 - j]->assignedNumber));


            /*if(cell[i][j]->assignedNumber)
            {
                binaryBuffer2 += pow(2, 8 - j);
            }*/

        }
        key[i].setNum(binaryBuffer, 16);
        //hint[i].setNum(binaryBuffer2, 16);

        delta = 0;
        binaryBuffer = 0;
        //binaryBuffer2 = 0;
        crypt = crypt.append(QString("%1\n").arg(code[i]));
        crypt = crypt.append(QString("%1\n").arg(key[i]));
        crypt = crypt.append(QString("%1\n").arg(hint[i]));
    }

    QFile outFile("/Users/Jake/Desktop/savedGame.txt");
    outFile.open(QIODevice::Text | QIODevice::WriteOnly);
    QTextStream out(&outFile);

    out << crypt;
    outFile.flush();
    outFile.close();

    crypt.clear();
}


void Sudoku::validateWindow()
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            cell[i][j]->setEnabled(true);

        }
    }

    ui->groupBox_2->setEnabled(true);
}


void Sudoku::invalidateWindow()
{
    coorX = -1;
    coorY = -1;
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            cell[i][j]->setEnabled(false);

            if(cell[i][j]->color == 0)
            {
                cell[i][j]->setStyleSheet("QPushButtonGrid { background-color: darkBlue; }");
            }
            else
            {
                cell[i][j]->setStyleSheet("QPushButtonGrid { background-color: magenta; }");
            }
        }
        number[i]->setEnabled(false);
    }
    ui->nullButton->setEnabled(false);
    ui->radioButton->setChecked(false);
    isCellSelected = false;

    ui->groupBox_2->setEnabled(false);

}


void Sudoku::on_actionClose_triggered()
{
    sudokuErrorWiper();
    invalidateWindow();
    clock->setHidden(true);
}

void Sudoku::on_pushButton_clicked()
{
    QDialog saveName;
    saveName.exec();
}

bool Sudoku::isSudokuComplete()
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if (cell[i][j]->realNumber != cell[i][j]->assignedNumber)
            {
                return false;
            }
        }
    }
    return true;
}

void Sudoku::on_normalButton_clicked()
{
    invalidateWindow();
    validateWindow();
    for (int i = 0; i < 9; i++)
    {
        number[i]->setEnabled(true);
    }
    ui->gridLayout->setEnabled(true);
    if (isCellSelected){
        for (int i = 0; i < 9; i++)
        {
            number[i]->setEnabled(true);
        }
    }

}

void Sudoku::on_hintButton_clicked()
{
    invalidateWindow();
    validateWindow();
    for (int i = 0; i < 9; i++)
    {
        number[i]->setEnabled(true);
    }
    ui->gridLayout->setEnabled(true);
    if (isCellSelected){
        validateCell();
    }
}

void Sudoku::on_clueButton_clicked()
{
    invalidateWindow();
    ui->groupBox_2->setEnabled(true);
    for (int i = 0; i < 9; i++)
    {
        number[i]->setEnabled(true);
    }
}
