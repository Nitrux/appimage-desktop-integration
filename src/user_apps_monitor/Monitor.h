//
// Created by alexis on 3/1/18.
//

#ifndef APPIMAGE_DESKTOP_INTEGRATION_MONITOR_H
#define APPIMAGE_DESKTOP_INTEGRATION_MONITOR_H

#include <QObject>

class Registry;
class QFileSystemWatcher;

class Monitor : public QObject {
    Q_OBJECT
    Registry *registry;
    QFileSystemWatcher *watcher;

public:
    Monitor(QObject *parent = nullptr);

    void setRegistry(Registry *registry);

    void setWatcher(QFileSystemWatcher *watcher);


    void sanitizeMenuEntries();

    void deployMissingEntries();

    void startWatch();

protected slots:
    void handleDirectoryChanged(const QString &path);
};


#endif //APPIMAGE_DESKTOP_INTEGRATION_MONITOR_H
