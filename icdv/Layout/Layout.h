/** 
 * @file: Layout.h
 */

#ifndef LAYOUT_H
#define LAYOUT_H

#include "..\Graph\predecls.h"

class LGraph;
class LNode;
class LEdge;

typedef LGraph* pLGraph;
typedef LNode*  pLNode;
typedef LEdge*  pLEdge;

#include "LNode.h"
#include "LEdge.h"
#include "LGraph.h"

void LayoutTest();

#endif