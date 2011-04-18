/** 
 * @file: LEdge.h
 */

#ifndef LAYOUT_EDGE_H
#define LAYOUT_EDGE_H

/// Edge with Layout methods
/**
 * This class contains one new variable: reverse
 * And method BreakLongEdge() for better drawing long edges
 */
class LEdge: public Edge {
  private:
    list<pLEdge> *m_composite_edges;

  public:

        list<pLEdge> *composite_edges() {
            return m_composite_edges;
        }

        LEdge(pLNode from, pLNode to): Edge((pNode)from, (pNode)to) {
		reverse = false;
                m_composite_edges = NULL;
	}

        ~LEdge();

        friend class LGraph;
        friend class LNode;

	/**
	 *  Lond edge is one with length(L) more than one rank.
	 *	This method makes L-1 dummy nodes and L edges between them 
	 *  to do this edge shorter
	 */
	void BreakLongEdge();
        void CompositeEdgesDump();
};

#endif
