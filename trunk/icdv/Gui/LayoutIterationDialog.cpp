#include "LayoutIterationDialog.h"
#include "ui_LayoutIterationDialog.h"

LayoutIterationDialog::LayoutIterationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LayoutIterationDialog)
{
    ui->setupUi(this);
    ui->layoutSpinBox->setValue(3);
    setWindowTitle("Set layout iterations");
}

LayoutIterationDialog::~LayoutIterationDialog()
{
    delete ui;
}

int LayoutIterationDialog::GetLayoutIterations() {
        return ui->layoutSpinBox->value();
    }
