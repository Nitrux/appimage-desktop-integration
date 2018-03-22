//
// Created by alexis on 3/22/18.
//
#include <QProcess>
#include <QDebug>
#include <QtCore/QStandardPaths>
#include <QtCore/QDir>

#include "UserAppsMonitorConfig.h"
#include "FirstRunConfig.h"

bool UserAppsMonitorConfig::isRunning() {
    return getPID() != -1;
}

int UserAppsMonitorConfig::getPID() {
    QProcess ps;
    ps.start("ps -o pid= -C user_apps_monitor");
    ps.closeWriteChannel();
    ps.waitForFinished();

    QString result = ps.readAll().trimmed();
    if (result.isEmpty())
        return -1;
    else
        return result.toInt();
}

void UserAppsMonitorConfig::start() {
    auto appimage = qgetenv("APPDIR");
    auto monitorPath = appimage + "/usr/bin/user_apps_monitor";

    qWarning() << monitorPath;
    QProcess::startDetached(monitorPath);
}

void UserAppsMonitorConfig::stop() {
    int pid = getPID();

    if (pid > 0)
        QProcess::startDetached("/bin/kill", {QString::number(pid, 10)});
}

bool UserAppsMonitorConfig::isEnabled() {
    bool xdgAutoStart = QFile::exists(getXDGPath());
    bool configAutoStart = QFile::exists(getDesktopFilePath());

    return xdgAutoStart != configAutoStart;
}

void UserAppsMonitorConfig::enable() {
    auto appimage = qgetenv("APPIMAGE");
    QString filePath = getDesktopFilePath();

    QString xdgPath = getXDGPath();

    if (QFile::exists(xdgPath))
        QFile::remove(filePath);
    else
        createDesktopFile(appimage, filePath);
}

void UserAppsMonitorConfig::createDesktopFile(const QByteArray &appimage, const QString &filePath)  {
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write("[Desktop Entry]\n"
                           "Type=Application\n"
                           "Icon=appimage\n"
                           "Categories=System;\n"
                           "Name=Appimage User Applications Monitor\n"
                           "Comment=Monitor appimage files in HOME/Applications and /opt/applications to create or "
                           "remove proper desktop integration files.\n"
                           "NoDisplay=true\n");
        file.write("Exec=" + appimage + " --monitor\n"
                "TryExec=" + appimage + "\n");

        file.close();
    }
}

QString UserAppsMonitorConfig::getDesktopFilePath()  {
    auto filePath = QDir::homePath() + "/.config/autostart/" + getDesktopFileName();
    return filePath;
}

void UserAppsMonitorConfig::disable() {
    const auto path = getDesktopFilePath();
    QString xdgPath = getXDGPath();

    if (QFile::exists(xdgPath))
        createDesktopFile("", path);
    else
        QFile::remove(getDesktopFilePath());
}

QString UserAppsMonitorConfig::getXDGPath()  {
    const auto xdgPath = "/etc/xdg/autostart/" + getDesktopFileName();
    return xdgPath;
}

const QString
UserAppsMonitorConfig::getDesktopFileName() { return "org.appimage.desktop-integration-apps-dir-monitor.desktop"; }



