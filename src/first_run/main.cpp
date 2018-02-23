#include <QApplication>
#include <QDesktopWidget>
#include <QCommandLineParser>

#include "core/Validator.h"
#include "core/Deployer.h"
#include "core/Executor.h"

#include "gui/UiController.h"


QCommandLineParser *createCommandLineParser(const QCoreApplication &app);


int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QApplication::setApplicationName("appimage-first-run");

    QCommandLineParser *parser = createCommandLineParser(app);
    const QStringList args = parser->positionalArguments();

    Validator validator;
    Deployer deployer;
    Executor executor;

    UiController controller;

    if (!args.isEmpty()) {
        const QString target = args.first();

        validator.setAppimage(target);

        controller.setValidator(&validator);
        controller.setDeployer(&deployer);
        controller.setExecutor(&executor);

        controller.exec();
    } else
        parser->showHelp(1);

    delete parser;
    return app.exec();
}

QCommandLineParser *createCommandLineParser(const QCoreApplication &app) {
    QCommandLineParser *parser = new QCommandLineParser();
    parser->setApplicationDescription(QObject::tr("AppImage verification and deployment utility"));
    parser->addHelpOption();

    parser->addPositionalArgument("appimage", QObject::tr("The AppImage file to execute."));
    parser->process(app);
    return parser;
}
