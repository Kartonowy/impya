#include "mainwindow.h"

#include <QApplication>
// #include "Portable_anymap.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Portable_Anymap* map = new Portable_Anymap();
    // map->loadFile();
    return a.exec();
}
