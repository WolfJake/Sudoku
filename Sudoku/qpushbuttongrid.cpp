#include "qpushbuttongrid.h"
#include "ui_qpushbuttongrid.h"

QPushButtonGrid::QPushButtonGrid(QPushButton *parent) :
    QPushButton(parent),
    ui(new Ui::QPushButtonGrid)
{
    ui->setupUi(this);
}

QPushButtonGrid::~QPushButtonGrid()
{
    delete ui;
}
