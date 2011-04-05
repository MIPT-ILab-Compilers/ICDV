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
