#ifndef REGISTRY_H
#define REGISTRY_H

#include <QObject>
#include <QDir>
#include <QSet>
#include <QString>

class Registry : public QObject
{
    Q_OBJECT
    QStringList dataLocations;
    QStringList appimagesLocations;

public:
    explicit Registry(QObject *parent = nullptr);

    void setDataLocations(const QStringList &dataLocations);
    void setAppimageLocations(const QStringList &locations);

    QStringList getDesktopEntriesPaths();
    QStringList getIconsPaths();
    QStringList getAppimagesPaths();

    QStringList getApplicationsWithoutDesktopIntegration();
    QStringList getOrphanDesktopIntegrationFiles();

    static QString extractHashFromDesktopIntegrationFile(const QString &entry);

private:
    QSet<QString> getDeployedAppimageHashes();

    QSet<QString> getHashesFromPaths(QStringList entries);
    QStringList getEntriesAbsolutePaths(QDir d, const QStringList &filters);

    bool isDeployed(const QSet<QString> &deployedAppimagesHashes, const QString &path) const;

    QSet<QString> getAppimageHashes(const QStringList &appimages) const;

    QStringList extractOrphanFiles(const QSet<QString> &hashes, const QStringList &desktopEntries) const;
};

#endif // REGISTRY_H
