#include "sharedviewfinder.h"
#include <QtDebug>
SharedViewfinder::SharedViewfinder() : QAbstractVideoSurface(nullptr) {}

QList<QVideoFrame::PixelFormat> SharedViewfinder::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    QList<QVideoFrame::PixelFormat> list;
    if (handleType == QAbstractVideoBuffer::NoHandle)
    {
        list.append(QVideoFrame::Format_RGB32);
    }
     qDebug()<<"start view finder" ;
    return list;

}

bool SharedViewfinder::present(const QVideoFrame &frame)
{
    QVideoFrame copy(frame);
    copy.map(QAbstractVideoBuffer::ReadOnly);
    QImage image(copy.bits(), copy.width(), copy.height(), copy.bytesPerLine(), QImage::Format_RGB32);
    copy.unmap();
//    qDebug()<<"poszloo";
    image = image.mirrored(true, true);
    emit frameReady(QPixmap::fromImage(image));

    return true;
}
