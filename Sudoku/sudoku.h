#ifndef SUDOKU_H
#define SUDOKU_H

#include <QMainWindow>

namespace Ui {
class Sudoku;
}

class QGridLayout;
class QPushButton;

class Sudoku : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Sudoku(QWidget *parent = 0);
    ~Sudoku();

private slots:
    void on_actionQuit_triggered();

    void on_rowBox_valueChanged(int arg1);

    void on_columnBox_valueChanged(int arg1);

    void number_clicked();

    void cell_clicked();

    void on_nullButton_clicked();

private:
    void initGui();
    Ui::Sudoku *ui;

    QGridLayout *grid;
    QPushButton *cell[9][9];
    QPushButton *number[9];
};

#endif // SUDOKU_H
