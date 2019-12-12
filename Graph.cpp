#include "Graph.h"
#include "Param.h"
#include "Game.h";
#include <iostream>

using namespace std;

Graph::Graph() {
	this->init();
}

Graph::~Graph() {
	for (auto n = nodes.begin(); n != nodes.end(); n++){
		delete *n;
	}

	for (auto e = edges.begin(); e != edges.end(); e++) {
		delete *e;
	}
}


void Graph::init() {
	//Fonction d'initialisation du graphe d'adjacence

	//Création des nodes
	for (int i = 0; i < Param::nbRows; i++) {
		for (int j = 0; j < Param::nbColumns; j++) {
			nodes.push_back(new NodeGraph(i, j));
		}
	}

	

	//Création des edges
	for (int i = 0; i < Param::nbRows; i++) {
		for (int j = 0; j < Param::nbColumns; j++) {
			for (int n = -1; n <= 1; n++) {
				for (int m = -1; m <= 1; m++) {
					if (n == 0 && m == 0) {
						//On ne fait rien puisque cela correspond à relier la case i,j à la case i,j
					}
					else {
						if (i + n < 0 || j + m < 0 || i + n >= Param::nbRows || j + m >= Param::nbColumns) {
							//On ne fait rien puisque cette case n'existe pas
						}
						else {
							edges.push_back(new EdgeGraph(this->getNode(i + n, j + m), this->getNode(i, j)));
							edges.push_back(new EdgeGraph(this->getNode(i, j), this->getNode(i + n, j + m)));
						}	
					}
				}
			}
		}
	}


	update(); //Pas forcément nécessaire dès l'init puisque ce sera obligatoirement fait avant tout calcul de chemin le plus court
}

void Graph::update() {
	//Update le graphe

	//Update des nodes
	for (auto it = nodes.begin(); it != nodes.end(); it++) {
		//Modifications des character présents sur les noeuds
		(*it)->setCharacter(Game::currentInstance->getBoard()->findChampion((*it)->getI(), (*it)->getJ()));
	}

	//Update des edges
	for (auto it = edges.begin(); it != edges.end(); it++) {
		(*it)->setWeight();
	}

}

float Graph::distance(NodeGraph * n1, NodeGraph * n2) {
	//Distance entre deux cases : utilisé dans le calcul du poids
	float d = sqrt(pow(n2->getX() - n1->getX(), 2) + pow(n2->getZ() - n1->getZ(), 2));

	return d;
}


NodeGraph* Graph::getNode(int i, int j) const {
	auto it = nodes.begin();
	
	advance(it, i*Param::nbColumns + j);
	
	return (*it);
}

list<NodeGraph*> Graph::getShorterPath(NodeGraph * startingNode, NodeGraph * targetNode) {
	this->update();

	//Algorithme de dijkstra

	//Initialisation
	for (auto it = nodes.begin(); it != nodes.end(); it++) {
		(*it)->setDistance(-1);
		(*it)->setVerified(false);
	}
	startingNode->setDistance(0);


	while (this->allVerified() != true) {
		NodeGraph * s = this->getMinNode();
		s->setVerified(true);
		list<NodeGraph*> voisins = this->getVoisins(s);
		for (auto v = voisins.begin(); v != voisins.end(); v++) {
			this->updateDist(s, *v);
		}
	}


	list<NodeGraph*> path;
	NodeGraph * s = targetNode->getPredecesseur();
	while (s->equals(startingNode) == false) {
		path.push_back(s);
		s = s->getPredecesseur();
	}
	path.reverse();
	return path;
}


NodeGraph* Graph::getMinNode() {
	float min = -1;
	NodeGraph *s = nullptr;
	for (auto it = nodes.begin(); it != nodes.end(); it++) {
		if ((*it)->isVerified()) {
			//Le node a déjà été traité donc on ne s'y intéresse pas
		}
		else {
			if ((*it)->getDistance() != -1){
				//La distance n'est pas infini
				if ((*it)->getDistance() < min || min == -1) {
					min = (*it)->getDistance();
					s = (*it);
				}
			}
		}
	}

	return s;
}


list<NodeGraph*> Graph::getVoisins(NodeGraph * n) const{
	list<NodeGraph*> voisins;
	
	for (auto it = edges.begin(); it != edges.end(); it++) {
		if (((*it)->getN1())->equals(n)) {
			voisins.push_back((*it)->getN2());
		}
	}
	return voisins;
}

bool Graph::allVerified() const{
	//Renvoie true si tous les nodes ont été vérifiés

	bool drap = true;
	for (auto it = nodes.begin(); it != nodes.end(); it++) {
		drap = drap && (*it)->isVerified();
	}

	return drap;
}

void Graph::updateDist(NodeGraph * s, NodeGraph * v) {
	if (v->getDistance() > s->getDistance() + EdgeGraph::getWeight(s, v) || v->getDistance() == -1) {
		v->setDistance(s->getDistance() + EdgeGraph::getWeight(s, v));
		v->setPredecesseur(s);
	}
}