#include "Deployer.h"

#include <appimage/appimage.h>

#include <QDir>
#include <QFile>
#include <QFileInfo>

Deployer::Deployer(QObject *parent) : QObject(parent)
{
    userApplicationsDir = QDir::home().filePath("Applications");
    systemApplicationsDir = "/usr/bin/";
}


QString Deployer::getUserDeploymentPath(const QString &path)
{
    QFileInfo fi(path);
    QString newPath = userApplicationsDir + "/" + fi.completeBaseName();

    return newPath;
}

void Deployer::deployUserwide(const QString &path)
{
    Deployer::path = path;
    emit deploying();

    QString newPath = getUserDeploymentPath(path);
    QFile::copy(path, newPath);

    if (!QFile::exists(newPath)) {
        emit failDeploy();
        return;
    }

    int result = appimage_register_in_system(newPath.toLocal8Bit(), true);
    if (result)
        emit failDeploy();
    else
        emit successDeploy();
}

void Deployer::deploySystemwide(const QString &path)
{
    Deployer::path = path;
    emit deploying();
    emit failDeploy();
}

void Deployer::cancelDeploy()
{
    QString newPath = getUserDeploymentPath(path);
    QFile::remove(newPath);
}
