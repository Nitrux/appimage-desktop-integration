#ifndef UNSECUREAPPIMAGEDIALOG_H
#define UNSECUREAPPIMAGEDIALOG_H

#include <QDialog>

class QMenu;
class QActions;
namespace Ui {
class UnsecureAppimageDialog;
}

class UnsecureAppimageDialog : public QDialog
{
    Q_OBJECT
    QString path;
public:
    explicit UnsecureAppimageDialog(QWidget *parent = 0);
    ~UnsecureAppimageDialog();

    void setAppimage(const QString &path);

signals:
    void deployUserwide(const QString &path);
    void deploySystemwide(const QString &path);
    void run(const QString &path);
    void runIsolated(const QString &path);

private slots:
    void on_deployButton_clicked();
    void on_closeButton_clicked();
    void on_runButton_clicked();

private:
    Ui::UnsecureAppimageDialog *ui;
    QMenu *runOptionsMenu;
    QMenu *deployOptionsMenu;
    QAction *runUnsecureAction;
    QAction *deploySystemAction;
    void setupDeployOptionsMenu();
    void setupRunOptionsMenu();
};

#endif // UNSECUREAPPIMAGEDIALOG_H
