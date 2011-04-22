#include "LayoutIterationDialog.h"
#include "ui_LayoutIterationDialog.h"

#include <QEventLoop>
#include <QTimer>
#include <QObject>

LayoutIterationDialog::LayoutIterationDialog(QMainWindow *parent) :
    QDialog(parent),
    ui(new Ui::LayoutIterationDialog)
{
    ui->setupUi(this);
    ui->layoutSpinBox->setValue(3);
    setWindowTitle("Set layout iterations");
    setFocus();
    raise();
    QEventLoop eventLoop;
    this->setEnabled(true);
    QObject::connect(ui->buttonBox, SIGNAL(accepted()), &eventLoop, SLOT(returnValue()));

}

LayoutIterationDialog::~LayoutIterationDialog()
{
    delete ui;
}

int LayoutIterationDialog::GetLayoutIterations() {
    return ui->layoutSpinBox->value();
}
