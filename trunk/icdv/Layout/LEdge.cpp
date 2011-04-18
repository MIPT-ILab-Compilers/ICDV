/** 
 * @file: LEdge.cpp
 */

#include "Layout.h"

void LEdge::BreakLongEdge(){
	
	///Difference between rank of the "in" and "out"  nodes
        int n = ((pLNode) to())->Rank() - ((pLNode) from())->Rank();

        pLNode prevnode = ((pLNode) from());
        pLNode newnode;

        bool is_reverse = reverse;
        pEdge new_edge;
        ///Adding n-1 nodes to do all rank differences equal 1
        for (int i = 1; i < n; i++){
               newnode = (pLNode) graph()->AddNode();
		newnode->dummy = true;
		newnode->rank = (((pLNode) from())->Rank()) + i;
               new_edge = graph()->AddEdge(prevnode, newnode);
               new_edge->SetReverse(is_reverse);
		prevnode = newnode;
        }
        new_edge = graph()->AddEdge(prevnode, to());
        new_edge->SetReverse(is_reverse);
        graph()->DeleteEdge(from(), to());
}
