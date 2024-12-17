#include "filedialog.h"
#include "QFileDialog"

FileDialog::FileDialog() {}

QString FileDialog::open(QWidget * parent) {
    QString filename = QFileDialog::getOpenFileName(parent,
        QFileDialog::tr("Open Text file"), "", QFileDialog::tr("All files (*)"));
    return filename;
}
