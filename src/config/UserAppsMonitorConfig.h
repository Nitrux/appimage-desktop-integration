//
// Created by alexis on 3/22/18.
//

#ifndef APPPIMAGE_DESKTOP_INTEGRATION_USERAPPSMONITORCONFIG_H
#define APPPIMAGE_DESKTOP_INTEGRATION_USERAPPSMONITORCONFIG_H


class UserAppsMonitorConfig {
public:
    static bool isRunning();
    static int getPID();

    static void start();
    static void stop();



    static bool isEnabled();

    static void enable();

    static QString getDesktopFilePath() ;

    static void disable();

    static const QString getDesktopFileName();

    static void createDesktopFile(const QByteArray &appimage, const QString &filePath) ;

    static QString getXDGPath() ;
};


#endif //APPPIMAGE_DESKTOP_INTEGRATION_USERAPPSMONITORCONFIG_H
