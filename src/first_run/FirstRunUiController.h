//
// Created by alexis on 20/02/18.
//

#ifndef APPIMAGE_DESKTOP_INTEGRATION_FIRSTRUNCONTROLLER_H
#define APPIMAGE_DESKTOP_INTEGRATION_FIRSTRUNCONTROLLER_H

#include <QObject>
#include <QStackedWidget>

class FirstRunUiController : public QObject {
    Q_OBJECT
    QStackedWidget stackedWidget;

public:
    FirstRunUiController(QObject *parent = nullptr) : QObject(parent) {}

signals:
    void cancelRequested();
    void deploy();
    void deploySystemWide();
    void run();
    void runIsolated();

public slots:
    void close();
    void showOpeningDialog(const QString &file);
    void showUnknownFileDialog(const QString &file);
    void showNoSignatureDialog();
    void showDeployProgress();
    void showDeployCompleteDialog();
    void showDeployErrorDialog(const QString &msg);

protected slots:
    void showMainWindow();
    void pushWidget(QWidget *widget);
    void popWidget();
};


#endif //APPIMAGE_DESKTOP_INTEGRATION_FIRSTRUNCONTROLLER_H
