#include "UnsecureAppimageDialog.h"
#include "ui_UnsecureAppimageDialog.h"

#include <QAction>
#include <QMenu>

UnsecureAppimageDialog::UnsecureAppimageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UnsecureAppimageDialog)
{
    ui->setupUi(this);
    setupDeployOptionsMenu();
    setupRunOptionsMenu();
}

void UnsecureAppimageDialog::setupDeployOptionsMenu()
{
    deploySystemAction = new QAction(QIcon(":/images/document-download.svg"),
                                     tr("Deploy System Wide"), this);
    connect(deploySystemAction, &QAction::triggered, [=](){ emit deploySystemwide(path); });
    deploySystemAction->setEnabled(false);

    deployOptionsMenu = new QMenu(this);
    deployOptionsMenu->addAction(deploySystemAction);

    ui->deployOptionsButton->setMenu(deployOptionsMenu);
}

void UnsecureAppimageDialog::setupRunOptionsMenu()
{
    runUnsecureAction = new QAction(QIcon(":/images/application-x-executable.svg"),
                                    tr("Run Unsecure"), this);
    connect(runUnsecureAction, &QAction::triggered, [=](){ emit run(path); });

    runOptionsMenu = new QMenu(this);
    runOptionsMenu->addAction(runUnsecureAction);

    ui->runOptionsButton->setMenu(runOptionsMenu);
}


UnsecureAppimageDialog::~UnsecureAppimageDialog()
{
    delete ui;

    delete runOptionsMenu;
    delete deployOptionsMenu;
    delete runUnsecureAction;
    delete deploySystemAction;
}

void UnsecureAppimageDialog::setAppimage(const QString &path)
{
    UnsecureAppimageDialog::path = path;
}

void UnsecureAppimageDialog::on_runButton_clicked()
{
    emit run(path);
}

void UnsecureAppimageDialog::on_closeButton_clicked()
{
    reject();
}

void UnsecureAppimageDialog::on_deployButton_clicked()
{
    emit deployUserwide(path);
}

void UnsecureAppimageDialog::on_checkBox_toggled(bool checked)
{
    ui->runButton->setEnabled(checked);
    if (checked)
        emit trust(path);
    else
        emit untrust(path);
}
