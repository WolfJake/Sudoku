#ifndef SUDOKU_H
#define SUDOKU_H

#include <QMainWindow>
#include "principal.h"
#include "ui_principal.h"


class principal;

namespace Ui {
class Sudoku;
}

class QGridLayout;
class QPushButton;
class QPushButtonGrid;
class Clock;

class Sudoku : public QMainWindow
{
    Q_OBJECT

public:
    explicit Sudoku(QWidget *parent = 0,int level = 1);
    ~Sudoku();

private slots:
    void initGui();

    bool validateCellAtPointWithNumber(int row, int column, int value, int counter);

    bool numberAssigner(int counter, int row, int column, int value);

    void sudokuGenerator(int row);

    bool sudokuBlankChecker();

    void sudokuErrorWiper();

    bool isSudokuComplete();

    void number_clicked();

    void cell_clicked();

    void on_nullButton_clicked();

    void validateCell();    

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionClose_triggered();

    void on_actionQuit_triggered();

    void validateWindow();

    void invalidateWindow();

    void on_pushButton_clicked();

    void on_normalButton_clicked();

    void on_hintButton_clicked();

    void on_clueButton_clicked();

    void levelEasy();

    void levelMedium();

    void levelHard();

    void on_actionNew_triggered();

private:

    Ui::Sudoku *ui;

    QPushButtonGrid *cell[9][9];
    QPushButton *number[9];
    QString crypt;
    Clock *clock;

    int coorX;
    int coorY;
    bool isCellSelected;
    int lev;
    principal *p;
};

#endif // SUDOKU_H
