/** 
 * @file: LNode.cpp
 */

#include "Layout.h"

/* Ranking */
int  LNode::Rank(){
	// If rank is determined before..
	if (rank >= 0) return rank;

    assert( !we_were_here );
	// If node has no incoming edges rank defines as 0
	if (in_edges_list()->empty()){
		rank  = 0;
	}else{
		// Rank defines as max Rank of adjacent inoming node.
		int res = 0;
		int temp = 0;
		for (list<pEdge>::iterator edge_iter = in_edges_list()->begin();
			edge_iter != in_edges_list()->end(); 
			edge_iter++){
				temp =((pLNode) (*edge_iter)->from())->Rank()+1;
				if (temp  > res){
					res = temp;
				}
		}
		rank = res;
	}
	we_were_here = true;
	return rank;
}


int LNode::Median(Ordering order,bool direction){
        vector<int> list;
	if (direction == MEDIAN_IN )
		list = order.AdjInPositions(this);
	else
		list = order.AdjOutPositions(this);

	int size = list.size();
	int m = size / 2;
	
	if (size     == 0) {return -1; }
	if (size % 2 == 1) {return (list[m]); }
	if (size == 2) {return (list[0] + list[1]) / 2; }

	int left = list[m - 1] - list[0];
	int right = list[size - 1] - list[m];
 
	return (list[m-1] * right + list[m] * left) / (left + right);
	
}



bool LNode::IsAdjacentToNode(pLNode node) {
	for(list<pEdge>::iterator edge_iter = out_edges_list()->begin(); 
		edge_iter != out_edges_list()->end();
		edge_iter++){
			if ( (pLNode)( (*edge_iter)->to())== node)
				return true;
	}
	return false;
}

