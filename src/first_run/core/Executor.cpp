#include "Executor.h"

#include <QDir>
#include <QProcess>

#include <QDebug>

Executor::Executor(QObject *parent) : QObject(parent)
{

}

void Executor::execute(const QString &path)
{
    auto permissions = QFile::permissions(path);
    QFile::setPermissions(path, permissions | QFileDevice::ExeUser);

    startDetached(path);

    QFile::setPermissions(path, permissions);
}

void Executor::executeIsolated(const QString &path)
{
}

void Executor::startDetached(const QString &path, QStringList arguments)
{
    QString parentDir = getParentDirPath(path);

    bool started = QProcess::startDetached(path, arguments, parentDir);
    if (started)
        emit executed();
    else
        emit failure();
}

QString Executor::getParentDirPath(const QString &path)
{
    QFileInfo fi(path);
    QString parentDir = fi.dir().path();

    return parentDir;
}
