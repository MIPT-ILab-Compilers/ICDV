/** 
 * @file: LNode.h
 */

#ifndef LAYOUT_NODE_H
#define LAYOUT_NODE_H

/// Extention of class Node for layout
/**
 * This node class contains new variable: 
 *		rank   - vertical relative position of node in the graph
 *		pos    - horisontal relative position
 *		median - temp value to calculate pos
 * Also there is some methods:
 *      Rank() to calculate rank
 *      Median() to calculate median
 *      IsAdjacentToNode is test for adjesent of 2 nodes
 */
class LNode: public Node {
private:
	int rank;
	int pos;
	int median;

	///Flag for the LNode::Rank()
	bool we_were_here;

	bool dummy;

public:
        // True, if it's an entry node.
	bool entry;
        // Number
	unsigned int uBlkId;
	list<unsigned int> m_preds_lst;
	list<unsigned int> m_succs_lst;
	list<unsigned int> m_exec_lst;
	list<unsigned int> m_prob_lst;

        bool IsDummy() {
            return dummy;
        }
public:
	/// Calculate node rank
	int Rank();
	
	int getMedian() {return median;}
	int getPos()    {return pos;}

        int getX() {return x;}
        int getY() {return y;}

	/** Calculate weighed median for the node.
	  * The median value of a vertex is defined as the median position of the adjacent vertices if that
	  *	is uniquely defined. Otherwise, it is interpolated between the two median positions using a
	  *	measure of tightness. Generally, the weighted median is biased toward the side where vertices are
	  *	more closely packed.
	  * 
	  * If direction == true then funcrion calculate IN MEDIAN
	  *	if false then OUT MEDIAN
	  */
	int Median(Ordering order,bool direction); 

	/// Return true if node is adjacent to this node
	bool IsAdjacentToNode(pLNode node);
	
	LNode(pLGraph pg): Node((pGraph)pg){
                x = y = -1;
		rank = -1;
		median = 0;
		we_were_here = false;
		dummy = false;
	}
        friend class LEdge;
        friend class LGraph;
};

#endif