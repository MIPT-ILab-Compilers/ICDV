/**
 * @file: GEdge.h
 */
#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class GNode;

class GEdge : public QGraphicsItem
{
public:
    GEdge(GNode *sourceNode, GNode *destNode);

    GNode *sourceNode() const;
    GNode *destNode() const;

    void adjust();

    enum { Type = UserType + 2 };
    int type() const { return Type; }

    void SetFromDummy(bool from_dummy) {
        is_from_dummy_node = from_dummy;
    }

    bool FromDummy() {
        return is_from_dummy_node;
    }

    bool ToDummy() {
        return is_to_dummy_node;
    }

    void SetToDummy(bool to_dummy) {
        is_to_dummy_node = to_dummy;
    }

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:
    bool reverse;
    bool is_from_dummy_node;
    bool is_to_dummy_node;
    GNode *source, *dest;
    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
};

#endif
