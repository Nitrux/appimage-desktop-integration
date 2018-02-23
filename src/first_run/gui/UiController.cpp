//
// Created by alexis on 20/02/18.
//
#include <QDialog>
#include <QMessageBox>

#include "UiController.h"


UiController::UiController(QObject *parent) :
    QObject(parent), validator(nullptr), deployer(nullptr), previousDialog(nullptr) {}

void UiController::setValidator(Validator *validator) {
    UiController::validator = validator;
}

void UiController::setDeployer(Deployer *deployer)
{
    UiController::deployer = deployer;
}

void UiController::setExecutor(Executor *executor)
{
    UiController::executor = executor;
}

void UiController::exec()
{
    Q_ASSERT(validator);
    Q_ASSERT(deployer);
    Q_ASSERT(executor);

    QObject::connect(validator, &Validator::invalidAppimage,
                     &validationDialog, &ValidationDialog::showErrorPage);
    QObject::connect(validator, &Validator::finished,
                     &validationDialog, &ValidationDialog::close);
    QObject::connect(validator, &Validator::unsignedAppimage,
                     this, &UiController::handleUnsignedAppimage);

    validationDialog.showOpeningPage();

    validator->validate();
}

void UiController::cancel() {
    validationDialog.close();
    unsecureAppimageDialog.close();
}

void UiController::handleUnsignedAppimage(const QString &path)
{
    unsecureAppimageDialog.setAppimage(path);
    unsecureAppimageDialog.show();

    connect(&unsecureAppimageDialog, &UnsecureAppimageDialog::deployUserwide,
            deployer, &Deployer::deployUserwide);

    connect(&unsecureAppimageDialog, &UnsecureAppimageDialog::run,
            this, &UiController::handleRun);

    connect(&unsecureAppimageDialog, &UnsecureAppimageDialog::trust,
            deployer, &Deployer::trustAppimage);
    connect(&unsecureAppimageDialog, &UnsecureAppimageDialog::untrust,
            deployer, &Deployer::untrustAppimage);

    connect(deployer, &Deployer::deploying,
            this, &UiController::handleDeploying);
}

void UiController::handleDeploying()
{
    previousDialog = &unsecureAppimageDialog;

    unsecureAppimageDialog.hide();

    connect(deployer, &Deployer::successDeploy,
            &deploymentDialog, &DeploymentDialog::handleSuccessDelpoy);
    connect(deployer, &Deployer::failDeploy,
            &deploymentDialog, &DeploymentDialog::handleFailDelpoy);

    connect(&deploymentDialog, &DeploymentDialog::accepted,
            this, &UiController::handleDeploymentDialogAccepted);

    deploymentDialog.show();
}

void UiController::showPreviousDialog()
{
    if (previousDialog)
        previousDialog->show();

    previousDialog = nullptr;
}

void UiController::handleDeploymentDialogAccepted()
{
    showPreviousDialog();
}

void UiController::handleDeploymentDialogRejected()
{
    deployer->cancelDeploy();
    showPreviousDialog();
}

void UiController::handleRun(const QString &path)
{
    connect(executor, &Executor::executed, this, &UiController::handleExecuted);
    connect(executor, &Executor::failure, this, &UiController::handleFailure);

    executor->execute(path);

    validationDialog.close();
    unsecureAppimageDialog.close();
    deploymentDialog.close();
}

void UiController::handleExecuted()
{
    exit(0);
}

void UiController::handleFailure()
{
    QMessageBox msg;
    msg.setText(tr("There was an error while trying to execute the appimage"));
    msg.exec();
}
