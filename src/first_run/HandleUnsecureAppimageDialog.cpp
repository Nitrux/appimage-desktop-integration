#include "HandleUnsecureAppimageDialog.h"
#include "ui_HandleUnsecureAppimageDialog.h"

#include <QAction>
#include <QMenu>

HandleUnsecureAppimageDialog::HandleUnsecureAppimageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HandleUnsecureAppimageDialog)
{
    ui->setupUi(this);
    setupDeployOptionsMenu();
    setupRunOptionsMenu();
}

void HandleUnsecureAppimageDialog::setupDeployOptionsMenu()
{
    deploySystemAction = new QAction(QIcon(":/images/document-download.svg"),
                                     tr("Deploy System Wide"), this);
    connect(deploySystemAction, &QAction::triggered, [=](){ emit deploySystemWide(); });
    deploySystemAction->setEnabled(false);

    deployOptionsMenu = new QMenu(this);
    deployOptionsMenu->addAction(deploySystemAction);

    ui->deployOptionsButton->setMenu(deployOptionsMenu);
}

void HandleUnsecureAppimageDialog::setupRunOptionsMenu()
{
    runUnsecureAction = new QAction(QIcon(":/images/application-x-executable.svg"),
                                    tr("Run Unsecure"), this);
    connect(runUnsecureAction, &QAction::triggered, [=](){ emit run(); });

    runOptionsMenu = new QMenu(this);
    runOptionsMenu->addAction(runUnsecureAction);

    ui->runOptionsButton->setMenu(runOptionsMenu);
}


HandleUnsecureAppimageDialog::~HandleUnsecureAppimageDialog()
{
    delete ui;

    delete runOptionsMenu;
    delete deployOptionsMenu;
    delete runUnsecureAction;
    delete deploySystemAction;
}

void HandleUnsecureAppimageDialog::on_runButton_clicked()
{
    emit runIsolated();
}

void HandleUnsecureAppimageDialog::on_closeButton_clicked()
{
    reject();
}

void HandleUnsecureAppimageDialog::on_deployButton_clicked()
{
    emit deploy();
}
