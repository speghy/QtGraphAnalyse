#include "openordelete.h"
#include "ui_openordelete.h"

OpenOrDelete::OpenOrDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenOrDelete)
{
    ui->setupUi(this);
}

OpenOrDelete::~OpenOrDelete()
{
    delete ui;
}

int OpenOrDelete::on_pushButton_clicked()
{
    return 1;
}

int OpenOrDelete::on_pushButton_2_clicked()
{
    return 2;
}
