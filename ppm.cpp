#include "ppm.h"
#include "QFile"
#include "QRegularExpression"

PPM::PPM() {}

QImage PPM::read(QString filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return QImage();;
    QByteArray byte_data = file.readAll();

    // check format
    if (byte_data[0] == 'P' && byte_data[1] == '3') {
        qDebug() << "P3 format";
    } else {
        qDebug() << "Not P3 format";
        return QImage();
    }

    // remove comments
    QList<QByteArray> lines = byte_data.split('\n');
    qDebug() << lines.takeFirst(); // pop format, dont care for now
    QList<QByteArray> Ssize = lines.takeFirst().split(' ');
    const int width = Ssize[0].toInt();
    const int height = Ssize[1].toInt();

    int max = lines.takeFirst().toInt();

    QList<QByteArray> real_data = lines.join(' ').split(' ');
    uchar* data = new uchar[height * width * 4]();
    // iterate over data and collect 3 bytes into one pixel
    int index = 0;
    uchar buf[4] = {0, 0, 0, 255};
    for (int i = 0; i < height * width * 3; ++i) {
        QByteArray v = real_data[i];

        for (int nth = 0; nth < 3; ++nth) {
            while (v == ' ' || v == '\n') {
                v = real_data[++i];
            }
            buf[2 - nth] = (uchar)v.toInt();
        }
        for (int j = 0; j < 4; ++j) {
            data[index] = buf[j];
            index++;
        }
        qDebug() << buf[0] << buf[1] << buf[2];

        // buf[2 - index % 3] = (uchar)v.toInt();
        // index++;

        // if (index % 3 == 0) {
        //     int start = index - 3;
        //     for (int j = 0; j < 3; ++j) {
        //         data[start + j] = buf[j];
        //     }
        //     qDebug() << buf[0] << buf[1] << buf[2];
        //     data[start + 3] = 255;
        //     index++;
        // }
    }

    //for (int i = 0; i < width * height * 3; ++i) {
    //    data[i] = (data[i] * 255 / max);
    //}
    qDebug() << "finished kinda";

    // QImage* canvas = new QImage(data, width, height, width * 4, QImage::Format_ARGB32);
    QImage canvas = QImage(data, width, height, width * 4, QImage::Format_ARGB32);
    return canvas;
}
