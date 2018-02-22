#include <QApplication>
#include <QDesktopWidget>
#include <QCommandLineParser>

#include "FirstRun.h"
#include "FirstRunUiController.h"

QCommandLineParser *createCommandLineParser(const QCoreApplication &app);


int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QApplication::setApplicationName("appimage-first-run");

    QCommandLineParser *parser = createCommandLineParser(app);
    const QStringList args = parser->positionalArguments();

    FirstRunUiController *controller = nullptr;
    FirstRun * firstRun = nullptr;
    if (!args.isEmpty()) {
        const QString target = args.first();

        controller = new FirstRunUiController();
        firstRun = new FirstRun(target);

        QObject::connect(firstRun, &FirstRun::canceled, controller, &FirstRunUiController::close);
        QObject::connect(firstRun, &FirstRun::completed, controller, &FirstRunUiController::close);

        QObject::connect(firstRun, &FirstRun::opening, controller, &FirstRunUiController::showOpeningDialog);
        QObject::connect(firstRun, &FirstRun::unrecognizedAppimageFormat, controller, &FirstRunUiController::showUnknownFileDialog);
        QObject::connect(firstRun, &FirstRun::noSignature, controller, &FirstRunUiController::showNoSignatureDialog);
        QObject::connect(controller, &FirstRunUiController::cancelRequested, firstRun, &FirstRun::cancel);

        QObject::connect(controller, &FirstRunUiController::run, firstRun, &FirstRun::run);
        QObject::connect(controller, &FirstRunUiController::runIsolated, firstRun, &FirstRun::runIsolated);
        QObject::connect(controller, &FirstRunUiController::deploy, firstRun, &FirstRun::deploy);
        QObject::connect(controller, &FirstRunUiController::deploySystemWide, firstRun, &FirstRun::deploySystemWide);


        QObject::connect(firstRun, &FirstRun::deployStarted, controller, &FirstRunUiController::showDeployProgress);
        QObject::connect(firstRun, &FirstRun::deployCompleted, controller, &FirstRunUiController::showDeployCompleteDialog);
        QObject::connect(firstRun, &FirstRun::deployError, controller, &FirstRunUiController::showDeployErrorDialog);

        firstRun->verify();
    } else
        parser->showHelp(1);

    delete parser;
    return app.exec();
}

QCommandLineParser *createCommandLineParser(const QCoreApplication &app) {
    QCommandLineParser *parser = new QCommandLineParser();
    parser->setApplicationDescription("AppImage verification and deployment utility");
    parser->addHelpOption();

    parser->addPositionalArgument("appimage", "The AppImage file to execute.");
    parser->process(app);
    return parser;
}
