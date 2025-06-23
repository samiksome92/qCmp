#include <backend.h>
#include <utils.h>

#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QList>
#include <QObject>
#include <QPair>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QRegularExpression>
#include <QString>
#include <QStringList>
#include <QStyleHints>
#include <QtLogging>

int main(int argc, char *argv[]) {
    qSetMessagePattern("[%{if-info}INFO%{endif}%{if-warning}WARN%{endif}%{if-fatal}FATAL%{endif}] %{message}");

    QGuiApplication app(argc, argv);
    app.setApplicationName("qCmp");
    app.setApplicationVersion("1.0.0");
    app.styleHints()->setColorScheme(Qt::ColorScheme::Dark);

    // Parse arguments.
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("dirs", "Directories to search.", "dirs...");
    parser.addOption({{"1", "pattern1"}, "Search pattern for first set.", "regex1"});
    parser.addOption({{"2", "pattern2"}, "Search pattern for second set.", "regex2"});
    parser.addOption({{"r", "rows"}, "Number of rows.", "n", "1"});
    parser.addOption({{"c", "cols"}, "Number of columns.", "m", "1"});
    parser.addOption({{"t", "timer"}, "Timer interval in seconds.", "s", "0.5"});
    parser.process(app);

    // Verify/sanitize arguments.
    QStringList args = parser.positionalArguments();
    if (args.length() < 1) qFatal() << "At least one directory must be provided.";
    if (!parser.isSet("pattern1") || !parser.isSet("pattern2")) qFatal() << "Both search patterns must be provided.";

    QRegularExpression re1(parser.value("pattern1"));
    QRegularExpression re2(parser.value("pattern2"));
    if (!re1.isValid() || re1.captureCount() < 1) qFatal() << "Pattern 1 is invalid.";
    if (!re2.isValid() || re2.captureCount() < 1) qFatal() << "Pattern 2 is invalid.";

    int rows = parser.value("rows").toInt();
    int cols = parser.value("cols").toInt();
    double timer = parser.value("timer").toDouble();

    // Find pairs.
    QStringList files;
    for (const QString &arg : parser.positionalArguments()) {
        QDir dir(arg);
        if (!dir.exists()) {
            qWarning().noquote() << QString("%1 does not exist.").arg(dir.path());
            continue;
        }
        files << listFiles(dir);
    }
    QList<QPair<QString, QString>> pairs = matchPairs(files, re1, re2);
    if (pairs.empty()) {
        qInfo() << "No matching image pairs found.";
        exit(0);
    }

    // Register font, initialize backend and execute app.
    if (QFontDatabase::addApplicationFont(":/fonts/IBMPlexSans-VariableFont_wdth,wght.ttf") < 0)
        qWarning() << "Failed to find font.";

    BackEnd backend(pairs, rows, cols, timer);
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("backend", &backend);
    engine.loadFromModule("qCmp", "Main");

    return app.exec();
}
