#include "formm.h"
#include "ui_formm.h"

Formm::Formm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Formm)
{
    ui->setupUi(this);
}

Formm::~Formm()
{
    delete ui;
}
