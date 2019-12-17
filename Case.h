#pragma once


class Case {
private:
	int i;
	int j;
	float color[3];


public:
	Case(int _i, int _j);

	void setColor(float c1, float c2, float c3);
	void display() const;
};
