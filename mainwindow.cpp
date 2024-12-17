#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QFile"
#include "QLabel"
#include "QVBoxLayout"
#include "filedialog.h"
#include "QRandomGenerator"
#include "anymap.h"
#include "ppm.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #181818;");
    menuBar()->setStyleSheet("background-color: #6a1e55;");
    QWidget* widget = new QWidget;
    setCentralWidget(widget);



    QWidget* filler = new QWidget;
    filler->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setContentsMargins(5, 5, 5, 5);
    layout->addWidget(filler);
    this->layout = layout;
    createCanvas();
    widget->setLayout(layout);

    createMenus();

    setWindowTitle(tr("Gimpowo kolory"));
    setMinimumSize(160, 160);
    resize(480, 320);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::createMenus() {
    QAction *openact = new QAction(tr("Open file"));
    openact->setShortcut(QKeySequence::New);
    connect(openact, &QAction::triggered, this, [=](){
        PPM* ppm = new PPM();
        QString filename = FileDialog::open(this);
        qDebug() << filename;
        QImage canvas = ppm->read(filename);
        QLabel* parent = this->findChild<QLabel*>();
        parent->setPixmap(QPixmap::fromImage(canvas));
        parent->show();

    });


    QAction *saveact = new QAction(tr("Save to file"));

    QMenu *filebar = menuBar()->addMenu(tr("&File"));
    filebar->addAction(openact);
    filebar->addAction(saveact);


    menuBar()->addMenu(filebar);
}

void MainWindow::createCanvas() {
    QImage canvas = PPM::read("C:/users/somewhere/Documents/impya/examples/miku.ppm");
    QLabel* label = new QLabel(this);
    label->setPixmap(QPixmap::fromImage(canvas));
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->layout->addWidget(label);
    label->show();
}
