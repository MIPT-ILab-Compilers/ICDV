#ifndef DUMPVIEW_H
#define DUMPVIEW_H

#include <QWidget>
#include <QString>
#include <QResizeEvent>

namespace Ui {
    class DumpView;
}

class DumpView : public QWidget
{
    Q_OBJECT

public:
    explicit DumpView(int id, const QString &source, QWidget *parent = 0);
    virtual ~DumpView();

    const QString &SetText(const QString &source);
    void DeleteText();

    void resizeEvent(QResizeEvent * resize);

private:
    Ui::DumpView *ui;
};

#endif // DUMPVIEW_H
