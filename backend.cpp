#include <backend.h>

#include <QList>
#include <QObject>
#include <QPair>
#include <QString>
#include <QVariantMap>
#include <QtMinMax>

const int BackEnd::MAX_ROWS = 3;
const int BackEnd::MAX_COLS = 3;
const double BackEnd::MIN_TIME = 0.1;
const double BackEnd::MAX_TIME = 5.0;

BackEnd::BackEnd(const QList<QPair<QString, QString>>& imgPairs, int rows, int cols, double timer) : QObject() {
    for (const QPair<QString, QString>& pair : imgPairs)
        this->imgPairs.append({{"first", pair.first}, {"second", pair.second}});
    this->rows = qBound(1, rows, MAX_ROWS);
    this->cols = qBound(1, cols, MAX_COLS);
    this->timer = qBound(MIN_TIME, timer, MAX_TIME);

    // Keep removing rows and columns until rows * cols is lesser than or equal to total number of images.
    while (this->rows * this->cols > this->imgPairs.length()) {
        this->rows = qMax(this->rows - 1, 1);
        if (this->rows * this->cols <= this->imgPairs.length()) break;
        this->cols = qMax(this->cols - 1, 1);
    }

    emit imgPairsChanged();
    emit rowsChanged();
    emit colsChanged();
    emit timerChanged();
    emit statusTextChanged();
}

QList<QVariantMap> BackEnd::getImgPairs() const { return imgPairs.sliced(imgIdx, rows * cols); }
int BackEnd::getRows() const { return rows; }
int BackEnd::getCols() const { return cols; }
double BackEnd::getTimer() const { return timer * 1000; }
QString BackEnd::getStatusText() const {
    if (rows * cols == 1)
        return QString("%1 / %2").arg(imgIdx + 1).arg(imgPairs.length());
    else
        return QString("%1-%2 / %3").arg(imgIdx + 1).arg(imgIdx + rows * cols).arg(imgPairs.length());
}

void BackEnd::prev() {
    if (imgIdx == 0) return;

    imgIdx = qMax(imgIdx - rows * cols, 0);
    emit imgPairsChanged();
    emit statusTextChanged();
}

void BackEnd::next() {
    if (imgIdx == imgPairs.length() - rows * cols) return;

    imgIdx = qMin(imgIdx + rows * cols, imgPairs.length() - rows * cols);
    emit imgPairsChanged();
    emit statusTextChanged();
}

void BackEnd::goTo(int n) {
    if (imgIdx == n - 1) return;

    imgIdx = qBound(0, n - 1, imgPairs.length() - rows * cols);
    emit imgPairsChanged();
    emit statusTextChanged();
}

void BackEnd::addRow() {
    if (rows == MAX_ROWS) return;
    if ((rows + 1) * cols > imgPairs.length()) return;

    rows += 1;
    imgIdx = qMin(imgIdx, imgPairs.length() - rows * cols);
    emit imgPairsChanged();
    emit rowsChanged();
    emit statusTextChanged();
}

void BackEnd::removeRow() {
    if (rows == 1) return;

    rows -= 1;
    emit rowsChanged();
    emit imgPairsChanged();
    emit statusTextChanged();
}

void BackEnd::addCol() {
    if (cols == MAX_COLS) return;
    if (rows * (cols + 1) > imgPairs.length()) return;

    cols += 1;
    imgIdx = qMin(imgIdx, imgPairs.length() - rows * cols);
    emit imgPairsChanged();
    emit colsChanged();
    emit statusTextChanged();
}

void BackEnd::removeCol() {
    if (cols == 1) return;

    cols -= 1;
    emit colsChanged();
    emit imgPairsChanged();
    emit statusTextChanged();
}
