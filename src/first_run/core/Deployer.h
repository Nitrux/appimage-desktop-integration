#ifndef DEPLOYER_H
#define DEPLOYER_H

#include <QObject>

class Deployer : public QObject
{
    Q_OBJECT
    QString getUserDeploymentPath(const QString &path);

    QString userApplicationsDir;
    QString systemApplicationsDir;

    QString path;
public:
    explicit Deployer(QObject *parent = nullptr);

signals:
    void deploying();
    void successDeploy();
    void failDeploy();

public slots:
    void deployUserwide(const QString &path);
    void deploySystemwide(const QString &path);
    void cancelDeploy();
};

#endif // DEPLOYER_H
