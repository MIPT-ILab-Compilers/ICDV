/** 
 * @file: LEdge.h
 */

#ifndef LAYOUT_EDGE_H
#define LAYOUT_EDGE_H

/// Edge with Layout methods
/**
 * This class contains one new variable: reverse
 * And method BreakLongEdge() for better drawing long edges
 */
class LEdge: public Edge {
public:
        LEdge(pLNode from, pLNode to): Edge((pNode)from, (pNode)to) {
		reverse = false;
	}

        friend class LGraph;
        friend class LNode;

	/**
	 *  Lond edge is one with length(L) more than one rank.
	 *	This method makes L-1 dummy nodes and L edges between them 
	 *  to do this edge shorter
	 */
	void BreakLongEdge();
};

#endif
