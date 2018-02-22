//
// Created by alexis on 19/02/18.
//
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>

#include <appimage/appimage.h>

#include "FirstRun.h"

FirstRun::FirstRun(const QString &target, QObject *parent) : QObject(parent), isFailed(false) {
    QString scapedTarget = target;
    if (scapedTarget.contains("~"))
        scapedTarget.replace("~", QDir::homePath());

    if (scapedTarget.contains("$HOME"))
        scapedTarget.replace("$HOME", QDir::homePath());

    QFileInfo f(scapedTarget);
    FirstRun::target = f.absoluteFilePath().toLocal8Bit();
}

void FirstRun::verify() {
    steps.enqueue([=]() { verifyType(); });
    steps.enqueue([=]() { verifySignature(); });

    connect(this, &FirstRun::stepCompleted, this, &FirstRun::nextStep);
    nextStep();
}

void FirstRun::nextStep() {
    if (isFailed)
        return;

    if (!steps.isEmpty()) {
        const auto f = steps.dequeue();
        f();
    } else
            emit completed();
}

void FirstRun::cancel() {
    emit canceled();
}

void FirstRun::run()
{
    auto permissions = QFile::permissions(target);
    QFile::setPermissions(target, permissions | QFileDevice::ExeUser);
    QProcess p;
    bool started = p.startDetached(target);
    if (started)
        emit completed();
    else
        qWarning() << p.errorString() << " while running " << target;

    QFile::setPermissions(target, permissions);
}

void FirstRun::runIsolated()
{
    qDebug() << __FUNCTION__ << " not implemented yet!";
}

void FirstRun::createApplicationsHomeDir()
{
    QDir home =  QDir::home();
    home.mkdir("Applications");
}

void FirstRun::deploy()
{
    createApplicationsHomeDir();

    QFile f(target);
    QFileInfo info(f);
    f.rename(QDir::homePath()+ "/Applications/"  +info.completeBaseName());


    emit deployStarted();
    int result = appimage_register_in_system(f.fileName().toLocal8Bit(), true);
    if (result == 0)
        emit deployCompleted();
    else {
        const QString errorMsg = tr("Something whent wrong while deploying the application.");
        emit deployError(errorMsg);
        qWarning() << errorMsg;
    }
}

void FirstRun::deploySystemWide()
{
    qDebug() << __FUNCTION__ << " not implemented yet!";
}

void FirstRun::verifyType() {
    emit opening(target);
    int res = check_appimage_type(target, true);

    if (res < 0) {
        isFailed = true;
        emit unrecognizedAppimageFormat(target);
    }

    emit stepCompleted();
}

void FirstRun::verifySignature() {
    emit noSignature();
}
