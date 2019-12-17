#include "Case.h"
#include "Param.h"
#include <GL\glew.h>
#include <GL\freeglut.h>


Case::Case(int _i, int _j) {
	i = _i;
	j = _j;
	color[0] = Param::caseColor[0];
	color[1] = Param::caseColor[1];
	color[2] = Param::caseColor[2];
}

void Case::setColor(float c1, float c2, float c3) {
	color[0] = c1;
	color[1] = c2;
	color[2] = c3;
}


void Case::display() const {
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_QUADS);
	glVertex3f(j*(Param::dimCase + Param::borderSpacingCase * 2) + Param::borderSpacingCase, 0.1f, i*(Param::dimCase + Param::borderSpacingCase * 2) + Param::borderSpacingCase);
	glVertex3f((j + 1)*(Param::dimCase + Param::borderSpacingCase * 2) - Param::borderSpacingCase, 0.1f, i*(Param::dimCase + Param::borderSpacingCase * 2) + Param::borderSpacingCase);
	glVertex3f((j + 1)*(Param::dimCase + Param::borderSpacingCase * 2) - Param::borderSpacingCase, 0.1f, (i + 1)*(Param::dimCase + Param::borderSpacingCase * 2) - Param::borderSpacingCase);
	glVertex3f(j*(Param::dimCase + Param::borderSpacingCase * 2) + Param::borderSpacingCase, 0.1f, (i + 1)*(Param::dimCase + Param::borderSpacingCase * 2) - Param::borderSpacingCase);
	glEnd();
}