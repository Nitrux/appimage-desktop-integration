//
// Created by alexis on 20/02/18.
//

#ifndef APPIMAGE_DESKTOP_INTEGRATION_FIRSTRUNCONTROLLER_H
#define APPIMAGE_DESKTOP_INTEGRATION_FIRSTRUNCONTROLLER_H

#include <QObject>
#include <QStackedWidget>

#include "core/Validator.h"
#include "core/Deployer.h"
#include "core/Executor.h"

#include "gui/ValidationDialog.h"
#include "gui/UnsecureAppimageDialog.h"
#include "gui/DeploymentDialog.h"

class UiController : public QObject {
    Q_OBJECT
    QStackedWidget stackedWidget;

    Validator *validator;
    Deployer *deployer;
    Executor *executor;

    ValidationDialog validationDialog;
    UnsecureAppimageDialog unsecureAppimageDialog;
    DeploymentDialog deploymentDialog;
    QWidget *previousDialog;
    void showPreviousDialog();

public:
    UiController(QObject *parent = nullptr);

    void setValidator(Validator *validator);
    void setDeployer(Deployer *deployer);
    void setExecutor(Executor *executor);

public slots:
    void exec();
    void cancel();

protected slots:
    void handleUnsignedAppimage(const QString &path);
    void handleDeploying();
    void handleDeploymentDialogAccepted();
    void handleDeploymentDialogRejected();
    void handleRun(const QString &path);
    void handleExecuted();
    void handleFailure();
};


#endif //APPIMAGE_DESKTOP_INTEGRATION_FIRSTRUNCONTROLLER_H
