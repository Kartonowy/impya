#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QObject>

class FileDialog
{
public:
    FileDialog();
    static QString open(QWidget*);
};

#endif // FILEDIALOG_H
