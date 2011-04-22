#ifndef LAYOUTITERATIONDIALOG_H
#define LAYOUTITERATIONDIALOG_H

#include <QDialog>

namespace Ui {
    class LayoutIterationDialog;
}

class LayoutIterationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LayoutIterationDialog(QWidget *parent = 0);
    ~LayoutIterationDialog();

    int GetLayoutIterations();

private:
    Ui::LayoutIterationDialog *ui;
};

#endif // LAYOUTITERATIONDIALOG_H
