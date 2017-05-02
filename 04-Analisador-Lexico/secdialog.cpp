#include "secdialog.h"
#include "ui_secdialog.h"
#include "analisadorlexico.h"

SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);
}

SecDialog::~SecDialog()
{
    delete ui;
}

void SecDialog::on_pushButton_clicked()
{
    AnalisadorLexico *analisador = new AnalisadorLexico();

    analisador->calcularPadrao(ui->entradaExpressao->text().toStdString(), ui->entradaExpressao->text().toStdString());
}
