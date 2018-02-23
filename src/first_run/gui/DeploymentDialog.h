#ifndef DEPLOYMENTDIALOG_H
#define DEPLOYMENTDIALOG_H

#include <QDialog>

namespace Ui {
class DeploymentDialog;
}

class DeploymentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeploymentDialog(QWidget *parent = 0);
    ~DeploymentDialog();

signals:
    void canceled();

public slots:
    void handleSuccessDelpoy();
    void handleFailDelpoy();

private:
    Ui::DeploymentDialog *ui;
    void resizeToStackedWidgetContent(QWidget *widget);

};

#endif // DEPLOYMENTDIALOG_H
