#ifndef HANDLEUNSECUREAPPIMAGEDIALOG_H
#define HANDLEUNSECUREAPPIMAGEDIALOG_H

#include <QDialog>

class QMenu;
class QActions;
namespace Ui {
class HandleUnsecureAppimageDialog;
}

class HandleUnsecureAppimageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HandleUnsecureAppimageDialog(QWidget *parent = 0);
    ~HandleUnsecureAppimageDialog();

signals:
    void deploy();
    void deploySystemWide();
    void run();
    void runIsolated();

private slots:
    void on_deployButton_clicked();

private slots:
    void on_closeButton_clicked();

    void on_runButton_clicked();

private:
    Ui::HandleUnsecureAppimageDialog *ui;
    QMenu *runOptionsMenu;
    QMenu *deployOptionsMenu;
    QAction *runUnsecureAction;
    QAction *deploySystemAction;
    void setupDeployOptionsMenu();
    void setupRunOptionsMenu();
};

#endif // HANDLEUNSECUREAPPIMAGEDIALOG_H
