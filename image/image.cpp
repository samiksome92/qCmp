#include <image.h>

#include <QImage>
#include <QPainter>
#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QRect>
#include <QString>

Image::Image(QQuickItem *parent) : QQuickPaintedItem(parent) {}

QString Image::getSource() const { return source; }
void Image::setSource(const QString &source) {
    if (this->source == source) return;

    this->source = source;
    image = QImage(source);
    scaledImage = image;
    update(QRect(0, 0, width(), height()));

    emit sourceChanged();
}
int Image::getPadding() const { return padding; }
void Image::setPadding(int padding) {
    if (this->padding == padding) return;

    this->padding = padding;
    update(QRect(0, 0, width(), height()));

    emit paddingChanged();
}
int Image::getRadius() const { return radius; }
void Image::setRadius(int radius) {
    if (this->radius == radius) return;

    this->radius = radius;
    update(QRect(0, 0, width(), height()));

    emit radiusChanged();
}

void Image::paint(QPainter *painter) {
    if (image.isNull()) return;

    painter->setRenderHint(QPainter::Antialiasing);

    int w = image.width();
    int h = image.height();
    double ar = static_cast<double>(w) / h;

    int tW = width() - 2 * padding;
    int tH = height() - 2 * padding;
    double tAr = static_cast<double>(tW) / tH;

    int x = 0;
    int y = 0;
    bool applyMask = false;
    if (ar <= tAr) {
        if (scaledImage.height() != tH) {
            scaledImage = image.scaledToHeight(tH, Qt::SmoothTransformation);
            applyMask = true;
        }
        x = (tW - scaledImage.width()) / 2;
    } else {
        if (scaledImage.width() != tW) {
            scaledImage = image.scaledToWidth(tW, Qt::SmoothTransformation);
            applyMask = true;
        }
        y = (tH - scaledImage.height()) / 2;
    }

    // Only apply radius mask if scaled image has changed and radius is greater than zero.
    if (radius > 0 && applyMask) {
        QImage mask(scaledImage.size(), QImage::Format_Alpha8);
        mask.fill(Qt::transparent);
        QPainter maskPainter(&mask);
        maskPainter.setRenderHint(QPainter::Antialiasing);
        maskPainter.setBrush(Qt::black);
        maskPainter.drawRoundedRect(mask.rect(), radius, radius);
        scaledImage.setAlphaChannel(mask);
    }

    painter->drawImage(x + padding, y + padding, scaledImage);
}
