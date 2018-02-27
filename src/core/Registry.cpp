#include "Registry.h"

#include <QDebug>
#include <QStandardPaths>

#include <appimage/appimage.h>

Registry::Registry(QObject *parent) : QObject(parent)
{
    dataLocations = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation);
}

void Registry::setDataLocations(const QStringList &dataLocations)
{
    Registry::dataLocations = dataLocations;
}

QSet<QString> Registry::getDeployedAppimageHashes()
{
    QStringList desktopEntries = getDesktopEntriesPaths();
    QStringList icons = getIconsPaths();

    QStringList paths;
    paths.append(desktopEntries);
    paths.append(icons);

    return getHashesFromPaths(paths);
}

QStringList Registry::getDesktopEntriesPaths()
{
    QStringList entries;
    for (const QString &l : dataLocations) {
        QDir d(l+"/applications");
        if (d.exists())
            entries.append(getEntriesAbsolutePaths(d, {"appimagekit*.desktop"}));
        else
            qWarning() << "Applications dir doesn't exist: " << d.absolutePath() ;
    }

    return entries;
}

QStringList Registry::getIconsPaths()
{
    QStringList entries;
    for (const QString &l : dataLocations) {
        QDir d(l+"/icons");
        if (d.exists())
            entries.append(getEntriesAbsolutePaths(d, {"appimagekit_*.png", "appimagekit_*.svg"}));
        else
            qWarning() << "Icons dir doesn't exist: " << d.absolutePath() ;
    }

    return entries;
}



QSet<QString> Registry::getHashesFromPaths(QStringList entries)
{
    QSet<QString> hashes;
    for (const QString &entry: entries)
        hashes << getGetHashFromPath(entry);

    return hashes;
}

QString Registry::getGetHashFromPath(const QString &entry) { return entry.section("/", -1).mid(12, 32); }

QStringList Registry::getEntriesAbsolutePaths(QDir d, const QStringList &filters)
{
    QStringList paths;

    const QStringList &dirEntryList = d.entryList(filters);

    for (const QString &entry : dirEntryList)
        paths.append(d.absoluteFilePath(entry));

    return paths;
}

void Registry::setAppimageLocations(const QStringList &locations) {
    Registry::appimagesLocations = locations;
}

QStringList Registry::getAppimagesPaths() {
    QStringList entries;
    for (const QString &l : appimagesLocations) {
        QDir d(l);
        if (d.exists()) {
            for (const QString &entry : d.entryList(QDir::NoDotAndDotDot | QDir::Files)) {
                const QString path = d.absoluteFilePath(entry);
                int type = check_appimage_type(path.toStdString().c_str(), false);
                if (type > 0)
                    entries << path;
            }

        }
        else
            qWarning() << "Icons dir doesn't exist: " << d.absolutePath() ;
    }

    return entries;
}
