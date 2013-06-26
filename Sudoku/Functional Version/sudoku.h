#ifndef SUDOKU_H
#define SUDOKU_H

#include <QMainWindow>

namespace Ui {
class Sudoku;
}

class QGridLayout;
class QPushButton;
class QPushButtonGrid;

class Sudoku : public QMainWindow
{
    Q_OBJECT

public:
    explicit Sudoku(QWidget *parent = 0);
    ~Sudoku();

private slots:
    void on_actionQuit_triggered();

    void number_clicked();

    void cell_clicked();

    void on_nullButton_clicked();

    void validateCell();

    bool validateCellAtPointWithNumber(int row, int column, int value, int counter);

    bool numberAssigner(int counter, int row, int column, int value);

    void sudokuGenerator(int row);

    bool sudokuBlankChecker();

    void sudokuErrorWiper();


private:
    void initGui();
    Ui::Sudoku *ui;

    QGridLayout *grid;
    QPushButtonGrid *cell[9][9];
    QPushButton *number[9];
    int coorX;
    int coorY;
    bool isCellSelected;
};

#endif // SUDOKU_H
