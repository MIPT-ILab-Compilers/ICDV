#include "dumpview.h"
#include "ui_dumpview.h"

DumpView::DumpView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DumpView)
{
    this->setWindowTitle("Dump node properties.");
    ui->setupUi(this);
}

void DumpView::SetText(const QString &source) {
    m_source.clear();
    if (source.isEmpty())
        m_source += "No properties for this node.";
    else
        m_source += source;
    ui->DumpLabel->setAlignment(Qt::AlignHCenter);
    ui->DumpLabel->setText(m_source);
}

void DumpView::DeleteText() {
    m_source.clear();
}

DumpView::~DumpView()
{
    delete ui;
}
