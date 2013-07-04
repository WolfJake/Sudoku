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

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void validateWindow();

    void invalidateWindow();

    void on_actionClose_triggered();

private:
    void initGui();
    Ui::Sudoku *ui;

    QPushButtonGrid *cell[9][9];
    QPushButton *number[9];
    QString crypt;

    int coorX;
    int coorY;
    bool isCellSelected;
};

#endif // SUDOKU_H
