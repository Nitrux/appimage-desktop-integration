//de empleo
// Created by alexis on 2/23/18.
//

#include <QDir>
#include <QCoreApplication>
#include <QFileSystemWatcher>

#include "Registry.h"

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("user-apps-monitor");

    QFileSystemWatcher watcher;
    const QStringList watchPaths = {
        "/opt",
        QDir::homePath() + "/Applications"
    };

    watcher.addPaths(watchPaths);

    Registry r();

    return app.exec();
}
