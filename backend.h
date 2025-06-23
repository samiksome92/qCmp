#ifndef BACKEND_H
#define BACKEND_H

#include <QList>
#include <QObject>
#include <QPair>
#include <QString>
#include <QVariantMap>

/**
 * Qt object to handle any non-UI related tasks.
 *
 * Methods and properties in this class are exposed to the UI as a context object. This class handles setting new
 * images, adding and removing rows & columns as well exposing all related properties that the UI can bind to.
 */
class BackEnd : public QObject {
    Q_OBJECT

    Q_PROPERTY(QList<QVariantMap> imgPairs READ getImgPairs NOTIFY imgPairsChanged)
    Q_PROPERTY(int rows READ getRows NOTIFY rowsChanged)
    Q_PROPERTY(int cols READ getCols NOTIFY colsChanged)
    Q_PROPERTY(double timer READ getTimer NOTIFY timerChanged)
    Q_PROPERTY(QString statusText READ getStatusText NOTIFY statusTextChanged)

   public:
    /**
     * Constructor.
     *
     * @param imgPairs List of image pairs to display. Cannot be empty.
     * @param rows Number of initial rows.
     * @param cols Number of initial columns.
     * @param timer Timer interval in seconds.
     */
    BackEnd(const QList<QPair<QString, QString>> &imgPairs, int rows, int cols, double timer);

    static const int MAX_ROWS;
    static const int MAX_COLS;
    static const double MIN_TIME;
    static const double MAX_TIME;

    /**
     * Returns current list of image pairs to be displayed.
     *
     * @returns List of pairs.
     */
    QList<QVariantMap> getImgPairs() const;
    /**
     * Returns the number of rows.
     *
     * @returns Number of rows.
     */
    int getRows() const;
    /**
     * Returns the number of columns.
     *
     * @returns Number of columns.
     */
    int getCols() const;
    /**
     * Returns the timer interval in milliseconds.
     *
     * @returns Timer interval
     */
    double getTimer() const;
    /**
     * Returns status text to display.
     *
     * @returns Status text.
     */
    QString getStatusText() const;
    /** Shows the previous set of images. */
    Q_INVOKABLE void prev();
    /** Shows the next set of images. */
    Q_INVOKABLE void next();
    /**
     * Sets the first image in the set to `n`th image.
     *
     * @param n Index of image.
     */
    Q_INVOKABLE void goTo(int n);
    /** Adds a row. */
    Q_INVOKABLE void addRow();
    /** Removes a row. */
    Q_INVOKABLE void removeRow();
    /** Adds a column. */
    Q_INVOKABLE void addCol();
    /** Removes a column. */
    Q_INVOKABLE void removeCol();

   signals:
    void imgPairsChanged() const;
    void rowsChanged() const;
    void colsChanged() const;
    void timerChanged() const;
    void statusTextChanged() const;

   private:
    QList<QVariantMap> imgPairs{QList<QVariantMap>()};
    int rows{1};
    int cols{1};
    double timer{MIN_TIME};
    int imgIdx{0};
};

#endif  // BACKEND_H
