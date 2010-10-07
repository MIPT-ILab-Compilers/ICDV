/** 
 * @file: Graph.h
 */
#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

/// Class for representation of directed graphs
/**
 * A directed graph or digraph is a pair G = (N,E) of: <br>
 *        * a set N, whose elements are called nodes, <br>
 *        * a set E of ordered pairs of vertices, directed edges <br><br>
 *
 * Graph contains list of nodes, list of edges, and the corresponding counters.<br>
 * It incapsulates all the work with memory allocation/deallocation, thus 
 * the user has no need to worry about it.
 */
class Graph {
protected:
	list<pNode> m_nodes_list;
	list<pEdge> m_edges_list;
	int m_total_nodes_num;
	int m_total_edges_num;
public:
	Graph() :
		m_total_nodes_num(0), 
		m_total_edges_num(0)
	{};
	virtual ~Graph() {
		Destroy();
	}

	/// Add a new node to the graph
	/**
	 * Allocate memory, create new node and insert it to nodes list of the graph
	 *  \sa AddEdge, DeleteNode, DeleteEdge
	 */
	virtual pNode AddNode();

	/// Connect nodes from and to
	/**
	 * Allocate needed memory, create new edge and insert it to 
	 * edges lists of nodes from and to, and to edges list of graph
	 *	\param from - start node of the edge
	 *	\param to   - end node of the edge
	 *  \sa AddNode, DeleteNode, DeleteEdge
	 */
	virtual pEdge AddEdge(pNode from, pNode to);

	/// Delete node from the graph and all its incoming and outgoing edges, 
	/// and free memory, allocated for node
	/** 
	 *	\param node - not to be deleted
	 *  \sa AddNode, AddEdge, DeleteEdge
	 */
	virtual void DeleteNode(pNode node);
	
	/// Delete edge between nodes from and to, and free allocated memory
	/** 
	 *	\param from - node from
	 *	\param to   - node to
	 *  \sa AddNode, AddEdge, DeleteNode
	 *  \return True if edge from->to had existed, False otherwise.
	 */
	virtual bool DeleteEdge(pNode from, pNode to);

	/// Free memory used for Node p
	virtual void  FreeNode(pNode p);
	/// Free memory used for Edge p
	virtual void  FreeEdge(pEdge p);

	virtual void Dump(); ///< Dump all nodes and edges
	virtual void Destroy(); ///< Delete all nodes and edges
	friend class Node;
	friend class Edge;
};

#endif
