//
// Created by alexis on 19/02/18.
//

#ifndef APPIMAGE_DESKTOP_INTEGRATION_FIRSTRUN_H
#define APPIMAGE_DESKTOP_INTEGRATION_FIRSTRUN_H

#include <QObject>
#include <QQueue>
#include <functional>

class FirstRun : public  QObject {
    Q_OBJECT
    QByteArray target;
    bool isFailed;
    QQueue<std::function<void(void)>> steps;
    void createApplicationsHomeDir();

public:
    FirstRun(const QString &target, QObject *parent = nullptr);

signals:
    void opening(const QString &file);
    void canceled();
    void completed();
    void unrecognizedAppimageFormat(const QString &file);
    void noSignature();

    void stepCompleted();

    void deployStarted();
    void deployError(const QString &msg);
    void deployCompleted();

public slots:
    void verify();
    void cancel();

    void run();
    void runIsolated();
    void deploy();
    void deploySystemWide();

protected slots:
    void nextStep();

protected:
    void verifyType();

    void verifySignature();


};


#endif //APPIMAGE_DESKTOP_INTEGRATION_FIRSTRUN_H
