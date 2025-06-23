#include <utils.h>

#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QList>
#include <QMap>
#include <QPair>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QString>
#include <QStringList>
#include <algorithm>

QStringList listFiles(const QDir &dir) {
    QStringList files;
    QDirIterator it(dir.path(), QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        files.append(it.filePath());
    }

    return files;
}

QString basename(const QRegularExpressionMatch &match) {
    QString basename;
    for (const QString &text : match.capturedTexts().sliced(1)) basename += text;

    return basename;
}

QList<QPair<QString, QString>> matchPairs(const QStringList &files, const QRegularExpression &re1,
                                          const QRegularExpression &re2) {
    // Find matches and store a map of basename to file name.
    QMap<QString, QString> matches1, matches2;
    for (const QString &file : files) {
        QFileInfo fi(file);
        QString fileNoExt = fi.dir().filePath(fi.completeBaseName());

        QRegularExpressionMatch match1 = re1.match(fileNoExt);
        if (match1.hasMatch()) {
            matches1[basename(match1)] = file;
            continue;
        }

        QRegularExpressionMatch match2 = re2.match(fileNoExt);
        if (match2.hasMatch()) matches2[basename(match2)] = file;
    }

    // Create pairs from matches sharing the same basename.
    QList<QPair<QString, QString>> pairs;
    for (const QString &basename : matches1.keys()) {
        if (matches2.contains(basename)) {
            pairs.append({matches1[basename], matches2[basename]});
        }
    }
    std::sort(pairs.begin(), pairs.end());

    return pairs;
}
