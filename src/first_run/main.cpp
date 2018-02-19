#include <QCoreApplication>
#include <QCommandLineParser>

#include <appimage/appimage.h>

int main (int argc, char **argv) {
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("appimage-first-run");

    QCommandLineParser parser;
    parser.setApplicationDescription("AppImage verification and deployment utility");
    parser.addHelpOption();

    parser.addPositionalArgument("appimage", "The AppImage file to execute.");
    parser.process(app);

    return 0;
}