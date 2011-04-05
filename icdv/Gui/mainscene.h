#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "Layout/Layout.h"

namespace Ui {
    class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = 0);
    ~MainScene();

public slots:
    bool LoadDump();
    bool Exit();
    bool Save();
    bool Authors();
    bool Version();
    bool ZoomIn();
    bool ZoomOut();

private:
    LGraph * m_graph;
    bool Draw();
    QGraphicsScene * view;
    Ui::MainScene *ui;
};

#endif // MAINSCENE_H
