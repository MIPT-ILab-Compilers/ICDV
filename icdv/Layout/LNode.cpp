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
	if ( (* in_edges_list()).empty()){
		rank  = 0;
	}else{
		// Rank defines as max Rank of adjacent inoming node.
		int res=0;
		int temp;
		for (list<pEdge>::iterator edge_iter = (*in_edges_list()).begin();
			edge_iter != (*in_edges_list()).end(); 
			edge_iter++){
				if ((temp =( ( (LNode *) ((LEdge *) (*edge_iter))->from())->Rank()+1)) > res){
					res = temp;
				}
		}
		rank = res;
	}
	we_were_here = 1;
	return rank;
}
