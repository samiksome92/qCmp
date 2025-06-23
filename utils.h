#ifndef UTILS_H
#define UTILS_H

#include <QDir>
#include <QList>
#include <QPair>
#include <QRegularExpression>
#include <QString>
#include <QStringList>

/**
 * Retrieves a list of all files present within provided directory.
 *
 * Searches the directory recursively.
 *
 * @param dir Directory to search.
 *
 * @returns List of all files found.
 */
QStringList listFiles(const QDir &dir);

/**
 * Given a list of files and two regular expressions, returns pairs of files which match the regular expressions and
 * share the same basename.
 *
 * The basename is simply a concatenation of all captured groups in the regex match.
 *
 * @param files List of files.
 * @param re1 First regular expression.
 * @param re2 Second regular expression.
 *
 * @returns Sorted list of matched file pairs.
 */
QList<QPair<QString, QString>> matchPairs(const QStringList &files, const QRegularExpression &re1,
                                          const QRegularExpression &re2);

#endif  // UTILS_H
