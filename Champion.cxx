#include "Champion.h"
#include <string>
#include "Param.h"
#include "Character.h"
#include <GL\glew.h>
#include <GL\freeglut.h>

using namespace std;

Champion::Champion(string _name, int _armor, int _magicResistance, float _spellPower, int _attackRange, float _attackSpeed, int _health, int _attackDamage, int _i, int _j, int _caseID, int _level, /*Race *_races[2],*/ int _cost) : Character(_name, _armor, _magicResistance, _spellPower, _attackRange, _attackSpeed, _health, _attackDamage, _i, _j, _caseID){
  level = _level;
  //races = _races;
  cost = _cost;
  setColor();

}


Champion::~Champion(){
//  delete races[0];
  //delete races[1];
  delete this;
}



void Champion::fight(list<Character*> allies, list<Character*> ennemies){
  //Gère les actions du champion lors du combat.

}


void Champion::displayCard(int i) const{
  //Affiche les "cards" du champion lors de la pioche.




  // Effacement du frame buffer
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //Affichage des bordures de la carte:
  glColor3f(1.0f,1.0f,1.0f);
  glBegin(GL_QUADS);

  glEnd();

  glutSwapBuffers();
}

void Champion::evolve(){
  //Fait evoluer le champion au niveau supérieur et modifie ses stats

}

void Champion::dragndrop(int _x, int _y){
  //Gère le piquer/déplacer du champion suite à l'action de l'utilisateur
	i = abs(_x / (Param::dimCase + 2 * Param::borderSpacingCase));
	j = abs(_y / (Param::dimCase + 2 * Param::borderSpacingCase));
}

int Champion::buy(){

  return -cost;
}

int Champion::sell(){

  return cost;//ATTENTION : Changer le cost du champion évolué pour la vente
}


void Champion::display() const{

  glMatrixMode(GL_MODELVIEW);

  glPushMatrix();

  glLoadIdentity();

  glColor4f(color[0],color[1],color[2],color[3]);

  glTranslatef(i*(2*Param::borderSpacingCase+Param::dimCase)+Param::borderSpacingCase+Param::dimCase/2, 4.0f, j*(2*Param::borderSpacingCase+Param::dimCase)+Param::borderSpacingCase+Param::dimCase/2);
  glutSolidSphere(4.0f,20,20);

  glPopMatrix();
}

void Champion::move(int _x, int _y){

}

void Champion::move(Character *target){

}

int Champion::die(){
	this -> alive = false;
	return 0;
}
