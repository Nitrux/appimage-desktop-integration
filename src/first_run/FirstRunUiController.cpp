//
// Created by alexis on 20/02/18.
//
#include <QDialog>
#include <QIcon>
#include <QMessageBox>
#include <QDebug>

#include "FirstRunUiController.h"
#include "ProgressDialog.h"
#include "HandleUnsecureAppimageDialog.h"
#include "FailureDialog.h"


void FirstRunUiController::showOpeningDialog(const QString &file) {
    ProgressDialog *dialog = new ProgressDialog();
    dialog->setText(tr("Opening Appimage file, please waith ..."));

    connect(dialog, &ProgressDialog::finished, this, &FirstRunUiController::cancelRequested);

    pushWidget(dialog);
}

void FirstRunUiController::showMainWindow() {
    stackedWidget.setVisible(true);
    stackedWidget.setWindowIcon(QIcon(":/images/appimage.svg"));
}

void FirstRunUiController::close() {
    auto win = stackedWidget.window();
    win->close();
}

void FirstRunUiController::showUnknownFileDialog(const QString &file) {
    FailureDialog *dialog = new FailureDialog();
    dialog->setText(tr("Unable to open: %1").arg(file));
    connect(dialog, &FailureDialog::closed, this, &FirstRunUiController::cancelRequested);

    pushWidget(dialog);
}

void FirstRunUiController::showNoSignatureDialog() {
    stackedWidget.removeWidget(nullptr);
    HandleUnsecureAppimageDialog *dialog = new HandleUnsecureAppimageDialog();

    connect(dialog, &HandleUnsecureAppimageDialog::run, this, &FirstRunUiController::run);
    connect(dialog, &HandleUnsecureAppimageDialog::runIsolated, this, &FirstRunUiController::runIsolated);
    connect(dialog, &HandleUnsecureAppimageDialog::deploy, this, &FirstRunUiController::deploy);
    connect(dialog, &HandleUnsecureAppimageDialog::deploySystemWide, this, &FirstRunUiController::deploySystemWide);
    connect(dialog, &HandleUnsecureAppimageDialog::finished, this, &FirstRunUiController::cancelRequested);

    int idx = stackedWidget.addWidget(dialog);
    stackedWidget.setCurrentIndex(idx);

    showMainWindow();
}

void FirstRunUiController::showDeployProgress()
{
    ProgressDialog *dialog = new ProgressDialog();
    dialog->setText(tr("Deploying, please waith ..."));

    pushWidget(dialog);
}

void FirstRunUiController::showDeployCompleteDialog()
{
    QMessageBox *dialog = new QMessageBox();
    dialog->setText(tr("The appimage was successfuly added to your system menu."));
    connect(dialog, &QMessageBox::finished, this, &FirstRunUiController::popWidget);
    popWidget();
    pushWidget(dialog);
}

void FirstRunUiController::showDeployErrorDialog(const QString &msg)
{
    FailureDialog *dialog = new FailureDialog();
    connect(dialog, &FailureDialog::closed, this, &FirstRunUiController::popWidget);

    dialog->setText(msg);

    popWidget();
    pushWidget(dialog);
}

void FirstRunUiController::pushWidget(QWidget *widget)
{
    int idx = stackedWidget.addWidget(widget);
    stackedWidget.setCurrentIndex(idx);

    showMainWindow();
}


void FirstRunUiController::popWidget()
{
    QWidget *current = stackedWidget.currentWidget();
    stackedWidget.removeWidget(current);
    current->deleteLater();
}
