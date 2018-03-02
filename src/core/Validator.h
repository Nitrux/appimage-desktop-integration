#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QObject>

#include <appimage/appimage.h>

class Validator : public QObject
{
    Q_OBJECT
    QString path;
public:
    explicit Validator(QObject *parent = nullptr);
    void setAppimage(const QString &path);

signals:
    void finished();
    void unsignedAppimage(const QString &path);
    void invalidAppimage(const QString &path);

public slots:
    void validate();
};

#endif // VALIDATOR_H
