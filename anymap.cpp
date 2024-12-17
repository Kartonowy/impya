#include "anymap.h"
#include "QFile"
#include "QTextStream"
#include "QDebug"
#include "QImage"
#include "QRegularExpression"

Anymap::Anymap(Anymap_FILETYPE ft, int width, int height, int* content_ptr) {
    this->ft = ft;
    this->width = width;
    this->height = height;
    this->content = content_ptr;
}

Anymap::Anymap(QFile file) {
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << line;
    }
}

QImage Anymap::P1(int winWidth, int winHeight) {
    QString Simage = "P1\n# komentarz\n6 10\n0 0 0 0 1 0\n0 0 0 0 1 0\n0 0 0 0 1 0\n0 0 0 0 1 0\n0 0 0 0 1 0\n0 0 0 0 1 0\n1 0 0 0 1 0\n0 1 1 1 0 0\n0 0 0 0 0 0\n0 0 0 0 0 0";
    QList<QString> lines = Simage.split("\n");
    lines.pop_front(); // pop format, dont care for now
    lines.pop_front(); // pop comment, also dont care
    QList<QString> Ssize = lines.takeFirst().split(" ");
    int width = Ssize[0].toInt();
    int height = Ssize[1].toInt();

    qDebug() << "width: " << width << "height: " << height;

    std::string Sdata = lines.join(" ").split(" ").join("").toStdString();
    qDebug() << Sdata;

// #include "QRandomGenerator"
//    QRandomGenerator gen(time(NULL));
    uchar* data = (uchar*)Sdata.c_str();
    for (int i = 0; i < width * height; ++i) {
        data[i] = data[i] - 48;
        if (data[i] == 1) {
            data[i] = 255;
        }
        //data[i] = gen.bounded(255);
        qDebug() << data[i];
    }


    // QImage* canvas = new QImage(data, width, height, QImage::Format_Mono);
    QImage canvas = (new QImage(data, width , height , width,  QImage::Format_Grayscale8))
                        ->scaled(winWidth, winHeight, Qt::KeepAspectRatio);
    return canvas;
}

QImage Anymap::P2(int winWidth, int winHeight) {
    QString Simage = "P2\n# Shows the word FEEP\n24 7\n15\n0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0\n0  3  3  3  3  0  0  7  7  7  7  0  0 11 11 11 11  0  0 15 15 15 15  0\n0  3  0  0  0  0  0  7  0  0  0  0  0 11  0  0  0  0  0 15  0  0 15  0\n0  3  3  3  0  0  0  7  7  7  0  0  0 11 11 11  0  0  0 15 15 15 15  0\n0  3  0  0  0  0  0  7  0  0  0  0  0 11  0  0  0  0  0 15  0  0  0  0\n0  3  0  0  0  0  0  7  7  7  7  0  0 11 11 11 11  0  0 15  0  0  0  0\n0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0";
    QList<QString> lines = Simage.split("\n");
    lines.pop_front(); // pop format, dont care for now
    lines.pop_front(); // pop comment, also dont care
    QList<QString> Ssize = lines.takeFirst().split(" ");
    const int width = Ssize[0].toInt();
    const int height = Ssize[1].toInt();
    int max = lines.takeFirst().toInt();

    uchar* twoja = new uchar[height * width];
    int index = 0;
    for (int i = 0; i < height; ++i) {
        QStringList splitted = lines[i].split(" ");
        splitted.removeAll(QString(""));
        for (int j = 0; j < width; ++j) {
            twoja[index] = splitted[j].toInt();
            index++;
        }
    }

    for (int i = 0; i < width * height; ++i) {
        twoja[i] = (twoja[i] * 255 / max);
    }

    // QImage* canvas = new QImage(data, width, height, QImage::Format_Mono);
    QImage canvas = (new QImage(twoja, width , height , width,  QImage::Format_Grayscale8))
                        ->scaled(winWidth, winHeight, Qt::KeepAspectRatio);
    return canvas;
}


QImage Anymap::P3(int winWidth, int winHeight) {
    QString Simage = "P3\n# 'P3' means this is a RGB color image in ASCII\n3 2\n255\n255   0   0\n0 255   0\n0   0 255\n255 255   0\n255 255 255\n0   0   0";
    QList<QString> lines = Simage.split("\n");
    lines.pop_front(); // pop format, dont care for now
    lines.pop_front(); // pop comment, also dont care
    qDebug() << lines;
    QList<QString> Ssize = lines.takeFirst().split(" ");
    const int width = Ssize[0].toInt();
    const int height = Ssize[1].toInt();
    qDebug() << "width: " << width << "height: " << height;
    int max = lines.takeFirst().toInt();

    uchar* twoja = new uchar[height * width * 3];
    int index = 0;
    for (int i = 0; i < height * 3; ++i) {
        QStringList splitted = lines[i].split(QRegularExpression("\\s+"));
        uchar buf[4] = {0, 0, 0, 255};
        for (int nth = 0; nth < 3; ++nth) {
            buf[2 - nth] = splitted[nth].toInt();
        }
        for (int j = 0; j < 4; ++j) {
            twoja[index] = buf[j];
            qDebug() << buf[j];
            index++;
        }
    }

    //for (int i = 0; i < width * height * 3; ++i) {
    //    twoja[i] = (twoja[i] * 255 / max);
    //}

    qDebug() << new QImage(twoja, width, height, width,  QImage::Format_RGB32);

    // QImage* canvas = new QImage(data, width, height, QImage::Format_Mono);
    QImage canvas = (new QImage(twoja, width, height, width * 4,  QImage::Format_ARGB32))
                        ->scaled(winWidth, winHeight, Qt::KeepAspectRatio);
    return canvas;

}
