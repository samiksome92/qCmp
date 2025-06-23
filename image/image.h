#ifndef IMAGE_H
#define IMAGE_H

#include <QtQmlIntegration/qqmlintegration.h>

#include <QImage>
#include <QObject>
#include <QPainter>
#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QString>

/**
 * Custom `QtQuick` object to display an image.
 *
 * The standard `Image` object does not downsample high resolution images smoothly. This class uses avoids that and
 * smoothly downsamples and upsamples the original image. Also has a radius property which can be used to round the
 * corners of the displayed image.
 */
class Image : public QQuickPaintedItem {
    Q_OBJECT

    Q_PROPERTY(QString source READ getSource WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(int padding READ getPadding WRITE setPadding NOTIFY paddingChanged)
    Q_PROPERTY(int radius READ getRadius WRITE setRadius NOTIFY radiusChanged)

    QML_ELEMENT

   public:
    /**
     * Constructor.
     *
     * @param parent Parent item.
     */
    Image(QQuickItem *parent = nullptr);

    /**
     * Returns the image source.
     *
     * @returns Image source.
     */
    QString getSource() const;
    /**
     * Sets the image source.
     *
     * @param source Image source.
     */
    void setSource(const QString &source);
    /**
     * Returns the padding used.
     *
     * @returns Image padding.
     */
    int getPadding() const;
    /**
     * Sets the padding to be used.
     *
     * @param padding Image padding.
     */
    void setPadding(int padding);
    /**
     * Returns radius of image rectangle.
     *
     * @returns Radius.
     */
    int getRadius() const;
    /**
     * Sets the image radius.
     *
     * Note that the radius is applied on the image not the object itself.
     *
     * @param radius Radius.
     */
    void setRadius(int radius);
    /**
     * Paints the object using `painter`.
     *
     * @param painter Painter to use.
     */
    void paint(QPainter *painter);

   signals:
    void sourceChanged() const;
    void paddingChanged() const;
    void radiusChanged();

   private:
    QString source{QString()};
    int padding{0};
    int radius{0};
    QImage image{QImage()};
    QImage scaledImage{QImage()};
};

#endif  // IMAGE_H
