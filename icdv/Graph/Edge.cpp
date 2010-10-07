/** 
 * @file: Edge.cpp
 */
#include "predecls.h"

Edge::Edge(pNode from, pNode to):
	m_from(from),
	m_to(to)
{
	assert(from);
	assert(to);
	assert(from->m_graph == to->m_graph);

	pGraph pg = from->m_graph;
	assert(pg);

	m_id = pg->m_total_edges_num;
	pg->m_total_edges_num++;
	pg->m_edges_list.push_back(this);

	m_graph = pg;

	from->m_out_edges_list.push_back(this);
	to->m_in_edges_list.push_back(this);
};

void Edge::Dump() {
	printf("Edge %d: %d-->%d\n", m_id, m_from->m_id, m_to->m_id);
};

void Edge::Print() {
	printf("%d->%d", m_from->m_id, m_to->m_id);
};

