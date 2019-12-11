#pragma once

#include "EdgeGraph.h";
#include "NodeGraph.h";
#include <list>;


class Graph {
private:
	std::list<NodeGraph*> nodes;
	std::list<EdgeGraph*> edges;

public:
	Graph();
	
	~Graph();

	void init();
	void update();

	static float distance(NodeGraph * n1, NodeGraph * n2);
	NodeGraph * getNode(int i, int j) const;
	NodeGraph * getMinNode();
	std::list<NodeGraph*> getVoisins(NodeGraph * n) const;
	bool allVerified() const;
	void updateDist(NodeGraph * s, NodeGraph * v);

	std::list<NodeGraph*> getShorterPath(NodeGraph * startingNode, NodeGraph * targetNode);
};