#include <QFileDialog>
#include <QString>
/**
 * @file: mainscene.cpp
 */

#include <QResizeEvent>
#include <QSize>
#include <QImage>

#include <map>

#include "../Gui/mainscene.h"
#include "../Gui/GNode.h"
#include "../Gui/GEdge.h"
#include "ui_mainscene.h"
#include "../DumpParser.h"
#include <stdio.h>
#define node_heigh 10
#define node_width 10

#define default_view_height 600
#define default_view_width 460

#define default_view_x 10
#define default_view_y 10

pLGraph VisTest()
{
        printf("\nLayout test started..\n");

        pLGraph g = new LGraph();

        int len = 10;
        pLNode *p = new pLNode[len];

        // Creating a new graph
        for(int i = 0; i < len; i++) {
                p[i] = (pLNode)g->AddNode();
        }

        // Performing some transformations
        g->AddEdge(p[0],p[1]);
        g->AddEdge(p[0],p[2]);
        g->AddEdge(p[0],p[3]);
        g->AddEdge(p[1],p[5]);
        g->AddEdge(p[2],p[6]);
        g->AddEdge(p[2],p[5]);
        g->AddEdge(p[3],p[4]);
        g->AddEdge(p[4],p[7]);
        g->AddEdge(p[4],p[9]);
        g->AddEdge(p[5],p[8]);
        g->AddEdge(p[6],p[9]);
        g->AddEdge(p[1],p[8]);
        g->AddEdge(p[1],p[7]);
        g->AddEdge(p[1],p[6]);
        g->AddEdge(p[1],p[5]);
        g->AddEdge(p[1],p[9]);

        //g->Layout();
        //g.Dump();

        //printf("maxrank = %i\n",g.getMaxrank());

        // Clean up
        //g.Destroy();
        //delete []p;

        //printf("Layout test passed!\n");
        return g;
}


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
void MainScene::resizeEvent(QResizeEvent * resize) {
    ui->CFGView->setGeometry(QRect(default_view_x,
                                   default_view_y,
                                   resize->size().width(),
                                   resize->size().height()));
}

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
        buf_node = new GNode(ui->CFGView, ((pLNode)(*node_iter))->IsDummy(), (*node_iter)->id());
        nodes_map[*node_iter] = buf_node;
        buf_node->setPos(((pLNode)(*node_iter))->getX(), ((pLNode)(*node_iter))->getY());
        if (((pLNode)(*node_iter))->IsDummy())
            buf_node->setVisible(false);
        m_scene->addItem(buf_node);
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
