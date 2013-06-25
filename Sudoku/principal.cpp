#include "principal.h"
#include "ui_principal.h"

principal::principal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::principal)
{
    ui->setupUi(this);
}

principal::~principal()
{
    delete ui;
}
