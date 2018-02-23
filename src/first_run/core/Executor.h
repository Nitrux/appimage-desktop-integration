#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <QObject>

class Executor : public QObject
{
    Q_OBJECT
public:
    explicit Executor(QObject *parent = nullptr);

signals:
    void executed();
    void failure();

public slots:
    void execute(const QString &path);
    void executeIsolated(const QString &path);

private:
    void startDetached(const QString &path, QStringList arguments = {});
    QString getParentDirPath(const QString &path);
};

#endif // EXECUTOR_H
