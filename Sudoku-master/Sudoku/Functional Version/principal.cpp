#include "principal.h"
#include "ui_principal.h"
#include "sudoku.h"
#include "ui_sudoku.h"
#include <QMessageBox>

principal::principal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::principal)
{
    ui->setupUi(this);
}

principal::~principal()
{
    delete ui;
}

void principal::on_pb_play_clicked()
{
    bool easy;
    bool medium;
    bool hard;
    easy =ui->rb_easy->isChecked();
    medium=ui->rb_medium->isChecked();
    hard=ui->rb_hard->isChecked();
    if (easy==false && medium==false && hard==false)
    {
        QMessageBox::critical(this,"ERROR","Escoja un nivel");
    }
    else if (easy)
    {
        Sudoku *s = new Sudoku(this,1);
        s->show();
        this->setVisible(false);
    }
    else if (medium)
    {
        Sudoku *s = new Sudoku(this,2);
        s->show();
        this->setVisible(false);
    }
    else if (hard)
    {
        Sudoku *s = new Sudoku(this,3);
        s->show();
        this->setVisible(false);
    }


}
