#include <QFileDialog>
#include <QString>

#include "mainscene.h"
#include "ui_mainscene.h"

MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);
}

MainScene::~MainScene()
{
    delete ui;
}

bool MainScene::ZoomIn() {
    return true;
}

bool MainScene::ZoomOut() {
    return true;
}

bool MainScene::LoadDump() {
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open a dump"),
                QDir::currentPath(),
                tr("Dump files (*.hz);;All files (*.*)") );
    if (filename.isNull()) {
        return false;
     }
    // Initialization of QGraphicsScene and QGraphicsView;
    // using Graph and Layout.
    // TODO(Lega): add here init of the graph.
    return true;
}

bool MainScene::Save() {
    return true;
}

bool MainScene::Authors() {
    return true;
}

bool MainScene::Version() {
    return true;
}

bool MainScene::Exit() {
    return true;
}

bool MainScene::Draw() {
    return true;
}
