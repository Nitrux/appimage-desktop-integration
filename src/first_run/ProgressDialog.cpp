#include "ProgressDialog.h"
#include "ui_ProgressDialog.h"

ProgressDialog::ProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
}

void ProgressDialog::on_cancelButton_clicked()
{
    reject();
}

void ProgressDialog::setText(const QString &text) {
    ui->label->setText(text);

}
