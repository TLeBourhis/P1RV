#include "NodeGraph.h"
#include "Param.h"

using namespace std;

NodeGraph::NodeGraph(int _i, int _j) {
	i = _i;
	j = _j;
	d = 0;
	verified = false;
	c = nullptr;
}

NodeGraph::~NodeGraph() {
	delete c;
}


float NodeGraph::getX() const {
	return i*(Param::dimCase + 2 * Param::borderSpacingCase) + Param::borderSpacingCase + Param::dimCase / 2;
}

float NodeGraph::getZ() const {
	return j*(Param::dimCase + 2 * Param::borderSpacingCase) + Param::borderSpacingCase + Param::dimCase / 2;
}

bool NodeGraph::isEmpty() const {
	return c == nullptr;
}

bool NodeGraph::equals(NodeGraph * n) const {
	return i == n->i && j == n->j;
}