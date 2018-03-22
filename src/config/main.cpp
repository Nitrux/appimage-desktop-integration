#include <QApplication>
#include <QDesktopWidget>
#include <QCommandLineParser>
#include <QProcess>
#include <UserAppsMonitorConfig.h>
#include <QDebug>

#include "GreeterDialog.h"


QCommandLineParser *createCommandLineParser(const QCoreApplication &app);

void startMonitor();

void openAppimage(const QString &target);

void showConfig(GreeterDialog *dialog);

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QApplication::setApplicationName("appimage-desktop-integration-tool");

    QCommandLineParser *parser = createCommandLineParser(app);
    const QStringList args = parser->positionalArguments();

    if (parser->isSet("monitor")) {
        startMonitor();
        return 0;
    } else if (parser->isSet("open")) {
        QString path = parser->value("open");
        openAppimage(path);

        return 0;
    } else {
        GreeterDialog *dialog;
        showConfig(dialog);
        return app.exec();
    }
}

void showConfig(GreeterDialog *dialog) {
    dialog = new GreeterDialog();
    dialog->show();
}

void openAppimage(const QString &target) {
    auto appimage = qgetenv("APPDIR");
    auto firstRunPath = appimage + "/usr/bin/appimage_first_run";

    QProcess::startDetached(firstRunPath, {target});
}

void startMonitor() {
    if (!UserAppsMonitorConfig::isRunning())
        UserAppsMonitorConfig::start();
}

QCommandLineParser *createCommandLineParser(const QCoreApplication &app) {
    QCommandLineParser *parser = new QCommandLineParser();
    parser->setApplicationDescription(QObject::tr("AppImage Desktop Integration tool"));
    parser->addHelpOption();

    parser->addOption({{"c", "config"}, "Show configuration dialog"});
    parser->addOption({{"m", "monitor"}, "Watch appimge files at $HOME/Applications and /opt/Applications"});
    parser->addOption({{"o", "open"}, "Open the appimage file at <path>.", "path"});


    parser->process(app);
    return parser;
}
