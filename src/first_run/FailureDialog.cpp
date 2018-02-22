#include "FailureDialog.h"
#include "ui_FailureDialog.h"

FailureDialog::FailureDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FailureDialog)
{
    ui->setupUi(this);
}

FailureDialog::~FailureDialog()
{
    delete ui;
}

void FailureDialog::setText(const QString &text)
{
    ui->labelBody->setText(text);
}

void FailureDialog::on_closeButton_clicked()
{
    emit closed();
}
