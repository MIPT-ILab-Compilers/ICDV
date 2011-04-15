#include <QFileDialog>
#include <QString>
#include <QResizeEvent>
#include <QSize>
#include <QImage>

#include <map>

#include "Gui/mainscene.h"
#include "Gui/GNode.h"
#include "Gui/GEdge.h"
#include "ui_mainscene.h"
#include "DumpParser.h"
#include <stdio.h>
#define node_heigh 10
#define node_width 10

#define default_view_height 600
#define default_view_width 460

#define default_view_x 10
#define default_view_y 10

MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene) {
    ui->setupUi(this);
    m_graph = new LGraph();
    m_scene = new QGraphicsScene(ui->CFGView->sceneRect());
}

MainScene::~MainScene() {
    if (m_graph)
        m_graph->Destroy();

    if (m_scene)
        delete m_scene;
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
                //QDir::currentPath(),
                "/Users",
                tr("Dump files (*.txt);;All files (*.*)") );

    if (filename.isNull()) {
        return false;
     }

    // Initialization of DumpProp and CFGView.
    ParseDump(m_graph, filename);

    Draw();
    return true;
}

bool MainScene::Save() {
    if (m_scene == NULL)
        return false;
    QString filename = QFileDialog::getSaveFileName(
                this,
                tr("Save image as"),
                //QDir::currentPath(),
                "/Users",
                tr("All files (*.*)") );

    if (filename.isNull()) {
        return false;
     }

    QImage image(m_scene->width(), m_scene->height(),
                 QImage::Format_ARGB32_Premultiplied);
    image.fill(0xFFFFFF);
    QPainter painter(&image);
    m_scene->render(&painter);
    image.save(filename);
    return true;
}

bool MainScene::Authors() {
    return true;
}

bool MainScene::Version() {
    return true;
}

bool MainScene::Exit() {
    delete this;
    return true;
}

bool MainScene::Resize(const QSize &iconSize) {
    ui->CFGView->resize(iconSize);
    return true;
}

// TODO(Lega): it needs to be tested on real dump.
// TODO(Lega): add nodes information displaying.
/*
void MainScene::resizeEvent(QResizeEvent * resize) {
    ui->CFGView->setGeometry(QRect(default_view_x,
                                   default_view_y,
                                   resize->width(),
                                   resize->height()));
}
*/
bool MainScene::SetGraph(LGraph * graph_to_set) {
    if (m_scene == NULL)
        return false;

    map<pNode, GNode *> nodes_map;
    GNode * buf_node;
    GEdge * buf_edge;
    for (list<pNode>::iterator node_iter = graph_to_set->nodes_list()->begin();
         node_iter != graph_to_set->nodes_list()->end();
         node_iter++)
    {
        buf_node = new GNode(ui->CFGView);
        nodes_map[*node_iter] = buf_node;
        m_scene->addItem(buf_node);
        buf_node->setPos((*node_iter)->x, (*node_iter)->y);
        if (((pLNode)(*node_iter))->IsDummy())
            buf_node->setVisible(false);
    }

    map<pEdge, bool> added_edges;
    for (list<pNode>::iterator node_iter = graph_to_set->nodes_list()->begin();
         node_iter != graph_to_set->nodes_list()->end();
         node_iter++)
    {
        for (list<pEdge>::iterator edge_iter = (*node_iter)->in_edges_list()->begin();
             edge_iter != (*node_iter)->in_edges_list()->end();
             edge_iter++)
        {
            if (added_edges.find((*edge_iter)) == added_edges.end())
            {
                added_edges[*edge_iter] = true;

                if (((pLEdge)(*edge_iter))->IsReverse() == false)
                    buf_edge = new GEdge(nodes_map[(*edge_iter)->to()],
                                         nodes_map[(*edge_iter)->from()]);
                else
                    buf_edge = new GEdge(nodes_map[(*edge_iter)->from()],
                                         nodes_map[(*edge_iter)->to()]);

                if (((pLNode)((*edge_iter)->to()))->IsDummy() ||
                        ((pLNode)((*edge_iter)->from()))->IsDummy())
                    buf_edge->setVisible(false);
                m_scene->addItem(buf_edge);
            }
        }
    }
    return true;
}

bool MainScene::Draw() {
    ui->statusbar->showMessage("Draw started");
    if (ui->CFGView == NULL) {
        ui->statusbar->showMessage("Cannot init QGraphicsView!\n");
        return false;
    }

    if (m_graph == NULL) {
        ui->statusbar->showMessage("Cannot display the dump");
        return false;
    }

    m_graph->Layout();

    if (SetGraph(m_graph)) {
        ui->CFGView->setScene(m_scene);
        ui->CFGView->show();
    } else {
        return false;
    }

    return true;
}
