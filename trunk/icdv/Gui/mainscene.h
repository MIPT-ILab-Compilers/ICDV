#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QSize>
#include <QResizeEvent>

#include "../Layout/Layout.h"

/// Class that's an implementation of gui.
/**
 * LoadDump() calls QFileDialog and Draw()
 * Draw() draws graph into view and displays
 *  it into ui->CFGView
 * Save() saves curent graph as an image file.
 * Authors() shows authors of this program:).
 * Version() shows version of this program.
 * ZoomIn() zooms in curent image.
 * ZoomOut() zooms out curent image.
 */

namespace Ui {
    class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

friend class GraphWidget;
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
    bool Resize(const QSize &iconSize);


protected:
    bool SetGraph(LGraph * graph_to_set);

    // Representation of call graph.
    LGraph * m_graph;

    QGraphicsScene * m_scene;
protected slots:
    // void MainScene::resizeEvent(QResizeEvent * resize).
    // void DrawToScene(LGraph * graph);

private:
    // This function draws m_graph into
    // view (see below) and puts it into
    // CFGView (look into mainscene.ui).
    bool Draw();

    // GraphWidget. It provides graph view.
    //GraphWidget * g_widget;

    // ui is a main window gui.
    Ui::MainScene *ui;
};

#endif // MAINSCENE_H
