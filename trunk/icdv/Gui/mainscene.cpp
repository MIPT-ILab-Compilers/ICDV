#include <QFileDialog>
#include <QString>

#include <map>

#include "mainscene.h"
#include "ui_mainscene.h"
#include "DumpParser.h"

#define node_heigh 10
#define node_width 10

LGraph * VisTest()
{
        LGraph * g = new LGraph();

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

        g->Layout();
        return g;
}

MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene) {
    ui->setupUi(this);
    m_graph = new LGraph();
    view = new QGraphicsScene(ui->CFGView->sceneRect());
}

MainScene::~MainScene() {
    if (ui)
        delete ui;

    if (m_graph)
        m_graph->Destroy();

    if (view)
        delete view;
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

// TODO(Lega): it needs to be tested on real dump.
// TODO(Lega): add nodes information displaying.
bool MainScene::Draw() {
    ui->DumpProp->setText("Draw started");
    if (ui->CFGView == NULL) {
        printf("Cannot init QGraphicsView!\n");
        return false;
    }

    if (m_graph == NULL) {
        ui->statusbar->showMessage("Cannot display the dump");
        return false;
    }

    if (view == NULL)
        view = new QGraphicsScene(ui->CFGView->sceneRect());

    // It's a test version.
    // TODO(Lega): make layout working with parser.
    // m_graph = VisTest();
    m_graph->Layout();

    map<pNode, bool> nodes_drawed;

    for (list<pNode>::iterator iter = m_graph->nodes_list()->begin();
         iter != m_graph->nodes_list()->end();
         iter++)
        if (((pLNode)(*iter))->IsDummy())
            nodes_drawed[*iter] = false;
        else
            nodes_drawed[*iter] = true;

    for (list<pEdge>::iterator iter = m_graph->edges_list()->begin();
         iter != m_graph->edges_list()->end();
         iter++) {

        if (nodes_drawed[(*iter)->from()]) {
            view->addEllipse((*iter)->from()->x-node_width/2, (*iter)->from()->y-node_heigh/2,
                             node_width, node_heigh);
            nodes_drawed[(*iter)->from()] = false;
        }

        if (nodes_drawed[(*iter)->to()]) {
            view->addEllipse((*iter)->to()->x-node_width/2, (*iter)->to()->y-node_heigh/2,
                             node_width, node_heigh);
            nodes_drawed[(*iter)->to()] = false;
        }

        view->addLine((*iter)->from()->x, (*iter)->from()->y,
                      (*iter)->to()->x, (*iter)->to()->y);
    }

    ui->CFGView->setScene(view);
    ui->CFGView->show();

    return true;
}
