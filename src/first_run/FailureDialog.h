#ifndef FAILUREDIALOG_H
#define FAILUREDIALOG_H

#include <QWidget>

namespace Ui {
class FailureDialog;
}

class FailureDialog : public QWidget
{
    Q_OBJECT

public:
    explicit FailureDialog(QWidget *parent = 0);
    ~FailureDialog();

    void setText(const QString &text);

signals:
    void closed();

private slots:
    void on_closeButton_clicked();

private:
    Ui::FailureDialog *ui;
};

#endif // FAILUREDIALOG_H
