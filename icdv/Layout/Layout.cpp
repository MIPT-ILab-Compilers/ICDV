/** 
 * @file: Layout.cpp
 */

#include "Layout.h"

/**
* Create a LGraph object and call some of its methods.
*/

void LayoutTest()
{
	printf("\nLayout test started..\n");

	LGraph g;

	int len = 10;
	pLNode *p = new pLNode[len];

	// Creating a new graph
	for(int i = 0; i < len; i++) {
		p[i] = (pLNode)g.AddNode();
	}
	for(int i = 0; i < len-1; i++) {
		g.AddEdge(p[i], p[i+1]);
	}
	for(int i = 2; i < len; i+=3) {
		g.AddEdge(p[i], p[i-2]);
	}
	g.Dump();

	// Performing some transformations
	g.DeleteNode(p[5]);
	g.DeleteNode(p[7]);
	g.DeleteEdge(p[3],p[4]);
	g.AddEdge(p[0],p[3]);
	g.AddEdge(p[4],p[9]);
	g.AddEdge(p[4],p[6]);
	g.Layout();

	g.Dump();

	// Clean up
	g.Destroy();
	delete []p;

	printf("Layout test passed!\n");
}
