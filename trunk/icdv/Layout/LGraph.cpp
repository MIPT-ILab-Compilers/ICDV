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
	Ordering order;
	order.order_vector = InitOrder();
	for (int i = 0; i <= 26; i++) {
		WeightedMedianHeuristic(&order,i);
		Transpose(&order);
	}
#ifdef DEBUG
	InitPos(order);
	printf("Crossings:%d\n",countCrossing(order));
#endif
        order.Dump();
}


void LGraph::InitRank() {
	// Calculating the rank for all Nodes
	for (list<pNode>::iterator node_iter = nodes_list()->begin();
		node_iter != nodes_list()->end(); 
		node_iter++){
                        unsigned int rank = ((LNode *)(*node_iter))->Rank();
			if (rank > maxrank)
				maxrank = rank;
	}
}

vector< vector<pLNode> > LGraph::InitOrder() {
        vector< vector<pLNode> > order(maxrank + 1);
	for (list<pNode>::iterator node_iter = nodes_list()->begin();
	node_iter != nodes_list()->end();
	node_iter++) {
                order[((pLNode) (*node_iter))->Rank()].push_back((pLNode) (*node_iter));
	}
	return order; 
}

void LGraph::ReverseReverseEdges(list<pEdge> &ReverseEdges){
	for (list<pEdge>::iterator edge_iter = ReverseEdges.begin();
		edge_iter != ReverseEdges.end();
		edge_iter++)
			((pLEdge) (*edge_iter))->Reverse();
}

void LGraph::FindLongEdges(list<pEdge> &LongEdges){
	for (list<pEdge>::iterator edge_iter = edges_list()->begin();
		edge_iter != edges_list()->end();
		edge_iter++){
			if (((pLNode) (*edge_iter)->to())->Rank() - 
				((pLNode) (*edge_iter)->from())->Rank() > 1)
				LongEdges.push_back(*edge_iter);
	}			
}

void LGraph::AddDummyNodes(list<pEdge> &LongEdges){
for (list<pEdge>::iterator edge_iter = LongEdges.begin();
		edge_iter != LongEdges.end();
		edge_iter++){
			((pLEdge) (*edge_iter))->BreakLongEdge();
	}			
}

/// Comparator to work with pointers
bool ComparePointer(pLNode node1, pLNode node2)
{
        return node1->getMedian() < node2->getMedian();
}

void LGraph::WeightedMedianHeuristic(Ordering* order,int iter){
        //Ordering  temp_order = (*order); // temp order
        Ordering temp_order;
        temp_order.order_vector = order->order_vector;
	if (iter % 2 == 0) {
                for(unsigned int r = 1; r <= maxrank; r++ ){
                        for(unsigned int i = 0;i < temp_order.order_vector[r].size(); i++) {
                                temp_order.order_vector[r][i]->median =
                                        temp_order.order_vector[r][i]->Median(*order,MEDIAN_IN);
			}
                        /// Sort temp_order using ComparePointer comparator
                        sort(temp_order.order_vector[r].begin(),
                                temp_order.order_vector[r].end(),
				ComparePointer); 
		}
	} else {
		for(int r = maxrank - 1; r >= 0; r-- ){			
                        for(unsigned int i = 0;i < temp_order.order_vector[r].size(); i++) {
                                temp_order.order_vector[r][i]->median =
                                        temp_order.order_vector[r][i]->Median(*order,MEDIAN_OUT);
			}
                        sort(temp_order.order_vector[r].begin(),
                                temp_order.order_vector[r].end(),
				ComparePointer);
		}
	}
        InitPos(temp_order);
        int cross_temp_order = countCrossing(temp_order);

	InitPos(*order);
	int cross_order = countCrossing(*order);
        if (cross_temp_order <= cross_order){
                order->order_vector = temp_order.order_vector;
	}
}

int LGraph::countCrossing(Ordering order){
	int crossing = 0;
        for (unsigned int rank = 0; rank < maxrank - 1; rank++)
		crossing += countCrossingOnRank(order,rank);
	return crossing;
}

int LGraph::countCrossingOnRank(Ordering order,int rank){
	int crossing = 0;
	
	// Making list of all edges betwen rank and rank+1
        vector<pLEdge> edge_list;
        for (unsigned int i = 0; i < order.order_vector[rank].size(); i++){
		for (list<pEdge>::iterator edge_iter = 
			order.order_vector[rank][i]->out_edges_list()->begin();
			edge_iter != order.order_vector[rank][i]->out_edges_list()->end();
			edge_iter++){
                                edge_list.push_back((pLEdge)(*edge_iter));
		}
	}

        for (unsigned int i = 0; i < edge_list.size(); i++){
                for (unsigned int j = i + 1; j < edge_list.size(); j++){
			//Criterion of crossing edge_list[i] and edge_list[j] 
			int cmp1 = ((pLNode)edge_list[i]->to())->pos -
						((pLNode)edge_list[j]->to())->pos;

			int cmp2 = ((pLNode)edge_list[i]->from())->pos -
						((pLNode)edge_list[j]->from())->pos;

			if ((cmp1 > 0 && cmp2 < 0) || (cmp1 < 0 && cmp2 > 0))
				crossing++;
		}
	}
	return crossing;
}	

void LGraph::InitPos(Ordering order){
        for(unsigned int rank = 0; rank < maxrank; rank++)
                for(unsigned int i = 0; i < order.order_vector[rank].size(); i++)
			order.order_vector[rank][i]->pos = i;
}

void LGraph::Transpose(Ordering *order){
	bool improved = true;
	while (improved){
		improved = false;
                for (unsigned int r = 0; r < order->order_vector.size(); r++){
                        for (unsigned int i = 0; i < order->order_vector[r].size() - 1; i++){
				pLNode v = order->order_vector[r][i];
				pLNode w = order->order_vector[r][i+1];
				InitPos(*order);
				int cross0 = countCrossing(*order);
				v->pos++;
				w->pos--;
				int cross1 = countCrossing(*order);
				if (cross1 < cross0){
					improved = true;
					order->order_vector[r][i] = w;
					order->order_vector[r][i + 1] = v;
				}
			}
		}
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
