#ifndef DUMPVIEW_H
#define DUMPVIEW_H

#include <QWidget>
#include <QString>

namespace Ui {
    class DumpView;
}

class DumpView : public QWidget
{
    Q_OBJECT

public:
    explicit DumpView(QWidget *parent = 0);
    virtual ~DumpView();

    void SetText(const QString &source);
    void DeleteText();

private:
    QString m_source;
    Ui::DumpView *ui;
};

#endif // DUMPVIEW_H
