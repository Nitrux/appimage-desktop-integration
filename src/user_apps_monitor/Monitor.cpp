//
// Created by alexis on 3/1/18.
//
#include <QFile>
#include <QFileSystemWatcher>
#include <QDebug>

#include <appimage/appimage.h>
#include <Registry.h>
#include <QtCore/QProcess>
#include "Monitor.h"

void Monitor::setRegistry(Registry *registry) {
    Monitor::registry = registry;
}

void Monitor::setWatcher(QFileSystemWatcher *watcher) {
    Q_ASSERT(watcher);

    Monitor::watcher = watcher;
}

Monitor::Monitor(QObject *parent) : QObject(parent) {}

void Monitor::sanitizeMenuEntries() {
    qDebug() << "Sanitizing menu entries: ";
    const auto list = registry->getOrphanDesktopIntegrationFiles();
    for (const QString &path: list) {
        QFile::remove(path);
        qDebug() << "Deleting: " << path;
    }
    qDebug() << "Sanitize completed";
}

void Monitor::deployMissingEntries() {
    qDebug() << "Deploy missing menu entries: ";
    const auto list = registry->getApplicationsWithoutDesktopIntegration();
    for (const QString &path: list) {
        int result = appimage_register_in_system(path.toLocal8Bit(), true);
        if (result)
                qWarning() << "Unable to create menu entries for: " << path;
    }
    qDebug() << "Deploy completed";
}

void Monitor::startWatch() {
    connect(watcher, &QFileSystemWatcher::directoryChanged, this, &Monitor::handleDirectoryChanged);
}

void Monitor::handleDirectoryChanged(const QString &) {
    sanitizeMenuEntries();
    deployMissingEntries();
}
