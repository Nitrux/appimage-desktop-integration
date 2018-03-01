//de empleo
// Created by alexis on 2/23/18.
//

#include <QDir>
#include <QCoreApplication>
#include <QFileSystemWatcher>
#include <QStandardPaths>

#include <Registry.h>
#include "Monitor.h"
#include "Deployer.h"

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("user-apps-monitor");

    QFileSystemWatcher watcher;
    const QStringList watchPaths = {
        "/opt",
        QDir::homePath() + "/Applications"
    };

    watcher.addPaths(watchPaths);

    Registry r;
    r.setDataLocations(QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation));
    r.setAppimageLocations(watchPaths);

    Monitor m;
    m.setRegistry(&r);
    m.setWatcher(&watcher);

    m.sanitizeMenuEntries();
    m.deployMissingEntries();

    m.startWatch();
    return app.exec();
}
