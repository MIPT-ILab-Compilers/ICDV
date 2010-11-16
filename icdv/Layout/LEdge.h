/** 
 * @file: LEdge.h
 */

/// Edge with Layout methods
/**
 * This class contains one new variable:
 */
class LEdge: public Edge {
	bool reverse;
public:
	LEdge(pLNode from, pLNode to): Edge((pNode)from, (pNode)to){
		reverse = 0;
	}
	friend LGraph;
	friend LNode;
};