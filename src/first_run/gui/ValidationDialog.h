#ifndef VALIDATIONDIALOG_H
#define VALIDATIONDIALOG_H

#include <QDialog>

namespace Ui {
class ValidationDialog;
}

class ValidationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ValidationDialog(QWidget *parent = 0);
    ~ValidationDialog();

public slots:
    void showOpeningPage();
    void showErrorPage();

private slots:
    void on_cancelButton_released();
    void on_closeButton_released();

private:
    Ui::ValidationDialog *ui;
    void resizeToStackedWidgetContent(QWidget *widget);
};

#endif // VALIDATIONDIALOG_H
