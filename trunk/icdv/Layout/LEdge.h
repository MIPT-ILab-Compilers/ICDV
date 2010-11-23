/** 
 * @file: LEdge.h
 */

#ifndef LAYOUT_EDGE_H
#define LAYOUT_EDGE_H

/// Edge with Layout methods
/**
 * This class contains one new variable: reverse
 * 
 */
class LEdge: public Edge {
	bool reverse; // flag is 1 if we alredy revert this edge for layout;
public:
	LEdge(pLNode from, pLNode to): Edge((pNode)from, (pNode)to){
		reverse = 0;
	}
	friend LGraph;
	friend LNode;
};

#endif