#include "DeploymentDialog.h"
#include "ui_DeploymentDialog.h"

#include <QPushButton>

DeploymentDialog::DeploymentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeploymentDialog)
{
    ui->setupUi(this);

    QWidget *w = ui->pageBusy;
    ui->stackedWidget->setCurrentWidget(w);

    resizeToStackedWidgetContent(w);

    connect(ui->cancelButton_2, &QPushButton::released, this, &DeploymentDialog::reject);
    connect(ui->closeButton_2, &QPushButton::released, this, &DeploymentDialog::accept);
    connect(ui->closeButton_3, &QPushButton::released, this, &DeploymentDialog::accept);
    connect(ui->closeButton_4, &QPushButton::released, this, &DeploymentDialog::accept);
}

DeploymentDialog::~DeploymentDialog()
{
    delete ui;
}

void DeploymentDialog::handleSuccessDelpoy()
{
    QWidget *w = ui->pageSuccess;
    ui->stackedWidget->setCurrentWidget(w);

    resizeToStackedWidgetContent(w);
}

void DeploymentDialog::handleFailDelpoy()
{
    QWidget *w = ui->pageFailDeployUser;
    ui->stackedWidget->setCurrentWidget(w);

    resizeToStackedWidgetContent(w);
}

void DeploymentDialog::resizeToStackedWidgetContent(QWidget *widget)
{
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    widget->adjustSize();
    adjustSize();
}
