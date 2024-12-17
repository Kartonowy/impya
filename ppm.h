#ifndef PPM_H
#define PPM_H

#include <QWidget>

class PPM
{
public:
    PPM(); // portable anymap format consisting of 3 bytes each pixel
    int width;
    int height;
    int* content;
    static QImage read(QString);
};

#endif // PPM_H
