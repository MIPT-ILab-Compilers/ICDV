/** 
 * @file: LEdge.cpp
 */

#include "Layout.h"

void LEdge::BreakLongEdge(){
	
	///Difference between rank of the "in" and "out"  nodes
        int n = ((pLNode) to())->Rank() - ((pLNode) from())->Rank();

        pLNode prevnode = ((pLNode) from());
        pLNode newnode;

        ///Adding n-1 nodes to do all rank differences equal 1
        for (int i = 1; i < n; i++){
                newnode = (pLNode) graph()->AddNode();
		newnode->dummy = true;
		newnode->rank = (((pLNode) from())->Rank()) + i;
                graph()->AddEdge(prevnode, newnode);
		prevnode = newnode;
        }
        graph()->AddEdge(prevnode, to());
        graph()->DeleteEdge(from(), to());
}
