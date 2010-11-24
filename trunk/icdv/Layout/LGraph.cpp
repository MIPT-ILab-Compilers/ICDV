/** 
 * @file: LGraph.cpp
 */

#include "Layout.h"

void LGraph::Layout(){
	list<pEdge> ReverseEdges;
	FindReverseEdges(ReverseEdges);
	ReverseReverseEdges(ReverseEdges);
	InitRank();	
	list<pEdge> LongEdges;
	FindLongEdges(LongEdges);
	AddDummyNodes(LongEdges);
	
	// Ordering

}


void LGraph::InitRank(){
	// Calculating the rank for all Nodes
	for (list<pNode>::iterator node_iter = (*nodes_list()).begin();
		node_iter != (*nodes_list()).end(); 
		node_iter++){
			int rank;
			rank = ((LNode *)(*node_iter))->Rank();
#ifdef DEBUG
			printf("Node:%i  rank:%i\n",((LNode *)(*node_iter))->id(),rank);
#endif
	}
}


void LGraph::ReverseReverseEdges(list<pEdge> &ReverseEdges){
	for (list<pEdge>::iterator edge_iter = ReverseEdges.begin();
		edge_iter != ReverseEdges.end();
		edge_iter++){
			((pLEdge) (*edge_iter))->Reverse();
	}				
}

void LGraph::FindLongEdges(list<pEdge> &LongEdges){
	for (list<pEdge>::iterator edge_iter = (*edges_list()).begin();
		edge_iter != (*edges_list()).end();
		edge_iter++){
			if (((pLNode) (*edge_iter)->to())->Rank() - ((pLNode) (*edge_iter)->from())->Rank() > 1){
				printf("BigEdge:%i\n",(*edge_iter)->id());
				LongEdges.push_back(*edge_iter);
			}
	}			
}

void LGraph::AddDummyNodes(list<pEdge> &LongEdges){
for (list<pEdge>::iterator edge_iter = LongEdges.begin();
		edge_iter != LongEdges.end();
		edge_iter++){
			((pLEdge) (*edge_iter))->BreakLongEdge();
	}			
}

void LGraph::FreeNode(pNode p){
	assert(p != NULL);
	delete (pLNode)p;
}

void LGraph::FreeEdge(pEdge p){
	assert(p != NULL);
	delete (pLEdge)p;
}

pLNode LGraph::AddNode()
{
	pLNode new_node = new LNode(this);
	return new_node;
}

pLEdge LGraph::AddEdge(pNode from, pNode to)
{
	pLEdge new_edge = new LEdge((pLNode)from,(pLNode)to);
	return new_edge;
}
