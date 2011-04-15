#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QList>

class GEdge;
class GraphWidget;
class QGraphicsSceneMouseEvent;

class GNode : public QGraphicsItem
{
public:
    GNode(QGraphicsView *graphWidget);

    void addEdge(GEdge *edge);
    QList<GEdge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const { return Type; }

    void calculateForces();
    bool advance();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    //QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    //void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QList<GEdge *> edgeList;
    QPointF newPos;
    GraphWidget *graph;
};

#endif
