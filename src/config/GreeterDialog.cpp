#include "GreeterDialog.h"
#include "ui_GreeterDialog.h"
#include "UserAppsMonitorConfig.h"

GreeterDialog::GreeterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GreeterDialog)
{
    ui->setupUi(this);
    connect(&ticker, &QTimer::timeout, this, &GreeterDialog::updateMessages);
    ticker.setInterval(1000);
    ticker.start();

    pastMonitorStatus = UserAppsMonitorConfig::isRunning();
    updateMessages();
}

GreeterDialog::~GreeterDialog()
{
    delete ui;
}

void GreeterDialog::on_pushButtonClose_released()
{
    close();
}

void GreeterDialog::on_pushButtonDisableAll_released()
{
    if (firstRunConfig.isEnabled())
        firstRunConfig.disable();

    if (UserAppsMonitorConfig::isEnabled())
        UserAppsMonitorConfig::disable();

    if (UserAppsMonitorConfig::isRunning())
        UserAppsMonitorConfig::stop();
}

void GreeterDialog::on_pushButtonEnableAll_released()
{
    if (!firstRunConfig.isEnabled())
        firstRunConfig.enable();

    if (!UserAppsMonitorConfig::isEnabled())
        UserAppsMonitorConfig::enable();

    if (!UserAppsMonitorConfig::isRunning())
        UserAppsMonitorConfig::start();
}

void GreeterDialog::updateMessages()
{
    bool firstRunEnabled = firstRunConfig.isEnabled();

    bool monitorEnabled = UserAppsMonitorConfig::isEnabled();
    bool monitorRunning = UserAppsMonitorConfig::isRunning();

    ui->checkBoxFirstRun->setChecked(firstRunEnabled);

    ui->checkBoxMonitorAutostart->setChecked(monitorEnabled);

    ui->pushButtonMonitorStatus->setEnabled(true);
    if (monitorRunning) {
        ui->label_MonitorStatus->setText(tr("The application dir monitor is <b>running</b>"));
        ui->pushButtonMonitorStatus->setText(tr("Stop"));
    } else {
        ui->label_MonitorStatus->setText(tr("The application dir monitor is <b>stopped</b>"));
        ui->pushButtonMonitorStatus->setText(tr("Start"));
    }
}


void GreeterDialog::on_pushButtonMonitorStatus_released()
{
    ui->pushButtonMonitorStatus->setEnabled(false);

    if (UserAppsMonitorConfig::isRunning()) {
        UserAppsMonitorConfig::stop();
        ui->label_MonitorStatus->setText(tr("The application dir monitor <b>stop requested</b>"));
    } else {
        UserAppsMonitorConfig::start();
        ui->label_MonitorStatus->setText(tr("The application dir monitor <b>start requested</b>"));
    }
}

void GreeterDialog::on_checkBoxMonitorAutostart_stateChanged(int arg1)
{
    if (arg1)
        UserAppsMonitorConfig::enable();
    else
        UserAppsMonitorConfig::disable();
}

void GreeterDialog::on_checkBoxFirstRun_stateChanged(int arg1)
{
    if (arg1)
        firstRunConfig.enable();
    else
        firstRunConfig.disable();
}
