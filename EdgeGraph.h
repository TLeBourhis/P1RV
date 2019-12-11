#pragma once

#include "NodeGraph.h"

class EdgeGraph {
private:
	NodeGraph * n1;
	NodeGraph * n2;
	float w; //Poids du lien

public:
	EdgeGraph(NodeGraph * _n1, NodeGraph * _n2);

	~EdgeGraph();

	void setWeight();
	NodeGraph * getN1() { return n1; };
	NodeGraph * getN2() { return n2; };

	static float getWeight(NodeGraph * n1, NodeGraph * n2);
};