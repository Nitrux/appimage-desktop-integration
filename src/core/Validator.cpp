#include "Validator.h"

#include <appimage/appimage.h>

Validator::Validator(QObject *parent) : QObject(parent)
{

}

void Validator::setAppimage(const QString &path)
{
    Validator::path = path;
}

void Validator::validate()
{
    int res = appimage_get_type(path.toLocal8Bit(), true);
    if (res < 0)
        emit invalidAppimage(path);
    else {
        emit unsignedAppimage(path);
        emit finished();
    }
}
