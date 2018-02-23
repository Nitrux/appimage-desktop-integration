#include "ValidationDialog.h"
#include "ui_ValidationDialog.h"

ValidationDialog::ValidationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ValidationDialog)
{
    ui->setupUi(this);
    showOpeningPage();
}

ValidationDialog::~ValidationDialog()
{
    delete ui;
}


void ValidationDialog::showOpeningPage()
{
    QWidget *widget = ui->pageOpening;
    ui->stackedWidget->setCurrentWidget(widget);

    resizeToStackedWidgetContent(widget);
    show();
}

void ValidationDialog::showErrorPage()
{
    QWidget *widget = ui->pageError;
    ui->stackedWidget->setCurrentWidget(widget);
    resizeToStackedWidgetContent(widget);
    show();
}

void ValidationDialog::resizeToStackedWidgetContent(QWidget *widget)
{
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    widget->adjustSize();
    adjustSize();
}

void ValidationDialog::on_closeButton_released()
{
    reject();
}

void ValidationDialog::on_cancelButton_released()
{
    reject();
}
