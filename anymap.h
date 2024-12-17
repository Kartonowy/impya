#ifndef ANYMAP_H
#define ANYMAP_H

#include <QFile>


enum Anymap_FILETYPE { P1, P2, P3, P4, P5, P6 };
class Anymap
{
public:
    Anymap_FILETYPE ft;
    int width;
    int height;
    int* content;
    Anymap(Anymap_FILETYPE, int, int, int*);
    Anymap(QFile);
    static QImage P1(int, int);
    static QImage P2(int, int);
    static QImage P3(int, int);
};

#endif // ANYMAP_H
