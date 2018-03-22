#ifndef GREETERDIALOG_H
#define GREETERDIALOG_H

#include <QDialog>
#include <QTimer>

#include "FirstRunConfig.h"

namespace Ui {
class GreeterDialog;
}

class GreeterDialog : public QDialog
{
    Q_OBJECT

    QTimer ticker;
    bool pastMonitorStatus;
public:
    explicit GreeterDialog(QWidget *parent = 0);
    ~GreeterDialog();

private slots:
    void on_pushButtonClose_released();

    void on_pushButtonDisableAll_released();

    void on_pushButtonEnableAll_released();

    void on_checkBoxMonitorAutostart_stateChanged(int arg1);

    void on_checkBoxFirstRun_stateChanged(int arg1);

    void on_pushButtonMonitorStatus_released();

    void updateMessages();

private:
    Ui::GreeterDialog *ui;
    FirstRunConfig firstRunConfig;
};

#endif // GREETERDIALOG_H
