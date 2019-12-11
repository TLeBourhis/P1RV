#include "EdgeGraph.h"
#include "Graph.h"
#include "Param.h"
#include <iostream>

using namespace std;

EdgeGraph::EdgeGraph(NodeGraph * _n1, NodeGraph * _n2) {
	n1 = _n1;
	n2 = _n2;

	setWeight(); //Initialisation du poids
}


EdgeGraph::~EdgeGraph() {
	delete n1;
	delete n2;
};

void EdgeGraph::setWeight() {
	//Somme entre la distance entre les deux noeuds + une constante si l'un des noeuds est occupé.
	w = Graph::distance(n1, n2);

	if (!n2->isEmpty()) {
		//La case est déjà occupée donc on augmente le poids pour qu'il soit "infini"
		w += Param::Cinf;
	}
}

float EdgeGraph::getWeight(NodeGraph * n1, NodeGraph * n2) {
	float w = Graph::distance(n1, n2);

	if (!n2->isEmpty()) {
		//La case est déjà occupée donc on augmente le poids pour qu'il soit "infini"
		w += Param::Cinf;
	}

	return w;
}
