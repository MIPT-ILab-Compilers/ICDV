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

 protected:
     QRectF boundingRect() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

 private:
     GNode *source, *dest;

     QPointF sourcePoint;
     QPointF destPoint;
     qreal arrowSize;
 };

 #endif
