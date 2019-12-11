#pragma once

#include "Character.h"

class NodeGraph {
private:
	int i;
	int j;
	float d;
	bool verified;
	NodeGraph *predecesseur;
	Character * c;

public:
	NodeGraph(int _i, int _j);

	~NodeGraph();

	float getX() const;
	float getZ() const;
	int getI() const {return i;};
	int getJ() const { return j; };
	void setCharacter(Character * _c) { c = _c; };
	bool isEmpty() const;
	void setDistance(float _d) {d = _d;};
	float getDistance() { return d; };
	void setVerified(bool _v) { verified = _v; };
	bool isVerified() { return verified; };
	bool equals(NodeGraph * n) const;
	NodeGraph* getPredecesseur() const { return predecesseur; };
	void setPredecesseur(NodeGraph * _predecesseur) {predecesseur = _predecesseur;};
};
