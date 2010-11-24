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

	///Vertical position of the node
	int rank;
	
	///Flag for the LNode::Rank()
	bool we_were_here;

	bool dummy;
public:
	/// Calculate node rank
	int Rank();
	LNode(pLGraph pg): Node((pGraph)pg){
		rank = -1;
		we_were_here = false;
		dummy = false;
	}
	friend LEdge;
	friend LGraph;
};

#endif