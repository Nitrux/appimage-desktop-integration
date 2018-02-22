#ifndef OPENINGDIALOG_H
#define OPENINGDIALOG_H

#include <QDialog>

namespace Ui {
class ProgressDialog;
}

class ProgressDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ProgressDialog(QWidget *parent = 0);
    ~ProgressDialog();

    void setText(const QString &text);
private slots:
    void on_cancelButton_clicked();

private:
    Ui::ProgressDialog *ui;
};

#endif // OPENINGDIALOG_H
