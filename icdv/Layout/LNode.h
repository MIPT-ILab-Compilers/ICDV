/** 
 * @file: LNode.h
 */

#ifndef LAYOUT_NODE_H
#define LAYOUT_NODE_H

/**
 * This class contains one new variable: rank
 * And method Rank() to calculate it.
 */
class LNode: public Node {
	int rank;
	bool we_were_here;
public:
	/// Calculate node rank
	int Rank();
	LNode(pLGraph pg): Node((pGraph)pg){
		rank = -1;
		we_were_here = 0;
	}
	friend LEdge;
	friend LGraph;
};

#endif