#include "filedialog.h"
#include "QFileDialog"

FileDialog::FileDialog() {}

void FileDialog::open(QWidget * parent) {
    QString filename = QFileDialog::getOpenFileName(parent,
        QFileDialog::tr("Open Text file"), "", QFileDialog::tr("All files (*)"));

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << line;
    }
}
