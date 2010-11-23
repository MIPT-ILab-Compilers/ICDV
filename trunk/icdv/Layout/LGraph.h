/** 
 * @file: LGraph.h
 */

#ifndef LAYOUT_GRAPH_H
#define LAYOUT_GRAPH_H

/// Graph with Layout methods
/**
 * 
 */

class LGraph: public Graph {
public:
	/// Replacing revert eages from the ReverceEdges list.
	void ReverseReverseEdges(list<pEdge> &ReverseEdges);

	void Layout();
	/// Init feasible ranking.
	virtual void InitRank();
	virtual pLNode AddNode();
	virtual pLEdge AddEdge(pNode from, pNode to);
	virtual void FreeNode(pNode p);
	virtual void FreeEdge(pEdge p);
	friend LEdge;
	friend LNode;
};

#endif