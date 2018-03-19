#include "Registry.h"

#include <QDebug>
#include <QStandardPaths>

#include <appimage/appimage.h>

#include <QSettings>

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
        hashes << extractHashFromDesktopIntegrationFile(entry);

    return hashes;
}

QString Registry::extractHashFromDesktopIntegrationFile(const QString &entry) { return entry.section("/", -1).mid(12, 32); }

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
                int type = appimage_get_type(path.toStdString().c_str(), false);
                if (type > 0)
                    entries << path;
            }

        }
        else
            qWarning() << "Icons dir doesn't exist: " << d.absolutePath() ;
    }

    return entries;
}

QStringList Registry::getApplicationsWithoutDesktopIntegration() {
    const auto appimages = getAppimagesPaths();
    const auto deployedAppimagesHashes = getDeployedAppimageHashes();

    QStringList list;
    for (const QString &path: appimages) {
        if (!isDeployed(deployedAppimagesHashes, path))
            list.append(path);
    }

    return list;
}

bool Registry::isDeployed(const QSet<QString> &deployedAppimagesHashes, const QString &path) const {
    const QString hash = appimage_get_md5(path.toStdString().c_str());
    bool deployed = deployedAppimagesHashes.contains(hash);
    return deployed;
}

QStringList Registry::getOrphanDesktopIntegrationFiles() {
    const auto appimages = getAppimagesPaths();
    const auto hashes = getAppimageHashes(appimages);

    QStringList desktopEntries = getDesktopEntriesPaths();
    QStringList icons = getIconsPaths();

    QStringList list;
    list << extractOrphanFiles(hashes, desktopEntries);
    list << extractOrphanFiles(hashes, icons);

    return list;
}

QStringList Registry::extractOrphanFiles(const QSet<QString> &hashes, const QStringList &desktopEntries) const {
    QStringList list;

    for (const QString &path: desktopEntries) {
        auto hash = extractHashFromDesktopIntegrationFile(path);
        if (!hashes.contains(hash)) {
            list << path;
        }
    }
    return list;
}

QSet<QString> Registry::getAppimageHashes(const QStringList &appimages) const {
    QSet<QString> hashes;
    for (const QString &path: appimages) {
        const QString hash =  appimage_get_md5(path.toStdString().c_str());
        hashes.insert(hash);
    }
    return hashes;
}
