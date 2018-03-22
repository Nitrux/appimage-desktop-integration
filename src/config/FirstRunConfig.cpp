//
// Created by alexis on 3/21/18.
//
#include <QDir>
#include <QStandardPaths>
#include <QDebug>
#include <QSettings>
#include "FirstRunConfig.h"

bool FirstRunConfig::isEnabled() {
    const auto configPaths = QStandardPaths::standardLocations(QStandardPaths::ApplicationsLocation);
    for (const QString applicationsDir: configPaths) {
        QDir dir(applicationsDir);
        auto entries = dir.entryList({"org.appimage.desktop-integration-first-run.desktop"});
        if (!entries.isEmpty())
            return true;
    }

    return false;
}

void FirstRunConfig::enable() {
    auto appimage = qgetenv("APPIMAGE");
    QString filePath = getDesktopFilePath();

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write("[Desktop Entry]\n"
                           "Type=Application\n"
                           "Icon=appimage\n"
                           "MimeType=application/x-iso9660-appimage;application/vnd.appimage;\n"
                           "Categories=System;\n"
                           "Name=Appimage First Run Utility\n"
                           "Comment=First run utility to verify and deploy desktop integration files for Appimages.\n"
                           "NoDisplay=true\n");
        file.write("Exec=" + appimage + " --open %F\n"
                "TryExec=" + appimage + "\n");

        file.close();
    }
}

QString FirstRunConfig::getDesktopFilePath() const {
    auto filePath = QDir::homePath() + "/.local/share/applications/org.appimage.desktop-integration-first-run.desktop";
    return filePath;
}

void FirstRunConfig::disable() {
    QFile::remove(getDesktopFilePath());
}
