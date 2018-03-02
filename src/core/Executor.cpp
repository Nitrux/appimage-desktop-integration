#include "Executor.h"

#include <QDir>
#include <QProcess>

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
    QFileInfo fi(path);
    bool started = QProcess::startDetached(fi.absoluteFilePath(), arguments, fi.absolutePath());
    if (started)
        emit executed();
    else
        emit failure();
}
