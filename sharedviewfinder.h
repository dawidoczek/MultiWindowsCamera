#ifndef SHAREDVIEWFINDER_H
#define SHAREDVIEWFINDER_H

#include <QAbstractVideoSurface>
#include <QPixmap>

class SharedViewfinder : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    SharedViewfinder();

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;
    bool present(const QVideoFrame &frame);

signals:
    void frameReady(QPixmap);
};

#endif
