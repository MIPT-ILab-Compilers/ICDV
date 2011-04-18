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

        ~LEdge(){
            if (m_composite_edges != NULL){
                list<pLEdge> *temp_list =m_composite_edges;
                delete m_composite_edges;
                for(list<pLEdge>::iterator edge_iter = temp_list->begin();
                    edge_iter != temp_list->end();
                    edge_iter++){
                            ((pLEdge) *edge_iter)->m_composite_edges = NULL;
                    }
            }
        }

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
